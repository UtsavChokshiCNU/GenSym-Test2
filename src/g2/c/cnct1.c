/* cnct1.c
 * Input file:  connect1.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "cnct1.h"


Object The_type_description_of_connection = UNBOUND;

Object Chain_of_available_connections = UNBOUND;

Object Connection_count = UNBOUND;

/* CONNECTION-STRUCTURE-MEMORY-USAGE */
Object connection_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(98,0);
    temp = Connection_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CONNECTION-COUNT */
Object outstanding_connection_count()
{
    Object def_structure_connection_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,1);
    gensymed_symbol = IFIX(Connection_count);
    def_structure_connection_variable = Chain_of_available_connections;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_connection_variable))
	goto end_loop;
    def_structure_connection_variable = 
	    ISVREF(def_structure_connection_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CONNECTION-1 */
Object reclaim_connection_1(connection)
    Object connection;
{
    Object svref_new_value;

    x_note_fn_call(98,2);
    inline_note_reclaim_cons(connection,Nil);
    svref_new_value = Chain_of_available_connections;
    SVREF(connection,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_connections = connection;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CONNECTION */
Object reclaim_structure_for_connection(connection)
    Object connection;
{
    x_note_fn_call(98,3);
    return reclaim_connection_1(connection);
}

static Object Qg2_defstruct_structure_name_connection_g2_struct;  /* g2-defstruct-structure-name::connection-g2-struct */

/* MAKE-PERMANENT-CONNECTION-STRUCTURE-INTERNAL */
Object make_permanent_connection_structure_internal()
{
    Object def_structure_connection_variable, connection_count_new_value;
    Object defstruct_g2_connection_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(98,4);
    def_structure_connection_variable = Nil;
    connection_count_new_value = FIXNUM_ADD1(Connection_count);
    Connection_count = connection_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_connection_variable = Nil;
	gensymed_symbol = (SI_Long)12L;
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
	defstruct_g2_connection_variable = the_array;
	SVREF(defstruct_g2_connection_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_connection_g2_struct;
	def_structure_connection_variable = defstruct_g2_connection_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_connection_variable);
}

/* MAKE-CONNECTION-1 */
Object make_connection_1()
{
    Object def_structure_connection_variable;

    x_note_fn_call(98,5);
    def_structure_connection_variable = Chain_of_available_connections;
    if (def_structure_connection_variable) {
	Chain_of_available_connections = 
		ISVREF(def_structure_connection_variable,(SI_Long)0L);
	SVREF(def_structure_connection_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_connection_g2_struct;
    }
    else
	def_structure_connection_variable = 
		make_permanent_connection_structure_internal();
    inline_note_allocate_cons(def_structure_connection_variable,Nil);
    SVREF(def_structure_connection_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)6L)) = Nil;
    ISVREF(def_structure_connection_variable,(SI_Long)7L) = FIX((SI_Long)0L);
    SVREF(def_structure_connection_variable,FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_connection_variable,FIX((SI_Long)10L)) = Nil;
    ISVREF(def_structure_connection_variable,(SI_Long)11L) = FIX((SI_Long)0L);
    return VALUES_1(def_structure_connection_variable);
}

/* CONNECTION-P-FUNCTION */
Object connection_p_function(thing)
    Object thing;
{
    x_note_fn_call(98,6);
    if (SIMPLE_VECTOR_P(thing))
	return VALUES_1(EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct) ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* FRAME-SERIAL-NUMBER-FOR-CONNECTION-FUNCTION */
Object frame_serial_number_for_connection_function(connection)
    Object connection;
{
    x_note_fn_call(98,7);
    return VALUES_1(ISVREF(connection,(SI_Long)10L));
}

Object Savable_connection_flags = UNBOUND;

Object Connection_not_directed_internal_flag = UNBOUND;

Object Connection_permanently_changed_flag = UNBOUND;

Object Connection_has_been_written_flag = UNBOUND;

Object Connection_existed_at_start_of_save_flag = UNBOUND;

Object Connection_overlap_cache_flag = UNBOUND;

Object Connection_overlap_cache_valid_flag = UNBOUND;

Object Transient_connection_flag = UNBOUND;

Object Connection_needs_indexing_flag = UNBOUND;

Object Connection_being_deleted_flag = UNBOUND;

Object Connection_found_in_search_flag = UNBOUND;

/* CLEAR-CONNECTIONS-FOUND-IN-SEARCH */
Object clear_connections_found_in_search(connections)
    Object connections;
{
    Object connection, ab_loop_list_;
    SI_Long svref_new_value;

    x_note_fn_call(98,8);
    connection = Nil;
    ab_loop_list_ = connections;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    svref_new_value = IFIX(ISVREF(connection,(SI_Long)7L)) &  ~(SI_Long)512L;
    ISVREF(connection,(SI_Long)7L) = FIX(svref_new_value);
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

Object Geometric_change_to_connection_is_temporary_p = UNBOUND;

/* NOTE-CHANGE-TO-CONNECTION-1 */
Object note_change_to_connection_1(connection_structure)
    Object connection_structure;
{
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(98,9);
    temp = (SI_Long)0L != (IFIX(ISVREF(connection_structure,(SI_Long)7L)) 
	    & (SI_Long)256L);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection_structure,(SI_Long)7L)) & 
		(SI_Long)128L;
	temp = (SI_Long)0L != gensymed_symbol;
    }
    if ( !temp)
	note_change_of_connection_for_drawing(connection_structure);
    if (Noting_changes_to_kb_p)
	note_change_to_connection_2(connection_structure);
    return VALUES_1(Nil);
}

/* NOTE-DELETION-OF-CONNECTION */
Object note_deletion_of_connection(connection_structure)
    Object connection_structure;
{
    SI_Long svref_new_value;

    x_note_fn_call(98,10);
    if (G2_has_v5_mode_windows_p)
	send_ws_representations_item_remove_as_subblock(connection_structure,
		Nil);
    if ( !((SI_Long)0L != (IFIX(ISVREF(connection_structure,(SI_Long)7L)) 
	    & (SI_Long)256L))) {
	svref_new_value = IFIX(ISVREF(connection_structure,(SI_Long)7L)) | 
		(SI_Long)256L;
	ISVREF(connection_structure,(SI_Long)7L) = FIX(svref_new_value);
	note_deletion_of_connection_for_drawing(connection_structure);
	if (Noting_changes_to_kb_p)
	    note_deletion_of_connection_2(connection_structure);
	invoke_rules_for_direct_connection_chaining(connection_structure,T);
	return invoke_rules_for_indirect_connection_chaining(connection_structure,
		T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* CONNECTION-FRAME-OF-CONNECTION? */
Object connection_frame_of_connection_qm(connection_structure)
    Object connection_structure;
{
    Object frame_or_class, x2;
    char temp;

    x_note_fn_call(98,11);
    frame_or_class = ISVREF(connection_structure,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_class)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(frame_or_class,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	return VALUES_1(frame_or_class);
    else
	return VALUES_1(Nil);
}

/* CONNECTION-CLASS-OF-CONNECTION */
Object connection_class_of_connection(connection_structure)
    Object connection_structure;
{
    Object frame_or_class;

    x_note_fn_call(98,12);
    frame_or_class = ISVREF(connection_structure,(SI_Long)1L);
    if (SYMBOLP(frame_or_class))
	return VALUES_1(frame_or_class);
    else
	return VALUES_1(ISVREF(ISVREF(frame_or_class,(SI_Long)1L),
		(SI_Long)1L));
}

/* WORKSPACE-OF-CONNECTION? */
Object workspace_of_connection_qm(connection_structure)
    Object connection_structure;
{
    Object input_end_qm, output_end_qm, x2, temp_1;
    char temp;

    x_note_fn_call(98,13);
    if ( !TRUEP(connection_structure))
	return VALUES_1(Nil);
    input_end_qm = ISVREF(connection_structure,(SI_Long)3L);
    output_end_qm = ISVREF(connection_structure,(SI_Long)2L);
    if (input_end_qm) {
	if (SIMPLE_VECTOR_P(input_end_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(input_end_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(input_end_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(input_end_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? get_workspace_if_any(input_end_qm) : Nil;
    if (temp_1)
	return VALUES_1(temp_1);
    else {
	if (output_end_qm) {
	    if (SIMPLE_VECTOR_P(output_end_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(output_end_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(output_end_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(output_end_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return get_workspace_if_any(output_end_qm);
	else
	    return VALUES_1(Nil);
    }
}

/* GET-MODULE-CONNECTION-IS-IN */
Object get_module_connection_is_in(connection_structure)
    Object connection_structure;
{
    Object temp;

    x_note_fn_call(98,14);
    temp = get_module_block_is_in(ISVREF(connection_structure,(SI_Long)3L));
    return VALUES_1(temp);
}

/* CONNECTION-WITHIN-MODULE-P */
Object connection_within_module_p(connection_structure,module)
    Object connection_structure, module;
{
    Object temp;

    x_note_fn_call(98,15);
    temp = EQ(get_module_block_is_in(ISVREF(connection_structure,
	    (SI_Long)3L)),module) ? T : Nil;
    return VALUES_1(temp);
}

/* LOOSE-END-P-FUNCTION */
Object loose_end_p_function(frame)
    Object frame;
{
    Object sub_class_bit_vector, temp;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;

    x_note_fn_call(98,16);
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Loose_end_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object The_type_description_of_loose_end_spot = UNBOUND;

Object Chain_of_available_loose_end_spots = UNBOUND;

Object Loose_end_spot_count = UNBOUND;

/* LOOSE-END-SPOT-STRUCTURE-MEMORY-USAGE */
Object loose_end_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(98,17);
    temp = Loose_end_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-LOOSE-END-SPOT-COUNT */
Object outstanding_loose_end_spot_count()
{
    Object def_structure_loose_end_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,18);
    gensymed_symbol = IFIX(Loose_end_spot_count);
    def_structure_loose_end_spot_variable = Chain_of_available_loose_end_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_loose_end_spot_variable))
	goto end_loop;
    def_structure_loose_end_spot_variable = 
	    ISVREF(def_structure_loose_end_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-LOOSE-END-SPOT-1 */
Object reclaim_loose_end_spot_1(loose_end_spot)
    Object loose_end_spot;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(98,19);
    inline_note_reclaim_cons(loose_end_spot,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = loose_end_spot;
    reclaim_structure_if_any(ISVREF(loose_end_spot,(SI_Long)2L));
    SVREF(loose_end_spot,FIX((SI_Long)2L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_loose_end_spots;
    SVREF(loose_end_spot,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_loose_end_spots = loose_end_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-LOOSE-END-SPOT */
Object reclaim_structure_for_loose_end_spot(loose_end_spot)
    Object loose_end_spot;
{
    x_note_fn_call(98,20);
    return reclaim_loose_end_spot_1(loose_end_spot);
}

static Object Qg2_defstruct_structure_name_loose_end_spot_g2_struct;  /* g2-defstruct-structure-name::loose-end-spot-g2-struct */

/* MAKE-PERMANENT-LOOSE-END-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_loose_end_spot_structure_internal()
{
    Object def_structure_loose_end_spot_variable;
    Object loose_end_spot_count_new_value;
    Object defstruct_g2_loose_end_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(98,21);
    def_structure_loose_end_spot_variable = Nil;
    loose_end_spot_count_new_value = FIXNUM_ADD1(Loose_end_spot_count);
    Loose_end_spot_count = loose_end_spot_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_loose_end_spot_variable = Nil;
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
	defstruct_g2_loose_end_spot_variable = the_array;
	SVREF(defstruct_g2_loose_end_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_loose_end_spot_g2_struct;
	SVREF(defstruct_g2_loose_end_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_loose_end_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_loose_end_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_loose_end_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_loose_end_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_loose_end_spot_variable = 
		defstruct_g2_loose_end_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_loose_end_spot_variable);
}

/* MAKE-LOOSE-END-SPOT-1 */
Object make_loose_end_spot_1()
{
    Object def_structure_loose_end_spot_variable;

    x_note_fn_call(98,22);
    def_structure_loose_end_spot_variable = Chain_of_available_loose_end_spots;
    if (def_structure_loose_end_spot_variable) {
	Chain_of_available_loose_end_spots = 
		ISVREF(def_structure_loose_end_spot_variable,(SI_Long)0L);
	SVREF(def_structure_loose_end_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_loose_end_spot_g2_struct;
    }
    else
	def_structure_loose_end_spot_variable = 
		make_permanent_loose_end_spot_structure_internal();
    inline_note_allocate_cons(def_structure_loose_end_spot_variable,Nil);
    SVREF(def_structure_loose_end_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_loose_end_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_loose_end_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_loose_end_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_loose_end_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_loose_end_spot_variable);
}

/* GENERATE-SPOT-FOR-LOOSE-END */
Object generate_spot_for_loose_end(loose_end,mouse_pointer)
    Object loose_end, mouse_pointer;
{
    x_note_fn_call(98,23);
    return push_last_spot(mouse_pointer,make_loose_end_spot_1(),loose_end);
}

/* OUTPUT-CONNECTION-P-FUNCTION */
Object output_connection_p_function(block,connection)
    Object block, connection;
{
    x_note_fn_call(98,24);
    return VALUES_1(EQ(ISVREF(connection,(SI_Long)3L),block) ? T : Nil);
}

/* RENDER-CONNECTION-IN-XOR-OVERLAY-P-FUNCTION */
Object render_connection_in_xor_overlay_p_function(connection)
    Object connection;
{
    Object block, temp;

    x_note_fn_call(98,25);
    block = ISVREF(connection,(SI_Long)3L);
    temp = (SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
	    (SI_Long)1024L) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	block = ISVREF(connection,(SI_Long)2L);
	return VALUES_1((SI_Long)0L != (IFIX(ISVREF(block,(SI_Long)5L)) & 
		(SI_Long)1024L) ? T : Nil);
    }
}

/* WORKSPACE-OF-CONNECTION-FRAME */
Object workspace_of_connection_frame(connection_frame_1)
    Object connection_frame_1;
{
    Object connection_qm;

    x_note_fn_call(98,26);
    connection_qm = ISVREF(connection_frame_1,(SI_Long)21L);
    return workspace_of_connection_qm(connection_qm);
}

Object In_suspend_resume_p = UNBOUND;

static Object Qconnection;         /* connection */

/* DEACTIVATE-FOR-CONNECTION */
Object deactivate_for_connection(connection)
    Object connection;
{
    Object current_computation_flags, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(98,27);
    if ( !TRUEP(In_suspend_resume_p)) {
	if ((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)5L)) & 
		(SI_Long)1L)) {
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL(Current_computation_flags,current_computation_flags,
		    0);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	      decache_roles_for_entities_related_to_this_connection(ISVREF(connection,
		      (SI_Long)21L));
	    POP_SPECIAL();
	}
    }
    frame = connection;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)7L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qconnection)) {
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
    return VALUES_1(Nil);
}

/* ACTIVATE-FOR-CONNECTION */
Object activate_for_connection(connection)
    Object connection;
{
    Object current_computation_flags, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);

    x_note_fn_call(98,28);
    if ( !TRUEP(In_suspend_resume_p)) {
	if ( !((SI_Long)0L != (IFIX(ISVREF(connection,(SI_Long)5L)) & 
		(SI_Long)1L))) {
	    current_computation_flags = Current_computation_flags;
	    PUSH_SPECIAL(Current_computation_flags,current_computation_flags,
		    0);
	      Current_computation_flags = 
		      FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	      decache_roles_for_entities_related_to_this_connection(ISVREF(connection,
		      (SI_Long)21L));
	    POP_SPECIAL();
	}
    }
    frame = connection;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)6L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qconnection)) {
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
    return VALUES_1(Nil);
}

/* GET-CROSS-SECTION-REGIONS-FUNCTION */
Object get_cross_section_regions_function(cross_section_pattern)
    Object cross_section_pattern;
{
    Object temp;

    x_note_fn_call(98,29);
    temp = CAAR(cross_section_pattern);
    if (CONSP(temp))
	return VALUES_1(CAR(cross_section_pattern));
    else
	return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* CONNECTION-POST-EQUAL */
Object connection_post_equal(connection_post_1,connection_post_2)
    Object connection_post_1, connection_post_2;
{
    Object temp, name_or_names_1, name_or_names_2;

    x_note_fn_call(98,30);
    temp = EQ(connection_post_1,connection_post_2) ? T : Nil;
    if (temp);
    else {
	name_or_names_1 = 
		get_lookup_slot_value_given_default(connection_post_1,
		Qname_or_names_for_frame,Nil);
	name_or_names_2 = 
		get_lookup_slot_value_given_default(connection_post_2,
		Qname_or_names_for_frame,Nil);
	temp = name_or_names_like_p(name_or_names_1,name_or_names_2);
    }
    return VALUES_1(temp);
}

static Object Qconnection_post;    /* connection-post */

static Object Qsuperior_connection_cache;  /* superior-connection-cache */

static Object Qinput;              /* input */

/* CLEANUP-FOR-CONNECTION-POST */
Object cleanup_for_connection_post(connection_post)
    Object connection_post;
{
    Object frame, sub_vector_qm, method_function_qm, superior_connection_cache;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(98,31);
    frame = connection_post;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qconnection_post)) {
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
    superior_connection_cache = 
	    get_lookup_slot_value_given_default(connection_post,
	    Qsuperior_connection_cache,Nil);
    if (superior_connection_cache)
	return remove_subworkspace_connection_post_from_connection(CDR(superior_connection_cache),
		connection_post,EQ(CAR(superior_connection_cache),Qinput) ?
		 T : Nil,T);
    else
	return VALUES_1(Nil);
}

/* NOTE-NAME-CHANGE-FOR-CONNECTION-POST */
Object note_name_change_for_connection_post(connection_post,old_names,
	    initializing_p)
    Object connection_post, old_names, initializing_p;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(98,32);
    if ( !TRUEP(initializing_p))
	decache_roles_for_connection_post_and_namesakes(connection_post,
		old_names);
    frame = connection_post;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)10L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qconnection_post)) {
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
    if ( !TRUEP(initializing_p))
	return decache_roles_for_connection_post_and_namesakes(connection_post,
		get_lookup_slot_value_given_default(connection_post,
		Qname_or_names_for_frame,Nil));
    else
	return VALUES_1(Nil);
}

/* CHANGE-CONNECTION-ATTRIBUTE */
Object change_connection_attribute(connection,indicator,value_qm)
    Object connection, indicator, value_qm;
{
    SI_Long gensymed_symbol;
    char temp;

    x_note_fn_call(98,33);
    temp = TRUEP(Noting_changes_to_kb_p);
    if (temp);
    else {
	gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & (SI_Long)128L;
	temp =  !((SI_Long)0L != gensymed_symbol) ?  
		!TRUEP(Geometric_change_to_connection_is_temporary_p) : 
		TRUEP(Nil);
    }
    if (temp)
	note_change_to_connection_1(connection);
    return change_connection_attribute_1(connection,indicator,value_qm);
}

/* CHANGE-CONNECTION-ATTRIBUTE-1 */
Object change_connection_attribute_1(connection,indicator,value_qm)
    Object connection, indicator, value_qm;
{
    Object l_trailer_qm, l, temp;

    x_note_fn_call(98,34);
    l_trailer_qm = Nil;
    l = ISVREF(connection,(SI_Long)9L);
  next_loop:
    if ( !TRUEP(l))
	goto end_loop;
    if (EQ(CAR(l),indicator)) {
	if (value_qm) {
	    reclaim_slot_value(CADR(l));
	    M_CADR(l) = value_qm;
	}
	else {
	    if (l_trailer_qm) {
		temp = CDDR(l);
		M_CDR(l_trailer_qm) = temp;
	    }
	    else {
		temp = CDDR(l);
		SVREF(connection,FIX((SI_Long)9L)) = temp;
	    }
	    M_CDDR(l) = Nil;
	    reclaim_slot_value(l);
	}
	return VALUES_1(value_qm);
    }
    l_trailer_qm = CDR(l);
    l = CDR(l_trailer_qm);
    goto next_loop;
  end_loop:
    if (value_qm) {
	temp = gensym_cons_1(indicator,gensym_cons_1(value_qm,
		ISVREF(connection,(SI_Long)9L)));
	SVREF(connection,FIX((SI_Long)9L)) = temp;
    }
    return VALUES_1(value_qm);
    return VALUES_1(Qnil);
}

static Object Qconnection_arrows;  /* connection-arrows */

/* CONNECTION-ARROWS-OF-CONNECTION */
Object connection_arrows_of_connection(connection)
    Object connection;
{
    Object plist;

    x_note_fn_call(98,35);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist)
	return getfq_function_no_default(plist,Qconnection_arrows);
    else
	return VALUES_1(Nil);
}

static Object Qline_pattern;       /* line-pattern */

/* CONNECTION-LINE-PATTERN */
Object connection_line_pattern(connection)
    Object connection;
{
    Object plist;

    x_note_fn_call(98,36);
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist)
	return getfq_function_no_default(plist,Qline_pattern);
    else
	return VALUES_1(Nil);
}

/* COMPUTE-SCALED-LINE-PATTERN */
Object compute_scaled_line_pattern(line_pattern,scale,total_width)
    Object line_pattern, scale, total_width;
{
    Object dashes, absolutep, result_1, dash, ab_loop_list_, length_1;
    Object ab_loop_list__1, temp, value, on, off, ab_loopvar_;
    Object ab_loop_maxmin_fl_, minoff, offcons;
    SI_Long unshifted_result;
    char temp_1;

    x_note_fn_call(98,37);
    if (line_pattern) {
	dashes = connection_line_pattern_dashes(line_pattern);
	absolutep = connection_line_pattern_absolute_p(line_pattern);
	result_1 = Nil;
	dash = Nil;
	ab_loop_list_ = dashes;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	dash = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SYMBOLP(dash)) {
	    length_1 = Nil;
	    ab_loop_list__1 = lookup_stock_line_pattern_element(dash);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    length_1 = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if (absolutep) {
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = length_1;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			length_1) && FIXNUM_LT(length_1,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,length_1)) 
			    + (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(scale,length_1);
	    }
	    else {
		value = FIXNUM_TIMES(length_1,total_width);
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(scale,value);
	    }
	    result_1 = gensym_cons_1(temp,result_1);
	    goto next_loop_1;
	  end_loop_1:;
	}
	else if (FIXNUMP(dash)) {
	    if (absolutep) {
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = dash;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			dash) && FIXNUM_LT(dash,
			    Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,dash)) + 
			    (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(scale,dash);
	    }
	    else {
		value = FIXNUM_TIMES(dash,total_width);
		if (IFIX(scale) == (SI_Long)4096L)
		    temp = value;
		else if (FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			scale) && FIXNUM_LT(scale,
			Isqrt_of_most_positive_fixnum) && 
			FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			value) && FIXNUM_LT(value,
			Isqrt_of_most_positive_fixnum)) {
		    unshifted_result = IFIX(FIXNUM_TIMES(scale,value)) + 
			    (SI_Long)2048L;
		    temp = FIX(unshifted_result >>  -  - (SI_Long)12L);
		}
		else
		    temp = scalef_function(scale,value);
	    }
	    result_1 = gensym_cons_1(temp,result_1);
	}
	else;
	goto next_loop;
      end_loop:;
	result_1 = nreverse(result_1);
	length_1 = Nil;
	ab_loop_list_ = result_1;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	length_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !(IFIX(length_1) == (SI_Long)0L)) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
	if (temp_1)
	    return VALUES_1(Nil);
	else if (connection_line_pattern_explicit_p(line_pattern))
	    return VALUES_1(result_1);
	else {
	    on = Nil;
	    off = Nil;
	    ab_loop_list_ = result_1;
	    ab_loopvar_ = FIX((SI_Long)0L);
	    ab_loop_maxmin_fl_ = T;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	  next_loop_3:
	    on = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    off = CAR(temp);
	    if (ab_loop_maxmin_fl_) {
		ab_loop_maxmin_fl_ = Nil;
		ab_loopvar_ = off;
	    }
	    else
		ab_loopvar_ = lmin(ab_loopvar_,off);
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    goto next_loop_3;
	  end_loop_3:
	    minoff = ab_loopvar_;
	    goto end_2;
	    minoff = Qnil;
	  end_2:;
	    offcons = CDR(result_1);
	  next_loop_4:
	    if ( !TRUEP(offcons))
		goto end_loop_4;
	    M_CAR(offcons) = minoff;
	    offcons = CDDR(offcons);
	    goto next_loop_4;
	  end_loop_4:;
	    return VALUES_1(result_1);
	}
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_connection_item = UNBOUND;

Object Chain_of_available_connection_items = UNBOUND;

Object Connection_item_count = UNBOUND;

/* CONNECTION-ITEM-STRUCTURE-MEMORY-USAGE */
Object connection_item_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(98,38);
    temp = Connection_item_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CONNECTION-ITEM-COUNT */
Object outstanding_connection_item_count()
{
    Object def_structure_connection_item_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,39);
    gensymed_symbol = IFIX(Connection_item_count);
    def_structure_connection_item_variable = 
	    Chain_of_available_connection_items;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_connection_item_variable))
	goto end_loop;
    def_structure_connection_item_variable = 
	    ISVREF(def_structure_connection_item_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CONNECTION-ITEM-1 */
Object reclaim_connection_item_1(connection_item)
    Object connection_item;
{
    Object svref_new_value;

    x_note_fn_call(98,40);
    inline_note_reclaim_cons(connection_item,Nil);
    svref_new_value = Chain_of_available_connection_items;
    SVREF(connection_item,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_connection_items = connection_item;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CONNECTION-ITEM */
Object reclaim_structure_for_connection_item(connection_item)
    Object connection_item;
{
    x_note_fn_call(98,41);
    return reclaim_connection_item_1(connection_item);
}

/* MAKE-PERMANENT-CONNECTION-ITEM-STRUCTURE-INTERNAL */
Object make_permanent_connection_item_structure_internal()
{
    Object def_structure_connection_item_variable, the_array;
    Object defstruct_g2_connection_item_variable, svref_new_value;
    SI_Long connection_item_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(98,42);
    def_structure_connection_item_variable = Nil;
    connection_item_count_new_value = IFIX(Connection_item_count) + 
	    (SI_Long)100L;
    Connection_item_count = FIX(connection_item_count_new_value);
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	gensymed_symbol_1 = (SI_Long)6L;
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
	defstruct_g2_connection_item_variable = the_array;
	def_structure_connection_item_variable = 
		defstruct_g2_connection_item_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	svref_new_value = Chain_of_available_connection_items;
	SVREF(def_structure_connection_item_variable,FIX((SI_Long)0L)) = 
		svref_new_value;
	Chain_of_available_connection_items = 
		def_structure_connection_item_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_connection_item_variable);
}

/* MAKE-CONNECTION-ITEM-1 */
Object make_connection_item_1(connection_item_connection)
    Object connection_item_connection;
{
    Object def_structure_connection_item_variable;

    x_note_fn_call(98,43);
    def_structure_connection_item_variable = 
	    Chain_of_available_connection_items;
    if (def_structure_connection_item_variable)
	Chain_of_available_connection_items = 
		ISVREF(def_structure_connection_item_variable,(SI_Long)0L);
    else
	def_structure_connection_item_variable = 
		make_permanent_connection_item_structure_internal();
    inline_note_allocate_cons(def_structure_connection_item_variable,Nil);
    SVREF(def_structure_connection_item_variable,FIX((SI_Long)0L)) = 
	    connection_item_connection;
    SVREF(def_structure_connection_item_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_connection_item_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_connection_item_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_connection_item_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_connection_item_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_connection_item_variable);
}

static Object Qab_gensym;          /* gensym */

/* RECLAIM-CONNECTION-ITEM-TABLE-LEAVES */
Object reclaim_connection_item_table_leaves(connection_item_table_binary_tree)
    Object connection_item_table_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(98,44);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(connection_item_table_binary_tree))
	goto end_loop;
    less_than_branch_qm = ISVREF(connection_item_table_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = ISVREF(connection_item_table_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(connection_item_table_binary_tree,(SI_Long)3L);
    reclaim_binary_tree_element_1(connection_item_table_binary_tree);
    alist_entry = Nil;
    ab_loop_list_ = alist;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    alist_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    inline_note_reclaim_cons(alist_entry,Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(alist_entry) = cdr_new_value;
    Available_gensym_conses = alist_entry;
    goto next_loop_1;
  end_loop_1:;
    if (alist) {
	last_1 = alist;
	next_qm = Nil;
      next_loop_2:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop_2;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop_2;
      end_loop_2:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	Available_gensym_conses = alist;
    }
    if (less_than_branch_qm && greater_than_branch_qm) {
	reclaim_connection_item_table_leaves(less_than_branch_qm);
	connection_item_table_binary_tree = greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	connection_item_table_binary_tree = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-CONNECTION-ITEM-TABLE-TREE */
Object clear_connection_item_table_tree(connection_item_table_binary_tree)
    Object connection_item_table_binary_tree;
{
    Object element_qm;

    x_note_fn_call(98,45);
    element_qm = CDR(connection_item_table_binary_tree);
    if (element_qm) {
	reclaim_connection_item_table_leaves(element_qm);
	M_CDR(connection_item_table_binary_tree) = Nil;
    }
    return VALUES_1(connection_item_table_binary_tree);
}

/* CONNECTION-ITEM-NAME-OR-NAMES */
Object connection_item_name_or_names(connection_item)
    Object connection_item;
{
    Object temp;

    x_note_fn_call(98,46);
    temp = copy_list_using_scope_conses(ISVREF(connection_item,(SI_Long)1L));
    temp = nconc2(temp,copy_list_using_scope_conses(ISVREF(connection_item,
	    (SI_Long)2L)));
    return VALUES_1(temp);
}

static Object Qconnection_item_table;  /* connection-item-table */

/* UPGRADE-CONNECTIONS */
Object upgrade_connections(connections)
    Object connections;
{
    Object new_cons, gensymed_symbol, connection_item_table;
    Object current_connection_names, connection_or_name, ab_loop_list_;
    Object gensymed_symbol_1, gensymed_symbol_4, old_connection_item_qm;
    Object new_connection_item, svref_new_value, temp;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(98,47);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qconnection_item_table;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    connection_item_table = gensymed_symbol;
    current_connection_names = Nil;
    connection_or_name = Nil;
    ab_loop_list_ = connections;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    connection_or_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (SYMBOLP(connection_or_name))
	current_connection_names = gensym_cons_1(connection_or_name,
		current_connection_names);
    else if (SIMPLE_VECTOR_P(connection_or_name) && 
	    EQ(ISVREF(connection_or_name,(SI_Long)0L),
	    Qg2_defstruct_structure_name_connection_g2_struct)) {
	gensymed_symbol = CDR(connection_item_table);
	gensymed_symbol_1 = connection_or_name;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(connection_or_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_1;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_2 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_2 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_2:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_2;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		old_connection_item_qm = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:
	    old_connection_item_qm = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	old_connection_item_qm = Qnil;
      end_2:;
	new_connection_item =  !TRUEP(old_connection_item_qm) ? 
		make_connection_item_1(connection_or_name) : Nil;
	if (old_connection_item_qm) {
	    svref_new_value = nreverse(current_connection_names);
	    SVREF(old_connection_item_qm,FIX((SI_Long)2L)) = svref_new_value;
	    SVREF(old_connection_item_qm,FIX((SI_Long)3L)) = T;
	    current_connection_names = Nil;
	}
	else {
	    svref_new_value = nreverse(current_connection_names);
	    SVREF(new_connection_item,FIX((SI_Long)1L)) = svref_new_value;
	    current_connection_names = Nil;
	    gensymed_symbol = connection_or_name;
	    set_balanced_binary_tree_entry(connection_item_table,Qeq,Nil,T,
		    gensymed_symbol,FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum)),new_connection_item);
	}
    }
    else;
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(connections);
    temp = connection_item_table;
    goto end_3;
    temp = Qnil;
  end_3:;
    return VALUES_1(temp);
}

/* UPGRADE-BLOCK-CONNECTIONS */
Object upgrade_block_connections(block)
    Object block;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_next_node_qm_, ab_current_alist_, ab_entry_cons_, connection;
    Object connection_item, duplicated_qm, ab_less_than_branch_qm_;
    Object svref_old_value, svref_new_value;
    Declare_special(1);

    x_note_fn_call(98,48);
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(block,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_next_node_qm_ = gensymed_symbol;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    connection = Nil;
    connection_item = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      duplicated_qm = Nil;
      ab_next_node_qm_ = M_CDR(ab_next_node_qm_);
    next_loop:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else {
	  if (ab_next_node_qm_) {
	      ab_current_node_ = ab_next_node_qm_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_1:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_1;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_qm_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_qm_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_1;
      connection = CAR(ab_entry_cons_);
      connection_item = CDR(ab_entry_cons_);
      duplicated_qm = ISVREF(connection_item,(SI_Long)3L);
      if ( !TRUEP(duplicated_qm) && EQ(Qinput,
	      get_direction_of_connection(2,connection,block))) {
	  svref_old_value = ISVREF(connection_item,(SI_Long)2L);
	  svref_new_value = ISVREF(connection_item,(SI_Long)1L);
	  SVREF(connection_item,FIX((SI_Long)2L)) = svref_new_value;
	  SVREF(connection_item,FIX((SI_Long)1L)) = Nil;
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* DOWNGRADE-CONNECTIONS */
Object downgrade_connections(connections)
    Object connections;
{
    Object scope_conses, ab_node_stack_, ab_current_node_, ab_next_node_qm_;
    Object ab_current_alist_, ab_entry_cons_, connection, connection_item;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_less_than_branch_qm_;
    Object temp, temp_1, names;
    Declare_special(1);

    x_note_fn_call(98,49);
    if (connections) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_next_node_qm_ = connections;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	connection = Nil;
	connection_item = Nil;
	PUSH_SPECIAL(Scope_conses,scope_conses,0);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	  ab_next_node_qm_ = M_CDR(ab_next_node_qm_);
	next_loop:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else {
	      if (ab_next_node_qm_) {
		  ab_current_node_ = ab_next_node_qm_;
		  ab_less_than_branch_qm_ = Nil;
		next_loop_1:
		  ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			  (SI_Long)1L);
		  if ( !TRUEP(ab_less_than_branch_qm_))
		      goto end_loop;
		  ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		  ab_current_node_ = ab_less_than_branch_qm_;
		  goto next_loop_1;
		end_loop:;
	      }
	      else if (ab_node_stack_) {
		  ab_next_node_qm_ = ab_node_stack_;
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      else
		  ab_current_node_ = Nil;
	      if (ab_current_node_) {
		  ab_next_node_qm_ = ISVREF(ab_current_node_,(SI_Long)2L);
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_1;
	  connection = CAR(ab_entry_cons_);
	  connection_item = CDR(ab_entry_cons_);
	  if (ISVREF(connection_item,(SI_Long)3L)) {
	      temp = 
		      copy_list_using_gensym_conses_1(ISVREF(connection_item,
		      (SI_Long)1L));
	      temp_1 = gensym_cons_1(ISVREF(connection_item,(SI_Long)0L),Nil);
	      ab_loopvar__2 = nconc2(temp,nconc2(temp_1,
		      nconc2(copy_list_using_gensym_conses_1(ISVREF(connection_item,
		      (SI_Long)2L)),gensym_cons_1(ISVREF(connection_item,
		      (SI_Long)0L),Nil))));
	  }
	  else {
	      names = 
		      nconc2(copy_list_using_gensym_conses_1(ISVREF(connection_item,
		      (SI_Long)1L)),
		      copy_list_using_gensym_conses_1(ISVREF(connection_item,
		      (SI_Long)2L)));
	      ab_loopvar__2 = nconc2(names,
		      gensym_cons_1(ISVREF(connection_item,(SI_Long)0L),Nil));
	  }
	  if (ab_loopvar__2) {
	      if (ab_loopvar__1)
		  M_CDR(ab_loopvar__1) = ab_loopvar__2;
	      else
		  ab_loopvar_ = ab_loopvar__2;
	      ab_loopvar__1 = last(ab_loopvar__2,_);
	  }
	  goto next_loop;
	end_loop_1:
	  temp_1 = ab_loopvar_;
	  goto end_1;
	  temp_1 = Qnil;
	end_1:;
	POP_SPECIAL();
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* CONNECTION-STRUCTURES */
Object connection_structures(item)
    Object item;
{
    Object result_1, scope_conses, ab_node_stack_, ab_current_node_;
    Object gensymed_symbol, ab_skip_list_form_, ab_skip_list_p_, ab_next_node_;
    Object ab_tail_node_, ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, elt_1, temp, ab_less_than_branch_qm_;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,50);
    result_1 = Nil;
    scope_conses = Scope_conses;
    ab_node_stack_ = Nil;
    ab_current_node_ = Nil;
    gensymed_symbol = ISVREF(item,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)6L) : Nil;
    ab_skip_list_form_ = gensymed_symbol;
    ab_skip_list_p_ = Nil;
    ab_next_node_ = Nil;
    ab_tail_node_ = Nil;
    ab_current_alist_ = Nil;
    ab_entry_cons_ = Nil;
    ab_connection_ = Nil;
    ab_connection_item_ = Nil;
    elt_1 = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      gensymed_symbol = CDR(ab_skip_list_form_);
      if (CONSP(gensymed_symbol)) {
	  temp = M_CAR(gensymed_symbol);
	  temp_1 = SIMPLE_VECTOR_P(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  temp = M_CDR(gensymed_symbol);
	  ab_skip_list_p_ = SIMPLE_VECTOR_P(temp) ? T : Nil;
      }
      else
	  ab_skip_list_p_ = Nil;
      if (ab_skip_list_p_) {
	  ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		  (SI_Long)0L),(SI_Long)0L);
	  ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	  if (EQ(ab_next_node_,ab_tail_node_))
	      ab_next_node_ = Nil;
      }
      else
	  ab_next_node_ = CDR(ab_skip_list_form_);
    next_loop:
    next_loop_1:
      if (ab_current_alist_) {
	  ab_entry_cons_ = M_CAR(ab_current_alist_);
	  ab_connection_ = M_CAR(ab_entry_cons_);
	  ab_connection_item_ = M_CDR(ab_entry_cons_);
	  ab_current_alist_ = M_CDR(ab_current_alist_);
      }
      else if (ab_skip_list_p_) {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_next_node_ = ISVREF(ISVREF(ab_current_node_,(SI_Long)0L),
		      (SI_Long)0L);
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	      ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	  }
	  else
	      ab_current_node_ = Nil;
      }
      else {
	  if (ab_next_node_) {
	      ab_current_node_ = ab_next_node_;
	      ab_less_than_branch_qm_ = Nil;
	    next_loop_2:
	      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
	      if ( !TRUEP(ab_less_than_branch_qm_))
		  goto end_loop;
	      ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
	      ab_current_node_ = ab_less_than_branch_qm_;
	      goto next_loop_2;
	    end_loop:;
	  }
	  else if (ab_node_stack_) {
	      ab_next_node_ = ab_node_stack_;
	      ab_current_node_ = M_CAR(ab_node_stack_);
	      ab_node_stack_ = M_CDR(ab_node_stack_);
	  }
	  else
	      ab_current_node_ = Nil;
	  if (ab_current_node_) {
	      ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_connection_ = M_CAR(ab_entry_cons_);
	      ab_connection_item_ = M_CDR(ab_entry_cons_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
      }
      if ( !TRUEP(ab_current_node_) || ab_current_node_ && ab_connection_)
	  goto end_1;
      goto next_loop_1;
    end_loop_1:
    end_1:
      if ( !TRUEP(ab_current_node_))
	  goto end_loop_2;
      elt_1 = ab_connection_;
      result_1 = gensym_cons_1(elt_1,result_1);
      goto next_loop;
    end_loop_2:
      result = nreverse(result_1);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

static Object Qinput_1;            /* input-1 */

/* PUT-CONTROL-BLOCK-INPUT-WHERE-SLOT-IS-ABSENT */
Object put_control_block_input_where_slot_is_absent(control_block,slot_value)
    Object control_block, slot_value;
{
    x_note_fn_call(98,51);
    put_attribute_value(4,control_block,Qinput_1,slot_value,T);
    return VALUES_1(Nil);
}

/* PUT-CONTROL-BLOCK-INPUT-1-WHERE-SLOT-IS-ABSENT */
Object put_control_block_input_1_where_slot_is_absent(control_block,slot_value)
    Object control_block, slot_value;
{
    x_note_fn_call(98,52);
    put_attribute_value(4,control_block,Qinput_1,slot_value,T);
    return VALUES_1(Nil);
}

static Object Qinput_2;            /* input-2 */

/* PUT-CONTROL-BLOCK-INPUT-2-WHERE-SLOT-IS-ABSENT */
Object put_control_block_input_2_where_slot_is_absent(control_block,slot_value)
    Object control_block, slot_value;
{
    x_note_fn_call(98,53);
    put_attribute_value(4,control_block,Qinput_2,slot_value,T);
    return VALUES_1(Nil);
}

static Object Qoutput_1;           /* output-1 */

/* PUT-CONTROL-BLOCK-OUTPUT-WHERE-SLOT-IS-ABSENT */
Object put_control_block_output_where_slot_is_absent(control_block,slot_value)
    Object control_block, slot_value;
{
    x_note_fn_call(98,54);
    put_attribute_value(4,control_block,Qoutput_1,slot_value,T);
    return VALUES_1(Nil);
}

Object Dont_include_offset_for_end_position_qm = UNBOUND;

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qcross_section_pattern;  /* cross-section-pattern */

/* CONNECTION-STRIPED-P */
Object connection_striped_p(connection)
    Object connection;
{
    Object connection_frame_or_class, x2, cross_section_pattern;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4, temp_1;
    Object temp_2, new_cons, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, cross_section_stripes;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(98,55);
    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_or_class,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	cross_section_pattern = ISVREF(connection_frame_or_class,(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(connection_frame_or_class,
		Class_description_gkbprop)) {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = connection_frame_or_class;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(connection_frame_or_class) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_1:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_1;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_1;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_1;
	      end_loop_1:
		gensymed_symbol = Qnil;
	      end_1:;
		goto end_2;
	    }
	    goto next_loop;
	  end_loop:
	    gensymed_symbol = Qnil;
	  end_2:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = connection_frame_or_class;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_1,
			Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_2:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_2;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_3:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_3;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_3;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_3;
	      end_loop_3:
		kb_properties = Qnil;
	      end_3:;
		goto end_4;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    kb_properties = Qnil;
	  end_4:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_4:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_4;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_5:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_5;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_5;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_5;
		  end_loop_5:
		    kb_specific_value = Qnil;
		  end_5:;
		    goto end_6;
		}
		goto next_loop_4;
	      end_loop_4:
		kb_specific_value = Qnil;
	      end_6:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_6:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_6;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_7:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_7;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_7;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_7;
		  end_loop_7:
		    resulting_value = Qnil;
		  end_7:;
		    goto end_8;
		}
		goto next_loop_6;
	      end_loop_6:
		resulting_value = Qnil;
	      end_8:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	else {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qconnection;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_8:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_8;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_9:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_9;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_9;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_9;
	      end_loop_9:
		gensymed_symbol = Qnil;
	      end_9:;
		goto end_10;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    gensymed_symbol = Qnil;
	  end_10:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_1,
			Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_10:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_10;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_11:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_11;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_11;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_11;
	      end_loop_11:
		kb_properties = Qnil;
	      end_11:;
		goto end_12;
	    }
	    goto next_loop_10;
	  end_loop_10:
	    kb_properties = Qnil;
	  end_12:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_12:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_12;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_13:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_13;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_13;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_13;
		  end_loop_13:
		    kb_specific_value = Qnil;
		  end_13:;
		    goto end_14;
		}
		goto next_loop_12;
	      end_loop_12:
		kb_specific_value = Qnil;
	      end_14:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_14:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_14;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_15:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_15;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_15;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_15;
		  end_loop_15:
		    resulting_value = Qnil;
		  end_15:;
		    goto end_16;
		}
		goto next_loop_14;
	      end_loop_14:
		resulting_value = Qnil;
	      end_16:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	cross_section_pattern = ISVREF(temp_2,(SI_Long)6L);
    }
    temp_2 = CAAR(cross_section_pattern);
    cross_section_stripes = CONSP(temp_2) ? CDR(cross_section_pattern) : 
	    cross_section_pattern;
    return VALUES_1( ! !TRUEP(CDR(cross_section_stripes)) ? T : Nil);
}

static Object Qstripe_color;       /* stripe-color */

/* GET-CONNECTION-COLOR */
Object get_connection_color(connection_frame_1,region)
    Object connection_frame_1, region;
{
    Object x2, cross_section_pattern_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_4, temp_1, temp_2, new_cons, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    Object cross_section_regions_qm, entry_qm;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(98,56);
    if (SIMPLE_VECTOR_P(connection_frame_1) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_1)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(connection_frame_1,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(connection_frame_1,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	cross_section_pattern_qm = ISVREF(connection_frame_1,(SI_Long)20L);
    else {
	if (lookup_global_or_kb_specific_property_value(connection_frame_1,
		Class_description_gkbprop)) {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = connection_frame_1;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(connection_frame_1) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_1:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_1;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_1;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_1;
	      end_loop_1:
		gensymed_symbol = Qnil;
	      end_1:;
		goto end_2;
	    }
	    goto next_loop;
	  end_loop:
	    gensymed_symbol = Qnil;
	  end_2:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = connection_frame_1;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_1,
			Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_2:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_2;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_3:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_3;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_3;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_3;
	      end_loop_3:
		kb_properties = Qnil;
	      end_3:;
		goto end_4;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    kb_properties = Qnil;
	  end_4:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_4:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_4;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_5:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_5;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_5;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_5;
		  end_loop_5:
		    kb_specific_value = Qnil;
		  end_5:;
		    goto end_6;
		}
		goto next_loop_4;
	      end_loop_4:
		kb_specific_value = Qnil;
	      end_6:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_6:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_6;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_7:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_7;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_7;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_7;
		  end_loop_7:
		    resulting_value = Qnil;
		  end_7:;
		    goto end_8;
		}
		goto next_loop_6;
	      end_loop_6:
		resulting_value = Qnil;
	      end_8:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	else {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = Qconnection;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Qconnection) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_8:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_8;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_9:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_9;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    gensymed_symbol = M_CDR(M_CAR(gensymed_symbol));
		    goto end_9;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_9;
	      end_loop_9:
		gensymed_symbol = Qnil;
	      end_9:;
		goto end_10;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    gensymed_symbol = Qnil;
	  end_10:;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = Qconnection;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		new_cons = Available_gensym_conses;
		if (new_cons) {
		    Available_gensym_conses = M_CDR(new_cons);
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_gensym_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		M_CDR(gensymed_symbol_1) = Nil;
		inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		gensymed_symbol = set_balanced_binary_tree_entry(temp_1,
			Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    gensymed_symbol = CDR(global_properties);
	    gensymed_symbol_1 = 
		    Current_kb_specific_property_list_property_name;
	    gensymed_symbol_2 = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    gensymed_symbol_3 = (SI_Long)0L;
	  next_loop_10:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_10;
	    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_2 < gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_2 > gensymed_symbol_3)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_4 = Nil;
	      next_loop_11:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_11;
		gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
		    kb_properties = M_CDR(M_CAR(gensymed_symbol));
		    goto end_11;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_11;
	      end_loop_11:
		kb_properties = Qnil;
	      end_11:;
		goto end_12;
	    }
	    goto next_loop_10;
	  end_loop_10:
	    kb_properties = Qnil;
	  end_12:;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		gensymed_symbol = CDR(kb_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_12:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_12;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_13:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_13;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			kb_specific_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_13;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_13;
		  end_loop_13:
		    kb_specific_value = Qnil;
		  end_13:;
		    goto end_14;
		}
		goto next_loop_12;
	      end_loop_12:
		kb_specific_value = Qnil;
	      end_14:;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		gensymed_symbol = CDR(global_properties);
		gensymed_symbol_1 = Class_description_gkbprop;
		gensymed_symbol_2 = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		gensymed_symbol_3 = (SI_Long)0L;
	      next_loop_14:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_14;
		gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_2 < gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_2 > gensymed_symbol_3)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_4 = Nil;
		  next_loop_15:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_15;
		    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_1,gensymed_symbol_4)) {
			resulting_value = M_CDR(M_CAR(gensymed_symbol));
			goto end_15;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_15;
		  end_loop_15:
		    resulting_value = Qnil;
		  end_15:;
		    goto end_16;
		}
		goto next_loop_14;
	      end_loop_14:
		resulting_value = Qnil;
	      end_16:;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    temp_2 = 
		    get_slot_description_of_class_description_function(Qcross_section_pattern,
		    gensymed_symbol,Nil);
	}
	cross_section_pattern_qm = ISVREF(temp_2,(SI_Long)6L);
    }
    if (cross_section_pattern_qm) {
	if (EQ(region,Qstripe_color)) {
	    temp_2 = CAAR(cross_section_pattern_qm);
	    if (ATOM(temp_2) &&  !TRUEP(CDR(cross_section_pattern_qm))) {
		temp_2 = CAR(cross_section_pattern_qm);
		temp_2 = CAR(temp_2);
		if (temp_2)
		    return VALUES_1(temp_2);
		else
		    return VALUES_1(Current_default_line_color);
	    }
	    else
		return VALUES_1(Nil);
	}
	else {
	    temp_2 = CAAR(cross_section_pattern_qm);
	    cross_section_regions_qm = CONSP(temp_2) ? 
		    CAR(cross_section_pattern_qm) : Nil;
	    if (cross_section_regions_qm) {
		entry_qm = assq_function(region,cross_section_regions_qm);
		if (entry_qm) {
		    temp_2 = CDR(entry_qm);
		    if (temp_2)
			return VALUES_1(temp_2);
		    else
			return VALUES_1(Current_default_line_color);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Nil);
}

/* GENERIC-DIRECTLY-CONNECTED-P */
Object generic_directly_connected_p(connection_frame_1,block)
    Object connection_frame_1, block;
{
    Object sub_class_bit_vector, connection, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(98,57);
    sub_class_bit_vector = ISVREF(ISVREF(connection_frame_1,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Connection_class_description,
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	connection = ISVREF(connection_frame_1,(SI_Long)21L);
	temp_1 = EQ(ISVREF(connection,(SI_Long)2L),block) ? T : Nil;
	if (temp_1)
	    return VALUES_1(temp_1);
	else
	    return VALUES_1(EQ(ISVREF(connection,(SI_Long)3L),block) ? T : 
		    Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Connection_vertex_hit_distance = UNBOUND;

Object The_type_description_of_connection_spot = UNBOUND;

Object Chain_of_available_connection_spots = UNBOUND;

Object Connection_spot_count = UNBOUND;

/* CONNECTION-SPOT-STRUCTURE-MEMORY-USAGE */
Object connection_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(98,58);
    temp = Connection_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CONNECTION-SPOT-COUNT */
Object outstanding_connection_spot_count()
{
    Object def_structure_connection_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(98,59);
    gensymed_symbol = IFIX(Connection_spot_count);
    def_structure_connection_spot_variable = 
	    Chain_of_available_connection_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_connection_spot_variable))
	goto end_loop;
    def_structure_connection_spot_variable = 
	    ISVREF(def_structure_connection_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CONNECTION-SPOT-1 */
Object reclaim_connection_spot_1(connection_spot)
    Object connection_spot;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(98,60);
    inline_note_reclaim_cons(connection_spot,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = connection_spot;
    reclaim_structure_if_any(ISVREF(connection_spot,(SI_Long)2L));
    SVREF(connection_spot,FIX((SI_Long)2L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_connection_spots;
    SVREF(connection_spot,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_connection_spots = connection_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CONNECTION-SPOT */
Object reclaim_structure_for_connection_spot(connection_spot)
    Object connection_spot;
{
    x_note_fn_call(98,61);
    return reclaim_connection_spot_1(connection_spot);
}

static Object Qg2_defstruct_structure_name_connection_spot_g2_struct;  /* g2-defstruct-structure-name::connection-spot-g2-struct */

/* MAKE-PERMANENT-CONNECTION-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_connection_spot_structure_internal()
{
    Object def_structure_connection_spot_variable;
    Object connection_spot_count_new_value;
    Object defstruct_g2_connection_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(98,62);
    def_structure_connection_spot_variable = Nil;
    connection_spot_count_new_value = FIXNUM_ADD1(Connection_spot_count);
    Connection_spot_count = connection_spot_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_connection_spot_variable = Nil;
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
	defstruct_g2_connection_spot_variable = the_array;
	SVREF(defstruct_g2_connection_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_connection_spot_g2_struct;
	SVREF(defstruct_g2_connection_spot_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_connection_spot_variable,FIX((SI_Long)2L)) = Nil;
	SVREF(defstruct_g2_connection_spot_variable,FIX((SI_Long)3L)) = Nil;
	SVREF(defstruct_g2_connection_spot_variable,FIX((SI_Long)4L)) = Nil;
	SVREF(defstruct_g2_connection_spot_variable,FIX((SI_Long)5L)) = Nil;
	def_structure_connection_spot_variable = 
		defstruct_g2_connection_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_connection_spot_variable);
}

/* MAKE-CONNECTION-SPOT-1 */
Object make_connection_spot_1()
{
    Object def_structure_connection_spot_variable;

    x_note_fn_call(98,63);
    def_structure_connection_spot_variable = 
	    Chain_of_available_connection_spots;
    if (def_structure_connection_spot_variable) {
	Chain_of_available_connection_spots = 
		ISVREF(def_structure_connection_spot_variable,(SI_Long)0L);
	SVREF(def_structure_connection_spot_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_connection_spot_g2_struct;
    }
    else
	def_structure_connection_spot_variable = 
		make_permanent_connection_spot_structure_internal();
    inline_note_allocate_cons(def_structure_connection_spot_variable,Nil);
    SVREF(def_structure_connection_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_connection_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_connection_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_connection_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_connection_spot_variable,FIX((SI_Long)5L)) = Nil;
    return VALUES_1(def_structure_connection_spot_variable);
}

/* GENERATE-SPOT-FOR-CONNECTION */
Object generate_spot_for_connection(connection,mouse_pointer)
    Object connection, mouse_pointer;
{
    Object temp;

    x_note_fn_call(98,64);
    temp = push_connection_vertex_spot_if_close(connection,mouse_pointer);
    if (temp)
	return VALUES_1(temp);
    else
	return push_last_spot(mouse_pointer,make_connection_spot_1(),
		connection);
}

static Object Qimage_plane_spot;   /* image-plane-spot */

static Object Qvertex;             /* vertex */

/* PUSH-CONNECTION-VERTEX-SPOT-IF-CLOSE */
Object push_connection_vertex_spot_if_close(connection_frame_1,mouse_pointer)
    Object connection_frame_1, mouse_pointer;
{
    Object spot, connection, image_plane, vertex_qm, distance_qm, x_qm, y_qm;
    Object result;

    x_note_fn_call(98,65);
    spot = ISVREF(mouse_pointer,(SI_Long)5L);
    connection = ISVREF(connection_frame_1,(SI_Long)21L);
    if (structure_type_p(spot,Qimage_plane_spot)) {
	image_plane = ISVREF(spot,(SI_Long)6L);
	if (selection_handles_visible_p(connection,image_plane)) {
	    result = find_closest_connection_vertex(connection,image_plane,
		    ISVREF(mouse_pointer,(SI_Long)2L),ISVREF(mouse_pointer,
		    (SI_Long)3L));
	    MVS_4(result,vertex_qm,distance_qm,x_qm,y_qm);
	    if (distance_qm && FIXNUM_LE(distance_qm,
		    Connection_vertex_hit_distance)) {
		push_selection_handle_spot(mouse_pointer,
			connection_frame_1,Qvertex,vertex_qm,x_qm,y_qm);
		return VALUES_1(T);
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

/* FIND-CLOSEST-CONNECTION-VERTEX */
Object find_closest_connection_vertex(connection,image_plane,x0,y0_1)
    Object connection, image_plane, x0, y0_1;
{
    Object current_frame_transform_qm, current_image_x_scale;
    Object current_image_y_scale, current_x_origin_of_drawing;
    Object current_y_origin_of_drawing, vertices, vertex_qm, distance_qm;
    Object vertex_x_qm, vertex_y_qm, x, y, ab_loop_list_, distance, temp, d1;
    Object d2, scale, value;
    SI_Long vertex, temp_1;
    double fd1, fd2;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(98,66);
    current_frame_transform_qm = Nil;
    current_image_x_scale = ISVREF(image_plane,(SI_Long)11L);
    current_image_y_scale = ISVREF(image_plane,(SI_Long)12L);
    current_x_origin_of_drawing = ISVREF(image_plane,(SI_Long)13L);
    current_y_origin_of_drawing = ISVREF(image_plane,(SI_Long)14L);
    PUSH_SPECIAL(Current_y_origin_of_drawing,current_y_origin_of_drawing,4);
      PUSH_SPECIAL(Current_x_origin_of_drawing,current_x_origin_of_drawing,3);
	PUSH_SPECIAL(Current_image_y_scale,current_image_y_scale,2);
	  PUSH_SPECIAL(Current_image_x_scale,current_image_x_scale,1);
	    PUSH_SPECIAL(Current_frame_transform_qm,current_frame_transform_qm,
		    0);
	      vertices = compute_connection_vertices(connection);
	      vertex_qm = Nil;
	      distance_qm = Nil;
	      vertex_x_qm = Nil;
	      vertex_y_qm = Nil;
	      x = Nil;
	      y = Nil;
	      ab_loop_list_ = vertices;
	      vertex = (SI_Long)0L;
	      distance = Nil;
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      x = CAR(ab_loop_list_);
	      temp = CDR(ab_loop_list_);
	      y = CAR(temp);
	    next_loop:
	      temp = FIXNUM_MINUS(x,x0);
	      d1 = FIXNUM_ABS(temp);
	      temp = FIXNUM_MINUS(y,y0_1);
	      d2 = FIXNUM_ABS(temp);
	      if (FIXNUM_LT(d1,
		      Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation) 
		      && FIXNUM_LT(d2,
		      Maximum_x_or_y_separation_allowing_fixnum_vector_distance_calculation))
		  distance = isqrt(FIXNUM_ADD(FIXNUM_TIMES(d1,d1),
			  FIXNUM_TIMES(d2,d2)));
	      else {
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      fd1 = (double)IFIX(d1);
		      fd2 = (double)IFIX(d2);
		      distance = l_round(DOUBLE_TO_DOUBLE_FLOAT(sqrt(fd1 * 
			      fd1 + fd2 * fd2)),_);
		  }
		  POP_LOCAL_ALLOCATION(0,0);
	      }
	      if ( !TRUEP(distance_qm) || FIXNUM_LT(distance,distance_qm)) {
		  vertex_qm = FIX(vertex);
		  distance_qm = distance;
		  scale = Current_image_x_scale;
		  value = FIXNUM_MINUS(x,Current_x_origin_of_drawing);
		  if (IFIX(scale) == (SI_Long)4096L)
		      vertex_x_qm = value;
		  else if ( 
			  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)))
		      vertex_x_qm = inverse_scalef_function(scale,value);
		  else if (IFIX(value) >= (SI_Long)0L) {
		      temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			      (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			      IFIX(scale));
		      vertex_x_qm = temp;
		  }
		  else {
		      temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
			      (SI_Long)12L) + (IFIX(scale) >>  -  - 
			      (SI_Long)1L)) / IFIX(scale);
		      temp = FIXNUM_NEGATE(FIX(temp_1));
		      vertex_x_qm = temp;
		  }
		  scale = Current_image_y_scale;
		  value = FIXNUM_MINUS(y,Current_y_origin_of_drawing);
		  if (IFIX(scale) == (SI_Long)4096L)
		      vertex_y_qm = value;
		  else if ( 
			  !(FIXNUM_LT(Minus_of_isqrt_of_most_positive_fixnum,
			  value) && FIXNUM_LT(value,
			  Isqrt_of_most_positive_fixnum)))
		      vertex_y_qm = inverse_scalef_function(scale,value);
		  else if (IFIX(value) >= (SI_Long)0L) {
		      temp = FIX(((IFIX(value) << (SI_Long)12L) + 
			      (IFIX(scale) >>  -  - (SI_Long)1L)) / 
			      IFIX(scale));
		      vertex_y_qm = temp;
		  }
		  else {
		      temp_1 = ((IFIX(FIXNUM_NEGATE(value)) << 
			      (SI_Long)12L) + (IFIX(scale) >>  -  - 
			      (SI_Long)1L)) / IFIX(scale);
		      temp = FIXNUM_NEGATE(FIX(temp_1));
		      vertex_y_qm = temp;
		  }
	      }
	      ab_loop_list_ = CDDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      x = CAR(ab_loop_list_);
	      temp = CDR(ab_loop_list_);
	      y = CAR(temp);
	      vertex = vertex + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      reclaim_gensym_list_1(vertices);
	      result = VALUES_4(vertex_qm,distance_qm,vertex_x_qm,vertex_y_qm);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qconnection_style;   /* connection-style */

static Object Qdiagonal;           /* diagonal */

/* MOVE-CONNECTION-VERTEX-BY */
Object move_connection_vertex_by(connection_or_connection_frame,vertex,dx,dy)
    Object connection_or_connection_frame, vertex, dx, dy;
{
    Object x2, connection, plist;
    char temp;

    x_note_fn_call(98,67);
    if (SIMPLE_VECTOR_P(connection_or_connection_frame) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_or_connection_frame)) 
	    > (SI_Long)2L &&  !EQ(ISVREF(connection_or_connection_frame,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(connection_or_connection_frame,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    connection = temp ? ISVREF(connection_or_connection_frame,
	    (SI_Long)21L) : connection_or_connection_frame;
    plist = ISVREF(connection,(SI_Long)9L);
    if (plist && EQ(getfq_function_no_default(plist,Qconnection_style),
	    Qdiagonal))
	return move_diagonal_connection_vertex_by(connection,vertex,dx,dy);
    else
	return move_orthogonal_connection_vertex_by(connection,vertex,dx,dy);
}

/* MOVE-IF-LOOSE-END */
Object move_if_loose_end(block,dx,dy)
    Object block, dx, dy;
{
    x_note_fn_call(98,68);
    if (loose_end_p_function(block)) {
	if ( !(FIXNUM_EQ(dx,dy) && IFIX(dy) == (SI_Long)0L))
	    return move_item_by(3,block,dx,FIXNUM_NEGATE(dy));
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant;      /* # */

static Object Qleft;               /* left */

static Object Qright;              /* right */

/* MOVE-DIAGONAL-CONNECTION-VERTEX-BY */
Object move_diagonal_connection_vertex_by(connection,vertex,dx,dy)
    Object connection, vertex, dx, dy;
{
    Object delta_or_deltas, workspace_qm, side;
    Object initial_orientation_horizontal_p, input_end, output_end, temp;
    Object adjacent_end, incff_1_arg, temp_2, sublist, rest_1, decff_1_arg;
    SI_Long gensymed_symbol;
    char temp_1;

    x_note_fn_call(98,69);
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    workspace_qm = workspace_of_connection_qm(connection);
    side = ISVREF(array_constant,IFIX(ISVREF(connection,(SI_Long)5L)) & 
	    (SI_Long)3L);
    initial_orientation_horizontal_p = EQ(side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(side,Qright) ? T : Nil;
    input_end = ISVREF(connection,(SI_Long)3L);
    output_end = ISVREF(connection,(SI_Long)2L);
    temp =  !TRUEP(delta_or_deltas) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (ATOM(delta_or_deltas)) {
	adjacent_end = IFIX(vertex) == (SI_Long)1L ? input_end : output_end;
	if (workspace_qm)
	    update_connection_images(T,workspace_qm,connection);
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	incff_1_arg = initial_orientation_horizontal_p ? dx : dy;
	temp_2 = FIXNUM_ADD(ISVREF(connection,(SI_Long)6L),incff_1_arg);
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = temp_2;
	if (workspace_qm) {
	    enlarge_workspace_for_connection(workspace_qm,connection);
	    update_connection_images(Nil,workspace_qm,connection);
	}
	if (initial_orientation_horizontal_p)
	    return move_if_loose_end(adjacent_end,FIX((SI_Long)0L),dy);
	else
	    return move_if_loose_end(adjacent_end,dx,FIX((SI_Long)0L));
    }
    else {
	sublist = CONSP(delta_or_deltas) ? ( !(IFIX(vertex) < (SI_Long)1L) 
		? nthcdr(FIX(IFIX(FIXNUM_SUB1(vertex)) * (SI_Long)2L),
		delta_or_deltas) : Nil) : Nil;
	rest_1 = CDDR(sublist);
	if (workspace_qm)
	    update_connection_images(T,workspace_qm,connection);
	temp_1 = TRUEP(Noting_changes_to_kb_p);
	if (temp_1);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp_1 =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp_1)
	    note_change_to_connection_1(connection);
	if (sublist) {
	    incff_1_arg = initial_orientation_horizontal_p ? dx : dy;
	    temp_2 = FIXNUM_ADD(CAR(sublist),incff_1_arg);
	    M_CAR(sublist) = temp_2;
	    if (CADR(sublist)) {
		incff_1_arg = initial_orientation_horizontal_p ? dy : dx;
		temp_2 = FIXNUM_ADD(CADR(sublist),incff_1_arg);
		M_CADR(sublist) = temp_2;
	    }
	}
	if (rest_1) {
	    decff_1_arg = initial_orientation_horizontal_p ? dx : dy;
	    temp_2 = FIXNUM_MINUS(CAR(rest_1),decff_1_arg);
	    M_CAR(rest_1) = temp_2;
	    if (CADR(rest_1)) {
		decff_1_arg = initial_orientation_horizontal_p ? dy : dx;
		temp_2 = FIXNUM_MINUS(CADR(rest_1),decff_1_arg);
		M_CADR(rest_1) = temp_2;
	    }
	}
	if (workspace_qm) {
	    enlarge_workspace_for_connection(workspace_qm,connection);
	    return update_connection_images(Nil,workspace_qm,connection);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* MOVE-ORTHOGONAL-CONNECTION-VERTEX-BY */
Object move_orthogonal_connection_vertex_by(connection,vertex,dx,dy)
    Object connection, vertex, dx, dy;
{
    Object delta_or_deltas, workspace_qm, side;
    Object initial_orientation_horizontal_p, input_end, output_end;
    Object adjacent_end, incff_1_arg, temp_1, sublist, prevlist, temp_2;
    Object temp_3, decff_1_arg;
    SI_Long gensymed_symbol;
    char temp, horizontal_p;

    x_note_fn_call(98,70);
    delta_or_deltas = ISVREF(connection,(SI_Long)6L);
    workspace_qm = workspace_of_connection_qm(connection);
    side = ISVREF(array_constant,IFIX(ISVREF(connection,(SI_Long)5L)) & 
	    (SI_Long)3L);
    initial_orientation_horizontal_p = EQ(side,Qleft) ? T : Nil;
    if (initial_orientation_horizontal_p);
    else
	initial_orientation_horizontal_p = EQ(side,Qright) ? T : Nil;
    input_end = ISVREF(connection,(SI_Long)3L);
    output_end = ISVREF(connection,(SI_Long)2L);
    if ( !TRUEP(delta_or_deltas)) {
	if (initial_orientation_horizontal_p) {
	    move_if_loose_end(input_end,FIX((SI_Long)0L),dy);
	    return move_if_loose_end(output_end,dx,FIX((SI_Long)0L));
	}
	else {
	    move_if_loose_end(input_end,dx,FIX((SI_Long)0L));
	    return move_if_loose_end(output_end,FIX((SI_Long)0L),dy);
	}
    }
    else if (ATOM(delta_or_deltas)) {
	adjacent_end = IFIX(vertex) == (SI_Long)1L ? input_end : output_end;
	if (workspace_qm)
	    update_connection_images(T,workspace_qm,connection);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	incff_1_arg = initial_orientation_horizontal_p ? dx : dy;
	temp_1 = FIXNUM_ADD(ISVREF(connection,(SI_Long)6L),incff_1_arg);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	SVREF(connection,FIX((SI_Long)6L)) = temp_1;
	if (workspace_qm) {
	    enlarge_workspace_for_connection(workspace_qm,connection);
	    update_connection_images(Nil,workspace_qm,connection);
	}
	if (initial_orientation_horizontal_p)
	    return move_if_loose_end(adjacent_end,FIX((SI_Long)0L),dy);
	else
	    return move_if_loose_end(adjacent_end,dx,FIX((SI_Long)0L));
    }
    else {
	sublist = IFIX(vertex) >= (SI_Long)1L ? nthcdr(FIXNUM_SUB1(vertex),
		delta_or_deltas) : Nil;
	prevlist = IFIX(vertex) >= (SI_Long)2L ? nthcdr(FIX(IFIX(vertex) - 
		(SI_Long)2L),delta_or_deltas) : Nil;
	temp_2 = chestnut_modf_function(vertex,FIX((SI_Long)2L));
	temp_3 = FIX((SI_Long)0L);
	horizontal_p =  !EQ(initial_orientation_horizontal_p,NUM_EQ(temp_2,
		temp_3) ? T : Nil);
	if (workspace_qm)
	    update_connection_images(T,workspace_qm,connection);
	temp = TRUEP(Noting_changes_to_kb_p);
	if (temp);
	else {
	    gensymed_symbol = IFIX(ISVREF(connection,(SI_Long)7L)) & 
		    (SI_Long)128L;
	    temp =  !((SI_Long)0L != gensymed_symbol) ?  
		    !TRUEP(Geometric_change_to_connection_is_temporary_p) :
		     TRUEP(Nil);
	}
	if (temp)
	    note_change_to_connection_1(connection);
	if (prevlist) {
	    incff_1_arg = horizontal_p ? dy : dx;
	    temp_1 = FIXNUM_ADD(CAR(prevlist),incff_1_arg);
	    M_CAR(prevlist) = temp_1;
	}
	if (CDDR(prevlist)) {
	    decff_1_arg = horizontal_p ? dy : dx;
	    temp_1 = FIXNUM_MINUS(CADDR(prevlist),decff_1_arg);
	    M_CADDR(prevlist) = temp_1;
	}
	if (sublist) {
	    incff_1_arg = horizontal_p ? dx : dy;
	    temp_1 = FIXNUM_ADD(CAR(sublist),incff_1_arg);
	    M_CAR(sublist) = temp_1;
	}
	if (CDDR(sublist)) {
	    decff_1_arg = horizontal_p ? dx : dy;
	    temp_1 = FIXNUM_MINUS(CADDR(sublist),decff_1_arg);
	    M_CADDR(sublist) = temp_1;
	}
	if (workspace_qm) {
	    enlarge_workspace_for_connection(workspace_qm,connection);
	    update_connection_images(Nil,workspace_qm,connection);
	}
	if (IFIX(vertex) == (SI_Long)1L) {
	    if (initial_orientation_horizontal_p)
		move_if_loose_end(input_end,FIX((SI_Long)0L),dy);
	    else
		move_if_loose_end(input_end,dx,FIX((SI_Long)0L));
	}
	if (FIXNUM_GT(vertex,length(delta_or_deltas))) {
	    temp_3 = chestnut_modf_function(length(delta_or_deltas),
		    FIX((SI_Long)2L));
	    temp_2 = FIX((SI_Long)0L);
	    if ( !EQ(initial_orientation_horizontal_p,NUM_EQ(temp_3,
		    temp_2) ? T : Nil))
		return move_if_loose_end(output_end,FIX((SI_Long)0L),dy);
	    else
		return move_if_loose_end(output_end,dx,FIX((SI_Long)0L));
	}
	else
	    return VALUES_1(Nil);
    }
}

/* ENLARGE-WORKSPACE-FOR-CONNECTION */
Object enlarge_workspace_for_connection(workspace,connection)
    Object workspace, connection;
{
    Object extreme_left_edge_so_far, extreme_top_edge_so_far;
    Object extreme_right_edge_so_far, extreme_bottom_edge_so_far;
    Object current_draw_document_p;
    Declare_special(5);
    Object result;

    x_note_fn_call(98,71);
    extreme_left_edge_so_far = Most_positive_fixnum;
    PUSH_SPECIAL(Extreme_left_edge_so_far,extreme_left_edge_so_far,4);
      extreme_top_edge_so_far = Most_positive_fixnum;
      PUSH_SPECIAL(Extreme_top_edge_so_far,extreme_top_edge_so_far,3);
	extreme_right_edge_so_far = Most_negative_fixnum;
	PUSH_SPECIAL(Extreme_right_edge_so_far,extreme_right_edge_so_far,2);
	  extreme_bottom_edge_so_far = Most_negative_fixnum;
	  PUSH_SPECIAL(Extreme_bottom_edge_so_far,extreme_bottom_edge_so_far,
		  1);
	    update_extreme_edges_from_connection(connection);
	    current_draw_document_p = Nil;
	    PUSH_SPECIAL(Current_draw_document_p,current_draw_document_p,0);
	      result = enlarge_workspace_if_necessary(5,workspace,
		      Extreme_left_edge_so_far,Extreme_top_edge_so_far,
		      Extreme_right_edge_so_far,Extreme_bottom_edge_so_far);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* SUBCLASSES */
Object subclasses(class_name)
    Object class_name;
{
    Object scope_conses, ab_loopvar_, subclass, ab_loopvar__1, ab_loopvar__2;
    Object ab_loopvar__3, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(98,72);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = class_name;
    subclass = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      ab_loopvar__3 = gensym_cons_1(subclass,Nil);
      if (ab_loopvar__2)
	  M_CDR(ab_loopvar__2) = ab_loopvar__3;
      else
	  ab_loopvar__1 = ab_loopvar__3;
      ab_loopvar__2 = ab_loopvar__3;
      goto next_loop;
    end_loop:
      result = VALUES_1(ab_loopvar__1);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* INSTANTIATED-CONNECTION-CLASS-P */
Object instantiated_connection_class_p(connection_class)
    Object connection_class;
{
    Object subclasses_1, scope_conses, ab_loopvar_, ab_loopvar__1, block;
    Object ab_loop_it_, ab_node_stack_, ab_current_node_, gensymed_symbol;
    Object ab_skip_list_form_, ab_skip_list_p_, ab_next_node_, ab_tail_node_;
    Object ab_current_alist_, ab_entry_cons_, ab_connection_;
    Object ab_connection_item_, connection, class_name, temp_1;
    Object ab_less_than_branch_qm_, x2, connection_frame_or_class;
    Object instantiated_qm;
    char temp;
    Declare_special(2);

    x_note_fn_call(98,73);
    subclasses_1 = subclasses(connection_class);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    block = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,1);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(Qblock);
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
      block = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      scope_conses = Scope_conses;
      ab_node_stack_ = Nil;
      ab_current_node_ = Nil;
      gensymed_symbol = ISVREF(block,(SI_Long)14L);
      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	      (SI_Long)6L) : Nil;
      ab_skip_list_form_ = gensymed_symbol;
      ab_skip_list_p_ = Nil;
      ab_next_node_ = Nil;
      ab_tail_node_ = Nil;
      ab_current_alist_ = Nil;
      ab_entry_cons_ = Nil;
      ab_connection_ = Nil;
      ab_connection_item_ = Nil;
      connection = Nil;
      PUSH_SPECIAL(Scope_conses,scope_conses,0);
	class_name = Nil;
	ab_loop_it_ = Nil;
	gensymed_symbol = CDR(ab_skip_list_form_);
	if (CONSP(gensymed_symbol)) {
	    temp_1 = M_CAR(gensymed_symbol);
	    temp = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    temp_1 = M_CDR(gensymed_symbol);
	    ab_skip_list_p_ = SIMPLE_VECTOR_P(temp_1) ? T : Nil;
	}
	else
	    ab_skip_list_p_ = Nil;
	if (ab_skip_list_p_) {
	    ab_next_node_ = ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		    (SI_Long)0L),(SI_Long)0L);
	    ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	    if (EQ(ab_next_node_,ab_tail_node_))
		ab_next_node_ = Nil;
	}
	else
	    ab_next_node_ = CDR(ab_skip_list_form_);
      next_loop_2:
      next_loop_3:
	if (ab_current_alist_) {
	    ab_entry_cons_ = M_CAR(ab_current_alist_);
	    ab_connection_ = M_CAR(ab_entry_cons_);
	    ab_connection_item_ = M_CDR(ab_entry_cons_);
	    ab_current_alist_ = M_CDR(ab_current_alist_);
	}
	else if (ab_skip_list_p_) {
	    if (ab_next_node_) {
		ab_current_node_ = ab_next_node_;
		ab_next_node_ = ISVREF(ISVREF(ab_current_node_,
			(SI_Long)0L),(SI_Long)0L);
		if (EQ(ab_next_node_,ab_tail_node_))
		    ab_next_node_ = Nil;
		ab_connection_ = ISVREF(ab_current_node_,(SI_Long)2L);
		ab_connection_item_ = ISVREF(ab_current_node_,(SI_Long)3L);
	    }
	    else
		ab_current_node_ = Nil;
	}
	else {
	    if (ab_next_node_) {
		ab_current_node_ = ab_next_node_;
		ab_less_than_branch_qm_ = Nil;
	      next_loop_4:
		ab_less_than_branch_qm_ = ISVREF(ab_current_node_,(SI_Long)1L);
		if ( !TRUEP(ab_less_than_branch_qm_))
		    goto end_loop_2;
		ab_node_stack_ = scope_cons(ab_current_node_,ab_node_stack_);
		ab_current_node_ = ab_less_than_branch_qm_;
		goto next_loop_4;
	      end_loop_2:;
	    }
	    else if (ab_node_stack_) {
		ab_next_node_ = ab_node_stack_;
		ab_current_node_ = M_CAR(ab_node_stack_);
		ab_node_stack_ = M_CDR(ab_node_stack_);
	    }
	    else
		ab_current_node_ = Nil;
	    if (ab_current_node_) {
		ab_next_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_connection_ = M_CAR(ab_entry_cons_);
		ab_connection_item_ = M_CDR(ab_entry_cons_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	}
	if ( !TRUEP(ab_current_node_) || ab_current_node_ && 
		ab_connection_ && EQ(ISVREF(ab_connection_,(SI_Long)3L),block))
	    goto end_1;
	goto next_loop_3;
      end_loop_3:
      end_1:
	if ( !TRUEP(ab_current_node_))
	    goto end_loop_4;
	connection = ab_connection_;
	if (SIMPLE_VECTOR_P(connection) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection)) > (SI_Long)2L 
		&&  !EQ(ISVREF(connection,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(connection,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    class_name = ISVREF(ISVREF(connection,(SI_Long)1L),(SI_Long)1L);
	else if (SIMPLE_VECTOR_P(connection) && EQ(ISVREF(connection,
		(SI_Long)0L),
		Qg2_defstruct_structure_name_connection_g2_struct)) {
	    connection_frame_or_class = ISVREF(connection,(SI_Long)1L);
	    if (SYMBOLP(connection_frame_or_class))
		class_name = connection_frame_or_class;
	    else {
		if (SIMPLE_VECTOR_P(connection_frame_or_class) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(connection_frame_or_class)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(connection_frame_or_class,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(connection_frame_or_class,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp)
		    class_name = ISVREF(ISVREF(connection_frame_or_class,
			    (SI_Long)1L),(SI_Long)1L);
		else
		    class_name = Nil;
	    }
	}
	else
	    class_name = type_of_named_structure(connection);
	ab_loop_it_ = member_eql(class_name,subclasses_1) ? T : Qnil;
	if (ab_loop_it_)
	    goto end_2;
	goto next_loop_2;
      end_loop_4:
	ab_loop_it_ = Qnil;
      end_2:;
      POP_SPECIAL();
      if (ab_loop_it_) {
	  instantiated_qm = ab_loop_it_;
	  goto end_3;
      }
      goto next_loop;
    end_loop_1:
      instantiated_qm = Qnil;
    end_3:;
    POP_SPECIAL();
    reclaim_gensym_list_1(subclasses_1);
    return VALUES_1(instantiated_qm);
}

void connect1_INIT()
{
    Object temp, reclaim_structure_for_connection_1, temp_1;
    Object reclaim_structure_for_loose_end_spot_1, type_description, temp_2;
    Object reclaim_structure_for_connection_item_1;
    Object reclaim_structure_for_connection_spot_1;
    Object Qbottom, Qtop, AB_package, Qclasses_which_define, Qgenerate_spot;
    Object Qgenerate_spot_for_connection, Qtype_of_frame_represented;
    Object Qabstract_type, Qenclosing_spot_type, Qinnermost_spot_p;
    Object Qtype_description_of_type, Qconnection_spot, Qreclaim_structure;
    Object Qoutstanding_connection_spot_count;
    Object Qconnection_spot_structure_memory_usage, Qutilities2;
    Object Qconnection_spot_count, Qchain_of_available_connection_spots;
    Object string_constant_50;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_49, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qconnect1;
    Object Qdont_include_offset_for_end_position_qm, Qabsent_slot_putter;
    Object Qput_control_block_output_where_slot_is_absent;
    Object Qcontrol_block_output;
    Object Qput_control_block_input_2_where_slot_is_absent;
    Object Qcontrol_block_input_2;
    Object Qput_control_block_input_1_where_slot_is_absent;
    Object Qcontrol_block_input_1;
    Object Qput_control_block_input_where_slot_is_absent, Qcontrol_block_input;
    Object Qsubstitute_class_and_kb_flags, Qinstrument_signal;
    Object Qinstrument_signal_connection_class, Qjunction_block_for_flow_pipe;
    Object Qstandard_flow_pipe_junction, Qflow_pipe;
    Object Qstandard_flow_pipe_connection_class, Qstandard_flow_pipe;
    Object Qjunction_block_for_instrument_signal, Qinstrument_signal_junction;
    Object Qflow_pipe_junction, Qconnection_item;
    Object Qoutstanding_connection_item_count;
    Object Qconnection_item_structure_memory_usage, Qconnection_item_count;
    Object Qchain_of_available_connection_items, string_constant_48;
    Object Qg2_defstruct_structure_name_connection_item_g2_struct;
    Object string_constant_47, Qconnection_line_pattern, Qterminal_post;
    Object Qnote_name_change, Qnote_name_change_for_connection_post, Qcleanup;
    Object Qcleanup_for_connection_post, string_constant_46;
    Object string_constant_45, list_constant_2, Qcreate_icon_description;
    Object string_constant_44, string_constant_43, string_constant_42;
    Object string_constant_41, Qdefault_junction, string_constant_40;
    Object string_constant_39, string_constant_38, Qobject, string_constant_37;
    Object list_constant_1, string_constant_36, string_constant_35, Qactivate;
    Object Qactivate_for_connection, Qdeactivate, Qdeactivate_for_connection;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, string_constant_30, string_constant_29;
    Object string_constant_28, string_constant_27, string_constant_26;
    Object string_constant_25, string_constant_24, string_constant_23;
    Object string_constant_22, string_constant_21, string_constant_20;
    Object string_constant_19, string_constant_18, string_constant_17;
    Object string_constant_16, string_constant_15, string_constant_14;
    Object string_constant_13, string_constant_12, string_constant_11;
    Object string_constant_10, string_constant_9, list_constant, Qitem;
    Object Qdefault_connection_class, Qloose_end, Qgenerate_spot_for_loose_end;
    Object Qloose_end_spot, Qoutstanding_loose_end_spot_count;
    Object Qloose_end_spot_structure_memory_usage, Qloose_end_spot_count;
    Object Qchain_of_available_loose_end_spots, string_constant_8;
    Object string_constant_7, string_constant_6, string_constant_5;
    Object string_constant_2, Qinvisible_entity, string_constant_4;
    Object string_constant_3, Qentity, Qoutstanding_connection_count;
    Object Qconnection_structure_memory_usage, Qconnection_count;
    Object Qchain_of_available_connections, string_constant_1, string_constant;

    x_note_fn_call(98,74);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_connection_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_connection_g2_struct,
	    Qconnection,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qconnection,
	    Qg2_defstruct_structure_name_connection_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_connection == UNBOUND)
	The_type_description_of_connection = Nil;
    string_constant = 
	    STATIC_STRING("43Dy8m83=+y1n83=+y8n8k1l8n0000001l1m8y83-3Mykwk0k0");
    temp = The_type_description_of_connection;
    The_type_description_of_connection = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_connection_g2_struct,
	    The_type_description_of_connection,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qconnection,The_type_description_of_connection,
	    Qtype_description_of_type);
    Qoutstanding_connection_count = 
	    STATIC_SYMBOL("OUTSTANDING-CONNECTION-COUNT",AB_package);
    Qconnection_structure_memory_usage = 
	    STATIC_SYMBOL("CONNECTION-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_1 = STATIC_STRING("1q83=+y8s83-Nry09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_connection_count);
    push_optimized_constant(Qconnection_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_1));
    Qchain_of_available_connections = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CONNECTIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_connections,
	    Chain_of_available_connections);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_connections,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qconnection_count = STATIC_SYMBOL("CONNECTION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_count,Connection_count);
    record_system_variable(Qconnection_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qconnection_structure_memory_usage,
	    STATIC_FUNCTION(connection_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_connection_count,
	    STATIC_FUNCTION(outstanding_connection_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_connection_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_connection,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qconnection,
	    reclaim_structure_for_connection_1);
    Savable_connection_flags = FIX((SI_Long)1L);
    Connection_not_directed_internal_flag = FIX((SI_Long)1L);
    Connection_permanently_changed_flag = FIX((SI_Long)2L);
    Connection_has_been_written_flag = FIX((SI_Long)4L);
    Connection_existed_at_start_of_save_flag = FIX((SI_Long)8L);
    Connection_overlap_cache_flag = FIX((SI_Long)16L);
    Connection_overlap_cache_valid_flag = FIX((SI_Long)32L);
    Transient_connection_flag = FIX((SI_Long)64L);
    Savable_connection_flags = FIX(IFIX(Savable_connection_flags) | 
	    (SI_Long)64L);
    Connection_needs_indexing_flag = FIX((SI_Long)128L);
    Connection_being_deleted_flag = FIX((SI_Long)256L);
    Connection_found_in_search_flag = FIX((SI_Long)512L);
    if (Geometric_change_to_connection_is_temporary_p == UNBOUND)
	Geometric_change_to_connection_is_temporary_p = Nil;
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinvisible_entity = STATIC_SYMBOL("INVISIBLE-ENTITY",AB_package);
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qinvisible_entity,list_constant);
    string_constant_2 = STATIC_STRING("1l1l8t");
    string_constant_3 = 
	    STATIC_STRING("1l4z8r8u8u83Sqy83Sqy00001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_4 = STATIC_STRING("1n8q1n83Sqy1l83-+y8t1m8u0");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(string_constant_3);
    add_class_to_environment(9,Qinvisible_entity,list_constant,Nil,temp,
	    Nil,temp_1,list_constant,
	    regenerate_optimized_constant(string_constant_4),Nil);
    Invisible_entity_class_description = 
	    lookup_global_or_kb_specific_property_value(Qinvisible_entity,
	    Class_description_gkbprop);
    Qloose_end = STATIC_SYMBOL("LOOSE-END",AB_package);
    check_if_superior_classes_are_defined(Qloose_end,list_constant);
    string_constant_5 = 
	    STATIC_STRING("1l4z8r8u8u83UYy83UYy00001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_6 = STATIC_STRING("1n8q1n83UYy1l83-+y8t1m8u0");
    temp = regenerate_optimized_constant(string_constant_2);
    temp_1 = regenerate_optimized_constant(string_constant_5);
    add_class_to_environment(9,Qloose_end,list_constant,Nil,temp,Nil,
	    temp_1,list_constant,
	    regenerate_optimized_constant(string_constant_6),Nil);
    Loose_end_class_description = 
	    lookup_global_or_kb_specific_property_value(Qloose_end,
	    Class_description_gkbprop);
    Qg2_defstruct_structure_name_loose_end_spot_g2_struct = 
	    STATIC_SYMBOL("LOOSE-END-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qloose_end_spot = STATIC_SYMBOL("LOOSE-END-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_loose_end_spot_g2_struct,
	    Qloose_end_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qloose_end_spot,
	    Qg2_defstruct_structure_name_loose_end_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_loose_end_spot == UNBOUND)
	The_type_description_of_loose_end_spot = Nil;
    string_constant_7 = 
	    STATIC_STRING("43Dy8m83UZy1o83UZy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_loose_end_spot;
    The_type_description_of_loose_end_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_7));
    mutate_global_property(Qg2_defstruct_structure_name_loose_end_spot_g2_struct,
	    The_type_description_of_loose_end_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qloose_end_spot,
	    The_type_description_of_loose_end_spot,Qtype_description_of_type);
    Qoutstanding_loose_end_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-LOOSE-END-SPOT-COUNT",AB_package);
    Qloose_end_spot_structure_memory_usage = 
	    STATIC_SYMBOL("LOOSE-END-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_8 = STATIC_STRING("1q83UZy8s83-cNy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_loose_end_spot_count);
    push_optimized_constant(Qloose_end_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_8));
    Qchain_of_available_loose_end_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-LOOSE-END-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_loose_end_spots,
	    Chain_of_available_loose_end_spots);
    record_system_variable(Qchain_of_available_loose_end_spots,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qloose_end_spot_count = STATIC_SYMBOL("LOOSE-END-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qloose_end_spot_count,Loose_end_spot_count);
    record_system_variable(Qloose_end_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qloose_end_spot_structure_memory_usage,
	    STATIC_FUNCTION(loose_end_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_loose_end_spot_count,
	    STATIC_FUNCTION(outstanding_loose_end_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_loose_end_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_loose_end_spot,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qloose_end_spot,
	    reclaim_structure_for_loose_end_spot_1);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qimage_plane_spot = STATIC_SYMBOL("IMAGE-PLANE-SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qloose_end_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qobject),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qgenerate_spot_for_loose_end = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-LOOSE-END",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_loose_end,
	    STATIC_FUNCTION(generate_spot_for_loose_end,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_loose_end);
    set_get(Qloose_end,Qgenerate_spot,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qloose_end,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qdefault_connection_class = STATIC_SYMBOL("DEFAULT-CONNECTION-CLASS",
	    AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qdefault_connection_class,CONS(Qconnection,
	    temp),Qsubstitute_class_and_kb_flags);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_1 = STATIC_CONS(Qitem,list_constant);
    check_if_superior_classes_are_defined(Qconnection,list_constant_1);
    string_constant_9 = STATIC_STRING("1l1m8v83=+y");
    Qconnection_line_pattern = STATIC_SYMBOL("CONNECTION-LINE-PATTERN",
	    AB_package);
    string_constant_10 = 
	    STATIC_STRING("1u4z8r83=Hy83=Hy83=+y83=+y01l2l83Tyl001p1l8o1l8z1l8l1l83Cy1m83Dy53-=yExport: ( [color: color-symbol, width: integer] *), writabl");
    string_constant_11 = 
	    STATIC_STRING("e: true,000004z8r83BQy83BQy83=+y83=+y00001u1l83Ey1l8l1l830Yy1l83Hy1m8p83=Hy1l83Fy1l83-4y1l83Ny1l8z1m83Dy53-=yExport: ( [color: c");
    string_constant_12 = 
	    STATIC_STRING("olor-symbol, width: integer] *), writable: true,000004z8r833Zy833Zy83=+y83=+y03Gy001n1l8l1l8z1m83Dy53ayExport: integer-or-none, ");
    string_constant_13 = 
	    STATIC_STRING("writable: true,000004z8r83FFy83FFy83=+y83=+y00001u1l83Ey1l8l1l830Yy1l83Hy1m8p833Zy1l83Fy1l83-4y1l83Ny1l8z1m83Dy53ayExport: integ");
    string_constant_14 = 
	    STATIC_STRING("er-or-none, writable: true,000004z8r83TCy83TCy83=+y83=+y0833-y001n1l8l1l8z1m83Dy53VyExport: class-name, writable = true000004z8r");
    string_constant_15 = 
	    STATIC_STRING("83DJy83DJy83=+y83=+y00001u1l83Ey1l8l1l830Yy1l83Hy1m8p833Qy1l83Fy1l83-4y1l83Ny1l8z1m83Dy53VyExport: class-name, writable = true00");
    string_constant_16 = 
	    STATIC_STRING("0004z8r83Ijy83Ijy83=+y83=+y00001n1l8o1l8l1m83Dy73-By3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-Ty3-ey3-by3-Ty3-ly3sy3Sy3-Vy3-hy3-gy");
    string_constant_17 = 
	    STATIC_STRING("3-gy3-Xy3-Vy3-my3-by3-hy3-gy3fy3-iy3-Ty3-ky3-my3Sy3-hy3-ky3Sy3-Vy3-hy3-gy3-gy3-Xy3-Vy3-my3-by3-hy3-gy3ey3Sy3-wyut3-my3-ry3-iy3-X");
    string_constant_18 = 
	    STATIC_STRING("y3Sy3-ly3-my3-ky3-ny3-Vy3-my3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-my3-ky3-ny3-Xy000004z8r8380y8380y83=+y83=+y083EEy00");
    string_constant_19 = 
	    STATIC_STRING("1o1m8p83BPy1l8l1l83Hy1m83Dy73-3y3-1y3-qy3-iy3-hy3-ky3-my3-Xy3-Wy3sy3Sy3-Gy3-ry3-iy3-Xy3Sy3-by3-ly3Sy3ay3-fy3-Xy3-fy3-Uy3-Xy3-ky3");
    string_constant_20 = 
	    STATIC_STRING("Sy3-ly3-Xy3-jy3ay3-Wy3-by3-Ty3-Zy3-hy3-gy3-Ty3-ey3Sy3-hy3-ky3-my3-ay3-hy3-Zy3-hy3-gy3-Ty3-ey3by3by3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy");
    string_constant_21 = 
	    STATIC_STRING("3-ey3-Xy3Sy3vy3Sy3-wyut3-my3-ky3-ny3-Xy000004z8r838-y838-y83=+y83=+y00001o1m8p838-y1l8l1l83Hy1m83Dy53YyExported: Type is TBD, wr");
    string_constant_22 = 
	    STATIC_STRING("itable = true000004z8r839Iy839Iy83=+y83=+y00001o1m8p9k1l8l1l83Hy1m83Dy53-1yExported: Type is (or solid (member seq (dash dot))),");
    string_constant_23 = STATIC_STRING(" writable = true00000");
    string_constant_24 = 
	    STATIC_STRING("1w8q1n83=+y1m83Ry83-+y1m8v83=+y1r83=Hy1l2l83Tyl8o8z8l83Cy1m83Dy53-=yExport: ( [color: color-symbol, width: integer] *), writable");
    string_constant_25 = 
	    STATIC_STRING(": true,1w83BQy083Ey8l830Yy83Hy1m8p83=Hy83Fy83-4y83Ny8z1m83Dy53-=yExport: ( [color: color-symbol, width: integer] *), writable: t");
    string_constant_26 = 
	    STATIC_STRING("rue,1p833Zy3Gy8l8z1m83Dy53ayExport: integer-or-none, writable: true,1w83FFy083Ey8l830Yy83Hy1m8p833Zy83Fy83-4y83Ny8z1m83Dy53ayExp");
    string_constant_27 = 
	    STATIC_STRING("ort: integer-or-none, writable: true,1p83TCy833-y8l8z1m83Dy53VyExport: class-name, writable = true1w83DJy083Ey8l830Yy83Hy1m8p833");
    string_constant_28 = 
	    STATIC_STRING("Qy83Fy83-4y83Ny8z1m83Dy53VyExport: class-name, writable = true1p83Ijy08o8l1m83Dy73-By3-1y3-qy3-iy3-hy3-ky3-my3Sy3-Ty3-ly3Sy3-Ty3");
    string_constant_29 = 
	    STATIC_STRING("-ey3-by3-Ty3-ly3sy3Sy3-Vy3-hy3-gy3-gy3-Xy3-Vy3-my3-by3-hy3-gy3fy3-iy3-Ty3-ky3-my3Sy3-hy3-ky3Sy3-Vy3-hy3-gy3-gy3-Xy3-Vy3-my3-by3-");
    string_constant_30 = 
	    STATIC_STRING("hy3-gy3ey3Sy3-wyut3-my3-ry3-iy3-Xy3Sy3-ly3-my3-ky3-ny3-Vy3-my3ey3Sy3-py3-ky3-by3-my3-Ty3-Uy3-ey3-Xy3Sy3vy3Sy3-my3-ky3-ny3-Xy1q83");
    string_constant_31 = 
	    STATIC_STRING("80y83EEy1m8p83BPy8l83Hy1m83Dy73-3y3-1y3-qy3-iy3-hy3-ky3-my3-Xy3-Wy3sy3Sy3-Gy3-ry3-iy3-Xy3Sy3-by3-ly3Sy3ay3-fy3-Xy3-fy3-Uy3-Xy3-k");
    string_constant_32 = 
	    STATIC_STRING("y3Sy3-ly3-Xy3-jy3ay3-Wy3-by3-Ty3-Zy3-hy3-gy3-Ty3-ey3Sy3-hy3-ky3-my3-ay3-hy3-Zy3-hy3-gy3-Ty3-ey3by3by3ey3Sy3-py3-ky3-by3-my3-Ty3-");
    string_constant_33 = 
	    STATIC_STRING("Uy3-ey3-Xy3Sy3vy3Sy3-wyut3-my3-ky3-ny3-Xy1q838-y01m8p838-y8l83Hy1m83Dy53YyExported: Type is TBD, writable = true1q839Iy01m8p9k8l");
    string_constant_34 = 
	    STATIC_STRING("83Hy1m83Dy53-1yExported: Type is (or solid (member seq (dash dot))), writable = true");
    temp = regenerate_optimized_constant(string_constant_9);
    clear_optimized_constants();
    push_optimized_constant(Qconnection_line_pattern);
    temp_1 = regenerate_optimized_constant(list(14,string_constant_10,
	    string_constant_11,string_constant_12,string_constant_13,
	    string_constant_14,string_constant_15,string_constant_16,
	    string_constant_17,string_constant_18,string_constant_19,
	    string_constant_20,string_constant_21,string_constant_22,
	    string_constant_23));
    clear_optimized_constants();
    push_optimized_constant(Qconnection_line_pattern);
    add_class_to_environment(9,Qconnection,list_constant_1,Nil,temp,Nil,
	    temp_1,list_constant_1,regenerate_optimized_constant(list(11,
	    string_constant_24,string_constant_25,string_constant_26,
	    string_constant_27,string_constant_28,string_constant_29,
	    string_constant_30,string_constant_31,string_constant_32,
	    string_constant_33,string_constant_34)),Nil);
    Connection_class_description = 
	    lookup_global_or_kb_specific_property_value(Qconnection,
	    Class_description_gkbprop);
    Qdeactivate_for_connection = STATIC_SYMBOL("DEACTIVATE-FOR-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_connection,
	    STATIC_FUNCTION(deactivate_for_connection,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_connection);
    set_get(Qconnection,Qdeactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qconnection,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qactivate_for_connection = STATIC_SYMBOL("ACTIVATE-FOR-CONNECTION",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_connection,
	    STATIC_FUNCTION(activate_for_connection,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_connection);
    set_get(Qconnection,Qactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qconnection,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    check_if_superior_classes_are_defined(Qobject,list_constant_1);
    string_constant_35 = STATIC_STRING("1n1m8v83-Oy1l83Iy1l83Ly");
    string_constant_36 = STATIC_STRING("0");
    string_constant_37 = 
	    STATIC_STRING("1m8q1p83-Oy1m83Ry83-+y1m8v83-Oy83Iy83Ly");
    temp = regenerate_optimized_constant(string_constant_35);
    temp_1 = regenerate_optimized_constant(string_constant_36);
    add_class_to_environment(9,Qobject,list_constant_1,Nil,temp,Nil,temp_1,
	    list_constant_1,
	    regenerate_optimized_constant(string_constant_37),Nil);
    Object_class_description = 
	    lookup_global_or_kb_specific_property_value(Qobject,
	    Class_description_gkbprop);
    Qdefault_junction = STATIC_SYMBOL("DEFAULT-JUNCTION",AB_package);
    list_constant_2 = STATIC_CONS(Qobject,Qnil);
    check_if_superior_classes_are_defined(Qdefault_junction,list_constant_2);
    string_constant_38 = STATIC_STRING("1o1m8v833-y1l8t1l83Iy1l83Ly");
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_39 = 
	    STATIC_STRING("1l4z8r8u8u833-y833-y01p8w9kss1l1p83Jy1mkk1msk1mss1mks001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_40 = 
	    STATIC_STRING("1n8q1q833-y1l83-Oy1m8v833-y8t83Iy83Ly1m8u1p8w9kss1l1p83Jy1mkk1msk1mss1mks");
    temp = regenerate_optimized_constant(string_constant_38);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(string_constant_39);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qdefault_junction,list_constant_2,Nil,temp,
	    Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(string_constant_40),Nil);
    Default_junction_class_description = 
	    lookup_global_or_kb_specific_property_value(Qdefault_junction,
	    Class_description_gkbprop);
    Qconnection_post = STATIC_SYMBOL("CONNECTION-POST",AB_package);
    check_if_superior_classes_are_defined(Qconnection_post,list_constant_2);
    string_constant_41 = STATIC_STRING("1m1m8v838=y1l8t");
    string_constant_42 = 
	    STATIC_STRING("1n4z8r8u8u838=y838=y01p8w9k3Gy3Gy1o1p83Jy1mkk1mk3Gy1m3Gy3Gy1m3Gyk1o83*fy1mlu1mul1m3Fyu1n83Oy1moo1m3Cy3Cy1n83Oy1mo3Cy1m3Cyo001o1l");
    string_constant_43 = 
	    STATIC_STRING("8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition000004z8r83bBy83bBy838=y838=y00001n1m8p83FEy1l83Ey1l8l000004z8r83bCy83");
    string_constant_44 = 
	    STATIC_STRING("bCy838=y838=y00001n1l83Ey1l8l1l83Uy00000");
    string_constant_45 = 
	    STATIC_STRING("1p8q1o838=y1l83-Oy1m8v838=y8t1m8u1p8w9k3Gy3Gy1o1p83Jy1mkk1mk3Gy1m3Gy3Gy1m3Gyk1o83*fy1mlu1mul1m3Fyu1n83Oy1moo1m3Cy3Cy1n83Oy1mo3Cy");
    string_constant_46 = 
	    STATIC_STRING("1m3Cyo1p83bBy01m8p83FEy83Ey8l1p83bCy083Ey8l83Uy");
    temp = regenerate_optimized_constant(string_constant_41);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_42,
	    string_constant_43,string_constant_44));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qconnection_post,list_constant_2,Nil,temp,
	    Nil,temp_1,list_constant_2,
	    regenerate_optimized_constant(LIST_2(string_constant_45,
	    string_constant_46)),Nil);
    Connection_post_class_description = 
	    lookup_global_or_kb_specific_property_value(Qconnection_post,
	    Class_description_gkbprop);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qsuperior_connection_cache = STATIC_SYMBOL("SUPERIOR-CONNECTION-CACHE",
	    AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    Qcleanup_for_connection_post = 
	    STATIC_SYMBOL("CLEANUP-FOR-CONNECTION-POST",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_connection_post,
	    STATIC_FUNCTION(cleanup_for_connection_post,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_connection_post);
    set_get(Qconnection_post,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qconnection_post,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qnote_name_change_for_connection_post = 
	    STATIC_SYMBOL("NOTE-NAME-CHANGE-FOR-CONNECTION-POST",AB_package);
    SET_SYMBOL_FUNCTION(Qnote_name_change_for_connection_post,
	    STATIC_FUNCTION(note_name_change_for_connection_post,NIL,FALSE,
	    3,3));
    Qnote_name_change = STATIC_SYMBOL("NOTE-NAME-CHANGE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qnote_name_change_for_connection_post);
    set_get(Qconnection_post,Qnote_name_change,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qnote_name_change),
	    Qclasses_which_define);
    temp_2 = CONS(Qconnection_post,temp);
    mutate_global_property(Qnote_name_change,temp_2,Qclasses_which_define);
    Qterminal_post = STATIC_SYMBOL("TERMINAL-POST",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qterminal_post,CONS(Qconnection_post,temp),
	    Qsubstitute_class_and_kb_flags);
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qconnection_line_pattern,
	    STATIC_FUNCTION(connection_line_pattern,NIL,FALSE,1,1));
    if (The_type_description_of_connection_item == UNBOUND)
	The_type_description_of_connection_item = Nil;
    string_constant_47 = 
	    STATIC_STRING("43Dy8m83Iky1m83Iky8k1l8k0000001o1m83*gy9k1m83=ey3-Wy1n8y83-3Ny1l83sxy1m83My83-AAykqk0k0");
    temp = The_type_description_of_connection_item;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_connection_item = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_47));
    Qg2_defstruct_structure_name_connection_item_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-ITEM-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    mutate_global_property(Qg2_defstruct_structure_name_connection_item_g2_struct,
	    The_type_description_of_connection_item,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qconnection_item = STATIC_SYMBOL("CONNECTION-ITEM",AB_package);
    mutate_global_property(Qconnection_item,
	    The_type_description_of_connection_item,Qtype_description_of_type);
    Qoutstanding_connection_item_count = 
	    STATIC_SYMBOL("OUTSTANDING-CONNECTION-ITEM-COUNT",AB_package);
    Qconnection_item_structure_memory_usage = 
	    STATIC_SYMBOL("CONNECTION-ITEM-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_48 = STATIC_STRING("1q83Iky8s83t+y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_connection_item_count);
    push_optimized_constant(Qconnection_item_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_48));
    Qchain_of_available_connection_items = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CONNECTION-ITEMS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_connection_items,
	    Chain_of_available_connection_items);
    record_system_variable(Qchain_of_available_connection_items,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qconnection_item_count = STATIC_SYMBOL("CONNECTION-ITEM-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_item_count,Connection_item_count);
    record_system_variable(Qconnection_item_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qconnection_item_structure_memory_usage,
	    STATIC_FUNCTION(connection_item_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_connection_item_count,
	    STATIC_FUNCTION(outstanding_connection_item_count,NIL,FALSE,0,0));
    reclaim_structure_for_connection_item_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_connection_item,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qconnection_item,
	    reclaim_structure_for_connection_item_1);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qconnection_item_table = STATIC_SYMBOL("CONNECTION-ITEM-TABLE",AB_package);
    Qflow_pipe_junction = STATIC_SYMBOL("FLOW-PIPE-JUNCTION",AB_package);
    Qjunction_block_for_flow_pipe = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-FOR-FLOW-PIPE",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qflow_pipe_junction,
	    CONS(Qjunction_block_for_flow_pipe,temp),
	    Qsubstitute_class_and_kb_flags);
    Qinstrument_signal_junction = 
	    STATIC_SYMBOL("INSTRUMENT-SIGNAL-JUNCTION",AB_package);
    Qjunction_block_for_instrument_signal = 
	    STATIC_SYMBOL("JUNCTION-BLOCK-FOR-INSTRUMENT-SIGNAL",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qinstrument_signal_junction,
	    CONS(Qjunction_block_for_instrument_signal,temp),
	    Qsubstitute_class_and_kb_flags);
    Qstandard_flow_pipe_junction = 
	    STATIC_SYMBOL("STANDARD-FLOW-PIPE-JUNCTION",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qstandard_flow_pipe_junction,
	    CONS(Qjunction_block_for_flow_pipe,temp),
	    Qsubstitute_class_and_kb_flags);
    Qstandard_flow_pipe = STATIC_SYMBOL("STANDARD-FLOW-PIPE",AB_package);
    Qflow_pipe = STATIC_SYMBOL("FLOW-PIPE",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qstandard_flow_pipe,CONS(Qflow_pipe,temp),
	    Qsubstitute_class_and_kb_flags);
    Qstandard_flow_pipe_connection_class = 
	    STATIC_SYMBOL("STANDARD-FLOW-PIPE-CONNECTION-CLASS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qstandard_flow_pipe_connection_class,
	    CONS(Qflow_pipe,temp),Qsubstitute_class_and_kb_flags);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qstandard_flow_pipe_junction,
	    CONS(Qjunction_block_for_flow_pipe,temp),
	    Qsubstitute_class_and_kb_flags);
    Qinstrument_signal_connection_class = 
	    STATIC_SYMBOL("INSTRUMENT-SIGNAL-CONNECTION-CLASS",AB_package);
    Qinstrument_signal = STATIC_SYMBOL("INSTRUMENT-SIGNAL",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qinstrument_signal_connection_class,
	    CONS(Qinstrument_signal,temp),Qsubstitute_class_and_kb_flags);
    Qinput_1 = STATIC_SYMBOL("INPUT-1",AB_package);
    Qcontrol_block_input = STATIC_SYMBOL("CONTROL-BLOCK-INPUT",AB_package);
    Qput_control_block_input_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CONTROL-BLOCK-INPUT-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_control_block_input_where_slot_is_absent,
	    STATIC_FUNCTION(put_control_block_input_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qcontrol_block_input,
	    SYMBOL_FUNCTION(Qput_control_block_input_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qcontrol_block_input_1 = STATIC_SYMBOL("CONTROL-BLOCK-INPUT-1",AB_package);
    Qput_control_block_input_1_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CONTROL-BLOCK-INPUT-1-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_control_block_input_1_where_slot_is_absent,
	    STATIC_FUNCTION(put_control_block_input_1_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcontrol_block_input_1,
	    SYMBOL_FUNCTION(Qput_control_block_input_1_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qinput_2 = STATIC_SYMBOL("INPUT-2",AB_package);
    Qcontrol_block_input_2 = STATIC_SYMBOL("CONTROL-BLOCK-INPUT-2",AB_package);
    Qput_control_block_input_2_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CONTROL-BLOCK-INPUT-2-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_control_block_input_2_where_slot_is_absent,
	    STATIC_FUNCTION(put_control_block_input_2_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcontrol_block_input_2,
	    SYMBOL_FUNCTION(Qput_control_block_input_2_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qoutput_1 = STATIC_SYMBOL("OUTPUT-1",AB_package);
    Qcontrol_block_output = STATIC_SYMBOL("CONTROL-BLOCK-OUTPUT",AB_package);
    Qput_control_block_output_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-CONTROL-BLOCK-OUTPUT-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_control_block_output_where_slot_is_absent,
	    STATIC_FUNCTION(put_control_block_output_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qcontrol_block_output,
	    SYMBOL_FUNCTION(Qput_control_block_output_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qdont_include_offset_for_end_position_qm = 
	    STATIC_SYMBOL("DONT-INCLUDE-OFFSET-FOR-END-POSITION\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdont_include_offset_for_end_position_qm,
	    Dont_include_offset_for_end_position_qm);
    Qconnect1 = STATIC_SYMBOL("CONNECT1",AB_package);
    record_system_variable(Qdont_include_offset_for_end_position_qm,
	    Qconnect1,Nil,Qnil,Qnil,Qnil,Qnil);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qstripe_color = STATIC_SYMBOL("STRIPE-COLOR",AB_package);
    Connection_vertex_hit_distance = FIX((SI_Long)5L);
    Qg2_defstruct_structure_name_connection_spot_g2_struct = 
	    STATIC_SYMBOL("CONNECTION-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qconnection_spot = STATIC_SYMBOL("CONNECTION-SPOT",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_connection_spot_g2_struct,
	    Qconnection_spot,Qab_name_of_unique_structure_type);
    mutate_global_property(Qconnection_spot,
	    Qg2_defstruct_structure_name_connection_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_connection_spot == UNBOUND)
	The_type_description_of_connection_spot = Nil;
    string_constant_49 = 
	    STATIC_STRING("43Dy8m83gIy1o83gIy83Qy8n8k1l83Qy0000001l1m8x83Qykqk0k0");
    temp = The_type_description_of_connection_spot;
    The_type_description_of_connection_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_49));
    mutate_global_property(Qg2_defstruct_structure_name_connection_spot_g2_struct,
	    The_type_description_of_connection_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qconnection_spot,
	    The_type_description_of_connection_spot,Qtype_description_of_type);
    Qoutstanding_connection_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-CONNECTION-SPOT-COUNT",AB_package);
    Qconnection_spot_structure_memory_usage = 
	    STATIC_SYMBOL("CONNECTION-SPOT-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_50 = STATIC_STRING("1q83gIy8s83-O=y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_connection_spot_count);
    push_optimized_constant(Qconnection_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_50));
    Qchain_of_available_connection_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CONNECTION-SPOTS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_connection_spots,
	    Chain_of_available_connection_spots);
    record_system_variable(Qchain_of_available_connection_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qconnection_spot_count = STATIC_SYMBOL("CONNECTION-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qconnection_spot_count,Connection_spot_count);
    record_system_variable(Qconnection_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qconnection_spot_structure_memory_usage,
	    STATIC_FUNCTION(connection_spot_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_connection_spot_count,
	    STATIC_FUNCTION(outstanding_connection_spot_count,NIL,FALSE,0,0));
    reclaim_structure_for_connection_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_connection_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qconnection_spot,
	    reclaim_structure_for_connection_spot_1);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qconnection_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qimage_plane_spot),
	    LIST_2(Qabstract_type,Qnil),LIST_2(Qtype_of_frame_represented,
	    Qconnection),ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qgenerate_spot_for_connection = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-CONNECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_connection,
	    STATIC_FUNCTION(generate_spot_for_connection,NIL,FALSE,2,2));
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_connection);
    set_get(Qconnection,Qgenerate_spot,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qconnection,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qvertex = STATIC_SYMBOL("VERTEX",AB_package);
    Qconnection_style = STATIC_SYMBOL("CONNECTION-STYLE",AB_package);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    array_constant = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant,(SI_Long)0L,Qtop);
    ISASET_1(array_constant,(SI_Long)1L,Qleft);
    ISASET_1(array_constant,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant,(SI_Long)3L,Qright);
}
