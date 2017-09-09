/* debug.c
 * Input file:  debug.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "debug.h"


/* C-PUT-STRING-STDERR */
Object c_put_string_stderr(string_1)
    Object string_1;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(94,0);
    gensymed_symbol = copy_foreign_string_arg_if_appropriate(string_1);
    temp = gensymed_symbol;
    if (temp);
    else
	temp = string_1;
    g2ext_puts(ISTRING(temp));
    if (gensymed_symbol)
	reclaim_gensym_string(gensymed_symbol);
    return VALUES_1(Nil);
}

Object The_type_description_of_snapshot_invocation_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_snapshot_invocation_infos, Qchain_of_available_snapshot_invocation_infos);

DEFINE_VARIABLE_WITH_SYMBOL(Snapshot_invocation_info_count, Qsnapshot_invocation_info_count);

Object Chain_of_available_snapshot_invocation_infos_vector = UNBOUND;

/* SNAPSHOT-INVOCATION-INFO-STRUCTURE-MEMORY-USAGE */
Object snapshot_invocation_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(94,1);
    temp = Snapshot_invocation_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)6L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SNAPSHOT-INVOCATION-INFO-COUNT */
Object outstanding_snapshot_invocation_info_count()
{
    Object def_structure_snapshot_invocation_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(94,2);
    gensymed_symbol = IFIX(Snapshot_invocation_info_count);
    def_structure_snapshot_invocation_info_variable = 
	    Chain_of_available_snapshot_invocation_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_snapshot_invocation_info_variable))
	goto end_loop;
    def_structure_snapshot_invocation_info_variable = 
	    ISVREF(def_structure_snapshot_invocation_info_variable,
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

/* RECLAIM-SNAPSHOT-INVOCATION-INFO-1-1 */
Object reclaim_snapshot_invocation_info_1_1(snapshot_invocation_info)
    Object snapshot_invocation_info;
{
    Object temp, svref_arg_2;

    x_note_fn_call(94,3);
    inline_note_reclaim_cons(snapshot_invocation_info,Nil);
    temp = ISVREF(Chain_of_available_snapshot_invocation_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(snapshot_invocation_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_snapshot_invocation_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = snapshot_invocation_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SNAPSHOT-INVOCATION-INFO */
Object reclaim_structure_for_snapshot_invocation_info(snapshot_invocation_info)
    Object snapshot_invocation_info;
{
    x_note_fn_call(94,4);
    return reclaim_snapshot_invocation_info_1_1(snapshot_invocation_info);
}

static Object Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct;  /* g2-defstruct-structure-name::snapshot-invocation-info-g2-struct */

/* MAKE-PERMANENT-SNAPSHOT-INVOCATION-INFO-STRUCTURE-INTERNAL */
Object make_permanent_snapshot_invocation_info_structure_internal()
{
    Object def_structure_snapshot_invocation_info_variable;
    Object defstruct_g2_snapshot_invocation_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(94,5);
    def_structure_snapshot_invocation_info_variable = Nil;
    atomic_incff_symval(Qsnapshot_invocation_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_snapshot_invocation_info_variable = Nil;
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
	defstruct_g2_snapshot_invocation_info_variable = the_array;
	SVREF(defstruct_g2_snapshot_invocation_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct;
	def_structure_snapshot_invocation_info_variable = 
		defstruct_g2_snapshot_invocation_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_snapshot_invocation_info_variable);
}

/* MAKE-SNAPSHOT-INVOCATION-INFO-1 */
Object make_snapshot_invocation_info_1(snapshot_invocation_info_procedure,
	    snapshot_invocation_info_n_compiles_of_procedure,
	    snapshot_invocation_info_code_body,
	    snapshot_invocation_info_program_counter,
	    snapshot_invocation_info_code_body_index)
    Object snapshot_invocation_info_procedure;
    Object snapshot_invocation_info_n_compiles_of_procedure;
    Object snapshot_invocation_info_code_body;
    Object snapshot_invocation_info_program_counter;
    Object snapshot_invocation_info_code_body_index;
{
    Object def_structure_snapshot_invocation_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(94,6);
    def_structure_snapshot_invocation_info_variable = 
	    ISVREF(Chain_of_available_snapshot_invocation_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_snapshot_invocation_info_variable) {
	svref_arg_1 = Chain_of_available_snapshot_invocation_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_snapshot_invocation_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_snapshot_invocation_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct;
    }
    else
	def_structure_snapshot_invocation_info_variable = 
		make_permanent_snapshot_invocation_info_structure_internal();
    inline_note_allocate_cons(def_structure_snapshot_invocation_info_variable,
	    Nil);
    SVREF(def_structure_snapshot_invocation_info_variable,
	    FIX((SI_Long)1L)) = snapshot_invocation_info_procedure;
    SVREF(def_structure_snapshot_invocation_info_variable,
	    FIX((SI_Long)2L)) = 
	    snapshot_invocation_info_n_compiles_of_procedure;
    SVREF(def_structure_snapshot_invocation_info_variable,
	    FIX((SI_Long)3L)) = snapshot_invocation_info_code_body;
    SVREF(def_structure_snapshot_invocation_info_variable,
	    FIX((SI_Long)4L)) = snapshot_invocation_info_program_counter;
    SVREF(def_structure_snapshot_invocation_info_variable,
	    FIX((SI_Long)5L)) = snapshot_invocation_info_code_body_index;
    return VALUES_1(def_structure_snapshot_invocation_info_variable);
}

/* RECLAIM-SNAPSHOT-INVOCATION-INFO */
Object reclaim_snapshot_invocation_info(struct_qm)
    Object struct_qm;
{
    x_note_fn_call(94,7);
    if (struct_qm)
	reclaim_snapshot_invocation_info_1_1(struct_qm);
    return VALUES_1(Nil);
}

/* COPY-SNAPSHOT-INVOCATION-INFO */
Object copy_snapshot_invocation_info(snapshot_invocation_info)
    Object snapshot_invocation_info;
{
    Object temp;

    x_note_fn_call(94,8);
    temp = make_snapshot_invocation_info_1(ISVREF(snapshot_invocation_info,
	    (SI_Long)1L),ISVREF(snapshot_invocation_info,(SI_Long)2L),
	    ISVREF(snapshot_invocation_info,(SI_Long)3L),
	    ISVREF(snapshot_invocation_info,(SI_Long)4L),
	    ISVREF(snapshot_invocation_info,(SI_Long)5L));
    return VALUES_1(temp);
}

/* SNAPSHOT-INVOCATION-INFO-STALE-P */
Object snapshot_invocation_info_stale_p(snapshot_invocation_info)
    Object snapshot_invocation_info;
{
    Object temp;

    x_note_fn_call(94,9);
    temp = ISVREF(snapshot_invocation_info,(SI_Long)2L);
    temp = FIXNUM_NE(temp,
	    n_compiles_this_session_function(ISVREF(snapshot_invocation_info,
	    (SI_Long)1L))) ? T : Nil;
    return VALUES_1(temp);
}

Object The_type_description_of_snapshot_of_block = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_snapshot_of_blocks, Qchain_of_available_snapshot_of_blocks);

DEFINE_VARIABLE_WITH_SYMBOL(Snapshot_of_block_count, Qsnapshot_of_block_count);

Object Chain_of_available_snapshot_of_blocks_vector = UNBOUND;

/* SNAPSHOT-OF-BLOCK-STRUCTURE-MEMORY-USAGE */
Object snapshot_of_block_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(94,10);
    temp = Snapshot_of_block_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-SNAPSHOT-OF-BLOCK-COUNT */
Object outstanding_snapshot_of_block_count()
{
    Object def_structure_snapshot_of_block_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(94,11);
    gensymed_symbol = IFIX(Snapshot_of_block_count);
    def_structure_snapshot_of_block_variable = 
	    Chain_of_available_snapshot_of_blocks;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_snapshot_of_block_variable))
	goto end_loop;
    def_structure_snapshot_of_block_variable = 
	    ISVREF(def_structure_snapshot_of_block_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-SNAPSHOT-OF-BLOCK-1 */
Object reclaim_snapshot_of_block_1(snapshot_of_block)
    Object snapshot_of_block;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(94,12);
    inline_note_reclaim_cons(snapshot_of_block,Nil);
    structure_being_reclaimed = snapshot_of_block;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_snapshot_invocation_info(ISVREF(snapshot_of_block,(SI_Long)2L));
      SVREF(snapshot_of_block,FIX((SI_Long)2L)) = Nil;
      reclaim_frame_serial_number(ISVREF(snapshot_of_block,(SI_Long)3L));
      SVREF(snapshot_of_block,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_snapshot_of_blocks_vector,
	    IFIX(Current_thread_index));
    SVREF(snapshot_of_block,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_snapshot_of_blocks_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = snapshot_of_block;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-SNAPSHOT-OF-BLOCK */
Object reclaim_structure_for_snapshot_of_block(snapshot_of_block)
    Object snapshot_of_block;
{
    x_note_fn_call(94,13);
    return reclaim_snapshot_of_block_1(snapshot_of_block);
}

static Object Qg2_defstruct_structure_name_snapshot_of_block_g2_struct;  /* g2-defstruct-structure-name::snapshot-of-block-g2-struct */

/* MAKE-PERMANENT-SNAPSHOT-OF-BLOCK-STRUCTURE-INTERNAL */
Object make_permanent_snapshot_of_block_structure_internal()
{
    Object def_structure_snapshot_of_block_variable;
    Object defstruct_g2_snapshot_of_block_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(94,14);
    def_structure_snapshot_of_block_variable = Nil;
    atomic_incff_symval(Qsnapshot_of_block_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_snapshot_of_block_variable = Nil;
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
	defstruct_g2_snapshot_of_block_variable = the_array;
	SVREF(defstruct_g2_snapshot_of_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_snapshot_of_block_g2_struct;
	def_structure_snapshot_of_block_variable = 
		defstruct_g2_snapshot_of_block_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_snapshot_of_block_variable);
}

/* MAKE-SNAPSHOT-OF-BLOCK-1-1 */
Object make_snapshot_of_block_1_1()
{
    Object def_structure_snapshot_of_block_variable, svref_arg_1, svref_arg_2;
    Object svref_new_value;

    x_note_fn_call(94,15);
    def_structure_snapshot_of_block_variable = 
	    ISVREF(Chain_of_available_snapshot_of_blocks_vector,
	    IFIX(Current_thread_index));
    if (def_structure_snapshot_of_block_variable) {
	svref_arg_1 = Chain_of_available_snapshot_of_blocks_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = ISVREF(def_structure_snapshot_of_block_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_snapshot_of_block_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_snapshot_of_block_g2_struct;
    }
    else
	def_structure_snapshot_of_block_variable = 
		make_permanent_snapshot_of_block_structure_internal();
    inline_note_allocate_cons(def_structure_snapshot_of_block_variable,Nil);
    SVREF(def_structure_snapshot_of_block_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_snapshot_of_block_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_snapshot_of_block_variable,FIX((SI_Long)3L)) = Nil;
    return VALUES_1(def_structure_snapshot_of_block_variable);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* OK-TO-GET-SOURCE-CODE-LOOKUP-INFO-P */
Object ok_to_get_source_code_lookup_info_p(computation_instance)
    Object computation_instance;
{
    Object x2, temp_1;
    char temp;

    x_note_fn_call(94,16);
    if (computation_instance) {
	if (SIMPLE_VECTOR_P(computation_instance) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(computation_instance)) > 
		(SI_Long)2L &&  !EQ(ISVREF(computation_instance,
		(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(computation_instance,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    temp_1 = temp ? code_body_invocation_qm(computation_instance) : Nil;
    return VALUES_1(temp_1);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_computation_instance, Qcurrent_computation_instance);

DEFINE_VARIABLE_WITH_SYMBOL(Cached_stack_frame_base, Qcached_stack_frame_base);

/* MAKE-SNAPSHOT-OF-BLOCK */
Object make_snapshot_of_block(block)
    Object block;
{
    Object snapshot, frame_serial_number_setf_arg, old, new_1, svref_new_value;
    Object computation_instance_for_block_qm, index_qm, program_counter_qm;
    Object temp;
    Object result;

    x_note_fn_call(94,17);
    snapshot = make_snapshot_of_block_1_1();
    SVREF(snapshot,FIX((SI_Long)1L)) = block;
    frame_serial_number_setf_arg = ISVREF(block,(SI_Long)3L);
    old = ISVREF(snapshot,(SI_Long)3L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    SVREF(snapshot,FIX((SI_Long)3L)) = svref_new_value;
    if (procedure_qm(block) && Current_computation_instance) {
	result = get_computation_instance_for_block(block,
		Current_computation_frame,Current_computation_instance,
		Cached_stack_frame_base);
	MVS_2(result,computation_instance_for_block_qm,index_qm);
	if (computation_instance_for_block_qm && 
		ok_to_get_source_code_lookup_info_p(computation_instance_for_block_qm)) 
		    {
	    program_counter_qm = 
		    invocation_stack_program_counter_function(computation_instance_for_block_qm);
	    if (program_counter_qm) {
		temp = n_compiles_this_session_function(block);
		svref_new_value = make_snapshot_invocation_info_1(block,
			temp,
			code_body_of_invocation_function(computation_instance_for_block_qm),
			program_counter_qm,index_qm);
		SVREF(snapshot,FIX((SI_Long)2L)) = svref_new_value;
	    }
	}
    }
    return VALUES_1(snapshot);
}

/* COPY-SNAPSHOT-OF-BLOCK */
Object copy_snapshot_of_block(snapshot_of_block)
    Object snapshot_of_block;
{
    Object new_1, svref_new_value, invocation_info_qm;

    x_note_fn_call(94,18);
    new_1 = make_snapshot_of_block_1_1();
    svref_new_value = ISVREF(snapshot_of_block,(SI_Long)1L);
    SVREF(new_1,FIX((SI_Long)1L)) = svref_new_value;
    svref_new_value = copy_frame_serial_number(ISVREF(snapshot_of_block,
	    (SI_Long)3L));
    SVREF(new_1,FIX((SI_Long)3L)) = svref_new_value;
    invocation_info_qm = ISVREF(snapshot_of_block,(SI_Long)2L);
    svref_new_value = invocation_info_qm ? 
	    copy_snapshot_invocation_info(invocation_info_qm) : Qnil;
    SVREF(new_1,FIX((SI_Long)2L)) = svref_new_value;
    return VALUES_1(new_1);
}

/* SNAPSHOT-OF-BLOCK-VALID-P */
Object snapshot_of_block_valid_p(snapshot_of_block)
    Object snapshot_of_block;
{
    Object gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(94,19);
    gensymed_symbol = ISVREF(ISVREF(snapshot_of_block,(SI_Long)1L),
	    (SI_Long)3L);
    x = ISVREF(snapshot_of_block,(SI_Long)1L);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = ISVREF(snapshot_of_block,(SI_Long)3L);
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
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) : 
			TRUEP(Qnil);
	}
    }
    return VALUES_1( !temp ? T : Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Snapshots_of_related_blocks, Qsnapshots_of_related_blocks);

/* RECORD-BLOCK-FOR-TFORMAT */
Object record_block_for_tformat(block_or_snapshot_of_block)
    Object block_or_snapshot_of_block;
{
    Object block, snapshot, ab_loop_list_, ab_loop_it_, temp_1;
    char temp;

    x_note_fn_call(94,20);
    block = SIMPLE_VECTOR_P(block_or_snapshot_of_block) && 
	    EQ(ISVREF(block_or_snapshot_of_block,(SI_Long)0L),
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct) ? 
	    ISVREF(block_or_snapshot_of_block,(SI_Long)1L) : 
	    block_or_snapshot_of_block;
    snapshot = Nil;
    ab_loop_list_ = Snapshots_of_related_blocks;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    snapshot = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(block,ISVREF(snapshot,(SI_Long)1L)) ? T : Nil;
    if (ab_loop_it_) {
	temp = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop;
  end_loop:
    temp = TRUEP(Qnil);
  end_1:;
    if ( !temp) {
	temp_1 = Snapshots_of_related_blocks;
	Snapshots_of_related_blocks = nconc2(temp_1,
		slot_value_cons_1(SIMPLE_VECTOR_P(block_or_snapshot_of_block) 
		&& EQ(ISVREF(block_or_snapshot_of_block,(SI_Long)0L),
		Qg2_defstruct_structure_name_snapshot_of_block_g2_struct) ?
		 copy_snapshot_of_block(block_or_snapshot_of_block) : 
		make_snapshot_of_block(block),Nil));
	temp_1 = Snapshots_of_related_blocks;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* RECLAIM-LIST-OF-BLOCK-SNAPSHOTS */
Object reclaim_list_of_block_snapshots(snapshots)
    Object snapshots;
{
    Object snapshot, ab_loop_list_;

    x_note_fn_call(94,21);
    if (snapshots) {
	snapshot = Nil;
	ab_loop_list_ = snapshots;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	snapshot = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_snapshot_of_block_1(snapshot);
	goto next_loop;
      end_loop:;
	return reclaim_slot_value_list_1(snapshots);
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-ERROR-TEXT */
Object make_error_text(text_string,blocks)
    Object text_string, blocks;
{
    x_note_fn_call(94,22);
    if (blocks)
	return slot_value_cons_1(text_string,blocks);
    else
	return VALUES_1(text_string);
}

/* ERROR-TEXT-P */
Object error_text_p(thing)
    Object thing;
{
    Object temp;

    x_note_fn_call(94,23);
    temp = text_string_p(thing);
    if (temp)
	return VALUES_1(temp);
    else if (CONSP(thing))
	return text_string_p(CONSP(thing) ? FIRST(thing) : thing);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ERROR-TEXT */
Object reclaim_error_text(error_text)
    Object error_text;
{
    Object string_1, things, thing, ab_loop_list_;

    x_note_fn_call(94,24);
    string_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    things = CONSP(error_text) ? REST(error_text) : Nil;
    if (T)
	reclaim_text_string(string_1);
    if (things) {
	thing = Nil;
	ab_loop_list_ = things;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	thing = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_snapshot_of_block_g2_struct))
	    reclaim_snapshot_of_block_1(thing);
	goto next_loop;
      end_loop:;
    }
    if (CONSP(error_text))
	return reclaim_slot_value_list_1(error_text);
    else
	return VALUES_1(Nil);
}

/* RECLAIM-ERROR-TEXT-BUT-NOT-STRING */
Object reclaim_error_text_but_not_string(error_text)
    Object error_text;
{
    Object string_1, things, thing, ab_loop_list_;

    x_note_fn_call(94,25);
    string_1 = CONSP(error_text) ? FIRST(error_text) : error_text;
    things = CONSP(error_text) ? REST(error_text) : Nil;
    if (Nil)
	reclaim_text_string(string_1);
    if (things) {
	thing = Nil;
	ab_loop_list_ = things;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	thing = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(thing) && EQ(ISVREF(thing,(SI_Long)0L),
		Qg2_defstruct_structure_name_snapshot_of_block_g2_struct))
	    reclaim_snapshot_of_block_1(thing);
	goto next_loop;
      end_loop:;
    }
    if (CONSP(error_text))
	return reclaim_slot_value_list_1(error_text);
    else
	return VALUES_1(Nil);
}

/* WRITE-ERROR-TEXT */
Object write_error_text(error_text)
    Object error_text;
{
    Object block, ab_loop_list_;

    x_note_fn_call(94,26);
    twrite(CONSP(error_text) ? FIRST(error_text) : error_text);
    if (Note_blocks_in_tformat) {
	block = Nil;
	ab_loop_list_ = CONSP(error_text) ? REST(error_text) : Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	block = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	inline_funcall_1(Note_blocks_in_tformat,block);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Kstack_error;        /* :stack-error */

/* APPLY-CATCHING-STACK-ERRORS */
Object apply_catching_stack_errors(function,args)
    Object function, args;
{
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp;
    Declare_catch(1);
    Object result;

    x_note_fn_call(94,27);
    if (PUSH_CATCH(Kstack_error,0)) {
	APPLY_1(function,args);
	reclaim_gensym_list_1(args);
	result = VALUES_1(Nil);
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    reclaim_gensym_list_1(args);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    result = VALUES_1(temp);
  end_gensymed_symbol:
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Stack_of_deferred_notification_strings, Qstack_of_deferred_notification_strings);

/* TRY-TO-DO-DEFERRED-USER-NOTIFICATIONS */
Object try_to_do_deferred_user_notifications()
{
    Object reversed_stack, element, ab_loop_list_, notification_string;
    Object notification_snapshots, snapshots_of_related_blocks;
    Declare_special(1);

    x_note_fn_call(94,28);
    if (Stack_of_deferred_notification_strings) {
	reversed_stack = nreverse(Stack_of_deferred_notification_strings);
	Stack_of_deferred_notification_strings = Nil;
	element = Nil;
	ab_loop_list_ = reversed_stack;
	notification_string = Nil;
	notification_snapshots = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	notification_string = car_or_atom(element);
	notification_snapshots = cdr_or_atom(element);
	snapshots_of_related_blocks = notification_snapshots;
	PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		0);
	  notify_user_2(notification_string);
	  if (Snapshots_of_related_blocks)
	      reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
	  if (CONSP(element))
	      reclaim_slot_value_cons_1(element);
	POP_SPECIAL();
	goto next_loop;
      end_loop:;
	reclaim_slot_value_list_1(reversed_stack);
	return VALUES_1(T);
    }
    else
	return VALUES_1(Nil);
}

static Object Qrecord_block_for_tformat;  /* record-block-for-tformat */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

/* NOTIFY-USER */
Object notify_user varargs_1(int, n)
{
    Object notification_as_format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(94,29);
    INIT_ARGS_nonrelocating();
    notification_as_format_string = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    snapshots_of_related_blocks = Nil;
    note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
    PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
	    6);
      PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
	      5);
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
		  if (EQ(arg1,No_arg))
		      tformat(1,notification_as_format_string);
		  else if (EQ(arg2,No_arg))
		      tformat(2,notification_as_format_string,arg1);
		  else if (EQ(arg3,No_arg))
		      tformat(3,notification_as_format_string,arg1,arg2);
		  else if (EQ(arg4,No_arg))
		      tformat(4,notification_as_format_string,arg1,arg2,arg3);
		  else if (EQ(arg5,No_arg))
		      tformat(5,notification_as_format_string,arg1,arg2,
			      arg3,arg4);
		  else if (EQ(arg6,No_arg))
		      tformat(6,notification_as_format_string,arg1,arg2,
			      arg3,arg4,arg5);
		  else if (EQ(arg7,No_arg))
		      tformat(7,notification_as_format_string,arg1,arg2,
			      arg3,arg4,arg5,arg6);
		  else if (EQ(arg8,No_arg))
		      tformat(8,notification_as_format_string,arg1,arg2,
			      arg3,arg4,arg5,arg6,arg7);
		  else if (EQ(arg9,No_arg))
		      tformat(9,notification_as_format_string,arg1,arg2,
			      arg3,arg4,arg5,arg6,arg7,arg8);
		  else
		      tformat(10,notification_as_format_string,arg1,arg2,
			      arg3,arg4,arg5,arg6,arg7,arg8,arg9);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	SAVE_VALUES(notify_user_1(temp));
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

static Object string_constant;     /* "log: ~A" */

/* NOTIFY-USER-1 */
Object notify_user_1(notification_string)
    Object notification_string;
{
    Object defer_notifications_qm;
    Declare_special(1);

    x_note_fn_call(94,30);
    if (Send_logbook_messages_to_console_p)
	notify_user_at_console(2,string_constant,notification_string);
    if (Defer_notifications_qm) {
	Stack_of_deferred_notification_strings = 
		slot_value_cons_1(Snapshots_of_related_blocks ? 
		slot_value_cons_1(notification_string,
		Snapshots_of_related_blocks) : notification_string,
		Stack_of_deferred_notification_strings);
	Snapshots_of_related_blocks = Nil;
	return VALUES_1(Snapshots_of_related_blocks);
    }
    else {
	defer_notifications_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
		0);
	  notify_user_2(notification_string);
	POP_SPECIAL();
	return try_to_do_deferred_user_notifications();
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Debugging_parameters, Qdebugging_parameters);

/* PUT-KB-TIMESTAMP-FIELD-1-WHERE-SLOT-IS-ABSENT */
Object put_kb_timestamp_field_1_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(94,31);
    return VALUES_1(Nil);
}

/* PUT-KB-TIMESTAMP-FIELD-2-WHERE-SLOT-IS-ABSENT */
Object put_kb_timestamp_field_2_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(94,32);
    return VALUES_1(Nil);
}

/* PUT-KB-TIMESTAMP-FIELD-3-WHERE-SLOT-IS-ABSENT */
Object put_kb_timestamp_field_3_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(94,33);
    return VALUES_1(Nil);
}

/* PUT-KB-TIMESTAMP-FIELD-4-WHERE-SLOT-IS-ABSENT */
Object put_kb_timestamp_field_4_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(94,34);
    return VALUES_1(Nil);
}

/* PUT-KB-TIMESTAMP-FIELD-5-WHERE-SLOT-IS-ABSENT */
Object put_kb_timestamp_field_5_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(94,35);
    return VALUES_1(Nil);
}

/* PUT-TASK-FRAGMENTATION-MAP-6-WHERE-SLOT-IS-ABSENT */
Object put_task_fragmentation_map_6_where_slot_is_absent(frame,value)
    Object frame, value;
{
    x_note_fn_call(94,36);
    return VALUES_1(Nil);
}

/* ACTIVATE-SUBCLASS-OF-ENTITY-FOR-DEBUGGING-PARAMETERS */
Object activate_subclass_of_entity_for_debugging_parameters(debugging_parameters)
    Object debugging_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(94,37);
    PUSH_SPECIAL_WITH_SYMBOL(Debugging_parameters,Qdebugging_parameters,debugging_parameters,
	    0);
      if ( !((SI_Long)0L != (IFIX(ISVREF(Debugging_parameters,
	      (SI_Long)5L)) & (SI_Long)1L))) {
	  close_tracing_file();
	  result = open_tracing_file(T);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-DEBUGGING-PARAMETERS */
Object deactivate_subclass_of_entity_for_debugging_parameters(debugging_parameters)
    Object debugging_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(94,38);
    PUSH_SPECIAL_WITH_SYMBOL(Debugging_parameters,Qdebugging_parameters,debugging_parameters,
	    0);
      if ((SI_Long)0L != (IFIX(ISVREF(Debugging_parameters,(SI_Long)5L)) & 
	      (SI_Long)1L))
	  result = close_tracing_file();
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

DEFINE_VARIABLE_WITH_SYMBOL(Warning_message_level, Qwarning_message_level);

DEFINE_VARIABLE_WITH_SYMBOL(Tracing_message_level, Qtracing_message_level);

DEFINE_VARIABLE_WITH_SYMBOL(Breakpoint_level, Qbreakpoint_level);

DEFINE_VARIABLE_WITH_SYMBOL(Source_stepping_level, Qsource_stepping_level);

DEFINE_VARIABLE_WITH_SYMBOL(Debugging_reset, Qdebugging_reset);

DEFINE_VARIABLE_WITH_SYMBOL(Disassemble_enabled_qm, Qdisassemble_enabled_qm);

DEFINE_VARIABLE_WITH_SYMBOL(Show_procedure_invocation_hierarchy_on_debugger_pause_p, Qshow_procedure_invocation_hierarchy_on_debugger_pause_p);

/* RESTORE-DEBUGGING-PARAMETERS-TO-DEFAULT-VALUES */
Object restore_debugging_parameters_to_default_values()
{
    Object code;
    char temp;

    x_note_fn_call(94,39);
    Warning_message_level = FIX((SI_Long)2L);
    Tracing_message_level = FIX((SI_Long)2L);
    Breakpoint_level = FIX((SI_Long)0L);
    Source_stepping_level = FIX((SI_Long)0L);
    Debugging_reset = Nil;
    Disassemble_enabled_qm = Nil;
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    Generate_source_annotation_info =  !temp ? T : Nil;
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    Show_procedure_invocation_hierarchy_on_debugger_pause_p =  !temp ? T : Nil;
    return VALUES_1(Show_procedure_invocation_hierarchy_on_debugger_pause_p);
}

static Object Qdisassembler_enabled;  /* disassembler-enabled */

static Object Qshow_procedure_invocation_hierarchy_at_pause_from_breakpoint;  /* show-procedure-invocation-hierarchy-at-pause-from-breakpoint */

/* INSTALL-SYSTEM-TABLE-FOR-DEBUGGING-PARAMETERS */
Object install_system_table_for_debugging_parameters(debugging_parameters)
    Object debugging_parameters;
{
    Object code;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(94,40);
    PUSH_SPECIAL_WITH_SYMBOL(Debugging_parameters,Qdebugging_parameters,debugging_parameters,
	    0);
      Warning_message_level = 
	      get_lookup_slot_value_given_default(Debugging_parameters,
	      Qwarning_message_level,FIX((SI_Long)2L));
      Tracing_message_level = 
	      get_lookup_slot_value_given_default(Debugging_parameters,
	      Qtracing_message_level,FIX((SI_Long)0L));
      Breakpoint_level = 
	      get_lookup_slot_value_given_default(Debugging_parameters,
	      Qbreakpoint_level,FIX((SI_Long)0L));
      Source_stepping_level = 
	      get_lookup_slot_value_given_default(Debugging_parameters,
	      Qsource_stepping_level,FIX((SI_Long)0L));
      if (get_lookup_slot_value_given_default(Debugging_parameters,
	      Qdisassembler_enabled,Nil)) {
	  code = M_CAR(M_CDR(Sparse_known_pathnames_list));
	  temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != 
		  (SI_Long)0L : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = 
		      TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
	  if (temp);
	  else {
	      code = M_CAR(M_CDR(Redo_saved_changes));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	      if (temp);
	      else
		  temp = TRUEP(SECOND(Old_eval_cons_list));
	  }
	  if (temp);
	  else {
	      code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
	  }
	  Disassemble_enabled_qm =  !temp ? T : Nil;
      }
      else
	  Disassemble_enabled_qm = Nil;
      if (get_lookup_slot_value_given_default(Debugging_parameters,
	      Qshow_procedure_invocation_hierarchy_at_pause_from_breakpoint,
		  T)) {
	  code = M_CAR(M_CDR(Sparse_known_pathnames_list));
	  temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != 
		  (SI_Long)0L : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = 
		      TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
	  if (temp);
	  else {
	      code = M_CAR(M_CDR(Redo_saved_changes));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	      if (temp);
	      else
		  temp = TRUEP(SECOND(Old_eval_cons_list));
	  }
	  if (temp);
	  else {
	      code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
	  }
	  Show_procedure_invocation_hierarchy_on_debugger_pause_p =  !temp 
		  ? T : Nil;
      }
      else
	  Show_procedure_invocation_hierarchy_on_debugger_pause_p = Nil;
      if (get_lookup_slot_value_given_default(Debugging_parameters,
	      Qgenerate_source_annotation_info,T)) {
	  code = M_CAR(M_CDR(Sparse_known_pathnames_list));
	  temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != 
		  (SI_Long)0L : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = 
		      TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
	  if (temp);
	  else {
	      code = M_CAR(M_CDR(Redo_saved_changes));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	      if (temp);
	      else
		  temp = TRUEP(SECOND(Old_eval_cons_list));
	  }
	  if (temp);
	  else {
	      code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	      temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		      (SI_Long)0L : TRUEP(Qnil);
	      if (temp);
	      else
		  temp = 
			  TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
	  }
	  Generate_source_annotation_info =  !temp ? T : Nil;
      }
      else
	  Generate_source_annotation_info = Nil;
      result = open_tracing_file(Nil);
    POP_SPECIAL();
    return result;
}

/* DEINSTALL-SYSTEM-TABLE-FOR-DEBUGGING-PARAMETERS */
Object deinstall_system_table_for_debugging_parameters(debugging_parameters)
    Object debugging_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(94,41);
    PUSH_SPECIAL_WITH_SYMBOL(Debugging_parameters,Qdebugging_parameters,debugging_parameters,
	    0);
      restore_debugging_parameters_to_default_values();
      result = close_tracing_file();
    POP_SPECIAL();
    return result;
}

/* PUT-WARNING-MESSAGE-LEVEL */
Object put_warning_message_level(debugging_parameters_instance,value,
	    gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    x_note_fn_call(94,42);
    if (system_table_installed_p(debugging_parameters_instance))
	Warning_message_level = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qwarning_message_level);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qwarning_message_level,value);
}

/* PUT-TRACING-MESSAGE-LEVEL */
Object put_tracing_message_level(debugging_parameters_instance,value,
	    gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    x_note_fn_call(94,43);
    if (system_table_installed_p(debugging_parameters_instance))
	Tracing_message_level = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qtracing_message_level);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qtracing_message_level,value);
}

/* PUT-BREAKPOINT-LEVEL */
Object put_breakpoint_level(debugging_parameters_instance,value,
	    gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    x_note_fn_call(94,44);
    if (system_table_installed_p(debugging_parameters_instance))
	Breakpoint_level = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qbreakpoint_level);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qbreakpoint_level,value);
}

/* PUT-SOURCE-STEPPING-LEVEL */
Object put_source_stepping_level(debugging_parameters_instance,value,
	    gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    x_note_fn_call(94,45);
    if (system_table_installed_p(debugging_parameters_instance))
	Source_stepping_level = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qsource_stepping_level);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qsource_stepping_level,value);
}

/* PUT-DISASSEMBLER-ENABLED */
Object put_disassembler_enabled(debugging_parameters_instance,value,
	    gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    Object code;
    char temp;

    x_note_fn_call(94,46);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp)
	value = Nil;
    if (system_table_installed_p(debugging_parameters_instance))
	Disassemble_enabled_qm = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qdisassembler_enabled);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qdisassembler_enabled,value);
}

/* PUT-SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT */
Object put_show_procedure_invocation_hierarchy_at_pause_from_breakpoint(debugging_parameters_instance,
	    value,gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    Object code;
    char temp;

    x_note_fn_call(94,47);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp)
	value = Nil;
    if (system_table_installed_p(debugging_parameters_instance))
	Show_procedure_invocation_hierarchy_on_debugger_pause_p = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qshow_procedure_invocation_hierarchy_at_pause_from_breakpoint);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qshow_procedure_invocation_hierarchy_at_pause_from_breakpoint,
	    value);
}

/* PUT-GENERATE-SOURCE-ANNOTATION-INFO */
Object put_generate_source_annotation_info(debugging_parameters_instance,
	    value,gensymed_symbol)
    Object debugging_parameters_instance, value, gensymed_symbol;
{
    Object code;
    char temp;

    x_note_fn_call(94,48);
    code = M_CAR(M_CDR(Sparse_known_pathnames_list));
    temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)512L) != (SI_Long)0L : 
	    TRUEP(Qnil);
    if (temp);
    else
	temp = 
		TRUEP(M_CAR(M_CDR(Cache_restricted_use_option_semantics_graph)));
    if (temp);
    else {
	code = M_CAR(M_CDR(Redo_saved_changes));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)64L) != (SI_Long)0L :
		 TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_runtime_option_semantics_graph)));
	if (temp);
	else
	    temp = TRUEP(SECOND(Old_eval_cons_list));
    }
    if (temp);
    else {
	code = M_CAR(M_CDR(Learned_list_to_expedite_ui));
	temp = FIXNUMP(code) ? (IFIX(code) & (SI_Long)1024L) != 
		(SI_Long)0L : TRUEP(Qnil);
	if (temp);
	else
	    temp = TRUEP(M_CAR(M_CDR(Cache_embedded_option_semantics_graph)));
    }
    if (temp)
	value = Nil;
    if (system_table_installed_p(debugging_parameters_instance))
	Generate_source_annotation_info = value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(debugging_parameters_instance,
		Qgenerate_source_annotation_info);
    return set_lookup_slot_value_1(debugging_parameters_instance,
	    Qgenerate_source_annotation_info,value);
}

static Object string_constant_1;   /* "0 (no warning messages)" */

static Object string_constant_2;   /* "1 (kb errors only)" */

static Object string_constant_3;   /* "2 (kb errors and deficiencies)" */

static Object string_constant_4;   /* "3 (kb errors, deficiencies, and other conditions)" */

/* WRITE-WARNING-MESSAGE-LEVEL-FROM-SLOT */
Object write_warning_message_level_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(94,49);
    if ( !(FIXNUMP(value) && FIXNUM_LE(FIX((SI_Long)-128L),value) && 
	    FIXNUM_LE(value,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(value)) {
	  case 0:
	    temp = string_constant_1;
	    break;
	  case 1:
	    temp = string_constant_2;
	    break;
	  case 2:
	    temp = string_constant_3;
	    break;
	  case 3:
	    temp = string_constant_4;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return twrite(temp);
}

static Object string_constant_5;   /* "0 (no trace messages)" */

static Object string_constant_6;   /* "1 (trace messages on entry and exit)" */

static Object string_constant_7;   /* "2 (trace messages at major steps)" */

static Object string_constant_8;   /* "3 (trace messages at every step)" */

/* WRITE-TRACING-MESSAGE-LEVEL-FROM-SLOT */
Object write_tracing_message_level_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(94,50);
    if ( !(FIXNUMP(value) && FIXNUM_LE(FIX((SI_Long)-128L),value) && 
	    FIXNUM_LE(value,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(value)) {
	  case 0:
	    temp = string_constant_5;
	    break;
	  case 1:
	    temp = string_constant_6;
	    break;
	  case 2:
	    temp = string_constant_7;
	    break;
	  case 3:
	    temp = string_constant_8;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return twrite(temp);
}

static Object string_constant_9;   /* "0 (no breakpoints)" */

static Object string_constant_10;  /* "1 (breakpoints on entry and exit)" */

static Object string_constant_11;  /* "2 (breakpoints at major steps)" */

static Object string_constant_12;  /* "3 (breakpoints at every step)" */

/* WRITE-BREAKPOINT-LEVEL-FROM-SLOT */
Object write_breakpoint_level_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(94,51);
    if ( !(FIXNUMP(value) && FIXNUM_LE(FIX((SI_Long)-128L),value) && 
	    FIXNUM_LE(value,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(value)) {
	  case 0:
	    temp = string_constant_9;
	    break;
	  case 1:
	    temp = string_constant_10;
	    break;
	  case 2:
	    temp = string_constant_11;
	    break;
	  case 3:
	    temp = string_constant_12;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return twrite(temp);
}

static Object string_constant_13;  /* "0 (no source stepping)" */

static Object string_constant_14;  /* "1 (source stepping)" */

/* WRITE-SOURCE-STEPPING-LEVEL-FROM-SLOT */
Object write_source_stepping_level_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(94,52);
    if ( !(FIXNUMP(value) && FIXNUM_LE(FIX((SI_Long)-128L),value) && 
	    FIXNUM_LE(value,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(value)) {
	  case 0:
	    temp = string_constant_13;
	    break;
	  case 1:
	    temp = string_constant_14;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    return twrite(temp);
}

static Object list_constant;       /* # */

/* COMPILE-MESSAGE-OVERRIDES-FOR-SLOT */
Object compile_message_overrides_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(94,53);
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
    temp = assq_function(parse_result,list_constant);
    return VALUES_1(CDR(temp));
}

static Object Qno_messages;        /* no-messages */

static Object string_constant_15;  /* "no breakpoints or trace messages" */

static Object Qno_breakpoints;     /* no-breakpoints */

static Object string_constant_16;  /* "no breakpoints, trace messages enabled" */

static Object string_constant_17;  /* "breakpoints and trace messages enabled" */

/* WRITE-MESSAGE-OVERRIDES-FROM-SLOT */
Object write_message_overrides_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    Object temp;

    x_note_fn_call(94,54);
    if (EQ(value,Qno_messages))
	temp = string_constant_15;
    else if (EQ(value,Qno_breakpoints))
	temp = string_constant_16;
    else
	temp = string_constant_17;
    return twrite(temp);
}

Object Debugging_shift_alist = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Disable_tracing_and_breakpoints_warning, Qdisable_tracing_and_breakpoints_warning);

static Object Qdefault;            /* default */

static Object Qsc;                 /* \; */

static Object string_constant_18;  /* "Note that messages and/or breakpoints have been disabled." */

/* COMPILE-TRACING-AND-BREAKPOINTS-FOR-SLOT */
Object compile_tracing_and_breakpoints_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object encoded_parameters, result_1, keyword, level, ab_loop_list_, shift;
    Object ab_loop_desetq_, temp, tracing, breakpoint, source_stepping;
    Object overrides;
    SI_Long gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(94,55);
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
	encoded_parameters = Nil;
    else if (EQ(CAR(parse_result),Qsc)) {
	result_1 = Completely_unspecified_debugging_code;
	keyword = Nil;
	level = Nil;
	ab_loop_list_ = CDR(parse_result);
	shift = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	keyword = CAR(ab_loop_desetq_);
	level = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = assq_function(keyword,Debugging_shift_alist);
	shift = CDR(temp);
	result_1 = logior(logandc2(result_1,ash(Message_field_mask,shift)),
		ash(level,shift));
	goto next_loop;
      end_loop:
	encoded_parameters = result_1;
	goto end_1;
	encoded_parameters = Qnil;
      end_1:;
    }
    else {
	temp = assq_function(CAR(parse_result),Debugging_shift_alist);
	shift = CDR(temp);
	level = CDR(parse_result);
	encoded_parameters = 
		logior(logandc2(Completely_unspecified_debugging_code,
		ash(Message_field_mask,shift)),ash(level,shift));
    }
    if (encoded_parameters) {
	gensymed_symbol_2 = IFIX(encoded_parameters) & (SI_Long)240L;
	tracing = ash(FIX(gensymed_symbol_2),FIX((SI_Long)-4L));
	breakpoint = ash(FIX(IFIX(encoded_parameters) & (SI_Long)3840L),
		FIX((SI_Long)-8L));
	source_stepping = ash(FIX(IFIX(encoded_parameters) & 
		(SI_Long)61440L),FIX((SI_Long)-12L));
	overrides = ISVREF(Debugging_parameters,(SI_Long)22L);
	if ( !TRUEP(Disable_tracing_and_breakpoints_warning) &&  
		!TRUEP(overrides) && IFIX(breakpoint) > (SI_Long)0L && 
		IFIX(tracing) > (SI_Long)0L && IFIX(source_stepping) > 
		(SI_Long)0L)
	    notify_engineer(1,string_constant_18);
    }
    return VALUES_1(encoded_parameters);
}

static Object list_constant_1;     /* # */

static Object list_constant_2;     /* # */

static Object Qab_warning;         /* warning */

static Object Qtracing;            /* tracing */

static Object Qbreakpoint;         /* breakpoint */

static Object Qsource_stepping;    /* source-stepping */

/* TRACING-AND-BREAKPOINTS-EVALUATION-SETTER */
Object tracing_and_breakpoints_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, temp_2, raw_value;
    Object breakpoints;
    Declare_special(5);
    Object result;

    x_note_fn_call(94,56);
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
		      goto end_tracing_and_breakpoints_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qdefault))
	result = VALUES_1(Qdefault);
    else {
	gensymed_symbol = evaluation_value;
	temp_2 = estructure_slot(gensymed_symbol,Qwarning_message_level,
		Nil) ? phrase_cons(phrase_cons(Qab_warning,
		estructure_slot(gensymed_symbol,Qwarning_message_level,
		Nil)),Nil) : Qnil;
	temp = estructure_slot(gensymed_symbol,Qtracing_message_level,Nil) 
		? phrase_cons(phrase_cons(Qtracing,
		estructure_slot(gensymed_symbol,Qtracing_message_level,
		Nil)),Nil) : Qnil;
	temp_1 = estructure_slot(gensymed_symbol,Qbreakpoint_level,Nil) ? 
		phrase_cons(phrase_cons(Qbreakpoint,
		estructure_slot(gensymed_symbol,Qbreakpoint_level,Nil)),
		Nil) : Qnil;
	raw_value = phrase_cons(Qsc,nconc2(temp_2,nconc2(temp,
		nconc2(temp_1,estructure_slot(gensymed_symbol,
		Qsource_stepping_level,Nil) ? 
		phrase_cons(phrase_cons(Qsource_stepping,
		estructure_slot(gensymed_symbol,Qsource_stepping_level,
		Nil)),Nil) : Qnil))));
	breakpoints = CDR(raw_value);
	if ( !TRUEP(CDR(breakpoints)))
	    result = VALUES_1(FIRST(breakpoints));
	else
	    result = VALUES_1(raw_value);
    }
  end_tracing_and_breakpoints_evaluation_setter:
    return result;
}

/* TRACING-AND-BREAKPOINTS-EVALUATION-GETTER */
Object tracing_and_breakpoints_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp, warning_level, tracing_level, breakpoint_level_1;
    Object source_stepping_level_1, gensymed_symbol_1, returned_struct;
    SI_Long gensymed_symbol;

    x_note_fn_call(94,57);
    if ( !TRUEP(slot_value))
	temp = Qdefault;
    else {
	warning_level = ash(FIX(IFIX(slot_value) & (SI_Long)15L),
		FIX((SI_Long)0L));
	gensymed_symbol = IFIX(slot_value) & (SI_Long)240L;
	tracing_level = ash(FIX(gensymed_symbol),FIX((SI_Long)-4L));
	breakpoint_level_1 = ash(FIX(IFIX(slot_value) & (SI_Long)3840L),
		FIX((SI_Long)-8L));
	source_stepping_level_1 = ash(FIX(IFIX(slot_value) & 
		(SI_Long)61440L),FIX((SI_Long)-12L));
	gensymed_symbol_1 = allocate_evaluation_structure(Nil);
	if ( !FIXNUM_EQ(warning_level,Message_field_mask))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qwarning_message_level,warning_level);
	if ( !FIXNUM_EQ(tracing_level,Message_field_mask))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qtracing_message_level,tracing_level);
	if ( !FIXNUM_EQ(breakpoint_level_1,Message_field_mask))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qbreakpoint_level,breakpoint_level_1);
	if ( !FIXNUM_EQ(source_stepping_level_1,Message_field_mask))
	    set_evaluation_structure_slot(gensymed_symbol_1,
		    Qsource_stepping_level,source_stepping_level_1);
	returned_struct = gensymed_symbol_1;
	temp = returned_struct;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qtracing_and_breakpoints;  /* tracing-and-breakpoints */

static Object Qtrend_chart;        /* trend-chart */

/* PUT-TRACING-AND-BREAKPOINTS */
Object put_tracing_and_breakpoints(block,new_breakpoints,gensymed_symbol)
    Object block, new_breakpoints, gensymed_symbol;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(94,58);
    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Procedure_class_description,
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
    if (temp)
	set_tracing_and_breakpoints_of_procedure_invocations(block,
		new_breakpoints);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(block,Qtracing_and_breakpoints);
    set_lookup_slot_value_1(block,Qtracing_and_breakpoints,new_breakpoints);
    if (kind_of_cell_based_display_p(block)) {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(Qtrend_chart,
		Class_description_gkbprop);
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(ISVREF(block,(SI_Long)1L),
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
	    set_tracing_and_breakpoints_for_trend_chart(block,new_breakpoints);
	else
	    update_cell_based_display_computation_style(1,block);
    }
    return VALUES_1(new_breakpoints);
}

static Object string_constant_19;  /* "default" */

static Object string_constant_20;  /* "warning message level " */

static Object string_constant_21;  /* "; " */

static Object string_constant_22;  /* "tracing message level " */

static Object string_constant_23;  /* "breakpoint level " */

static Object string_constant_24;  /* "source stepping level " */

/* WRITE-TRACING-AND-BREAKPOINTS-FROM-SLOT */
Object write_tracing_and_breakpoints_from_slot(value,frame)
    Object value, frame;
{
    Object warning_level, tracing_level, breakpoint_level_1;
    Object source_stepping_level_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(94,59);
    if ( !TRUEP(value))
	return twrite(string_constant_19);
    else {
	warning_level = ash(FIX(IFIX(value) & (SI_Long)15L),FIX((SI_Long)0L));
	gensymed_symbol = IFIX(value) & (SI_Long)240L;
	tracing_level = ash(FIX(gensymed_symbol),FIX((SI_Long)-4L));
	breakpoint_level_1 = ash(FIX(IFIX(value) & (SI_Long)3840L),
		FIX((SI_Long)-8L));
	source_stepping_level_1 = ash(FIX(IFIX(value) & (SI_Long)61440L),
		FIX((SI_Long)-12L));
	if ( !FIXNUM_EQ(warning_level,Message_field_mask)) {
	    twrite(string_constant_20);
	    write_warning_message_level_from_slot(warning_level,frame);
	    if ( !(FIXNUM_EQ(tracing_level,Message_field_mask) && 
		    FIXNUM_EQ(breakpoint_level_1,Message_field_mask) && 
		    FIXNUM_EQ(source_stepping_level_1,Message_field_mask)))
		twrite(string_constant_21);
	}
	if ( !FIXNUM_EQ(tracing_level,Message_field_mask)) {
	    twrite(string_constant_22);
	    write_tracing_message_level_from_slot(tracing_level,frame);
	    if ( !(FIXNUM_EQ(breakpoint_level_1,Message_field_mask) && 
		    FIXNUM_EQ(source_stepping_level_1,Message_field_mask)))
		twrite(string_constant_21);
	}
	if ( !FIXNUM_EQ(breakpoint_level_1,Message_field_mask)) {
	    twrite(string_constant_23);
	    write_breakpoint_level_from_slot(breakpoint_level_1,frame);
	    if ( !FIXNUM_EQ(source_stepping_level_1,Message_field_mask))
		twrite(string_constant_21);
	}
	if ( !FIXNUM_EQ(source_stepping_level_1,Message_field_mask)) {
	    twrite(string_constant_24);
	    return write_source_stepping_level_from_slot(source_stepping_level_1,
		    frame);
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object array_constant;      /* # */

static Object string_constant_25;  /* "~a" */

/* WRITE-TRACE-FILE-PATHNAME-FROM-SLOT */
Object write_trace_file_pathname_from_slot(format_1,gensymed_symbol)
    Object format_1, gensymed_symbol;
{
    x_note_fn_call(94,60);
    if ( !TRUEP(format_1))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (text_string_p(format_1))
	return tprin(format_1,T);
    else
	return tformat(2,string_constant_25,format_1);
}

static Object Qtracing_file;       /* tracing-file */

/* PUT-TRACING-FILE */
Object put_tracing_file(debugging_parameters_instance,new_value,
	    initialization_qm)
    Object debugging_parameters_instance, new_value, initialization_qm;
{
    x_note_fn_call(94,61);
    if (initialization_qm ||  
	    !TRUEP(system_table_installed_p(debugging_parameters_instance)) 
	    ||  !TRUEP(explanation_related_features_enabled_func_qm())) {
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(debugging_parameters_instance,
		    Qtracing_file);
	set_lookup_slot_value_1(debugging_parameters_instance,
		Qtracing_file,new_value);
    }
    else {
	close_tracing_file();
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(debugging_parameters_instance,
		    Qtracing_file);
	set_lookup_slot_value_1(debugging_parameters_instance,
		Qtracing_file,new_value);
	open_tracing_file(Nil);
    }
    return VALUES_1(new_value);
}

/* PUT-MESSAGE-AND-BREAKPOINT-OVERRIDES */
Object put_message_and_breakpoint_overrides(debugging_parameters_instance,
	    new_value,initialization_qm)
    Object debugging_parameters_instance, new_value, initialization_qm;
{
    x_note_fn_call(94,62);
    if (initialization_qm ||  
	    !TRUEP(system_table_installed_p(debugging_parameters_instance)) 
	    ||  !TRUEP(explanation_related_features_enabled_func_qm()))
	ISVREF(debugging_parameters_instance,(SI_Long)22L) = new_value;
    else {
	close_tracing_file();
	ISVREF(debugging_parameters_instance,(SI_Long)22L) = new_value;
	open_tracing_file(Nil);
    }
    return VALUES_1(new_value);
}

DEFINE_VARIABLE_WITH_SYMBOL(Saved_warning_level, Qsaved_warning_level);

DEFINE_VARIABLE_WITH_SYMBOL(Saved_tracing_level, Qsaved_tracing_level);

DEFINE_VARIABLE_WITH_SYMBOL(Saved_breakpoint_level, Qsaved_breakpoint_level);

DEFINE_VARIABLE_WITH_SYMBOL(Saved_source_stepping_level, Qsaved_source_stepping_level);

DEFINE_VARIABLE_WITH_SYMBOL(Trace_messages_within_extent_of_rule, Qtrace_messages_within_extent_of_rule);

/* RESET-DEBUGGING-PARAMETERS */
Object reset_debugging_parameters()
{
    x_note_fn_call(94,63);
    Warning_message_level = 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qwarning_message_level,FIX((SI_Long)2L));
    Tracing_message_level = 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtracing_message_level,FIX((SI_Long)0L));
    Breakpoint_level = 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qbreakpoint_level,FIX((SI_Long)0L));
    Source_stepping_level = 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qsource_stepping_level,FIX((SI_Long)0L));
    Saved_warning_level = Nil;
    Saved_tracing_level = Nil;
    Saved_breakpoint_level = Nil;
    Saved_source_stepping_level = Nil;
    if (explanation_related_features_enabled_func_qm())
	return reset_message_accumulation_variables();
    else
	return VALUES_1(Nil);
}

/* RESET-MESSAGE-ACCUMULATION-VARIABLES */
Object reset_message_accumulation_variables()
{
    Object text_string, ab_loop_list_;

    x_note_fn_call(94,64);
    text_string = Nil;
    ab_loop_list_ = Trace_messages_within_extent_of_rule;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_text_string(text_string);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(Trace_messages_within_extent_of_rule);
    Trace_messages_within_extent_of_rule = Nil;
    return VALUES_1(Trace_messages_within_extent_of_rule);
}

/* SET-DEBUGGING-PARAMETERS */
Object set_debugging_parameters(encoded_parameters)
    Object encoded_parameters;
{
    SI_Long warning_level, gensymed_symbol, gensymed_symbol_1, tracing_level;
    SI_Long breakpoint_level_1, source_stepping_level_1;

    x_note_fn_call(94,65);
    warning_level = IFIX(encoded_parameters) & (SI_Long)15L;
    gensymed_symbol = IFIX(encoded_parameters) & (SI_Long)240L;
    gensymed_symbol_1 = (SI_Long)4L;
    tracing_level = gensymed_symbol >>  -  - gensymed_symbol_1;
    breakpoint_level_1 = (IFIX(encoded_parameters) & (SI_Long)3840L) >>  - 
	     - (SI_Long)8L;
    source_stepping_level_1 = (IFIX(encoded_parameters) & (SI_Long)61440L) 
	    >>  -  - (SI_Long)12L;
    Warning_message_level = warning_level == IFIX(Message_field_mask) ? 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qwarning_message_level,FIX((SI_Long)2L)) : FIX(warning_level);
    Tracing_message_level = tracing_level == IFIX(Message_field_mask) ? 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtracing_message_level,FIX((SI_Long)0L)) : FIX(tracing_level);
    Breakpoint_level = breakpoint_level_1 == IFIX(Message_field_mask) ? 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qbreakpoint_level,FIX((SI_Long)0L)) : FIX(breakpoint_level_1);
    Source_stepping_level = source_stepping_level_1 == 
	    IFIX(Message_field_mask) ? 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qsource_stepping_level,FIX((SI_Long)0L)) : 
	    FIX(source_stepping_level_1);
    return VALUES_1(Source_stepping_level);
}

DEFINE_VARIABLE_WITH_SYMBOL(Suppress_warning_message_header_qm, Qsuppress_warning_message_header_qm);

/* RESET-SUPPRESS-HEADER-VARIABLE */
Object reset_suppress_header_variable()
{
    x_note_fn_call(94,66);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

/* WRITE-WARNING-MESSAGE-STRING */
Object write_warning_message_string(level,message_1)
    Object level, message_1;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(7);

    x_note_fn_call(94,67);
    if (FIXNUM_LE(level,Warning_message_level) &&  !TRUEP(Debugging_reset)) {
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
		      twrite(message_1);
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
    return VALUES_1(Nil);
}

/* GIVE-WARNING-1 */
Object give_warning_1 varargs_1(int, n)
{
    Object target_warning_level, format_string;
    Object arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9;
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object calling_tformat_for_give_warning_qm, temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_stack_pointer;
    Declare_special(8);
    Object result;

    x_note_fn_call(94,68);
    INIT_ARGS_nonrelocating();
    target_warning_level = REQUIRED_ARG_nonrelocating();
    format_string = REQUIRED_ARG_nonrelocating();
    SAVE_STACK();
    arg1 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg2 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg3 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg4 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg5 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg6 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg7 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg8 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    arg9 = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : 
	    No_arg;
    END_ARGS_nonrelocating();
    if ( !TRUEP(Debugging_reset)) {
	break_out_of_debug_messages();
	snapshots_of_related_blocks = Nil;
	note_blocks_in_tformat = SYMBOL_FUNCTION(Qrecord_block_for_tformat);
	PUSH_SPECIAL_WITH_SYMBOL(Note_blocks_in_tformat,Qnote_blocks_in_tformat,note_blocks_in_tformat,
		7);
	  PUSH_SPECIAL_WITH_SYMBOL(Snapshots_of_related_blocks,Qsnapshots_of_related_blocks,snapshots_of_related_blocks,
		  6);
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string_list,Qcurrent_wide_string_list,current_wide_string_list,
		    5);
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
		      4);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			3);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			  2);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			    1);
		      if ( !TRUEP(Suppress_warning_message_header_qm))
			  write_warning_message_header(target_warning_level);
		      calling_tformat_for_give_warning_qm = T;
		      PUSH_SPECIAL_WITH_SYMBOL(Calling_tformat_for_give_warning_qm,Qcalling_tformat_for_give_warning_qm,calling_tformat_for_give_warning_qm,
			      0);
			if (EQ(arg1,No_arg))
			    tformat(1,format_string);
			else if (EQ(arg2,No_arg))
			    tformat(2,format_string,arg1);
			else if (EQ(arg3,No_arg))
			    tformat(3,format_string,arg1,arg2);
			else if (EQ(arg4,No_arg))
			    tformat(4,format_string,arg1,arg2,arg3);
			else if (EQ(arg5,No_arg))
			    tformat(5,format_string,arg1,arg2,arg3,arg4);
			else if (EQ(arg6,No_arg))
			    tformat(6,format_string,arg1,arg2,arg3,arg4,arg5);
			else if (EQ(arg7,No_arg))
			    tformat(7,format_string,arg1,arg2,arg3,arg4,
				    arg5,arg6);
			else if (EQ(arg8,No_arg))
			    tformat(8,format_string,arg1,arg2,arg3,arg4,
				    arg5,arg6,arg7);
			else if (EQ(arg9,No_arg))
			    tformat(9,format_string,arg1,arg2,arg3,arg4,
				    arg5,arg6,arg7,arg8);
			else
			    tformat(10,format_string,arg1,arg2,arg3,arg4,
				    arg5,arg6,arg7,arg8,arg9);
		      POP_SPECIAL();
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
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

static Object string_constant_26;  /* "Error" */

static Object string_constant_27;  /* "Error or incomplete KB" */

static Object string_constant_28;  /* "General warning" */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* WRITE-WARNING-MESSAGE-HEADER */
Object write_warning_message_header(level)
    Object level;
{
    Object temp;

    x_note_fn_call(94,69);
    if ( !(FIXNUMP(level) && FIXNUM_LE(FIX((SI_Long)-128L),level) && 
	    FIXNUM_LE(level,FIX((SI_Long)127L))))
	temp = Nil;
    else
	switch (INTEGER_TO_CHAR(level)) {
	  case 1:
	    temp = string_constant_26;
	    break;
	  case 2:
	    temp = string_constant_27;
	    break;
	  case 3:
	    temp = string_constant_28;
	    break;
	  default:
	    temp = Nil;
	    break;
	}
    twrite_general_string(temp);
    if (BOUNDP(Qcurrent_computation_frame) && Current_computation_frame) {
	twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)4L));
	denote_component_of_block(1,T);
    }
    return twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)2L));
}

/* GIVE-ICP-ERROR-WARNING-MESSAGE */
Object give_icp_error_warning_message(shutdownp,error_type,
	    error_string_or_out_of_synch_case,arg1,arg2,arg3)
    Object shutdownp, error_type, error_string_or_out_of_synch_case, arg1;
    Object arg2, arg3;
{
    Object snapshots_of_related_blocks, note_blocks_in_tformat;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(7);
    Object result;

    x_note_fn_call(94,70);
    SAVE_STACK();
    if (FIXNUM_LE(shutdownp ? FIX((SI_Long)1L) : FIX((SI_Long)2L),
	    Warning_message_level) &&  !TRUEP(Debugging_reset)) {
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
		      twrite_icp_error(5,error_type,
			      error_string_or_out_of_synch_case,arg1,arg2,
			      arg3);
		      if (of_class_p_function(arg1,Qblock))
			  record_block_for_tformat(arg1);
		      if (of_class_p_function(arg2,Qblock))
			  record_block_for_tformat(arg2);
		      if (of_class_p_function(arg3,Qblock))
			  record_block_for_tformat(arg3);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    SAVE_VALUES(notify_user_1(temp));
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

/* MODIFY-TRACING-AND-BREAKPOINTS-CONTEXT-ON-ENTRY */
Object modify_tracing_and_breakpoints_context_on_entry(frame,
	    tracing_and_breakpoints)
    Object frame, tracing_and_breakpoints;
{
    x_note_fn_call(94,71);
    Saved_warning_level = Warning_message_level;
    Saved_tracing_level = Tracing_message_level;
    Saved_breakpoint_level = Breakpoint_level;
    Saved_source_stepping_level = Source_stepping_level;
    if (in_order_p(frame) ||  !TRUEP(ISVREF(ISVREF(frame,(SI_Long)1L),
	    (SI_Long)16L))) {
	Warning_message_level = FIX((SI_Long)0L);
	Tracing_message_level = FIX((SI_Long)0L);
	Breakpoint_level = FIX((SI_Long)0L);
	Source_stepping_level = FIX((SI_Long)0L);
	return VALUES_1(Source_stepping_level);
    }
    else if (tracing_and_breakpoints)
	return set_debugging_parameters(tracing_and_breakpoints);
    else {
	Warning_message_level = 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qwarning_message_level,FIX((SI_Long)2L));
	Tracing_message_level = 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qtracing_message_level,FIX((SI_Long)0L));
	Breakpoint_level = 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qbreakpoint_level,FIX((SI_Long)0L));
	Source_stepping_level = 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qsource_stepping_level,FIX((SI_Long)0L));
	return VALUES_1(Source_stepping_level);
    }
}

static Object string_constant_29;  /* "~A  Break on entry." */

/* ISSUE-TRACING-AND-BREAKPOINTS-ENTRY-MESSAGE */
Object issue_tracing_and_breakpoints_entry_message(frame,entry_message)
    Object frame, entry_message;
{
    Object overrides, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(94,72);
    overrides = ISVREF(Debugging_parameters,(SI_Long)22L);
    if ( !TRUEP(entry_message))
	return VALUES_1(Nil);
    else if (in_order_p(frame))
	return reclaim_text_string(entry_message);
    else if (IFIX(Breakpoint_level) > (SI_Long)0L && overrides) {
	notify_engineer(2,string_constant_29,entry_message);
	return pause_during_debug(entry_message);
    }
    else if (IFIX(Tracing_message_level) > (SI_Long)0L && overrides) {
	break_out_of_debug_messages();
	if (explanation_related_features_enabled_func_qm() && 
		(IFIX(Current_computation_flags) & (SI_Long)1024L) != 
		(SI_Long)0L) {
	    Trace_messages_within_extent_of_rule = 
		    gensym_cons_1(entry_message,
		    Trace_messages_within_extent_of_rule);
	    return VALUES_1(Trace_messages_within_extent_of_rule);
	}
	else {
	    if (explanation_related_features_enabled_func_qm()) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_1 = (SI_Long)1L;
		    gensymed_symbol_2 = superior_class_bit_number & 
			    (SI_Long)7L;
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
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)1024L);
		Trace_messages_within_extent_of_rule = 
			gensym_cons_1(entry_message,
			Trace_messages_within_extent_of_rule);
		return VALUES_1(Trace_messages_within_extent_of_rule);
	    }
	    else {
		notify_engineer(2,string_constant_25,entry_message);
		return reclaim_text_string(entry_message);
	    }
	}
    }
    else
	return reclaim_text_string(entry_message);
}

static Object string_constant_30;  /* "~NW Break on exit." */

static Object string_constant_31;  /* "~A  Break on exit." */

static Object string_constant_32;  /* "~NW" */

static Object string_constant_33;  /* "~%" */

static Object string_constant_34;  /* "   " */

/* ISSUE-TRACING-AND-BREAKPOINT-EXIT-MESSAGE */
Object issue_tracing_and_breakpoint_exit_message(frame,exit_message_qm)
    Object frame, exit_message_qm;
{
    Object overrides, sub_class_bit_vector, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object listed_text_string, combined_message;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(94,73);
    overrides = ISVREF(Debugging_parameters,(SI_Long)22L);
    if (in_order_p(frame)) {
	if (exit_message_qm)
	    reclaim_error_text(exit_message_qm);
    }
    else if (exit_message_qm && Debugging_reset)
	reclaim_error_text(exit_message_qm);
    else if (IFIX(Breakpoint_level) > (SI_Long)0L && overrides && 
	    exit_message_qm) {
	notify_engineer(2,string_constant_30,exit_message_qm);
	pause_during_debug(tformat_text_string(2,string_constant_31,
		exit_message_qm));
    }
    else if (IFIX(Tracing_message_level) > (SI_Long)0L && overrides) {
	break_out_of_debug_messages();
	if (exit_message_qm) {
	    if (explanation_related_features_enabled_func_qm() && 
		    (IFIX(Current_computation_flags) & (SI_Long)1024L) != 
		    (SI_Long)0L)
		Trace_messages_within_extent_of_rule = 
			gensym_cons_1(exit_message_qm,
			Trace_messages_within_extent_of_rule);
	    else {
		notify_engineer(2,string_constant_32,exit_message_qm);
		reclaim_error_text(exit_message_qm);
	    }
	}
	if (explanation_related_features_enabled_func_qm()) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
		temp = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp = TRUEP(Nil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    Trace_messages_within_extent_of_rule = 
		    nreverse(Trace_messages_within_extent_of_rule);
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
		      tformat(1,string_constant_33);
		      listed_text_string = 
			      Trace_messages_within_extent_of_rule;
		    next_loop:
		      if ( !TRUEP(listed_text_string))
			  goto end_loop;
		      if (CDR(listed_text_string) &&  
			      !EQ(listed_text_string,
			      Trace_messages_within_extent_of_rule))
			  twrite(string_constant_34);
		      tformat(2,string_constant_32,CAR(listed_text_string));
		      reclaim_error_text(CAR(listed_text_string));
		      if (CDR(listed_text_string))
			  tformat(1,string_constant_33);
		      listed_text_string = M_CDR(listed_text_string);
		      goto next_loop;
		    end_loop:;
		      combined_message = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    notify_engineer(1,combined_message);
	    reclaim_error_text(combined_message);
	    reclaim_gensym_list_1(Trace_messages_within_extent_of_rule);
	    Trace_messages_within_extent_of_rule = Nil;
	}
    }
    else if (exit_message_qm)
	reclaim_error_text(exit_message_qm);
    return VALUES_1(Nil);
}

/* TFORMAT-MAJOR-TRACE-MESSAGE-1 */
Object tformat_major_trace_message_1(control_string,arg1,arg2,arg3,arg4,
	    arg5,arg6,arg7,arg8,arg9)
    Object control_string, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;
    Object arg9;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object output_message;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(94,74);
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
	      tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,arg6,arg7,
		      arg8,arg9);
	      output_message = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return write_major_trace_message_function(output_message);
}

static Object string_constant_35;  /* "~A Break on exit." */

/* WRITE-MAJOR-TRACE-MESSAGE-FUNCTION */
Object write_major_trace_message_function(output_message)
    Object output_message;
{
    Object overrides;

    x_note_fn_call(94,75);
    overrides = ISVREF(Debugging_parameters,(SI_Long)22L);
    if (IFIX(Breakpoint_level) > (SI_Long)1L && overrides) {
	notify_engineer(2,string_constant_35,output_message);
	return pause_during_debug(tformat_text_string(2,string_constant_35,
		output_message));
    }
    else if (overrides) {
	break_out_of_debug_messages();
	if (explanation_related_features_enabled_func_qm()) {
	    if ((IFIX(Current_computation_flags) & (SI_Long)1024L) != 
		    (SI_Long)0L) {
		Trace_messages_within_extent_of_rule = 
			gensym_cons_1(output_message,
			Trace_messages_within_extent_of_rule);
		return VALUES_1(Trace_messages_within_extent_of_rule);
	    }
	    else {
		notify_engineer(2,string_constant_25,output_message);
		return reclaim_text_string(output_message);
	    }
	}
	else {
	    notify_engineer(2,string_constant_25,output_message);
	    return reclaim_text_string(output_message);
	}
    }
    else
	return reclaim_text_string(output_message);
}

/* TFORMAT-DETAIL-TRACE-MESSAGE-1 */
Object tformat_detail_trace_message_1(control_string,arg1,arg2,arg3,arg4,
	    arg5,arg6,arg7,arg8,arg9)
    Object control_string, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8;
    Object arg9;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object output_message;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(94,76);
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
	      tformat(10,control_string,arg1,arg2,arg3,arg4,arg5,arg6,arg7,
		      arg8,arg9);
	      output_message = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return write_detail_trace_message_function(output_message);
}

/* WRITE-DETAIL-TRACE-MESSAGE-FUNCTION */
Object write_detail_trace_message_function(output_message)
    Object output_message;
{
    Object overrides;

    x_note_fn_call(94,77);
    overrides = ISVREF(Debugging_parameters,(SI_Long)22L);
    if (IFIX(Breakpoint_level) > (SI_Long)2L && overrides) {
	notify_engineer(2,string_constant_35,output_message);
	return pause_during_debug(tformat_text_string(2,string_constant_35,
		output_message));
    }
    else if (overrides) {
	break_out_of_debug_messages();
	if (explanation_related_features_enabled_func_qm()) {
	    if ((IFIX(Current_computation_flags) & (SI_Long)1024L) != 
		    (SI_Long)0L) {
		Trace_messages_within_extent_of_rule = 
			gensym_cons_1(output_message,
			Trace_messages_within_extent_of_rule);
		return VALUES_1(Trace_messages_within_extent_of_rule);
	    }
	    else {
		notify_engineer(2,string_constant_25,output_message);
		return reclaim_text_string(output_message);
	    }
	}
	else {
	    notify_engineer(2,string_constant_25,output_message);
	    return reclaim_text_string(output_message);
	}
    }
    else
	return reclaim_text_string(output_message);
}

static Object Qmessage_and_breakpoint_overrides;  /* message-and-breakpoint-overrides */

/* REMOVE-TRACING-AND-BREAKPOINTS */
Object remove_tracing_and_breakpoints()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, entity;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(94,78);
    change_slot_value(3,Debugging_parameters,Qtracing_message_level,
	    FIX((SI_Long)0L));
    change_slot_value(3,Debugging_parameters,Qbreakpoint_level,
	    FIX((SI_Long)0L));
    change_slot_value(3,Debugging_parameters,Qsource_stepping_level,
	    FIX((SI_Long)0L));
    change_slot_value(3,Debugging_parameters,
	    Qmessage_and_breakpoint_overrides,Nil);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    entity = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
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
      entity = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      change_slot_value(3,entity,Qtracing_and_breakpoints,Nil);
      goto next_loop;
    end_loop_1:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* FIX-FRAME-WITH-SUBSTITUTE-CLASS-FOR-DEBUGGING-PARAMETERS */
Object fix_frame_with_substitute_class_for_debugging_parameters(debugging_parameters)
    Object debugging_parameters;
{
    Declare_special(1);
    Object result;

    x_note_fn_call(94,79);
    PUSH_SPECIAL_WITH_SYMBOL(Debugging_parameters,Qdebugging_parameters,debugging_parameters,
	    0);
      result = delete_frame(Debugging_parameters);
    POP_SPECIAL();
    return result;
}

static Object Qtracing_file_string;  /* tracing-file-string */

static Object Qtracing_file_stream;  /* tracing-file-stream */

static Object Qtrace_outputting_to_file_qm;  /* trace-outputting-to-file? */

static Object string_constant_36;  /* "Couldn't open tracing file ~s:  ~a." */

/* OPEN-TRACING-FILE */
Object open_tracing_file(activating_qm)
    Object activating_qm;
{
    Object pathname_qm, temp, error_text;

    x_note_fn_call(94,80);
    if ((activating_qm || System_is_running || System_has_paused) && 
	    ISVREF(Debugging_parameters,(SI_Long)22L)) {
	pathname_qm = get_pathname_for_file_from_slot(Debugging_parameters,
		Qtracing_file);
	if (pathname_qm) {
	    if (text_string_p(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qtracing_file_string,Nil)))
		reclaim_text_string(get_lookup_slot_value_given_default(Debugging_parameters,
			Qtracing_file_string,Nil));
	    set_non_savable_lookup_slot_value(Debugging_parameters,
		    Qtracing_file_string,pathname_qm);
	    temp = Debugging_parameters;
	    set_non_savable_lookup_slot_value(temp,Qtracing_file_stream,
		    g2_stream_open_for_output(pathname_qm));
	    if (g2_stream_p(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qtracing_file_stream,Nil))) {
		set_non_savable_lookup_slot_value(Debugging_parameters,
			Qtrace_outputting_to_file_qm,T);
		return VALUES_1(T);
	    }
	    else {
		error_text = most_recent_file_operation_status_as_text();
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(4,FIX((SI_Long)1L),string_constant_36,
			    pathname_qm,error_text);
		Suppress_warning_message_header_qm = Nil;
		reclaim_text_string(error_text);
		return VALUES_1(Nil);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CLOSE-TRACING-FILE */
Object close_tracing_file()
{
    Object file_stream_qm;

    x_note_fn_call(94,81);
    file_stream_qm = 
	    get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtracing_file_stream,Nil);
    if (text_string_p(get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtracing_file_string,Nil)))
	reclaim_text_string(get_lookup_slot_value_given_default(Debugging_parameters,
		Qtracing_file_string,Nil));
    set_non_savable_lookup_slot_value(Debugging_parameters,
	    Qtracing_file_string,Nil);
    if (file_stream_qm) {
	g2_stream_close(file_stream_qm);
	set_non_savable_lookup_slot_value(Debugging_parameters,
		Qtracing_file_stream,Nil);
    }
    return set_non_savable_lookup_slot_value(Debugging_parameters,
	    Qtrace_outputting_to_file_qm,Nil);
}

/* GET-PATHNAME-FOR-FILE-FROM-SLOT */
Object get_pathname_for_file_from_slot(frame,slot_name_for_pathname)
    Object frame, slot_name_for_pathname;
{
    Object pathname_1;

    x_note_fn_call(94,82);
    pathname_1 = get_slot_value_function(frame,slot_name_for_pathname,Nil);
    if ( !TRUEP(pathname_1))
	return VALUES_1(Nil);
    else if (text_string_p(pathname_1))
	return copy_text_string(pathname_1);
    else
	return VALUES_1(Nil);
}

/* WARNING-MESSAGE-WITH-NO-ARGS */
Object warning_message_with_no_args(warning_level,format_string)
    Object warning_level, format_string;
{
    x_note_fn_call(94,83);
    Suppress_warning_message_header_qm = T;
    if (FIXNUM_LE(warning_level,Warning_message_level))
	give_warning_1(2,warning_level,format_string);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

/* WARNING-MESSAGE-WITH-ONE-ARG */
Object warning_message_with_one_arg(warning_level,format_string,arg1)
    Object warning_level, format_string, arg1;
{
    x_note_fn_call(94,84);
    Suppress_warning_message_header_qm = T;
    if (FIXNUM_LE(warning_level,Warning_message_level))
	give_warning_1(3,warning_level,format_string,arg1);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

/* WARNING-MESSAGE-WITH-TWO-ARGS */
Object warning_message_with_two_args(warning_level,format_string,arg1,arg2)
    Object warning_level, format_string, arg1, arg2;
{
    x_note_fn_call(94,85);
    Suppress_warning_message_header_qm = T;
    if (FIXNUM_LE(warning_level,Warning_message_level))
	give_warning_1(4,warning_level,format_string,arg1,arg2);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

/* WARNING-MESSAGE-WITH-THREE-ARGS */
Object warning_message_with_three_args(warning_level,format_string,arg1,
	    arg2,arg3)
    Object warning_level, format_string, arg1, arg2, arg3;
{
    x_note_fn_call(94,86);
    Suppress_warning_message_header_qm = T;
    if (FIXNUM_LE(warning_level,Warning_message_level))
	give_warning_1(5,warning_level,format_string,arg1,arg2,arg3);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

static Object string_constant_37;  /* "~NF does not have a color pattern to change -- it is not polychrome." */

/* WARN-OF-NON-POLYCHROME-ICON */
Object warn_of_non_polychrome_icon(entity)
    Object entity;
{
    x_note_fn_call(94,87);
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)2L),string_constant_37,entity);
    else
	return VALUES_1(Nil);
}

static Object string_constant_38;  /* "~NF does not have a single icon color to change -- it is polychrome." */

/* WARN-OF-POLYCHROME-ICON */
Object warn_of_polychrome_icon(entity)
    Object entity;
{
    x_note_fn_call(94,88);
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(3,FIX((SI_Long)2L),string_constant_38,entity);
    else
	return VALUES_1(Nil);
}

static Object string_constant_39;  /* "~a is not a valid color attribute for ~NF." */

/* WARN-OF-INVALID-COLOR-ATTRIBUTE */
Object warn_of_invalid_color_attribute(item,invalid_color_attribute)
    Object item, invalid_color_attribute;
{
    x_note_fn_call(94,89);
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(4,FIX((SI_Long)2L),string_constant_39,
		invalid_color_attribute,item);
    else
	return VALUES_1(Nil);
}

static Object string_constant_40;  /* "~a is not a valid color region for ~NF." */

/* WARN-OF-INVALID-COLOR-REGION */
Object warn_of_invalid_color_region(item,invalid_color_region)
    Object item, invalid_color_region;
{
    x_note_fn_call(94,90);
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(4,FIX((SI_Long)2L),string_constant_40,
		invalid_color_region,item);
    else
	return VALUES_1(Nil);
}

static Object string_constant_41;  /* "Attempt to change the ~a region of ~NF. ~
				    *     The class definition for ~a does not have a region named ~a."
				    */

/* WARN-OF-MISSING-COLOR-REGION */
Object warn_of_missing_color_region(entity,region)
    Object entity, region;
{
    x_note_fn_call(94,91);
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(6,FIX((SI_Long)2L),string_constant_41,region,
		entity,ISVREF(ISVREF(entity,(SI_Long)1L),(SI_Long)1L),region);
    else
	return VALUES_1(Nil);
}

static Object string_constant_42;  /* "Attempt to change an unnamed color region in ~NF using its color name ~
				    *      (~a).  Unnamed color regions cannot be changed."
				    */

/* WARN-OF-UNNAMED-COLOR-REGION */
Object warn_of_unnamed_color_region(entity,region)
    Object entity, region;
{
    x_note_fn_call(94,92);
    if ((SI_Long)2L <= IFIX(Warning_message_level))
	return give_warning_1(4,FIX((SI_Long)2L),string_constant_42,entity,
		region);
    else
	return VALUES_1(Nil);
}

static Object Qcm;                 /* \, */

static Object string_constant_43;  /* "~a ~a illegal color~a" */

static Object string_constant_44;  /* "are" */

static Object string_constant_45;  /* "is an" */

static Object string_constant_46;  /* "s" */

static Object string_constant_47;  /* "" */

/* WARN-OF-ILLEGAL-COLORS */
Object warn_of_illegal_colors(illegal_colors)
    Object illegal_colors;
{
    Object remaining_colors, remaining_colors_without_duplicates, ab_loopvar_;
    Object ab_loopvar__1, previous_illegal_colors, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object list_of_colors_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(94,93);
    if (illegal_colors) {
	remaining_colors = illegal_colors;
	remaining_colors_without_duplicates = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(remaining_colors))
	    goto end_loop;
	previous_illegal_colors = illegal_colors;
      next_loop_1:
	if ( !TRUEP(previous_illegal_colors))
	    goto end_loop_1;
	if (EQ(previous_illegal_colors,remaining_colors))
	    goto end_loop_1;
	if (EQ(CAR(previous_illegal_colors),CAR(remaining_colors))) {
	    temp = TRUEP(Nil);
	    goto end_1;
	}
	previous_illegal_colors = M_CDR(previous_illegal_colors);
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(T);
	goto end_1;
	temp = TRUEP(Qnil);
      end_1:;
	if (temp) {
	    ab_loopvar__1 = gensym_cons_1(CAR(remaining_colors),Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		remaining_colors_without_duplicates = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	}
	remaining_colors = M_CDR(remaining_colors);
	goto next_loop;
      end_loop:
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
		  write_symbol_list(3,remaining_colors_without_duplicates,
			  Qcm,Qand);
		  list_of_colors_text_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	if ((SI_Long)2L <= IFIX(Warning_message_level))
	    give_warning_1(5,FIX((SI_Long)2L),string_constant_43,
		    list_of_colors_text_string,
		    CDR(remaining_colors_without_duplicates) ? 
		    string_constant_44 : string_constant_45,
		    CDR(remaining_colors_without_duplicates) ? 
		    string_constant_46 : string_constant_47);
	reclaim_text_string(list_of_colors_text_string);
	reclaim_gensym_list_1(remaining_colors_without_duplicates);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_3;    /* # */

static Object array_constant_4;    /* # */

static Object string_constant_48;  /* "~A " */

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* POST-TELEWINDOWS-CONNECTION-CLOGGED */
Object post_telewindows_connection_clogged(g2_window_qm,clogged_qm)
    Object g2_window_qm, clogged_qm;
{
    Object defer_notifications_qm, snapshots_of_related_blocks;
    Object note_blocks_in_tformat, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_stack_pointer;
    Declare_special(8);
    Object result;

    x_note_fn_call(94,94);
    SAVE_STACK();
    defer_notifications_qm = T;
    PUSH_SPECIAL_WITH_SYMBOL(Defer_notifications_qm,Qdefer_notifications_qm,defer_notifications_qm,
	    7);
      if ((SI_Long)2L <= IFIX(Warning_message_level) &&  
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
		bv16_length = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
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
			    ((UBYTE_16_ISAREF_1(Current_wide_string,
			    length_1 - (SI_Long)1L) & (SI_Long)8191L) << 
			    (SI_Long)16L));
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
			    1);
		      current_twriting_output_type = Qwide_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      0);
			if ( !TRUEP(g2_window_qm))
			    twrite_beginning_of_wide_string(array_constant_3,
				    FIX((SI_Long)25L));
			else {
			    twrite_beginning_of_wide_string(array_constant_4,
				    FIX((SI_Long)31L));
			    tformat(2,string_constant_48,
				    get_or_make_up_name_for_block(g2_window_qm));
			}
			if (clogged_qm)
			    twrite_beginning_of_wide_string(array_constant_5,
				    FIX((SI_Long)11L));
			else
			    twrite_beginning_of_wide_string(array_constant_6,
				    FIX((SI_Long)17L));
			temp = copy_out_current_wide_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      SAVE_VALUES(notify_user_1(temp));
	      if (Snapshots_of_related_blocks) {
		  reclaim_list_of_block_snapshots(Snapshots_of_related_blocks);
		  Snapshots_of_related_blocks = Nil;
	      }
	      result = RESTORE_VALUES();
	    POP_SPECIAL();
	  POP_SPECIAL();
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* C-EMIT-PERFORMANCE-COUNTER */
Object c_emit_performance_counter(format_string,message_number,stream_handle)
    Object format_string, message_number, stream_handle;
{
    Object temp;

    x_note_fn_call(94,95);
    temp = 
	    DOUBLE_TO_DOUBLE_FLOAT(g2ext_emit_performance_counter(UBYTE_16_SARRAY_TO_USHORT_PTR(format_string),
	    IFIX(message_number),IFIX(stream_handle)));
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Current_message_serial_number, Qcurrent_message_serial_number);

/* G2-PERFORMANCE-FREQUENCY */
Object g2_performance_frequency()
{
    Object stream_handle;

    x_note_fn_call(94,96);
    stream_handle = FIX((SI_Long)-1L);
    if (get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtrace_outputting_to_file_qm,Nil) && 
	    g2_stream_p(get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtracing_file_stream,Nil)))
	stream_handle = 
		ISVREF(get_lookup_slot_value_given_default(Debugging_parameters,
		Qtracing_file_stream,Nil),(SI_Long)1L);
    return VALUES_1(FIX(g2ext_performance_frequency(IFIX(stream_handle),
	    IFIX(Current_message_serial_number))));
}

static Object Qfloat_array;        /* float-array */

/* G2-EMIT-PERFORMANCE-COUNTER */
Object g2_emit_performance_counter(format_string)
    Object format_string;
{
    Object stream_handle, c_float, amf_available_array_cons_qm, amf_array;
    Object temp, temp_1, amf_result, new_float;
    double aref_new_value;

    x_note_fn_call(94,97);
    stream_handle = FIX((SI_Long)-1L);
    if (get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtrace_outputting_to_file_qm,Nil) && 
	    g2_stream_p(get_lookup_slot_value_given_default(Debugging_parameters,
	    Qtracing_file_stream,Nil)))
	stream_handle = 
		ISVREF(get_lookup_slot_value_given_default(Debugging_parameters,
		Qtracing_file_stream,Nil),(SI_Long)1L);
    c_float = c_emit_performance_counter(format_string,
	    Current_message_serial_number,stream_handle);
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
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
    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(c_float);
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
    return VALUES_1(new_float);
}

/* G2-REPORT-PERFORMANCE-COUNTER */
Object g2_report_performance_counter()
{
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float;
    double c_float;

    x_note_fn_call(94,98);
    c_float = g2ext_report_performance_counter();
    amf_available_array_cons_qm = 
	    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
    if (amf_available_array_cons_qm) {
	amf_array = M_CAR(amf_available_array_cons_qm);
	temp = Vector_of_simple_float_array_pools;
	temp_1 = M_CDR(amf_available_array_cons_qm);
	SVREF(temp,FIX((SI_Long)1L)) = temp_1;
	inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	if (ISVREF(Available_float_array_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	}
	else {
	    temp = Available_float_array_conses_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
	    temp = Available_float_array_conses_tail_vector;
	    temp_1 = Current_thread_index;
	    SVREF(temp,temp_1) = amf_available_array_cons_qm;
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
    DFLOAT_ISASET_1(new_float,(SI_Long)0L,c_float);
    return VALUES_1(new_float);
}

void debug_INIT()
{
    Object temp, reclaim_structure_for_snapshot_invocation_info_1;
    Object reclaim_structure_for_snapshot_of_block_1, temp_1, temp_2;
    Object tracing_and_breakpoints_evaluation_setter_1;
    Object tracing_and_breakpoints_evaluation_getter_1, gensymed_symbol;
    Object Qg2_report_performance_counter;
    Object Qfunction_keeps_procedure_environment_valid_qm, AB_package;
    Object Qg2_emit_performance_counter, Qg2_performance_frequency;
    Object list_constant_85, Qclasses_which_define;
    Object Qfix_frame_with_substitute_class;
    Object Qfix_frame_with_substitute_class_for_debugging_parameters;
    Object Qsubstitute_class_and_kb_flags;
    Object Qdebugging_message_and_breakpoint_parameters;
    Object Qtracing_and_breakpoint_parameters, Qreset_suppress_header_variable;
    Object Qab_debug, Qslot_putter, Qput_message_and_breakpoint_overrides;
    Object Qput_tracing_file, Qslot_value_writer;
    Object Qwrite_trace_file_pathname_from_slot, Qtrace_file_pathname;
    Object string_constant_78, Qwrite_tracing_and_breakpoints_from_slot;
    Object Qput_tracing_and_breakpoints, Qnamed, list_constant_84;
    Object list_constant_83, Qab_or, list_constant_82, list_constant_81;
    Object Qab_structure, list_constant_80, list_constant_79, list_constant_78;
    Object list_constant_77, list_constant_76, list_constant_12;
    Object list_constant_75, list_constant_74, list_constant_73;
    Object list_constant_72, Qtype_specification_simple_expansion;
    Object list_constant_71, Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_tracing_and_breakpoints_for_slot;
    Object Qcompletely_unspecified_debugging_code, list_constant_70;
    Object Qdebugging_shift_alist, list_constant_69, list_constant_68;
    Object list_constant_67, list_constant_66, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object Qmessage, Qsimplify_associative_operation;
    Object Qwrite_message_overrides_from_slot, Qmessage_overrides;
    Object Qcompile_message_overrides_for_slot, list_constant_65;
    Object list_constant_64, Qbreakpoints, Qab_no, string_constant_73;
    Object string_constant_72, Qwrite_source_stepping_level_from_slot;
    Object string_constant_71, Qwrite_breakpoint_level_from_slot;
    Object list_constant_63, list_constant_62, list_constant_61;
    Object list_constant_60, list_constant_59, list_constant_58;
    Object list_constant_57, list_constant_51, list_constant_6;
    Object list_constant_22, list_constant_10, list_constant_44;
    Object list_constant_43, list_constant_39, list_constant_56;
    Object list_constant_55, list_constant_18, list_constant_41;
    Object list_constant_40, list_constant_54, list_constant_53;
    Object list_constant_13, list_constant_37, list_constant_19;
    Object list_constant_36, list_constant_35, list_constant_52;
    Object list_constant_7, list_constant_5;
    Object Qwrite_tracing_message_level_from_slot, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_9;
    Object list_constant_32, list_constant_42, Qsteps, Qmajor, Qab_at;
    Object list_constant_38, Qexit, Qentry, Qon, list_constant_34;
    Object list_constant_33, Qwrite_warning_message_level_from_slot;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_26;
    Object list_constant_25, list_constant_24, list_constant_23;
    Object list_constant_20, list_constant_15, list_constant_14, Qconditions;
    Object Qother, list_constant_21, Qdeficiencies, list_constant_17;
    Object list_constant_16, Qonly, Qerrors, Qkb, list_constant_11;
    Object list_constant_8, list_constant_4, Qcp, Qmessages, Qop;
    Object Qput_generate_source_annotation_info;
    Object Qput_show_procedure_invocation_hierarchy_at_pause_from_breakpoint;
    Object Qput_disassembler_enabled, Qput_source_stepping_level;
    Object Qput_breakpoint_level, Qput_tracing_message_level;
    Object Qput_warning_message_level, Qdeinstall_system_table;
    Object Qdeinstall_system_table_for_debugging_parameters;
    Object Qinstall_system_table;
    Object Qinstall_system_table_for_debugging_parameters;
    Object Qdisassembler_enabled_qm, Qtracing_and_breakpoints_enabled_qm;
    Object Qdeactivate_subclass_of_entity;
    Object Qdeactivate_subclass_of_entity_for_debugging_parameters;
    Object Qactivate_subclass_of_entity;
    Object Qactivate_subclass_of_entity_for_debugging_parameters;
    Object Qabsent_slot_putter;
    Object Qput_task_fragmentation_map_6_where_slot_is_absent;
    Object Qtask_fragmentation_map_6;
    Object Qput_kb_timestamp_field_5_where_slot_is_absent;
    Object Qkb_timestamp_field_5;
    Object Qput_kb_timestamp_field_4_where_slot_is_absent;
    Object Qkb_timestamp_field_4;
    Object Qput_kb_timestamp_field_3_where_slot_is_absent;
    Object Qkb_timestamp_field_3;
    Object Qput_kb_timestamp_field_2_where_slot_is_absent;
    Object Qkb_timestamp_field_2;
    Object Qput_kb_timestamp_field_1_where_slot_is_absent;
    Object Qkb_timestamp_field_1, Ksystem_frame, string_constant_70;
    Object string_constant_69, string_constant_68, string_constant_67;
    Object string_constant_66, string_constant_65, list_constant_3;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object Qsystem_table, Qnotify_user, G2_DEFSTRUCT_STRUCTURE_NAME_package;
    Object Qsnapshot_of_block, Qreclaim_structure;
    Object Qoutstanding_snapshot_of_block_count;
    Object Qsnapshot_of_block_structure_memory_usage, Qutilities2;
    Object string_constant_52, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_51, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qsnapshot_invocation_info;
    Object Qoutstanding_snapshot_invocation_info_count;
    Object Qsnapshot_invocation_info_structure_memory_usage;
    Object string_constant_50, string_constant_49;

    x_note_fn_call(94,99);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct = 
	    STATIC_SYMBOL("SNAPSHOT-INVOCATION-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qsnapshot_invocation_info = STATIC_SYMBOL("SNAPSHOT-INVOCATION-INFO",
	    AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct,
	    Qsnapshot_invocation_info,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qsnapshot_invocation_info,
	    Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_snapshot_invocation_info == UNBOUND)
	The_type_description_of_snapshot_invocation_info = Nil;
    string_constant_49 = 
	    STATIC_STRING("43Dy8m83nGy1n83nGy8n8k1l8n0000001m1n8y83-5ty1p83-DLy83-DKy83-DIy83-DMy83-DJy1m83My83-B4ykqk0k0");
    temp = The_type_description_of_snapshot_invocation_info;
    The_type_description_of_snapshot_invocation_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_49));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_snapshot_invocation_info_g2_struct,
	    The_type_description_of_snapshot_invocation_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qsnapshot_invocation_info,
	    The_type_description_of_snapshot_invocation_info,
	    Qtype_description_of_type);
    Qoutstanding_snapshot_invocation_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-SNAPSHOT-INVOCATION-INFO-COUNT",
	    AB_package);
    Qsnapshot_invocation_info_structure_memory_usage = 
	    STATIC_SYMBOL("SNAPSHOT-INVOCATION-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_50 = STATIC_STRING("1q83nGy8s83-q9y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_snapshot_invocation_info_count);
    push_optimized_constant(Qsnapshot_invocation_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_50));
    Qchain_of_available_snapshot_invocation_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SNAPSHOT-INVOCATION-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_snapshot_invocation_infos,
	    Chain_of_available_snapshot_invocation_infos);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_snapshot_invocation_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsnapshot_invocation_info_count = 
	    STATIC_SYMBOL("SNAPSHOT-INVOCATION-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsnapshot_invocation_info_count,
	    Snapshot_invocation_info_count);
    record_system_variable(Qsnapshot_invocation_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_snapshot_invocation_infos_vector == UNBOUND)
	Chain_of_available_snapshot_invocation_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsnapshot_invocation_info_structure_memory_usage,
	    STATIC_FUNCTION(snapshot_invocation_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_snapshot_invocation_info_count,
	    STATIC_FUNCTION(outstanding_snapshot_invocation_info_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_snapshot_invocation_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_snapshot_invocation_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qsnapshot_invocation_info,
	    reclaim_structure_for_snapshot_invocation_info_1);
    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct = 
	    STATIC_SYMBOL("SNAPSHOT-OF-BLOCK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qsnapshot_of_block = STATIC_SYMBOL("SNAPSHOT-OF-BLOCK",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_snapshot_of_block_g2_struct,
	    Qsnapshot_of_block,Qab_name_of_unique_structure_type);
    mutate_global_property(Qsnapshot_of_block,
	    Qg2_defstruct_structure_name_snapshot_of_block_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_snapshot_of_block == UNBOUND)
	The_type_description_of_snapshot_of_block = Nil;
    string_constant_51 = 
	    STATIC_STRING("43Dy8m83nHy1n83nHy8n8k1l8n0000001m1m8y83-5uy1m830ly83-DNykok0k0");
    temp = The_type_description_of_snapshot_of_block;
    The_type_description_of_snapshot_of_block = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_51));
    mutate_global_property(Qg2_defstruct_structure_name_snapshot_of_block_g2_struct,
	    The_type_description_of_snapshot_of_block,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qsnapshot_of_block,
	    The_type_description_of_snapshot_of_block,
	    Qtype_description_of_type);
    Qoutstanding_snapshot_of_block_count = 
	    STATIC_SYMBOL("OUTSTANDING-SNAPSHOT-OF-BLOCK-COUNT",AB_package);
    Qsnapshot_of_block_structure_memory_usage = 
	    STATIC_SYMBOL("SNAPSHOT-OF-BLOCK-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_52 = STATIC_STRING("1q83nHy8s83-qAy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_snapshot_of_block_count);
    push_optimized_constant(Qsnapshot_of_block_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_52));
    Qchain_of_available_snapshot_of_blocks = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-SNAPSHOT-OF-BLOCKS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_snapshot_of_blocks,
	    Chain_of_available_snapshot_of_blocks);
    record_system_variable(Qchain_of_available_snapshot_of_blocks,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qsnapshot_of_block_count = STATIC_SYMBOL("SNAPSHOT-OF-BLOCK-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsnapshot_of_block_count,
	    Snapshot_of_block_count);
    record_system_variable(Qsnapshot_of_block_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_snapshot_of_blocks_vector == UNBOUND)
	Chain_of_available_snapshot_of_blocks_vector = make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qsnapshot_of_block_structure_memory_usage,
	    STATIC_FUNCTION(snapshot_of_block_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_snapshot_of_block_count,
	    STATIC_FUNCTION(outstanding_snapshot_of_block_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_snapshot_of_block_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_snapshot_of_block,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qsnapshot_of_block,
	    reclaim_structure_for_snapshot_of_block_1);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    if (Snapshots_of_related_blocks == UNBOUND)
	Snapshots_of_related_blocks = Nil;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    if (Stack_of_deferred_notification_strings == UNBOUND)
	Stack_of_deferred_notification_strings = Nil;
    Qrecord_block_for_tformat = STATIC_SYMBOL("RECORD-BLOCK-FOR-TFORMAT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qrecord_block_for_tformat,
	    STATIC_FUNCTION(record_block_for_tformat,NIL,FALSE,1,1));
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qnotify_user = STATIC_SYMBOL("NOTIFY-USER",AB_package);
    SET_SYMBOL_FUNCTION(Qnotify_user,STATIC_FUNCTION(notify_user,NIL,TRUE,
	    1,10));
    if (Send_logbook_messages_to_console_p == UNBOUND)
	Send_logbook_messages_to_console_p = Nil;
    string_constant = STATIC_STRING("log: ~A");
    Qdebugging_parameters = STATIC_SYMBOL("DEBUGGING-PARAMETERS",AB_package);
    Qsystem_table = STATIC_SYMBOL("SYSTEM-TABLE",AB_package);
    list_constant_3 = STATIC_CONS(Qsystem_table,Qnil);
    check_if_superior_classes_are_defined(Qdebugging_parameters,
	    list_constant_3);
    string_constant_53 = STATIC_STRING("1l1l83ey");
    string_constant_54 = 
	    STATIC_STRING("13Iy4z8r832Ty832Ty8386y8386y0m001m1l8l1m8p832Ty000004z8r836My836My8386y8386y0k001m1l8l1m8p836My000004z8r8352y8352y8386y8386y0k00");
    string_constant_55 = 
	    STATIC_STRING("1m1l8l1m8p8352y000004z8r83A-y83A-y8386y8386y0k001m1l8l1m8p83A-y000004z8r839Py839Py8386y8386y00001o1l8o1l8l1l83Hy1m8p83Ky000004z8");
    string_constant_56 = 
	    STATIC_STRING("r83Zwy83Zwy8386y8386y08k001n1l8l1l83Cy1m8p83Ky000004z8r83Jxy83Jxy8386y8386y00001n1l8l1l83Cy1m8p83Ky000004z8r83Psy83Psy8386y8386y");
    string_constant_57 = 
	    STATIC_STRING("08k001n1l8l1l83Cy1m8p83Ky000004z8r83cHy83cHy8386y8386y00001o1l83Ey1m8p83FUy1l8l1l83Cy000004z8r83cJy83cJy8386y8386y00001p1l8l1l83");
    string_constant_58 = 
	    STATIC_STRING("Ey1l83Ny1l83Hy1m83Dy5sInternal000004z8r83cIy83cIy8386y8386y00001p1l8l1l83Ey1l83Ny1l83Hy1m83Dy5sInternal000004z8r83cGy83cGy8386y8");
    string_constant_59 = 
	    STATIC_STRING("386y00001p1l8l1l83Ey1l83Ny1l83Hy1m83Dy5sInternal000004z8r83RSy83RSy8386y8386y00001m1l8l1l83Cy000004z8r83KCy83KCy8386y8386y03=4y0");
    string_constant_60 = 
	    STATIC_STRING("01o1l83Ey1m8p83Biy1l8l1l83Hy000004z8r83bSy83bSy8386y8386y00001p1l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal000004z8r83bTy83bTy8386y8386y");
    string_constant_61 = 
	    STATIC_STRING("00001p1l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal000004z8r83bUy83bUy8386y8386y00001p1l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal000004z8r83bVy8");
    string_constant_62 = 
	    STATIC_STRING("3bVy8386y8386y00001p1l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal000004z8r83bWy83bWy8386y8386y00001o1l8o1l8l1l83Cy1l83Ny000004z8r83Uly83U");
    string_constant_63 = 
	    STATIC_STRING("ly8386y8386y00001p1l8o1l8l1l83Hy1l83Ny1m83Dy5sInternal000004z8r83Umy83Umy8386y8386y00001p1l8o1l8l1l83Hy1l83Ny1m83Dy5sInternal000");
    string_constant_64 = 
	    STATIC_STRING("004z8r83H*y83H*y8386y8386y00001p1l8o1l8l1l83Hy1l83Ny1m83Dy5sInternal00000");
    string_constant_65 = 
	    STATIC_STRING("13Ky8q1n8386y1l83-sy83ey1o832Tym8l1m8p832Ty1o836Myk8l1m8p836My1o8352yk8l1m8p8352y1o83A-yk8l1m8p83A-y1q839Py08o8l83Hy1m8p83Ky1p83");
    string_constant_66 = 
	    STATIC_STRING("Zwy8k1l8l1l83Cy1m8p83Ky1p83Jxy01l8l1l83Cy1m8p83Ky1p83Psy8k1l8l1l83Cy1m8p83Ky1q83cHy01l83Ey1m8p83FUy1l8l1l83Cy1q83cJy01l83Ey1l83N");
    string_constant_67 = 
	    STATIC_STRING("y1l83Hy1m83Dy5sInternal1q83cIy01l83Ey1l83Ny1l83Hy1m83Dy5sInternal1q83cGy01l83Ey1l83Ny1l83Hy1m83Dy5sInternal1o83RSy08l83Cy1q83KCy");
    string_constant_68 = 
	    STATIC_STRING("3=4y1l83Ey1m8p83Biy1l8l1l83Hy1r83bSy01l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal1r83bTy01l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal1r83bUy01l8");
    string_constant_69 = 
	    STATIC_STRING("o1l8l1l83Cy1l83Ny1m83Dy5sInternal1r83bVy01l8o1l8l1l83Cy1l83Ny1m83Dy5sInternal1q83bWy01l8o1l8l1l83Cy1l83Ny1r83Uly01l8o1l8l1l83Hy1");
    string_constant_70 = 
	    STATIC_STRING("l83Ny1m83Dy5sInternal1r83Umy01l8o1l8l1l83Hy1l83Ny1m83Dy5sInternal1r83H*y01l8o1l8l1l83Hy1l83Ny1m83Dy5sInternal");
    temp = regenerate_optimized_constant(string_constant_53);
    temp_1 = regenerate_optimized_constant(list(11,string_constant_54,
	    string_constant_55,string_constant_56,string_constant_57,
	    string_constant_58,string_constant_59,string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63,
	    string_constant_64));
    add_class_to_environment(9,Qdebugging_parameters,list_constant_3,Nil,
	    temp,Nil,temp_1,list_constant_3,
	    regenerate_optimized_constant(list(6,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69,string_constant_70)),Nil);
    SET_SYMBOL_VALUE_LOCATION(Qdebugging_parameters,Debugging_parameters);
    Qab_debug = STATIC_SYMBOL("DEBUG",AB_package);
    Ksystem_frame = STATIC_SYMBOL("SYSTEM-FRAME",Pkeyword);
    record_system_variable(Qdebugging_parameters,Qab_debug,Ksystem_frame,
	    Qnil,Qnil,Qnil,Qt);
    Qkb_timestamp_field_1 = STATIC_SYMBOL("KB-TIMESTAMP-FIELD-1",AB_package);
    Qput_kb_timestamp_field_1_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-TIMESTAMP-FIELD-1-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_timestamp_field_1_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_timestamp_field_1_where_slot_is_absent,
	    NIL,FALSE,2,2));
    Qabsent_slot_putter = STATIC_SYMBOL("ABSENT-SLOT-PUTTER",AB_package);
    mutate_global_property(Qkb_timestamp_field_1,
	    SYMBOL_FUNCTION(Qput_kb_timestamp_field_1_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qkb_timestamp_field_2 = STATIC_SYMBOL("KB-TIMESTAMP-FIELD-2",AB_package);
    Qput_kb_timestamp_field_2_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-TIMESTAMP-FIELD-2-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_timestamp_field_2_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_timestamp_field_2_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qkb_timestamp_field_2,
	    SYMBOL_FUNCTION(Qput_kb_timestamp_field_2_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qkb_timestamp_field_3 = STATIC_SYMBOL("KB-TIMESTAMP-FIELD-3",AB_package);
    Qput_kb_timestamp_field_3_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-TIMESTAMP-FIELD-3-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_timestamp_field_3_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_timestamp_field_3_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qkb_timestamp_field_3,
	    SYMBOL_FUNCTION(Qput_kb_timestamp_field_3_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qkb_timestamp_field_4 = STATIC_SYMBOL("KB-TIMESTAMP-FIELD-4",AB_package);
    Qput_kb_timestamp_field_4_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-TIMESTAMP-FIELD-4-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_timestamp_field_4_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_timestamp_field_4_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qkb_timestamp_field_4,
	    SYMBOL_FUNCTION(Qput_kb_timestamp_field_4_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qkb_timestamp_field_5 = STATIC_SYMBOL("KB-TIMESTAMP-FIELD-5",AB_package);
    Qput_kb_timestamp_field_5_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-KB-TIMESTAMP-FIELD-5-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_kb_timestamp_field_5_where_slot_is_absent,
	    STATIC_FUNCTION(put_kb_timestamp_field_5_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qkb_timestamp_field_5,
	    SYMBOL_FUNCTION(Qput_kb_timestamp_field_5_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qtask_fragmentation_map_6 = STATIC_SYMBOL("TASK-FRAGMENTATION-MAP-6",
	    AB_package);
    Qput_task_fragmentation_map_6_where_slot_is_absent = 
	    STATIC_SYMBOL("PUT-TASK-FRAGMENTATION-MAP-6-WHERE-SLOT-IS-ABSENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_task_fragmentation_map_6_where_slot_is_absent,
	    STATIC_FUNCTION(put_task_fragmentation_map_6_where_slot_is_absent,
	    NIL,FALSE,2,2));
    mutate_global_property(Qtask_fragmentation_map_6,
	    SYMBOL_FUNCTION(Qput_task_fragmentation_map_6_where_slot_is_absent),
	    Qabsent_slot_putter);
    Qactivate_subclass_of_entity_for_debugging_parameters = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY-FOR-DEBUGGING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_debugging_parameters,
	    STATIC_FUNCTION(activate_subclass_of_entity_for_debugging_parameters,
	    NIL,FALSE,1,1));
    Qactivate_subclass_of_entity = 
	    STATIC_SYMBOL("ACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qactivate_subclass_of_entity_for_debugging_parameters);
    set_get(Qdebugging_parameters,Qactivate_subclass_of_entity,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qdebugging_parameters,temp);
    mutate_global_property(Qactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qdeactivate_subclass_of_entity_for_debugging_parameters = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY-FOR-DEBUGGING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_debugging_parameters,
	    STATIC_FUNCTION(deactivate_subclass_of_entity_for_debugging_parameters,
	    NIL,FALSE,1,1));
    Qdeactivate_subclass_of_entity = 
	    STATIC_SYMBOL("DEACTIVATE-SUBCLASS-OF-ENTITY",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qdeactivate_subclass_of_entity_for_debugging_parameters);
    set_get(Qdebugging_parameters,Qdeactivate_subclass_of_entity,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate_subclass_of_entity),
	    Qclasses_which_define);
    temp_2 = CONS(Qdebugging_parameters,temp);
    mutate_global_property(Qdeactivate_subclass_of_entity,temp_2,
	    Qclasses_which_define);
    Qmessage_and_breakpoint_overrides = 
	    STATIC_SYMBOL("MESSAGE-AND-BREAKPOINT-OVERRIDES",AB_package);
    Qtracing_and_breakpoints_enabled_qm = 
	    STATIC_SYMBOL("TRACING-AND-BREAKPOINTS-ENABLED\?",AB_package);
    alias_slot_name(3,Qmessage_and_breakpoint_overrides,
	    Qtracing_and_breakpoints_enabled_qm,Qdebugging_parameters);
    Qdisassembler_enabled = STATIC_SYMBOL("DISASSEMBLER-ENABLED",AB_package);
    Qdisassembler_enabled_qm = STATIC_SYMBOL("DISASSEMBLER-ENABLED\?",
	    AB_package);
    alias_slot_name(3,Qdisassembler_enabled,Qdisassembler_enabled_qm,
	    Qdebugging_parameters);
    Qwarning_message_level = STATIC_SYMBOL("WARNING-MESSAGE-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qwarning_message_level,Warning_message_level);
    record_system_variable(Qwarning_message_level,Qab_debug,
	    FIX((SI_Long)2L),Qnil,Qnil,Qnil,Qnil);
    Qtracing_message_level = STATIC_SYMBOL("TRACING-MESSAGE-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtracing_message_level,Tracing_message_level);
    record_system_variable(Qtracing_message_level,Qab_debug,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qbreakpoint_level = STATIC_SYMBOL("BREAKPOINT-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbreakpoint_level,Breakpoint_level);
    record_system_variable(Qbreakpoint_level,Qab_debug,FIX((SI_Long)0L),
	    Qnil,Qnil,Qnil,Qnil);
    Qsource_stepping_level = STATIC_SYMBOL("SOURCE-STEPPING-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsource_stepping_level,Source_stepping_level);
    record_system_variable(Qsource_stepping_level,Qab_debug,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qdebugging_reset = STATIC_SYMBOL("DEBUGGING-RESET",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdebugging_reset,Debugging_reset);
    record_system_variable(Qdebugging_reset,Qab_debug,Nil,Qnil,Qnil,Qnil,Qnil);
    Qgenerate_source_annotation_info = 
	    STATIC_SYMBOL("GENERATE-SOURCE-ANNOTATION-INFO",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgenerate_source_annotation_info,
	    Generate_source_annotation_info);
    record_system_variable(Qgenerate_source_annotation_info,Qab_debug,T,
	    Qnil,Qnil,Qnil,Qnil);
    Qshow_procedure_invocation_hierarchy_at_pause_from_breakpoint = 
	    STATIC_SYMBOL("SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT",
	    AB_package);
    Qinstall_system_table_for_debugging_parameters = 
	    STATIC_SYMBOL("INSTALL-SYSTEM-TABLE-FOR-DEBUGGING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qinstall_system_table_for_debugging_parameters,
	    STATIC_FUNCTION(install_system_table_for_debugging_parameters,
	    NIL,FALSE,1,1));
    Qinstall_system_table = STATIC_SYMBOL("INSTALL-SYSTEM-TABLE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinstall_system_table_for_debugging_parameters);
    set_get(Qdebugging_parameters,Qinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qdebugging_parameters,temp);
    mutate_global_property(Qinstall_system_table,temp_2,Qclasses_which_define);
    Qdeinstall_system_table_for_debugging_parameters = 
	    STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE-FOR-DEBUGGING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdeinstall_system_table_for_debugging_parameters,
	    STATIC_FUNCTION(deinstall_system_table_for_debugging_parameters,
	    NIL,FALSE,1,1));
    Qdeinstall_system_table = STATIC_SYMBOL("DEINSTALL-SYSTEM-TABLE",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeinstall_system_table_for_debugging_parameters);
    set_get(Qdebugging_parameters,Qdeinstall_system_table,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeinstall_system_table),
	    Qclasses_which_define);
    temp_2 = CONS(Qdebugging_parameters,temp);
    mutate_global_property(Qdeinstall_system_table,temp_2,
	    Qclasses_which_define);
    Qput_warning_message_level = STATIC_SYMBOL("PUT-WARNING-MESSAGE-LEVEL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_warning_message_level,
	    STATIC_FUNCTION(put_warning_message_level,NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qwarning_message_level,
	    SYMBOL_FUNCTION(Qput_warning_message_level),Qslot_putter);
    Qput_tracing_message_level = STATIC_SYMBOL("PUT-TRACING-MESSAGE-LEVEL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_tracing_message_level,
	    STATIC_FUNCTION(put_tracing_message_level,NIL,FALSE,3,3));
    mutate_global_property(Qtracing_message_level,
	    SYMBOL_FUNCTION(Qput_tracing_message_level),Qslot_putter);
    Qput_breakpoint_level = STATIC_SYMBOL("PUT-BREAKPOINT-LEVEL",AB_package);
    SET_SYMBOL_FUNCTION(Qput_breakpoint_level,
	    STATIC_FUNCTION(put_breakpoint_level,NIL,FALSE,3,3));
    mutate_global_property(Qbreakpoint_level,
	    SYMBOL_FUNCTION(Qput_breakpoint_level),Qslot_putter);
    Qput_source_stepping_level = STATIC_SYMBOL("PUT-SOURCE-STEPPING-LEVEL",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_source_stepping_level,
	    STATIC_FUNCTION(put_source_stepping_level,NIL,FALSE,3,3));
    mutate_global_property(Qsource_stepping_level,
	    SYMBOL_FUNCTION(Qput_source_stepping_level),Qslot_putter);
    Qput_disassembler_enabled = STATIC_SYMBOL("PUT-DISASSEMBLER-ENABLED",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_disassembler_enabled,
	    STATIC_FUNCTION(put_disassembler_enabled,NIL,FALSE,3,3));
    mutate_global_property(Qdisassembler_enabled,
	    SYMBOL_FUNCTION(Qput_disassembler_enabled),Qslot_putter);
    Qput_show_procedure_invocation_hierarchy_at_pause_from_breakpoint = 
	    STATIC_SYMBOL("PUT-SHOW-PROCEDURE-INVOCATION-HIERARCHY-AT-PAUSE-FROM-BREAKPOINT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qput_show_procedure_invocation_hierarchy_at_pause_from_breakpoint,
	    STATIC_FUNCTION(put_show_procedure_invocation_hierarchy_at_pause_from_breakpoint,
	    NIL,FALSE,3,3));
    mutate_global_property(Qshow_procedure_invocation_hierarchy_at_pause_from_breakpoint,
	    SYMBOL_FUNCTION(Qput_show_procedure_invocation_hierarchy_at_pause_from_breakpoint),
	    Qslot_putter);
    Qput_generate_source_annotation_info = 
	    STATIC_SYMBOL("PUT-GENERATE-SOURCE-ANNOTATION-INFO",AB_package);
    SET_SYMBOL_FUNCTION(Qput_generate_source_annotation_info,
	    STATIC_FUNCTION(put_generate_source_annotation_info,NIL,FALSE,
	    3,3));
    mutate_global_property(Qgenerate_source_annotation_info,
	    SYMBOL_FUNCTION(Qput_generate_source_annotation_info),
	    Qslot_putter);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qquote,FIX((SI_Long)0L));
    Qop = STATIC_SYMBOL("(",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qquote,Qop);
    Qab_no = STATIC_SYMBOL("NO",AB_package);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qquote,Qab_no);
    Qab_warning = STATIC_SYMBOL("WARNING",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qquote,Qab_warning);
    Qmessages = STATIC_SYMBOL("MESSAGES",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qquote,Qmessages);
    Qcp = STATIC_SYMBOL(")",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qquote,Qcp);
    list_constant_10 = STATIC_CONS(list_constant_4,Qnil);
    list_constant_11 = STATIC_LIST_STAR((SI_Long)6L,list_constant_5,
	    list_constant_6,list_constant_7,list_constant_8,
	    list_constant_9,list_constant_10);
    list_constant_12 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,Qwarning_message_level,
	    list_constant_11,list_constant_12);
    list_constant_13 = STATIC_CONS(Qquote,list_constant_12);
    Qkb = STATIC_SYMBOL("KB",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qquote,Qkb);
    Qerrors = STATIC_SYMBOL("ERRORS",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qquote,Qerrors);
    Qonly = STATIC_SYMBOL("ONLY",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qquote,Qonly);
    list_constant_17 = STATIC_LIST_STAR((SI_Long)6L,list_constant_13,
	    list_constant_6,list_constant_14,list_constant_15,
	    list_constant_16,list_constant_10);
    list_constant_28 = STATIC_LIST_STAR((SI_Long)3L,Qwarning_message_level,
	    list_constant_17,list_constant_12);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qquote,FIX((SI_Long)2L));
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qquote,Qand);
    Qdeficiencies = STATIC_SYMBOL("DEFICIENCIES",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qquote,Qdeficiencies);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)7L,list_constant_18,
	    list_constant_6,list_constant_14,list_constant_15,
	    list_constant_19,list_constant_20,list_constant_10);
    list_constant_29 = STATIC_LIST_STAR((SI_Long)3L,Qwarning_message_level,
	    list_constant_21,list_constant_12);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qquote,FIX((SI_Long)3L));
    Qcm = STATIC_SYMBOL(",",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qquote,Qcm);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qquote,Qother);
    Qconditions = STATIC_SYMBOL("CONDITIONS",AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquote,Qconditions);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)11L,list_constant_22,
	    list_constant_6,list_constant_14,list_constant_15,
	    list_constant_23,list_constant_20,list_constant_23,
	    list_constant_19,list_constant_24,list_constant_25,
	    list_constant_10);
    list_constant_30 = STATIC_LIST_STAR((SI_Long)3L,Qwarning_message_level,
	    list_constant_26,list_constant_12);
    list_constant_31 = STATIC_LIST((SI_Long)4L,list_constant_27,
	    list_constant_28,list_constant_29,list_constant_30);
    add_grammar_rules_function(list_constant_31);
    string_constant_1 = STATIC_STRING("0 (no warning messages)");
    string_constant_2 = STATIC_STRING("1 (kb errors only)");
    string_constant_3 = STATIC_STRING("2 (kb errors and deficiencies)");
    string_constant_4 = 
	    STATIC_STRING("3 (kb errors, deficiencies, and other conditions)");
    Qwrite_warning_message_level_from_slot = 
	    STATIC_SYMBOL("WRITE-WARNING-MESSAGE-LEVEL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_warning_message_level_from_slot,
	    STATIC_FUNCTION(write_warning_message_level_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qwarning_message_level,
	    SYMBOL_FUNCTION(Qwrite_warning_message_level_from_slot),
	    Qslot_value_writer);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qquote,Qtrace);
    list_constant_33 = STATIC_CONS(list_constant_9,list_constant_10);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)5L,list_constant_5,
	    list_constant_6,list_constant_7,list_constant_32,list_constant_33);
    list_constant_46 = STATIC_LIST_STAR((SI_Long)3L,Qtracing_message_level,
	    list_constant_34,list_constant_12);
    Qon = STATIC_SYMBOL("ON",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qquote,Qon);
    Qentry = STATIC_SYMBOL("ENTRY",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qquote,Qentry);
    Qexit = STATIC_SYMBOL("EXIT",AB_package);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qquote,Qexit);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)9L,list_constant_13,
	    list_constant_6,list_constant_32,list_constant_9,
	    list_constant_35,list_constant_36,list_constant_19,
	    list_constant_37,list_constant_10);
    list_constant_47 = STATIC_LIST_STAR((SI_Long)3L,Qtracing_message_level,
	    list_constant_38,list_constant_12);
    Qab_at = STATIC_SYMBOL("AT",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qquote,Qab_at);
    Qmajor = STATIC_SYMBOL("MAJOR",AB_package);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qquote,Qmajor);
    Qsteps = STATIC_SYMBOL("STEPS",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qquote,Qsteps);
    list_constant_42 = STATIC_LIST_STAR((SI_Long)8L,list_constant_18,
	    list_constant_6,list_constant_32,list_constant_9,
	    list_constant_39,list_constant_40,list_constant_41,
	    list_constant_10);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,Qtracing_message_level,
	    list_constant_42,list_constant_12);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qquote,Qevery);
    list_constant_44 = STATIC_LIST((SI_Long)2L,Qquote,Qstep);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)8L,list_constant_22,
	    list_constant_6,list_constant_32,list_constant_9,
	    list_constant_39,list_constant_43,list_constant_44,
	    list_constant_10);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)3L,Qtracing_message_level,
	    list_constant_45,list_constant_12);
    list_constant_50 = STATIC_LIST((SI_Long)4L,list_constant_46,
	    list_constant_47,list_constant_48,list_constant_49);
    add_grammar_rules_function(list_constant_50);
    string_constant_5 = STATIC_STRING("0 (no trace messages)");
    string_constant_6 = STATIC_STRING("1 (trace messages on entry and exit)");
    string_constant_7 = STATIC_STRING("2 (trace messages at major steps)");
    string_constant_8 = STATIC_STRING("3 (trace messages at every step)");
    Qwrite_tracing_message_level_from_slot = 
	    STATIC_SYMBOL("WRITE-TRACING-MESSAGE-LEVEL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_tracing_message_level_from_slot,
	    STATIC_FUNCTION(write_tracing_message_level_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtracing_message_level,
	    SYMBOL_FUNCTION(Qwrite_tracing_message_level_from_slot),
	    Qslot_value_writer);
    Qbreakpoints = STATIC_SYMBOL("BREAKPOINTS",AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qquote,Qbreakpoints);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)5L,list_constant_5,
	    list_constant_6,list_constant_7,list_constant_51,list_constant_10);
    list_constant_59 = STATIC_LIST_STAR((SI_Long)3L,Qbreakpoint_level,
	    list_constant_52,list_constant_12);
    list_constant_53 = STATIC_LIST_STAR((SI_Long)5L,list_constant_35,
	    list_constant_36,list_constant_19,list_constant_37,
	    list_constant_10);
    list_constant_54 = STATIC_LIST_STAR((SI_Long)4L,list_constant_13,
	    list_constant_6,list_constant_51,list_constant_53);
    list_constant_60 = STATIC_LIST_STAR((SI_Long)3L,Qbreakpoint_level,
	    list_constant_54,list_constant_12);
    list_constant_55 = STATIC_LIST_STAR((SI_Long)4L,list_constant_39,
	    list_constant_40,list_constant_41,list_constant_10);
    list_constant_56 = STATIC_LIST_STAR((SI_Long)4L,list_constant_18,
	    list_constant_6,list_constant_51,list_constant_55);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)3L,Qbreakpoint_level,
	    list_constant_56,list_constant_12);
    list_constant_57 = STATIC_LIST_STAR((SI_Long)4L,list_constant_39,
	    list_constant_43,list_constant_44,list_constant_10);
    list_constant_58 = STATIC_LIST_STAR((SI_Long)4L,list_constant_22,
	    list_constant_6,list_constant_51,list_constant_57);
    list_constant_62 = STATIC_LIST_STAR((SI_Long)3L,Qbreakpoint_level,
	    list_constant_58,list_constant_12);
    list_constant_63 = STATIC_LIST((SI_Long)4L,list_constant_59,
	    list_constant_60,list_constant_61,list_constant_62);
    add_grammar_rules_function(list_constant_63);
    string_constant_9 = STATIC_STRING("0 (no breakpoints)");
    string_constant_10 = STATIC_STRING("1 (breakpoints on entry and exit)");
    string_constant_11 = STATIC_STRING("2 (breakpoints at major steps)");
    string_constant_12 = STATIC_STRING("3 (breakpoints at every step)");
    Qwrite_breakpoint_level_from_slot = 
	    STATIC_SYMBOL("WRITE-BREAKPOINT-LEVEL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_breakpoint_level_from_slot,
	    STATIC_FUNCTION(write_breakpoint_level_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qbreakpoint_level,
	    SYMBOL_FUNCTION(Qwrite_breakpoint_level_from_slot),
	    Qslot_value_writer);
    string_constant_71 = 
	    STATIC_STRING("1m1n83A-y1q1m9kk1m9k83-9y1m9k83=Ty1m9k83aWy1m9k83-Dly1m9k83-Ayl1n83A-y1p1m9kl1m9k83-9y1m9k83aWy1m9k83-Dly1m9k83-Ayl");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_71));
    string_constant_13 = STATIC_STRING("0 (no source stepping)");
    string_constant_14 = STATIC_STRING("1 (source stepping)");
    Qwrite_source_stepping_level_from_slot = 
	    STATIC_SYMBOL("WRITE-SOURCE-STEPPING-LEVEL-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_source_stepping_level_from_slot,
	    STATIC_FUNCTION(write_source_stepping_level_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qsource_stepping_level,
	    SYMBOL_FUNCTION(Qwrite_source_stepping_level_from_slot),
	    Qslot_value_writer);
    string_constant_72 = 
	    STATIC_STRING("1n1n83-eVy1p1m9k83=Ty1m9k83fSy1m9k83=Uy1m9k83-FAy1m9k83Djyl1n83-eVy1q1m9k83=Ty1m9k83fSy1m9k83vy1m9k83-FAy1m9k83Djy1m9k83h1ym1n83");
    string_constant_73 = 
	    STATIC_STRING("-eVy1p1m9k83fSy1m9k83-ty1m9k83-FAy1m9k83Djy1m9k83h1yp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_72,
	    string_constant_73)));
    Qno_messages = STATIC_SYMBOL("NO-MESSAGES",AB_package);
    list_constant_64 = STATIC_CONS(Qab_no,Qno_messages);
    Qno_breakpoints = STATIC_SYMBOL("NO-BREAKPOINTS",AB_package);
    list_constant_65 = STATIC_CONS(Qbreakpoints,Qno_breakpoints);
    list_constant = STATIC_LIST((SI_Long)2L,list_constant_64,list_constant_65);
    Qmessage_overrides = STATIC_SYMBOL("MESSAGE-OVERRIDES",AB_package);
    Qcompile_message_overrides_for_slot = 
	    STATIC_SYMBOL("COMPILE-MESSAGE-OVERRIDES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_message_overrides_for_slot,
	    STATIC_FUNCTION(compile_message_overrides_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qmessage_overrides,
	    SYMBOL_FUNCTION(Qcompile_message_overrides_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qmessage_overrides,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_15 = STATIC_STRING("no breakpoints or trace messages");
    string_constant_16 = 
	    STATIC_STRING("no breakpoints, trace messages enabled");
    string_constant_17 = 
	    STATIC_STRING("breakpoints and trace messages enabled");
    Qwrite_message_overrides_from_slot = 
	    STATIC_SYMBOL("WRITE-MESSAGE-OVERRIDES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_message_overrides_from_slot,
	    STATIC_FUNCTION(write_message_overrides_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qmessage_overrides,
	    SYMBOL_FUNCTION(Qwrite_message_overrides_from_slot),
	    Qslot_value_writer);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_74 = 
	    STATIC_STRING("1y1m83-py1m9k83Py1m83-py83-tfy1m83-tfy83-wsy1o83-tfy1n83-wsy1m9k83-Zy83-tfy1nmln9l1m83-tfy83-tgy1o83-tfy1n83-tgy1m9k83-Zy83-tfy1");
    string_constant_75 = 
	    STATIC_STRING("nmln9l1m83-tfy83-L2y1o83-tfy1n83-L2y1m9k83-Zy83-tfy1nmln9l1m83-tfy83-qKy1o83-tfy1n83-qKy1m9k83-Zy83-tfy1nmln9l1n83-wsy1o1m9k83oW");
    string_constant_76 = 
	    STATIC_STRING("y1m9k9m1m9k83-2*y832Ty2l83oWyo1n83-tgy1o1m9k83-tey1m9k9m1m9k83-2*y836My2l83-teyo1n83-L2y1n1m9k83B0y1m9k83-2*y8352y2l83B0yn1n83-q");
    string_constant_77 = 
	    STATIC_STRING("Ky1o1m9k83aWy1m9k83-Dly1m9k83-2*y83A-y2l83-qJyo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qmessage);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_4(string_constant_74,
	    string_constant_75,string_constant_76,string_constant_77)));
    Qdebugging_shift_alist = STATIC_SYMBOL("DEBUGGING-SHIFT-ALIST",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdebugging_shift_alist,Debugging_shift_alist);
    list_constant_66 = STATIC_CONS(Qab_warning,FIX((SI_Long)0L));
    Qtracing = STATIC_SYMBOL("TRACING",AB_package);
    list_constant_67 = STATIC_CONS(Qtracing,FIX((SI_Long)4L));
    Qbreakpoint = STATIC_SYMBOL("BREAKPOINT",AB_package);
    list_constant_68 = STATIC_CONS(Qbreakpoint,FIX((SI_Long)8L));
    Qsource_stepping = STATIC_SYMBOL("SOURCE-STEPPING",AB_package);
    list_constant_69 = STATIC_CONS(Qsource_stepping,FIX((SI_Long)12L));
    list_constant_70 = STATIC_LIST((SI_Long)4L,list_constant_66,
	    list_constant_67,list_constant_68,list_constant_69);
    SET_SYMBOL_VALUE(Qdebugging_shift_alist,list_constant_70);
    Qcompletely_unspecified_debugging_code = 
	    STATIC_SYMBOL("COMPLETELY-UNSPECIFIED-DEBUGGING-CODE",AB_package);
    SET_SYMBOL_VALUE(Qcompletely_unspecified_debugging_code,
	    FIX((SI_Long)65535L));
    if (Disable_tracing_and_breakpoints_warning == UNBOUND)
	Disable_tracing_and_breakpoints_warning = Nil;
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    string_constant_18 = 
	    STATIC_STRING("Note that messages and/or breakpoints have been disabled.");
    Qtracing_and_breakpoints = STATIC_SYMBOL("TRACING-AND-BREAKPOINTS",
	    AB_package);
    Qcompile_tracing_and_breakpoints_for_slot = 
	    STATIC_SYMBOL("COMPILE-TRACING-AND-BREAKPOINTS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_tracing_and_breakpoints_for_slot,
	    STATIC_FUNCTION(compile_tracing_and_breakpoints_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qtracing_and_breakpoints,
	    SYMBOL_FUNCTION(Qcompile_tracing_and_breakpoints_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qtracing_and_breakpoints,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_71 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_72 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,list_constant_71);
    set_property_value_function(get_symbol_properties_function(Qtracing_and_breakpoints),
	    Qtype_specification_simple_expansion,list_constant_72);
    list_constant_83 = STATIC_LIST((SI_Long)2L,Qmember,Qdefault);
    list_constant_73 = STATIC_CONS(FIX((SI_Long)3L),Qnil);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)5L,Qmember,
	    FIX((SI_Long)0L),FIX((SI_Long)1L),FIX((SI_Long)2L),
	    list_constant_73);
    list_constant_75 = STATIC_CONS(list_constant_74,Qnil);
    list_constant_77 = STATIC_CONS(Qwarning_message_level,list_constant_75);
    list_constant_78 = STATIC_CONS(Qtracing_message_level,list_constant_75);
    list_constant_79 = STATIC_CONS(Qbreakpoint_level,list_constant_75);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)3L,Qmember,
	    FIX((SI_Long)0L),list_constant_12);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qsource_stepping_level,
	    list_constant_76);
    list_constant_81 = STATIC_LIST((SI_Long)4L,list_constant_77,
	    list_constant_78,list_constant_79,list_constant_80);
    list_constant_82 = STATIC_LIST((SI_Long)5L,Qab_or,
	    Qwarning_message_level,Qtracing_message_level,
	    Qbreakpoint_level,Qsource_stepping_level);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_81,list_constant_82);
    list_constant_2 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_83,
	    list_constant_84);
    define_type_specification_explicit_complex_type(Qtracing_and_breakpoints,
	    list_constant_2);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qnamed,Qtracing_and_breakpoints);
    tracing_and_breakpoints_evaluation_setter_1 = 
	    STATIC_FUNCTION(tracing_and_breakpoints_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qtracing_and_breakpoints,
	    tracing_and_breakpoints_evaluation_setter_1);
    tracing_and_breakpoints_evaluation_getter_1 = 
	    STATIC_FUNCTION(tracing_and_breakpoints_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtracing_and_breakpoints,
	    tracing_and_breakpoints_evaluation_getter_1);
    Qtrend_chart = STATIC_SYMBOL("TREND-CHART",AB_package);
    Qput_tracing_and_breakpoints = 
	    STATIC_SYMBOL("PUT-TRACING-AND-BREAKPOINTS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_tracing_and_breakpoints,
	    STATIC_FUNCTION(put_tracing_and_breakpoints,NIL,FALSE,3,3));
    mutate_global_property(Qtracing_and_breakpoints,
	    SYMBOL_FUNCTION(Qput_tracing_and_breakpoints),Qslot_putter);
    string_constant_19 = STATIC_STRING("default");
    string_constant_20 = STATIC_STRING("warning message level ");
    string_constant_21 = STATIC_STRING("; ");
    string_constant_22 = STATIC_STRING("tracing message level ");
    string_constant_23 = STATIC_STRING("breakpoint level ");
    string_constant_24 = STATIC_STRING("source stepping level ");
    Qwrite_tracing_and_breakpoints_from_slot = 
	    STATIC_SYMBOL("WRITE-TRACING-AND-BREAKPOINTS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_tracing_and_breakpoints_from_slot,
	    STATIC_FUNCTION(write_tracing_and_breakpoints_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtracing_and_breakpoints,
	    SYMBOL_FUNCTION(Qwrite_tracing_and_breakpoints_from_slot),
	    Qslot_value_writer);
    string_constant_78 = STATIC_STRING("1m1m83FUy83-Uy1n83FUy1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_78));
    list_constant_85 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant_25 = STATIC_STRING("~a");
    Qtrace_file_pathname = STATIC_SYMBOL("TRACE-FILE-PATHNAME",AB_package);
    Qwrite_trace_file_pathname_from_slot = 
	    STATIC_SYMBOL("WRITE-TRACE-FILE-PATHNAME-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_trace_file_pathname_from_slot,
	    STATIC_FUNCTION(write_trace_file_pathname_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qtrace_file_pathname,
	    SYMBOL_FUNCTION(Qwrite_trace_file_pathname_from_slot),
	    Qslot_value_writer);
    Qtracing_file = STATIC_SYMBOL("TRACING-FILE",AB_package);
    Qput_tracing_file = STATIC_SYMBOL("PUT-TRACING-FILE",AB_package);
    SET_SYMBOL_FUNCTION(Qput_tracing_file,STATIC_FUNCTION(put_tracing_file,
	    NIL,FALSE,3,3));
    mutate_global_property(Qtracing_file,
	    SYMBOL_FUNCTION(Qput_tracing_file),Qslot_putter);
    Qput_message_and_breakpoint_overrides = 
	    STATIC_SYMBOL("PUT-MESSAGE-AND-BREAKPOINT-OVERRIDES",AB_package);
    SET_SYMBOL_FUNCTION(Qput_message_and_breakpoint_overrides,
	    STATIC_FUNCTION(put_message_and_breakpoint_overrides,NIL,FALSE,
	    3,3));
    mutate_global_property(Qmessage_and_breakpoint_overrides,
	    SYMBOL_FUNCTION(Qput_message_and_breakpoint_overrides),
	    Qslot_putter);
    Qsaved_warning_level = STATIC_SYMBOL("SAVED-WARNING-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaved_warning_level,Saved_warning_level);
    record_system_variable(Qsaved_warning_level,Qab_debug,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qsaved_tracing_level = STATIC_SYMBOL("SAVED-TRACING-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaved_tracing_level,Saved_tracing_level);
    record_system_variable(Qsaved_tracing_level,Qab_debug,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qsaved_breakpoint_level = STATIC_SYMBOL("SAVED-BREAKPOINT-LEVEL",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaved_breakpoint_level,Saved_breakpoint_level);
    record_system_variable(Qsaved_breakpoint_level,Qab_debug,Nil,Qnil,Qnil,
	    Qnil,Qnil);
    Qsaved_source_stepping_level = 
	    STATIC_SYMBOL("SAVED-SOURCE-STEPPING-LEVEL",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsaved_source_stepping_level,
	    Saved_source_stepping_level);
    record_system_variable(Qsaved_source_stepping_level,Qab_debug,Nil,Qnil,
	    Qnil,Qnil,Qnil);
    Qtrace_messages_within_extent_of_rule = 
	    STATIC_SYMBOL("TRACE-MESSAGES-WITHIN-EXTENT-OF-RULE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtrace_messages_within_extent_of_rule,
	    Trace_messages_within_extent_of_rule);
    record_system_variable(Qtrace_messages_within_extent_of_rule,Qab_debug,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qsuppress_warning_message_header_qm = 
	    STATIC_SYMBOL("SUPPRESS-WARNING-MESSAGE-HEADER\?",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qsuppress_warning_message_header_qm,
	    Suppress_warning_message_header_qm);
    record_system_variable(Qsuppress_warning_message_header_qm,Qab_debug,
	    Nil,Qnil,Qnil,Qnil,Qnil);
    Qreset_suppress_header_variable = 
	    STATIC_SYMBOL("RESET-SUPPRESS-HEADER-VARIABLE",AB_package);
    def_bombout_clean_up_function(Qreset_suppress_header_variable);
    SET_SYMBOL_FUNCTION(Qreset_suppress_header_variable,
	    STATIC_FUNCTION(reset_suppress_header_variable,NIL,FALSE,0,0));
    string_constant_26 = STATIC_STRING("Error");
    string_constant_27 = STATIC_STRING("Error or incomplete KB");
    string_constant_28 = STATIC_STRING("General warning");
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    string_constant_29 = STATIC_STRING("~A  Break on entry.");
    string_constant_30 = STATIC_STRING("~NW Break on exit.");
    string_constant_31 = STATIC_STRING("~A  Break on exit.");
    string_constant_32 = STATIC_STRING("~NW");
    string_constant_33 = STATIC_STRING("~%");
    string_constant_34 = STATIC_STRING("   ");
    string_constant_35 = STATIC_STRING("~A Break on exit.");
    Qtracing_and_breakpoint_parameters = 
	    STATIC_SYMBOL("TRACING-AND-BREAKPOINT-PARAMETERS",AB_package);
    Qsubstitute_class_and_kb_flags = 
	    STATIC_SYMBOL("SUBSTITUTE-CLASS-AND-KB-FLAGS",AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qtracing_and_breakpoint_parameters,
	    CONS(Qdebugging_parameters,temp),Qsubstitute_class_and_kb_flags);
    Qdebugging_message_and_breakpoint_parameters = 
	    STATIC_SYMBOL("DEBUGGING-MESSAGE-AND-BREAKPOINT-PARAMETERS",
	    AB_package);
    temp = FIX((SI_Long)199L);
    mutate_global_property(Qdebugging_message_and_breakpoint_parameters,
	    CONS(Qdebugging_parameters,temp),Qsubstitute_class_and_kb_flags);
    Qfix_frame_with_substitute_class_for_debugging_parameters = 
	    STATIC_SYMBOL("FIX-FRAME-WITH-SUBSTITUTE-CLASS-FOR-DEBUGGING-PARAMETERS",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qfix_frame_with_substitute_class_for_debugging_parameters,
	    STATIC_FUNCTION(fix_frame_with_substitute_class_for_debugging_parameters,
	    NIL,FALSE,1,1));
    Qfix_frame_with_substitute_class = 
	    STATIC_SYMBOL("FIX-FRAME-WITH-SUBSTITUTE-CLASS",AB_package);
    temp_2 = 
	    SYMBOL_FUNCTION(Qfix_frame_with_substitute_class_for_debugging_parameters);
    set_get(Qdebugging_parameters,Qfix_frame_with_substitute_class,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfix_frame_with_substitute_class),
	    Qclasses_which_define);
    temp_2 = CONS(Qdebugging_parameters,temp);
    mutate_global_property(Qfix_frame_with_substitute_class,temp_2,
	    Qclasses_which_define);
    Qtracing_file_string = STATIC_SYMBOL("TRACING-FILE-STRING",AB_package);
    Qtracing_file_stream = STATIC_SYMBOL("TRACING-FILE-STREAM",AB_package);
    Qtrace_outputting_to_file_qm = 
	    STATIC_SYMBOL("TRACE-OUTPUTTING-TO-FILE\?",AB_package);
    string_constant_36 = STATIC_STRING("Couldn\'t open tracing file ~s:  ~a.");
    string_constant_37 = 
	    STATIC_STRING("~NF does not have a color pattern to change -- it is not polychrome.");
    string_constant_38 = 
	    STATIC_STRING("~NF does not have a single icon color to change -- it is polychrome.");
    string_constant_39 = 
	    STATIC_STRING("~a is not a valid color attribute for ~NF.");
    string_constant_40 = 
	    STATIC_STRING("~a is not a valid color region for ~NF.");
    string_constant_41 = 
	    STATIC_STRING("Attempt to change the ~a region of ~NF. ~\n    The class definition for ~a does not have a region named ~a.");
    string_constant_42 = 
	    STATIC_STRING("Attempt to change an unnamed color region in ~NF using its color name ~\n     (~a).  Unnamed color regions cannot be changed.");
    string_constant_43 = STATIC_STRING("~a ~a illegal color~a");
    string_constant_44 = STATIC_STRING("are");
    string_constant_45 = STATIC_STRING("is an");
    string_constant_46 = STATIC_STRING("s");
    string_constant_47 = STATIC_STRING("");
    array_constant_3 = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)57344L);
    array_constant_4 = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)29L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)39L,(SI_Long)57344L);
    string_constant_48 = STATIC_STRING("~A ");
    array_constant_5 = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_85,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)57344L);
    Qg2_performance_frequency = STATIC_SYMBOL("G2-PERFORMANCE-FREQUENCY",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_performance_frequency,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_performance_frequency,
	    STATIC_FUNCTION(g2_performance_frequency,NIL,FALSE,0,0));
    Qg2_emit_performance_counter = 
	    STATIC_SYMBOL("G2-EMIT-PERFORMANCE-COUNTER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_emit_performance_counter,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    SET_SYMBOL_FUNCTION(Qg2_emit_performance_counter,
	    STATIC_FUNCTION(g2_emit_performance_counter,NIL,FALSE,1,1));
    Qg2_report_performance_counter = 
	    STATIC_SYMBOL("G2-REPORT-PERFORMANCE-COUNTER",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_report_performance_counter,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_report_performance_counter,
	    STATIC_FUNCTION(g2_report_performance_counter,NIL,FALSE,0,0));
}
