/* bridge.c
 * Input file:  bridge.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "bridge.h"


/* LGSI-INT-OF */
Object g2int_lgsi_int_of(item)
    Object item;
{
    x_note_fn_call(57,0);
    return VALUES_1(LONG_TO_FIXNUM(g2int_shared_gsi_int_of(item)));
}

/* LGSI-STR-OF */
Object g2int_lgsi_str_of(item)
    Object item;
{
    x_note_fn_call(57,1);
    return VALUES_1(inline_restore_lisp_gensym_string(g2int_shared_gsi_str_of(Nil,
	    item)));
}

/* LGSI-SYM-OF */
Object g2int_lgsi_sym_of(item)
    Object item;
{
    Object temp;

    x_note_fn_call(57,2);
    temp = inline_restore_lisp_gensym_string(g2int_shared_gsi_sym_of(Nil,
	    item));
    return intern(temp,G2int_ab_package_1);
}

/* LGSI-SET-SYM */
Object g2int_lgsi_set_sym(item,value)
    Object item, value;
{
    x_note_fn_call(57,3);
    return VALUES_1(VOID_TO_NULL(g2int_shared_gsi_set_sym(Nil,item,
	    inline_extract_c_string(SYMBOL_NAME(value)))));
}

/* LGSI-SET-INT */
Object g2int_lgsi_set_int(item,value)
    Object item, value;
{
    x_note_fn_call(57,4);
    return VALUES_1(VOID_TO_NULL(g2int_shared_gsi_set_int(item,
	    FIXNUM_TO_LONG(value))));
}

/* LGSI-SET-STR */
Object g2int_lgsi_set_str(item,value)
    Object item, value;
{
    x_note_fn_call(57,5);
    return VALUES_1(VOID_TO_NULL(g2int_shared_gsi_set_str(Nil,item,
	    inline_extract_c_string(value))));
}

/* LGSI-ATTR-BY-NAME */
Object g2int_lgsi_attr_by_name(item_with_attributes,attribute_name)
    Object item_with_attributes, attribute_name;
{
    x_note_fn_call(57,6);
    return VALUES_1(g2int_shared_gsi_attr_by_name(Nil,item_with_attributes,
	    inline_extract_c_string(SYMBOL_NAME(attribute_name))));
}

/* LGSI-RECLAIM-ITEMS */
Object g2int_lgsi_reclaim_items(item_to_reclaim)
    Object item_to_reclaim;
{
    x_note_fn_call(57,7);
    return VALUES_1(VOID_TO_NULL(g2int_shared_gsi_reclaim_items(inline_extract_c_array(item_to_reclaim,
	    G2int_gsi_magic_offset))));
}

Object G2int_the_type_description_of_rpc_thread = UNBOUND;

Object G2int_chain_of_available_rpc_threads = UNBOUND;

Object G2int_rpc_thread_count = UNBOUND;

/* RECLAIM-RPC-THREAD-1 */
Object g2int_reclaim_rpc_thread_1(rpc_thread)
    Object rpc_thread;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(57,8);
    inline_note_reclaim_cons(rpc_thread,Nil);
    old_structure_being_reclaimed = G2int_structure_being_reclaimed;
    G2int_structure_being_reclaimed = rpc_thread;
    g2int_reclaim_sockets(ISVREF(rpc_thread,(SI_Long)11L));
    SVREF(rpc_thread,FIX((SI_Long)11L)) = Nil;
    g2int_reclaim_event_tree(ISVREF(rpc_thread,(SI_Long)12L));
    SVREF(rpc_thread,FIX((SI_Long)12L)) = Nil;
    G2int_structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = G2int_chain_of_available_rpc_threads;
    SVREF(rpc_thread,FIX((SI_Long)0L)) = svref_new_value;
    G2int_chain_of_available_rpc_threads = rpc_thread;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-RPC-THREAD */
Object g2int_reclaim_structure_for_rpc_thread(rpc_thread)
    Object rpc_thread;
{
    x_note_fn_call(57,9);
    return g2int_reclaim_rpc_thread_1(rpc_thread);
}

static Object Qg2_defstruct_structure_name_rpc_thread_g2_struct;  /* g2-defstruct-structure-name::rpc-thread-g2-struct */

/* MAKE-PERMANENT-RPC-THREAD-STRUCTURE-INTERNAL */
Object g2int_make_permanent_rpc_thread_structure_internal()
{
    Object def_structure_rpc_thread_variable, temp;
    Object defstruct_g2_rpc_thread_variable, the_array;
    SI_Long gensymed_symbol, gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(57,10);
    def_structure_rpc_thread_variable = Nil;
    temp = FIXNUM_ADD1(G2int_rpc_thread_count);
    G2int_rpc_thread_count = temp;
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_rpc_thread_variable = Nil;
	gensymed_symbol_1 = (SI_Long)19L;
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
	defstruct_g2_rpc_thread_variable = the_array;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rpc_thread_g2_struct;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)5L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)6L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)7L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)8L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)9L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)15L)) = Nil;
	SVREF(defstruct_g2_rpc_thread_variable,FIX((SI_Long)16L)) = Nil;
	def_structure_rpc_thread_variable = defstruct_g2_rpc_thread_variable;
	SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)5L)) = Nil;
	if (gensymed_symbol >= (SI_Long)1L)
	    goto end_loop_1;
	temp = G2int_chain_of_available_rpc_threads;
	SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)0L)) = temp;
	G2int_chain_of_available_rpc_threads = 
		def_structure_rpc_thread_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_rpc_thread_variable);
}

static Object Knew;                /* :new */

static Object Kallocated;          /* :allocated */

static Object Qg2int_null_thread_contour_wrapper;  /* null-thread-contour-wrapper */

/* MAKE-RPC-THREAD-1 */
Object g2int_make_rpc_thread_1()
{
    Object def_structure_rpc_thread_variable, svref_new_value;

    x_note_fn_call(57,11);
    def_structure_rpc_thread_variable = G2int_chain_of_available_rpc_threads;
    if (def_structure_rpc_thread_variable) {
	G2int_chain_of_available_rpc_threads = 
		ISVREF(def_structure_rpc_thread_variable,(SI_Long)0L);
	SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_rpc_thread_g2_struct;
    }
    else
	def_structure_rpc_thread_variable = 
		g2int_make_permanent_rpc_thread_structure_internal();
    inline_note_allocate_cons(def_structure_rpc_thread_variable,Nil);
    svref_new_value = g2int_generate_thread_number();
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)1L)) = 
	    svref_new_value;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)7L)) = Knew;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)8L)) = Kallocated;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)9L)) = Nil;
    ISVREF(def_structure_rpc_thread_variable,(SI_Long)10L) = 
	    FIX((SI_Long)100L);
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)13L)) = Nil;
    svref_new_value = SYMBOL_FUNCTION(Qg2int_null_thread_contour_wrapper);
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)14L)) = 
	    svref_new_value;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)15L)) = Nil;
    SVREF(def_structure_rpc_thread_variable,FIX((SI_Long)16L)) = Nil;
    return VALUES_1(def_structure_rpc_thread_variable);
}

Object G2int_ignored_return_values_for_signals_prop = UNBOUND;

Object G2int_return_function_of_rpc_prop = UNBOUND;

Object G2int_current_rpc_call_handle = UNBOUND;

static Object Qg2int_rpc_signal;   /* rpc-signal */

static Object Qg2int_return_function_of_rpc;  /* return-function-of-rpc */

static Object Qg2int_ignored_return_values_for_signals;  /* ignored-return-values-for-signals */

/* CONTOUR-WRAPPER-FOR-RPC-THREADS */
Object g2int_contour_wrapper_for_rpc_threads()
{
    Object current_icp_socket, signal_name, signal_description, rpc_name, temp;
    Declare_catch(1);
    Declare_special(1);
    Object result;

    x_note_fn_call(57,12);
    current_icp_socket = ISVREF(G2int_current_thread,(SI_Long)18L);
    PUSH_SPECIAL(G2int_current_icp_socket,current_icp_socket,0);
      if (PUSH_CATCH(Qg2int_rpc_signal,0)) {
	  FUNCALL_0(ISVREF(G2int_current_thread,(SI_Long)15L));
	  result = VALUES_1(Nil);
      }
      else
	  result = CATCH_VALUES();
      POP_CATCH(0);
      MVS_2(result,signal_name,signal_description);
      if (signal_name) {
	  rpc_name = ISVREF(G2int_current_thread,(SI_Long)2L);
	  temp = 
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(rpc_name),
		  Qg2int_return_function_of_rpc);
	  APPLY_3(temp,signal_name,signal_description,
		  g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(rpc_name),
		  Qg2int_ignored_return_values_for_signals));
	  result = g2int_thread_kill(G2int_current_thread);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* SIGNAL-FROM-RPC */
Object g2int_signal_from_rpc(signal_name,signal_value)
    Object signal_name, signal_value;
{
    Object result;

    x_note_fn_call(57,13);
    result = VALUES_2(signal_name,signal_value);
    THROW(Qg2int_rpc_signal,result);
}

Object G2int_alist_for_rpc_into_g2_prop = UNBOUND;

static Object Qg2int_alist_for_rpc_into_g2;  /* alist-for-rpc-into-g2 */

/* LOOKUP-GSI-RPC-INFO */
Object g2int_lookup_gsi_rpc_info(context,name)
    Object context, name;
{
    Object temp;

    x_note_fn_call(57,14);
    temp = g2int_assq_function(context,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qg2int_alist_for_rpc_into_g2));
    return VALUES_1(CDR(temp));
}

/* INSTALL-GSI-RPC-INFO */
Object g2int_install_gsi_rpc_info(context,name,gsi_rpc_info)
    Object context, name, gsi_rpc_info;
{
    Object old_entry_qm, gensym_push_modify_macro_arg, car_1, cdr_1;
    Object alist_for_rpc_into_g2_new_value;

    x_note_fn_call(57,15);
    old_entry_qm = g2int_assq_function(context,
	    g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
	    Qg2int_alist_for_rpc_into_g2));
    if (old_entry_qm)
	return VALUES_1(M_CDR(old_entry_qm) = gsi_rpc_info);
    else {
	gensym_push_modify_macro_arg = g2int_gensym_cons_1(context,
		gsi_rpc_info);
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = g2int_getfq_function_no_default(INLINE_SYMBOL_PLIST(name),
		Qg2int_alist_for_rpc_into_g2);
	alist_for_rpc_into_g2_new_value = g2int_gensym_cons_1(car_1,cdr_1);
	return g2int_mutate_global_property(name,
		alist_for_rpc_into_g2_new_value,Qg2int_alist_for_rpc_into_g2);
    }
}

Object G2int_temp_array_for_declare_remote = UNBOUND;

Object G2int_temp_for_declare_remote = UNBOUND;

static Object Qg2int_development;  /* development */

static Object Qg2int_gsi_generic_rpc_return_handler;  /* gsi-generic-rpc-return-handler */

/* LGSI-RPC-DECLARE-REMOTE */
Object g2int_lgsi_rpc_declare_remote(list_function_symbol,number_of_args,
	    number_of_values)
    Object list_function_symbol, number_of_args, number_of_values;
{
    Object temp, temp_1, handle;

    x_note_fn_call(57,16);
    if (g2int_eval_feature(Qg2int_development)) {
	temp = G2int_temp_array_for_declare_remote;
	temp_1 = SYMBOL_NAME(list_function_symbol);
	g2int_shared_gsi_rpc_declare_remote_plain(Nil,temp,temp_1,
		Qg2int_gsi_generic_rpc_return_handler,
		FIXNUM_TO_LONG(number_of_args),
		FIXNUM_TO_LONG(number_of_values),
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
	handle = ISVREF(G2int_temp_array_for_declare_remote,(SI_Long)0L);
    }
    else {
	lgsi_rpc_declare_remote_1(ISTRING(SYMBOL_NAME(list_function_symbol)),
		INTEGER_TO_INT(number_of_args),
		INTEGER_TO_INT(number_of_values));
	handle = G2int_temp_for_declare_remote;
    }
    g2int_install_gsi_rpc_info(g2int_gsi_current_context_number(),
	    list_function_symbol,handle);
    return VALUES_1(handle);
}

static Object string_constant;     /* "No RPC info for ~S" */

static Object Qg2int_gsi_web;      /* gsi-web */

/* APPLY-RPC-IMPORTED-G2 */
Object g2int_apply_rpc_imported_g2(routine_name,argument_list)
    Object routine_name, argument_list;
{
    Object rpc_info, c_vector_of_items, magic_number, argument_items;
    Object argument_value, ab_loop_list_, ab_loop_iter_flag_, temp;
    SI_Long i;

    x_note_fn_call(57,17);
    rpc_info = 
	    g2int_lookup_gsi_rpc_info(g2int_gsi_current_context_number(),
	    routine_name);
    if ( !TRUEP(rpc_info)) {
	g2int_notify_user_at_console(2,string_constant,routine_name);
	return VALUES_1(Nil);
    }
    else {
	c_vector_of_items = 
		gsi_make_items(FIXNUM_TO_LONG(length(argument_list)));
	magic_number = inline_gsi_get_magic_header(c_vector_of_items);
	argument_items = IFIX(magic_number) == (SI_Long)5472500L ? 
		inline_get_array_from_c(c_vector_of_items,
		G2int_gsi_magic_offset) : g2int_gsi_error(2,Qg2int_gsi_web,
		G2int_gsi_bad_magic_number);
	argument_value = Nil;
	ab_loop_list_ = argument_list;
	i = (SI_Long)0L;
	ab_loop_iter_flag_ = T;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	argument_value = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    i = i + (SI_Long)1L;
	g2int_set_simple_value_in_item(ISVREF(argument_items,i + 
		(SI_Long)1L),argument_value);
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
	temp = inline_extract_c_array(argument_items,G2int_gsi_magic_offset);
	g2int_shared_gsi_rpc_start(rpc_info,temp,
		FIXNUM_TO_LONG(g2int_gsi_current_context_number()));
	g2int_lgsi_reclaim_items(argument_items);
	return VALUES_1(T);
    }
}

/* GET-VALUE-OF-ANY-SIMPLE-TYPE */
Object g2int_get_value_of_any_simple_type(item)
    Object item;
{
    Object temp_1;
    SI_Long temp, value;

    x_note_fn_call(57,18);
    temp = g2int_shared_gsi_type_of(item);
    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
	temp_1 = Nil;
    else
	switch ((char)temp) {
	  case 1:
	    temp_1 = g2int_lgsi_int_of(item);
	    break;
	  case 4:
	    temp_1 = g2int_lgsi_str_of(item);
	    break;
	  case 3:
	    temp_1 = g2int_lgsi_sym_of(item);
	    break;
	  case 5:
	    value = g2int_shared_gsi_log_of(item);
	    if ((SI_Long)1000L == value)
		temp_1 = T;
	    else if ((SI_Long)-1000L == value)
		temp_1 = Nil;
	    else
		temp_1 = cerror((SI_Long)2L,"Go",
			"Logicals must be true or false");
	    break;
	  default:
	    temp_1 = Nil;
	    break;
	}
    return VALUES_1(temp_1);
}

/* SET-SIMPLE-VALUE-IN-ITEM */
Object g2int_set_simple_value_in_item(item,value)
    Object item, value;
{
    Object temp;

    x_note_fn_call(57,19);
    g2int_shared_gsi_clear_item(item);
    if (FIXNUMP(value))
	temp = VOID_TO_NULL(g2int_shared_gsi_set_int(item,
		FIXNUM_TO_LONG(value)));
    else if (STRINGP(value))
	temp = VOID_TO_NULL(g2int_shared_gsi_set_str(Nil,item,
		inline_extract_c_string(value)));
    else if (EQ(value,T))
	temp = VOID_TO_NULL(g2int_shared_gsi_set_log(item,(SI_Long)1000L));
    else if (EQ(value,Nil))
	temp = VOID_TO_NULL(g2int_shared_gsi_set_log(item,(SI_Long)-1000L));
    else if (SYMBOLP(value))
	temp = VOID_TO_NULL(g2int_shared_gsi_set_sym(Nil,item,
		inline_extract_c_string(SYMBOL_NAME(value))));
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* LGSI-GET-ATTRIBUTE-VALUE */
Object g2int_lgsi_get_attribute_value(item,attribute_name)
    Object item, attribute_name;
{
    x_note_fn_call(57,20);
    return g2int_get_value_of_any_simple_type(g2int_lgsi_attr_by_name(item,
	    attribute_name));
}

void bridge_INIT()
{
    Object symbol_value_arg, temp, reclaim_structure_for_rpc_thread;
    Object AB_package, Qg2int_rpc_thread, Qg2int_reclaim_structure;
    Object Qg2int_utilities2, Qg2int_rpc_thread_count;
    Object Qg2int_chain_of_available_rpc_threads;
    Object Qg2int_type_description_of_type;
    Object Qg2int_type_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_3, Qg2int_unique_structure_type_of_ab_nameqm;
    Object Qg2int_ab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, string_constant_1;
    Object string_constant_2;

    x_note_fn_call(57,21);
    SET_PACKAGE("AB");
    string_constant_1 = STATIC_STRING("TIMPL");
    string_constant_2 = 
	    STATIC_STRING("*ALLOW-MULTIPLE-FOREIGN-FUNCTIONS-PER-C-NAME*");
    if (find_package(string_constant_1)) {
	symbol_value_arg = find_symbol(string_constant_2,
		find_package(string_constant_1));
	set(symbol_value_arg,T);
    }
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_rpc_thread_g2_struct = 
	    STATIC_SYMBOL("RPC-THREAD-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_rpc_thread = STATIC_SYMBOL("RPC-THREAD",AB_package);
    Qg2int_ab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_rpc_thread_g2_struct,
	    Qg2int_rpc_thread,Qg2int_ab_name_of_unique_structure_type);
    Qg2int_unique_structure_type_of_ab_nameqm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    g2int_mutate_global_property(Qg2int_rpc_thread,
	    Qg2_defstruct_structure_name_rpc_thread_g2_struct,
	    Qg2int_unique_structure_type_of_ab_nameqm);
    if (G2int_the_type_description_of_rpc_thread == UNBOUND)
	G2int_the_type_description_of_rpc_thread = Nil;
    string_constant_3 = 
	    STATIC_STRING("43Dy8l83Py1o83Py83Cy8m8k1l83Cy0000001m1m8o83Cy1n8n83=Ly0k3Fyk0k0");
    temp = G2int_the_type_description_of_rpc_thread;
    G2int_the_type_description_of_rpc_thread = 
	    g2int_load_and_initialize_type_description(temp,
	    g2int_regenerate_optimized_constant(string_constant_3));
    Qg2int_type_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    g2int_mutate_global_property(Qg2_defstruct_structure_name_rpc_thread_g2_struct,
	    G2int_the_type_description_of_rpc_thread,
	    Qg2int_type_description_of_unique_type_name_of_gensym_structure);
    Qg2int_type_description_of_type = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",AB_package);
    g2int_mutate_global_property(Qg2int_rpc_thread,
	    G2int_the_type_description_of_rpc_thread,
	    Qg2int_type_description_of_type);
    Qg2int_chain_of_available_rpc_threads = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-RPC-THREADS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_chain_of_available_rpc_threads,
	    G2int_chain_of_available_rpc_threads);
    Qg2int_utilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    g2int_record_system_variable(Qg2int_chain_of_available_rpc_threads,
	    Qg2int_utilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qg2int_rpc_thread_count = STATIC_SYMBOL("RPC-THREAD-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qg2int_rpc_thread_count,G2int_rpc_thread_count);
    g2int_record_system_variable(Qg2int_rpc_thread_count,Qg2int_utilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qg2int_reclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_rpc_thread = 
	    STATIC_FUNCTION(g2int_reclaim_structure_for_rpc_thread,NIL,
	    FALSE,1,1);
    g2int_record_direct_structure_method(Qg2int_reclaim_structure,
	    Qg2int_rpc_thread,reclaim_structure_for_rpc_thread);
    Knew = STATIC_SYMBOL("NEW",Pkeyword);
    Kallocated = STATIC_SYMBOL("ALLOCATED",Pkeyword);
    Qg2int_null_thread_contour_wrapper = 
	    STATIC_SYMBOL("NULL-THREAD-CONTOUR-WRAPPER",AB_package);
    Qg2int_ignored_return_values_for_signals = 
	    STATIC_SYMBOL("IGNORED-RETURN-VALUES-FOR-SIGNALS",AB_package);
    G2int_ignored_return_values_for_signals_prop = 
	    Qg2int_ignored_return_values_for_signals;
    Qg2int_return_function_of_rpc = STATIC_SYMBOL("RETURN-FUNCTION-OF-RPC",
	    AB_package);
    G2int_return_function_of_rpc_prop = Qg2int_return_function_of_rpc;
    Qg2int_rpc_signal = STATIC_SYMBOL("RPC-SIGNAL",AB_package);
    Qg2int_alist_for_rpc_into_g2 = STATIC_SYMBOL("ALIST-FOR-RPC-INTO-G2",
	    AB_package);
    G2int_alist_for_rpc_into_g2_prop = Qg2int_alist_for_rpc_into_g2;
    if (G2int_temp_array_for_declare_remote == UNBOUND)
	G2int_temp_array_for_declare_remote = make_array(1,FIX((SI_Long)1L));
    if (G2int_temp_for_declare_remote == UNBOUND)
	G2int_temp_for_declare_remote = Nil;
    Qg2int_development = STATIC_SYMBOL("DEVELOPMENT",AB_package);
    Qg2int_gsi_generic_rpc_return_handler = 
	    STATIC_SYMBOL("GSI-GENERIC-RPC-RETURN-HANDLER",AB_package);
    string_constant = STATIC_STRING("No RPC info for ~S");
    Qg2int_gsi_web = STATIC_SYMBOL("GSI-WEB",AB_package);
}
