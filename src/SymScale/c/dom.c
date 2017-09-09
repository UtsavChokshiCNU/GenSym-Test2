/* dom.c
 * Input file:  dom.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "dom.h"


Object The_type_description_of_xml_structure = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_xml_structures, Qchain_of_available_xml_structures);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_structure_count, Qxml_structure_count);

Object Chain_of_available_xml_structures_vector = UNBOUND;

/* XML-STRUCTURE-STRUCTURE-MEMORY-USAGE */
Object xml_structure_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(190,0);
    temp = Xml_structure_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-XML-STRUCTURE-COUNT */
Object outstanding_xml_structure_count()
{
    Object def_structure_xml_structure_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(190,1);
    gensymed_symbol = IFIX(Xml_structure_count);
    def_structure_xml_structure_variable = Chain_of_available_xml_structures;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_xml_structure_variable))
	goto end_loop;
    def_structure_xml_structure_variable = 
	    ISVREF(def_structure_xml_structure_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-XML-STRUCTURE-1 */
Object reclaim_xml_structure_1(xml_structure)
    Object xml_structure;
{
    Object temp, svref_arg_2;

    x_note_fn_call(190,2);
    inline_note_reclaim_cons(xml_structure,Nil);
    temp = ISVREF(Chain_of_available_xml_structures_vector,
	    IFIX(Current_thread_index));
    SVREF(xml_structure,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_xml_structures_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = xml_structure;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-XML-STRUCTURE */
Object reclaim_structure_for_xml_structure(xml_structure)
    Object xml_structure;
{
    x_note_fn_call(190,3);
    return reclaim_xml_structure_1(xml_structure);
}

static Object Qg2_defstruct_structure_name_xml_structure_g2_struct;  /* g2-defstruct-structure-name::xml-structure-g2-struct */

/* MAKE-PERMANENT-XML-STRUCTURE-STRUCTURE-INTERNAL */
Object make_permanent_xml_structure_structure_internal()
{
    Object def_structure_xml_structure_variable;
    Object defstruct_g2_xml_structure_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(190,4);
    def_structure_xml_structure_variable = Nil;
    atomic_incff_symval(Qxml_structure_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_xml_structure_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_xml_structure_variable = the_array;
	SVREF(defstruct_g2_xml_structure_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_structure_g2_struct;
	def_structure_xml_structure_variable = 
		defstruct_g2_xml_structure_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_xml_structure_variable);
}

/* MAKE-XML-STRUCTURE-1 */
Object make_xml_structure_1()
{
    Object def_structure_xml_structure_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(190,5);
    def_structure_xml_structure_variable = 
	    ISVREF(Chain_of_available_xml_structures_vector,
	    IFIX(Current_thread_index));
    if (def_structure_xml_structure_variable) {
	svref_arg_1 = Chain_of_available_xml_structures_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_xml_structure_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_xml_structure_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_structure_g2_struct;
    }
    else
	def_structure_xml_structure_variable = 
		make_permanent_xml_structure_structure_internal();
    inline_note_allocate_cons(def_structure_xml_structure_variable,Nil);
    SVREF(def_structure_xml_structure_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_xml_structure_variable);
}

DEFINE_VARIABLE_WITH_SYMBOL(Xml_structures_extent, Qxml_structures_extent);

DEFINE_VARIABLE_WITH_SYMBOL(Current_xml_structures, Qcurrent_xml_structures);

/* ADD-XML-STRUCTURE-TO-CURRENT-XML-STRUCTURES */
Object add_xml_structure_to_current_xml_structures(xml_structure)
    Object xml_structure;
{
    x_note_fn_call(190,6);
    if (BOUNDP(Qcurrent_xml_structures)) {
	Current_xml_structures = nconc2(Current_xml_structures,
		gensym_cons_1(xml_structure,Nil));
	return VALUES_1(Current_xml_structures);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_xml_node = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_xml_nodes, Qchain_of_available_xml_nodes);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_node_count, Qxml_node_count);

Object Chain_of_available_xml_nodes_vector = UNBOUND;

/* XML-NODE-STRUCTURE-MEMORY-USAGE */
Object xml_node_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(190,7);
    temp = Xml_node_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-XML-NODE-COUNT */
Object outstanding_xml_node_count()
{
    Object def_structure_xml_node_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(190,8);
    gensymed_symbol = IFIX(Xml_node_count);
    def_structure_xml_node_variable = Chain_of_available_xml_nodes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_xml_node_variable))
	goto end_loop;
    def_structure_xml_node_variable = 
	    ISVREF(def_structure_xml_node_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-XML-NODE-INTERNAL-1 */
Object reclaim_xml_node_internal_1(xml_node)
    Object xml_node;
{
    Object temp, svref_arg_2;

    x_note_fn_call(190,9);
    inline_note_reclaim_cons(xml_node,Nil);
    temp = ISVREF(Chain_of_available_xml_nodes_vector,
	    IFIX(Current_thread_index));
    SVREF(xml_node,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_xml_nodes_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = xml_node;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-XML-NODE */
Object reclaim_structure_for_xml_node(xml_node)
    Object xml_node;
{
    x_note_fn_call(190,10);
    return reclaim_xml_node_internal_1(xml_node);
}

static Object Qg2_defstruct_structure_name_xml_node_g2_struct;  /* g2-defstruct-structure-name::xml-node-g2-struct */

/* MAKE-PERMANENT-XML-NODE-STRUCTURE-INTERNAL */
Object make_permanent_xml_node_structure_internal()
{
    Object def_structure_xml_node_variable, defstruct_g2_xml_node_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(190,11);
    def_structure_xml_node_variable = Nil;
    atomic_incff_symval(Qxml_node_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_xml_node_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_xml_node_variable = the_array;
	SVREF(defstruct_g2_xml_node_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_node_g2_struct;
	SVREF(defstruct_g2_xml_node_variable,FIX((SI_Long)1L)) = Nil;
	def_structure_xml_node_variable = defstruct_g2_xml_node_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_xml_node_variable);
}

/* MAKE-XML-NODE-1 */
Object make_xml_node_1()
{
    Object def_structure_xml_node_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(190,12);
    def_structure_xml_node_variable = 
	    ISVREF(Chain_of_available_xml_nodes_vector,
	    IFIX(Current_thread_index));
    if (def_structure_xml_node_variable) {
	svref_arg_1 = Chain_of_available_xml_nodes_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_xml_node_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_xml_node_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_node_g2_struct;
    }
    else
	def_structure_xml_node_variable = 
		make_permanent_xml_node_structure_internal();
    inline_note_allocate_cons(def_structure_xml_node_variable,Nil);
    SVREF(def_structure_xml_node_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_xml_node_variable);
}

Object The_type_description_of_xml_node_list = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_xml_node_lists, Qchain_of_available_xml_node_lists);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_node_list_count, Qxml_node_list_count);

Object Chain_of_available_xml_node_lists_vector = UNBOUND;

/* XML-NODE-LIST-STRUCTURE-MEMORY-USAGE */
Object xml_node_list_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(190,13);
    temp = Xml_node_list_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-XML-NODE-LIST-COUNT */
Object outstanding_xml_node_list_count()
{
    Object def_structure_xml_node_list_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(190,14);
    gensymed_symbol = IFIX(Xml_node_list_count);
    def_structure_xml_node_list_variable = Chain_of_available_xml_node_lists;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_xml_node_list_variable))
	goto end_loop;
    def_structure_xml_node_list_variable = 
	    ISVREF(def_structure_xml_node_list_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-XML-NODE-LIST-INTERNAL-1 */
Object reclaim_xml_node_list_internal_1(xml_node_list)
    Object xml_node_list;
{
    Object temp, svref_arg_2;

    x_note_fn_call(190,15);
    inline_note_reclaim_cons(xml_node_list,Nil);
    temp = ISVREF(Chain_of_available_xml_node_lists_vector,
	    IFIX(Current_thread_index));
    SVREF(xml_node_list,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_xml_node_lists_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = xml_node_list;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-XML-NODE-LIST */
Object reclaim_structure_for_xml_node_list(xml_node_list)
    Object xml_node_list;
{
    x_note_fn_call(190,16);
    return reclaim_xml_node_list_internal_1(xml_node_list);
}

static Object Qg2_defstruct_structure_name_xml_node_list_g2_struct;  /* g2-defstruct-structure-name::xml-node-list-g2-struct */

/* MAKE-PERMANENT-XML-NODE-LIST-STRUCTURE-INTERNAL */
Object make_permanent_xml_node_list_structure_internal()
{
    Object def_structure_xml_node_list_variable;
    Object defstruct_g2_xml_node_list_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(190,17);
    def_structure_xml_node_list_variable = Nil;
    atomic_incff_symval(Qxml_node_list_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_xml_node_list_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_xml_node_list_variable = the_array;
	SVREF(defstruct_g2_xml_node_list_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_node_list_g2_struct;
	SVREF(defstruct_g2_xml_node_list_variable,FIX((SI_Long)1L)) = Nil;
	def_structure_xml_node_list_variable = 
		defstruct_g2_xml_node_list_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_xml_node_list_variable);
}

/* MAKE-XML-NODE-LIST-1 */
Object make_xml_node_list_1()
{
    Object def_structure_xml_node_list_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(190,18);
    def_structure_xml_node_list_variable = 
	    ISVREF(Chain_of_available_xml_node_lists_vector,
	    IFIX(Current_thread_index));
    if (def_structure_xml_node_list_variable) {
	svref_arg_1 = Chain_of_available_xml_node_lists_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_xml_node_list_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_xml_node_list_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_node_list_g2_struct;
    }
    else
	def_structure_xml_node_list_variable = 
		make_permanent_xml_node_list_structure_internal();
    inline_note_allocate_cons(def_structure_xml_node_list_variable,Nil);
    SVREF(def_structure_xml_node_list_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_xml_node_list_variable);
}

/* CREATE-XML-NODE */
Object create_xml_node(native_pointer)
    Object native_pointer;
{
    Object result_1;

    x_note_fn_call(190,19);
    result_1 = make_xml_node_1();
    SVREF(result_1,FIX((SI_Long)1L)) = native_pointer;
    add_xml_structure_to_current_xml_structures(result_1);
    return VALUES_1(result_1);
}

/* CREATE-XML-NODE-LIST */
Object create_xml_node_list(native_pointer)
    Object native_pointer;
{
    Object result_1;

    x_note_fn_call(190,20);
    result_1 = make_xml_node_list_1();
    SVREF(result_1,FIX((SI_Long)1L)) = native_pointer;
    add_xml_structure_to_current_xml_structures(result_1);
    return VALUES_1(result_1);
}

/* RECLAIM-XML-NODE */
Object reclaim_xml_node(node)
    Object node;
{
    x_note_fn_call(190,21);
    if (g2xml_node_type(IFIX(ISVREF(node,(SI_Long)1L))) == 
	    IFIX(Xml_document_node))
	g2xml_dispose_document(IFIX(ISVREF(node,(SI_Long)1L)));
    else
	g2xml_dispose_pointer(IFIX(ISVREF(node,(SI_Long)1L)));
    reclaim_xml_node_internal_1(node);
    return VALUES_1(Nil);
}

/* RECLAIM-XML-NODE-LIST */
Object reclaim_xml_node_list(node_list)
    Object node_list;
{
    x_note_fn_call(190,22);
    g2xml_dispose_pointer(IFIX(ISVREF(node_list,(SI_Long)1L)));
    return reclaim_xml_node_list_internal_1(node_list);
}

/* PRINT-XML-NODE */
Object print_xml_node(xml_node,stream,depth)
    Object xml_node, stream, depth;
{
    Object node_type_symbol, dot_object_dot, dot_stream_dot;

    x_note_fn_call(190,23);
    node_type_symbol = xml_node_type_symbol(xml_node);
    dot_object_dot = xml_node;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)3L,stream,"XML-NODE type=~a",node_type_symbol);
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

/* PRINT-XML-NODE-LIST */
Object print_xml_node_list(xml_node_list,stream,depth)
    Object xml_node_list, stream, depth;
{
    Object node_list_length, dot_object_dot, dot_stream_dot;

    x_note_fn_call(190,24);
    node_list_length = xml_node_list_length(xml_node_list);
    dot_object_dot = xml_node_list;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)3L,stream,"XML-NODE-LIST length=~a",node_list_length);
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

Object The_type_description_of_xml_namespace = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_xml_namespaces, Qchain_of_available_xml_namespaces);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_namespace_count, Qxml_namespace_count);

Object Chain_of_available_xml_namespaces_vector = UNBOUND;

/* XML-NAMESPACE-STRUCTURE-MEMORY-USAGE */
Object xml_namespace_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(190,25);
    temp = Xml_namespace_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-XML-NAMESPACE-COUNT */
Object outstanding_xml_namespace_count()
{
    Object def_structure_xml_namespace_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(190,26);
    gensymed_symbol = IFIX(Xml_namespace_count);
    def_structure_xml_namespace_variable = Chain_of_available_xml_namespaces;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_xml_namespace_variable))
	goto end_loop;
    def_structure_xml_namespace_variable = 
	    ISVREF(def_structure_xml_namespace_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-XML-NAMESPACE-INTERNAL-1 */
Object reclaim_xml_namespace_internal_1(xml_namespace)
    Object xml_namespace;
{
    Object temp, svref_arg_2;

    x_note_fn_call(190,27);
    inline_note_reclaim_cons(xml_namespace,Nil);
    temp = ISVREF(Chain_of_available_xml_namespaces_vector,
	    IFIX(Current_thread_index));
    SVREF(xml_namespace,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_xml_namespaces_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = xml_namespace;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-XML-NAMESPACE */
Object reclaim_structure_for_xml_namespace(xml_namespace)
    Object xml_namespace;
{
    x_note_fn_call(190,28);
    return reclaim_xml_namespace_internal_1(xml_namespace);
}

static Object Qg2_defstruct_structure_name_xml_namespace_g2_struct;  /* g2-defstruct-structure-name::xml-namespace-g2-struct */

/* MAKE-PERMANENT-XML-NAMESPACE-STRUCTURE-INTERNAL */
Object make_permanent_xml_namespace_structure_internal()
{
    Object def_structure_xml_namespace_variable;
    Object defstruct_g2_xml_namespace_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(190,29);
    def_structure_xml_namespace_variable = Nil;
    atomic_incff_symval(Qxml_namespace_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_xml_namespace_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_xml_namespace_variable = the_array;
	SVREF(defstruct_g2_xml_namespace_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_namespace_g2_struct;
	SVREF(defstruct_g2_xml_namespace_variable,FIX((SI_Long)1L)) = Nil;
	def_structure_xml_namespace_variable = 
		defstruct_g2_xml_namespace_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_xml_namespace_variable);
}

/* MAKE-XML-NAMESPACE-1 */
Object make_xml_namespace_1()
{
    Object def_structure_xml_namespace_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(190,30);
    def_structure_xml_namespace_variable = 
	    ISVREF(Chain_of_available_xml_namespaces_vector,
	    IFIX(Current_thread_index));
    if (def_structure_xml_namespace_variable) {
	svref_arg_1 = Chain_of_available_xml_namespaces_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_xml_namespace_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_xml_namespace_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_namespace_g2_struct;
    }
    else
	def_structure_xml_namespace_variable = 
		make_permanent_xml_namespace_structure_internal();
    inline_note_allocate_cons(def_structure_xml_namespace_variable,Nil);
    SVREF(def_structure_xml_namespace_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_xml_namespace_variable);
}

Object The_type_description_of_xml_namespace_list = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_xml_namespace_lists, Qchain_of_available_xml_namespace_lists);

DEFINE_VARIABLE_WITH_SYMBOL(Xml_namespace_list_count, Qxml_namespace_list_count);

Object Chain_of_available_xml_namespace_lists_vector = UNBOUND;

/* XML-NAMESPACE-LIST-STRUCTURE-MEMORY-USAGE */
Object xml_namespace_list_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(190,31);
    temp = Xml_namespace_list_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-XML-NAMESPACE-LIST-COUNT */
Object outstanding_xml_namespace_list_count()
{
    Object def_structure_xml_namespace_list_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(190,32);
    gensymed_symbol = IFIX(Xml_namespace_list_count);
    def_structure_xml_namespace_list_variable = 
	    Chain_of_available_xml_namespace_lists;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_xml_namespace_list_variable))
	goto end_loop;
    def_structure_xml_namespace_list_variable = 
	    ISVREF(def_structure_xml_namespace_list_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-XML-NAMESPACE-LIST-INTERNAL-1 */
Object reclaim_xml_namespace_list_internal_1(xml_namespace_list)
    Object xml_namespace_list;
{
    Object temp, svref_arg_2;

    x_note_fn_call(190,33);
    inline_note_reclaim_cons(xml_namespace_list,Nil);
    temp = ISVREF(Chain_of_available_xml_namespace_lists_vector,
	    IFIX(Current_thread_index));
    SVREF(xml_namespace_list,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_xml_namespace_lists_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = xml_namespace_list;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-XML-NAMESPACE-LIST */
Object reclaim_structure_for_xml_namespace_list(xml_namespace_list)
    Object xml_namespace_list;
{
    x_note_fn_call(190,34);
    return reclaim_xml_namespace_list_internal_1(xml_namespace_list);
}

static Object Qg2_defstruct_structure_name_xml_namespace_list_g2_struct;  /* g2-defstruct-structure-name::xml-namespace-list-g2-struct */

/* MAKE-PERMANENT-XML-NAMESPACE-LIST-STRUCTURE-INTERNAL */
Object make_permanent_xml_namespace_list_structure_internal()
{
    Object def_structure_xml_namespace_list_variable;
    Object defstruct_g2_xml_namespace_list_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(190,35);
    def_structure_xml_namespace_list_variable = Nil;
    atomic_incff_symval(Qxml_namespace_list_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_xml_namespace_list_variable = Nil;
	gensymed_symbol = (SI_Long)2L;
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
	defstruct_g2_xml_namespace_list_variable = the_array;
	SVREF(defstruct_g2_xml_namespace_list_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_xml_namespace_list_g2_struct;
	SVREF(defstruct_g2_xml_namespace_list_variable,FIX((SI_Long)1L)) = Nil;
	def_structure_xml_namespace_list_variable = 
		defstruct_g2_xml_namespace_list_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_xml_namespace_list_variable);
}

/* MAKE-XML-NAMESPACE-LIST-1 */
Object make_xml_namespace_list_1()
{
    Object def_structure_xml_namespace_list_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(190,36);
    def_structure_xml_namespace_list_variable = 
	    ISVREF(Chain_of_available_xml_namespace_lists_vector,
	    IFIX(Current_thread_index));
    if (def_structure_xml_namespace_list_variable) {
	svref_arg_1 = Chain_of_available_xml_namespace_lists_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_xml_namespace_list_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_xml_namespace_list_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_xml_namespace_list_g2_struct;
    }
    else
	def_structure_xml_namespace_list_variable = 
		make_permanent_xml_namespace_list_structure_internal();
    inline_note_allocate_cons(def_structure_xml_namespace_list_variable,Nil);
    SVREF(def_structure_xml_namespace_list_variable,FIX((SI_Long)1L)) = Nil;
    return VALUES_1(def_structure_xml_namespace_list_variable);
}

/* CREATE-XML-NAMESPACE */
Object create_xml_namespace(native_pointer)
    Object native_pointer;
{
    Object result_1;

    x_note_fn_call(190,37);
    result_1 = make_xml_namespace_1();
    SVREF(result_1,FIX((SI_Long)1L)) = native_pointer;
    add_xml_structure_to_current_xml_structures(result_1);
    return VALUES_1(result_1);
}

/* RECLAIM-XML-NAMESPACE */
Object reclaim_xml_namespace(xml_namespace)
    Object xml_namespace;
{
    x_note_fn_call(190,38);
    g2xml_dispose_pointer(IFIX(ISVREF(xml_namespace,(SI_Long)1L)));
    return reclaim_xml_namespace_internal_1(xml_namespace);
}

/* CREATE-XML-NAMESPACE-LIST */
Object create_xml_namespace_list(native_pointer)
    Object native_pointer;
{
    Object result_1;

    x_note_fn_call(190,39);
    result_1 = make_xml_namespace_list_1();
    SVREF(result_1,FIX((SI_Long)1L)) = native_pointer;
    add_xml_structure_to_current_xml_structures(result_1);
    return VALUES_1(result_1);
}

/* RECLAIM-XML-NAMESPACE-LIST */
Object reclaim_xml_namespace_list(xml_namespace)
    Object xml_namespace;
{
    x_note_fn_call(190,40);
    g2xml_dispose_pointer(IFIX(ISVREF(xml_namespace,(SI_Long)1L)));
    return reclaim_xml_namespace_list_internal_1(xml_namespace);
}

/* PRINT-XML-NAMESPACE-LIST */
Object print_xml_namespace_list(xml_namespace_list,stream,depth)
    Object xml_namespace_list, stream, depth;
{
    Object namespace_list_length, dot_object_dot, dot_stream_dot;

    x_note_fn_call(190,41);
    namespace_list_length = xml_namespace_list_length(xml_namespace_list);
    dot_object_dot = xml_namespace_list;
    dot_stream_dot = stream;
    print_random_object_prefix(dot_object_dot,dot_stream_dot);
    format((SI_Long)3L,stream,"XML-NAMESPACE-LIST length=~a",
	    namespace_list_length);
    return print_random_object_suffix(dot_object_dot,dot_stream_dot);
}

/* RECLAIM-XML-STRUCTURES */
Object reclaim_xml_structures varargs_1(int, n)
{
    Object xml_structures;
    Object ignore_documents, xml_structure, ab_loop_list_, xml_documents, doc;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,42);
    INIT_ARGS_nonrelocating();
    xml_structures = REQUIRED_ARG_nonrelocating();
    ignore_documents = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    xml_structure = Nil;
    ab_loop_list_ = xml_structures;
    xml_documents = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    xml_structure = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SIMPLE_VECTOR_P(xml_structure) && EQ(ISVREF(xml_structure,
	    (SI_Long)0L),Qg2_defstruct_structure_name_xml_node_g2_struct)) {
	if (g2xml_node_type(IFIX(ISVREF(xml_structure,(SI_Long)1L))) == 
		IFIX(Xml_document_node)) {
	    if ( !TRUEP(ignore_documents))
		xml_documents = gensym_cons_1(xml_structure,xml_documents);
	}
	else
	    reclaim_xml_node(xml_structure);
    }
    else if (SIMPLE_VECTOR_P(xml_structure) && EQ(ISVREF(xml_structure,
	    (SI_Long)0L),Qg2_defstruct_structure_name_xml_node_list_g2_struct))
	reclaim_xml_node_list(xml_structure);
    else if (SIMPLE_VECTOR_P(xml_structure) && EQ(ISVREF(xml_structure,
	    (SI_Long)0L),Qg2_defstruct_structure_name_xml_namespace_g2_struct))
	reclaim_xml_namespace(xml_structure);
    else if (SIMPLE_VECTOR_P(xml_structure) && EQ(ISVREF(xml_structure,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_xml_namespace_list_g2_struct))
	reclaim_xml_namespace_list(xml_structure);
    else;
    goto next_loop;
  end_loop:
    doc = Nil;
    ab_loop_list_ = xml_documents;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    doc = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_xml_node(doc);
    goto next_loop_1;
  end_loop_1:;
    reclaim_gensym_list_1(xml_documents);
    return VALUES_1(Qnil);
}

/* C-XML-READ-FILE */
Object c_xml_read_file(path)
    Object path;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,43);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(path);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = path;
    temp = LONG_TO_FIXNUM(g2xml_read_file(ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* XML-READ-FILE */
Object xml_read_file(path)
    Object path;
{
    Object native_pointer;

    x_note_fn_call(190,44);
    native_pointer = c_xml_read_file(path);
    if (IFIX(native_pointer) >= (SI_Long)0L)
	return create_xml_node(native_pointer);
    else
	return VALUES_1(Nil);
}

/* C-XML-READ-STRING */
Object c_xml_read_string(string_1,len)
    Object string_1, len;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,45);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    temp = LONG_TO_FIXNUM(g2xml_read_string(ISTRING(temp),IFIX(len)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* XML-READ-STRING */
Object xml_read_string(text_string)
    Object text_string;
{
    Object native_pointer;

    x_note_fn_call(190,46);
    native_pointer = c_xml_read_string(text_string,
	    text_string_length(text_string));
    if (IFIX(native_pointer) >= (SI_Long)0L)
	return create_xml_node(native_pointer);
    else
	return VALUES_1(Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* XML-READ-STRING-OR-STACK-ERROR */
Object xml_read_string_or_stack_error(text_string)
    Object text_string;
{
    Object document, temp, errors, top_of_stack, text_string_1, snapshots;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_1, ab_loop_list_, message_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(190,47);
    document = xml_read_string(text_string);
    temp = document;
    if (temp);
    else {
	errors = xml_get_errors();
	top_of_stack = Cached_top_of_stack;
	text_string_1 = Nil;
	snapshots = Nil;
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
		      error_1 = Nil;
		      ab_loop_list_ = errors;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      error_1 = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      twrite_general_string(error_1);
		      goto next_loop;
		    end_loop:;
		      reclaim_gensym_tree_with_text_strings(errors);
		      text_string_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    snapshots = Snapshots_of_related_blocks;
	    Snapshots_of_related_blocks = Nil;
	    if (Snapshots_of_related_blocks) {
		reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		Snapshots_of_related_blocks = Nil;
	    }
	  POP_SPECIAL();
	POP_SPECIAL();
	message_1 = make_error_text(text_string_1,snapshots);
	temp = raw_stack_error_named_error(top_of_stack,message_1);
    }
    return VALUES_1(temp);
}

/* C-XML-ERROR-GET-MESSAGE-IN-BUFFER */
Object c_xml_error_get_message_in_buffer(error_1,buffer,size,start)
    Object error_1, buffer, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,48);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_error_get_message_in_buffer(IFIX(error_1),ISTRING(temp),
	    IFIX(size),IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* C-XML-ERROR-GET-FILENAME-IN-BUFFER */
Object c_xml_error_get_filename_in_buffer(error_1,buffer,size,start)
    Object error_1, buffer, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,49);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_error_get_filename_in_buffer(IFIX(error_1),ISTRING(temp),
	    IFIX(size),IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-GET-ERRORS */
Object xml_get_errors()
{
    Object error_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(190,50);
    error_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    error_1 = LONG_TO_FIXNUM(g2xml_next_error());
    if ( !(IFIX(error_1) >= (SI_Long)0L))
	goto end_loop;
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
	      twrite_xml_error(error_1);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    ab_loopvar__2 = gensym_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    g2xml_dispose_error(IFIX(error_1));
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qutf_8_string;       /* utf-8-string */

static Object string_constant;     /* "~a:~a:" */

static Object string_constant_1;   /* "Line ~a:" */

static Object string_constant_2;   /* "~a:" */

static Object string_constant_3;   /* " ~a" */

/* TWRITE-XML-ERROR */
Object twrite_xml_error(error_1)
    Object error_1;
{
    Object string_buffer, wide_string_value, message_1, filename;
    SI_Long true_size_required, temp, size_to_use, line_number, column_number;

    x_note_fn_call(190,51);
    true_size_required = g2xml_error_get_message_size(IFIX(error_1));
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_error_get_message_in_buffer(error_1,string_buffer,
		FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	message_1 = wide_string_value;
    }
    else
	message_1 = Nil;
    if (message_1) {
	true_size_required = g2xml_error_get_filename_size(IFIX(error_1));
	temp = IFIX(Maximum_length_for_sax_strings);
	size_to_use = MIN(true_size_required,temp);
	if (size_to_use >= (SI_Long)0L) {
	    string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	    wide_string_value = Nil;
	    c_xml_error_get_filename_in_buffer(error_1,string_buffer,
		    FIX(size_to_use),FIX((SI_Long)0L));
	    wide_string_value = import_text_string(2,string_buffer,
		    Qutf_8_string);
	    reclaim_simple_gensym_string(string_buffer);
	    filename = wide_string_value;
	}
	else
	    filename = Nil;
	line_number = g2xml_error_get_line_number(IFIX(error_1));
	column_number = g2xml_error_get_column_number(IFIX(error_1));
	if (filename) {
	    tformat(3,string_constant,filename,FIX(line_number));
	    reclaim_text_string(filename);
	}
	else
	    tformat(2,string_constant_1,FIX(line_number));
	if (column_number >= (SI_Long)0L)
	    tformat(2,string_constant_2,FIX(column_number));
	tformat(2,string_constant_3,message_1);
	return reclaim_text_string(message_1);
    }
    else
	return VALUES_1(Nil);
}

/* C-XML-WRITE-FILE */
Object c_xml_write_file(document,path)
    Object document, path;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,52);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(path);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = path;
    temp = FIX(g2xml_write_file(IFIX(document),ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* C-XML-BUFFER-GET-CONTENT-IN-BUFFER */
Object c_xml_buffer_get_content_in_buffer(xml_buffer,buffer,size,start)
    Object xml_buffer, buffer, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,53);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_buffer_get_content_in_buffer(IFIX(xml_buffer),ISTRING(temp),
	    IFIX(size),IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-WRITE-FILE */
Object xml_write_file(document,path)
    Object document, path;
{
    x_note_fn_call(190,54);
    return c_xml_write_file(ISVREF(document,(SI_Long)1L),path);
}

/* XML-WRITE-TEXT-STRING */
Object xml_write_text_string(document)
    Object document;
{
    Object string_buffer, wide_string_value, temp_1;
    SI_Long buffer;
    SI_Long true_size_required, temp, size_to_use;

    x_note_fn_call(190,55);
    buffer = g2xml_write_buffer(IFIX(ISVREF(document,(SI_Long)1L)));
    true_size_required = g2xml_buffer_get_content_size(buffer);
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_buffer_get_content_in_buffer(LONG_TO_FIXNUM(buffer),
		string_buffer,FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	temp_1 = wide_string_value;
    }
    else
	temp_1 = Nil;
    g2xml_dispose_buffer(buffer);
    return VALUES_1(temp_1);
}

static Object Knil;                /* :nil */

/* CONVERT-XML-NAME-TO-SYMBOL */
Object convert_xml_name_to_symbol(xml_name_text_string_qm)
    Object xml_name_text_string_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object num_hyphens, char_1, code, temp, schar_arg_2, schar_new_value;
    Object thing_1, simple_or_wide_character, symbol_text_string, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, ab_loop_bind_;
    SI_Long i, ab_loop_bind__1, i_1;
    char thing;
    Declare_special(5);

    x_note_fn_call(190,56);
    if ( !TRUEP(xml_name_text_string_qm))
	return VALUES_1(Nil);
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
	      num_hyphens = FIX((SI_Long)0L);
	      ab_loop_bind_ = 
		      IFIX(text_string_length(xml_name_text_string_qm));
	      i = (SI_Long)0L;
	      char_1 = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(xml_name_text_string_qm,i));
	      if (IFIX(char_1) == (SI_Long)45L)
		  num_hyphens = FIXNUM_ADD1(num_hyphens);
	      else {
		  code = char_1;
		  if (unicode_lowercase_if_uppercase(code)) {
		      ab_loop_bind__1 = (IFIX(num_hyphens) << (SI_Long)1L) 
			      + (SI_Long)1L;
		      i_1 = (SI_Long)0L;
		    next_loop_1:
		      if (i_1 >= ab_loop_bind__1)
			  goto end_loop_1;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = '-';
			  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = '-';
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		      i_1 = i_1 + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_1 = char_1;
			  twrite_wide_character(CHARACTERP(thing_1) ? 
				  CHAR_CODE(thing_1) : thing_1);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing_1 = char_1;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ?
				   CHAR_CODE(thing_1) : thing_1);
			  SET_SCHAR(temp,schar_arg_2,schar_new_value);
			  temp = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp;
		      }
		  }
		  else {
		      code = char_1;
		      if (unicode_uppercase_if_lowercase(code)) {
			  ab_loop_bind__1 = IFIX(num_hyphens) << (SI_Long)1L;
			  i_1 = (SI_Long)0L;
			next_loop_2:
			  if (i_1 >= ab_loop_bind__1)
			      goto end_loop_2;
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = '-';
			      twrite_wide_character(CHARACTERP(CHR(thing)) 
				      ? CHAR_CODE(CHR(thing)) : CHR(thing));
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = '-';
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(CHR(thing)) ? 
				      CHAR_CODE(CHR(thing)) : CHR(thing));
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
			  i_1 = i_1 + (SI_Long)1L;
			  goto next_loop_2;
			end_loop_2:;
			  code = char_1;
			  if (IFIX(code) < (SI_Long)127L)
			      simple_or_wide_character = (SI_Long)97L <= 
				      IFIX(code) && IFIX(code) <= 
				      (SI_Long)122L ? FIX(IFIX(code) + 
				      (SI_Long)-32L) : code;
			  else {
			      simple_or_wide_character = 
				      unicode_uppercase_if_lowercase(code);
			      if (simple_or_wide_character);
			      else
				  simple_or_wide_character = code;
			  }
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing_1 = simple_or_wide_character;
			      twrite_wide_character(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing_1 = simple_or_wide_character;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
		      }
		      else {
			  ab_loop_bind__1 = IFIX(num_hyphens);
			  i_1 = (SI_Long)0L;
			next_loop_3:
			  if (i_1 >= ab_loop_bind__1)
			      goto end_loop_3;
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing = '-';
			      twrite_wide_character(CHARACTERP(CHR(thing)) 
				      ? CHAR_CODE(CHR(thing)) : CHR(thing));
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing = '-';
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(CHR(thing)) ? 
				      CHAR_CODE(CHR(thing)) : CHR(thing));
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
			  i_1 = i_1 + (SI_Long)1L;
			  goto next_loop_3;
			end_loop_3:;
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing_1 = char_1;
			      twrite_wide_character(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing_1 = char_1;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			      SET_SCHAR(temp,schar_arg_2,schar_new_value);
			      temp = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp;
			  }
		      }
		  }
		  num_hyphens = FIX((SI_Long)0L);
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      ab_loop_bind_ = IFIX(num_hyphens);
	      i = (SI_Long)0L;
	    next_loop_4:
	      if (i >= ab_loop_bind_)
		  goto end_loop_4;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = '-';
		  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = '-';
		  schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_4;
	    end_loop_4:;
	      symbol_text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp_1 = intern_text_string(1,symbol_text_string);
    if (temp_1)
	return VALUES_1(temp_1);
    else
	return VALUES_1(Knil);
}

/* CONVERT-XML-NAME-TO-SYMBOL-AND-RECLAIM */
Object convert_xml_name_to_symbol_and_reclaim(name)
    Object name;
{
    Object temp;

    x_note_fn_call(190,57);
    temp = convert_xml_name_to_symbol(name);
    if (name)
	reclaim_text_string(name);
    return VALUES_1(temp);
}

/* CONVERT-SYMBOL-TO-XML-NAME */
Object convert_symbol_to_xml_name(symbol)
    Object symbol;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object symbol_text_string, num_hyphens, char_1, code, temp_1, schar_arg_2;
    Object schar_new_value, thing_1, simple_or_wide_character;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, ab_loop_bind_;
    SI_Long i, ab_loop_bind__1, i_1;
    char temp;
    char thing;
    Declare_special(5);
    Object result;

    x_note_fn_call(190,58);
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
	      symbol_text_string = symbol_name_text_string(symbol);
	      num_hyphens = FIX((SI_Long)0L);
	      ab_loop_bind_ = IFIX(text_string_length(symbol_text_string));
	      i = (SI_Long)0L;
	      char_1 = Nil;
	    next_loop:
	      if (i >= ab_loop_bind_)
		  goto end_loop;
	      char_1 = FIX(UBYTE_16_ISAREF_1(symbol_text_string,i));
	      if (IFIX(char_1) == (SI_Long)45L)
		  num_hyphens = FIXNUM_ADD1(num_hyphens);
	      else {
		  code = char_1;
		  temp = TRUEP(unicode_lowercase_if_uppercase(code));
		  if (temp);
		  else {
		      code = char_1;
		      temp = TRUEP(unicode_uppercase_if_lowercase(code));
		  }
		  if (temp) {
		      ab_loop_bind__1 = IFIX(num_hyphens) >>  -  - (SI_Long)1L;
		      i_1 = (SI_Long)0L;
		    next_loop_1:
		      if (i_1 >= ab_loop_bind__1)
			  goto end_loop_1;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = '-';
			  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = '-';
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		      i_1 = i_1 + (SI_Long)1L;
		      goto next_loop_1;
		    end_loop_1:;
		      if (oddp(num_hyphens)) {
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing_1 = char_1;
			      twrite_wide_character(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp_1 = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing_1 = char_1;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			      temp_1 = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp_1;
			  }
		      }
		      else {
			  code = char_1;
			  if (IFIX(code) < (SI_Long)127L)
			      simple_or_wide_character = (SI_Long)65L <= 
				      IFIX(code) && IFIX(code) <= 
				      (SI_Long)90L ? FIX(IFIX(code) + 
				      (SI_Long)32L) : code;
			  else {
			      simple_or_wide_character = 
				      unicode_lowercase_if_uppercase(code);
			      if (simple_or_wide_character);
			      else
				  simple_or_wide_character = code;
			  }
			  if (EQ(Current_twriting_output_type,Qwide_string)) {
			      thing_1 = simple_or_wide_character;
			      twrite_wide_character(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			  }
			  else {
			      if ( 
				      !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				      Total_length_of_current_gensym_string))
				  extend_current_gensym_string(0);
			      temp_1 = Current_gensym_string;
			      schar_arg_2 = 
				      Fill_pointer_for_current_gensym_string;
			      thing_1 = simple_or_wide_character;
			      schar_new_value = 
				      CODE_CHAR(CHARACTERP(thing_1) ? 
				      CHAR_CODE(thing_1) : thing_1);
			      SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			      temp_1 = 
				      FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			      Fill_pointer_for_current_gensym_string = temp_1;
			  }
		      }
		  }
		  else {
		      ab_loop_bind__1 = IFIX(num_hyphens);
		      i_1 = (SI_Long)0L;
		    next_loop_2:
		      if (i_1 >= ab_loop_bind__1)
			  goto end_loop_2;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing = '-';
			  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing = '-';
			  schar_new_value = 
				  CODE_CHAR(CHARACTERP(CHR(thing)) ? 
				  CHAR_CODE(CHR(thing)) : CHR(thing));
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		      i_1 = i_1 + (SI_Long)1L;
		      goto next_loop_2;
		    end_loop_2:;
		      if (EQ(Current_twriting_output_type,Qwide_string)) {
			  thing_1 = char_1;
			  twrite_wide_character(CHARACTERP(thing_1) ? 
				  CHAR_CODE(thing_1) : thing_1);
		      }
		      else {
			  if ( 
				  !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
				  Total_length_of_current_gensym_string))
			      extend_current_gensym_string(0);
			  temp_1 = Current_gensym_string;
			  schar_arg_2 = Fill_pointer_for_current_gensym_string;
			  thing_1 = char_1;
			  schar_new_value = CODE_CHAR(CHARACTERP(thing_1) ?
				   CHAR_CODE(thing_1) : thing_1);
			  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
			  temp_1 = 
				  FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
			  Fill_pointer_for_current_gensym_string = temp_1;
		      }
		  }
		  num_hyphens = FIX((SI_Long)0L);
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      ab_loop_bind_ = IFIX(num_hyphens);
	      i = (SI_Long)0L;
	    next_loop_3:
	      if (i >= ab_loop_bind_)
		  goto end_loop_3;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = '-';
		  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp_1 = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = '-';
		  schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
		  SET_SCHAR(temp_1,schar_arg_2,schar_new_value);
		  temp_1 = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp_1;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop_3;
	    end_loop_3:;
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* CONVERT-XML-NAMES-TO-SYMBOLS */
Object convert_xml_names_to_symbols(names_string)
    Object names_string;
{
    Object names, name, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(190,59);
    if (names_string) {
	names = 
		parse_text_line_into_list_of_text_strings_function(names_string,
		Whitespace_wide_characters,Whitespace_wide_characters,Nil,
		Nil,Nil);
	name = Nil;
	ab_loop_list_ = names;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		slot_value_cons_1(convert_xml_name_to_symbol_and_reclaim(name),
		Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(names);
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* CONVERT-XML-NAMES-TO-SYMBOLS-AND-RECLAIM */
Object convert_xml_names_to_symbols_and_reclaim(names)
    Object names;
{
    Object temp;

    x_note_fn_call(190,60);
    temp = convert_xml_names_to_symbols(names);
    if (names)
	reclaim_text_string(names);
    return VALUES_1(temp);
}

static Object string_constant_4;   /* " " */

/* CONVERT-SYMBOLS-TO-XML-NAMES */
Object convert_symbols_to_xml_names(symbols)
    Object symbols;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object symbol, ab_loop_list_, xml_name, space_p, ab_loop_iter_flag_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(190,61);
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
	      symbol = Nil;
	      ab_loop_list_ = symbols;
	      xml_name = Nil;
	      space_p = Nil;
	      ab_loop_iter_flag_ = T;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      symbol = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      xml_name = convert_symbol_to_xml_name(symbol);
	      if ( !TRUEP(ab_loop_iter_flag_))
		  space_p = T;
	      if (space_p)
		  twrite(string_constant_4);
	      twrite(xml_name);
	      reclaim_text_string(xml_name);
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop;
	    end_loop:;
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* XML-NODE-GET-LINE */
Object xml_node_get_line(node)
    Object node;
{
    x_note_fn_call(190,62);
    return VALUES_1(FIX(g2xml_get_line(IFIX(ISVREF(node,(SI_Long)1L)))));
}

/* C-XML-GET-CONTENT-IN-BUFFER */
Object c_xml_get_content_in_buffer(node,result_1,size,start)
    Object node, result_1, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,63);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(result_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = result_1;
    g2xml_get_content_in_buffer(IFIX(node),ISTRING(temp),IFIX(size),
	    IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-NODE-GET-CONTENT */
Object xml_node_get_content(node)
    Object node;
{
    Object string_buffer, wide_string_value;
    SI_Long true_size_required, temp, size_to_use;

    x_note_fn_call(190,64);
    true_size_required = g2xml_get_content_size(IFIX(ISVREF(node,
	    (SI_Long)1L)));
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_get_content_in_buffer(ISVREF(node,(SI_Long)1L),string_buffer,
		FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	return VALUES_1(wide_string_value);
    }
    else
	return VALUES_1(Nil);
}

/* XML-NODE-TYPE */
Object xml_node_type(xml_node)
    Object xml_node;
{
    x_note_fn_call(190,65);
    return VALUES_1(FIX(g2xml_node_type(IFIX(ISVREF(xml_node,(SI_Long)1L)))));
}

static Object Qxml_element_node;   /* xml-element-node */

static Object Qxml_attribute_node;  /* xml-attribute-node */

static Object Qxml_text_node;      /* xml-text-node */

static Object Qxml_cdata_section_node;  /* xml-cdata-section-node */

static Object Qxml_entity_reference_node;  /* xml-entity-reference-node */

static Object Qxml_entity_node;    /* xml-entity-node */

static Object Qxml_processing_instruction_node;  /* xml-processing-instruction-node */

static Object Qxml_comment_node;   /* xml-comment-node */

static Object Qxml_document_node;  /* xml-document-node */

static Object Qxml_document_type_node;  /* xml-document-type-node */

static Object Qxml_document_fragment_node;  /* xml-document-fragment-node */

static Object Qxml_notation_node;  /* xml-notation-node */

/* XML-NODE-TYPE-SYMBOL */
Object xml_node_type_symbol(xml_node)
    Object xml_node;
{
    SI_Long temp;

    x_note_fn_call(190,66);
    temp = g2xml_node_type(IFIX(ISVREF(xml_node,(SI_Long)1L)));
    if ( !((SI_Long)-128L <= temp && temp <= (SI_Long)127L))
	return VALUES_1(Nil);
    else
	switch ((char)temp) {
	  case 1:
	    return VALUES_1(Qxml_element_node);
	  case 2:
	    return VALUES_1(Qxml_attribute_node);
	  case 3:
	    return VALUES_1(Qxml_text_node);
	  case 4:
	    return VALUES_1(Qxml_cdata_section_node);
	  case 5:
	    return VALUES_1(Qxml_entity_reference_node);
	  case 6:
	    return VALUES_1(Qxml_entity_node);
	  case 7:
	    return VALUES_1(Qxml_processing_instruction_node);
	  case 8:
	    return VALUES_1(Qxml_comment_node);
	  case 9:
	    return VALUES_1(Qxml_document_node);
	  case 10:
	    return VALUES_1(Qxml_document_type_node);
	  case 11:
	    return VALUES_1(Qxml_document_fragment_node);
	  case 12:
	    return VALUES_1(Qxml_notation_node);
	  default:
	    return VALUES_1(Nil);
	}
}

/* XML-ELEMENT-P */
Object xml_element_p(xml_node)
    Object xml_node;
{
    x_note_fn_call(190,67);
    return VALUES_1(EQ(xml_node_type_symbol(xml_node),Qxml_element_node) ? 
	    T : Nil);
}

/* C-XML-NODE-NEW-CHILD */
Object c_xml_node_new_child(node,namespace,name,value)
    Object node, namespace, name, value;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(190,68);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(value);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = value;
    temp = LONG_TO_FIXNUM(g2xml_node_new_child(IFIX(node),IFIX(namespace),
	    temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

static Object string_constant_5;   /* "" */

/* XML-NODE-NEW-CHILD */
Object xml_node_new_child varargs_1(int, n)
{
    Object node, tagname;
    Object namespace, text_content, temp, temp_1, temp_2, result_pointer;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,69);
    INIT_ARGS_nonrelocating();
    node = REQUIRED_ARG_nonrelocating();
    tagname = REQUIRED_ARG_nonrelocating();
    namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    text_content = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(node,(SI_Long)1L);
    temp_1 = namespace ? ISVREF(namespace,(SI_Long)1L) : FIX((SI_Long)-1L);
    temp_2 = text_content;
    if (temp_2);
    else
	temp_2 = string_constant_5;
    result_pointer = c_xml_node_new_child(temp,temp_1,tagname,temp_2);
    if (IFIX(result_pointer) >= (SI_Long)0L)
	return create_xml_node(result_pointer);
    else
	return VALUES_1(Nil);
}

/* C-XML-NODE-ADD-CONTENT */
Object c_xml_node_add_content(node,value)
    Object node, value;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,70);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(value);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = value;
    g2xml_node_add_content(IFIX(node),ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-NODE-ADD-CONTENT */
Object xml_node_add_content(node,textvalue)
    Object node, textvalue;
{
    x_note_fn_call(190,71);
    return c_xml_node_add_content(ISVREF(node,(SI_Long)1L),textvalue);
}

/* C-XML-NODE-ADD-COMMENT */
Object c_xml_node_add_comment(node,text)
    Object node, text;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,72);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(text);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = text;
    g2xml_node_add_comment(IFIX(node),ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-NODE-ADD-COMMENT */
Object xml_node_add_comment(node,text)
    Object node, text;
{
    x_note_fn_call(190,73);
    return c_xml_node_add_comment(ISVREF(node,(SI_Long)1L),text);
}

/* XML-NODE-PARENT-NODE */
Object xml_node_parent_node(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,74);
    result_pointer = g2xml_node_parent_node(IFIX(ISVREF(xml_node,
	    (SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-CHILD-NODES */
Object xml_node_child_nodes(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,75);
    result_pointer = g2xml_node_child_nodes(IFIX(ISVREF(xml_node,
	    (SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node_list(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-FIRST-CHILD */
Object xml_node_first_child(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,76);
    result_pointer = g2xml_node_child_nodes(IFIX(ISVREF(xml_node,
	    (SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-LAST-CHILD */
Object xml_node_last_child(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,77);
    result_pointer = g2xml_node_last_child(IFIX(ISVREF(xml_node,(SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-GET-CHILD-BY-NAME */
Object xml_node_get_child_by_name varargs_1(int, n)
{
    Object node, local_name;
    Object ns_uri;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,78);
    INIT_ARGS_nonrelocating();
    node = REQUIRED_ARG_nonrelocating();
    local_name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    return xml_node_list_item_by_name(3,xml_node_child_nodes(node),
	    local_name,ns_uri);
}

/* XML-NODE-GET-CHILD-BY-NAME-SYMBOL */
Object xml_node_get_child_by_name_symbol varargs_1(int, n)
{
    Object node, name;
    Object ns_uri, name_string, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,79);
    INIT_ARGS_nonrelocating();
    node = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    name_string = convert_symbol_to_xml_name(name);
    temp = xml_node_get_child_by_name(3,node,name_string,ns_uri);
    reclaim_text_string(name_string);
    return VALUES_1(temp);
}

/* XML-NODE-PREVIOUS-SIBLING */
Object xml_node_previous_sibling(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,80);
    result_pointer = g2xml_node_previous_sibling(IFIX(ISVREF(xml_node,
	    (SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-NEXT-SIBLING */
Object xml_node_next_sibling(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,81);
    result_pointer = g2xml_node_next_sibling(IFIX(ISVREF(xml_node,
	    (SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-ATTRIBUTES */
Object xml_node_attributes(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,82);
    result_pointer = g2xml_node_attributes(IFIX(ISVREF(xml_node,(SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node_list(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-NAMESPACE */
Object xml_node_namespace(xml_node)
    Object xml_node;
{
    SI_Long result_pointer;

    x_note_fn_call(190,83);
    result_pointer = g2xml_node_namespace(IFIX(ISVREF(xml_node,(SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_namespace(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-SET-NAMESPACE */
Object xml_node_set_namespace(xml_node,xml_namespace_qm)
    Object xml_node, xml_namespace_qm;
{
    x_note_fn_call(190,84);
    g2xml_node_set_namespace(IFIX(ISVREF(xml_node,(SI_Long)1L)),
	    xml_namespace_qm ? IFIX(ISVREF(xml_namespace_qm,(SI_Long)1L)) :
	     (SI_Long)-1L);
    return VALUES_1(Nil);
}

/* XML-NODE-NAMESPACE-URI */
Object xml_node_namespace_uri(node)
    Object node;
{
    Object namespace;

    x_note_fn_call(190,85);
    namespace = xml_node_namespace(node);
    if (namespace)
	return xml_namespace_get_uri(namespace);
    else
	return VALUES_1(Nil);
}

/* XML-NODE-NAMESPACE-URI-EQUALS-P */
Object xml_node_namespace_uri_equals_p(node,ns_uri)
    Object node, ns_uri;
{
    Object ns_uri_of_node, temp;

    x_note_fn_call(190,86);
    ns_uri_of_node = xml_node_namespace_uri(node);
    temp = equalw(ns_uri,ns_uri_of_node);
    if (ns_uri_of_node)
	reclaim_text_string(ns_uri_of_node);
    return VALUES_1(temp);
}

/* XML-NODE-LOCAL-NAME */
Object xml_node_local_name(node)
    Object node;
{
    Object string_buffer, wide_string_value;
    SI_Long true_size_required, temp, size_to_use;

    x_note_fn_call(190,87);
    true_size_required = g2xml_node_local_name_size(IFIX(ISVREF(node,
	    (SI_Long)1L)));
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_node_local_name_in_buffer(ISVREF(node,(SI_Long)1L),
		string_buffer,FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	return VALUES_1(wide_string_value);
    }
    else
	return VALUES_1(Nil);
}

/* C-XML-NODE-LOCAL-NAME-IN-BUFFER */
Object c_xml_node_local_name_in_buffer(node,buffer,size,start)
    Object node, buffer, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,88);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_node_local_name_in_buffer(IFIX(node),ISTRING(temp),IFIX(size),
	    IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-NODE-LOCAL-NAME-SYMBOL */
Object xml_node_local_name_symbol(node)
    Object node;
{
    x_note_fn_call(190,89);
    return convert_xml_name_to_symbol_and_reclaim(xml_node_local_name(node));
}

/* XML-NODE-LOCAL-NAME-EQUALS-P */
Object xml_node_local_name_equals_p(node,local_name)
    Object node, local_name;
{
    Object local_name_of_node, temp;

    x_note_fn_call(190,90);
    local_name_of_node = xml_node_local_name(node);
    temp = equalw(local_name,local_name_of_node);
    if (local_name_of_node)
	reclaim_text_string(local_name_of_node);
    return VALUES_1(temp);
}

/* XML-NODE-PREFIX */
Object xml_node_prefix(node)
    Object node;
{
    Object namespace;

    x_note_fn_call(190,91);
    namespace = xml_node_namespace(node);
    if (namespace)
	return xml_namespace_get_prefix(namespace);
    else
	return VALUES_1(Nil);
}

/* XML-NODE-NAME */
Object xml_node_name(node)
    Object node;
{
    Object temp, temp_1, temp_2;

    x_note_fn_call(190,92);
    temp = xml_node_local_name(node);
    temp_1 = xml_node_prefix(node);
    temp_2 = xml_node_namespace_uri(node);
    return VALUES_3(temp,temp_1,temp_2);
}

/* XML-NODE-NAME-SYMBOLS */
Object xml_node_name_symbols(node)
    Object node;
{
    Object local_name, prefix, ns_uri, temp, temp_1;
    Object result;

    x_note_fn_call(190,93);
    result = xml_node_name(node);
    MVS_3(result,local_name,prefix,ns_uri);
    temp = convert_xml_name_to_symbol_and_reclaim(local_name);
    temp_1 = convert_xml_name_to_symbol_and_reclaim(prefix);
    return VALUES_3(temp,temp_1,ns_uri);
}

/* XML-NODE-NAME-EQUALS-P */
Object xml_node_name_equals_p varargs_1(int, n)
{
    Object node, local_name;
    Object ns_uri;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,94);
    INIT_ARGS_nonrelocating();
    node = REQUIRED_ARG_nonrelocating();
    local_name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    if (xml_node_namespace_uri_equals_p(node,ns_uri))
	return xml_node_local_name_equals_p(node,local_name);
    else
	return VALUES_1(Nil);
}

/* XML-NODE-NAME-SYMBOL-EQUALS-P */
Object xml_node_name_symbol_equals_p varargs_1(int, n)
{
    Object node, name;
    Object ns_uri, name_string, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,95);
    INIT_ARGS_nonrelocating();
    node = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    name_string = convert_symbol_to_xml_name(name);
    temp = xml_node_name_equals_p(3,node,name_string,ns_uri);
    reclaim_text_string(name_string);
    return VALUES_1(temp);
}

/* C-XML-NODE-LOOKUP-NAMESPACE */
Object c_xml_node_lookup_namespace(node,prefix)
    Object node, prefix;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,96);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(prefix);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = prefix;
    temp = LONG_TO_FIXNUM(g2xml_node_lookup_namespace(IFIX(node),
	    ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(temp);
}

/* XML-NODE-LOOKUP-NAMESPACE */
Object xml_node_lookup_namespace(xml_node,prefix_qm)
    Object xml_node, prefix_qm;
{
    Object temp, temp_1, result_pointer;

    x_note_fn_call(190,97);
    temp = ISVREF(xml_node,(SI_Long)1L);
    temp_1 = prefix_qm;
    if (temp_1);
    else
	temp_1 = string_constant_5;
    result_pointer = c_xml_node_lookup_namespace(temp,temp_1);
    if (IFIX(result_pointer) >= (SI_Long)0L)
	return create_xml_namespace(result_pointer);
    else
	return VALUES_1(Nil);
}

/* XML-NODE-LOOKUP-NAMESPACE-SYMBOL */
Object xml_node_lookup_namespace_symbol(node,prefix_qm)
    Object node, prefix_qm;
{
    Object prefix_string_qm, temp;

    x_note_fn_call(190,98);
    prefix_string_qm = convert_symbol_to_xml_name(prefix_qm);
    temp = xml_node_lookup_namespace(node,prefix_string_qm);
    if (prefix_string_qm)
	reclaim_text_string(prefix_string_qm);
    return VALUES_1(temp);
}

/* XML-QNAME-EXPAND */
Object xml_qname_expand(qname)
    Object qname;
{
    Object colon_pos_qm, temp, temp_1;
    Declare_stack_pointer;
    Object result;

    x_note_fn_call(190,99);
    SAVE_STACK();
    colon_pos_qm = position_in_text_string(FIX((SI_Long)58L),qname);
    if (colon_pos_qm) {
	temp = text_string_substring(qname,FIXNUM_ADD1(colon_pos_qm),Nil);
	temp_1 = text_string_substring(qname,FIX((SI_Long)0L),colon_pos_qm);
	SAVE_VALUES(VALUES_2(temp,temp_1));
	reclaim_text_string(qname);
	result = RESTORE_VALUES();
	RESTORE_STACK();
	return result;
    }
    else {
	result = VALUES_2(qname,Nil);
	RESTORE_STACK();
	return result;
    }
}

/* XML-NODE-EXPAND-QNAME */
Object xml_node_expand_qname(node,qname)
    Object node, qname;
{
    Object local_name, prefix_qm, temp;
    Object result;

    x_note_fn_call(190,100);
    result = xml_qname_expand(qname);
    MVS_2(result,local_name,prefix_qm);
    temp = xml_node_lookup_namespace(node,prefix_qm);
    return VALUES_3(local_name,prefix_qm,temp);
}

/* XML-NODE-EXPAND-QNAME-SYMBOLS */
Object xml_node_expand_qname_symbols(node,qname)
    Object node, qname;
{
    Object local_name, prefix_qm, namespace_qm, temp, temp_1;
    Object result;

    x_note_fn_call(190,101);
    result = xml_node_expand_qname(node,qname);
    MVS_3(result,local_name,prefix_qm,namespace_qm);
    temp = convert_xml_name_to_symbol_and_reclaim(local_name);
    temp_1 = convert_xml_name_to_symbol_and_reclaim(prefix_qm);
    return VALUES_3(temp,temp_1,namespace_qm);
}

/* XML-NODE-HAS-CHILD-NODES-P */
Object xml_node_has_child_nodes_p(xml_node)
    Object xml_node;
{
    x_note_fn_call(190,102);
    return VALUES_1(g2xml_node_has_child_nodes_p(IFIX(ISVREF(xml_node,
	    (SI_Long)1L))) != (SI_Long)0L ? T : Nil);
}

/* XML-NODE-HAS-ATTRIBUTES-P */
Object xml_node_has_attributes_p(xml_node)
    Object xml_node;
{
    x_note_fn_call(190,103);
    return VALUES_1(g2xml_node_has_attributes_p(IFIX(ISVREF(xml_node,
	    (SI_Long)1L))) != (SI_Long)0L ? T : Nil);
}

/* XML-NODE-LIST-LENGTH */
Object xml_node_list_length(xml_node_list)
    Object xml_node_list;
{
    x_note_fn_call(190,104);
    return VALUES_1(FIX(g2xml_node_list_length(IFIX(ISVREF(xml_node_list,
	    (SI_Long)1L)))));
}

/* XML-NODE-LIST-ITEM */
Object xml_node_list_item(xml_node_list,index_1)
    Object xml_node_list, index_1;
{
    SI_Long result_pointer;

    x_note_fn_call(190,105);
    result_pointer = g2xml_node_list_item(IFIX(ISVREF(xml_node_list,
	    (SI_Long)1L)),IFIX(index_1));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NODE-LIST-ITEM-BY-NAME */
Object xml_node_list_item_by_name varargs_1(int, n)
{
    Object node_list, local_name;
    Object ns_uri, node, ab_list_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,106);
    INIT_ARGS_nonrelocating();
    node_list = REQUIRED_ARG_nonrelocating();
    local_name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    node = Nil;
    ab_list_ = node_list;
    if ( !TRUEP(ab_list_))
	goto end_loop;
    node = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(node))
	goto end_loop;
    if (xml_node_name_equals_p(3,node,local_name,ns_uri))
	return VALUES_1(node);
    node = xml_node_next_sibling(node);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* XML-CREATE-DOCUMENT */
Object xml_create_document()
{
    SI_Long result_pointer;

    x_note_fn_call(190,107);
    result_pointer = g2xml_create_document();
    if (result_pointer >= (SI_Long)0L)
	return create_xml_node(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-DOCUMENT-ROOT-ELEMENT */
Object xml_document_root_element(xml_document)
    Object xml_document;
{
    Object child, ab_list_, ab_node_;

    x_note_fn_call(190,108);
    child = Nil;
    ab_list_ = xml_node_child_nodes(xml_document);
    if ( !TRUEP(ab_list_))
	goto end_loop;
    ab_node_ = xml_node_list_item(ab_list_,FIX((SI_Long)0L));
  next_loop:
    if ( !TRUEP(ab_node_))
	goto end_loop_1;
    if (xml_element_p(ab_node_))
	goto end_loop_1;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop;
  end_loop_1:
    child = ab_node_;
    goto end_1;
    child = Qnil;
  end_1:;
  next_loop_1:
    if ( !TRUEP(child))
	goto end_loop;
    return VALUES_1(child);
    ab_node_ = xml_node_next_sibling(child);
  next_loop_2:
    if ( !TRUEP(ab_node_))
	goto end_loop_2;
    if (xml_element_p(ab_node_))
	goto end_loop_2;
    ab_node_ = xml_node_next_sibling(ab_node_);
    goto next_loop_2;
  end_loop_2:
    child = ab_node_;
    goto end_2;
    child = Qnil;
  end_2:;
    goto next_loop_1;
  end_loop:
    return VALUES_1(Qnil);
}

/* XML-DOCUMENT-IS-VALID-P */
Object xml_document_is_valid_p(xml_document,xml_schema_document)
    Object xml_document, xml_schema_document;
{
    x_note_fn_call(190,109);
    return VALUES_1((SI_Long)0L == 
	    g2xml_document_validate(IFIX(ISVREF(xml_document,(SI_Long)1L)),
	    IFIX(ISVREF(xml_schema_document,(SI_Long)1L))) ? T : Nil);
}

/* XML-VALIDATE-FILE */
Object xml_validate_file(path_to_file)
    Object path_to_file;
{
    Object xml_doc;

    x_note_fn_call(190,110);
    xml_doc = xml_read_file(path_to_file);
    if (xml_validate_document(xml_doc))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* XML-VALIDATE-TEXT */
Object xml_validate_text(document_text)
    Object document_text;
{
    Object xml_doc;

    x_note_fn_call(190,111);
    xml_doc = xml_read_string(document_text);
    if (xml_validate_document(xml_doc))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* XML-VALIDATE-FILE2 */
Object xml_validate_file2(path_to_file,path_to_schema)
    Object path_to_file, path_to_schema;
{
    Object xml_doc, schema_doc;

    x_note_fn_call(190,112);
    xml_doc = xml_read_file(path_to_file);
    schema_doc = xml_read_file(path_to_schema);
    if (xml_validate_document2(xml_doc,schema_doc))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* XML-VALIDATE-TEXT2 */
Object xml_validate_text2(document_text,schema_text)
    Object document_text, schema_text;
{
    Object xml_doc, schema_doc;

    x_note_fn_call(190,113);
    xml_doc = xml_read_string(document_text);
    schema_doc = xml_read_string(schema_text);
    if (xml_validate_document2(xml_doc,schema_doc))
	return VALUES_1(Evaluation_true_value);
    else
	return VALUES_1(Evaluation_false_value);
}

/* XML-VALIDATE-DOCUMENT2 */
Object xml_validate_document2(xml_document,schema_document)
    Object xml_document, schema_document;
{
    Object errors, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_1, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(190,114);
    errors = Nil;
    if ( !(xml_document && schema_document && 
	    xml_document_is_valid_p(xml_document,schema_document))) {
	errors = xml_get_errors();
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
		      error_1 = Nil;
		      ab_loop_list_ = errors;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      error_1 = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      twrite_general_string(error_1);
		      goto next_loop;
		    end_loop:;
		      reclaim_gensym_tree_with_text_strings(errors);
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
	return VALUES_1(Nil);
    }
    return VALUES_1(T);
}

/* XML-VALIDATE-DOCUMENT */
Object xml_validate_document(xml_document)
    Object xml_document;
{
    Object errors, snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_1, ab_loop_list_, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(190,115);
    errors = Nil;
    if ( !(xml_document && (SI_Long)0L == 
	    g2xml_validate(IFIX(ISVREF(xml_document,(SI_Long)1L))))) {
	errors = xml_get_errors();
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
		      error_1 = Nil;
		      ab_loop_list_ = errors;
		    next_loop:
		      if ( !TRUEP(ab_loop_list_))
			  goto end_loop;
		      error_1 = M_CAR(ab_loop_list_);
		      ab_loop_list_ = M_CDR(ab_loop_list_);
		      twrite_general_string(error_1);
		      goto next_loop;
		    end_loop:;
		      reclaim_gensym_tree_with_text_strings(errors);
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
	return VALUES_1(Nil);
    }
    return VALUES_1(T);
}

/* C-XML-ATTR-GET-NAME-IN-BUFFER */
Object c_xml_attr_get_name_in_buffer(node,result_1,size,start)
    Object node, result_1, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,116);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(result_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = result_1;
    g2xml_attr_get_name_in_buffer(IFIX(node),ISTRING(temp),IFIX(size),
	    IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-ATTR-GET-NAME */
Object xml_attr_get_name(xml_attr)
    Object xml_attr;
{
    Object string_buffer, wide_string_value;
    SI_Long true_size_required, temp, size_to_use;

    x_note_fn_call(190,117);
    true_size_required = g2xml_attr_get_name_size(IFIX(ISVREF(xml_attr,
	    (SI_Long)1L)));
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_attr_get_name_in_buffer(ISVREF(xml_attr,(SI_Long)1L),
		string_buffer,FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	return VALUES_1(wide_string_value);
    }
    else
	return VALUES_1(Nil);
}

/* C-XML-ELEMENT-GET-ATTRIBUTE-SIZE */
Object c_xml_element_get_attribute_size(xml_element,name,namespace)
    Object xml_element, name, namespace;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(190,118);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(namespace);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = namespace;
    temp = FIX(g2xml_element_get_attribute_size(IFIX(xml_element),temp_1,
	    ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* C-XML-ELEMENT-GET-ATTRIBUTE-IN-BUFFER */
Object c_xml_element_get_attribute_in_buffer(xml_element,name,namespace,
	    buffer,size,start)
    Object xml_element, name, namespace, buffer, size, start;
{
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2, temp;
    char *temp_1, *temp_2;

    x_note_fn_call(190,119);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(namespace);
    gensymed_symbol_2 = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = namespace;
    temp_2 = ISTRING(temp);
    temp = gensymed_symbol_2;
    if (temp);
    else
	temp = buffer;
    g2xml_element_get_attribute_in_buffer(IFIX(xml_element),temp_1,temp_2,
	    ISTRING(temp),IFIX(size),IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    if (gensymed_symbol_2)
	reclaim_gensym_string(gensymed_symbol_2);
    return VALUES_1(Nil);
}

/* XML-ELEMENT-GET-ATTRIBUTE */
Object xml_element_get_attribute varargs_1(int, n)
{
    Object xml_element, name;
    Object namespace_uri, temp, temp_1, true_size_required, size_to_use;
    Object string_buffer, wide_string_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,120);
    INIT_ARGS_nonrelocating();
    xml_element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    namespace_uri = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(xml_element,(SI_Long)1L);
    temp_1 = namespace_uri;
    if (temp_1);
    else
	temp_1 = string_constant_5;
    true_size_required = c_xml_element_get_attribute_size(temp,name,temp_1);
    size_to_use = FIXNUM_MIN(true_size_required,
	    Maximum_length_for_sax_strings);
    if (IFIX(size_to_use) >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(size_to_use);
	wide_string_value = Nil;
	temp_1 = ISVREF(xml_element,(SI_Long)1L);
	temp = namespace_uri;
	if (temp);
	else
	    temp = string_constant_5;
	c_xml_element_get_attribute_in_buffer(temp_1,name,temp,
		string_buffer,size_to_use,FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	return VALUES_1(wide_string_value);
    }
    else
	return VALUES_1(Nil);
}

/* XML-ELEMENT-GET-ATTRIBUTE-SYMBOL */
Object xml_element_get_attribute_symbol varargs_1(int, n)
{
    Object element, name;
    Object ns_uri;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,121);
    INIT_ARGS_nonrelocating();
    element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    return convert_xml_name_to_symbol_and_reclaim(xml_element_get_attribute(3,
	    element,name,ns_uri));
}

/* XML-ELEMENT-GET-ATTRIBUTE-SYMBOLS */
Object xml_element_get_attribute_symbols varargs_1(int, n)
{
    Object element, name;
    Object ns_uri;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,122);
    INIT_ARGS_nonrelocating();
    element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    return convert_xml_names_to_symbols_and_reclaim(xml_element_get_attribute(3,
	    element,name,ns_uri));
}

/* XML-ELEMENT-GET-ATTRIBUTE-QNAME */
Object xml_element_get_attribute_qname varargs_1(int, n)
{
    Object element, name;
    Object ns_uri, qname;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,123);
    INIT_ARGS_nonrelocating();
    element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    ns_uri = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    qname = xml_element_get_attribute(3,element,name,ns_uri);
    if (qname)
	return xml_node_expand_qname(element,qname);
    else
	return VALUES_3(Nil,Nil,Nil);
}

/* XML-NAMESPACE-GET-PREFIX-SYMBOL */
Object xml_namespace_get_prefix_symbol(namespace)
    Object namespace;
{
    x_note_fn_call(190,124);
    return convert_xml_name_to_symbol_and_reclaim(xml_namespace_get_prefix(namespace));
}

/* C-XML-ELEMENT-SET-ATTRIBUTE */
Object c_xml_element_set_attribute(element,namespace,name,value)
    Object element, namespace, name, value;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(190,125);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(value);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = value;
    g2xml_element_set_attribute(IFIX(element),IFIX(namespace),temp_1,
	    ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(Nil);
}

/* XML-ELEMENT-SET-ATTRIBUTE */
Object xml_element_set_attribute varargs_1(int, n)
{
    Object xml_element, name, value;
    Object namespace;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,126);
    INIT_ARGS_nonrelocating();
    xml_element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    c_xml_element_set_attribute(ISVREF(xml_element,(SI_Long)1L),namespace ?
	     ISVREF(namespace,(SI_Long)1L) : FIX((SI_Long)-1L),name,value);
    return VALUES_1(T);
}

/* XML-ELEMENT-SET-ATTRIBUTE-SYMBOL */
Object xml_element_set_attribute_symbol varargs_1(int, n)
{
    Object element, name, value;
    Object namespace, value_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,127);
    INIT_ARGS_nonrelocating();
    element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (value) {
	value_string = convert_symbol_to_xml_name(value);
	xml_element_set_attribute(4,element,name,value_string,namespace);
	return reclaim_text_string(value_string);
    }
    else
	return VALUES_1(Nil);
}

/* XML-ELEMENT-SET-ATTRIBUTE-SYMBOLS */
Object xml_element_set_attribute_symbols varargs_1(int, n)
{
    Object element, name, vals;
    Object namespace, value_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,128);
    INIT_ARGS_nonrelocating();
    element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    vals = REQUIRED_ARG_nonrelocating();
    namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    value_string = convert_symbols_to_xml_names(vals);
    xml_element_set_attribute(4,element,name,value_string,namespace);
    return reclaim_text_string(value_string);
}

/* XML-ELEMENT-SET-ATTRIBUTE-FROM-TEXT-SLOT-VALUE */
Object xml_element_set_attribute_from_text_slot_value varargs_1(int, n)
{
    Object element, name, slot_value;
    Object namespace, value_string;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,129);
    INIT_ARGS_nonrelocating();
    element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    slot_value = REQUIRED_ARG_nonrelocating();
    namespace = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (slot_value) {
	value_string = convert_text_to_text_string(1,CDR(slot_value));
	xml_element_set_attribute(4,element,name,value_string,namespace);
	return reclaim_text_string(value_string);
    }
    else
	return VALUES_1(Nil);
}

/* C-XML-ELEMENT-GET-ATTRIBUTE-NODE */
Object c_xml_element_get_attribute_node(xml_element,name,namespace)
    Object xml_element, name, namespace;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(190,130);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(namespace);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = namespace;
    temp = 
	    LONG_TO_FIXNUM(g2xml_element_get_attribute_node(IFIX(xml_element),
	    temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* XML-ELEMENT-GET-ATTRIBUTE-NODE */
Object xml_element_get_attribute_node varargs_1(int, n)
{
    Object xml_element, name;
    Object namespace_uri, temp, temp_1, result_pointer;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,131);
    INIT_ARGS_nonrelocating();
    xml_element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    namespace_uri = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(xml_element,(SI_Long)1L);
    temp_1 = namespace_uri;
    if (temp_1);
    else
	temp_1 = string_constant_5;
    result_pointer = c_xml_element_get_attribute_node(temp,name,temp_1);
    if (IFIX(result_pointer) >= (SI_Long)0L)
	return create_xml_node(result_pointer);
    else
	return VALUES_1(Nil);
}

/* C-XML-ELEMENT-HAS-ATTRIBUTE-P */
Object c_xml_element_has_attribute_p(xml_element,name,namespace)
    Object xml_element, name, namespace;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(190,132);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(name);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(namespace);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = name;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = namespace;
    temp = FIX(g2xml_element_has_attribute_p(IFIX(xml_element),temp_1,
	    ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* XML-ELEMENT-HAS-ATTRIBUTE-P */
Object xml_element_has_attribute_p varargs_1(int, n)
{
    Object xml_element, name;
    Object namespace_uri, temp, temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,133);
    INIT_ARGS_nonrelocating();
    xml_element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    namespace_uri = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(xml_element,(SI_Long)1L);
    temp_1 = namespace_uri;
    if (temp_1);
    else
	temp_1 = string_constant_5;
    return VALUES_1(IFIX(c_xml_element_has_attribute_p(temp,name,temp_1)) 
	    != (SI_Long)0L ? T : Nil);
}

/* XML-ELEMENT-GET-INHERITED-ATTRIBUTE */
Object xml_element_get_inherited_attribute varargs_1(int, n)
{
    Object xml_element, name;
    Object namespace_uri, temp, parent_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,134);
    INIT_ARGS_nonrelocating();
    xml_element = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    namespace_uri = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = xml_element_get_attribute(3,xml_element,name,namespace_uri);
    if (temp)
	return VALUES_1(temp);
    else {
	parent_1 = xml_node_parent_node(xml_element);
	if (parent_1)
	    return xml_element_get_inherited_attribute(3,parent_1,name,
		    namespace_uri);
	else
	    return VALUES_1(Nil);
    }
}

/* C-XML-ELEMENT-NEW-NAMESPACE */
Object c_xml_element_new_namespace(xml_element,uri,prefix)
    Object xml_element, uri, prefix;
{
    Object gensymed_symbol, gensymed_symbol_1, temp;
    char *temp_1;

    x_note_fn_call(190,135);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(uri);
    gensymed_symbol_1 = copy_foreign_string_arg_if_appropriate(prefix);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = uri;
    temp_1 = ISTRING(temp);
    temp = gensymed_symbol_1;
    if (temp);
    else
	temp = prefix;
    temp = LONG_TO_FIXNUM(g2xml_element_new_namespace(IFIX(xml_element),
	    temp_1,ISTRING(temp)));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    if (gensymed_symbol_1)
	reclaim_gensym_string(gensymed_symbol_1);
    return VALUES_1(temp);
}

/* XML-ELEMENT-NEW-NAMESPACE */
Object xml_element_new_namespace varargs_1(int, n)
{
    Object xml_element, uri;
    Object prefix, temp, temp_1, result_pointer;
    Declare_varargs_nonrelocating;

    x_note_fn_call(190,136);
    INIT_ARGS_nonrelocating();
    xml_element = REQUIRED_ARG_nonrelocating();
    uri = REQUIRED_ARG_nonrelocating();
    prefix = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() 
	    : Nil;
    END_ARGS_nonrelocating();
    temp = ISVREF(xml_element,(SI_Long)1L);
    temp_1 = prefix;
    if (temp_1);
    else
	temp_1 = string_constant_5;
    result_pointer = c_xml_element_new_namespace(temp,uri,temp_1);
    if (IFIX(result_pointer) >= (SI_Long)0L)
	return create_xml_namespace(result_pointer);
    else
	return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object string_constant_6;   /* "name" */

/* SET-FRAME-NAME-FROM-XML-ELEMENT */
Object set_frame_name_from_xml_element(frame,element)
    Object frame, element;
{
    Object allow_name_box_creation_without_workspace;
    Declare_special(1);
    Object result;

    x_note_fn_call(190,137);
    allow_name_box_creation_without_workspace = T;
    PUSH_SPECIAL_WITH_SYMBOL(Allow_name_box_creation_without_workspace,Qallow_name_box_creation_without_workspace,allow_name_box_creation_without_workspace,
	    0);
      result = change_slot_value(3,frame,Qname_or_names_for_frame,
	      xml_element_get_attribute_symbol(2,element,string_constant_6));
    POP_SPECIAL();
    return result;
}

/* XML-ELEMENT-GET-NAMESPACE-LIST */
Object xml_element_get_namespace_list(xml_document,xml_element)
    Object xml_document, xml_element;
{
    SI_Long result_pointer;

    x_note_fn_call(190,138);
    result_pointer = 
	    g2xml_element_get_namespace_list(IFIX(ISVREF(xml_document,
	    (SI_Long)1L)),IFIX(ISVREF(xml_element,(SI_Long)1L)));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_namespace_list(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* XML-NAMESPACE-LIST-LENGTH */
Object xml_namespace_list_length(xml_namespace_list)
    Object xml_namespace_list;
{
    x_note_fn_call(190,139);
    return VALUES_1(FIX(g2xml_namespace_list_length(IFIX(ISVREF(xml_namespace_list,
	    (SI_Long)1L)))));
}

/* XML-NAMESPACE-LIST-ITEM */
Object xml_namespace_list_item(xml_namespace_list,index_1)
    Object xml_namespace_list, index_1;
{
    SI_Long result_pointer;

    x_note_fn_call(190,140);
    result_pointer = 
	    g2xml_namespace_list_item(IFIX(ISVREF(xml_namespace_list,
	    (SI_Long)1L)),IFIX(index_1));
    if (result_pointer >= (SI_Long)0L)
	return create_xml_namespace(LONG_TO_FIXNUM(result_pointer));
    else
	return VALUES_1(Nil);
}

/* C-XML-NAMESPACE-GET-URI-IN-BUFFER */
Object c_xml_namespace_get_uri_in_buffer(node,buffer,size,start)
    Object node, buffer, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,141);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_namespace_get_uri_in_buffer(IFIX(node),ISTRING(temp),IFIX(size),
	    IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-NAMESPACE-GET-URI */
Object xml_namespace_get_uri(xml_namespace)
    Object xml_namespace;
{
    Object string_buffer, wide_string_value;
    SI_Long true_size_required, temp, size_to_use;

    x_note_fn_call(190,142);
    true_size_required = 
	    g2xml_namespace_get_uri_size(IFIX(ISVREF(xml_namespace,
	    (SI_Long)1L)));
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_namespace_get_uri_in_buffer(ISVREF(xml_namespace,
		(SI_Long)1L),string_buffer,FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	return VALUES_1(wide_string_value);
    }
    else
	return VALUES_1(Nil);
}

/* C-XML-NAMESPACE-GET-PREFIX-IN-BUFFER */
Object c_xml_namespace_get_prefix_in_buffer(node,buffer,size,start)
    Object node, buffer, size, start;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(190,143);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(buffer);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = buffer;
    g2xml_namespace_get_prefix_in_buffer(IFIX(node),ISTRING(temp),
	    IFIX(size),IFIX(start));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

/* XML-NAMESPACE-GET-PREFIX */
Object xml_namespace_get_prefix(xml_namespace)
    Object xml_namespace;
{
    Object string_buffer, wide_string_value;
    SI_Long true_size_required, temp, size_to_use;

    x_note_fn_call(190,144);
    true_size_required = 
	    g2xml_namespace_get_prefix_size(IFIX(ISVREF(xml_namespace,
	    (SI_Long)1L)));
    temp = IFIX(Maximum_length_for_sax_strings);
    size_to_use = MIN(true_size_required,temp);
    if (size_to_use >= (SI_Long)0L) {
	string_buffer = obtain_simple_gensym_string(FIX(size_to_use));
	wide_string_value = Nil;
	c_xml_namespace_get_prefix_in_buffer(ISVREF(xml_namespace,
		(SI_Long)1L),string_buffer,FIX(size_to_use),FIX((SI_Long)0L));
	wide_string_value = import_text_string(2,string_buffer,Qutf_8_string);
	reclaim_simple_gensym_string(string_buffer);
	return VALUES_1(wide_string_value);
    }
    else
	return VALUES_1(Nil);
}

void dom_INIT()
{
    Object temp, reclaim_structure_for_xml_structure_1;
    Object named_dynamic_extent_description, reclaim_structure_for_xml_node_1;
    Object reclaim_structure_for_xml_node_list_1;
    Object reclaim_structure_for_xml_namespace_1;
    Object reclaim_structure_for_xml_namespace_list_1, gensymed_symbol;
    Object AB_package, Qxml_validate_text2;
    Object Qfunction_keeps_procedure_environment_valid_qm, Qxml_validate_file2;
    Object Qxml_validate_text, Qxml_validate_file, Qprint_xml_namespace_list;
    Object Qxml_namespace_list, Qreclaim_structure;
    Object Qoutstanding_xml_namespace_list_count;
    Object Qxml_namespace_list_structure_memory_usage, Qutilities2;
    Object string_constant_17, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_16, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qxml_namespace;
    Object Qoutstanding_xml_namespace_count;
    Object Qxml_namespace_structure_memory_usage, string_constant_15;
    Object string_constant_14, Qprint_xml_node_list, Qprint_xml_node;
    Object Qxml_node_list, Qoutstanding_xml_node_list_count;
    Object Qxml_node_list_structure_memory_usage, string_constant_13;
    Object string_constant_12, Qxml_node, Qoutstanding_xml_node_count;
    Object Qxml_node_structure_memory_usage, string_constant_11;
    Object string_constant_10, Qnamed_dynamic_extent_description, Qdom;
    Object string_constant_9, Qxml_structure, Qoutstanding_xml_structure_count;
    Object Qxml_structure_structure_memory_usage, string_constant_8;
    Object string_constant_7;

    x_note_fn_call(190,145);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_xml_structure_g2_struct = 
	    STATIC_SYMBOL("XML-STRUCTURE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qxml_structure = STATIC_SYMBOL("XML-STRUCTURE",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_xml_structure_g2_struct,
	    Qxml_structure,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qxml_structure,
	    Qg2_defstruct_structure_name_xml_structure_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_xml_structure == UNBOUND)
	The_type_description_of_xml_structure = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m832ry1n832ry8n8k1l8n0000000kmk0k0");
    temp = The_type_description_of_xml_structure;
    The_type_description_of_xml_structure = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_xml_structure_g2_struct,
	    The_type_description_of_xml_structure,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qxml_structure,
	    The_type_description_of_xml_structure,Qtype_description_of_type);
    Qoutstanding_xml_structure_count = 
	    STATIC_SYMBOL("OUTSTANDING-XML-STRUCTURE-COUNT",AB_package);
    Qxml_structure_structure_memory_usage = 
	    STATIC_SYMBOL("XML-STRUCTURE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_8 = STATIC_STRING("1q832ry8s83-xoy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_xml_structure_count);
    push_optimized_constant(Qxml_structure_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_xml_structures = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-XML-STRUCTURES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_xml_structures,
	    Chain_of_available_xml_structures);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_xml_structures,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qxml_structure_count = STATIC_SYMBOL("XML-STRUCTURE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_structure_count,Xml_structure_count);
    record_system_variable(Qxml_structure_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_xml_structures_vector == UNBOUND)
	Chain_of_available_xml_structures_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qxml_structure_structure_memory_usage,
	    STATIC_FUNCTION(xml_structure_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_xml_structure_count,
	    STATIC_FUNCTION(outstanding_xml_structure_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_xml_structure_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_xml_structure,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qxml_structure,
	    reclaim_structure_for_xml_structure_1);
    string_constant_9 = STATIC_STRING("XML-STRUCTURES-EXTENT");
    if (Xml_structures_extent == UNBOUND)
	Xml_structures_extent = make_recursive_lock(2,Kname,string_constant_9);
    Qxml_structures_extent = STATIC_SYMBOL("XML-STRUCTURES-EXTENT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_structures_extent,Xml_structures_extent);
    Qdom = STATIC_SYMBOL("DOM",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qxml_structures_extent,
	    Qdom,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qxml_structures_extent,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    Qcurrent_xml_structures = STATIC_SYMBOL("CURRENT-XML-STRUCTURES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_xml_structures,Current_xml_structures);
    Qg2_defstruct_structure_name_xml_node_g2_struct = 
	    STATIC_SYMBOL("XML-NODE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qxml_node = STATIC_SYMBOL("XML-NODE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_xml_node_g2_struct,
	    Qxml_node,Qab_name_of_unique_structure_type);
    mutate_global_property(Qxml_node,
	    Qg2_defstruct_structure_name_xml_node_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_xml_node == UNBOUND)
	The_type_description_of_xml_node = Nil;
    Qprint_xml_node = STATIC_SYMBOL("PRINT-XML-NODE",AB_package);
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83oky1o83oky832ry8n8k1l832ry0000001n1m8x832ry1m83My83-BNy1m83=0y9kkmk0k0");
    temp = The_type_description_of_xml_node;
    clear_optimized_constants();
    push_optimized_constant(Qprint_xml_node);
    The_type_description_of_xml_node = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_xml_node_g2_struct,
	    The_type_description_of_xml_node,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qxml_node,The_type_description_of_xml_node,
	    Qtype_description_of_type);
    Qoutstanding_xml_node_count = 
	    STATIC_SYMBOL("OUTSTANDING-XML-NODE-COUNT",AB_package);
    Qxml_node_structure_memory_usage = 
	    STATIC_SYMBOL("XML-NODE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_11 = STATIC_STRING("1q83oky8s83-xmy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_xml_node_count);
    push_optimized_constant(Qxml_node_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_xml_nodes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-XML-NODES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_xml_nodes,
	    Chain_of_available_xml_nodes);
    record_system_variable(Qchain_of_available_xml_nodes,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qxml_node_count = STATIC_SYMBOL("XML-NODE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_node_count,Xml_node_count);
    record_system_variable(Qxml_node_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_xml_nodes_vector == UNBOUND)
	Chain_of_available_xml_nodes_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qxml_node_structure_memory_usage,
	    STATIC_FUNCTION(xml_node_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_xml_node_count,
	    STATIC_FUNCTION(outstanding_xml_node_count,NIL,FALSE,0,0));
    reclaim_structure_for_xml_node_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_xml_node,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qxml_node,
	    reclaim_structure_for_xml_node_1);
    Qg2_defstruct_structure_name_xml_node_list_g2_struct = 
	    STATIC_SYMBOL("XML-NODE-LIST-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qxml_node_list = STATIC_SYMBOL("XML-NODE-LIST",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_xml_node_list_g2_struct,
	    Qxml_node_list,Qab_name_of_unique_structure_type);
    mutate_global_property(Qxml_node_list,
	    Qg2_defstruct_structure_name_xml_node_list_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_xml_node_list == UNBOUND)
	The_type_description_of_xml_node_list = Nil;
    Qprint_xml_node_list = STATIC_SYMBOL("PRINT-XML-NODE-LIST",AB_package);
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83oly1o83oly832ry8n8k1l832ry0000001n1m8x832ry1m83My83-BOy1m83=0y9kkmk0k0");
    temp = The_type_description_of_xml_node_list;
    clear_optimized_constants();
    push_optimized_constant(Qprint_xml_node_list);
    The_type_description_of_xml_node_list = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    mutate_global_property(Qg2_defstruct_structure_name_xml_node_list_g2_struct,
	    The_type_description_of_xml_node_list,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qxml_node_list,
	    The_type_description_of_xml_node_list,Qtype_description_of_type);
    Qoutstanding_xml_node_list_count = 
	    STATIC_SYMBOL("OUTSTANDING-XML-NODE-LIST-COUNT",AB_package);
    Qxml_node_list_structure_memory_usage = 
	    STATIC_SYMBOL("XML-NODE-LIST-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_13 = STATIC_STRING("1q83oly8s83-xny09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_xml_node_list_count);
    push_optimized_constant(Qxml_node_list_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_xml_node_lists = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-XML-NODE-LISTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_xml_node_lists,
	    Chain_of_available_xml_node_lists);
    record_system_variable(Qchain_of_available_xml_node_lists,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qxml_node_list_count = STATIC_SYMBOL("XML-NODE-LIST-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_node_list_count,Xml_node_list_count);
    record_system_variable(Qxml_node_list_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_xml_node_lists_vector == UNBOUND)
	Chain_of_available_xml_node_lists_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qxml_node_list_structure_memory_usage,
	    STATIC_FUNCTION(xml_node_list_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_xml_node_list_count,
	    STATIC_FUNCTION(outstanding_xml_node_list_count,NIL,FALSE,0,0));
    reclaim_structure_for_xml_node_list_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_xml_node_list,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qxml_node_list,
	    reclaim_structure_for_xml_node_list_1);
    SET_SYMBOL_FUNCTION(Qprint_xml_node,STATIC_FUNCTION(print_xml_node,NIL,
	    FALSE,3,3));
    SET_SYMBOL_FUNCTION(Qprint_xml_node_list,
	    STATIC_FUNCTION(print_xml_node_list,NIL,FALSE,3,3));
    Qg2_defstruct_structure_name_xml_namespace_g2_struct = 
	    STATIC_SYMBOL("XML-NAMESPACE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qxml_namespace = STATIC_SYMBOL("XML-NAMESPACE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_xml_namespace_g2_struct,
	    Qxml_namespace,Qab_name_of_unique_structure_type);
    mutate_global_property(Qxml_namespace,
	    Qg2_defstruct_structure_name_xml_namespace_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_xml_namespace == UNBOUND)
	The_type_description_of_xml_namespace = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8m83oiy1o83oiy832ry8n8k1l832ry0000001m1m8x832ry1m83My83-BLykmk0k0");
    temp = The_type_description_of_xml_namespace;
    The_type_description_of_xml_namespace = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
    mutate_global_property(Qg2_defstruct_structure_name_xml_namespace_g2_struct,
	    The_type_description_of_xml_namespace,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qxml_namespace,
	    The_type_description_of_xml_namespace,Qtype_description_of_type);
    Qoutstanding_xml_namespace_count = 
	    STATIC_SYMBOL("OUTSTANDING-XML-NAMESPACE-COUNT",AB_package);
    Qxml_namespace_structure_memory_usage = 
	    STATIC_SYMBOL("XML-NAMESPACE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_15 = STATIC_STRING("1q83oiy8s83-xky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_xml_namespace_count);
    push_optimized_constant(Qxml_namespace_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qchain_of_available_xml_namespaces = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-XML-NAMESPACES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_xml_namespaces,
	    Chain_of_available_xml_namespaces);
    record_system_variable(Qchain_of_available_xml_namespaces,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qxml_namespace_count = STATIC_SYMBOL("XML-NAMESPACE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_namespace_count,Xml_namespace_count);
    record_system_variable(Qxml_namespace_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_xml_namespaces_vector == UNBOUND)
	Chain_of_available_xml_namespaces_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qxml_namespace_structure_memory_usage,
	    STATIC_FUNCTION(xml_namespace_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_xml_namespace_count,
	    STATIC_FUNCTION(outstanding_xml_namespace_count,NIL,FALSE,0,0));
    reclaim_structure_for_xml_namespace_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_xml_namespace,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qxml_namespace,
	    reclaim_structure_for_xml_namespace_1);
    Qg2_defstruct_structure_name_xml_namespace_list_g2_struct = 
	    STATIC_SYMBOL("XML-NAMESPACE-LIST-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qxml_namespace_list = STATIC_SYMBOL("XML-NAMESPACE-LIST",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_xml_namespace_list_g2_struct,
	    Qxml_namespace_list,Qab_name_of_unique_structure_type);
    mutate_global_property(Qxml_namespace_list,
	    Qg2_defstruct_structure_name_xml_namespace_list_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_xml_namespace_list == UNBOUND)
	The_type_description_of_xml_namespace_list = Nil;
    Qprint_xml_namespace_list = STATIC_SYMBOL("PRINT-XML-NAMESPACE-LIST",
	    AB_package);
    string_constant_16 = 
	    STATIC_STRING("43Dy8m83ojy1o83ojy832ry8n8k1l832ry0000001n1m8x832ry1m83My83-BMy1m83=0y9kkmk0k0");
    temp = The_type_description_of_xml_namespace_list;
    clear_optimized_constants();
    push_optimized_constant(Qprint_xml_namespace_list);
    The_type_description_of_xml_namespace_list = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    mutate_global_property(Qg2_defstruct_structure_name_xml_namespace_list_g2_struct,
	    The_type_description_of_xml_namespace_list,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qxml_namespace_list,
	    The_type_description_of_xml_namespace_list,
	    Qtype_description_of_type);
    Qoutstanding_xml_namespace_list_count = 
	    STATIC_SYMBOL("OUTSTANDING-XML-NAMESPACE-LIST-COUNT",AB_package);
    Qxml_namespace_list_structure_memory_usage = 
	    STATIC_SYMBOL("XML-NAMESPACE-LIST-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q83ojy8s83-xly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_xml_namespace_list_count);
    push_optimized_constant(Qxml_namespace_list_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_xml_namespace_lists = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-XML-NAMESPACE-LISTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_xml_namespace_lists,
	    Chain_of_available_xml_namespace_lists);
    record_system_variable(Qchain_of_available_xml_namespace_lists,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qxml_namespace_list_count = STATIC_SYMBOL("XML-NAMESPACE-LIST-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qxml_namespace_list_count,
	    Xml_namespace_list_count);
    record_system_variable(Qxml_namespace_list_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_xml_namespace_lists_vector == UNBOUND)
	Chain_of_available_xml_namespace_lists_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qxml_namespace_list_structure_memory_usage,
	    STATIC_FUNCTION(xml_namespace_list_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_xml_namespace_list_count,
	    STATIC_FUNCTION(outstanding_xml_namespace_list_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_xml_namespace_list_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_xml_namespace_list,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qxml_namespace_list,
	    reclaim_structure_for_xml_namespace_list_1);
    SET_SYMBOL_FUNCTION(Qprint_xml_namespace_list,
	    STATIC_FUNCTION(print_xml_namespace_list,NIL,FALSE,3,3));
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qutf_8_string = STATIC_SYMBOL("UTF-8-STRING",AB_package);
    string_constant = STATIC_STRING("~a:~a:");
    string_constant_1 = STATIC_STRING("Line ~a:");
    string_constant_2 = STATIC_STRING("~a:");
    string_constant_3 = STATIC_STRING(" ~a");
    Knil = STATIC_SYMBOL("NIL",Pkeyword);
    string_constant_4 = STATIC_STRING(" ");
    Qxml_element_node = STATIC_SYMBOL("XML-ELEMENT-NODE",AB_package);
    Qxml_attribute_node = STATIC_SYMBOL("XML-ATTRIBUTE-NODE",AB_package);
    Qxml_text_node = STATIC_SYMBOL("XML-TEXT-NODE",AB_package);
    Qxml_cdata_section_node = STATIC_SYMBOL("XML-CDATA-SECTION-NODE",
	    AB_package);
    Qxml_entity_reference_node = STATIC_SYMBOL("XML-ENTITY-REFERENCE-NODE",
	    AB_package);
    Qxml_entity_node = STATIC_SYMBOL("XML-ENTITY-NODE",AB_package);
    Qxml_processing_instruction_node = 
	    STATIC_SYMBOL("XML-PROCESSING-INSTRUCTION-NODE",AB_package);
    Qxml_comment_node = STATIC_SYMBOL("XML-COMMENT-NODE",AB_package);
    Qxml_document_node = STATIC_SYMBOL("XML-DOCUMENT-NODE",AB_package);
    Qxml_document_type_node = STATIC_SYMBOL("XML-DOCUMENT-TYPE-NODE",
	    AB_package);
    Qxml_document_fragment_node = 
	    STATIC_SYMBOL("XML-DOCUMENT-FRAGMENT-NODE",AB_package);
    Qxml_notation_node = STATIC_SYMBOL("XML-NOTATION-NODE",AB_package);
    string_constant_5 = STATIC_STRING("");
    Qxml_validate_file = STATIC_SYMBOL("XML-VALIDATE-FILE",AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qxml_validate_file,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qxml_validate_file,
	    STATIC_FUNCTION(xml_validate_file,NIL,FALSE,1,1));
    Qxml_validate_text = STATIC_SYMBOL("XML-VALIDATE-TEXT",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qxml_validate_text,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qxml_validate_text,
	    STATIC_FUNCTION(xml_validate_text,NIL,FALSE,1,1));
    Qxml_validate_file2 = STATIC_SYMBOL("XML-VALIDATE-FILE2",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qxml_validate_file2,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qxml_validate_file2,
	    STATIC_FUNCTION(xml_validate_file2,NIL,FALSE,2,2));
    Qxml_validate_text2 = STATIC_SYMBOL("XML-VALIDATE-TEXT2",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qxml_validate_text2,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qxml_validate_text2,
	    STATIC_FUNCTION(xml_validate_text2,NIL,FALSE,2,2));
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    string_constant_6 = STATIC_STRING("name");
}
