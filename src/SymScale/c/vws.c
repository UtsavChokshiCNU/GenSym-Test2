/* vws.c
 * Input file:  views.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "vws.h"


/* UI-STACK-ERROR-1 */
Object ui_stack_error_1(message_1,value)
    Object message_1, value;
{
    Object top_of_stack, message_2, temp;

    x_note_fn_call(222,0);
    top_of_stack = Cached_top_of_stack;
    message_2 = tformat_stack_error_text_string(2,message_1,value);
    temp = raw_stack_error_named_error(top_of_stack,message_2);
    return VALUES_1(temp);
}

static Object string_constant;     /* "No ~a found for handle ~s." */

/* FIND-NATIVE-VIEW-OR-STACK-ERROR */
Object find_native_view_or_stack_error varargs_1(int, n)
{
    Object gensym_window, handle;
    Object class_qm, temp, top_of_stack, message_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(222,1);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    handle = REQUIRED_ARG_nonrelocating();
    class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = find_native_window(3,gensym_window,handle,class_qm);
    if (temp)
	return VALUES_1(temp);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant,
		pretty_name_of_view_class(class_qm),handle);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

static Object Qg2_workspace_view;  /* g2-workspace-view */

static Object string_constant_1;   /* "Workspace View" */

static Object Qg2_tree_view;       /* g2-tree-view */

static Object string_constant_2;   /* "Tree View" */

static Object Qg2_html_view;       /* g2-html-view */

static Object string_constant_3;   /* "HTML View" */

static Object Qg2_shortcut_bar;    /* g2-shortcut-bar */

static Object string_constant_4;   /* "Shortcut Bar" */

static Object Qg2_chart_view;      /* g2-chart-view */

static Object string_constant_5;   /* "Chart View" */

static Object Qg2_dialog_view;     /* g2-dialog-view */

static Object string_constant_6;   /* "Dialog View" */

static Object Qg2_property_grid;   /* g2-property-grid */

static Object string_constant_7;   /* "Property Grid" */

static Object Qg2_status_bar;      /* g2-status-bar */

static Object string_constant_8;   /* "Status Bar" */

static Object Qg2_tabular_view;    /* g2-tabular-view */

static Object string_constant_9;   /* "Tabular View" */

static Object string_constant_10;  /* "Native View" */

static Object string_constant_11;  /* "View" */

/* PRETTY-NAME-OF-VIEW-CLASS */
Object pretty_name_of_view_class(view_class)
    Object view_class;
{
    x_note_fn_call(222,2);
    if (EQ(view_class,Qg2_workspace_view))
	return VALUES_1(string_constant_1);
    else if (EQ(view_class,Qg2_tree_view))
	return VALUES_1(string_constant_2);
    else if (EQ(view_class,Qg2_html_view))
	return VALUES_1(string_constant_3);
    else if (EQ(view_class,Qg2_shortcut_bar))
	return VALUES_1(string_constant_4);
    else if (EQ(view_class,Qg2_chart_view))
	return VALUES_1(string_constant_5);
    else if (EQ(view_class,Qg2_dialog_view))
	return VALUES_1(string_constant_6);
    else if (EQ(view_class,Qg2_property_grid))
	return VALUES_1(string_constant_7);
    else if (EQ(view_class,Qg2_status_bar))
	return VALUES_1(string_constant_8);
    else if (EQ(view_class,Qg2_tabular_view))
	return VALUES_1(string_constant_9);
    else if (EQ(view_class,Qnil))
	return VALUES_1(string_constant_10);
    else
	return VALUES_1(string_constant_11);
}

static Object Qnone;               /* none */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* STORED-CALLBACK-PROCEDURE */
Object stored_callback_procedure(value)
    Object value;
{
    Object x2, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(222,3);
    if (EQ(value,Qnone))
	return VALUES_1(Nil);
    else if (SYMBOLP(value))
	return VALUES_1(value);
    else {
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(value,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
	if (temp)
	    return get_primary_name_for_frame_if_any(value);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qforeground;         /* foreground */

static Object Qbackground;         /* background */

static Object Qtransparent;        /* transparent */

static Object Qcolor_value_vector_index_and_intensity;  /* color-value-vector-index-and-intensity */

static Object string_constant_12;  /* "~A is not a valid color name." */

/* VALID-COLOR-DESIGNATION-OR-STACK-ERROR */
Object valid_color_designation_or_stack_error(value)
    Object value;
{
    Object top_of_stack, message_1;

    x_note_fn_call(222,4);
    if ( !(SYMBOLP(value) && (EQ(value,Qforeground) || EQ(value,
	    Qbackground) || EQ(value,Qtransparent) || 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(value),
	    Qcolor_value_vector_index_and_intensity) || rgb_color_p(value) 
	    ||  !TRUEP(value) || EQ(value,Qnone) || rgb_color_p(value)))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_12,
		value);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
    else
	return VALUES_1(Nil);
}

static Object Qblack;              /* black */

static Object Qwhite;              /* white */

/* RGB-COLOR-VALUE-OR-STACK-ERROR */
Object rgb_color_value_or_stack_error(color)
    Object color;
{
    x_note_fn_call(222,5);
    valid_color_designation_or_stack_error(color);
    if (EQ(color,Qforeground))
	return rgb_value_of_gensym_color(Qblack);
    else if (EQ(color,Qbackground))
	return rgb_value_of_gensym_color(Qwhite);
    else if (EQ(color,Qnone) || EQ(color,Qtransparent) || EQ(color,Qnil))
	return VALUES_1(FIX((SI_Long)-1L));
    else
	return rgb_value_of_gensym_color(color);
}

/* NATIVE-ICON-HANDLE-OR-STACK-ERROR */
Object native_icon_handle_or_stack_error(gensym_window,value)
    Object gensym_window, value;
{
    x_note_fn_call(222,6);
    if ( !TRUEP(value) || EQ(value,Qnone))
	return VALUES_1(FIX((SI_Long)-1L));
    else {
	valid_icon_designation_or_stack_error(value);
	return send_native_icon(2,gensym_window,value);
    }
}

/* SECURE-TELEWINDOWS-CONNECTION-P */
Object secure_telewindows_connection_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,7);
    if (ISVREF(gensym_window,(SI_Long)12L))
	return VALUES_1(g2ext_secure_socket_p(IFIX(ISVREF(ISVREF(gensym_window,
		(SI_Long)12L),(SI_Long)1L))) == (SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* GET-VIEW-CALLBACK-IF-ANY */
Object get_view_callback_if_any(view)
    Object view;
{
    Object temp;

    x_note_fn_call(222,8);
    if (ISVREF(view,(SI_Long)27L)) {
	temp = ISVREF(view,(SI_Long)27L);
	return get_view_callback(temp,
		pretty_name_of_view_class(ISVREF(view,(SI_Long)14L)));
    }
    else
	return VALUES_1(Nil);
}

static Object list_constant;       /* # */

/* GET-VIEW-CALLBACK */
Object get_view_callback(name_or_frame,description)
    Object name_or_frame, description;
{
    x_note_fn_call(222,9);
    return get_callback_procedure(3,name_or_frame,description,list_constant);
}

static Object Qitem_reference;     /* item-reference */

static Object Qitem;               /* item */

static Object Qab_structure;       /* structure */

/* INVOKE-VIEW-CALLBACK-1 */
Object invoke_view_callback_1(view,procedure,event,item,info,user_data_qm)
    Object view, procedure, event, item, info, user_data_qm;
{
    Object user_data_ev, item_or_value, gensymed_symbol, temp, x2;
    Object svref_new_value, gensymed_symbol_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(222,10);
    if ( !TRUEP(user_data_qm))
	user_data_ev = Qnone;
    else if ( !(CONSP(user_data_qm) && EQ(M_CDR(user_data_qm),
	    Qitem_reference)))
	user_data_ev = FIXNUMP(user_data_qm) || user_data_qm && 
		SYMBOLP(user_data_qm) || SIMPLE_VECTOR_P(user_data_qm) ? 
		user_data_qm : copy_if_evaluation_value_1(user_data_qm);
    else {
	item_or_value = user_data_qm;
	if (CONSP(item_or_value) && EQ(M_CDR(item_or_value),
		Qitem_reference) ? TRUEP(ISVREF(M_CAR(item_or_value),
		(SI_Long)3L)) : TRUEP(item_or_value)) {
	    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)2L + 
		    (SI_Long)1L));
	    gensymed_symbol_1 = (SI_Long)0L;
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		svref_arg_2 = gensymed_symbol_1 + 
			IFIX(Managed_array_index_offset);
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
		SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qitem;
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		SVREF(temp,FIX((SI_Long)1L)) = Qitem;
	    }
	    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
		    Maximum_in_place_array_size)) {
		item_or_value = user_data_qm;
		item_or_value = CONSP(item_or_value) && 
			EQ(M_CDR(item_or_value),Qitem_reference) ? 
			ISVREF(M_CAR(item_or_value),(SI_Long)3L) : 
			item_or_value;
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
		SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
	    }
	    else {
		temp = ISVREF(gensymed_symbol,(SI_Long)2L);
		item_or_value = user_data_qm;
		item_or_value = CONSP(item_or_value) && 
			EQ(M_CDR(item_or_value),Qitem_reference) ? 
			ISVREF(M_CAR(item_or_value),(SI_Long)3L) : 
			item_or_value;
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
	    user_data_ev = eval_cons_1(gensymed_symbol,Qab_structure);
	}
	else
	    user_data_ev = Qnil;
    }
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_2 = gensymed_symbol;
    M_CAR(gensymed_symbol_2) = event;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp = g2_window_for_gensym_window_qm(ISVREF(view,(SI_Long)1L));
    M_CAR(gensymed_symbol_2) = temp;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp = ISVREF(view,(SI_Long)2L);
    M_CAR(gensymed_symbol_2) = temp;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(item) != (SI_Long)0L ? 
	    copy_text_string(item) : item;
    if (temp);
    else
	temp = Qnone;
    M_CAR(gensymed_symbol_2) = temp;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    temp = allocate_evaluation_structure(info);
    M_CAR(gensymed_symbol_2) = temp;
    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
    M_CAR(gensymed_symbol_2) = user_data_ev;
    return apply_kb_procedure(procedure,gensymed_symbol);
}

DEFINE_VARIABLE_WITH_SYMBOL(Available_item_or_name_hash_hash_vector_43_vectors, Qavailable_item_or_name_hash_hash_vector_43_vectors);

DEFINE_VARIABLE_WITH_SYMBOL(Count_of_item_or_name_hash_hash_vector_43_vectors, Qcount_of_item_or_name_hash_hash_vector_43_vectors);

Object Available_item_or_name_hash_hash_vector_43_vectors_vector = UNBOUND;

/* ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object item_or_name_hash_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(222,11);
    temp = Count_of_item_or_name_hash_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTORS */
Object out_item_or_name_hash_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(222,12);
    temp = FIXNUM_MINUS(Count_of_item_or_name_hash_hash_vector_43_vectors,
	    length(Available_item_or_name_hash_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_item_or_name_hash_hash_vector_43_vector_internal()
{
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(222,13);
    atomic_incff_symval(Qcount_of_item_or_name_hash_hash_vector_43_vectors,
	    FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

static Object Qvector_pool;        /* vector-pool */

/* MAKE-ITEM-OR-NAME-HASH-HASH-VECTOR */
Object make_item_or_name_hash_hash_vector()
{
    Object temp, svref_arg_1, svref_arg_2, temp_1, vector_pool_cons, temp_2;
    Object svref_arg_2_1;

    x_note_fn_call(222,14);
    if (ISVREF(Available_item_or_name_hash_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index))) {
	temp = 
		M_CAR(ISVREF(Available_item_or_name_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	svref_arg_1 = 
		Available_item_or_name_hash_hash_vector_43_vectors_vector;
	svref_arg_2 = Current_thread_index;
	temp_1 = 
		M_CDR(ISVREF(Available_item_or_name_hash_hash_vector_43_vectors_vector,
		IFIX(Current_thread_index)));
	vector_pool_cons = 
		ISVREF(Available_item_or_name_hash_hash_vector_43_vectors_vector,
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
		make_permanent_item_or_name_hash_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-ITEM-OR-NAME-HASH-HASH-VECTOR */
Object reclaim_item_or_name_hash_hash_vector(item_or_name_hash_hash_vector_43_vector)
    Object item_or_name_hash_hash_vector_43_vector;
{
    Object svref_arg_1, svref_arg_2, new_cons, temp, svref_arg_2_1;
    Object svref_new_value, gensymed_symbol;

    x_note_fn_call(222,15);
    svref_arg_1 = Available_item_or_name_hash_hash_vector_43_vectors_vector;
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
    M_CAR(gensymed_symbol) = item_or_name_hash_hash_vector_43_vector;
    temp = 
	    ISVREF(Available_item_or_name_hash_hash_vector_43_vectors_vector,
	    IFIX(Current_thread_index));
    M_CDR(gensymed_symbol) = temp;
    inline_note_allocate_cons(gensymed_symbol,Qvector_pool);
    SVREF(svref_arg_1,svref_arg_2) = gensymed_symbol;
    return VALUES_1(Nil);
}

static Object Qsentinel_node;      /* sentinel-node */

static Object Qhead;               /* head */

static Object Qtail;               /* tail */

/* MAKE-ITEM-OR-NAME-HASH-TREE-FOR-HASH-SKIP-LIST-SENTINEL */
Object make_item_or_name_hash_tree_for_hash_skip_list_sentinel(hash,tail)
    Object hash, tail;
{
    Object node, next, svref_new_value;
    SI_Long i;

    x_note_fn_call(222,16);
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

/* MUTATE-ITEM-OR-NAME-HASH-TREE-FOR-HASH-SKIP-LIST-ENTRY */
Object mutate_item_or_name_hash_tree_for_hash_skip_list_entry(node,new_key,
	    new_entry)
    Object node, new_key, new_entry;
{
    x_note_fn_call(222,17);
    reclaim_item_or_name(ISVREF(node,(SI_Long)2L));
    reclaim_gensym_list_if_list(ISVREF(node,(SI_Long)3L));
    SVREF(node,FIX((SI_Long)2L)) = new_key;
    SVREF(node,FIX((SI_Long)3L)) = new_entry;
    return VALUES_1(Nil);
}

Object Fp_mutate_item_or_name_hash_tree_for_hash_skip_list_entry = UNBOUND;

static Object Qequalw;             /* equalw */

/* CLEAR-ITEM-OR-NAME-HASH-TREE */
Object clear_item_or_name_hash_tree(item_or_name_hash_tree_for_hash_skip_list)
    Object item_or_name_hash_tree_for_hash_skip_list;
{
    Object head, tail, element_qm, key_qm, temp, old_key, old_entry;
    Object result;

    x_note_fn_call(222,18);
    head = M_CAR(M_CDR(item_or_name_hash_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(item_or_name_hash_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequalw),temp,
	    item_or_name_hash_tree_for_hash_skip_list,FIX((SI_Long)31L),
	    hash_item_or_name(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_item_or_name(old_key);
    if (old_entry)
	reclaim_gensym_list_if_list(old_entry);
    goto next_loop;
  end_loop:;
    return VALUES_1(item_or_name_hash_tree_for_hash_skip_list);
}

static Object Qitem_or_name_hash_tree_for_hash;  /* item-or-name-hash-tree-for-hash */

static Object Qlookup;             /* lookup */

/* MAKE-ITEM-OR-NAME-HASH */
Object make_item_or_name_hash()
{
    Object new_vector, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol, gensymed_symbol_1, temp;
    SI_Long index_1;

    x_note_fn_call(222,19);
    new_vector = make_item_or_name_hash_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    tail = 
	    make_item_or_name_hash_tree_for_hash_skip_list_sentinel(Most_positive_fixnum,
	    Nil);
    head = 
	    make_item_or_name_hash_tree_for_hash_skip_list_sentinel(Most_negative_fixnum,
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
    M_CAR(gensymed_symbol) = Qitem_or_name_hash_tree_for_hash;
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

/* FLATTEN-ITEM-OR-NAME-HASH */
Object flatten_item_or_name_hash(item_or_name_hash_hash_table)
    Object item_or_name_hash_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(222,20);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(item_or_name_hash_hash_table,index_1);
    if (subtree) {
	temp = flatten_skip_list(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-ITEM-OR-NAME-HASH */
Object clear_item_or_name_hash(item_or_name_hash_hash_table)
    Object item_or_name_hash_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(222,21);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_item_or_name_hash_tree(ISVREF(item_or_name_hash_hash_table,index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-ITEM-OR-NAME-HASH */
Object reclaim_item_or_name_hash(item_or_name_hash_hash_table)
    Object item_or_name_hash_hash_table;
{
    Object item_or_name_hash_tree_for_hash_skip_list, head, tail, element_qm;
    Object key_qm, temp, old_key, old_entry, last_1, next_qm, temp_1;
    Object svref_arg_2;
    SI_Long index_1;
    Object result;

    x_note_fn_call(222,22);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    item_or_name_hash_tree_for_hash_skip_list = 
	    ISVREF(item_or_name_hash_hash_table,index_1);
    head = M_CAR(M_CDR(item_or_name_hash_tree_for_hash_skip_list));
    tail = M_CDR(M_CDR(item_or_name_hash_tree_for_hash_skip_list));
    element_qm = Nil;
    key_qm = Nil;
  next_loop_1:
    element_qm = ATOMIC_REF_OBJECT(ISVREF(ISVREF(head,(SI_Long)0L),
	    (SI_Long)0L));
    key_qm = ISVREF(element_qm,(SI_Long)2L);
    if ( ! !EQ(element_qm,tail))
	goto end_loop_1;
    temp = key_qm;
    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequalw),temp,
	    item_or_name_hash_tree_for_hash_skip_list,FIX((SI_Long)31L),
	    hash_item_or_name(key_qm));
    MVS_2(result,old_key,old_entry);
    if (old_key)
	reclaim_item_or_name(old_key);
    if (old_entry)
	reclaim_gensym_list_if_list(old_entry);
    goto next_loop_1;
  end_loop_1:
    reclaim_skip_list_element(head);
    reclaim_skip_list_element(tail);
    M_CDDR(item_or_name_hash_tree_for_hash_skip_list) = Nil;
    M_CADR(item_or_name_hash_tree_for_hash_skip_list) = Nil;
    M_CAR(item_or_name_hash_tree_for_hash_skip_list) = Nil;
    if (item_or_name_hash_tree_for_hash_skip_list) {
	last_1 = item_or_name_hash_tree_for_hash_skip_list;
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
	    M_CDR(temp_1) = item_or_name_hash_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	else {
	    temp_1 = Available_lookup_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = 
		    item_or_name_hash_tree_for_hash_skip_list;
	    temp_1 = Available_lookup_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp_1,svref_arg_2) = last_1;
	}
	M_CDR(last_1) = Nil;
    }
    ISVREF(item_or_name_hash_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = reclaim_item_or_name_hash_hash_vector(item_or_name_hash_hash_table);
    return VALUES_1(temp);
}

/* HASH-ITEM-OR-NAME */
Object hash_item_or_name(item_or_name)
    Object item_or_name;
{
    Object x2;
    char temp;

    x_note_fn_call(222,23);
    if (CONSP(item_or_name) && EQ(M_CDR(item_or_name),Qitem_reference))
	return hash_item_reference(item_or_name);
    else {
	if (SIMPLE_VECTOR_P(item_or_name) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_name)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_name,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_name,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return hash_item_reference(ISVREF(item_or_name,(SI_Long)2L));
	else
	    return sxhashw(item_or_name);
    }
}

/* RECLAIM-ITEM-OR-NAME */
Object reclaim_item_or_name(item_or_name)
    Object item_or_name;
{
    x_note_fn_call(222,24);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(item_or_name) != (SI_Long)0L)
	return reclaim_wide_string(item_or_name);
    else if (CONSP(item_or_name) && EQ(M_CDR(item_or_name),Qitem_reference))
	return reclaim_evaluation_item_reference(item_or_name);
    else
	return VALUES_1(Qnil);
}

/* COPY-ITEM-OR-NAME */
Object copy_item_or_name(item_or_name)
    Object item_or_name;
{
    Object x2, item_or_value;
    char temp;

    x_note_fn_call(222,25);
    if (SIMPLE_VECTOR_P(item_or_name) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_name)) > (SI_Long)2L && 
	     !EQ(ISVREF(item_or_name,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_name,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	item_or_value = item_or_name;
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
	if (temp)
	    return get_reference_to_item(item_or_value);
	else
	    return VALUES_1(item_or_value);
    }
    else if (CONSP(item_or_name) && EQ(M_CDR(item_or_name),Qitem_reference))
	return copy_evaluation_item_reference(item_or_name);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(item_or_name) != (SI_Long)0L)
	return copy_wide_string(item_or_name);
    else
	return VALUES_1(item_or_name);
}

/* ITEM-OR-NAME-HASH-GET */
Object item_or_name_hash_get(item_or_name,hash_table)
    Object item_or_name, hash_table;
{
    Object key, temp_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(222,26);
    key = copy_item_or_name(item_or_name);
    gensymed_symbol = IFIX(hash_item_or_name(key));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(hash_table,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = key;
    key_hash_value = gensymed_symbol;
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
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_1:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !TRUEP(equalw(key_value,ISVREF(curr,
	    (SI_Long)2L)))) {
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
    temp_1 = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (equalw(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    reclaim_item_or_name(key);
    return VALUES_1(temp_1);
}

/* ITEM-OR-NAME-HASH-PUT */
Object item_or_name_hash_put(item_or_name,handle,hash_table)
    Object item_or_name, handle, hash_table;
{
    Object key, temp_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, entry, temp_3;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(222,27);
    key = copy_item_or_name(item_or_name);
    gensymed_symbol = IFIX(hash_item_or_name(key));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(hash_table,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = key;
    key_hash_value = gensymed_symbol;
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
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_1:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !TRUEP(equalw(key_value,ISVREF(curr,
	    (SI_Long)2L)))) {
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
    entry = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (equalw(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    gensymed_symbol = IFIX(hash_item_or_name(key));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_2 = SVREF(hash_table,FIX(temp));
    temp_1 = Fp_mutate_item_or_name_hash_tree_for_hash_skip_list_entry;
    if ( !TRUEP(entry))
	temp_3 = handle;
    else if (ATOM(entry))
	temp_3 = gensym_list_2(handle,entry);
    else if (CONSP(entry))
	temp_3 = gensym_cons_1(handle,copy_list_using_gensym_conses_1(entry));
    else
	temp_3 = Qnil;
    return set_skip_list_entry(temp_2,FIX((SI_Long)31L),Qequalw,temp_1,T,
	    key,FIX(gensymed_symbol),temp_3);
}

/* ITEM-OR-NAME-HASH-REMOVE */
Object item_or_name_hash_remove(item_or_name,handle,hash_table)
    Object item_or_name, handle, hash_table;
{
    Object key, temp_1, skip_list, key_value, marked, pred, curr, succ;
    Object reference, temp_2, entry_hash, entry, old_key, old_entry, temp_3, x;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long gensymed_symbol, temp, key_hash_value, bottom_level, level;
    SI_Long ab_loop_bind_;
    Object result;

    x_note_fn_call(222,28);
    key = copy_item_or_name(item_or_name);
    gensymed_symbol = IFIX(hash_item_or_name(key));
    temp = gensymed_symbol % (SI_Long)43L;
    temp_1 = SVREF(hash_table,FIX(temp));
    skip_list = CDR(temp_1);
    key_value = key;
    key_hash_value = gensymed_symbol;
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
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_1:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp_2 = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp_2,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !TRUEP(equalw(key_value,ISVREF(curr,
	    (SI_Long)2L)))) {
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
    entry = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (equalw(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(entry))
	return reclaim_item_or_name(key);
    else if (ATOM(entry)) {
	if (EQL(handle,entry)) {
	    gensymed_symbol = IFIX(hash_item_or_name(key));
	    temp = gensymed_symbol % (SI_Long)43L;
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequalw),key,
		    SVREF(hash_table,FIX(temp)),FIX((SI_Long)31L),
		    FIX(gensymed_symbol));
	    MVS_2(result,old_key,old_entry);
	    if (old_key)
		reclaim_item_or_name(old_key);
	    if (old_entry)
		reclaim_gensym_list_if_list(old_entry);
	}
	return reclaim_item_or_name(key);
    }
    else if ( !TRUEP(CDR(entry))) {
	temp_1 = CAR(entry);
	if (EQL(handle,temp_1)) {
	    gensymed_symbol = IFIX(hash_item_or_name(key));
	    temp = gensymed_symbol % (SI_Long)43L;
	    result = delete_skip_list_entry(SYMBOL_FUNCTION(Qequalw),key,
		    SVREF(hash_table,FIX(temp)),FIX((SI_Long)31L),
		    FIX(gensymed_symbol));
	    MVS_2(result,old_key,old_entry);
	    if (old_key)
		reclaim_item_or_name(old_key);
	    if (old_entry)
		reclaim_gensym_list_if_list(old_entry);
	}
	return reclaim_item_or_name(key);
    }
    else if ( !TRUEP(CDDR(entry))) {
	temp_1 = CAR(entry);
	if (EQL(handle,temp_1)) {
	    gensymed_symbol = IFIX(hash_item_or_name(key));
	    temp = gensymed_symbol % (SI_Long)43L;
	    return set_skip_list_entry(SVREF(hash_table,FIX(temp)),
		    FIX((SI_Long)31L),Qequalw,
		    Fp_mutate_item_or_name_hash_tree_for_hash_skip_list_entry,
		    T,key,FIX(gensymed_symbol),CADR(entry));
	}
	else {
	    temp_1 = CADR(entry);
	    if (EQL(handle,temp_1)) {
		gensymed_symbol = IFIX(hash_item_or_name(key));
		temp = gensymed_symbol % (SI_Long)43L;
		return set_skip_list_entry(SVREF(hash_table,FIX(temp)),
			FIX((SI_Long)31L),Qequalw,
			Fp_mutate_item_or_name_hash_tree_for_hash_skip_list_entry,
			T,key,FIX(gensymed_symbol),CAR(entry));
	    }
	    else
		return reclaim_item_or_name(key);
	}
    }
    else {
	gensymed_symbol = IFIX(hash_item_or_name(key));
	temp = gensymed_symbol % (SI_Long)43L;
	temp_3 = SVREF(hash_table,FIX(temp));
	temp_2 = Fp_mutate_item_or_name_hash_tree_for_hash_skip_list_entry;
	x = Nil;
	ab_loop_list_ = entry;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	x = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQL(x,handle)) {
	    ab_loopvar__2 = gensym_cons_1(x,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_3;
      end_loop_3:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	return set_skip_list_entry(temp_3,FIX((SI_Long)31L),Qequalw,temp_2,
		T,key,FIX(gensymed_symbol),temp_1);
    }
}

Object Status_bar_action_type = UNBOUND;

Object Status_bar_configure_type = UNBOUND;

Object Status_bar_remove_pane_type = UNBOUND;

Object Status_bar_pane_options_type = UNBOUND;

Object The_type_description_of_status_bar = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_status_bars, Qchain_of_available_status_bars);

DEFINE_VARIABLE_WITH_SYMBOL(Status_bar_count, Qstatus_bar_count);

Object Chain_of_available_status_bars_vector = UNBOUND;

/* STATUS-BAR-STRUCTURE-MEMORY-USAGE */
Object status_bar_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(222,29);
    temp = Status_bar_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)32L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STATUS-BAR-COUNT */
Object outstanding_status_bar_count()
{
    Object def_structure_status_bar_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,30);
    gensymed_symbol = IFIX(Status_bar_count);
    def_structure_status_bar_variable = Chain_of_available_status_bars;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_status_bar_variable))
	goto end_loop;
    def_structure_status_bar_variable = 
	    ISVREF(def_structure_status_bar_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STATUS-BAR-1-1 */
Object reclaim_status_bar_1_1(status_bar)
    Object status_bar;
{
    Object temp, svref_arg_2;

    x_note_fn_call(222,31);
    inline_note_reclaim_cons(status_bar,Nil);
    temp = ISVREF(Chain_of_available_status_bars_vector,
	    IFIX(Current_thread_index));
    SVREF(status_bar,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_status_bars_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = status_bar;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STATUS-BAR */
Object reclaim_structure_for_status_bar(status_bar)
    Object status_bar;
{
    x_note_fn_call(222,32);
    return reclaim_status_bar_1_1(status_bar);
}

static Object Qg2_defstruct_structure_name_status_bar_g2_struct;  /* g2-defstruct-structure-name::status-bar-g2-struct */

/* MAKE-PERMANENT-STATUS-BAR-STRUCTURE-INTERNAL */
Object make_permanent_status_bar_structure_internal()
{
    Object def_structure_status_bar_variable, defstruct_g2_status_bar_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(222,33);
    def_structure_status_bar_variable = Nil;
    atomic_incff_symval(Qstatus_bar_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_status_bar_variable = Nil;
	gensymed_symbol = (SI_Long)32L;
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
	defstruct_g2_status_bar_variable = the_array;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_status_bar_g2_struct;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)21L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)22L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)23L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)24L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)25L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)26L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)27L)) = Nil;
	SVREF(defstruct_g2_status_bar_variable,FIX((SI_Long)28L)) = Nil;
	def_structure_status_bar_variable = defstruct_g2_status_bar_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_status_bar_variable);
}

static Object Qdestroy;            /* destroy */

/* MAKE-STATUS-BAR-1 */
Object make_status_bar_1()
{
    Object def_structure_status_bar_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(222,34);
    def_structure_status_bar_variable = 
	    ISVREF(Chain_of_available_status_bars_vector,
	    IFIX(Current_thread_index));
    if (def_structure_status_bar_variable) {
	svref_arg_1 = Chain_of_available_status_bars_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_status_bar_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_status_bar_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_status_bar_g2_struct;
    }
    else
	def_structure_status_bar_variable = 
		make_permanent_status_bar_structure_internal();
    inline_note_allocate_cons(def_structure_status_bar_variable,Nil);
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_status_bar_variable,(SI_Long)2L) = FIX((SI_Long)-1L);
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_status_bar_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_status_bar_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(def_structure_status_bar_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_status_bar_variable,(SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)8L)) = Nil;
    ISVREF(def_structure_status_bar_variable,(SI_Long)9L) = FIX((SI_Long)0L);
    ISVREF(def_structure_status_bar_variable,(SI_Long)10L) = FIX((SI_Long)0L);
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)16L)) = Qdestroy;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)22L)) = T;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)25L)) = T;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)28L)) = Nil;
    ISVREF(def_structure_status_bar_variable,(SI_Long)29L) = FIX((SI_Long)1L);
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_status_bar_variable,FIX((SI_Long)31L)) = Nil;
    return VALUES_1(def_structure_status_bar_variable);
}

/* CLEAN-UP-STRUCTURE-FOR-STATUS-BAR */
Object clean_up_structure_for_status_bar(status_bar)
    Object status_bar;
{
    Object gensym_window, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,35);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    SVREF(gensym_window,FIX((SI_Long)67L)) = Nil;
    status_bar_reset_locally(2,status_bar,T);
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_status_bar,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)9L);
    gensymed_symbol_1 = status_bar;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RECLAIM-STATUS-BAR */
Object reclaim_status_bar(status_bar)
    Object status_bar;
{
    x_note_fn_call(222,36);
    return reclaim_native_window(status_bar);
}

Object The_type_description_of_status_bar_pane = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_status_bar_panes, Qchain_of_available_status_bar_panes);

DEFINE_VARIABLE_WITH_SYMBOL(Status_bar_pane_count, Qstatus_bar_pane_count);

Object Chain_of_available_status_bar_panes_vector = UNBOUND;

/* STATUS-BAR-PANE-STRUCTURE-MEMORY-USAGE */
Object status_bar_pane_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(222,37);
    temp = Status_bar_pane_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STATUS-BAR-PANE-COUNT */
Object outstanding_status_bar_pane_count()
{
    Object def_structure_status_bar_pane_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,38);
    gensymed_symbol = IFIX(Status_bar_pane_count);
    def_structure_status_bar_pane_variable = 
	    Chain_of_available_status_bar_panes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_status_bar_pane_variable))
	goto end_loop;
    def_structure_status_bar_pane_variable = 
	    ISVREF(def_structure_status_bar_pane_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STATUS-BAR-PANE-1-1 */
Object reclaim_status_bar_pane_1_1(status_bar_pane)
    Object status_bar_pane;
{
    Object temp, svref_arg_2;

    x_note_fn_call(222,39);
    inline_note_reclaim_cons(status_bar_pane,Nil);
    temp = ISVREF(Chain_of_available_status_bar_panes_vector,
	    IFIX(Current_thread_index));
    SVREF(status_bar_pane,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_status_bar_panes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = status_bar_pane;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STATUS-BAR-PANE */
Object reclaim_structure_for_status_bar_pane(status_bar_pane)
    Object status_bar_pane;
{
    x_note_fn_call(222,40);
    return reclaim_status_bar_pane_1_1(status_bar_pane);
}

static Object Qg2_defstruct_structure_name_status_bar_pane_g2_struct;  /* g2-defstruct-structure-name::status-bar-pane-g2-struct */

/* MAKE-PERMANENT-STATUS-BAR-PANE-STRUCTURE-INTERNAL */
Object make_permanent_status_bar_pane_structure_internal()
{
    Object def_structure_status_bar_pane_variable;
    Object defstruct_g2_status_bar_pane_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(222,41);
    def_structure_status_bar_pane_variable = Nil;
    atomic_incff_symval(Qstatus_bar_pane_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_status_bar_pane_variable = Nil;
	gensymed_symbol = (SI_Long)4L;
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
	defstruct_g2_status_bar_pane_variable = the_array;
	SVREF(defstruct_g2_status_bar_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_status_bar_pane_g2_struct;
	def_structure_status_bar_pane_variable = 
		defstruct_g2_status_bar_pane_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_status_bar_pane_variable);
}

/* MAKE-STATUS-BAR-PANE-1 */
Object make_status_bar_pane_1(status_bar_pane_handle,status_bar_pane_id,
	    status_bar_pane_user_data)
    Object status_bar_pane_handle, status_bar_pane_id;
    Object status_bar_pane_user_data;
{
    Object def_structure_status_bar_pane_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(222,42);
    def_structure_status_bar_pane_variable = 
	    ISVREF(Chain_of_available_status_bar_panes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_status_bar_pane_variable) {
	svref_arg_1 = Chain_of_available_status_bar_panes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_status_bar_pane_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_status_bar_pane_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_status_bar_pane_g2_struct;
    }
    else
	def_structure_status_bar_pane_variable = 
		make_permanent_status_bar_pane_structure_internal();
    inline_note_allocate_cons(def_structure_status_bar_pane_variable,Nil);
    SVREF(def_structure_status_bar_pane_variable,FIX((SI_Long)1L)) = 
	    status_bar_pane_handle;
    SVREF(def_structure_status_bar_pane_variable,FIX((SI_Long)2L)) = 
	    status_bar_pane_id;
    SVREF(def_structure_status_bar_pane_variable,FIX((SI_Long)3L)) = 
	    status_bar_pane_user_data;
    return VALUES_1(def_structure_status_bar_pane_variable);
}

/* RECLAIM-STATUS-BAR-PANE */
Object reclaim_status_bar_pane(pane)
    Object pane;
{
    Object thing;

    x_note_fn_call(222,43);
    thing = ISVREF(pane,(SI_Long)2L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    thing = ISVREF(pane,(SI_Long)3L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    return reclaim_status_bar_pane_1_1(pane);
}

/* GET-STATUS-BAR */
Object get_status_bar(gensym_window)
    Object gensym_window;
{
    Object temp, status_bar;

    x_note_fn_call(222,44);
    temp = ISVREF(gensym_window,(SI_Long)67L);
    if (temp)
	return VALUES_1(temp);
    else {
	status_bar = make_status_bar_1();
	SVREF(status_bar,FIX((SI_Long)1L)) = gensym_window;
	SVREF(status_bar,FIX((SI_Long)14L)) = Qg2_status_bar;
	SVREF(gensym_window,FIX((SI_Long)67L)) = status_bar;
	status_bar_create_initial_panes(status_bar);
	return VALUES_1(status_bar);
    }
}

static Object Qg2_documentation_line;  /* g2-documentation-line */

static Object Qg2_security_icon;   /* g2-security-icon */

/* STATUS-BAR-CREATE-INITIAL-PANES */
Object status_bar_create_initial_panes(status_bar)
    Object status_bar;
{
    Object gensym_window;

    x_note_fn_call(222,45);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    status_bar_add_pane_1(status_bar,FIX((SI_Long)0L),
	    Qg2_documentation_line,Nil);
    if (secure_telewindows_connection_p(gensym_window))
	return status_bar_add_pane_1(status_bar,FIX((SI_Long)-1L),
		Qg2_security_icon,Nil);
    else
	return VALUES_1(Nil);
}

/* STATUS-BAR-RESET-LOCALLY */
Object status_bar_reset_locally varargs_1(int, n)
{
    Object status_bar;
    Object reclaiming, pane, ab_loop_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(222,46);
    INIT_ARGS_nonrelocating();
    status_bar = REQUIRED_ARG_nonrelocating();
    reclaiming = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    pane = Nil;
    ab_loop_list_ = ISVREF(status_bar,(SI_Long)31L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_status_bar_pane(pane);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(ISVREF(status_bar,(SI_Long)31L));
    reclaim_gensym_list_1(ISVREF(status_bar,(SI_Long)30L));
    ISVREF(status_bar,(SI_Long)29L) = FIX((SI_Long)1L);
    SVREF(status_bar,FIX((SI_Long)30L)) = Nil;
    SVREF(status_bar,FIX((SI_Long)31L)) = Nil;
    if ( !TRUEP(reclaiming))
	return status_bar_create_initial_panes(status_bar);
    else
	return VALUES_1(Nil);
}

/* STATUS-BAR-FIND-PANE */
Object status_bar_find_pane(status_bar,pane_designation)
    Object status_bar, pane_designation;
{
    Object pane, ab_loop_list_, temp, thing;

    x_note_fn_call(222,47);
    pane = Nil;
    ab_loop_list_ = ISVREF(status_bar,(SI_Long)31L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(pane_designation,FIX((SI_Long)0L)))
	temp = EQ(ISVREF(pane,(SI_Long)2L),Qg2_documentation_line) ? T : Nil;
    else {
	temp = ISVREF(pane,(SI_Long)2L);
	if (EQL(temp,pane_designation))
	    temp = T;
	else {
	    thing = ISVREF(pane,(SI_Long)2L);
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L ? 
		    INLINE_UNSIGNED_BYTE_16_VECTOR_P(pane_designation) != 
		    (SI_Long)0L : TRUEP(Nil))
		temp = string_eq_w(ISVREF(pane,(SI_Long)2L),pane_designation);
	    else
		temp = Qnil;
	}
    }
    if (temp)
	return VALUES_1(pane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* STATUS-BAR-FIND-PANE-BY-HANDLE */
Object status_bar_find_pane_by_handle(status_bar,handle)
    Object status_bar, handle;
{
    Object pane, ab_loop_list_, temp;

    x_note_fn_call(222,48);
    pane = Nil;
    ab_loop_list_ = ISVREF(status_bar,(SI_Long)31L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    pane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(pane,(SI_Long)1L);
    if (EQL(temp,handle))
	return VALUES_1(pane);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object string_constant_13;  /* "Status-bar pane ~NV not found." */

/* STATUS-BAR-FIND-PANE-OR-STACK-ERROR */
Object status_bar_find_pane_or_stack_error(status_bar,pane_designation)
    Object status_bar, pane_designation;
{
    Object temp, top_of_stack, message_1;

    x_note_fn_call(222,49);
    temp = status_bar_find_pane(status_bar,pane_designation);
    if (temp)
	return VALUES_1(temp);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_13,
		pane_designation);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

static Object Qab_gensym;          /* gensym */

/* STATUS-BAR-ALLOCATE-PANE-HANDLE */
Object status_bar_allocate_pane_handle(status_bar)
    Object status_bar;
{
    Object temp, temp_1, gensym_pop_store, cons_1, next_cons, svref_arg_2;

    x_note_fn_call(222,50);
    if (FIXNUM_LT(ISVREF(status_bar,(SI_Long)29L),
	    Status_bar_maximum_pane_count)) {
	temp = ISVREF(status_bar,(SI_Long)29L);
	temp_1 = FIXNUM_ADD1(ISVREF(status_bar,(SI_Long)29L));
	SVREF(status_bar,FIX((SI_Long)29L)) = temp_1;
	return VALUES_1(temp);
    }
    else {
	gensym_pop_store = Nil;
	cons_1 = ISVREF(status_bar,(SI_Long)30L);
	if (cons_1) {
	    gensym_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_gensym);
	    if (ISVREF(Available_gensym_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_gensym_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = cons_1;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
	    }
	    else {
		temp_1 = Available_gensym_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
		temp_1 = Available_gensym_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp_1,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	SVREF(status_bar,FIX((SI_Long)30L)) = next_cons;
	return VALUES_1(gensym_pop_store);
    }
}

/* STATUS-BAR-ADD-PANE-LOCALLY */
Object status_bar_add_pane_locally(status_bar,id,user_data)
    Object status_bar, id, user_data;
{
    Object handle_qm;

    x_note_fn_call(222,51);
    handle_qm = status_bar_allocate_pane_handle(status_bar);
    if (handle_qm)
	return status_bar_add_pane_1(status_bar,handle_qm,id,user_data);
    else
	return VALUES_1(Nil);
}

/* STATUS-BAR-ADD-PANE-1 */
Object status_bar_add_pane_1(status_bar,handle,id,user_data)
    Object status_bar, handle, id, user_data;
{
    Object temp, pane, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object svref_new_value;

    x_note_fn_call(222,52);
    temp = INLINE_UNSIGNED_BYTE_16_VECTOR_P(id) != (SI_Long)0L ? 
	    copy_text_string(id) : id;
    pane = make_status_bar_pane_1(handle,temp,FIXNUMP(user_data) || 
	    user_data && SYMBOLP(user_data) || SIMPLE_VECTOR_P(user_data) ?
	     user_data : copy_if_evaluation_value_1(user_data));
    gensym_push_modify_macro_arg = pane;
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(status_bar,(SI_Long)31L);
    svref_new_value = gensym_cons_1(car_1,cdr_1);
    SVREF(status_bar,FIX((SI_Long)31L)) = svref_new_value;
    return VALUES_1(pane);
}

/* STATUS-BAR-REMOVE-PANE-LOCALLY */
Object status_bar_remove_pane_locally(status_bar,pane)
    Object status_bar, pane;
{
    Object svref_new_value;

    x_note_fn_call(222,53);
    svref_new_value = delete_gensym_element_1(pane,ISVREF(status_bar,
	    (SI_Long)31L));
    SVREF(status_bar,FIX((SI_Long)31L)) = svref_new_value;
    svref_new_value = nconc2(ISVREF(status_bar,(SI_Long)30L),
	    gensym_cons_1(ISVREF(pane,(SI_Long)1L),Nil));
    SVREF(status_bar,FIX((SI_Long)30L)) = svref_new_value;
    return reclaim_status_bar_pane(pane);
}

static Object Qreset;              /* reset */

/* NOTE-KB-RESET-FOR-NATIVE-STATUS-BARS */
Object note_kb_reset_for_native_status_bars()
{
    Object workstation, ab_loop_list_, gensym_window, status_bar_qm;

    x_note_fn_call(222,54);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
    status_bar_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    status_bar_qm = ISVREF(gensym_window,(SI_Long)67L);
    if (status_bar_qm) {
	status_bar_reset_locally(1,status_bar_qm);
	if (FIXNUM_LT(Icp_window_protocol_supports_manage_status_bar_ex,
		ISVREF(gensym_window,(SI_Long)11L)))
	    manage_status_bar(gensym_window,Qreset,Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qid;                 /* id */

static Object Qicon;               /* icon */

static Object Qbackground_color;   /* background-color */

static Object Qforeground_color;   /* foreground-color */

static Object Qwidth;              /* width */

static Object Qfit;                /* fit */

static Object Qalignment;          /* alignment */

/* PREPROCESS-STATUS-BAR-PANE-OPTIONS */
Object preprocess_status_bar_pane_options(gensym_window,status_bar,arg)
    Object gensym_window, status_bar, arg;
{
    Object sublist, property_1, value, temp, pane_qm, cadr_new_value;

    x_note_fn_call(222,55);
    if (plistp(arg)) {
	sublist = arg;
	property_1 = Nil;
	value = Nil;
      next_loop:
	if ( !TRUEP(sublist))
	    goto end_loop;
	property_1 = CAR(sublist);
	temp = CDR(sublist);
	value = CAR(temp);
	if (EQ(property_1,Qid) || EQ(property_1,Qposition)) {
	    pane_qm = status_bar_find_pane(status_bar,value);
	    if (text_string_p(value))
		reclaim_text_string(value);
	    cadr_new_value = pane_qm ? ISVREF(pane_qm,(SI_Long)1L) : 
		    FIX((SI_Long)-1L);
	    M_CADR(sublist) = cadr_new_value;
	}
	else if (EQ(property_1,Qicon)) {
	    cadr_new_value = 
		    native_icon_handle_or_stack_error(gensym_window,value);
	    M_CADR(sublist) = cadr_new_value;
	}
	else if (EQ(property_1,Qbackground_color) || EQ(property_1,
		Qforeground_color)) {
	    cadr_new_value = rgb_color_value_or_stack_error(value);
	    M_CADR(sublist) = cadr_new_value;
	}
	else if (EQ(property_1,Qwidth)) {
	    if (EQ(value,Qfit))
		M_CADR(sublist) = FIX((SI_Long)-1L);
	}
	else if (EQ(property_1,Qalignment)) {
	    cadr_new_value = encode_text_alignment(value);
	    M_CADR(sublist) = cadr_new_value;
	}
	sublist = CDDR(sublist);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qicp;                /* icp */

static Object Qtelewindows;        /* telewindows */

/* MANAGE-STATUS-BAR */
Object manage_status_bar(gensym_window,action,arg)
    Object gensym_window, action, arg;
{
    Object icp_output_port_qm, current_icp_port, current_icp_socket, temp;
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
    Object result;

    x_note_fn_call(222,56);
    if (EQ(ISVREF(gensym_window,(SI_Long)1L),Qicp)) {
	icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
	if (icp_output_port_qm && 
		icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
	    current_icp_port = icp_output_port_qm;
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
					temp = 
						send_icp_manage_status_bar(gensym_window,
						action,arg);
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
	else
	    return VALUES_1(Nil);
    }
    else
	return manage_status_bar_1(action,arg);
}

/* STATUS-BAR-RESET */
Object status_bar_reset(status_bar)
    Object status_bar;
{
    Object gensym_window;

    x_note_fn_call(222,57);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    status_bar_reset_locally(1,status_bar);
    if (FIXNUM_LT(Icp_window_protocol_supports_manage_status_bar_ex,
	    ISVREF(gensym_window,(SI_Long)11L)))
	return manage_status_bar(gensym_window,Qreset,Nil);
    else
	return VALUES_1(Nil);
}

static Object Qvisible;            /* visible */

static Object Qhide;               /* hide */

static Object Qcallback;           /* callback */

static Object Qmin_height;         /* min-height */

static Object Qset_min_height;     /* set-min-height */

static Object Quser_data;          /* user-data */

static Object list_constant_1;     /* # */

/* STATUS-BAR-CONFIGURE */
Object status_bar_configure(status_bar,plist,user_data_qm,panes_ev_qm)
    Object status_bar, plist, user_data_qm, panes_ev_qm;
{
    Object gensym_window, property_1, value, ab_loop_list_, temp;
    Object svref_new_value, gensymed_symbol, held_vector, pane_ev, elt_1;
    Object validated_elt, pane_user_data_qm;
    SI_Long next_index, length_1;

    x_note_fn_call(222,58);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    status_bar_reset(status_bar);
    property_1 = Nil;
    value = Nil;
    ab_loop_list_ = plist;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    property_1 = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    if (EQ(property_1,Qvisible)) {
	if ( !TRUEP(value))
	    manage_status_bar(gensym_window,Qhide,Nil);
    }
    else if (EQ(property_1,Qcallback)) {
	svref_new_value = stored_callback_procedure(value);
	SVREF(status_bar,FIX((SI_Long)27L)) = svref_new_value;
    }
    else if (EQ(property_1,Qmin_height))
	manage_status_bar(gensym_window,Qset_min_height,value);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:;
    if (panes_ev_qm) {
	gensymed_symbol = panes_ev_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	pane_ev = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_1:
	if (next_index >= length_1)
	    goto end_loop_1;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	pane_ev = validated_elt;
	check_type_or_stack_error(2,pane_ev,Status_bar_pane_options_type);
	pane_user_data_qm = CONSP(pane_ev) && EQ(M_CDR(pane_ev),
		Qab_structure) ? estructure_slot(pane_ev,Quser_data,Nil) : 
		Qnil;
	plist = unbox_evaluation_value(2,pane_ev,list_constant_1);
	status_bar_add_pane(status_bar,plist,pane_user_data_qm);
	reclaim_unboxed_evaluation_value(plist);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtext;               /* text */

static Object string_constant_14;  /* "Maximum of ~D status-bar panes exceeded." */

static Object Qadd_pane;           /* add-pane */

/* STATUS-BAR-ADD-PANE */
Object status_bar_add_pane(status_bar,plist,user_data_qm)
    Object status_bar, plist, user_data_qm;
{
    Object gensym_window, id, position_qm, top_of_stack, message_1;

    x_note_fn_call(222,59);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    id = getf(plist,Qid,_);
    if (id);
    else
	id = getf(plist,Qtext,_);
    position_qm = getf(plist,Qposition,_);
    if (position_qm)
	status_bar_find_pane_or_stack_error(status_bar,position_qm);
    if ( !TRUEP(status_bar_add_pane_locally(status_bar,id,user_data_qm))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_14,
		Status_bar_maximum_pane_count);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    preprocess_status_bar_pane_options(gensym_window,status_bar,plist);
    return manage_status_bar(gensym_window,Qadd_pane,plist);
}

static Object Qmodify_pane;        /* modify-pane */

/* STATUS-BAR-MODIFY-PANE */
Object status_bar_modify_pane(status_bar,plist,user_data_qm)
    Object status_bar, plist, user_data_qm;
{
    Object gensym_window, id, pane, thing, svref_new_value;

    x_note_fn_call(222,60);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    id = getf(plist,Qid,_);
    pane = status_bar_find_pane_or_stack_error(status_bar,id);
    if (user_data_qm) {
	thing = ISVREF(pane,(SI_Long)3L);
	if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	    reclaim_if_evaluation_value_1(thing);
	svref_new_value = FIXNUMP(user_data_qm) || user_data_qm && 
		SYMBOLP(user_data_qm) ? user_data_qm : 
		copy_evaluation_value_1(user_data_qm);
	SVREF(pane,FIX((SI_Long)3L)) = svref_new_value;
    }
    preprocess_status_bar_pane_options(gensym_window,status_bar,plist);
    return manage_status_bar(gensym_window,Qmodify_pane,plist);
}

static Object Qremove_pane;        /* remove-pane */

/* STATUS-BAR-REMOVE-PANE */
Object status_bar_remove_pane(status_bar,arg)
    Object status_bar, arg;
{
    Object gensym_window, id, pane;

    x_note_fn_call(222,61);
    gensym_window = ISVREF(status_bar,(SI_Long)1L);
    if (plistp(arg))
	id = getf(arg,Qid,_);
    else if (ATOM(arg))
	id = arg;
    else
	id = Qnil;
    pane = status_bar_find_pane_or_stack_error(status_bar,id);
    status_bar_remove_pane_locally(status_bar,pane);
    preprocess_status_bar_pane_options(gensym_window,status_bar,arg);
    return manage_status_bar(gensym_window,Qremove_pane,ISVREF(pane,
	    (SI_Long)1L));
}

/* STATUS-BAR-API-P */
Object status_bar_api_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,62);
    if (twng_window_p(gensym_window))
	return VALUES_1(FIXNUM_LT(Icp_window_protocol_supports_manage_status_bar_ex,
		ISVREF(gensym_window,(SI_Long)11L)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_15;  /* "Status bars are not supported on ~NF" */

static Object string_constant_16;  /* "Modifying the status bar is not supported on ~NF" */

static Object list_constant_2;     /* # */

static Object string_constant_17;  /* "The status-bar action ~A is not supported on ~NF" */

static Object Qpanes;              /* panes */

static Object list_constant_3;     /* # */

static Object Qset_callback;       /* set-callback */

static Object list_constant_4;     /* # */

static Object Qconfigure;          /* configure */

/* G2-UI-MANAGE-STATUS-BAR */
Object g2_ui_manage_status_bar(action,ev_arg,g2_window)
    Object action, ev_arg, g2_window;
{
    Object gensym_window, top_of_stack, message_1, user_data_qm, panes_qm, arg;
    Object status_bar, svref_new_value;

    x_note_fn_call(222,63);
    check_type_or_stack_error(2,action,Status_bar_action_type);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    if ( !TRUEP(native_menu_bar_p(gensym_window))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_15,
		g2_window);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !FIXNUM_LT(Icp_window_protocol_supports_manage_status_bar,
	    ISVREF(gensym_window,(SI_Long)11L))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_16,
		g2_window);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    if ( !(memq_function(action,list_constant_2) || 
	    status_bar_api_p(gensym_window))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(3,string_constant_17,
		action,g2_window);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    user_data_qm = CONSP(ev_arg) && EQ(M_CDR(ev_arg),Qab_structure) ? 
	    estructure_slot(ev_arg,Quser_data,Nil) : Qnil;
    panes_qm = CONSP(ev_arg) && EQ(M_CDR(ev_arg),Qab_structure) ? 
	    estructure_slot(ev_arg,Qpanes,Nil) : Qnil;
    arg = unbox_evaluation_value(2,ev_arg,list_constant_3);
    status_bar = get_status_bar(gensym_window);
    if (EQ(action,Qset_callback)) {
	check_type_or_stack_error(2,ev_arg,list_constant_4);
	svref_new_value = stored_callback_procedure(arg);
	SVREF(status_bar,FIX((SI_Long)27L)) = svref_new_value;
    }
    else if (EQ(action,Qconfigure)) {
	check_type_or_stack_error(2,ev_arg,Status_bar_configure_type);
	status_bar_configure(status_bar,arg,user_data_qm,panes_qm);
    }
    else if (EQ(action,Qreset))
	status_bar_reset(status_bar);
    else if (EQ(action,Qadd_pane)) {
	check_type_or_stack_error(2,ev_arg,Status_bar_pane_options_type);
	status_bar_add_pane(status_bar,arg,user_data_qm);
    }
    else if (EQ(action,Qmodify_pane)) {
	check_type_or_stack_error(2,ev_arg,Status_bar_pane_options_type);
	status_bar_modify_pane(status_bar,arg,user_data_qm);
    }
    else if (EQ(action,Qremove_pane)) {
	check_type_or_stack_error(2,ev_arg,Status_bar_remove_pane_type);
	status_bar_remove_pane(status_bar,arg);
    }
    else
	manage_status_bar(gensym_window,action,arg);
    reclaim_unboxed_evaluation_value(arg);
    reclaim_evaluation_value(ev_arg);
    return VALUES_1(Evaluation_false_value);
}

static Object Qleft_click;         /* left-click */

static Object Qmiddle_click;       /* middle-click */

static Object Qright_click;        /* right-click */

/* STATUS-BAR-EVENT-NAME */
Object status_bar_event_name(event_code,modifier_bits)
    Object event_code, modifier_bits;
{
    Object click_qm;

    x_note_fn_call(222,64);
    if ( !(FIXNUMP(event_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    event_code) && FIXNUM_LE(event_code,FIX((SI_Long)127L))))
	click_qm = Nil;
    else
	switch (INTEGER_TO_CHAR(event_code)) {
	  case 1:
	    click_qm = Qleft_click;
	    break;
	  case 2:
	    click_qm = Qmiddle_click;
	    break;
	  case 3:
	    click_qm = Qright_click;
	    break;
	  default:
	    click_qm = Nil;
	    break;
	}
    return mouse_click_event_name(click_qm,modifier_bits);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* MOUSE-CLICK-EVENT-NAME */
Object mouse_click_event_name(click_qm,modifier_bits)
    Object click_qm, modifier_bits;
{
    Object write_symbols_parsably_qm, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(6);
    Object result;

    x_note_fn_call(222,65);
    if (click_qm) {
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		5);
	  current_wide_string_list = Qdo_not_use;
	  PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		  4);
	    wide_string_bv16 = allocate_byte_vector_16(FIX((SI_Long)2048L 
		    + (SI_Long)3L));
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
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			  0);
		    twrite_key_modifier_bits(FIXNUM_LOGIOR(FIX((SI_Long)770L),
			    modifier_bits),Nil);
		    twrite_symbol(1,click_qm);
		    temp = copy_out_current_wide_string();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  result = intern_text_string(1,nstring_upcasew(temp));
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

static Object Qbits;               /* bits */

static Object Qevent;              /* event */

static Object Qpane;               /* pane */

static Object Qx;                  /* x */

static Object Qy;                  /* y */

/* HANDLE-STATUS-BAR-MESSAGE */
Object handle_status_bar_message(mouse_pointer)
    Object mouse_pointer;
{
    Object gensym_window, event_plist, x_in_window, y_in_window, status_bar;
    Object bits, event_qm, pane_qm, user_window_x, user_window_y, procedure;
    Object result;

    x_note_fn_call(222,66);
    gensym_window = window_blackboard_function(mouse_pointer);
    event_plist = event_plist_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (gensym_window && event_plist && x_in_window && y_in_window) {
	status_bar = get_status_bar(gensym_window);
	bits = getf(event_plist,Qbits,FIX((SI_Long)0L));
	event_qm = status_bar_event_name(getf(event_plist,Qevent,_),bits);
	pane_qm = status_bar_find_pane_by_handle(status_bar,
		getf(event_plist,Qpane,_));
	if (event_qm) {
	    result = gensym_window_point_to_user_window_point(gensym_window,
		    x_in_window,y_in_window);
	    MVS_2(result,user_window_x,user_window_y);
	    procedure = get_view_callback_if_any(status_bar);
	    if (procedure)
		return invoke_view_callback_1(status_bar,procedure,
			event_qm,pane_qm ? ISVREF(pane_qm,(SI_Long)2L) : 
			Nil,eval_list_4(Qx,user_window_x,Qy,user_window_y),
			pane_qm ? ISVREF(pane_qm,(SI_Long)3L) : Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_logbook_view = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_logbook_views, Qchain_of_available_logbook_views);

DEFINE_VARIABLE_WITH_SYMBOL(Logbook_view_count, Qlogbook_view_count);

Object Chain_of_available_logbook_views_vector = UNBOUND;

/* LOGBOOK-VIEW-STRUCTURE-MEMORY-USAGE */
Object logbook_view_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(222,67);
    temp = Logbook_view_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)30L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LOGBOOK-VIEW-COUNT */
Object outstanding_logbook_view_count()
{
    Object def_structure_logbook_view_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,68);
    gensymed_symbol = IFIX(Logbook_view_count);
    def_structure_logbook_view_variable = Chain_of_available_logbook_views;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_logbook_view_variable))
	goto end_loop;
    def_structure_logbook_view_variable = 
	    ISVREF(def_structure_logbook_view_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LOGBOOK-VIEW-1-1 */
Object reclaim_logbook_view_1_1(logbook_view)
    Object logbook_view;
{
    Object temp, svref_arg_2;

    x_note_fn_call(222,69);
    inline_note_reclaim_cons(logbook_view,Nil);
    temp = ISVREF(Chain_of_available_logbook_views_vector,
	    IFIX(Current_thread_index));
    SVREF(logbook_view,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_logbook_views_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = logbook_view;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LOGBOOK-VIEW */
Object reclaim_structure_for_logbook_view(logbook_view)
    Object logbook_view;
{
    x_note_fn_call(222,70);
    return reclaim_logbook_view_1_1(logbook_view);
}

static Object Qg2_defstruct_structure_name_logbook_view_g2_struct;  /* g2-defstruct-structure-name::logbook-view-g2-struct */

/* MAKE-PERMANENT-LOGBOOK-VIEW-STRUCTURE-INTERNAL */
Object make_permanent_logbook_view_structure_internal()
{
    Object def_structure_logbook_view_variable;
    Object defstruct_g2_logbook_view_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(222,71);
    def_structure_logbook_view_variable = Nil;
    atomic_incff_symval(Qlogbook_view_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_logbook_view_variable = Nil;
	gensymed_symbol = (SI_Long)30L;
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
	defstruct_g2_logbook_view_variable = the_array;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_logbook_view_g2_struct;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)21L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)22L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)23L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)24L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)25L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)26L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)27L)) = Nil;
	SVREF(defstruct_g2_logbook_view_variable,FIX((SI_Long)28L)) = Nil;
	def_structure_logbook_view_variable = 
		defstruct_g2_logbook_view_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_logbook_view_variable);
}

/* MAKE-LOGBOOK-VIEW-1-1 */
Object make_logbook_view_1_1()
{
    Object def_structure_logbook_view_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(222,72);
    def_structure_logbook_view_variable = 
	    ISVREF(Chain_of_available_logbook_views_vector,
	    IFIX(Current_thread_index));
    if (def_structure_logbook_view_variable) {
	svref_arg_1 = Chain_of_available_logbook_views_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_logbook_view_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_logbook_view_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_logbook_view_g2_struct;
    }
    else
	def_structure_logbook_view_variable = 
		make_permanent_logbook_view_structure_internal();
    inline_note_allocate_cons(def_structure_logbook_view_variable,Nil);
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_logbook_view_variable,(SI_Long)2L) = 
	    FIX((SI_Long)-1L);
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_logbook_view_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_logbook_view_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(def_structure_logbook_view_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_logbook_view_variable,(SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)8L)) = Nil;
    ISVREF(def_structure_logbook_view_variable,(SI_Long)9L) = FIX((SI_Long)0L);
    ISVREF(def_structure_logbook_view_variable,(SI_Long)10L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)16L)) = Qdestroy;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)22L)) = T;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)25L)) = T;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_logbook_view_variable,FIX((SI_Long)28L)) = Nil;
    ISVREF(def_structure_logbook_view_variable,(SI_Long)29L) = 
	    FIX((SI_Long)1L);
    return VALUES_1(def_structure_logbook_view_variable);
}

static Object Qg2_output_view;     /* g2-output-view */

/* MAKE-LOGBOOK-VIEW */
Object make_logbook_view(gensym_window,callback,container,options)
    Object gensym_window, callback, container, options;
{
    Object lbv;

    x_note_fn_call(222,73);
    lbv = make_logbook_view_1_1();
    initialize_native_view(6,lbv,gensym_window,Qg2_output_view,container,
	    options,callback);
    return VALUES_1(lbv);
}

/* CLEAN-UP-STRUCTURE-FOR-LOGBOOK-VIEW */
Object clean_up_structure_for_logbook_view(logbook_view)
    Object logbook_view;
{
    Object gensym_window, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,74);
    gensym_window = ISVREF(logbook_view,(SI_Long)1L);
    if (EQ(logbook_view,ISVREF(gensym_window,(SI_Long)65L)))
	SVREF(gensym_window,FIX((SI_Long)65L)) = Nil;
    if (EQ(logbook_view,ISVREF(gensym_window,(SI_Long)66L)))
	SVREF(gensym_window,FIX((SI_Long)66L)) = Nil;
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_logbook_view,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)9L);
    gensymed_symbol_1 = logbook_view;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RECLAIM-LOGBOOK-VIEW */
Object reclaim_logbook_view(lbv)
    Object lbv;
{
    x_note_fn_call(222,75);
    return reclaim_native_window(lbv);
}

/* LOGBOOK-VIEWS-P */
Object logbook_views_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,76);
    if (twng_window_p(gensym_window))
	return VALUES_1(FIXNUM_LT(Icp_window_protocol_supports_manage_logbook,
		ISVREF(gensym_window,(SI_Long)11L)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object Qappend_message;     /* append-message */

static Object Qdelete_message;     /* delete-message */

static Object Qnormal_message;     /* normal-message */

static Object Qfade_message;       /* fade-message */

static Object Qhighlight_message;  /* highlight-message */

static Object Qset_line_wrap;      /* set-line-wrap */

static Object Qset_include_date_in_title;  /* set-include-date-in-title */

static Object string_constant_18;  /* "Unknown action ~a on logbook views." */

/* MANAGE-LOGBOOK-VIEW */
Object manage_logbook_view varargs_1(int, n)
{
    Object lbv, action;
    Object arg, stack_error_qm, gensym_window, handle, svref_new_value;
    Object top_of_stack, message_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(222,77);
    INIT_ARGS_nonrelocating();
    lbv = REQUIRED_ARG_nonrelocating();
    action = REQUIRED_ARG_nonrelocating();
    arg = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    FIX((SI_Long)0L);
    stack_error_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    gensym_window = ISVREF(lbv,(SI_Long)1L);
    handle = ISVREF(lbv,(SI_Long)2L);
    if (logbook_views_p(gensym_window)) {
	if (EQ(action,Qdestroy))
	    return manage_logbook_1(4,gensym_window,FIX((SI_Long)2L),
		    handle,FIX((SI_Long)0L));
	else if (EQ(action,Qappend_message)) {
	    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(arg) != (SI_Long)0L) {
		manage_logbook_1(6,gensym_window,FIX((SI_Long)10L),handle,
			ISVREF(lbv,(SI_Long)29L),Nil,arg);
		svref_new_value = FIXNUM_ADD1(ISVREF(lbv,(SI_Long)29L));
		return VALUES_1(SVREF(lbv,FIX((SI_Long)29L)) = 
			svref_new_value);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(action,Qdelete_message)) {
	    if (FIXNUMP(arg))
		return manage_logbook_1(4,gensym_window,FIX((SI_Long)11L),
			handle,arg);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(action,Qnormal_message)) {
	    if (FIXNUMP(arg))
		return manage_logbook_1(4,gensym_window,FIX((SI_Long)12L),
			handle,arg);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(action,Qfade_message)) {
	    if (FIXNUMP(arg))
		return manage_logbook_1(4,gensym_window,FIX((SI_Long)13L),
			handle,arg);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(action,Qhighlight_message)) {
	    if (FIXNUMP(arg))
		return manage_logbook_1(4,gensym_window,FIX((SI_Long)14L),
			handle,arg);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(action,Qset_line_wrap))
	    return manage_logbook_1(4,gensym_window,FIX((SI_Long)15L),
		    handle,arg ? FIX((SI_Long)1L) : FIX((SI_Long)0L));
	else if (EQ(action,Qset_include_date_in_title))
	    return manage_logbook_1(4,gensym_window,FIX((SI_Long)16L),
		    handle,arg ? FIX((SI_Long)1L) : FIX((SI_Long)0L));
	else if (stack_error_qm) {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_18,action);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qselect;             /* select */

static Object Qkey_pressed;        /* key-pressed */

/* LOGBOOK-VIEW-EVENT-NAME */
Object logbook_view_event_name(event_code)
    Object event_code;
{
    x_note_fn_call(222,78);
    if ( !(FIXNUMP(event_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    event_code) && FIXNUM_LE(event_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(event_code)) {
	  case 1:
	    return VALUES_1(Qselect);
	  case 2:
	    return VALUES_1(Qright_click);
	  case 3:
	    return VALUES_1(Qkey_pressed);
	  default:
	    return VALUES_1(Nil);
	}
}

static Object Qwindow;             /* window */

static Object Qmsg;                /* msg */

static Object Qno_user_data;       /* no-user-data */

/* HANDLE-LOGBOOK-VIEW-EVENT */
Object handle_logbook_view_event(mouse_pointer)
    Object mouse_pointer;
{
    Object gensym_window, event_plist, g2_window, handle, lbv_qm, event_qm;
    Object message_serial_number_qm, x_in_window, y_in_window, message_qm;
    Object temp, procedure;

    x_note_fn_call(222,79);
    gensym_window = window_blackboard_function(mouse_pointer);
    event_plist = event_plist_blackboard_function(mouse_pointer);
    g2_window = g2_window_blackboard_function(mouse_pointer);
    if (gensym_window && event_plist) {
	handle = getf(event_plist,Qwindow,FIX((SI_Long)-1L));
	lbv_qm = find_native_window(3,gensym_window,handle,Qg2_output_view);
	event_qm = logbook_view_event_name(getf(event_plist,Qevent,_));
	message_serial_number_qm = getf(event_plist,Qmsg,_);
	x_in_window = getf(event_plist,Qx,_);
	y_in_window = getf(event_plist,Qy,_);
	if (native_logbook_p(lbv_qm))
	    message_qm = find_logbook_message(message_serial_number_qm);
	else if (native_message_board_p(lbv_qm))
	    message_qm = find_message_board_message(message_serial_number_qm);
	else
	    message_qm = Qnil;
	temp =  !TRUEP(lbv_qm) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (message_qm)
	    return handle_logbook_view_event_1(6,lbv_qm,event_qm,
		    message_qm,x_in_window,y_in_window,g2_window);
	else {
	    procedure = get_view_callback_if_any(lbv_qm);
	    if (procedure)
		return invoke_view_callback_1(lbv_qm,procedure,event_qm,
			message_serial_number_qm,Nil,Qno_user_data);
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qtext_box;           /* text-box */

/* HANDLE-LOGBOOK-VIEW-EVENT-1 */
Object handle_logbook_view_event_1 varargs_1(int, n)
{
    Object lbv, event, message_1, x_in_window, y_in_window;
    Object g2_window, workstation, mouse_pointer;
    Declare_varargs_nonrelocating;

    x_note_fn_call(222,80);
    INIT_ARGS_nonrelocating();
    lbv = REQUIRED_ARG_nonrelocating();
    event = REQUIRED_ARG_nonrelocating();
    message_1 = REQUIRED_ARG_nonrelocating();
    x_in_window = REQUIRED_ARG_nonrelocating();
    y_in_window = REQUIRED_ARG_nonrelocating();
    g2_window = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workstation = ISVREF(ISVREF(lbv,(SI_Long)1L),(SI_Long)2L);
    update_att_tables(message_1,g2_window);
    if (EQ(event,Qselect))
	return VALUES_1(Nil);
    else if (EQ(event,Qright_click)) {
	mouse_pointer = synthesize_mouse_pointer(3,workstation,message_1,
		FIX((SI_Long)768L));
	post_command_menu(5,Qtext_box,mouse_pointer,x_in_window,
		y_in_window,message_1);
	return release_mouse_pointer_if_any(mouse_pointer);
    }
    else if (EQ(event,Qkey_pressed))
	return VALUES_1(Nil);
    else
	return VALUES_1(Qnil);
}

static Object Qtitle;              /* title */

static Object Qheight;             /* height */

static Object Qcontainer;          /* container */

static Object Qclose_action;       /* close-action */

static Object Qdock;               /* dock */

static Object Qneighbor;           /* neighbor */

static Object Qstate;              /* state */

static Object Qautohidden;         /* autohidden */

static Object Qhidden;             /* hidden */

/* CREATE-LOGBOOK-VIEW */
Object create_logbook_view varargs_1(int, n)
{
    Object gensym_window, title, width, height;
    Object dock_qm, neighbor_qm, hidden_qm, container, gensymed_symbol;
    Object gensymed_symbol_1, temp, options, lbv;
    Declare_varargs_nonrelocating;

    x_note_fn_call(222,81);
    INIT_ARGS_nonrelocating();
    gensym_window = REQUIRED_ARG_nonrelocating();
    title = REQUIRED_ARG_nonrelocating();
    width = REQUIRED_ARG_nonrelocating();
    height = REQUIRED_ARG_nonrelocating();
    dock_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    neighbor_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    hidden_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    container = Qpane;
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)10L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qtitle;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = title;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qwidth;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = width;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qheight;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = height;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qcontainer;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = container;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qclose_action;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qhide;
    temp = dock_qm ? gensym_list_2(Qdock,dock_qm) : Nil;
    options = nconc2(gensymed_symbol,nconc2(temp,nconc2(neighbor_qm ? 
	    gensym_list_2(Qneighbor,neighbor_qm) : Nil,hidden_qm ? 
	    gensym_list_2(Qstate,dock_qm ? Qautohidden : Qhidden) : Nil)));
    lbv = make_logbook_view(gensym_window,Nil,container,options);
    manage_logbook_1(6,gensym_window,FIX((SI_Long)1L),ISVREF(lbv,
	    (SI_Long)2L),FIX((SI_Long)0L),FIX((SI_Long)0L),options);
    reclaim_gensym_list_1(options);
    return VALUES_1(lbv);
}

/* POPULATE-LOGBOOK-VIEW */
Object populate_logbook_view(lbv,messages)
    Object lbv, messages;
{
    Object gensym_window, handle, message_1, ab_loop_list_, string_1, number;
    Object date, temp;

    x_note_fn_call(222,82);
    gensym_window = ISVREF(lbv,(SI_Long)1L);
    handle = ISVREF(lbv,(SI_Long)2L);
    message_1 = Nil;
    ab_loop_list_ = messages;
    string_1 = Nil;
    number = Nil;
    date = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    message_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = ISVREF(message_1,(SI_Long)16L);
    string_1 = convert_text_to_text_string(1,CDR(temp));
    temp = ISVREF(message_1,(SI_Long)20L);
    if (temp);
    else {
	temp = FIXNUM_ADD1(ISVREF(lbv,(SI_Long)29L));
	SVREF(lbv,FIX((SI_Long)29L)) = temp;
    }
    number = temp;
    temp = ISVREF(message_1,(SI_Long)21L);
    if (temp);
    else
	temp = FIX((SI_Long)0L);
    date = temp;
    manage_logbook_1(6,gensym_window,FIX((SI_Long)10L),handle,number,date,
	    string_1);
    reclaim_text_string(string_1);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* APPEND-MESSAGE-TO-LOGBOOK-VIEW */
Object append_message_to_logbook_view(lbv,message_number,date,string_1)
    Object lbv, message_number, date, string_1;
{
    x_note_fn_call(222,83);
    return manage_logbook_1(6,ISVREF(lbv,(SI_Long)1L),FIX((SI_Long)10L),
	    ISVREF(lbv,(SI_Long)2L),message_number,date,string_1);
}

static Object Qmessage_board;      /* message-board */

static Object Qlogbook;            /* logbook */

static Object Qautoshown;          /* autoshown */

/* APPEND-MESSAGE-TO-ALL-LOGBOOK-VIEWS */
Object append_message_to_all_logbook_views(message_1,autoshow,type)
    Object message_1, autoshow, type;
{
    Object string_qm, message_number, message_date, workstation, ab_loop_list_;
    Object gensym_window, temp, lbv_qm, newly_created_qm;
    Object result;

    x_note_fn_call(222,84);
    string_qm = Nil;
    message_number = ISVREF(message_1,(SI_Long)20L);
    if (message_number);
    else
	message_number = FIX((SI_Long)0L);
    message_date = ISVREF(message_1,(SI_Long)21L);
    if (message_date);
    else
	message_date = FIX((SI_Long)0L);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    if ( !TRUEP(workstation_dead_p(ISVREF(gensym_window,(SI_Long)2L)))) {
	if (EQ(type,Qmessage_board))
	    temp = use_native_message_board_p(gensym_window);
	else if (EQ(type,Qlogbook))
	    temp = use_native_logbook_p(gensym_window);
	else
	    temp = Qnil;
	if (temp) {
	    if ( !TRUEP(string_qm)) {
		temp = ISVREF(message_1,(SI_Long)16L);
		string_qm = convert_text_to_text_string(1,CDR(temp));
	    }
	    if (EQ(type,Qmessage_board))
		result = ensure_native_message_board(gensym_window);
	    else if (EQ(type,Qlogbook))
		result = ensure_native_logbook(gensym_window);
	    else
		result = VALUES_1(Qnil);
	    MVS_2(result,lbv_qm,newly_created_qm);
	    if (lbv_qm) {
		if (autoshow)
		    pct_set_native_window_state(lbv_qm,Qautoshown);
		if ( !TRUEP(newly_created_qm))
		    append_message_to_logbook_view(lbv_qm,message_number,
			    message_date,string_qm);
	    }
	}
    }
    goto next_loop;
  end_loop:;
    if (string_qm)
	return reclaim_text_string(string_qm);
    else
	return VALUES_1(Nil);
}

/* DESTROY-NATIVE-LOGBOOK-VIEWS */
Object destroy_native_logbook_views(logbook_p)
    Object logbook_p;
{
    Object workstation, ab_loop_list_, gensym_window, lbv_qm;

    x_note_fn_call(222,85);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
    lbv_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    lbv_qm = logbook_p ? ISVREF(gensym_window,(SI_Long)65L) : 
	    ISVREF(gensym_window,(SI_Long)66L);
    if (lbv_qm)
	manage_logbook_1(4,gensym_window,FIX((SI_Long)2L),ISVREF(lbv_qm,
		(SI_Long)2L),FIX((SI_Long)0L));
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* REMOVE-BLOCK-FROM-NATIVE-VIEWS */
Object remove_block_from_native_views(block)
    Object block;
{
    Object sub_class_bit_vector, temp_1, logbook_p, board_p, messages;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(222,86);
    if (EQ(block,current_message_board_qm()))
	return destroy_native_logbook_views(Nil);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Logbook_page_class_description,(SI_Long)18L));
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
	    if (current_logbook_qm()) {
		temp_1 = ISVREF(Current_logbook_qm,(SI_Long)20L);
		temp =  !TRUEP(CDR(temp_1));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		temp_1 = ISVREF(Current_logbook_qm,(SI_Long)20L);
		temp = EQ(block,CAR(temp_1));
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp)
		return destroy_native_logbook_views(T);
	    else
		return remove_messages_on_page(block,T);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
		logbook_p = message_on_logbook_p(block);
		board_p = message_on_message_board_p(block);
		if (logbook_p || board_p) {
		    messages = gensym_cons_1(block,Nil);
		    remove_messages_from_native_books(messages,logbook_p);
		    return reclaim_gensym_list_1(messages);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Qnil);
	}
    }
}

/* REMOVE-MESSAGES-ON-PAGE */
Object remove_messages_on_page(workspace,logbook_p)
    Object workspace, logbook_p;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, block;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, sub_class_bit_vector;
    Object messages;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(222,87);
    gensymed_symbol = ACCESS_ONCE(ISVREF(workspace,(SI_Long)14L));
    gensymed_symbol = gensymed_symbol ? ACCESS_ONCE(ISVREF(gensymed_symbol,
	    (SI_Long)4L)) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    block = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    if (ab_queue_form_)
	ab_next_queue_element_ = constant_queue_next(ISVREF(ab_queue_form_,
		(SI_Long)2L),ab_queue_form_);
  next_loop:
    if ( !TRUEP(ab_next_queue_element_))
	goto end_loop;
    block = ISVREF(ab_next_queue_element_,(SI_Long)4L);
    ab_next_queue_element_ = constant_queue_next(ab_next_queue_element_,
	    ab_queue_form_);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
	ab_loopvar__2 = gensym_cons_1(block,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    messages = ab_loopvar_;
    goto end_1;
    messages = Qnil;
  end_1:;
    remove_messages_from_native_books(messages,logbook_p);
    return reclaim_gensym_list_1(messages);
}

/* REMOVE-MESSAGES-FROM-NATIVE-BOOKS */
Object remove_messages_from_native_books(messages,logbook_p)
    Object messages, logbook_p;
{
    Object workstation, ab_loop_list_, gensym_window, lbv_qm;
    Object icp_output_port_qm, current_icp_port, current_icp_socket, temp;
    Object disable_resumability, number_of_icp_bytes_for_message_series;
    Object icp_buffers_for_message_group;
    Object icp_buffer_of_start_of_message_series_qm;
    Object icp_byte_position_of_start_of_message_series_qm;
    Object number_of_icp_bytes_to_fill_buffer, current_icp_buffer;
    Object current_write_icp_byte_position;
    Object number_of_icp_bytes_in_message_group, writing_icp_message_group;
    Object gensymed_symbol, aref_arg_1, message_1, ab_loop_list__1;
    double gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    double gensymed_symbol_4, gensymed_symbol_5, aref_new_value;
    Declare_special(12);

    x_note_fn_call(222,88);
    if (messages) {
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
	gensym_window = Nil;
	lbv_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensym_window = ISVREF(workstation,(SI_Long)1L);
	lbv_qm = logbook_p ? ISVREF(gensym_window,(SI_Long)65L) : 
		ISVREF(gensym_window,(SI_Long)66L);
	if (lbv_qm) {
	    if (EQ(ISVREF(gensym_window,(SI_Long)1L),Qicp)) {
		icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
		if (icp_output_port_qm && 
			icp_connection_open_p(ISVREF(icp_output_port_qm,
			(SI_Long)2L))) {
		    current_icp_port = icp_output_port_qm;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			    11);
		      current_icp_socket = ISVREF(Current_icp_port,
			      (SI_Long)2L);
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			      10);
			temp = IFIX(ISVREF(Current_icp_socket,
				(SI_Long)22L)) >= (SI_Long)17L ? 
				ISVREF(Current_icp_socket,(SI_Long)53L) : Nil;
			if (temp);
			else
			    temp = EQ(ISVREF(Current_icp_socket,
				    (SI_Long)25L),Qtelewindows) ? T : Nil;
			disable_resumability = temp;
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
					    gensymed_symbol_1 = 0.0;
					    gensymed_symbol_2 = 0.0;
					    if (Profiling_enabled_qm) {
						gensymed_symbol = T;
						gensymed_symbol_1 = 
							DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							(SI_Long)2L),
							(SI_Long)0L);
						gensymed_symbol_2 = 
							g2ext_unix_time_as_float();
						aref_arg_1 = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)2L);
						DFLOAT_ISASET_1(aref_arg_1,
							(SI_Long)0L,
							gensymed_symbol_2);
					    }
					    if (icp_connection_open_p(Current_icp_socket) 
						    &&  
						    !TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
							{
						message_1 = Nil;
						ab_loop_list__1 = messages;
					      next_loop_1:
						if ( !TRUEP(ab_loop_list__1))
						    goto end_loop_1;
						message_1 = 
							M_CAR(ab_loop_list__1);
						ab_loop_list__1 = 
							M_CDR(ab_loop_list__1);
						if (ISVREF(message_1,
							(SI_Long)20L)) {
						    send_icp_manage_logbook(gensym_window,
							    FIX((SI_Long)11L),
							    ISVREF(lbv_qm,
							    (SI_Long)2L),
							    ISVREF(message_1,
							    (SI_Long)20L),
							    FIX((SI_Long)0L),
							    FIX((SI_Long)0L));
						    ISVREF(message_1,
							    (SI_Long)20L) 
							    = Nil;
						}
						goto next_loop_1;
					      end_loop_1:;
						end_icp_message_group();
					    }
					    if (Profiling_enabled_qm) {
						gensymed_symbol_3 = 
							g2ext_unix_time_as_float();
						gensymed_symbol_4 = 
							DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
							(SI_Long)2L),
							(SI_Long)0L);
						gensymed_symbol_5 = 
							gensymed_symbol_3 
							- gensymed_symbol_4;
						aref_arg_1 = 
							ISVREF(Profiling_enabled_qm,
							(SI_Long)6L);
						aref_new_value = 
							gensymed_symbol_5 
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
							gensymed_symbol_1 
							+ 
							gensymed_symbol_5 
							+ 
							(gensymed_symbol_4 
							- 
							gensymed_symbol_2) 
							: gensymed_symbol_3;
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
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qshow_operator_logbook_in_this_window_qm;  /* show-operator-logbook-in-this-window? */

/* USE-NATIVE-LOGBOOK-P */
Object use_native_logbook_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,89);
    if (ISVREF(Logbook_parameters,(SI_Long)39L) && 
	    logbook_views_p(gensym_window) && 
	    g2_window_for_gensym_window_qm(gensym_window))
	return get_lookup_slot_value_given_default(g2_window_for_gensym_window_qm(gensym_window),
		Qshow_operator_logbook_in_this_window_qm,T);
    else
	return VALUES_1(Nil);
}

/* NATIVE-LOGBOOK-P */
Object native_logbook_p(native_window)
    Object native_window;
{
    x_note_fn_call(222,90);
    return VALUES_1(EQ(native_window,ISVREF(ISVREF(native_window,
	    (SI_Long)1L),(SI_Long)65L)) ? T : Nil);
}

/* FIND-LOGBOOK-MESSAGE */
Object find_logbook_message(serial_number_qm)
    Object serial_number_qm;
{
    Object gensymed_symbol, ab_loop_list_, ab_queue_form_;
    Object ab_next_queue_element_, message_1, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(222,91);
    if (serial_number_qm) {
	if (current_logbook_qm()) {
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(Current_logbook_qm,(SI_Long)20L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(gensymed_symbol,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    message_1 = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_1:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_1;
	    message_1 = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    sub_class_bit_vector = ISVREF(ISVREF(message_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
		temp_1 = ISVREF(message_1,(SI_Long)20L);
		if (EQL(serial_number_qm,temp_1))
		    return VALUES_1(message_1);
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
    else
	return VALUES_1(Nil);
}

/* ENSURE-NATIVE-LOGBOOK */
Object ensure_native_logbook(gensym_window)
    Object gensym_window;
{
    Object temp, svref_new_value;

    x_note_fn_call(222,92);
    temp = ISVREF(gensym_window,(SI_Long)65L);
    if (temp)
	return VALUES_1(temp);
    else if ( !TRUEP(workstation_dead_p(ISVREF(gensym_window,(SI_Long)2L)))) {
	svref_new_value = create_native_logbook(gensym_window);
	return VALUES_2(SVREF(gensym_window,FIX((SI_Long)65L)) = 
		svref_new_value,T);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant;      /* # */

/* CREATE-NATIVE-LOGBOOK */
Object create_native_logbook(gensym_window)
    Object gensym_window;
{
    Object dock, neighbor, lbv, messages, gensymed_symbol, ab_loop_list_;
    Object ab_queue_form_, ab_next_queue_element_, message_1;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char hide_qm, temp;

    x_note_fn_call(222,93);
    dock = ISVREF(Logbook_parameters,(SI_Long)41L);
    neighbor = Nil;
    hide_qm =  !TRUEP(ISVREF(Logbook_parameters,(SI_Long)38L));
    lbv = create_logbook_view(7,gensym_window,array_constant,
	    ISVREF(Logbook_parameters,(SI_Long)22L),
	    ISVREF(Logbook_parameters,(SI_Long)23L),dock,neighbor,hide_qm ?
	     T : Nil);
    if (current_logbook_qm()) {
	if (ISVREF(Logbook_parameters,(SI_Long)40L))
	    manage_logbook_view(3,lbv,Qset_include_date_in_title,Nil);
	messages = Nil;
	if (current_logbook_qm()) {
	    gensymed_symbol = Nil;
	    ab_loop_list_ = ISVREF(Current_logbook_qm,(SI_Long)20L);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    gensymed_symbol = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = ACCESS_ONCE(ISVREF(gensymed_symbol,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    message_1 = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop_1:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop_1;
	    message_1 = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    sub_class_bit_vector = ISVREF(ISVREF(message_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
		messages = gensym_cons_1(message_1,messages);
	    goto next_loop_1;
	  end_loop_1:;
	    goto next_loop;
	  end_loop:;
	}
	populate_logbook_view(lbv,messages);
	reclaim_gensym_list_1(messages);
    }
    return VALUES_1(lbv);
}

/* SHOW-NATIVE-LOGBOOK */
Object show_native_logbook(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,94);
    if (ISVREF(gensym_window,(SI_Long)65L))
	return pct_set_native_window_state(ISVREF(gensym_window,
		(SI_Long)65L),Qautoshown);
    else
	return ensure_native_logbook(gensym_window);
}

/* HIDE-NATIVE-LOGBOOK */
Object hide_native_logbook(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,95);
    if (ISVREF(gensym_window,(SI_Long)65L))
	return pct_set_native_window_state(ISVREF(gensym_window,
		(SI_Long)65L),Qhidden);
    else
	return VALUES_1(Nil);
}

/* APPEND-MESSAGE-TO-ALL-NATIVE-LOGBOOKS */
Object append_message_to_all_native_logbooks(message_1)
    Object message_1;
{
    x_note_fn_call(222,96);
    return append_message_to_all_logbook_views(message_1,
	    ISVREF(Logbook_parameters,(SI_Long)38L),Qlogbook);
}

static Object Qprefer_native;      /* prefer-native */

static Object Qinclude_date;       /* include-date */

/* NOTE-NATIVE-LOGBOOK-PREFERENCE-CHANGED */
Object note_native_logbook_preference_changed(preference,new_value)
    Object preference, new_value;
{
    Object workstation, ab_loop_list_, gensym_window, g2_window_qm;

    x_note_fn_call(222,97);
    workstation = Nil;
    ab_loop_list_ = Workstations_in_service;
    gensym_window = Nil;
    g2_window_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    workstation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensym_window = ISVREF(workstation,(SI_Long)1L);
    g2_window_qm = g2_window_for_gensym_window_qm(gensym_window);
    if ( !TRUEP(g2_window_qm));
    else if ( !TRUEP(logbook_views_p(gensym_window)));
    else if (EQ(preference,Qprefer_native)) {
	if (new_value && use_native_logbook_p(gensym_window)) {
	    hide_logbook_in_g2_window(g2_window_qm);
	    show_native_logbook(gensym_window);
	}
	else if (ISVREF(gensym_window,(SI_Long)65L)) {
	    manage_logbook_view(2,ISVREF(gensym_window,(SI_Long)65L),Qdestroy);
	    show_logbook_in_g2_window(g2_window_qm);
	}
    }
    else if (EQ(preference,Qinclude_date)) {
	if (ISVREF(gensym_window,(SI_Long)65L))
	    manage_logbook_view(3,ISVREF(gensym_window,(SI_Long)65L),
		    Qset_include_date_in_title, !TRUEP(new_value) ? T : Nil);
    }
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* USE-NATIVE-MESSAGE-BOARD-P */
Object use_native_message_board_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,98);
    if (ISVREF(Message_board_parameters,(SI_Long)28L))
	return logbook_views_p(gensym_window);
    else
	return VALUES_1(Nil);
}

/* NATIVE-MESSAGE-BOARD-P */
Object native_message_board_p(native_window)
    Object native_window;
{
    x_note_fn_call(222,99);
    return VALUES_1(EQ(native_window,ISVREF(ISVREF(native_window,
	    (SI_Long)1L),(SI_Long)66L)) ? T : Nil);
}

/* FIXNUM-LESSP */
Object fixnum_lessp(a,b)
    Object a, b;
{
    x_note_fn_call(222,100);
    return VALUES_1(FIXNUM_LT(a,b) ? T : Nil);
}

/* FIND-MESSAGE-BOARD-MESSAGE */
Object find_message_board_message(serial_number_qm)
    Object serial_number_qm;
{
    Object gensymed_symbol, ab_queue_form_, ab_next_queue_element_, message_1;
    Object sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(222,101);
    if (serial_number_qm) {
	if (current_message_board_qm()) {
	    gensymed_symbol = ACCESS_ONCE(ISVREF(Current_message_board_qm,
		    (SI_Long)14L));
	    gensymed_symbol = gensymed_symbol ? 
		    ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    message_1 = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = 
			constant_queue_next(ISVREF(ab_queue_form_,
			(SI_Long)2L),ab_queue_form_);
	  next_loop:
	    if ( !TRUEP(ab_next_queue_element_))
		goto end_loop;
	    message_1 = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	    ab_next_queue_element_ = 
		    constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	    sub_class_bit_vector = ISVREF(ISVREF(message_1,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Message_class_description,(SI_Long)18L));
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
	    if (temp ? TRUEP(ISVREF(message_1,(SI_Long)20L)) : TRUEP(Nil)) {
		temp_1 = ISVREF(message_1,(SI_Long)20L);
		if (EQL(serial_number_qm,temp_1))
		    return VALUES_1(message_1);
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qfixnum_lessp;       /* fixnum-lessp */

static Object Qmessage_serial_number_function;  /* message-serial-number-function */

/* GET-MESSAGE-BOARD-MESSAGES */
Object get_message_board_messages()
{
    Object messages, gensymed_symbol, ab_queue_form_, ab_next_queue_element_;
    Object message_1, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(222,102);
    messages = Nil;
    if (current_message_board_qm()) {
	gensymed_symbol = ACCESS_ONCE(ISVREF(Current_message_board_qm,
		(SI_Long)14L));
	gensymed_symbol = gensymed_symbol ? 
		ACCESS_ONCE(ISVREF(gensymed_symbol,(SI_Long)4L)) : Nil;
	ab_queue_form_ = gensymed_symbol;
	ab_next_queue_element_ = Nil;
	message_1 = Nil;
	if (ab_queue_form_)
	    ab_next_queue_element_ = 
		    constant_queue_next(ISVREF(ab_queue_form_,(SI_Long)2L),
		    ab_queue_form_);
      next_loop:
	if ( !TRUEP(ab_next_queue_element_))
	    goto end_loop;
	message_1 = ISVREF(ab_next_queue_element_,(SI_Long)4L);
	ab_next_queue_element_ = 
		constant_queue_next(ab_next_queue_element_,ab_queue_form_);
	sub_class_bit_vector = ISVREF(ISVREF(message_1,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Message_class_description,
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
	if (temp ? TRUEP(ISVREF(message_1,(SI_Long)20L)) : TRUEP(Nil))
	    messages = gensym_cons_1(message_1,messages);
	goto next_loop;
      end_loop:;
    }
    return sort_list(messages,SYMBOL_FUNCTION(Qfixnum_lessp),
	    SYMBOL_FUNCTION(Qmessage_serial_number_function));
}

/* ENSURE-NATIVE-MESSAGE-BOARD */
Object ensure_native_message_board(gensym_window)
    Object gensym_window;
{
    Object temp, svref_new_value;

    x_note_fn_call(222,103);
    temp = ISVREF(gensym_window,(SI_Long)66L);
    if (temp)
	return VALUES_1(temp);
    else {
	svref_new_value = create_native_message_board(gensym_window);
	return VALUES_2(SVREF(gensym_window,FIX((SI_Long)66L)) = 
		svref_new_value,T);
    }
}

static Object Qright;              /* right */

static Object array_constant_1;    /* # */

/* CREATE-NATIVE-MESSAGE-BOARD */
Object create_native_message_board(gensym_window)
    Object gensym_window;
{
    Object dock_qm, neighbor_qm, lbv, messages;

    x_note_fn_call(222,104);
    dock_qm = Qright;
    neighbor_qm = Nil;
    lbv = create_logbook_view(6,gensym_window,array_constant_1,
	    ISVREF(Message_board_parameters,(SI_Long)22L),
	    ISVREF(Message_board_parameters,(SI_Long)23L),dock_qm,neighbor_qm);
    messages = get_message_board_messages();
    if (ISVREF(Message_board_parameters,(SI_Long)29L))
	manage_logbook_view(3,lbv,Qset_include_date_in_title,Nil);
    populate_logbook_view(lbv,messages);
    reclaim_gensym_list_1(messages);
    return VALUES_1(lbv);
}

/* SHOW-NATIVE-MESSAGE-BOARD */
Object show_native_message_board(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,105);
    if (ISVREF(gensym_window,(SI_Long)66L))
	return pct_set_native_window_state(ISVREF(gensym_window,
		(SI_Long)66L),Qautoshown);
    else
	return ensure_native_message_board(gensym_window);
}

/* HIDE-NATIVE-MESSAGE-BOARD */
Object hide_native_message_board(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,106);
    if (ISVREF(gensym_window,(SI_Long)66L))
	return pct_set_native_window_state(ISVREF(gensym_window,
		(SI_Long)66L),Qhidden);
    else
	return VALUES_1(Nil);
}

/* APPEND-MESSAGE-TO-ALL-NATIVE-MESSAGE-BOARDS */
Object append_message_to_all_native_message_boards(message_1)
    Object message_1;
{
    x_note_fn_call(222,107);
    return append_message_to_all_logbook_views(message_1,Nil,Qmessage_board);
}

/* NOTE-NATIVE-MESSAGE-BOARD-PREFERENCE-CHANGED */
Object note_native_message_board_preference_changed(preference,new_value)
    Object preference, new_value;
{
    Object workstation, ab_loop_list_, gensym_window, image_plane_qm;
    Object showable_qm;

    x_note_fn_call(222,108);
    if (current_message_board_qm()) {
	workstation = Nil;
	ab_loop_list_ = Workstations_in_service;
	gensym_window = Nil;
	image_plane_qm = Nil;
	showable_qm = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	workstation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensym_window = ISVREF(workstation,(SI_Long)1L);
	image_plane_qm = image_plane_of_workspace_on_window(gensym_window,
		Current_message_board_qm);
	showable_qm = 
		workspaces_can_be_shown_at_this_kb_level_p(Current_message_board_qm,
		workstation);
	if (logbook_views_p(gensym_window)) {
	    if (EQ(preference,Qprefer_native)) {
		if (new_value) {
		    if (image_plane_qm)
			delete_image_plane(image_plane_qm);
		    if (showable_qm)
			show_native_message_board(gensym_window);
		}
		else if (ISVREF(gensym_window,(SI_Long)66L)) {
		    manage_logbook_view(2,ISVREF(gensym_window,
			    (SI_Long)66L),Qdestroy);
		    if (showable_qm)
			show_message_board_in_window(gensym_window);
		}
	    }
	    else if (EQ(preference,Qinclude_date)) {
		if (ISVREF(gensym_window,(SI_Long)66L))
		    manage_logbook_view(3,ISVREF(gensym_window,
			    (SI_Long)66L),Qset_include_date_in_title, 
			    !TRUEP(new_value) ? T : Nil);
	    }
	}
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Tabular_view_action, Qtabular_view_action);

Object Tabular_view_options_type = UNBOUND;

Object Tabular_view_action_type = UNBOUND;

Object Tabular_view_column_designation_type = UNBOUND;

Object Tabular_view_column_type = UNBOUND;

Object Tabular_view_add_column_type = UNBOUND;

Object Tabular_view_logical_id_type = UNBOUND;

Object Tabular_view_row_type = UNBOUND;

Object Tabular_view_replace_row_type = UNBOUND;

Object Tabular_view_cell_type = UNBOUND;

Object Tabular_view_column_cell_type = UNBOUND;

Object Tabular_view_replace_cell_type = UNBOUND;

static Object Qadd_column;         /* add-column */

static Object Qadd_columns;        /* add-columns */

/* TABULAR-VIEW-COLUMN-TYPE */
Object tabular_view_column_type()
{
    x_note_fn_call(222,109);
    if (EQ(Tabular_view_action,Qadd_column) || EQ(Tabular_view_action,
	    Qadd_columns))
	return VALUES_1(Tabular_view_add_column_type);
    else
	return VALUES_1(Tabular_view_column_type);
}

static Object Qreplace_cells;      /* replace-cells */

/* TABULAR-VIEW-CELL-TYPE */
Object tabular_view_cell_type()
{
    x_note_fn_call(222,110);
    if (EQ(Tabular_view_action,Qadd_column) || EQ(Tabular_view_action,
	    Qadd_columns))
	return VALUES_1(Tabular_view_column_cell_type);
    else if (EQ(Tabular_view_action,Qreplace_cells))
	return VALUES_1(Tabular_view_replace_cell_type);
    else
	return VALUES_1(Tabular_view_cell_type);
}

Object The_type_description_of_tabular_view = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_tabular_views, Qchain_of_available_tabular_views);

DEFINE_VARIABLE_WITH_SYMBOL(Tabular_view_count, Qtabular_view_count);

Object Chain_of_available_tabular_views_vector = UNBOUND;

/* TABULAR-VIEW-STRUCTURE-MEMORY-USAGE */
Object tabular_view_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(222,111);
    temp = Tabular_view_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)33L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-TABULAR-VIEW-COUNT */
Object outstanding_tabular_view_count()
{
    Object def_structure_tabular_view_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,112);
    gensymed_symbol = IFIX(Tabular_view_count);
    def_structure_tabular_view_variable = Chain_of_available_tabular_views;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_tabular_view_variable))
	goto end_loop;
    def_structure_tabular_view_variable = 
	    ISVREF(def_structure_tabular_view_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-TABULAR-VIEW-1-1 */
Object reclaim_tabular_view_1_1(tabular_view)
    Object tabular_view;
{
    Object temp, svref_arg_2;

    x_note_fn_call(222,113);
    inline_note_reclaim_cons(tabular_view,Nil);
    temp = ISVREF(Chain_of_available_tabular_views_vector,
	    IFIX(Current_thread_index));
    SVREF(tabular_view,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_tabular_views_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = tabular_view;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-TABULAR-VIEW */
Object reclaim_structure_for_tabular_view(tabular_view)
    Object tabular_view;
{
    x_note_fn_call(222,114);
    return reclaim_tabular_view_1_1(tabular_view);
}

static Object Qg2_defstruct_structure_name_tabular_view_g2_struct;  /* g2-defstruct-structure-name::tabular-view-g2-struct */

/* MAKE-PERMANENT-TABULAR-VIEW-STRUCTURE-INTERNAL */
Object make_permanent_tabular_view_structure_internal()
{
    Object def_structure_tabular_view_variable;
    Object defstruct_g2_tabular_view_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(222,115);
    def_structure_tabular_view_variable = Nil;
    atomic_incff_symval(Qtabular_view_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_tabular_view_variable = Nil;
	gensymed_symbol = (SI_Long)33L;
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
	defstruct_g2_tabular_view_variable = the_array;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tabular_view_g2_struct;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)16L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)17L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)18L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)19L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)20L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)21L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)22L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)23L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)24L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)25L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)26L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)27L)) = Nil;
	SVREF(defstruct_g2_tabular_view_variable,FIX((SI_Long)28L)) = Nil;
	def_structure_tabular_view_variable = 
		defstruct_g2_tabular_view_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_tabular_view_variable);
}

/* MAKE-TABULAR-VIEW-1-1 */
Object make_tabular_view_1_1()
{
    Object def_structure_tabular_view_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(222,116);
    def_structure_tabular_view_variable = 
	    ISVREF(Chain_of_available_tabular_views_vector,
	    IFIX(Current_thread_index));
    if (def_structure_tabular_view_variable) {
	svref_arg_1 = Chain_of_available_tabular_views_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_tabular_view_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_tabular_view_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_tabular_view_g2_struct;
    }
    else
	def_structure_tabular_view_variable = 
		make_permanent_tabular_view_structure_internal();
    inline_note_allocate_cons(def_structure_tabular_view_variable,Nil);
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)1L)) = Nil;
    ISVREF(def_structure_tabular_view_variable,(SI_Long)2L) = 
	    FIX((SI_Long)-1L);
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)3L)) = Nil;
    ISVREF(def_structure_tabular_view_variable,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(def_structure_tabular_view_variable,(SI_Long)5L) = FIX((SI_Long)0L);
    ISVREF(def_structure_tabular_view_variable,(SI_Long)6L) = FIX((SI_Long)0L);
    ISVREF(def_structure_tabular_view_variable,(SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)8L)) = Nil;
    ISVREF(def_structure_tabular_view_variable,(SI_Long)9L) = FIX((SI_Long)0L);
    ISVREF(def_structure_tabular_view_variable,(SI_Long)10L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)16L)) = Qdestroy;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)17L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)18L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)19L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)20L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)21L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)22L)) = T;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)23L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)24L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)25L)) = T;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)26L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)28L)) = Nil;
    ISVREF(def_structure_tabular_view_variable,(SI_Long)29L) = 
	    FIX((SI_Long)0L);
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_tabular_view_variable,FIX((SI_Long)32L)) = Nil;
    return VALUES_1(def_structure_tabular_view_variable);
}

/* MAKE-TABULAR-VIEW */
Object make_tabular_view(gensym_window)
    Object gensym_window;
{
    Object tbv;

    x_note_fn_call(222,117);
    tbv = make_tabular_view_1_1();
    SVREF(tbv,FIX((SI_Long)1L)) = gensym_window;
    return VALUES_1(tbv);
}

/* INITIALIZE-TABULAR-VIEW */
Object initialize_tabular_view(tbv,callback,container,user_data,options)
    Object tbv, callback, container, user_data, options;
{
    Object item_or_value, x2, svref_new_value;
    char temp;

    x_note_fn_call(222,118);
    initialize_native_view(6,tbv,ISVREF(tbv,(SI_Long)1L),Qg2_tabular_view,
	    container,options,callback);
    item_or_value = FIXNUMP(user_data) || user_data && SYMBOLP(user_data) 
	    || SIMPLE_VECTOR_P(user_data) ? user_data : 
	    copy_if_evaluation_value_1(user_data);
    if (SIMPLE_VECTOR_P(item_or_value) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_value,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    svref_new_value = temp ? get_reference_to_item(item_or_value) : 
	    item_or_value;
    SVREF(tbv,FIX((SI_Long)32L)) = svref_new_value;
    return VALUES_1(tbv);
}

/* CLEAN-UP-STRUCTURE-FOR-TABULAR-VIEW */
Object clean_up_structure_for_tabular_view(tabular_view)
    Object tabular_view;
{
    Object thing, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(222,119);
    tabular_view_delete_all_rows(tabular_view);
    thing = ISVREF(tabular_view,(SI_Long)32L);
    if ( !(FIXNUMP(thing) || SYMBOLP(thing) || SIMPLE_VECTOR_P(thing)))
	reclaim_if_evaluation_value_1(thing);
    SVREF(tabular_view,FIX((SI_Long)32L)) = Nil;
    gensymed_symbol = 
	    ISVREF(ISVREF(ISVREF(The_type_description_of_tabular_view,
	    (SI_Long)9L),(SI_Long)0L),(SI_Long)9L);
    gensymed_symbol_1 = tabular_view;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RECLAIM-TABULAR-VIEW */
Object reclaim_tabular_view(tbv)
    Object tbv;
{
    x_note_fn_call(222,120);
    return reclaim_native_window(tbv);
}

/* TABULAR-VIEWS-P */
Object tabular_views_p(gensym_window)
    Object gensym_window;
{
    x_note_fn_call(222,121);
    if (nms_controls_p(gensym_window))
	return VALUES_1(FIXNUM_LT(Icp_window_protocol_supports_tabular_views,
		ISVREF(gensym_window,(SI_Long)11L)) ? T : Nil);
    else
	return VALUES_1(Nil);
}

static Object string_constant_19;  /* "Tabular views are not supported on ~NF" */

/* TABULAR-VIEWS-WINDOW-OR-STACK-ERROR */
Object tabular_views_window_or_stack_error(g2_window)
    Object g2_window;
{
    Object gensym_window, top_of_stack, message_1;

    x_note_fn_call(222,122);
    gensym_window = map_to_gensym_window_or_stack_error(g2_window);
    if ( !TRUEP(tabular_views_p(gensym_window))) {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_19,
		g2_window);
	raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(gensym_window);
}

/* %TABULAR-VIEW-FIND-ROW */
Object pct_tabular_view_find_row(tbv,logical_id_qm,row_id_qm)
    Object tbv, logical_id_qm, row_id_qm;
{
    Object cell, ab_loop_list_, logical_id, row_id;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,123);
    cell = Nil;
    ab_loop_list_ = ISVREF(tbv,(SI_Long)30L);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      logical_id = Nil;
      row_id = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Cell = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      logical_id = CAR(Cell);
      row_id = CDR(Cell);
      if (equalw(logical_id_qm,logical_id) || EQL(row_id_qm,row_id)) {
	  result = VALUES_1(Cell);
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* %TABULAR-VIEW-RECLAIM-CELL */
Object pct_tabular_view_reclaim_cell(cell)
    Object cell;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(222,124);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
      reclaim_unboxed_evaluation_value(CAR(Cell));
      result = reclaim_gensym_cons_1(Cell);
    POP_SPECIAL();
    return result;
}

/* TABULAR-VIEW-ADD-LOGICAL-ID */
Object tabular_view_add_logical_id(tbv,logical_id,row_id)
    Object tbv, logical_id, row_id;
{
    Object gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(222,125);
    gensym_push_modify_macro_arg = gensym_cons_1(unbox_evaluation_value(1,
	    logical_id),row_id);
    car_1 = gensym_push_modify_macro_arg;
    cdr_1 = ISVREF(tbv,(SI_Long)30L);
    svref_new_value = gensym_cons_1(car_1,cdr_1);
    return VALUES_1(SVREF(tbv,FIX((SI_Long)30L)) = svref_new_value);
}

/* TABULAR-VIEW-DELETE-ALL-ROWS */
Object tabular_view_delete_all_rows(tbv)
    Object tbv;
{
    x_note_fn_call(222,126);
    reclaim_gensym_list_1(ISVREF(tbv,(SI_Long)31L));
    SVREF(tbv,FIX((SI_Long)31L)) = Nil;
    return tabular_view_reclaim_rows(tbv);
}

/* TABULAR-VIEW-RECLAIM-ROWS */
Object tabular_view_reclaim_rows(tbv)
    Object tbv;
{
    Object cell, ab_loop_list_;
    Declare_special(1);

    x_note_fn_call(222,127);
    cell = Nil;
    ab_loop_list_ = ISVREF(tbv,(SI_Long)30L);
    PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Cell = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      pct_tabular_view_reclaim_cell(Cell);
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    reclaim_gensym_list_1(ISVREF(tbv,(SI_Long)30L));
    return VALUES_1(SVREF(tbv,FIX((SI_Long)30L)) = Nil);
}

/* TABULAR-VIEW-GET-LOGICAL-ID */
Object tabular_view_get_logical_id(tbv,row_id)
    Object tbv, row_id;
{
    Object temp;

    x_note_fn_call(222,128);
    temp = pct_tabular_view_find_row(tbv,Nil,row_id);
    return VALUES_1(CAR(temp));
}

/* TABULAR-VIEW-GET-ROW-ID */
Object tabular_view_get_row_id(tbv,logical_id)
    Object tbv, logical_id;
{
    Object temp;

    x_note_fn_call(222,129);
    temp = pct_tabular_view_find_row(tbv,logical_id,Nil);
    return VALUES_1(CDR(temp));
}

/* TABULAR-VIEW-DELETE-ROWS */
Object tabular_view_delete_rows(tbv,row_ids)
    Object tbv, row_ids;
{
    Object row_id, ab_loop_list_;

    x_note_fn_call(222,130);
    row_id = Nil;
    ab_loop_list_ = row_ids;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    row_id = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    tabular_view_delete_row(tbv,row_id);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qdeselect;           /* deselect */

/* TABULAR-VIEW-DELETE-ROW */
Object tabular_view_delete_row(tbv,row_id)
    Object tbv, row_id;
{
    Object cell_qm, svref_new_value;

    x_note_fn_call(222,131);
    cell_qm = pct_tabular_view_find_row(tbv,Nil,row_id);
    if (cell_qm) {
	tabular_view_update_selected_rows(tbv,Qdeselect,row_id);
	svref_new_value = delete_gensym_element_1(cell_qm,ISVREF(tbv,
		(SI_Long)30L));
	SVREF(tbv,FIX((SI_Long)30L)) = svref_new_value;
	return pct_tabular_view_reclaim_cell(cell_qm);
    }
    else
	return VALUES_1(Nil);
}

/* TABULAR-VIEW-UPDATE-SELECTED-ROWS */
Object tabular_view_update_selected_rows(tbv,event,row_id)
    Object tbv, event, row_id;
{
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list_, ab_loop_it_, svref_new_value;
    char temp;

    x_note_fn_call(222,132);
    if (EQ(event,Qselect)) {
	gensym_modify_macro_using_test_arg_1 = row_id;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = ISVREF(tbv,(SI_Long)31L);
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
	SVREF(tbv,FIX((SI_Long)31L)) = svref_new_value;
    }
    else if (EQ(event,Qdeselect)) {
	svref_new_value = delete_gensym_element_1(row_id,ISVREF(tbv,
		(SI_Long)31L));
	SVREF(tbv,FIX((SI_Long)31L)) = svref_new_value;
    }
    return VALUES_1(ISVREF(tbv,(SI_Long)31L));
}

/* TABULAR-VIEW-SELECTED-ROWS-AS-SEQUENCE */
Object tabular_view_selected_rows_as_sequence(tbv)
    Object tbv;
{
    Object row_id, ab_loop_list_, logical_id_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(222,133);
    row_id = Nil;
    ab_loop_list_ = ISVREF(tbv,(SI_Long)31L);
    logical_id_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    row_id = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    logical_id_qm = tabular_view_get_logical_id(tbv,row_id);
    if (logical_id_qm) {
	ab_loopvar__2 = eval_cons_1(FIXNUMP(logical_id_qm) || 
		logical_id_qm && SYMBOLP(logical_id_qm) || 
		SIMPLE_VECTOR_P(logical_id_qm) ? logical_id_qm : 
		copy_if_evaluation_value_1(logical_id_qm),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    return allocate_evaluation_sequence(temp);
}

static Object string_constant_20;  /* "Tabular-view row with logical-id ~NV not found." */

/* TABULAR-VIEW-FIND-ROW-OR-STACK-ERROR */
Object tabular_view_find_row_or_stack_error(tbv,logical_id_ev)
    Object tbv, logical_id_ev;
{
    Object temp, top_of_stack, message_1;

    x_note_fn_call(222,134);
    temp = tabular_view_get_row_id(tbv,logical_id_ev);
    if (temp)
	return VALUES_1(temp);
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(2,string_constant_20,
		logical_id_ev);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

static Object Qcells;              /* cells */

static Object Qrow_values;         /* row-values */

/* TABULAR-VIEW-CELLS-EVALUE */
Object tabular_view_cells_evalue(estructure)
    Object estructure;
{
    Object temp;

    x_note_fn_call(222,135);
    temp = estructure_slot(estructure,Qcells,Nil);
    if (temp)
	return VALUES_1(temp);
    else
	return estructure_slot(estructure,Qrow_values,Nil);
}

/* PREPROCESS-TABULAR-VIEW-ROWS */
Object preprocess_tabular_view_rows(tbv,evalue_qm)
    Object tbv, evalue_qm;
{
    Object gensymed_symbol, held_vector, row, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,136);
    if (evalue_qm) {
	gensymed_symbol = evalue_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	row = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
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
	  Row = validated_elt;
	  ab_loopvar__2 = gensym_cons_1(preprocess_tabular_view_row(tbv,
		  Row),Nil);
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
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PREPROCESS-TABULAR-VIEW-REPLACE-ROWS */
Object preprocess_tabular_view_replace_rows(tbv,evalue_qm)
    Object tbv, evalue_qm;
{
    Object gensymed_symbol, held_vector, row, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,137);
    if (evalue_qm) {
	gensymed_symbol = evalue_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	row = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Row,Qrow,row,0);
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
	  Row = validated_elt;
	  ab_loopvar__2 = 
		  gensym_cons_1(preprocess_tabular_view_replace_row(tbv,
		  Row),Nil);
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
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PREPROCESS-TABULAR-VIEW-COLUMNS */
Object preprocess_tabular_view_columns(tbv,evalue_qm)
    Object tbv, evalue_qm;
{
    Object gensymed_symbol, held_vector, column, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,138);
    if (evalue_qm) {
	gensymed_symbol = evalue_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	column = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Column,Qcolumn,column,0);
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
	  Column = validated_elt;
	  ab_loopvar__2 = gensym_cons_1(preprocess_tabular_view_column(tbv,
		  Column),Nil);
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
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PREPROCESS-TABULAR-VIEW-CELLS */
Object preprocess_tabular_view_cells(tbv,evalue_qm)
    Object tbv, evalue_qm;
{
    Object gensymed_symbol, held_vector, cell, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,139);
    if (evalue_qm) {
	gensymed_symbol = evalue_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	cell = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Cell,Qcell,cell,0);
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
	  Cell = validated_elt;
	  ab_loopvar__2 = gensym_cons_1(preprocess_tabular_view_cell(tbv,
		  Cell),Nil);
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
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PREPROCESS-TABULAR-VIEW-LOGICAL-IDS */
Object preprocess_tabular_view_logical_ids(tbv,evalue_qm)
    Object tbv, evalue_qm;
{
    Object gensymed_symbol, held_vector, logical_id, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;

    x_note_fn_call(222,140);
    if (evalue_qm) {
	gensymed_symbol = evalue_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	logical_id = Nil;
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
	logical_id = validated_elt;
	ab_loopvar__2 = 
		gensym_cons_1(tabular_view_find_row_or_stack_error(tbv,
		logical_id),Nil);
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
	return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object Qlogical_id;         /* logical-id */

/* PREPROCESS-TABULAR-VIEW-ROW */
Object preprocess_tabular_view_row(tbv,evalue)
    Object tbv, evalue;
{
    Object temp, temp_1, temp_2, cells, plist, logical_id_qm, svref_new_value;
    Object row_id, logical_id;
    Object result;

    x_note_fn_call(222,141);
    check_type_or_stack_error(2,evalue,Tabular_view_row_type);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evalue) != (SI_Long)0L)
	result = gensym_cons_1(unbox_evaluation_value(1,evalue),Nil);
    else if (CONSP(evalue) && EQ(M_CDR(evalue),Qsequence))
	result = preprocess_tabular_view_cells(tbv,evalue);
    else if (CONSP(evalue) && EQ(M_CDR(evalue),Qab_structure)) {
	temp = preprocess_tabular_view_cells(tbv,
		tabular_view_cells_evalue(evalue));
	temp_1 = preprocess_tabular_view_structure(3,tbv,evalue,
		list_constant_5);
	temp_2 = estructure_slot(evalue,Qlogical_id,Nil);
	result = VALUES_3(temp,temp_1,temp_2);
    }
    else
	result = VALUES_1(Qnil);
    MVS_3(result,cells,plist,logical_id_qm);
    temp_2 = ISVREF(tbv,(SI_Long)29L);
    svref_new_value = FIXNUM_ADD1(ISVREF(tbv,(SI_Long)29L));
    SVREF(tbv,FIX((SI_Long)29L)) = svref_new_value;
    row_id = temp_2;
    logical_id = logical_id_qm;
    if (logical_id);
    else
	logical_id = row_id;
    tabular_view_add_logical_id(tbv,logical_id,row_id);
    return gensym_cons_1(row_id,gensym_cons_1(cells,plist));
}

static Object list_constant_6;     /* # */

/* PREPROCESS-TABULAR-VIEW-REPLACE-ROW */
Object preprocess_tabular_view_replace_row(tbv,evalue)
    Object tbv, evalue;
{
    Object row_id, cells, plist;

    x_note_fn_call(222,142);
    check_type_or_stack_error(2,evalue,Tabular_view_replace_row_type);
    row_id = tabular_view_find_row_or_stack_error(tbv,
	    estructure_slot(evalue,Qlogical_id,Nil));
    cells = preprocess_tabular_view_cells(tbv,
	    tabular_view_cells_evalue(evalue));
    plist = preprocess_tabular_view_structure(3,tbv,evalue,list_constant_6);
    return gensym_cons_1(row_id,gensym_cons_1(cells,plist));
}

/* PREPROCESS-TABULAR-VIEW-COLUMN */
Object preprocess_tabular_view_column(tbv,evalue)
    Object tbv, evalue;
{
    x_note_fn_call(222,143);
    check_type_or_stack_error(2,evalue,tabular_view_column_type());
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evalue) != (SI_Long)0L)
	return unbox_evaluation_value(1,evalue);
    else if (CONSP(evalue) && EQ(M_CDR(evalue),Qab_structure))
	return preprocess_tabular_view_structure(2,tbv,evalue);
    else
	return VALUES_1(Qnil);
}

/* PREPROCESS-TABULAR-VIEW-CELL */
Object preprocess_tabular_view_cell(tbv,evalue)
    Object tbv, evalue;
{
    Object evaluation_value;

    x_note_fn_call(222,144);
    check_type_or_stack_error(2,evalue,tabular_view_cell_type());
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(evalue) != (SI_Long)0L)
	return unbox_evaluation_value(1,evalue);
    else if ( !(CONSP(evalue) && EQ(M_CDR(evalue),Qab_structure)))
	return VALUES_1(Nil);
    else if ((SI_Long)1L == IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evalue),
	    (SI_Long)1L))) >>  -  - (SI_Long)1L && estructure_slot(evalue,
	    Qtext_value,Nil)) {
	evaluation_value = estructure_slot(evalue,Qtext_value,Nil);
	if (FIXNUMP(evaluation_value) || evaluation_value && 
		SYMBOLP(evaluation_value))
	    return VALUES_1(evaluation_value);
	else
	    return copy_evaluation_value_1(evaluation_value);
    }
    else if (CONSP(evalue) && EQ(M_CDR(evalue),Qab_structure))
	return preprocess_tabular_view_structure(2,tbv,evalue);
    else
	return VALUES_1(Qnil);
}

static Object Qsort_column;        /* sort-column */

static Object Qsorting_order;      /* sorting-order */

static Object Qtext_color;         /* text-color */

static Object Qgridline_color;     /* gridline-color */

static Object Qrows;               /* rows */

static Object Qadd_rows;           /* add-rows */

static Object Qadd_rows_to_top;    /* add-rows-to-top */

static Object Qadd_row;            /* add-row */

static Object Qreplace_rows;       /* replace-rows */

static Object Qmodify_rows;        /* modify-rows */

static Object Qreplace_row;        /* replace-row */

static Object Qmodify_row;         /* modify-row */

static Object Qremove_row;         /* remove-row */

static Object Qremove_rows;        /* remove-rows */

static Object Qremove_selected_rows;  /* remove-selected-rows */

static Object Qremove_all_rows;    /* remove-all-rows */

static Object Qselect_rows;        /* select-rows */

static Object Qselected_rows;      /* selected-rows */

static Object Qdeselect_rows;      /* deselect-rows */

static Object Qrow_id;             /* row-id */

static Object Qselect_row;         /* select-row */

static Object Qdeselect_row;       /* deselect-row */

static Object Qcolumns;            /* columns */

static Object Qmodify_columns;     /* modify-columns */

static Object Qremove_column;      /* remove-column */

static Object Qremove_columns;     /* remove-columns */

static Object list_constant_7;     /* # */

static Object Qmodify_column;      /* modify-column */

static Object Qmodify_cells;       /* modify-cells */

static Object Qindex;              /* index */

/* PREPROCESS-TABULAR-VIEW-OPTION */
Object preprocess_tabular_view_option(tbv,option,evalue)
    Object tbv, option, evalue;
{
    Object temp, row_id, row_ids;

    x_note_fn_call(222,145);
    if (EQ(option,Qsort_column))
	return sort_column_value_or_stack_error(evalue);
    else if (EQ(option,Qsorting_order))
	return sorting_order_value_or_stack_error(evalue);
    else if (EQ(option,Qbackground_color) || EQ(option,Qtext_color) || 
	    EQ(option,Qgridline_color))
	return rgb_color_value_or_stack_error(evalue);
    else if (EQ(option,Qicon))
	return native_icon_handle_or_stack_error(ISVREF(tbv,(SI_Long)1L),
		evalue);
    else if (EQ(option,Qrows) || EQ(option,Qadd_rows) || EQ(option,
	    Qadd_rows_to_top))
	return preprocess_tabular_view_rows(tbv,evalue);
    else if (EQ(option,Qadd_row)) {
	temp = gensym_cons_1(preprocess_tabular_view_row(tbv,evalue),Nil);
	return VALUES_2(temp,Qadd_rows);
    }
    else if (EQ(option,Qreplace_rows) || EQ(option,Qmodify_rows))
	return preprocess_tabular_view_replace_rows(tbv,evalue);
    else if (EQ(option,Qreplace_row)) {
	temp = gensym_cons_1(preprocess_tabular_view_replace_row(tbv,
		evalue),Nil);
	return VALUES_2(temp,Qreplace_rows);
    }
    else if (EQ(option,Qmodify_row)) {
	temp = gensym_cons_1(preprocess_tabular_view_replace_row(tbv,
		evalue),Nil);
	return VALUES_2(temp,Qmodify_rows);
    }
    else if (EQ(option,Qremove_row)) {
	row_id = tabular_view_find_row_or_stack_error(tbv,evalue);
	tabular_view_delete_row(tbv,row_id);
	return VALUES_1(row_id);
    }
    else if (EQ(option,Qremove_rows)) {
	row_ids = preprocess_tabular_view_logical_ids(tbv,evalue);
	tabular_view_delete_rows(tbv,row_ids);
	return VALUES_2(row_ids,Qremove_row);
    }
    else if (EQ(option,Qremove_selected_rows)) {
	row_ids = copy_list_using_gensym_conses_1(ISVREF(tbv,(SI_Long)31L));
	tabular_view_delete_rows(tbv,row_ids);
	return VALUES_2(row_ids,Qremove_row);
    }
    else if (EQ(option,Qremove_all_rows))
	return tabular_view_delete_all_rows(tbv);
    else if (EQ(option,Qselect_rows) || EQ(option,Qselected_rows) || 
	    EQ(option,Qdeselect_rows))
	return preprocess_tabular_view_logical_ids(tbv,evalue);
    else if (EQ(option,Qlogical_id)) {
	temp = tabular_view_find_row_or_stack_error(tbv,evalue);
	return VALUES_2(temp,Qrow_id);
    }
    else if (EQ(option,Qselect_row) || EQ(option,Qdeselect_row) || 
	    EQ(option,Qposition))
	return tabular_view_find_row_or_stack_error(tbv,evalue);
    else if (EQ(option,Qcolumns) || EQ(option,Qadd_columns) || EQ(option,
	    Qmodify_columns))
	return preprocess_tabular_view_columns(tbv,evalue);
    else if (EQ(option,Qadd_column)) {
	temp = gensym_cons_1(preprocess_tabular_view_column(tbv,evalue),Nil);
	return VALUES_2(temp,Qadd_columns);
    }
    else if (EQ(option,Qremove_column)) {
	check_type_or_stack_error(2,evalue,
		Tabular_view_column_designation_type);
	return unbox_evaluation_value(1,evalue);
    }
    else if (EQ(option,Qremove_columns)) {
	check_type_or_stack_error(2,evalue,list_constant_7);
	temp = unbox_evaluation_value(1,evalue);
	return VALUES_2(temp,Qremove_column);
    }
    else if (EQ(option,Qmodify_column)) {
	temp = gensym_cons_1(preprocess_tabular_view_column(tbv,evalue),Nil);
	return VALUES_2(temp,Qmodify_columns);
    }
    else if (EQ(option,Qcells) || EQ(option,Qrow_values)) {
	temp = preprocess_tabular_view_cells(tbv,evalue);
	return VALUES_2(temp,Qcells);
    }
    else if (EQ(option,Qreplace_cells) || EQ(option,Qmodify_cells))
	return preprocess_tabular_view_cells(tbv,evalue);
    else if (EQ(option,Qcolumn) || EQ(option,Qindex)) {
	temp = unbox_evaluation_value(1,evalue);
	return VALUES_2(temp,Qcolumn);
    }
    else
	return unbox_evaluation_value(1,evalue);
}

/* PREPROCESS-TABULAR-VIEW-STRUCTURE */
Object preprocess_tabular_view_structure varargs_1(int, n)
{
    Object tbv, evalue;
    Object skip, slot_star, value_star, gensymed_symbol, held_vector, slot;
    Object attribute_value, ev, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;
    SI_Long next_index, length_1, gensymed_symbol_1;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(222,146);
    INIT_ARGS_nonrelocating();
    tbv = REQUIRED_ARG_nonrelocating();
    evalue = REQUIRED_ARG_nonrelocating();
    skip = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    slot_star = Nil;
    value_star = Nil;
    gensymed_symbol = evalue;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    slot = Nil;
    attribute_value = Nil;
    ev = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    slot = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
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
    ev = validate_item_or_evaluation_value(attribute_value,Nil,Nil);
    next_index = next_index + (SI_Long)2L;
    if ( !TRUEP(memq_function(slot,skip))) {
	result = preprocess_tabular_view_option(tbv,slot,ev);
	MVS_2(result,value_star,slot_star);
	temp = slot_star;
	if (temp);
	else
	    temp = slot;
	ab_loopvar__2 = gensym_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	ab_loopvar__2 = gensym_cons_1(value_star,Nil);
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

static Object Qmdi_child;          /* mdi-child */

static Object list_constant_8;     /* # */

static Object Qcreate;             /* create */

/* G2-UI-CREATE-TABULAR-VIEW */
Object g2_ui_create_tabular_view(title,callback,options,g2_window)
    Object title, callback, options, g2_window;
{
    Object gensym_window, container, user_data, tbv, options_star, temp;

    x_note_fn_call(222,147);
    check_type_or_stack_error(2,options,Tabular_view_options_type);
    gensym_window = tabular_views_window_or_stack_error(g2_window);
    container = estructure_slot(options,Qcontainer,Qmdi_child);
    user_data = estructure_slot(options,Quser_data,Nil);
    tbv = make_tabular_view(gensym_window);
    options_star = preprocess_tabular_view_structure(3,tbv,options,
	    list_constant_8);
    options_star = preprocess_icon_options(gensym_window,options_star);
    options_star = preprocess_container_options(gensym_window,options_star,
	    Qg2_tabular_view);
    temp = options_star;
    options_star = mutate_gensym_plist(temp,Qtitle,copy_text_string(title));
    initialize_tabular_view(tbv,callback,container,user_data,options_star);
    manage_tabular_view(tbv,Qcreate,options_star);
    reclaim_unboxed_evaluation_value(options_star);
    if ( !(FIXNUMP(title) || SYMBOLP(title) || SIMPLE_VECTOR_P(title)))
	reclaim_if_evaluation_value_1(title);
    if ( !(FIXNUMP(callback) || SYMBOLP(callback) || 
	    SIMPLE_VECTOR_P(callback)))
	reclaim_if_evaluation_value_1(callback);
    if ( !(FIXNUMP(options) || SYMBOLP(options) || SIMPLE_VECTOR_P(options)))
	reclaim_if_evaluation_value_1(options);
    return VALUES_1(ISVREF(tbv,(SI_Long)2L));
}

/* G2-UI-MANAGE-TABULAR-VIEW */
Object g2_ui_manage_tabular_view(action,handle,ev_arg,g2_window)
    Object action, handle, ev_arg, g2_window;
{
    Object gensym_window, tbv, tabular_view_action, arg_star, action_star;
    Object temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,148);
    check_type_or_stack_error(2,action,Tabular_view_action_type);
    gensym_window = tabular_views_window_or_stack_error(g2_window);
    tbv = find_native_view_or_stack_error(3,gensym_window,handle,
	    Qg2_tabular_view);
    tabular_view_action = action;
    PUSH_SPECIAL_WITH_SYMBOL(Tabular_view_action,Qtabular_view_action,tabular_view_action,
	    0);
      if (EQ(action,Qdestroy)) {
	  manage_tabular_view(tbv,action,Nil);
	  reclaim_tabular_view(tbv);
      }
      else {
	  result = preprocess_tabular_view_option(tbv,action,ev_arg);
	  MVS_2(result,arg_star,action_star);
	  temp = action_star;
	  if (temp);
	  else
	      temp = action;
	  manage_tabular_view(tbv,temp,arg_star);
	  reclaim_unboxed_evaluation_value(arg_star);
      }
      if ( !(FIXNUMP(ev_arg) || SYMBOLP(ev_arg) || SIMPLE_VECTOR_P(ev_arg)))
	  reclaim_if_evaluation_value_1(ev_arg);
      if ( !(FIXNUMP(handle) || SYMBOLP(handle) || SIMPLE_VECTOR_P(handle)))
	  result = reclaim_if_evaluation_value_1(handle);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* MANAGE-TABULAR-VIEW */
Object manage_tabular_view(tbv,action,arg)
    Object tbv, action, arg;
{
    Object gensym_window, handle, icp_output_port_qm, current_icp_port;
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
    Object result;

    x_note_fn_call(222,149);
    gensym_window = ISVREF(tbv,(SI_Long)1L);
    handle = ISVREF(tbv,(SI_Long)2L);
    if (EQ(ISVREF(gensym_window,(SI_Long)1L),Qicp)) {
	if (IFIX(Writing_icp_message_group) > (SI_Long)0L)
	    return send_icp_manage_tabular_view(gensym_window,action,
		    handle,arg);
	else {
	    icp_output_port_qm = ISVREF(gensym_window,(SI_Long)12L);
	    if (icp_output_port_qm && 
		    icp_connection_open_p(ISVREF(icp_output_port_qm,
		    (SI_Long)2L))) {
		current_icp_port = icp_output_port_qm;
		PUSH_SPECIAL_WITH_SYMBOL(Current_icp_port,Qcurrent_icp_port,current_icp_port,
			11);
		  current_icp_socket = ISVREF(Current_icp_port,(SI_Long)2L);
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icp_socket,Qcurrent_icp_socket,current_icp_socket,
			  10);
		    temp = IFIX(ISVREF(Current_icp_socket,(SI_Long)22L)) 
			    >= (SI_Long)17L ? ISVREF(Current_icp_socket,
			    (SI_Long)53L) : Nil;
		    if (temp);
		    else
			temp = EQ(ISVREF(Current_icp_socket,(SI_Long)25L),
				Qtelewindows) ? T : Nil;
		    disable_resumability = temp;
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
						    (SI_Long)0L,
						    gensymed_symbol_2);
					}
					if (icp_connection_open_p(Current_icp_socket) 
						&&  
						!TRUEP(icp_connection_being_shutdown_qm(Current_icp_socket))) 
						    {
					    temp = 
						    send_icp_manage_tabular_view(gensym_window,
						    action,handle,arg);
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
					    gensymed_symbol_5 = 
						    gensymed_symbol_3 - 
						    gensymed_symbol_4;
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L);
					    aref_new_value = 
						    gensymed_symbol_5 + 
						    DFLOAT_ISAREF_1(ISVREF(Profiling_enabled_qm,
						    (SI_Long)6L),(SI_Long)0L);
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    aref_new_value);
					    aref_arg_1 = 
						    ISVREF(Profiling_enabled_qm,
						    (SI_Long)2L);
					    aref_new_value = 
						    gensymed_symbol ? 
						    gensymed_symbol_1 + 
						    gensymed_symbol_5 + 
						    (gensymed_symbol_4 - 
						    gensymed_symbol_2) : 
						    gensymed_symbol_3;
					    DFLOAT_ISASET_1(aref_arg_1,
						    (SI_Long)0L,
						    aref_new_value);
					}
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
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return manage_tabular_view_1(gensym_window,action,handle,arg);
}

static Object Qselection_changed;  /* selection-changed */

/* TABULAR-VIEW-EVENT-NAME */
Object tabular_view_event_name(event_code,keycode)
    Object event_code, keycode;
{
    x_note_fn_call(222,150);
    if ( !(FIXNUMP(event_code) && FIXNUM_LE(FIX((SI_Long)-128L),
	    event_code) && FIXNUM_LE(event_code,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(event_code)) {
	  case 1:
	    return VALUES_1(Qselect);
	  case 2:
	    return VALUES_1(Qdeselect);
	  case 3:
	    return mouse_click_event_name(Qleft_click,keycode);
	  case 4:
	    return mouse_click_event_name(Qmiddle_click,keycode);
	  case 5:
	    return mouse_click_event_name(Qright_click,keycode);
	  case 6:
	    return VALUES_1(Qkey_pressed);
	  case 7:
	    return VALUES_1(Qselection_changed);
	  default:
	    return VALUES_1(Nil);
	}
}

static Object Qkey;                /* key */

static Object Qvalue;              /* value */

static Object list_constant_9;     /* # */

static Object Qlabel;              /* label */

/* HANDLE-TABULAR-VIEW-MESSAGE */
Object handle_tabular_view_message(mouse_pointer)
    Object mouse_pointer;
{
    Object gensym_window, event_plist, x_in_window, y_in_window, handle;
    Object tbv_qm, event_qm, keycode, row_id_qm, column_qm, label_qm;
    Object event_name_qm, user_window_x, user_window_y, keysym_qm;
    Object logical_id_qm, update_selection_qm, procedure, temp, temp_1, temp_2;
    Object temp_3, component_qm;
    Object result;

    x_note_fn_call(222,151);
    gensym_window = window_blackboard_function(mouse_pointer);
    event_plist = event_plist_blackboard_function(mouse_pointer);
    x_in_window = x_in_window_blackboard_function(mouse_pointer);
    y_in_window = y_in_window_blackboard_function(mouse_pointer);
    if (gensym_window && event_plist && x_in_window && y_in_window) {
	handle = getf(event_plist,Qwindow,FIX((SI_Long)-1L));
	tbv_qm = find_native_window(3,gensym_window,handle,Qg2_tabular_view);
	event_qm = getf(event_plist,Qevent,_);
	keycode = getf(event_plist,Qkey,FIX((SI_Long)0L));
	row_id_qm = getf(event_plist,Qrow,_);
	column_qm = getf(event_plist,Qcolumn,_);
	label_qm = getf(event_plist,Qvalue,_);
	event_name_qm = tabular_view_event_name(event_qm,keycode);
	if (tbv_qm && event_name_qm) {
	    result = gensym_window_point_to_user_window_point(gensym_window,
		    x_in_window,y_in_window);
	    MVS_2(result,user_window_x,user_window_y);
	    keysym_qm = IFIX(keycode) > (SI_Long)0L ? 
		    parseable_symbol_from_key_code(canonicalize_key_code(keycode)) 
		    : Nil;
	    logical_id_qm = tabular_view_get_logical_id(tbv_qm,row_id_qm);
	    update_selection_qm = memq_function(event_name_qm,list_constant_9);
	    if (row_id_qm && update_selection_qm)
		tabular_view_update_selected_rows(tbv_qm,event_name_qm,
			row_id_qm);
	    procedure = get_view_callback_if_any(tbv_qm);
	    if (procedure) {
		temp = label_qm ? eval_list_2(Qlabel,
			INLINE_UNSIGNED_BYTE_16_VECTOR_P(label_qm) != 
			(SI_Long)0L ? copy_text_string(label_qm) : 
			label_qm) : Nil;
		temp_1 = column_qm ? eval_list_2(Qcolumn,column_qm) : Nil;
		temp_2 = keysym_qm ? eval_list_2(Qkey,keysym_qm) : Nil;
		temp_3 = gensym_list_2(Qselected_rows,
			tabular_view_selected_rows_as_sequence(tbv_qm));
		temp_3 = nconc2(temp,nconc2(temp_1,nconc2(temp_2,
			nconc2(temp_3,gensym_list_4(Qx,user_window_x,Qy,
			user_window_y)))));
		invoke_view_callback_1(tbv_qm,procedure,event_name_qm,
			logical_id_qm,temp_3,ISVREF(tbv_qm,(SI_Long)32L));
	    }
	    component_qm = ISVREF(tbv_qm,(SI_Long)28L);
	    if (component_qm) {
		if (EQ(event_name_qm,Qselect) || EQ(event_name_qm,
			Qdeselect) || EQ(event_name_qm,Qselection_changed)) {
		    if ( 
			    !FIXNUM_LT(Icp_window_protocol_supports_tabular_view_selection_changed_events,
			    ISVREF(gensym_window,(SI_Long)11L)) || 
			    EQ(event_name_qm,Qselection_changed))
			return call_dialog_update_callback_if_any(component_qm,
				gensym_window);
		    else
			return VALUES_1(Nil);
		}
		else {
		    temp_2 = logical_id_qm;
		    if (temp_2);
		    else
			temp_2 = FIX((SI_Long)-1L);
		    temp_3 = column_qm;
		    if (temp_3);
		    else
			temp_3 = FIX((SI_Long)-1L);
		    return call_dialog_gesture_callback_if_any(component_qm,
			    keycode,temp_2,temp_3,x_in_window,y_in_window);
		}
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

static Object Qgridlines;          /* gridlines */

static Object Qsortable;           /* sortable */

static Object Qsingle_selection;   /* single-selection */

/* CREATE-TABULAR-VIEW-IN-DIALOG */
Object create_tabular_view_in_dialog(gensym_window,dialog_handle,
	    component_id,columns,rows,selected_rows,sort_column,
	    sorting_order,row_height,text_color,background_color,gridlines,
	    gridline_color,allow_sort_rows,single_selection)
    Object gensym_window, dialog_handle, component_id, columns, rows;
    Object selected_rows, sort_column, sorting_order, row_height, text_color;
    Object background_color, gridlines, gridline_color, allow_sort_rows;
    Object single_selection;
{
    Object tbv, temp, temp_1, temp_2, temp_3, temp_4, temp_5, temp_6, temp_7;
    Object temp_8, temp_9, temp_10, temp_11, plist;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,152);
    PUSH_SPECIAL_WITH_SYMBOL(Row_height,Qrow_height,row_height,0);
      tbv = make_tabular_view(gensym_window);
      temp = gensym_list_4(Qcontainer,dialog_handle,Qneighbor,component_id);
      temp_1 = columns ? gensym_list_2(Qcolumns,
	      preprocess_tabular_view_columns(tbv,columns)) : Nil;
      temp_2 = rows ? gensym_list_2(Qrows,preprocess_tabular_view_rows(tbv,
	      rows)) : Nil;
      temp_3 = selected_rows ? gensym_list_2(Qselected_rows,
	      preprocess_tabular_view_logical_ids(tbv,selected_rows)) : Nil;
      temp_4 = sort_column ? gensym_list_2(Qsort_column,
	      preprocess_tabular_view_option(tbv,Qsort_column,
	      sort_column)) : Nil;
      temp_5 = sorting_order ? gensym_list_2(Qsorting_order,
	      preprocess_tabular_view_option(tbv,Qsorting_order,
	      sorting_order)) : Nil;
      temp_6 = Row_height ? gensym_list_2(Qrow_height,
	      preprocess_tabular_view_option(tbv,Qrow_height,Row_height)) :
	       Nil;
      temp_7 = text_color ? gensym_list_2(Qtext_color,
	      preprocess_tabular_view_option(tbv,Qtext_color,text_color)) :
	       Nil;
      temp_8 = background_color ? gensym_list_2(Qbackground_color,
	      preprocess_tabular_view_option(tbv,Qbackground_color,
	      background_color)) : Nil;
      temp_9 = gridlines ? gensym_list_2(Qgridlines,
	      preprocess_tabular_view_option(tbv,Qgridlines,gridlines)) : Nil;
      temp_10 = gridline_color ? gensym_list_2(Qgridline_color,
	      preprocess_tabular_view_option(tbv,Qgridline_color,
	      gridline_color)) : Nil;
      temp_11 = allow_sort_rows ? gensym_list_2(Qsortable,
	      preprocess_tabular_view_option(tbv,Qsortable,
	      allow_sort_rows)) : Nil;
      plist = nconc2(temp,nconc2(temp_1,nconc2(temp_2,nconc2(temp_3,
	      nconc2(temp_4,nconc2(temp_5,nconc2(temp_6,nconc2(temp_7,
	      nconc2(temp_8,nconc2(temp_9,nconc2(temp_10,nconc2(temp_11,
	      single_selection ? gensym_list_2(Qsingle_selection,
	      preprocess_tabular_view_option(tbv,Qsingle_selection,
	      single_selection)) : Nil))))))))))));
      initialize_tabular_view(tbv,Nil,dialog_handle,Nil,plist);
      manage_tabular_view(tbv,Qcreate,plist);
      reclaim_unboxed_evaluation_value(plist);
      result = VALUES_1(tbv);
    POP_SPECIAL();
    return result;
}

static Object Qremove_all_selected_rows;  /* remove-all-selected-rows */

/* MANAGE-TABULAR-VIEW-IN-DIALOG */
Object manage_tabular_view_in_dialog(tbv,action,ev_arg)
    Object tbv, action, ev_arg;
{
    Object tabular_view_action, arg_star, action_star, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(222,153);
    if (EQ(action,Qremove_all_selected_rows))
	action = Qremove_selected_rows;
    tabular_view_action = action;
    PUSH_SPECIAL_WITH_SYMBOL(Tabular_view_action,Qtabular_view_action,tabular_view_action,
	    0);
      result = preprocess_tabular_view_option(tbv,action,ev_arg);
      MVS_2(result,arg_star,action_star);
      temp = action_star;
      if (temp);
      else
	  temp = action;
      manage_tabular_view(tbv,temp,arg_star);
      result = reclaim_unboxed_evaluation_value(arg_star);
    POP_SPECIAL();
    return result;
}

static Object string_constant_21;  /* "Get dialog base units is not supported on ~NF" */

static Object string_constant_22;  /* "g2-ui-get-dialog-base-units is only supported in Enterprise edition" */

/* G2-UI-GET-DIALOG-BASE-UNITS */
Object g2_ui_get_dialog_base_units(g2_window)
    Object g2_window;
{
    Object gensym_window_qm, top_of_stack, message_1;
    SI_Long hbu, vbu;

    x_note_fn_call(222,154);
    if (g2_enterprise_p()) {
	gensym_window_qm = map_to_gensym_window_or_stack_error(g2_window);
	if (twng_p(gensym_window_qm)) {
	    hbu = g2ext_get_hbu();
	    vbu = g2ext_get_vbu();
	    return VALUES_2(FIX(hbu),FIX(vbu));
	}
	else {
	    top_of_stack = Cached_top_of_stack;
	    message_1 = tformat_stack_error_text_string(2,
		    string_constant_21,g2_window);
	    return raw_stack_error_named_error(top_of_stack,message_1);
	}
    }
    else {
	top_of_stack = Cached_top_of_stack;
	message_1 = tformat_stack_error_text_string(1,string_constant_22);
	return raw_stack_error_named_error(top_of_stack,message_1);
    }
}

void views_INIT()
{
    Object temp, reclaim_structure_for_status_bar_1;
    Object clean_up_structure_for_status_bar_1;
    Object reclaim_structure_for_status_bar_pane_1, gensymed_symbol;
    Object reclaim_structure_for_logbook_view_1;
    Object clean_up_structure_for_logbook_view_1;
    Object reclaim_structure_for_tabular_view_1;
    Object clean_up_structure_for_tabular_view_1;
    Object Qg2_ui_get_dialog_base_units;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qhandle_tabular_view_message, Qnew_style_event_handler;
    Object Qmanage_tabular_view, Qg2_ui_manage_tabular_view;
    Object Qg2_ui_create_tabular_view, list_constant_54, Qtabular_view;
    Object Qclean_up_structure, Qreclaim_structure;
    Object Qoutstanding_tabular_view_count;
    Object Qtabular_view_structure_memory_usage, Qutilities2;
    Object string_constant_31, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_30, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, list_constant_135;
    Object list_constant_134, list_constant_133, list_constant_132, Qab_or;
    Object list_constant_131, list_constant_87, list_constant_88;
    Object list_constant_101, list_constant_130, list_constant_106;
    Object list_constant_115, list_constant_38, list_constant_129;
    Object list_constant_128, list_constant_127, list_constant_124;
    Object list_constant_126, list_constant_125, list_constant_123;
    Object list_constant_122, list_constant_121, list_constant_120;
    Object list_constant_107, list_constant_108, list_constant_119;
    Object list_constant_118, list_constant_57, list_constant_117;
    Object list_constant_116, list_constant_114, list_constant_113;
    Object list_constant_112, list_constant_28, list_constant_111;
    Object list_constant_110, list_constant_109, list_constant_42;
    Object list_constant_102, list_constant_58, list_constant_105;
    Object list_constant_104, list_constant_103, list_constant_100;
    Object list_constant_99, Qtext_width, Qheader_width, list_constant_98;
    Object list_constant_97, Qremove_all_columns, Qdeselect_all_rows;
    Object Qchange_sort, Qfont_size_change, Qsort_rows, list_constant_96;
    Object list_constant_95, list_constant_94, list_constant_93;
    Object list_constant_92, list_constant_91, list_constant_90;
    Object list_constant_89, list_constant_18, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_83;
    Object list_constant_82, list_constant_81, list_constant_80;
    Object list_constant_79, list_constant_78, list_constant_77;
    Object list_constant_76, list_constant_75, list_constant_74;
    Object list_constant_73, list_constant_72, list_constant_71;
    Object list_constant_70, list_constant_69, list_constant_68;
    Object list_constant_67, list_constant_66, list_constant_65;
    Object list_constant_64, list_constant_63, list_constant_62;
    Object list_constant_61, list_constant_60, list_constant_59;
    Object list_constant_17, list_constant_56, list_constant_32, Qmin_width;
    Object list_constant_55, Qy_scroll_position, Qx_scroll_position;
    Object Qmaximizeable, Qminimizeable, Qresizeable, Qcloseable, Qdraggable;
    Object Qautohideable, Qfloatable, list_constant_52, Qtop, Qleft;
    Object list_constant_53, list_constant_51, Qdatum, list_constant_50;
    Object Qwithin, Qbottom, list_constant_49, Qclosed, Qfloating, Qdocked;
    Object Qmaximized, Qminimized, Qnormal, Qvisible_caption, list_constant_48;
    Object Qhandle_logbook_view_event, Qlogbook_view;
    Object Qoutstanding_logbook_view_count;
    Object Qlogbook_view_structure_memory_usage, string_constant_29;
    Object string_constant_28, Qhandle_status_bar_message;
    Object Qg2_ui_manage_status_bar, Qset_text, Qshow, Qmanage_status_bar;
    Object Qstatus_bar_pane, Qoutstanding_status_bar_pane_count;
    Object Qstatus_bar_pane_structure_memory_usage, string_constant_27;
    Object string_constant_26, Qstatus_bar, Qoutstanding_status_bar_count;
    Object Qstatus_bar_structure_memory_usage, string_constant_25;
    Object string_constant_24, list_constant_47, list_constant_46;
    Object list_constant_45, list_constant_44, list_constant_15;
    Object list_constant_43, list_constant_41, list_constant_40;
    Object list_constant_39, list_constant_37, list_constant_36;
    Object list_constant_23, Qborders, Qenabled, Qtooltip, list_constant_35;
    Object Qcenter, list_constant_34, list_constant_33, Qtruth_value;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object Qitem_or_datum, list_constant_27, list_constant_22;
    Object list_constant_26, list_constant_25, list_constant_24;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object list_constant_16, list_constant_14, list_constant_11;
    Object list_constant_13, Qprocedure, Qab_class, list_constant_12;
    Object Qmutate_item_or_name_hash_tree_for_hash_skip_list_entry;
    Object Qout_item_or_name_hash_hash_vector_43_vectors;
    Object Qitem_or_name_hash_hash_vector_43_vector_memory_usage;
    Object string_constant_23, list_constant_10, Qg2_window;

    x_note_fn_call(222,155);
    SET_PACKAGE("AB");
    string_constant = STATIC_STRING("No ~a found for handle ~s.");
    AB_package = STATIC_PACKAGE("AB");
    Qg2_workspace_view = STATIC_SYMBOL("G2-WORKSPACE-VIEW",AB_package);
    string_constant_1 = STATIC_STRING("Workspace View");
    Qg2_tree_view = STATIC_SYMBOL("G2-TREE-VIEW",AB_package);
    string_constant_2 = STATIC_STRING("Tree View");
    Qg2_html_view = STATIC_SYMBOL("G2-HTML-VIEW",AB_package);
    string_constant_3 = STATIC_STRING("HTML View");
    Qg2_shortcut_bar = STATIC_SYMBOL("G2-SHORTCUT-BAR",AB_package);
    string_constant_4 = STATIC_STRING("Shortcut Bar");
    Qg2_chart_view = STATIC_SYMBOL("G2-CHART-VIEW",AB_package);
    string_constant_5 = STATIC_STRING("Chart View");
    Qg2_dialog_view = STATIC_SYMBOL("G2-DIALOG-VIEW",AB_package);
    string_constant_6 = STATIC_STRING("Dialog View");
    Qg2_property_grid = STATIC_SYMBOL("G2-PROPERTY-GRID",AB_package);
    string_constant_7 = STATIC_STRING("Property Grid");
    Qg2_status_bar = STATIC_SYMBOL("G2-STATUS-BAR",AB_package);
    string_constant_8 = STATIC_STRING("Status Bar");
    Qg2_tabular_view = STATIC_SYMBOL("G2-TABULAR-VIEW",AB_package);
    string_constant_9 = STATIC_STRING("Tabular View");
    string_constant_10 = STATIC_STRING("Native View");
    string_constant_11 = STATIC_STRING("View");
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qbackground = STATIC_SYMBOL("BACKGROUND",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qcolor_value_vector_index_and_intensity = 
	    STATIC_SYMBOL("COLOR-VALUE-VECTOR-INDEX-AND-INTENSITY",AB_package);
    string_constant_12 = STATIC_STRING("~A is not a valid color name.");
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qg2_window = STATIC_SYMBOL("G2-WINDOW",AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qab_class,Qg2_window);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_11 = STATIC_CONS(Qab_structure,Qnil);
    list_constant = STATIC_LIST((SI_Long)6L,Qsymbol,list_constant_10,
	    Qinteger,Qdatum,list_constant_11,Qdatum);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qavailable_item_or_name_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_item_or_name_hash_hash_vector_43_vectors,
	    Available_item_or_name_hash_hash_vector_43_vectors);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qavailable_item_or_name_hash_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_item_or_name_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_item_or_name_hash_hash_vector_43_vectors,
	    Count_of_item_or_name_hash_hash_vector_43_vectors);
    record_system_variable(Qcount_of_item_or_name_hash_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Available_item_or_name_hash_hash_vector_43_vectors_vector == UNBOUND)
	Available_item_or_name_hash_hash_vector_43_vectors_vector = 
		make_thread_array(Nil);
    Qout_item_or_name_hash_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qitem_or_name_hash_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("ITEM-OR-NAME-HASH-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_23 = STATIC_STRING("1q83-bCy83*9y83-P+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_item_or_name_hash_hash_vector_43_vectors);
    push_optimized_constant(Qitem_or_name_hash_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_23));
    SET_SYMBOL_FUNCTION(Qitem_or_name_hash_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(item_or_name_hash_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_item_or_name_hash_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_item_or_name_hash_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qvector_pool = STATIC_SYMBOL("VECTOR-POOL",AB_package);
    Qsentinel_node = STATIC_SYMBOL("SENTINEL-NODE",AB_package);
    Qhead = STATIC_SYMBOL("HEAD",AB_package);
    Qtail = STATIC_SYMBOL("TAIL",AB_package);
    Qmutate_item_or_name_hash_tree_for_hash_skip_list_entry = 
	    STATIC_SYMBOL("MUTATE-ITEM-OR-NAME-HASH-TREE-FOR-HASH-SKIP-LIST-ENTRY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmutate_item_or_name_hash_tree_for_hash_skip_list_entry,
	    STATIC_FUNCTION(mutate_item_or_name_hash_tree_for_hash_skip_list_entry,
	    NIL,FALSE,3,3));
    Fp_mutate_item_or_name_hash_tree_for_hash_skip_list_entry = 
	    SYMBOL_FUNCTION(Qmutate_item_or_name_hash_tree_for_hash_skip_list_entry);
    Qequalw = STATIC_SYMBOL("EQUALW",AB_package);
    Qitem_or_name_hash_tree_for_hash = 
	    STATIC_SYMBOL("ITEM-OR-NAME-HASH-TREE-FOR-HASH",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    Qshow = STATIC_SYMBOL("SHOW",AB_package);
    Qset_text = STATIC_SYMBOL("SET-TEXT",AB_package);
    Qset_min_height = STATIC_SYMBOL("SET-MIN-HEIGHT",AB_package);
    Qset_callback = STATIC_SYMBOL("SET-CALLBACK",AB_package);
    Qconfigure = STATIC_SYMBOL("CONFIGURE",AB_package);
    Qadd_pane = STATIC_SYMBOL("ADD-PANE",AB_package);
    Qmodify_pane = STATIC_SYMBOL("MODIFY-PANE",AB_package);
    Qremove_pane = STATIC_SYMBOL("REMOVE-PANE",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)10L,Qmember,Qhide,Qshow,
	    Qset_text,Qset_min_height,Qset_callback,Qconfigure,Qadd_pane,
	    Qmodify_pane,Qremove_pane);
    Status_bar_action_type = list_constant_12;
    Qvisible = STATIC_SYMBOL("VISIBLE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qvisible,Qtruth_value);
    Qcallback = STATIC_SYMBOL("CALLBACK",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qab_class,Qprocedure);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_or,Qsymbol,list_constant_13);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qcallback,list_constant_4);
    Quser_data = STATIC_SYMBOL("USER-DATA",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_17 = STATIC_LIST((SI_Long)2L,Quser_data,Qitem_or_datum);
    Qmin_height = STATIC_SYMBOL("MIN-HEIGHT",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qmin_height,Qinteger);
    Qpanes = STATIC_SYMBOL("PANES",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_11);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qpanes,list_constant_14);
    list_constant_20 = STATIC_LIST((SI_Long)5L,list_constant_15,
	    list_constant_16,list_constant_17,list_constant_18,
	    list_constant_19);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_20);
    Status_bar_configure_type = list_constant_21;
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qid = STATIC_SYMBOL("ID",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)4L,Qab_or,Qinteger,Qsymbol,Qtext);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qid,list_constant_22);
    list_constant_24 = STATIC_CONS(list_constant_23,Qnil);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_24);
    list_constant_26 = STATIC_LIST((SI_Long)5L,Qab_or,Qinteger,Qsymbol,
	    Qtext,list_constant_25);
    Status_bar_remove_pane_type = list_constant_26;
    list_constant_27 = STATIC_CONS(list_constant_22,Qnil);
    list_constant_36 = STATIC_CONS(Qposition,list_constant_27);
    list_constant_28 = STATIC_CONS(Qtext,Qnil);
    list_constant_37 = STATIC_CONS(Qtext,list_constant_28);
    Qicon = STATIC_SYMBOL("ICON",AB_package);
    list_constant_29 = STATIC_CONS(Qitem_or_datum,Qnil);
    list_constant_38 = STATIC_CONS(Qicon,list_constant_29);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qfit = STATIC_SYMBOL("FIT",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qmember,Qfit);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_30);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qwidth,list_constant_31);
    Qbackground_color = STATIC_SYMBOL("BACKGROUND-COLOR",AB_package);
    list_constant_32 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_33 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qsymbol,
	    list_constant_32);
    list_constant_34 = STATIC_CONS(list_constant_33,Qnil);
    list_constant_40 = STATIC_CONS(Qbackground_color,list_constant_34);
    Qforeground_color = STATIC_SYMBOL("FOREGROUND-COLOR",AB_package);
    list_constant_41 = STATIC_CONS(Qforeground_color,list_constant_34);
    Qalignment = STATIC_SYMBOL("ALIGNMENT",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qcenter = STATIC_SYMBOL("CENTER",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)4L,Qmember,Qleft,Qcenter,Qright);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qalignment,list_constant_35);
    Qtooltip = STATIC_SYMBOL("TOOLTIP",AB_package);
    list_constant_43 = STATIC_CONS(Qtooltip,list_constant_28);
    Qenabled = STATIC_SYMBOL("ENABLED",AB_package);
    list_constant_44 = STATIC_CONS(Qenabled,list_constant_32);
    Qborders = STATIC_SYMBOL("BORDERS",AB_package);
    list_constant_45 = STATIC_CONS(Qborders,list_constant_32);
    list_constant_46 = STATIC_LIST((SI_Long)13L,list_constant_23,
	    list_constant_36,list_constant_37,list_constant_38,
	    list_constant_39,list_constant_40,list_constant_41,
	    list_constant_42,list_constant_43,list_constant_15,
	    list_constant_44,list_constant_45,list_constant_17);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_46);
    Status_bar_pane_options_type = list_constant_47;
    Qg2_defstruct_structure_name_status_bar_g2_struct = 
	    STATIC_SYMBOL("STATUS-BAR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstatus_bar = STATIC_SYMBOL("STATUS-BAR",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_status_bar_g2_struct,
	    Qstatus_bar,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qstatus_bar,
	    Qg2_defstruct_structure_name_status_bar_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_status_bar == UNBOUND)
	The_type_description_of_status_bar = Nil;
    string_constant_24 = 
	    STATIC_STRING("43Dy8m83nQy1p83nQy83=Ly83*vy8n8k1l83=Ly0000001m1m8x83=Ly1m83My83-B7yk3Syk0k0");
    temp = The_type_description_of_status_bar;
    The_type_description_of_status_bar = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_24));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_status_bar_g2_struct,
	    The_type_description_of_status_bar,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qstatus_bar,The_type_description_of_status_bar,
	    Qtype_description_of_type);
    Qoutstanding_status_bar_count = 
	    STATIC_SYMBOL("OUTSTANDING-STATUS-BAR-COUNT",AB_package);
    Qstatus_bar_structure_memory_usage = 
	    STATIC_SYMBOL("STATUS-BAR-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_25 = STATIC_STRING("1q83nQy8s83-quy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_status_bar_count);
    push_optimized_constant(Qstatus_bar_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_25));
    Qchain_of_available_status_bars = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STATUS-BARS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_status_bars,
	    Chain_of_available_status_bars);
    record_system_variable(Qchain_of_available_status_bars,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qstatus_bar_count = STATIC_SYMBOL("STATUS-BAR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstatus_bar_count,Status_bar_count);
    record_system_variable(Qstatus_bar_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_status_bars_vector == UNBOUND)
	Chain_of_available_status_bars_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qstatus_bar_structure_memory_usage,
	    STATIC_FUNCTION(status_bar_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_status_bar_count,
	    STATIC_FUNCTION(outstanding_status_bar_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_status_bar_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_status_bar,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qstatus_bar,
	    reclaim_structure_for_status_bar_1);
    Qdestroy = STATIC_SYMBOL("DESTROY",AB_package);
    Qclean_up_structure = STATIC_SYMBOL("CLEAN-UP-STRUCTURE",AB_package);
    clean_up_structure_for_status_bar_1 = 
	    STATIC_FUNCTION(clean_up_structure_for_status_bar,NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_structure,Qstatus_bar,
	    clean_up_structure_for_status_bar_1);
    Qg2_defstruct_structure_name_status_bar_pane_g2_struct = 
	    STATIC_SYMBOL("STATUS-BAR-PANE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstatus_bar_pane = STATIC_SYMBOL("STATUS-BAR-PANE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_status_bar_pane_g2_struct,
	    Qstatus_bar_pane,Qab_name_of_unique_structure_type);
    mutate_global_property(Qstatus_bar_pane,
	    Qg2_defstruct_structure_name_status_bar_pane_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_status_bar_pane == UNBOUND)
	The_type_description_of_status_bar_pane = Nil;
    string_constant_26 = 
	    STATIC_STRING("43Dy8m83nRy1n83nRy8n8k1l8n0000001m1m83My83-B8y1n8y83-6+y1n83-Dhy83-Diy83-Djykok0k0");
    temp = The_type_description_of_status_bar_pane;
    The_type_description_of_status_bar_pane = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_26));
    mutate_global_property(Qg2_defstruct_structure_name_status_bar_pane_g2_struct,
	    The_type_description_of_status_bar_pane,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qstatus_bar_pane,
	    The_type_description_of_status_bar_pane,Qtype_description_of_type);
    Qoutstanding_status_bar_pane_count = 
	    STATIC_SYMBOL("OUTSTANDING-STATUS-BAR-PANE-COUNT",AB_package);
    Qstatus_bar_pane_structure_memory_usage = 
	    STATIC_SYMBOL("STATUS-BAR-PANE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_27 = STATIC_STRING("1q83nRy8s83-qvy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_status_bar_pane_count);
    push_optimized_constant(Qstatus_bar_pane_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_27));
    Qchain_of_available_status_bar_panes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STATUS-BAR-PANES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_status_bar_panes,
	    Chain_of_available_status_bar_panes);
    record_system_variable(Qchain_of_available_status_bar_panes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qstatus_bar_pane_count = STATIC_SYMBOL("STATUS-BAR-PANE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstatus_bar_pane_count,Status_bar_pane_count);
    record_system_variable(Qstatus_bar_pane_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_status_bar_panes_vector == UNBOUND)
	Chain_of_available_status_bar_panes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qstatus_bar_pane_structure_memory_usage,
	    STATIC_FUNCTION(status_bar_pane_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_status_bar_pane_count,
	    STATIC_FUNCTION(outstanding_status_bar_pane_count,NIL,FALSE,0,0));
    reclaim_structure_for_status_bar_pane_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_status_bar_pane,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qstatus_bar_pane,
	    reclaim_structure_for_status_bar_pane_1);
    Qg2_documentation_line = STATIC_SYMBOL("G2-DOCUMENTATION-LINE",AB_package);
    Qg2_security_icon = STATIC_SYMBOL("G2-SECURITY-ICON",AB_package);
    string_constant_13 = STATIC_STRING("Status-bar pane ~NV not found.");
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qreset = STATIC_SYMBOL("RESET",AB_package);
    Qicp = STATIC_SYMBOL("ICP",AB_package);
    Qtelewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    Qmanage_status_bar = STATIC_SYMBOL("MANAGE-STATUS-BAR",AB_package);
    SET_SYMBOL_FUNCTION(Qmanage_status_bar,
	    STATIC_FUNCTION(manage_status_bar,NIL,FALSE,3,3));
    list_constant_1 = STATIC_CONS(Quser_data,Qnil);
    string_constant_14 = 
	    STATIC_STRING("Maximum of ~D status-bar panes exceeded.");
    Qg2_ui_manage_status_bar = STATIC_SYMBOL("G2-UI-MANAGE-STATUS-BAR",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_manage_status_bar,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_15 = STATIC_STRING("Status bars are not supported on ~NF");
    string_constant_16 = 
	    STATIC_STRING("Modifying the status bar is not supported on ~NF");
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qhide,Qshow,Qset_text);
    string_constant_17 = 
	    STATIC_STRING("The status-bar action ~A is not supported on ~NF");
    list_constant_3 = STATIC_LIST((SI_Long)2L,Quser_data,Qpanes);
    SET_SYMBOL_FUNCTION(Qg2_ui_manage_status_bar,
	    STATIC_FUNCTION(g2_ui_manage_status_bar,NIL,FALSE,3,3));
    Qleft_click = STATIC_SYMBOL("LEFT-CLICK",AB_package);
    Qmiddle_click = STATIC_SYMBOL("MIDDLE-CLICK",AB_package);
    Qright_click = STATIC_SYMBOL("RIGHT-CLICK",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qhandle_status_bar_message = STATIC_SYMBOL("HANDLE-STATUS-BAR-MESSAGE",
	    AB_package);
    Qnew_style_event_handler = STATIC_SYMBOL("NEW-STYLE-EVENT-HANDLER",
	    AB_package);
    mutate_global_property(Qhandle_status_bar_message,
	    Qhandle_status_bar_message,Qnew_style_event_handler);
    Qbits = STATIC_SYMBOL("BITS",AB_package);
    Qevent = STATIC_SYMBOL("EVENT",AB_package);
    Qpane = STATIC_SYMBOL("PANE",AB_package);
    Qx = STATIC_SYMBOL("X",AB_package);
    Qy = STATIC_SYMBOL("Y",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_status_bar_message,
	    STATIC_FUNCTION(handle_status_bar_message,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_logbook_view_g2_struct = 
	    STATIC_SYMBOL("LOGBOOK-VIEW-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qlogbook_view = STATIC_SYMBOL("LOGBOOK-VIEW",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_logbook_view_g2_struct,
	    Qlogbook_view,Qab_name_of_unique_structure_type);
    mutate_global_property(Qlogbook_view,
	    Qg2_defstruct_structure_name_logbook_view_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_logbook_view == UNBOUND)
	The_type_description_of_logbook_view = Nil;
    string_constant_28 = 
	    STATIC_STRING("43Dy8m83kay1p83kay83=Ly83*vy8n8k1l83=Ly0000001n1m8x83=Ly1m8y83-4my1m83My83-Afyk3Qyk0k0");
    temp = The_type_description_of_logbook_view;
    The_type_description_of_logbook_view = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_28));
    mutate_global_property(Qg2_defstruct_structure_name_logbook_view_g2_struct,
	    The_type_description_of_logbook_view,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qlogbook_view,
	    The_type_description_of_logbook_view,Qtype_description_of_type);
    Qoutstanding_logbook_view_count = 
	    STATIC_SYMBOL("OUTSTANDING-LOGBOOK-VIEW-COUNT",AB_package);
    Qlogbook_view_structure_memory_usage = 
	    STATIC_SYMBOL("LOGBOOK-VIEW-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_29 = STATIC_STRING("1q83kay8s83-dDy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_logbook_view_count);
    push_optimized_constant(Qlogbook_view_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_29));
    Qchain_of_available_logbook_views = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LOGBOOK-VIEWS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_logbook_views,
	    Chain_of_available_logbook_views);
    record_system_variable(Qchain_of_available_logbook_views,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qlogbook_view_count = STATIC_SYMBOL("LOGBOOK-VIEW-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlogbook_view_count,Logbook_view_count);
    record_system_variable(Qlogbook_view_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_logbook_views_vector == UNBOUND)
	Chain_of_available_logbook_views_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qlogbook_view_structure_memory_usage,
	    STATIC_FUNCTION(logbook_view_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_logbook_view_count,
	    STATIC_FUNCTION(outstanding_logbook_view_count,NIL,FALSE,0,0));
    reclaim_structure_for_logbook_view_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_logbook_view,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qlogbook_view,
	    reclaim_structure_for_logbook_view_1);
    Qg2_output_view = STATIC_SYMBOL("G2-OUTPUT-VIEW",AB_package);
    clean_up_structure_for_logbook_view_1 = 
	    STATIC_FUNCTION(clean_up_structure_for_logbook_view,NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_structure,Qlogbook_view,
	    clean_up_structure_for_logbook_view_1);
    Qappend_message = STATIC_SYMBOL("APPEND-MESSAGE",AB_package);
    Qdelete_message = STATIC_SYMBOL("DELETE-MESSAGE",AB_package);
    Qnormal_message = STATIC_SYMBOL("NORMAL-MESSAGE",AB_package);
    Qfade_message = STATIC_SYMBOL("FADE-MESSAGE",AB_package);
    Qhighlight_message = STATIC_SYMBOL("HIGHLIGHT-MESSAGE",AB_package);
    Qset_line_wrap = STATIC_SYMBOL("SET-LINE-WRAP",AB_package);
    Qset_include_date_in_title = STATIC_SYMBOL("SET-INCLUDE-DATE-IN-TITLE",
	    AB_package);
    string_constant_18 = STATIC_STRING("Unknown action ~a on logbook views.");
    Qselect = STATIC_SYMBOL("SELECT",AB_package);
    Qkey_pressed = STATIC_SYMBOL("KEY-PRESSED",AB_package);
    Qhandle_logbook_view_event = STATIC_SYMBOL("HANDLE-LOGBOOK-VIEW-EVENT",
	    AB_package);
    mutate_global_property(Qhandle_logbook_view_event,
	    Qhandle_logbook_view_event,Qnew_style_event_handler);
    Qwindow = STATIC_SYMBOL("WINDOW",AB_package);
    Qmsg = STATIC_SYMBOL("MSG",AB_package);
    Qno_user_data = STATIC_SYMBOL("NO-USER-DATA",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_logbook_view_event,
	    STATIC_FUNCTION(handle_logbook_view_event,NIL,FALSE,1,1));
    Qtext_box = STATIC_SYMBOL("TEXT-BOX",AB_package);
    Qtitle = STATIC_SYMBOL("TITLE",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    Qcontainer = STATIC_SYMBOL("CONTAINER",AB_package);
    Qclose_action = STATIC_SYMBOL("CLOSE-ACTION",AB_package);
    Qdock = STATIC_SYMBOL("DOCK",AB_package);
    Qneighbor = STATIC_SYMBOL("NEIGHBOR",AB_package);
    Qstate = STATIC_SYMBOL("STATE",AB_package);
    Qautohidden = STATIC_SYMBOL("AUTOHIDDEN",AB_package);
    Qhidden = STATIC_SYMBOL("HIDDEN",AB_package);
    Qmessage_board = STATIC_SYMBOL("MESSAGE-BOARD",AB_package);
    Qlogbook = STATIC_SYMBOL("LOGBOOK",AB_package);
    Qautoshown = STATIC_SYMBOL("AUTOSHOWN",AB_package);
    Qshow_operator_logbook_in_this_window_qm = 
	    STATIC_SYMBOL("SHOW-OPERATOR-LOGBOOK-IN-THIS-WINDOW\?",AB_package);
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_48,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)76L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)57344L);
    Qprefer_native = STATIC_SYMBOL("PREFER-NATIVE",AB_package);
    Qinclude_date = STATIC_SYMBOL("INCLUDE-DATE",AB_package);
    Qfixnum_lessp = STATIC_SYMBOL("FIXNUM-LESSP",AB_package);
    SET_SYMBOL_FUNCTION(Qfixnum_lessp,STATIC_FUNCTION(fixnum_lessp,NIL,
	    FALSE,2,2));
    Qmessage_serial_number_function = 
	    STATIC_SYMBOL("MESSAGE-SERIAL-NUMBER-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qmessage_serial_number_function,
	    STATIC_FUNCTION(message_serial_number_function,NIL,FALSE,1,1));
    array_constant_1 = STATIC_ARRAY(list_constant_48,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    if (Tabular_view_action == UNBOUND)
	Tabular_view_action = Nil;
    list_constant_65 = STATIC_CONS(Qtitle,list_constant_28);
    Qvisible_caption = STATIC_SYMBOL("VISIBLE-CAPTION",AB_package);
    list_constant_66 = STATIC_CONS(Qvisible_caption,list_constant_32);
    Qnormal = STATIC_SYMBOL("NORMAL",AB_package);
    Qminimized = STATIC_SYMBOL("MINIMIZED",AB_package);
    Qmaximized = STATIC_SYMBOL("MAXIMIZED",AB_package);
    Qdocked = STATIC_SYMBOL("DOCKED",AB_package);
    Qfloating = STATIC_SYMBOL("FLOATING",AB_package);
    Qclosed = STATIC_SYMBOL("CLOSED",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)9L,Qmember,Qnormal,Qminimized,
	    Qmaximized,Qautohidden,Qhidden,Qdocked,Qfloating,Qclosed);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qstate,list_constant_49);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qwithin = STATIC_SYMBOL("WITHIN",AB_package);
    list_constant_50 = STATIC_LIST((SI_Long)8L,Qmember,Qleft,Qtop,Qright,
	    Qbottom,Qfloat,Qwithin,Qnone);
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qdock,list_constant_50);
    Qmdi_child = STATIC_SYMBOL("MDI-CHILD",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)3L,Qmember,Qpane,Qmdi_child);
    list_constant_52 = STATIC_CONS(Qdatum,Qnil);
    list_constant_53 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_51,list_constant_52);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qcontainer,list_constant_53);
    list_constant_54 = STATIC_CONS(Qinteger,Qnil);
    list_constant_70 = STATIC_CONS(Qleft,list_constant_54);
    list_constant_71 = STATIC_CONS(Qtop,list_constant_54);
    list_constant_72 = STATIC_CONS(Qwidth,list_constant_54);
    list_constant_73 = STATIC_CONS(Qheight,list_constant_54);
    list_constant_74 = STATIC_CONS(Qneighbor,list_constant_52);
    Qfloatable = STATIC_SYMBOL("FLOATABLE",AB_package);
    list_constant_75 = STATIC_CONS(Qfloatable,list_constant_32);
    Qautohideable = STATIC_SYMBOL("AUTOHIDEABLE",AB_package);
    list_constant_76 = STATIC_CONS(Qautohideable,list_constant_32);
    Qdraggable = STATIC_SYMBOL("DRAGGABLE",AB_package);
    list_constant_77 = STATIC_CONS(Qdraggable,list_constant_32);
    Qcloseable = STATIC_SYMBOL("CLOSEABLE",AB_package);
    list_constant_78 = STATIC_CONS(Qcloseable,list_constant_32);
    Qresizeable = STATIC_SYMBOL("RESIZEABLE",AB_package);
    list_constant_79 = STATIC_CONS(Qresizeable,list_constant_32);
    Qminimizeable = STATIC_SYMBOL("MINIMIZEABLE",AB_package);
    list_constant_80 = STATIC_CONS(Qminimizeable,list_constant_32);
    Qmaximizeable = STATIC_SYMBOL("MAXIMIZEABLE",AB_package);
    list_constant_81 = STATIC_CONS(Qmaximizeable,list_constant_32);
    Qx_scroll_position = STATIC_SYMBOL("X-SCROLL-POSITION",AB_package);
    list_constant_82 = STATIC_CONS(Qx_scroll_position,list_constant_54);
    Qy_scroll_position = STATIC_SYMBOL("Y-SCROLL-POSITION",AB_package);
    list_constant_83 = STATIC_CONS(Qy_scroll_position,list_constant_54);
    list_constant_55 = STATIC_LIST((SI_Long)3L,Qmember,Qdestroy,Qhide);
    list_constant_84 = STATIC_LIST((SI_Long)2L,Qclose_action,list_constant_55);
    list_constant_56 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_85 = STATIC_CONS(Qcallback,list_constant_56);
    Qmin_width = STATIC_SYMBOL("MIN-WIDTH",AB_package);
    list_constant_86 = STATIC_CONS(Qmin_width,list_constant_54);
    list_constant_87 = STATIC_CONS(Qbackground_color,list_constant_56);
    Qtext_color = STATIC_SYMBOL("TEXT-COLOR",AB_package);
    list_constant_88 = STATIC_CONS(Qtext_color,list_constant_56);
    Qgridlines = STATIC_SYMBOL("GRIDLINES",AB_package);
    list_constant_89 = STATIC_CONS(Qgridlines,list_constant_32);
    Qgridline_color = STATIC_SYMBOL("GRIDLINE-COLOR",AB_package);
    list_constant_90 = STATIC_CONS(Qgridline_color,list_constant_56);
    Qsortable = STATIC_SYMBOL("SORTABLE",AB_package);
    list_constant_91 = STATIC_CONS(Qsortable,list_constant_32);
    Qrow_height = STATIC_SYMBOL("ROW-HEIGHT",AB_package);
    list_constant_92 = STATIC_CONS(Qrow_height,list_constant_54);
    Qsingle_selection = STATIC_SYMBOL("SINGLE-SELECTION",AB_package);
    list_constant_93 = STATIC_CONS(Qsingle_selection,list_constant_32);
    Qcolumns = STATIC_SYMBOL("COLUMNS",AB_package);
    list_constant_57 = STATIC_CONS(Qsequence,Qnil);
    list_constant_58 = STATIC_CONS(list_constant_57,Qnil);
    list_constant_59 = STATIC_CONS(Qcolumns,list_constant_58);
    Qrows = STATIC_SYMBOL("ROWS",AB_package);
    list_constant_60 = STATIC_CONS(Qrows,list_constant_58);
    Qselected_rows = STATIC_SYMBOL("SELECTED-ROWS",AB_package);
    list_constant_61 = STATIC_CONS(Qselected_rows,list_constant_58);
    Qsort_column = STATIC_SYMBOL("SORT-COLUMN",AB_package);
    list_constant_62 = STATIC_CONS(Qsort_column,list_constant_54);
    Qsorting_order = STATIC_SYMBOL("SORTING-ORDER",AB_package);
    list_constant_63 = STATIC_CONS(Qsorting_order,list_constant_56);
    list_constant_64 = STATIC_CONS(list_constant_17,Qnil);
    list_constant_94 = STATIC_LIST_STAR((SI_Long)6L,list_constant_59,
	    list_constant_60,list_constant_61,list_constant_62,
	    list_constant_63,list_constant_64);
    list_constant_95 = STATIC_LIST_STAR((SI_Long)32L,list_constant_65,
	    list_constant_66,list_constant_38,list_constant_67,
	    list_constant_68,list_constant_69,list_constant_70,
	    list_constant_71,list_constant_72,list_constant_73,
	    list_constant_74,list_constant_75,list_constant_76,
	    list_constant_77,list_constant_78,list_constant_79,
	    list_constant_80,list_constant_81,list_constant_82,
	    list_constant_83,list_constant_84,list_constant_85,
	    list_constant_86,list_constant_18,list_constant_87,
	    list_constant_88,list_constant_89,list_constant_90,
	    list_constant_91,list_constant_92,list_constant_93,
	    list_constant_94);
    list_constant_96 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_95);
    Tabular_view_options_type = list_constant_96;
    Qadd_row = STATIC_SYMBOL("ADD-ROW",AB_package);
    Qadd_rows = STATIC_SYMBOL("ADD-ROWS",AB_package);
    Qmodify_row = STATIC_SYMBOL("MODIFY-ROW",AB_package);
    Qmodify_rows = STATIC_SYMBOL("MODIFY-ROWS",AB_package);
    Qreplace_row = STATIC_SYMBOL("REPLACE-ROW",AB_package);
    Qreplace_rows = STATIC_SYMBOL("REPLACE-ROWS",AB_package);
    Qreplace_cells = STATIC_SYMBOL("REPLACE-CELLS",AB_package);
    Qmodify_cells = STATIC_SYMBOL("MODIFY-CELLS",AB_package);
    Qselect_row = STATIC_SYMBOL("SELECT-ROW",AB_package);
    Qdeselect_row = STATIC_SYMBOL("DESELECT-ROW",AB_package);
    Qdeselect_all_rows = STATIC_SYMBOL("DESELECT-ALL-ROWS",AB_package);
    Qremove_row = STATIC_SYMBOL("REMOVE-ROW",AB_package);
    Qremove_rows = STATIC_SYMBOL("REMOVE-ROWS",AB_package);
    Qremove_all_rows = STATIC_SYMBOL("REMOVE-ALL-ROWS",AB_package);
    Qremove_selected_rows = STATIC_SYMBOL("REMOVE-SELECTED-ROWS",AB_package);
    Qadd_column = STATIC_SYMBOL("ADD-COLUMN",AB_package);
    Qadd_columns = STATIC_SYMBOL("ADD-COLUMNS",AB_package);
    Qmodify_column = STATIC_SYMBOL("MODIFY-COLUMN",AB_package);
    Qmodify_columns = STATIC_SYMBOL("MODIFY-COLUMNS",AB_package);
    Qremove_column = STATIC_SYMBOL("REMOVE-COLUMN",AB_package);
    Qremove_columns = STATIC_SYMBOL("REMOVE-COLUMNS",AB_package);
    Qremove_all_columns = STATIC_SYMBOL("REMOVE-ALL-COLUMNS",AB_package);
    Qsort_rows = STATIC_SYMBOL("SORT-ROWS",AB_package);
    Qadd_rows_to_top = STATIC_SYMBOL("ADD-ROWS-TO-TOP",AB_package);
    Qfont_size_change = STATIC_SYMBOL("FONT-SIZE-CHANGE",AB_package);
    Qchange_sort = STATIC_SYMBOL("CHANGE-SORT",AB_package);
    list_constant_97 = STATIC_LIST((SI_Long)7L,Qbackground_color,
	    Qtext_color,Qrow_height,Qsort_rows,Qadd_rows_to_top,
	    Qfont_size_change,Qchange_sort);
    list_constant_98 = STATIC_LIST_STAR((SI_Long)32L,Qmember,Qdestroy,
	    Qadd_row,Qadd_rows,Qrows,Qmodify_row,Qmodify_rows,Qreplace_row,
	    Qreplace_rows,Qreplace_cells,Qmodify_cells,Qselect_row,
	    Qdeselect_row,Qselected_rows,Qdeselect_all_rows,Qremove_row,
	    Qremove_rows,Qremove_all_rows,Qremove_selected_rows,
	    Qadd_column,Qadd_columns,Qcolumns,Qmodify_column,
	    Qmodify_columns,Qremove_column,Qremove_columns,
	    Qremove_all_columns,Qgridlines,Qgridline_color,Qsortable,
	    Qsingle_selection,list_constant_97);
    Tabular_view_action_type = list_constant_98;
    Tabular_view_column_designation_type = Qinteger;
    Qtext_value = STATIC_SYMBOL("TEXT-VALUE",AB_package);
    list_constant_101 = STATIC_CONS(Qtext_value,list_constant_28);
    Qheader_width = STATIC_SYMBOL("HEADER-WIDTH",AB_package);
    Qtext_width = STATIC_SYMBOL("TEXT-WIDTH",AB_package);
    list_constant_99 = STATIC_LIST((SI_Long)3L,Qmember,Qheader_width,
	    Qtext_width);
    list_constant_100 = STATIC_LIST((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_99);
    list_constant_102 = STATIC_LIST((SI_Long)2L,Qwidth,list_constant_100);
    list_constant_103 = STATIC_LIST((SI_Long)4L,list_constant_101,
	    list_constant_102,list_constant_38,list_constant_42);
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_103);
    list_constant_105 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,
	    list_constant_104);
    Tabular_view_column_type = list_constant_105;
    Qcolumn = STATIC_SYMBOL("COLUMN",AB_package);
    list_constant_106 = STATIC_CONS(Qcolumn,list_constant_54);
    Qcells = STATIC_SYMBOL("CELLS",AB_package);
    list_constant_107 = STATIC_CONS(Qcells,list_constant_58);
    Qrow_values = STATIC_SYMBOL("ROW-VALUES",AB_package);
    list_constant_108 = STATIC_CONS(Qrow_values,list_constant_58);
    list_constant_109 = STATIC_LIST((SI_Long)7L,list_constant_101,
	    list_constant_102,list_constant_38,list_constant_42,
	    list_constant_106,list_constant_107,list_constant_108);
    list_constant_110 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_109);
    list_constant_111 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,
	    list_constant_110);
    Tabular_view_add_column_type = list_constant_111;
    list_constant_112 = STATIC_CONS(Qsymbol,list_constant_28);
    list_constant_113 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qnumber,
	    list_constant_112);
    Tabular_view_logical_id_type = list_constant_113;
    Qlogical_id = STATIC_SYMBOL("LOGICAL-ID",AB_package);
    list_constant_114 = STATIC_CONS(list_constant_113,Qnil);
    list_constant_115 = STATIC_CONS(Qlogical_id,list_constant_114);
    list_constant_116 = STATIC_CONS(Qposition,list_constant_114);
    list_constant_117 = STATIC_LIST((SI_Long)6L,list_constant_115,
	    list_constant_116,list_constant_88,list_constant_87,
	    list_constant_108,list_constant_107);
    list_constant_118 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_117);
    list_constant_119 = STATIC_LIST((SI_Long)4L,Qab_or,Qtext,
	    list_constant_57,list_constant_118);
    Tabular_view_row_type = list_constant_119;
    list_constant_120 = STATIC_LIST((SI_Long)4L,list_constant_88,
	    list_constant_87,list_constant_108,list_constant_107);
    list_constant_121 = STATIC_CONS(list_constant_115,list_constant_120);
    list_constant_122 = STATIC_LIST((SI_Long)2L,Qand,Qlogical_id);
    list_constant_123 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_121,list_constant_122);
    Tabular_view_replace_row_type = list_constant_123;
    list_constant_124 = STATIC_LIST((SI_Long)2L,list_constant_101,
	    list_constant_38);
    list_constant_125 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_124);
    list_constant_126 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,
	    list_constant_125);
    Tabular_view_cell_type = list_constant_126;
    list_constant_127 = STATIC_CONS(list_constant_115,list_constant_124);
    list_constant_128 = STATIC_LIST((SI_Long)2L,Qab_structure,
	    list_constant_127);
    list_constant_129 = STATIC_LIST((SI_Long)3L,Qab_or,Qtext,
	    list_constant_128);
    Tabular_view_column_cell_type = list_constant_129;
    Qindex = STATIC_SYMBOL("INDEX",AB_package);
    list_constant_130 = STATIC_CONS(Qindex,list_constant_54);
    list_constant_131 = STATIC_CONS(list_constant_38,Qnil);
    list_constant_133 = STATIC_LIST_STAR((SI_Long)7L,list_constant_115,
	    list_constant_106,list_constant_130,list_constant_101,
	    list_constant_88,list_constant_87,list_constant_131);
    list_constant_132 = STATIC_LIST((SI_Long)3L,Qab_or,Qcolumn,Qindex);
    list_constant_134 = STATIC_LIST((SI_Long)3L,Qand,Qlogical_id,
	    list_constant_132);
    list_constant_135 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_133,list_constant_134);
    Tabular_view_replace_cell_type = list_constant_135;
    Qg2_defstruct_structure_name_tabular_view_g2_struct = 
	    STATIC_SYMBOL("TABULAR-VIEW-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtabular_view = STATIC_SYMBOL("TABULAR-VIEW",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_tabular_view_g2_struct,
	    Qtabular_view,Qab_name_of_unique_structure_type);
    mutate_global_property(Qtabular_view,
	    Qg2_defstruct_structure_name_tabular_view_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_tabular_view == UNBOUND)
	The_type_description_of_tabular_view = Nil;
    string_constant_30 = 
	    STATIC_STRING("43Dy8m83nfy1p83nfy83=Ly83*vy8n8k1l83=Ly0000001n1m8x83=Ly1m8y83-62y1m83My83-B9yk3Tyk0k0");
    temp = The_type_description_of_tabular_view;
    The_type_description_of_tabular_view = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_30));
    mutate_global_property(Qg2_defstruct_structure_name_tabular_view_g2_struct,
	    The_type_description_of_tabular_view,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qtabular_view,
	    The_type_description_of_tabular_view,Qtype_description_of_type);
    Qoutstanding_tabular_view_count = 
	    STATIC_SYMBOL("OUTSTANDING-TABULAR-VIEW-COUNT",AB_package);
    Qtabular_view_structure_memory_usage = 
	    STATIC_SYMBOL("TABULAR-VIEW-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_31 = STATIC_STRING("1q83nfy8s83-s9y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_tabular_view_count);
    push_optimized_constant(Qtabular_view_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_31));
    Qchain_of_available_tabular_views = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-TABULAR-VIEWS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_tabular_views,
	    Chain_of_available_tabular_views);
    record_system_variable(Qchain_of_available_tabular_views,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qtabular_view_count = STATIC_SYMBOL("TABULAR-VIEW-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtabular_view_count,Tabular_view_count);
    record_system_variable(Qtabular_view_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_tabular_views_vector == UNBOUND)
	Chain_of_available_tabular_views_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qtabular_view_structure_memory_usage,
	    STATIC_FUNCTION(tabular_view_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_tabular_view_count,
	    STATIC_FUNCTION(outstanding_tabular_view_count,NIL,FALSE,0,0));
    reclaim_structure_for_tabular_view_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_tabular_view,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qtabular_view,
	    reclaim_structure_for_tabular_view_1);
    clean_up_structure_for_tabular_view_1 = 
	    STATIC_FUNCTION(clean_up_structure_for_tabular_view,NIL,FALSE,1,1);
    record_direct_structure_method(Qclean_up_structure,Qtabular_view,
	    clean_up_structure_for_tabular_view_1);
    string_constant_19 = 
	    STATIC_STRING("Tabular views are not supported on ~NF");
    Qdeselect = STATIC_SYMBOL("DESELECT",AB_package);
    string_constant_20 = 
	    STATIC_STRING("Tabular-view row with logical-id ~NV not found.");
    list_constant_5 = STATIC_LIST((SI_Long)3L,Qlogical_id,Qcells,Qrow_values);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qlogical_id,Qcells);
    Qselect_rows = STATIC_SYMBOL("SELECT-ROWS",AB_package);
    Qdeselect_rows = STATIC_SYMBOL("DESELECT-ROWS",AB_package);
    Qrow_id = STATIC_SYMBOL("ROW-ID",AB_package);
    list_constant_7 = STATIC_CONS(Qsequence,list_constant_54);
    Qg2_ui_create_tabular_view = STATIC_SYMBOL("G2-UI-CREATE-TABULAR-VIEW",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_create_tabular_view,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    list_constant_8 = STATIC_CONS(Qcontainer,list_constant_1);
    Qcreate = STATIC_SYMBOL("CREATE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_ui_create_tabular_view,
	    STATIC_FUNCTION(g2_ui_create_tabular_view,NIL,FALSE,4,4));
    Qg2_ui_manage_tabular_view = STATIC_SYMBOL("G2-UI-MANAGE-TABULAR-VIEW",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_manage_tabular_view,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_ui_manage_tabular_view,
	    STATIC_FUNCTION(g2_ui_manage_tabular_view,NIL,FALSE,4,4));
    Qmanage_tabular_view = STATIC_SYMBOL("MANAGE-TABULAR-VIEW",AB_package);
    SET_SYMBOL_FUNCTION(Qmanage_tabular_view,
	    STATIC_FUNCTION(manage_tabular_view,NIL,FALSE,3,3));
    Qselection_changed = STATIC_SYMBOL("SELECTION-CHANGED",AB_package);
    Qhandle_tabular_view_message = 
	    STATIC_SYMBOL("HANDLE-TABULAR-VIEW-MESSAGE",AB_package);
    mutate_global_property(Qhandle_tabular_view_message,
	    Qhandle_tabular_view_message,Qnew_style_event_handler);
    Qkey = STATIC_SYMBOL("KEY",AB_package);
    Qrow = STATIC_SYMBOL("ROW",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qselect,Qdeselect);
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_tabular_view_message,
	    STATIC_FUNCTION(handle_tabular_view_message,NIL,FALSE,1,1));
    Qremove_all_selected_rows = STATIC_SYMBOL("REMOVE-ALL-SELECTED-ROWS",
	    AB_package);
    Qg2_ui_get_dialog_base_units = 
	    STATIC_SYMBOL("G2-UI-GET-DIALOG-BASE-UNITS",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_ui_get_dialog_base_units,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    string_constant_21 = 
	    STATIC_STRING("Get dialog base units is not supported on ~NF");
    string_constant_22 = 
	    STATIC_STRING("g2-ui-get-dialog-base-units is only supported in Enterprise edition");
    SET_SYMBOL_FUNCTION(Qg2_ui_get_dialog_base_units,
	    STATIC_FUNCTION(g2_ui_get_dialog_base_units,NIL,FALSE,1,1));
}
