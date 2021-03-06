/* parse.c
 * Input file:  parse.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "parse.h"


Object Current_edit_state = UNBOUND;

Object Current_edit_workspace = UNBOUND;

Object Keep_edit_workspace_hidden_no_matter_what_qm = UNBOUND;

Object Directory_of_names_kbprop = UNBOUND;

Object The_type_description_of_annotation = UNBOUND;

Object Chain_of_available_annotations = UNBOUND;

Object Annotation_count = UNBOUND;

/* ANNOTATION-STRUCTURE-MEMORY-USAGE */
Object annotation_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,0);
    temp = Annotation_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-ANNOTATION-COUNT */
Object outstanding_annotation_count()
{
    Object def_structure_annotation_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,1);
    gensymed_symbol = IFIX(Annotation_count);
    def_structure_annotation_variable = Chain_of_available_annotations;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_annotation_variable))
	goto end_loop;
    def_structure_annotation_variable = 
	    ISVREF(def_structure_annotation_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-ANNOTATION-1 */
Object reclaim_annotation_1(annotation)
    Object annotation;
{
    Object svref_new_value;

    x_note_fn_call(78,2);
    inline_note_reclaim_cons(annotation,Nil);
    svref_new_value = Chain_of_available_annotations;
    SVREF(annotation,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_annotations = annotation;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-ANNOTATION */
Object reclaim_structure_for_annotation(annotation)
    Object annotation;
{
    x_note_fn_call(78,3);
    return reclaim_annotation_1(annotation);
}

static Object Qg2_defstruct_structure_name_annotation_g2_struct;  /* g2-defstruct-structure-name::annotation-g2-struct */

/* MAKE-PERMANENT-ANNOTATION-STRUCTURE-INTERNAL */
Object make_permanent_annotation_structure_internal()
{
    Object def_structure_annotation_variable, annotation_count_new_value;
    Object defstruct_g2_annotation_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,4);
    def_structure_annotation_variable = Nil;
    annotation_count_new_value = FIXNUM_ADD1(Annotation_count);
    Annotation_count = annotation_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_annotation_variable = Nil;
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
	defstruct_g2_annotation_variable = the_array;
	SVREF(defstruct_g2_annotation_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_annotation_g2_struct;
	def_structure_annotation_variable = defstruct_g2_annotation_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_annotation_variable);
}

/* MAKE-ANNOTATION-1 */
Object make_annotation_1(begin_line,begin_char_pos)
    Object begin_line, begin_char_pos;
{
    Object def_structure_annotation_variable;

    x_note_fn_call(78,5);
    def_structure_annotation_variable = Chain_of_available_annotations;
    if (def_structure_annotation_variable) {
	Chain_of_available_annotations = 
		ISVREF(def_structure_annotation_variable,(SI_Long)0L);
	SVREF(def_structure_annotation_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_annotation_g2_struct;
    }
    else
	def_structure_annotation_variable = 
		make_permanent_annotation_structure_internal();
    inline_note_allocate_cons(def_structure_annotation_variable,Nil);
    SVREF(def_structure_annotation_variable,FIX((SI_Long)1L)) = begin_line;
    SVREF(def_structure_annotation_variable,FIX((SI_Long)2L)) = begin_char_pos;
    return VALUES_1(def_structure_annotation_variable);
}

/* CLONE-ANNOTATION */
Object clone_annotation(annotation)
    Object annotation;
{
    Object temp;

    x_note_fn_call(78,6);
    temp = make_annotation_1(ISVREF(annotation,(SI_Long)1L),
	    ISVREF(annotation,(SI_Long)2L));
    return VALUES_1(temp);
}

/* RECLAIM-ANNOTATION? */
Object reclaim_annotation_qm(annotation_qm)
    Object annotation_qm;
{
    x_note_fn_call(78,7);
    if (annotation_qm)
	reclaim_annotation_1(annotation_qm);
    return VALUES_1(Nil);
}

static Object Qreclaim_annotation_qm;  /* reclaim-annotation? */

/* MAKE-SEXP-ANNOTATION-HASH */
Object make_sexp_annotation_hash()
{
    Object temp;

    x_note_fn_call(78,8);
    temp = make_eq_hash_table(FIX((SI_Long)43L),Nil,
	    SYMBOL_FUNCTION(Qreclaim_annotation_qm));
    return VALUES_1(temp);
}

/* GET-SEXP-ANNOTATION-HASH */
Object get_sexp_annotation_hash(sexp,hash)
    Object sexp, hash;
{
    Object temp;

    x_note_fn_call(78,9);
    temp = eq_gethash(hash,sexp,Nil);
    return VALUES_1(temp);
}

/* SET-SEXP-ANNOTATION-HASH */
Object set_sexp_annotation_hash(sexp,hash,annotation)
    Object sexp, hash, annotation;
{
    Object temp;

    x_note_fn_call(78,10);
    temp = eq_puthash(hash,sexp,annotation);
    return VALUES_1(temp);
}

/* RECLAIM-SEXP-ANNOTATION-HASH? */
Object reclaim_sexp_annotation_hash_qm(hash_qm)
    Object hash_qm;
{
    x_note_fn_call(78,11);
    if (hash_qm)
	reclaim_eq_hash_table(hash_qm);
    return VALUES_1(Nil);
}

Object The_type_description_of_edit_state = UNBOUND;

Object Chain_of_available_edit_states = UNBOUND;

Object Edit_state_count = UNBOUND;

/* EDIT-STATE-STRUCTURE-MEMORY-USAGE */
Object edit_state_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,12);
    temp = Edit_state_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)103L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EDIT-STATE-COUNT */
Object outstanding_edit_state_count()
{
    Object def_structure_edit_state_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,13);
    gensymed_symbol = IFIX(Edit_state_count);
    def_structure_edit_state_variable = Chain_of_available_edit_states;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_edit_state_variable))
	goto end_loop;
    def_structure_edit_state_variable = 
	    ISVREF(def_structure_edit_state_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EDIT-STATE-1 */
Object reclaim_edit_state_1(edit_state)
    Object edit_state;
{
    Object old_structure_being_reclaimed, thing, svref_new_value;

    x_note_fn_call(78,14);
    inline_note_reclaim_cons(edit_state,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = edit_state;
    release_mouse_pointers(ISVREF(edit_state,(SI_Long)1L));
    SVREF(edit_state,FIX((SI_Long)1L)) = Nil;
    reclaim_frame_serial_number(ISVREF(edit_state,(SI_Long)2L));
    SVREF(edit_state,FIX((SI_Long)2L)) = Nil;
    reclaim_frame_serial_number(ISVREF(edit_state,(SI_Long)4L));
    SVREF(edit_state,FIX((SI_Long)4L)) = Nil;
    reclaim_edit_undo_or_redo_stack(ISVREF(edit_state,(SI_Long)34L));
    SVREF(edit_state,FIX((SI_Long)34L)) = Nil;
    reclaim_edit_undo_or_redo_stack(ISVREF(edit_state,(SI_Long)35L));
    SVREF(edit_state,FIX((SI_Long)35L)) = Nil;
    reclaim_chain_of_incomplete_phrases(ISVREF(edit_state,(SI_Long)36L));
    SVREF(edit_state,FIX((SI_Long)36L)) = Nil;
    reclaim_vectors_for_phrase_conses(ISVREF(edit_state,(SI_Long)37L));
    SVREF(edit_state,FIX((SI_Long)37L)) = Nil;
    reclaim_text_strings_in_phrases(ISVREF(edit_state,(SI_Long)39L));
    SVREF(edit_state,FIX((SI_Long)39L)) = Nil;
    reclaim_managed_floats_in_phrases(ISVREF(edit_state,(SI_Long)40L));
    SVREF(edit_state,FIX((SI_Long)40L)) = Nil;
    reclaim_managed_longs_in_phrases(ISVREF(edit_state,(SI_Long)41L));
    SVREF(edit_state,FIX((SI_Long)41L)) = Nil;
    reclaim_most_recent_reason_for_bad_parse_qm(ISVREF(edit_state,
	    (SI_Long)42L));
    SVREF(edit_state,FIX((SI_Long)42L)) = Nil;
    reclaim_gensym_list_if_list(ISVREF(edit_state,(SI_Long)43L));
    SVREF(edit_state,FIX((SI_Long)43L)) = Nil;
    reclaim_slot_value(ISVREF(edit_state,(SI_Long)47L));
    SVREF(edit_state,FIX((SI_Long)47L)) = Nil;
    reclaim_slot_value(ISVREF(edit_state,(SI_Long)49L));
    SVREF(edit_state,FIX((SI_Long)49L)) = Nil;
    reclaim_hfep_hanc_type_function(ISVREF(edit_state,(SI_Long)62L));
    SVREF(edit_state,FIX((SI_Long)62L)) = Nil;
    reclaim_hfep_hanc_type_function(ISVREF(edit_state,(SI_Long)63L));
    SVREF(edit_state,FIX((SI_Long)63L)) = Nil;
    reclaim_gensym_tree_function(ISVREF(edit_state,(SI_Long)74L));
    SVREF(edit_state,FIX((SI_Long)74L)) = Nil;
    reclaim_sexp_annotation_hash_qm(ISVREF(edit_state,(SI_Long)90L));
    SVREF(edit_state,FIX((SI_Long)90L)) = Nil;
    reclaim_pending_procedure_signature_workspaces(ISVREF(edit_state,
	    (SI_Long)91L));
    SVREF(edit_state,FIX((SI_Long)91L)) = Nil;
    reclaim_frame_serial_number(ISVREF(edit_state,(SI_Long)93L));
    SVREF(edit_state,FIX((SI_Long)93L)) = Nil;
    reclaim_gensym_tree_function(ISVREF(edit_state,(SI_Long)99L));
    SVREF(edit_state,FIX((SI_Long)99L)) = Nil;
    thing = ISVREF(edit_state,(SI_Long)100L);
    if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(thing) != (SI_Long)0L)
	reclaim_wide_string(thing);
    SVREF(edit_state,FIX((SI_Long)100L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_edit_states;
    SVREF(edit_state,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_edit_states = edit_state;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EDIT-STATE */
Object reclaim_structure_for_edit_state(edit_state)
    Object edit_state;
{
    x_note_fn_call(78,15);
    return reclaim_edit_state_1(edit_state);
}

static Object Qg2_defstruct_structure_name_edit_state_g2_struct;  /* g2-defstruct-structure-name::edit-state-g2-struct */

/* MAKE-PERMANENT-EDIT-STATE-STRUCTURE-INTERNAL */
Object make_permanent_edit_state_structure_internal()
{
    Object def_structure_edit_state_variable, edit_state_count_new_value;
    Object defstruct_g2_edit_state_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,16);
    def_structure_edit_state_variable = Nil;
    edit_state_count_new_value = FIXNUM_ADD1(Edit_state_count);
    Edit_state_count = edit_state_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_edit_state_variable = Nil;
	gensymed_symbol = (SI_Long)103L;
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
	defstruct_g2_edit_state_variable = the_array;
	SVREF(defstruct_g2_edit_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_edit_state_g2_struct;
	SVREF(defstruct_g2_edit_state_variable,FIX((SI_Long)1L)) = Nil;
	SVREF(defstruct_g2_edit_state_variable,FIX((SI_Long)2L)) = Nil;
	def_structure_edit_state_variable = defstruct_g2_edit_state_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_edit_state_variable);
}

/* MAKE-EDIT-STATE-1 */
Object make_edit_state_1()
{
    Object def_structure_edit_state_variable, svref_new_value;

    x_note_fn_call(78,17);
    def_structure_edit_state_variable = Chain_of_available_edit_states;
    if (def_structure_edit_state_variable) {
	Chain_of_available_edit_states = 
		ISVREF(def_structure_edit_state_variable,(SI_Long)0L);
	SVREF(def_structure_edit_state_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_edit_state_g2_struct;
    }
    else
	def_structure_edit_state_variable = 
		make_permanent_edit_state_structure_internal();
    inline_note_allocate_cons(def_structure_edit_state_variable,Nil);
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)1L)) = Nil;
    svref_new_value = copy_of_current_frame_serial_number_function();
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)2L)) = 
	    svref_new_value;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)27L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)29L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)30L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)31L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)32L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)33L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)34L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)35L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)36L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)37L)) = Nil;
    ISVREF(def_structure_edit_state_variable,(SI_Long)38L) = FIX((SI_Long)0L);
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)39L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)40L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)41L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)42L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)43L)) = Nil;
    ISVREF(def_structure_edit_state_variable,(SI_Long)44L) = FIX((SI_Long)0L);
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)45L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)46L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)47L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)49L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)50L)) = Nil;
    ISVREF(def_structure_edit_state_variable,(SI_Long)51L) = FIX((SI_Long)95L);
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)52L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)53L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)54L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)55L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)56L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)57L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)58L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)59L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)60L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)61L)) = Nil;
    svref_new_value = make_hfep_hanc_type_function();
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)62L)) = 
	    svref_new_value;
    svref_new_value = make_hfep_hanc_type_function();
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)63L)) = 
	    svref_new_value;
    ISVREF(def_structure_edit_state_variable,(SI_Long)64L) = FIX((SI_Long)0L);
    ISVREF(def_structure_edit_state_variable,(SI_Long)65L) = FIX((SI_Long)0L);
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)66L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)67L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)68L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)69L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)70L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)71L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)72L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)73L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)74L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)75L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)76L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)77L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)78L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)79L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)80L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)81L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)82L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)83L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)84L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)85L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)86L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)87L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)88L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)89L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)90L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)91L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)92L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)93L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)94L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)95L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)96L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)97L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)98L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)99L)) = Nil;
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)100L)) = Nil;
    ISVREF(def_structure_edit_state_variable,(SI_Long)101L) = FIX((SI_Long)0L);
    SVREF(def_structure_edit_state_variable,FIX((SI_Long)102L)) = Nil;
    return VALUES_1(def_structure_edit_state_variable);
}

/* RECLAIM-MOST-RECENT-REASON-FOR-BAD-PARSE? */
Object reclaim_most_recent_reason_for_bad_parse_qm(list_1)
    Object list_1;
{
    Object first_reason_qm;

    x_note_fn_call(78,18);
    first_reason_qm = CADDDR(list_1);
    if (first_reason_qm)
	reclaim_text_string(first_reason_qm);
    return reclaim_gensym_list_1(list_1);
}

/* NOTE-USE-OF-TEXT-STRING-IN-PHRASE */
Object note_use_of_text_string_in_phrase(text_string)
    Object text_string;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(78,19);
    svref_arg_1 = Current_edit_state;
    svref_new_value = gensym_cons_1(text_string,ISVREF(Current_edit_state,
	    (SI_Long)39L));
    SVREF(svref_arg_1,FIX((SI_Long)39L)) = svref_new_value;
    return VALUES_1(text_string);
}

/* RECLAIM-TEXT-STRINGS-IN-PHRASES */
Object reclaim_text_strings_in_phrases(text_strings_in_phrases)
    Object text_strings_in_phrases;
{
    Object text_string, ab_loop_list_;

    x_note_fn_call(78,20);
    text_string = Nil;
    ab_loop_list_ = text_strings_in_phrases;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    text_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_text_string(text_string);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(text_strings_in_phrases);
    return VALUES_1(Nil);
}

/* NOTE-USE-OF-MANAGED-FLOAT-IN-PHRASE */
Object note_use_of_managed_float_in_phrase(managed_float)
    Object managed_float;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(78,21);
    svref_arg_1 = Current_edit_state;
    svref_new_value = gensym_cons_1(managed_float,
	    ISVREF(Current_edit_state,(SI_Long)40L));
    SVREF(svref_arg_1,FIX((SI_Long)40L)) = svref_new_value;
    return VALUES_1(managed_float);
}

/* NOTE-USE-OF-MANAGED-LONG-IN-PHRASE */
Object note_use_of_managed_long_in_phrase(managed_long)
    Object managed_long;
{
    Object svref_arg_1, svref_new_value;

    x_note_fn_call(78,22);
    svref_arg_1 = Current_edit_state;
    svref_new_value = gensym_cons_1(managed_long,ISVREF(Current_edit_state,
	    (SI_Long)41L));
    SVREF(svref_arg_1,FIX((SI_Long)41L)) = svref_new_value;
    return VALUES_1(managed_long);
}

/* RECLAIM-MANAGED-FLOATS-IN-PHRASES */
Object reclaim_managed_floats_in_phrases(managed_floats_in_phrases)
    Object managed_floats_in_phrases;
{
    Object managed_float, ab_loop_list_;

    x_note_fn_call(78,23);
    managed_float = Nil;
    ab_loop_list_ = managed_floats_in_phrases;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    managed_float = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_managed_simple_float_array_of_length_1(managed_float);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(managed_floats_in_phrases);
    return VALUES_1(Nil);
}

/* RECLAIM-MANAGED-LONGS-IN-PHRASES */
Object reclaim_managed_longs_in_phrases(managed_longs_in_phrases)
    Object managed_longs_in_phrases;
{
    Object managed_long, ab_loop_list_;

    x_note_fn_call(78,24);
    managed_long = Nil;
    ab_loop_list_ = managed_longs_in_phrases;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    managed_long = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_managed_simple_long_array_of_length_1(managed_long);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(managed_longs_in_phrases);
    return VALUES_1(Nil);
}

Object Phrase_sequence_marker = UNBOUND;

Object Phrase_structure_marker = UNBOUND;

Object Phrase_item_denotation_marker = UNBOUND;

Object Phrase_item_marker = UNBOUND;

Object The_type_description_of_edit_box_change = UNBOUND;

Object Chain_of_available_edit_box_changes = UNBOUND;

Object Edit_box_change_count = UNBOUND;

/* EDIT-BOX-CHANGE-STRUCTURE-MEMORY-USAGE */
Object edit_box_change_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,25);
    temp = Edit_box_change_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EDIT-BOX-CHANGE-COUNT */
Object outstanding_edit_box_change_count()
{
    Object def_structure_edit_box_change_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,26);
    gensymed_symbol = IFIX(Edit_box_change_count);
    def_structure_edit_box_change_variable = 
	    Chain_of_available_edit_box_changes;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_edit_box_change_variable))
	goto end_loop;
    def_structure_edit_box_change_variable = 
	    ISVREF(def_structure_edit_box_change_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EDIT-BOX-CHANGE-1 */
Object reclaim_edit_box_change_1(edit_box_change)
    Object edit_box_change;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(78,27);
    inline_note_reclaim_cons(edit_box_change,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = edit_box_change;
    reclaim_slot_value(ISVREF(edit_box_change,(SI_Long)7L));
    SVREF(edit_box_change,FIX((SI_Long)7L)) = Nil;
    reclaim_gensym_tree_1(ISVREF(edit_box_change,(SI_Long)11L));
    SVREF(edit_box_change,FIX((SI_Long)11L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_edit_box_changes;
    SVREF(edit_box_change,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_edit_box_changes = edit_box_change;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EDIT-BOX-CHANGE */
Object reclaim_structure_for_edit_box_change(edit_box_change)
    Object edit_box_change;
{
    x_note_fn_call(78,28);
    return reclaim_edit_box_change_1(edit_box_change);
}

static Object Qg2_defstruct_structure_name_edit_box_change_g2_struct;  /* g2-defstruct-structure-name::edit-box-change-g2-struct */

/* MAKE-PERMANENT-EDIT-BOX-CHANGE-STRUCTURE-INTERNAL */
Object make_permanent_edit_box_change_structure_internal()
{
    Object def_structure_edit_box_change_variable;
    Object edit_box_change_count_new_value;
    Object defstruct_g2_edit_box_change_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,29);
    def_structure_edit_box_change_variable = Nil;
    edit_box_change_count_new_value = FIXNUM_ADD1(Edit_box_change_count);
    Edit_box_change_count = edit_box_change_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_edit_box_change_variable = Nil;
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
	defstruct_g2_edit_box_change_variable = the_array;
	SVREF(defstruct_g2_edit_box_change_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_edit_box_change_g2_struct;
	def_structure_edit_box_change_variable = 
		defstruct_g2_edit_box_change_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_edit_box_change_variable);
}

/* MAKE-EDIT-BOX-CHANGE-1 */
Object make_edit_box_change_1(special_type_of_edit_box_change_qm,
	    line_index_of_old_and_new_text_segment,
	    line_index_where_difference_in_texts_starts,
	    character_index_where_difference_in_texts_starts,
	    line_index_past_old_text_segment,
	    line_index_past_new_text_segment,old_text_segment,
	    old_width_for_text,old_cursor_line_index,
	    old_cursor_character_index,
	    old_position_for_kfep_conversion_text_region_qm)
    Object special_type_of_edit_box_change_qm;
    Object line_index_of_old_and_new_text_segment;
    Object line_index_where_difference_in_texts_starts;
    Object character_index_where_difference_in_texts_starts;
    Object line_index_past_old_text_segment, line_index_past_new_text_segment;
    Object old_text_segment, old_width_for_text, old_cursor_line_index;
    Object old_cursor_character_index;
    Object old_position_for_kfep_conversion_text_region_qm;
{
    Object def_structure_edit_box_change_variable;

    x_note_fn_call(78,30);
    def_structure_edit_box_change_variable = 
	    Chain_of_available_edit_box_changes;
    if (def_structure_edit_box_change_variable) {
	Chain_of_available_edit_box_changes = 
		ISVREF(def_structure_edit_box_change_variable,(SI_Long)0L);
	SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_edit_box_change_g2_struct;
    }
    else
	def_structure_edit_box_change_variable = 
		make_permanent_edit_box_change_structure_internal();
    inline_note_allocate_cons(def_structure_edit_box_change_variable,Nil);
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)1L)) = 
	    special_type_of_edit_box_change_qm;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)2L)) = 
	    line_index_of_old_and_new_text_segment;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)3L)) = 
	    line_index_where_difference_in_texts_starts;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)4L)) = 
	    character_index_where_difference_in_texts_starts;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)5L)) = 
	    line_index_past_old_text_segment;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)6L)) = 
	    line_index_past_new_text_segment;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)7L)) = 
	    old_text_segment;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)8L)) = 
	    old_width_for_text;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)9L)) = 
	    old_cursor_line_index;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)10L)) = 
	    old_cursor_character_index;
    SVREF(def_structure_edit_box_change_variable,FIX((SI_Long)11L)) = 
	    old_position_for_kfep_conversion_text_region_qm;
    return VALUES_1(def_structure_edit_box_change_variable);
}

/* RECLAIM-EDIT-UNDO-OR-REDO-STACK */
Object reclaim_edit_undo_or_redo_stack(edit_undo_or_redo_stack)
    Object edit_undo_or_redo_stack;
{
    Object edit_box_change, ab_loop_list_;

    x_note_fn_call(78,31);
    edit_box_change = Nil;
    ab_loop_list_ = edit_undo_or_redo_stack;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    edit_box_change = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_edit_box_change_1(edit_box_change);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(edit_undo_or_redo_stack);
}

/* GET-CURRENT-SEXP-ANNOTATION-HASH */
Object get_current_sexp_annotation_hash()
{
    Object temp, svref_arg_1;

    x_note_fn_call(78,32);
    temp = ISVREF(Current_edit_state,(SI_Long)90L);
    if (temp);
    else {
	svref_arg_1 = Current_edit_state;
	temp = make_sexp_annotation_hash();
	SVREF(svref_arg_1,FIX((SI_Long)90L)) = temp;
    }
    return VALUES_1(temp);
}

/* GET-CURRENT-ANNOTATION-CONTEXT */
Object get_current_annotation_context(sexp)
    Object sexp;
{
    Object temp;

    x_note_fn_call(78,33);
    temp = get_sexp_annotation_hash(sexp,get_current_sexp_annotation_hash());
    return VALUES_1(temp);
}

/* SET-CURRENT-ANNOTATION-CONTEXT */
Object set_current_annotation_context(sexp,annotation)
    Object sexp, annotation;
{
    Object temp;

    x_note_fn_call(78,34);
    temp = set_sexp_annotation_hash(sexp,
	    get_current_sexp_annotation_hash(),annotation);
    return VALUES_1(temp);
}

/* ADD-ANOTHER-VECTOR-FOR-PHRASE-CONSES */
Object add_another_vector_for_phrase_conses()
{
    Object svref_arg_1, temp, svref_new_value;

    x_note_fn_call(78,35);
    svref_arg_1 = Current_edit_state;
    temp = allocate_managed_simple_vector(FIX((SI_Long)64L));
    svref_new_value = gensym_cons_1(temp,ISVREF(Current_edit_state,
	    (SI_Long)37L));
    SVREF(svref_arg_1,FIX((SI_Long)37L)) = svref_new_value;
    svref_arg_1 = Current_edit_state;
    return VALUES_1(ISVREF(svref_arg_1,(SI_Long)38L) = FIX((SI_Long)63L));
}

static Object Qab_gensym;          /* gensym */

/* PHRASE-CONS */
Object phrase_cons(x,y)
    Object x, y;
{
    Object svref_arg_1, svref_new_value, temp, new_cons, gensymed_symbol_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(78,36);
    svref_arg_1 = Current_edit_state;
    svref_new_value = FIXNUM_SUB1(ISVREF(svref_arg_1,(SI_Long)38L));
    gensymed_symbol = IFIX(SVREF(svref_arg_1,FIX((SI_Long)38L)) = 
	    svref_new_value);
    if (gensymed_symbol < (SI_Long)0L)
	gensymed_symbol = IFIX(add_another_vector_for_phrase_conses());
    temp = ISVREF(Current_edit_state,(SI_Long)37L);
    svref_arg_1 = CAR(temp);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol_1) = x;
    M_CDR(gensymed_symbol_1) = y;
    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
    return VALUES_1(ISVREF(svref_arg_1,gensymed_symbol) = gensymed_symbol_1);
}

/* PHRASE-LIST-2 */
Object phrase_list_2(first_1,second_1)
    Object first_1, second_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,37);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)2L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    return VALUES_1(gensymed_symbol);
}

/* PHRASE-LIST-3 */
Object phrase_list_3(first_1,second_1,third_1)
    Object first_1, second_1, third_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,38);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)3L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    return VALUES_1(gensymed_symbol);
}

/* PHRASE-LIST-4 */
Object phrase_list_4(first_1,second_1,third_1,fourth_1)
    Object first_1, second_1, third_1, fourth_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,39);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)4L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = first_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = second_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = third_1;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = fourth_1;
    return VALUES_1(gensymed_symbol);
}

/* MAKE-PHRASE-LIST */
Object make_phrase_list(count_1)
    Object count_1;
{
    Object gensymed_symbol, gensymed_symbol_1, temp, phrase_list;
    Object phrase_cons_1, svref_arg_1, svref_new_value;
    SI_Long ab_loop_repeat_, gensymed_symbol_2;

    x_note_fn_call(78,40);
    gensymed_symbol = FIXNUM_SUB1(count_1);
    if (IFIX(gensymed_symbol) >= (SI_Long)0L) {
	gensymed_symbol_1 = Nil;
      next_loop:
	ab_loop_repeat_ = IFIX(gensymed_symbol);
	gensymed_symbol_1 = Available_gensym_conses;
      next_loop_1:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop:
	goto end_1;
	gensymed_symbol_1 = Qnil;
      end_1:;
	if (gensymed_symbol_1)
	    goto end_loop_1;
	replenish_gensym_list_pool(gensymed_symbol);
	goto next_loop;
      end_loop_1:
	if ( !((SI_Long)0L == inline_debugging_consing())) {
	    gensymed_symbol = Available_gensym_conses;
	  next_loop_2:
	    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	    if (EQ(gensymed_symbol,gensymed_symbol_1))
		goto end_loop_2;
	    gensymed_symbol = CDR(gensymed_symbol);
	    goto next_loop_2;
	  end_loop_2:;
	}
	temp = Available_gensym_conses;
	Available_gensym_conses = CDR(gensymed_symbol_1);
	M_CDR(gensymed_symbol_1) = Nil;
	phrase_list = temp;
	goto end_2;
	phrase_list = Qnil;
      end_2:;
    }
    else
	phrase_list = Nil;
    phrase_cons_1 = phrase_list;
  next_loop_3:
    if ( !TRUEP(phrase_cons_1))
	goto end_loop_3;
    svref_arg_1 = Current_edit_state;
    svref_new_value = FIXNUM_SUB1(ISVREF(svref_arg_1,(SI_Long)38L));
    gensymed_symbol_2 = IFIX(SVREF(svref_arg_1,FIX((SI_Long)38L)) = 
	    svref_new_value);
    if (gensymed_symbol_2 < (SI_Long)0L)
	gensymed_symbol_2 = IFIX(add_another_vector_for_phrase_conses());
    temp = ISVREF(Current_edit_state,(SI_Long)37L);
    svref_arg_1 = CAR(temp);
    ISVREF(svref_arg_1,gensymed_symbol_2) = phrase_cons_1;
    phrase_cons_1 = M_CDR(phrase_cons_1);
    goto next_loop_3;
  end_loop_3:
    return VALUES_1(phrase_list);
    return VALUES_1(Qnil);
}

/* PHRASE-CONS-WITH-ARGS-REVERSED */
Object phrase_cons_with_args_reversed(cdr_1,car_1)
    Object cdr_1, car_1;
{
    x_note_fn_call(78,41);
    return phrase_cons(car_1,cdr_1);
}

/* COPY-LIST-USING-PHRASE-CONSES */
Object copy_list_using_phrase_conses(list_qm)
    Object list_qm;
{
    Object new_list, last_new_cons, current_copy_position, cdr_new_value;

    x_note_fn_call(78,42);
    if (ATOM(list_qm))
	return VALUES_1(list_qm);
    else {
	new_list = phrase_cons(CAR(list_qm),CDR(list_qm));
	last_new_cons = new_list;
	current_copy_position = CDR(list_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	cdr_new_value = phrase_cons(CAR(current_copy_position),
		CDR(current_copy_position));
	M_CDR(last_new_cons) = cdr_new_value;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	return VALUES_1(new_list);
	return VALUES_1(Qnil);
    }
}

/* RECLAIM-VECTORS-FOR-PHRASE-CONSES */
Object reclaim_vectors_for_phrase_conses(vectors_for_phrase_conses)
    Object vectors_for_phrase_conses;
{
    Object managed_simple_vector, ab_loop_list_, start_index;
    Object ab_loop_iter_flag_, gensym_cons, cdr_new_value;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(78,43);
    managed_simple_vector = Nil;
    ab_loop_list_ = vectors_for_phrase_conses;
    start_index = ISVREF(Structure_being_reclaimed,(SI_Long)38L);
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    managed_simple_vector = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	start_index = FIX((SI_Long)0L);
    i = IFIX(start_index);
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_simple_vector));
  next_loop_1:
    if (i >= ab_loop_bind_)
	goto end_loop_1;
    gensym_cons = ISVREF(managed_simple_vector,i);
    inline_note_reclaim_cons(gensym_cons,Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(gensym_cons) = cdr_new_value;
    Available_gensym_conses = gensym_cons;
    i = i + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    reclaim_managed_simple_vector(managed_simple_vector);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(vectors_for_phrase_conses);
}

/* COPY-TREE-USING-PHRASE-CONSES */
Object copy_tree_using_phrase_conses(x)
    Object x;
{
    Object temp;

    x_note_fn_call(78,44);
    if (ATOM(x))
	return VALUES_1(x);
    else {
	temp = copy_tree_using_phrase_conses(CAR(x));
	return phrase_cons(temp,copy_tree_using_phrase_conses(CDR(x)));
    }
}

Object Phrase_copying_needs_annotation_rehashing = UNBOUND;

/* COPY-FOR-PHRASE */
Object copy_for_phrase(value_for_phrase)
    Object value_for_phrase;
{
    Object temp, amf_available_array_cons_qm, amf_array, temp_1;
    Object svref_new_value, amf_result, incff_1_arg, new_float;
    Object new_phrase_list, annotation_qm;
    double aref_new_value;

    x_note_fn_call(78,45);
    if (text_string_p(value_for_phrase))
	temp = 
		note_use_of_text_string_in_phrase(copy_text_string(value_for_phrase));
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value_for_phrase) != (SI_Long)0L 
	    && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value_for_phrase)) == 
	    (SI_Long)1L)
	temp = 
		note_use_of_managed_float_in_phrase(copy_managed_float(value_for_phrase));
    else if (CONSP(value_for_phrase) && EQ(M_CDR(value_for_phrase),
	    Phrase_sequence_marker)) {
	temp = copy_for_phrase(CAR(value_for_phrase));
	temp = phrase_cons(temp,Phrase_sequence_marker);
    }
    else if (CONSP(value_for_phrase) && EQ(M_CDR(value_for_phrase),
	    Phrase_structure_marker)) {
	temp = copy_for_phrase(CAR(value_for_phrase));
	temp = phrase_cons(temp,Phrase_structure_marker);
    }
    else if (CONSP(value_for_phrase) && EQ(M_CDR(value_for_phrase),
	    Phrase_item_denotation_marker)) {
	temp = copy_for_phrase(CAR(value_for_phrase));
	temp = phrase_cons(temp,Phrase_item_denotation_marker);
    }
    else if (CONSP(value_for_phrase) && EQ(M_CDR(value_for_phrase),
	    Phrase_item_marker)) {
	temp = copy_for_phrase(CAR(value_for_phrase));
	temp = phrase_cons(temp,Phrase_item_marker);
    }
    else if (FLOATP(value_for_phrase)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp_1 = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp_1;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp_1 = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp_1;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp_1 = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp_1;
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value_for_phrase);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = note_use_of_managed_float_in_phrase(new_float);
    }
    else if (ATOM(value_for_phrase))
	temp = value_for_phrase;
    else {
	temp = copy_for_phrase(CAR(value_for_phrase));
	new_phrase_list = phrase_cons(temp,
		copy_for_phrase(CDR(value_for_phrase)));
	if (Phrase_copying_needs_annotation_rehashing) {
	    annotation_qm = get_current_annotation_context(value_for_phrase);
	    if (annotation_qm)
		set_current_annotation_context(new_phrase_list,
			clone_annotation(annotation_qm));
	}
	temp = new_phrase_list;
    }
    return VALUES_1(temp);
}

/* PHRASE-NUMBER-P */
Object phrase_number_p(phrase_or_token)
    Object phrase_or_token;
{
    Object temp;

    x_note_fn_call(78,46);
    temp = NUMBERP(phrase_or_token) ? T : Nil;
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_or_token) != 
		(SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_or_token)) == 
		(SI_Long)1L ? T : Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (INLINE_LONG_VECTOR_P(phrase_or_token) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_or_token)) 
		== (SI_Long)1L ? T : Nil);
    else
	return VALUES_1(Nil);
}

/* ATOMIC-PHRASE-P */
Object atomic_phrase_p(x)
    Object x;
{
    Object temp;

    x_note_fn_call(78,47);
    temp = ATOM(x) ? T : Nil;
    if (temp);
    else
	temp = INLINE_DOUBLE_FLOAT_VECTOR_P(x) != (SI_Long)0L ? 
		(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L ? T : 
		Nil) : Qnil;
    if (temp)
	return VALUES_1(temp);
    else if (INLINE_LONG_VECTOR_P(x) != (SI_Long)0L)
	return VALUES_1(IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) == (SI_Long)1L ?
		 T : Nil);
    else
	return VALUES_1(Nil);
}

/* SET-NTH-ELEMENT-OF-VARIABLE-LENGTH-GRAMMAR-LIST */
Object set_nth_element_of_variable_length_grammar_list varargs_1(int, n)
{
    Object list_1, n_1, value;
    Object extension_element, size, temp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp_1, index_qm, tail;
    SI_Long ab_loop_repeat_;
    Declare_varargs_nonrelocating;

    x_note_fn_call(78,48);
    INIT_ARGS_nonrelocating();
    list_1 = REQUIRED_ARG_nonrelocating();
    n_1 = REQUIRED_ARG_nonrelocating();
    value = REQUIRED_ARG_nonrelocating();
    extension_element = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    size = length(list_1);
    if ( !FIXNUM_LT(n_1,size)) {
	temp = list_1;
	ab_loop_repeat_ = IFIX(FIXNUM_MINUS(FIXNUM_ADD1(n_1),size));
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	ab_loopvar__2 = gensym_cons_1(extension_element,Nil);
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
	list_1 = nconc2(temp,temp_1);
    }
    M_NTH(n_1,list_1) = value;
    index_qm = position(6,extension_element,list_1,Kfrom_end,T,Ktest_not,
	    SYMBOL_FUNCTION(Qeql));
    if ( !TRUEP(index_qm)) {
	reclaim_gensym_list_1(list_1);
	return VALUES_1(Nil);
    }
    else {
	tail = nthcdr(index_qm,list_1);
	reclaim_gensym_list_1(CDR(tail));
	M_CDR(tail) = Nil;
	return VALUES_1(list_1);
    }
}

Object Bad_phrase = UNBOUND;

/* TRANSFORM-CONSTITUENT */
Object transform_constituent(constituent,transformation_list)
    Object constituent, transformation_list;
{
    Object temp;

    x_note_fn_call(78,49);
    if ( !EQ(CAR(transformation_list),FIX((SI_Long)1L)))
	constituent = 
		transform_constituent_per_template(CAR(transformation_list),
		constituent);
    temp = CDR(transformation_list) ? 
	    perform_transformation_operations(constituent,
	    CDR(transformation_list)) : constituent;
    return VALUES_1(temp);
}

Object Current_transform_constituent_array = UNBOUND;

Object Current_transform_constituent_count = UNBOUND;

/* ENSURE-TRANSFORM-CONSTITUENT-ARRAY */
Object ensure_transform_constituent_array(length_1)
    Object length_1;
{
    Object temp;

    x_note_fn_call(78,50);
    Current_transform_constituent_count = length_1;
    if (Current_transform_constituent_array) {
	if ( 
		!FIXNUM_GE(SIMPLE_ARRAY_ANY_1_LENGTH(Current_transform_constituent_array),
		length_1)) {
	    reclaim_managed_simple_vector(Current_transform_constituent_array);
	    Current_transform_constituent_array = 
		    allocate_managed_simple_vector(length_1);
	    temp = Current_transform_constituent_array;
	}
	else
	    temp = Nil;
    }
    else {
	Current_transform_constituent_array = 
		allocate_managed_simple_vector(FIX((SI_Long)1024L));
	temp = Current_transform_constituent_array;
    }
    return VALUES_1(temp);
}

/* TRANSFORM-CONSTITUENT-PER-TEMPLATE */
Object transform_constituent_per_template(transformation_template,constituent)
    Object transformation_template, constituent;
{
    Object svref_arg_1, temp;

    x_note_fn_call(78,51);
    ensure_transform_constituent_array(FIX((SI_Long)1L));
    svref_arg_1 = Current_transform_constituent_array;
    SVREF(svref_arg_1,FIX((SI_Long)0L)) = constituent;
    temp = transform_by_template(transformation_template);
    return VALUES_1(temp);
}

/* MAKE-CONSTITUENT-PER-TEMPLATE */
Object make_constituent_per_template(transformation_template,
	    stack_of_all_but_last_constituent,last_constituent,
	    number_of_constituents_minus_one)
    Object transformation_template, stack_of_all_but_last_constituent;
    Object last_constituent, number_of_constituents_minus_one;
{
    Object svref_arg_1, constituent, ab_loop_list_, ab_loop_iter_flag_, temp;
    SI_Long i;

    x_note_fn_call(78,52);
    ensure_transform_constituent_array(FIXNUM_ADD1(number_of_constituents_minus_one));
    svref_arg_1 = Current_transform_constituent_array;
    SVREF(svref_arg_1,number_of_constituents_minus_one) = last_constituent;
    constituent = Nil;
    ab_loop_list_ = stack_of_all_but_last_constituent;
    i = IFIX(FIXNUM_SUB1(number_of_constituents_minus_one));
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    constituent = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	i = i - (SI_Long)1L;
    if (i < (SI_Long)0L)
	goto end_loop;
    svref_arg_1 = Current_transform_constituent_array;
    ISVREF(svref_arg_1,i) = constituent;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    temp = transform_by_template(transformation_template);
    return VALUES_1(temp);
}

static Object Qwhole;              /* whole */

/* TRANSFORM-BY-TEMPLATE */
Object transform_by_template(template_1)
    Object template_1;
{
    Object temp;

    x_note_fn_call(78,53);
    temp = CONSP(template_1) ? transform_by_template_rec(template_1,Nil,
	    Qwhole) : FIXNUMP(template_1) ? (FIXNUM_LE(template_1,
	    Current_transform_constituent_count) ? 
	    ISVREF(Current_transform_constituent_array,
	    IFIX(FIXNUM_SUB1(template_1))) : Nil) : template_1;
    return VALUES_1(temp);
}

static Object Qat;                 /* @ */

/* TRANSFORM-BY-TEMPLATE-REC */
Object transform_by_template_rec(template_1,parent_cons,mode)
    Object template_1, parent_cons, mode;
{
    Object head, gensymed_symbol, cdr_1, template_2, copy, transformed_thing;
    Object cons_1, temp_1;
    char temp;

    x_note_fn_call(78,54);
    if (CONSP(template_1)) {
	head = M_CAR(template_1);
	gensymed_symbol = head;
	if (CONSP(gensymed_symbol) && EQ(M_CAR(gensymed_symbol),Qat)) {
	    cdr_1 = M_CDR(gensymed_symbol);
	    temp = CONSP(cdr_1) && FIXNUMP(M_CAR(cdr_1)) ?  
		    !TRUEP(M_CDR(cdr_1)) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    template_2 = M_CAR(M_CDR(head));
	    copy = copy_for_phrase(FIXNUMP(template_2) ? 
		    (FIXNUM_LE(template_2,
		    Current_transform_constituent_count) ? 
		    ISVREF(Current_transform_constituent_array,
		    IFIX(FIXNUM_SUB1(template_2))) : Nil) : template_2);
	    if (ATOM(copy))
		error((SI_Long)2L,"spliced transform must be a list: ~s",copy);
	    transform_by_template_rec(CDR(template_1),last(copy,_),Qcdr);
	    transformed_thing = copy;
	}
	else {
	    cons_1 = phrase_cons(Nil,Nil);
	    transform_by_template_rec(CAR(template_1),cons_1,Qcar);
	    transform_by_template_rec(CDR(template_1),cons_1,Qcdr);
	    transformed_thing = cons_1;
	}
    }
    else
	transformed_thing = FIXNUMP(template_1) ? (FIXNUM_LE(template_1,
		Current_transform_constituent_count) ? 
		ISVREF(Current_transform_constituent_array,
		IFIX(FIXNUM_SUB1(template_1))) : Nil) : template_1;
    if (EQ(mode,Qcar)) {
	M_CAR(parent_cons) = transformed_thing;
	temp_1 = Nil;
    }
    else if (EQ(mode,Qcdr)) {
	M_CDR(parent_cons) = transformed_thing;
	temp_1 = Nil;
    }
    else if (EQ(mode,Qwhole))
	temp_1 = transformed_thing;
    else
	temp_1 = error((SI_Long)2L,
		"The value of MODE (~s), is not one of (CAR CDR WHOLE).",mode);
    return VALUES_1(temp_1);
}

/* PERFORM-TRANSFORMATION-OPERATIONS */
Object perform_transformation_operations(constituent,transformation_operations)
    Object constituent, transformation_operations;
{
    Object constituent_or_bad_phrase, reason_for_bad_phrase;
    Object transformed_constituent, transformation_operation, ab_loop_list_;
    Object temp, svref_new_value, svref_arg_1;
    Object result;

    x_note_fn_call(78,55);
    constituent_or_bad_phrase = Nil;
    reason_for_bad_phrase = Nil;
    transformed_constituent = constituent;
    transformation_operation = Nil;
    ab_loop_list_ = transformation_operations;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    transformation_operation = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (ATOM(transformation_operation)) {
	temp = SYMBOL_FUNCTION(transformation_operation);
	result = FUNCALL_1(temp,transformed_constituent);
    }
    else {
	temp = CAR(transformation_operation);
	result = APPLY_2(temp,transformed_constituent,
		CDR(transformation_operation));
    }
    MVS_2(result,constituent_or_bad_phrase,reason_for_bad_phrase);
    if (EQ(constituent_or_bad_phrase,Bad_phrase)) {
	svref_new_value = ISVREF(Current_edit_state,(SI_Long)42L);
	if (svref_new_value);
	else {
	    svref_arg_1 = Current_edit_state;
	    svref_new_value = gensym_list_4(Nil,Nil,Nil,Nil);
	    SVREF(svref_arg_1,FIX((SI_Long)42L)) = svref_new_value;
	}
	M_CAR(svref_new_value) = reason_for_bad_phrase;
	temp = Bad_phrase;
	goto end_1;
    }
    transformed_constituent = constituent_or_bad_phrase;
    goto next_loop;
  end_loop:
    temp = transformed_constituent;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Grammar_transform_can_return_bad_phrase_p_prop = UNBOUND;

static Object Qgrammar_transform_can_return_bad_phrase_p;  /* grammar-transform-can-return-bad-phrase-p */

/* SET-GRAMMAR-TRANSFORM-CAN-RETURN-BAD-PHRASE-P */
Object set_grammar_transform_can_return_bad_phrase_p(transform)
    Object transform;
{
    x_note_fn_call(78,56);
    mutate_global_property(transform,T,
	    Qgrammar_transform_can_return_bad_phrase_p);
    return VALUES_1(Nil);
}

/* SIMPLIFY-ASSOCIATIVE-OPERATION */
Object simplify_associative_operation(associative_operation)
    Object associative_operation;
{
    Object operator_1, first_arg, second_arg, temp;

    x_note_fn_call(78,57);
    operator_1 = CAR(associative_operation);
    first_arg = SECOND(associative_operation);
    second_arg = THIRD(associative_operation);
    if (CONSP(first_arg) && EQ(CAR(first_arg),operator_1)) {
	temp = copy_list_using_phrase_conses(CDR(first_arg));
	return phrase_cons(operator_1,nconc2(temp,
		CDDR(associative_operation)));
    }
    else if (CONSP(second_arg) && EQ(CAR(second_arg),operator_1))
	return phrase_cons(operator_1,
		phrase_cons(SECOND(associative_operation),CDR(second_arg)));
    else
	return VALUES_1(associative_operation);
}

/* SIMPLIFY-LAST-OF-NARY-ASSOCIATIVE-OPERATOR */
Object simplify_last_of_nary_associative_operator(form)
    Object form;
{
    Object temp, last_arg, temp_1, cons_1, result_1, ab_loopvar_;
    Object ab_loopvar__1, temp_2, elt_1, ab_loop_list_, ab_loopvar__2;

    x_note_fn_call(78,58);
    temp = last(form,_);
    last_arg = CAR(temp);
    if (CONSP(last_arg) && EQ(CAR(last_arg),CAR(form))) {
	temp_1 = CAR(form);
	cons_1 = CDR(form);
	result_1 = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(cons_1))
	    goto end_loop;
	if ( !TRUEP(CDR(cons_1)))
	    goto end_loop;
	ab_loopvar__1 = phrase_cons(CAR(cons_1),Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    result_1 = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	cons_1 = M_CDR(cons_1);
	goto next_loop;
      end_loop:
	temp_2 = result_1;
	elt_1 = Nil;
	ab_loop_list_ = CDR(last_arg);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = phrase_cons(elt_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	temp = nconc2(temp_2,temp);
	goto end_2;
	temp = Qnil;
      end_2:;
	return phrase_cons(temp_1,temp);
    }
    else
	return VALUES_1(form);
}

/* CHECK-RANGE-OF-ELEMENT */
Object check_range_of_element(list_1,element_index,minimum_qm,maximum_qm)
    Object list_1, element_index, minimum_qm, maximum_qm;
{
    Object phrase_number, element_value, temp;
    char temp_1;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(78,59);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	phrase_number = nth(FIXNUM_SUB1(element_index),list_1);
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == (SI_Long)1L)
	    element_value = 
		    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == (SI_Long)1L)
	    element_value = aref1(phrase_number,FIX((SI_Long)0L));
	else
	    element_value = phrase_number;
	if (minimum_qm) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(minimum_qm) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(minimum_qm)) == (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(minimum_qm,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(minimum_qm) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(minimum_qm)) == (SI_Long)1L)
		temp = aref1(minimum_qm,FIX((SI_Long)0L));
	    else
		temp = minimum_qm;
	    temp_1 = NUM_LT(element_value,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1);
	else if (maximum_qm) {
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(maximum_qm) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maximum_qm)) == (SI_Long)1L)
		temp = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(maximum_qm,
			(SI_Long)0L));
	    else if (INLINE_LONG_VECTOR_P(maximum_qm) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(maximum_qm)) == (SI_Long)1L)
		temp = aref1(maximum_qm,FIX((SI_Long)0L));
	    else
		temp = maximum_qm;
	    temp_1 = NUM_GT(element_value,temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    result = VALUES_1(Bad_phrase);
	else
	    result = VALUES_1(list_1);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

Object Reserved_word_p_prop = UNBOUND;

static Object Qreserved_word_p;    /* reserved-word-p */

/* RESERVE-WORDS */
Object reserve_words(symbols)
    Object symbols;
{
    Object symbol, ab_loop_list_;

    x_note_fn_call(78,60);
    symbol = Nil;
    ab_loop_list_ = symbols;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    mutate_global_property(symbol,T,Qreserved_word_p);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Last_assigned_grammar_number = UNBOUND;

Object The_type_description_of_gensym_grammar = UNBOUND;

Object Chain_of_available_gensym_grammars = UNBOUND;

Object Gensym_grammar_count = UNBOUND;

/* GENSYM-GRAMMAR-STRUCTURE-MEMORY-USAGE */
Object gensym_grammar_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,61);
    temp = Gensym_grammar_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)12L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-GENSYM-GRAMMAR-COUNT */
Object outstanding_gensym_grammar_count()
{
    Object def_structure_gensym_grammar_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,62);
    gensymed_symbol = IFIX(Gensym_grammar_count);
    def_structure_gensym_grammar_variable = Chain_of_available_gensym_grammars;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_gensym_grammar_variable))
	goto end_loop;
    def_structure_gensym_grammar_variable = 
	    ISVREF(def_structure_gensym_grammar_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-GENSYM-GRAMMAR-1 */
Object reclaim_gensym_grammar_1(gensym_grammar)
    Object gensym_grammar;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(78,63);
    inline_note_reclaim_cons(gensym_grammar,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = gensym_grammar;
    reclaim_gensym_tree_1(ISVREF(gensym_grammar,(SI_Long)5L));
    SVREF(gensym_grammar,FIX((SI_Long)5L)) = Nil;
    reclaim_tokens_with_specific_categories(ISVREF(gensym_grammar,
	    (SI_Long)6L));
    SVREF(gensym_grammar,FIX((SI_Long)6L)) = Nil;
    reclaim_category_symbols(ISVREF(gensym_grammar,(SI_Long)7L));
    SVREF(gensym_grammar,FIX((SI_Long)7L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_gensym_grammars;
    SVREF(gensym_grammar,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_gensym_grammars = gensym_grammar;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-GENSYM-GRAMMAR */
Object reclaim_structure_for_gensym_grammar(gensym_grammar)
    Object gensym_grammar;
{
    x_note_fn_call(78,64);
    return reclaim_gensym_grammar_1(gensym_grammar);
}

static Object Qg2_defstruct_structure_name_gensym_grammar_g2_struct;  /* g2-defstruct-structure-name::gensym-grammar-g2-struct */

/* MAKE-PERMANENT-GENSYM-GRAMMAR-STRUCTURE-INTERNAL */
Object make_permanent_gensym_grammar_structure_internal()
{
    Object def_structure_gensym_grammar_variable;
    Object gensym_grammar_count_new_value;
    Object defstruct_g2_gensym_grammar_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,65);
    def_structure_gensym_grammar_variable = Nil;
    gensym_grammar_count_new_value = FIXNUM_ADD1(Gensym_grammar_count);
    Gensym_grammar_count = gensym_grammar_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_gensym_grammar_variable = Nil;
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
	defstruct_g2_gensym_grammar_variable = the_array;
	SVREF(defstruct_g2_gensym_grammar_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_grammar_g2_struct;
	def_structure_gensym_grammar_variable = 
		defstruct_g2_gensym_grammar_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_gensym_grammar_variable);
}

/* MAKE-GENSYM-GRAMMAR-INTERNAL-1 */
Object make_gensym_grammar_internal_1(grammar_name)
    Object grammar_name;
{
    Object def_structure_gensym_grammar_variable, temp;

    x_note_fn_call(78,66);
    def_structure_gensym_grammar_variable = Chain_of_available_gensym_grammars;
    if (def_structure_gensym_grammar_variable) {
	Chain_of_available_gensym_grammars = 
		ISVREF(def_structure_gensym_grammar_variable,(SI_Long)0L);
	SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_gensym_grammar_g2_struct;
    }
    else
	def_structure_gensym_grammar_variable = 
		make_permanent_gensym_grammar_structure_internal();
    inline_note_allocate_cons(def_structure_gensym_grammar_variable,Nil);
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)2L)) = 
	    grammar_name;
    temp = add1(Last_assigned_grammar_number);
    Last_assigned_grammar_number = temp;
    temp = Last_assigned_grammar_number;
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)1L)) = temp;
    temp = intern(format((SI_Long)3L,Nil,"CATEGORY-IN-GRAMMAR-~D",
	    Last_assigned_grammar_number),_);
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)3L)) = temp;
    temp = intern(format((SI_Long)3L,Nil,"CATEGORY-OF-TOKEN-IN-GRAMMAR-~D",
	    Last_assigned_grammar_number),_);
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)4L)) = temp;
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)7L)) = Nil;
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)8L)) = Nil;
    ISVREF(def_structure_gensym_grammar_variable,(SI_Long)9L) = 
	    FIX((SI_Long)-1L);
    SVREF(def_structure_gensym_grammar_variable,FIX((SI_Long)10L)) = Nil;
    ISVREF(def_structure_gensym_grammar_variable,(SI_Long)11L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_gensym_grammar_variable);
}

Object Category_visit_vector_qm = UNBOUND;

Object Current_category_visit_stamp = UNBOUND;

Object Last_assigned_category_index = UNBOUND;

Object Gensym_grammar_prop = UNBOUND;

static Object Qgensym_grammar;     /* gensym-grammar */

/* MAKE-GENSYM-GRAMMAR */
Object make_gensym_grammar(grammar_name)
    Object grammar_name;
{
    Object gensym_grammar;

    x_note_fn_call(78,67);
    gensym_grammar = make_gensym_grammar_internal_1(grammar_name);
    mutate_global_property(grammar_name,gensym_grammar,Qgensym_grammar);
    return VALUES_1(gensym_grammar);
}

/* GET-GENSYM-GRAMMAR */
Object get_gensym_grammar(grammar_or_grammar_name)
    Object grammar_or_grammar_name;
{
    x_note_fn_call(78,68);
    if (SYMBOLP(grammar_or_grammar_name))
	return getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_or_grammar_name),
		Qgensym_grammar);
    else
	return VALUES_1(grammar_or_grammar_name);
}

Object Required_token_types = UNBOUND;

Object Current_grammar = UNBOUND;

Object Current_indicator_for_category_of_this_name = UNBOUND;

Object Current_indicator_for_category_of_symbol_token = UNBOUND;

/* SET-CURRENT-GRAMMAR */
Object set_current_grammar(gensym_grammar)
    Object gensym_grammar;
{
    x_note_fn_call(78,69);
    Current_grammar = gensym_grammar;
    Current_indicator_for_category_of_this_name = ISVREF(gensym_grammar,
	    (SI_Long)3L);
    Current_indicator_for_category_of_symbol_token = ISVREF(gensym_grammar,
	    (SI_Long)4L);
    if (There_is_a_current_kb_qm &&  !TRUEP(ISVREF(gensym_grammar,
	    (SI_Long)8L)))
	compile_grammar(gensym_grammar);
    return VALUES_1(gensym_grammar);
}

Object Most_positive_fixnum_minus_2 = UNBOUND;

/* SET-UP-CATEGORY-VISIT */
Object set_up_category_visit()
{
    Object svref_arg_1, svref_new_value;
    SI_Long svref_new_value_1;
    XDeclare_area(1);

    x_note_fn_call(78,70);
    if ( !(ISVREF(Current_grammar,(SI_Long)10L) && 
	    FIXNUM_GT(length(ISVREF(Current_grammar,(SI_Long)10L)),
	    ISVREF(Current_grammar,(SI_Long)9L)))) {
	if (PUSH_AREA(Dynamic_area,0)) {
	    svref_arg_1 = Current_grammar;
	    svref_new_value = make_array(3,
		    FIXNUM_ADD1(ISVREF(Current_grammar,(SI_Long)9L)),
		    Kinitial_element,FIX((SI_Long)0L));
	    SVREF(svref_arg_1,FIX((SI_Long)10L)) = svref_new_value;
	}
	POP_AREA(0);
    }
    if (FIXNUM_GT(ISVREF(Current_grammar,(SI_Long)11L),
	    Most_positive_fixnum_minus_2)) {
	svref_arg_1 = Current_grammar;
	ISVREF(svref_arg_1,(SI_Long)11L) = FIX((SI_Long)0L);
    }
    svref_arg_1 = Current_grammar;
    svref_new_value_1 = IFIX(ISVREF(svref_arg_1,(SI_Long)11L)) + (SI_Long)2L;
    return VALUES_1(ISVREF(svref_arg_1,(SI_Long)11L) = FIX(svref_new_value_1));
}

Object The_type_description_of_category_for_token = UNBOUND;

Object Chain_of_available_category_for_tokens = UNBOUND;

Object Category_for_token_count = UNBOUND;

/* CATEGORY-FOR-TOKEN-STRUCTURE-MEMORY-USAGE */
Object category_for_token_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,71);
    temp = Category_for_token_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CATEGORY-FOR-TOKEN-COUNT */
Object outstanding_category_for_token_count()
{
    Object def_structure_category_for_token_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,72);
    gensymed_symbol = IFIX(Category_for_token_count);
    def_structure_category_for_token_variable = 
	    Chain_of_available_category_for_tokens;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_category_for_token_variable))
	goto end_loop;
    def_structure_category_for_token_variable = 
	    ISVREF(def_structure_category_for_token_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CATEGORY-FOR-TOKEN-1 */
Object reclaim_category_for_token_1(category_for_token)
    Object category_for_token;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(78,73);
    inline_note_reclaim_cons(category_for_token,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = category_for_token;
    reclaim_gensym_list_1(ISVREF(category_for_token,(SI_Long)2L));
    SVREF(category_for_token,FIX((SI_Long)2L)) = Nil;
    reclaim_gensym_list_1(ISVREF(category_for_token,(SI_Long)3L));
    SVREF(category_for_token,FIX((SI_Long)3L)) = Nil;
    reclaim_phrase_rule_completions(ISVREF(category_for_token,(SI_Long)4L));
    SVREF(category_for_token,FIX((SI_Long)4L)) = Nil;
    reclaim_agenda_of_more_general_categories(ISVREF(category_for_token,
	    (SI_Long)5L));
    SVREF(category_for_token,FIX((SI_Long)5L)) = Nil;
    reclaim_cached_strict_subcategory_info(ISVREF(category_for_token,
	    (SI_Long)6L));
    SVREF(category_for_token,FIX((SI_Long)6L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_category_for_tokens;
    SVREF(category_for_token,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_category_for_tokens = category_for_token;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CATEGORY-FOR-TOKEN */
Object reclaim_structure_for_category_for_token(category_for_token)
    Object category_for_token;
{
    x_note_fn_call(78,74);
    return reclaim_category_for_token_1(category_for_token);
}

static Object Qg2_defstruct_structure_name_category_for_token_g2_struct;  /* g2-defstruct-structure-name::category-for-token-g2-struct */

/* MAKE-PERMANENT-CATEGORY-FOR-TOKEN-STRUCTURE-INTERNAL */
Object make_permanent_category_for_token_structure_internal()
{
    Object def_structure_category_for_token_variable;
    Object category_for_token_count_new_value;
    Object defstruct_g2_category_for_token_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,75);
    def_structure_category_for_token_variable = Nil;
    category_for_token_count_new_value = FIXNUM_ADD1(Category_for_token_count);
    Category_for_token_count = category_for_token_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_category_for_token_variable = Nil;
	gensymed_symbol = (SI_Long)8L;
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
	defstruct_g2_category_for_token_variable = the_array;
	SVREF(defstruct_g2_category_for_token_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_for_token_g2_struct;
	def_structure_category_for_token_variable = 
		defstruct_g2_category_for_token_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_category_for_token_variable);
}

/* MAKE-CATEGORY-FOR-TOKEN-STRUCTURE-1 */
Object make_category_for_token_structure_1(category_token)
    Object category_token;
{
    Object def_structure_category_for_token_variable;

    x_note_fn_call(78,76);
    def_structure_category_for_token_variable = 
	    Chain_of_available_category_for_tokens;
    if (def_structure_category_for_token_variable) {
	Chain_of_available_category_for_tokens = 
		ISVREF(def_structure_category_for_token_variable,(SI_Long)0L);
	SVREF(def_structure_category_for_token_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_category_for_token_g2_struct;
    }
    else
	def_structure_category_for_token_variable = 
		make_permanent_category_for_token_structure_internal();
    inline_note_allocate_cons(def_structure_category_for_token_variable,Nil);
    SVREF(def_structure_category_for_token_variable,FIX((SI_Long)7L)) = 
	    category_token;
    SVREF(def_structure_category_for_token_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_category_for_token_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_category_for_token_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_category_for_token_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_category_for_token_variable,FIX((SI_Long)6L)) = Nil;
    return VALUES_1(def_structure_category_for_token_variable);
}

Object The_type_description_of_category_for_category_symbol = UNBOUND;

Object Chain_of_available_category_for_category_symbols = UNBOUND;

Object Category_for_category_symbol_count = UNBOUND;

/* CATEGORY-FOR-CATEGORY-SYMBOL-STRUCTURE-MEMORY-USAGE */
Object category_for_category_symbol_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,77);
    temp = Category_for_category_symbol_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)13L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CATEGORY-FOR-CATEGORY-SYMBOL-COUNT */
Object outstanding_category_for_category_symbol_count()
{
    Object def_structure_category_for_category_symbol_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,78);
    gensymed_symbol = IFIX(Category_for_category_symbol_count);
    def_structure_category_for_category_symbol_variable = 
	    Chain_of_available_category_for_category_symbols;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_category_for_category_symbol_variable))
	goto end_loop;
    def_structure_category_for_category_symbol_variable = 
	    ISVREF(def_structure_category_for_category_symbol_variable,
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

/* RECLAIM-CATEGORY-FOR-CATEGORY-SYMBOL-1 */
Object reclaim_category_for_category_symbol_1(category_for_category_symbol)
    Object category_for_category_symbol;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(78,79);
    inline_note_reclaim_cons(category_for_category_symbol,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = category_for_category_symbol;
    reclaim_gensym_list_1(ISVREF(category_for_category_symbol,(SI_Long)2L));
    SVREF(category_for_category_symbol,FIX((SI_Long)2L)) = Nil;
    reclaim_gensym_list_1(ISVREF(category_for_category_symbol,(SI_Long)3L));
    SVREF(category_for_category_symbol,FIX((SI_Long)3L)) = Nil;
    reclaim_phrase_rule_completions(ISVREF(category_for_category_symbol,
	    (SI_Long)4L));
    SVREF(category_for_category_symbol,FIX((SI_Long)4L)) = Nil;
    reclaim_agenda_of_more_general_categories(ISVREF(category_for_category_symbol,
	    (SI_Long)5L));
    SVREF(category_for_category_symbol,FIX((SI_Long)5L)) = Nil;
    reclaim_cached_strict_subcategory_info(ISVREF(category_for_category_symbol,
	    (SI_Long)6L));
    SVREF(category_for_category_symbol,FIX((SI_Long)6L)) = Nil;
    reclaim_gensym_list_1(ISVREF(category_for_category_symbol,(SI_Long)8L));
    SVREF(category_for_category_symbol,FIX((SI_Long)8L)) = Nil;
    reclaim_gensym_list_1(ISVREF(category_for_category_symbol,(SI_Long)9L));
    SVREF(category_for_category_symbol,FIX((SI_Long)9L)) = Nil;
    reclaim_gensym_list_1(ISVREF(category_for_category_symbol,(SI_Long)10L));
    SVREF(category_for_category_symbol,FIX((SI_Long)10L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_category_for_category_symbols;
    SVREF(category_for_category_symbol,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_category_for_category_symbols = 
	    category_for_category_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CATEGORY-FOR-CATEGORY-SYMBOL */
Object reclaim_structure_for_category_for_category_symbol(category_for_category_symbol)
    Object category_for_category_symbol;
{
    x_note_fn_call(78,80);
    return reclaim_category_for_category_symbol_1(category_for_category_symbol);
}

static Object Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct;  /* g2-defstruct-structure-name::category-for-category-symbol-g2-struct */

/* MAKE-PERMANENT-CATEGORY-FOR-CATEGORY-SYMBOL-STRUCTURE-INTERNAL */
Object make_permanent_category_for_category_symbol_structure_internal()
{
    Object def_structure_category_for_category_symbol_variable;
    Object category_for_category_symbol_count_new_value;
    Object defstruct_g2_category_for_category_symbol_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,81);
    def_structure_category_for_category_symbol_variable = Nil;
    category_for_category_symbol_count_new_value = 
	    FIXNUM_ADD1(Category_for_category_symbol_count);
    Category_for_category_symbol_count = 
	    category_for_category_symbol_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_category_for_category_symbol_variable = Nil;
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
	defstruct_g2_category_for_category_symbol_variable = the_array;
	SVREF(defstruct_g2_category_for_category_symbol_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct;
	def_structure_category_for_category_symbol_variable = 
		defstruct_g2_category_for_category_symbol_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_category_for_category_symbol_variable);
}

static Object Qnot_a_result_category;  /* not-a-result-category */

/* MAKE-CATEGORY-FOR-CATEGORY-SYMBOL-1 */
Object make_category_for_category_symbol_1(category_symbol)
    Object category_symbol;
{
    Object def_structure_category_for_category_symbol_variable;

    x_note_fn_call(78,82);
    def_structure_category_for_category_symbol_variable = 
	    Chain_of_available_category_for_category_symbols;
    if (def_structure_category_for_category_symbol_variable) {
	Chain_of_available_category_for_category_symbols = 
		ISVREF(def_structure_category_for_category_symbol_variable,
		(SI_Long)0L);
	SVREF(def_structure_category_for_category_symbol_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct;
    }
    else
	def_structure_category_for_category_symbol_variable = 
		make_permanent_category_for_category_symbol_structure_internal();
    inline_note_allocate_cons(def_structure_category_for_category_symbol_variable,
	    Nil);
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)7L)) = category_symbol;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)8L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)11L)) = Qnot_a_result_category;
    SVREF(def_structure_category_for_category_symbol_variable,
	    FIX((SI_Long)12L)) = Nil;
    return VALUES_1(def_structure_category_for_category_symbol_variable);
}

/* GET-OR-MAKE-CATEGORY-FOR-CATEGORY-SYMBOL */
Object get_or_make_category_for_category_symbol(category_symbol)
    Object category_symbol;
{
    Object temp, new_category, temp_1, svref_new_value;
    XDeclare_area(1);
    Object result;

    x_note_fn_call(78,83);
    temp = get(category_symbol,Current_indicator_for_category_of_this_name,_);
    if (temp)
	return VALUES_1(temp);
    else {
	new_category = make_category_for_category_symbol_1(category_symbol);
	temp_1 = Current_grammar;
	svref_new_value = FIXNUM_ADD1(ISVREF(temp_1,(SI_Long)9L));
	SVREF(temp_1,FIX((SI_Long)9L)) = svref_new_value;
	SVREF(new_category,FIX((SI_Long)1L)) = svref_new_value;
	temp_1 = Current_grammar;
	svref_new_value = gensym_cons_1(category_symbol,
		ISVREF(Current_grammar,(SI_Long)7L));
	SVREF(temp_1,FIX((SI_Long)7L)) = svref_new_value;
	if (PUSH_AREA(Dynamic_area,0)) {
	    temp_1 = Current_indicator_for_category_of_this_name;
	    result = set_get(category_symbol,temp_1,new_category);
	}
	POP_AREA(0);
	return result;
    }
}

/* GET-CATEGORY-OF-TOKEN */
Object get_category_of_token(token_value)
    Object token_value;
{
    Object key, value, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(78,84);
    if (SYMBOLP(token_value))
	return get(token_value,
		Current_indicator_for_category_of_symbol_token,_);
    else if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(token_value) != (SI_Long)0L) {
	key = Nil;
	value = Nil;
	ab_loop_list_ = ISVREF(Current_grammar,(SI_Long)5L);
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	key = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	value = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(key) != (SI_Long)0L && 
		string_eq_w(token_value,key))
	    return VALUES_1(value);
	goto next_loop;
      end_loop:
	return VALUES_1(Nil);
	return VALUES_1(Qnil);
    }
    else {
	temp = assoc_eql(token_value,ISVREF(Current_grammar,(SI_Long)5L));
	return VALUES_1(SECOND(temp));
    }
}

/* SET-CATEGORY-OF-TOKEN */
Object set_category_of_token(token,category)
    Object token, category;
{
    Object temp, svref_new_value;

    x_note_fn_call(78,85);
    if (SYMBOLP(token)) {
	temp = 
		gensym_cons_1(Current_indicator_for_category_of_symbol_token,
		gensym_cons_1(category,SYMBOL_PLIST(token)));
	SET_SYMBOL_PLIST(token,temp);
    }
    else {
	temp = Current_grammar;
	svref_new_value = gensym_cons_1(gensym_list_2(token,category),
		ISVREF(Current_grammar,(SI_Long)5L));
	SVREF(temp,FIX((SI_Long)5L)) = svref_new_value;
    }
    return VALUES_1(category);
}

/* MAKE-CATEGORY-FOR-TOKEN */
Object make_category_for_token(token,existing_category_of_token_qm)
    Object token, existing_category_of_token_qm;
{
    Object temp, svref_new_value, category_specifically_for_token;
    Object token_instances_without_specific_categories, temp_1;

    x_note_fn_call(78,86);
    temp = Current_grammar;
    svref_new_value = gensym_cons_1(token,ISVREF(Current_grammar,(SI_Long)6L));
    SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    category_specifically_for_token = 
	    make_category_for_token_structure_1(token);
    temp = Current_grammar;
    svref_new_value = FIXNUM_ADD1(ISVREF(temp,(SI_Long)9L));
    SVREF(temp,FIX((SI_Long)9L)) = svref_new_value;
    SVREF(category_specifically_for_token,FIX((SI_Long)1L)) = svref_new_value;
    if (existing_category_of_token_qm) {
	token_instances_without_specific_categories = 
		ISVREF(existing_category_of_token_qm,(SI_Long)9L);
	temp = gensym_cons_1(existing_category_of_token_qm,Nil);
	SVREF(category_specifically_for_token,FIX((SI_Long)2L)) = temp;
	temp_1 = member_eql(token,token_instances_without_specific_categories);
	temp = delete_gensym_element_1(CAR(temp_1),
		token_instances_without_specific_categories);
	SVREF(existing_category_of_token_qm,FIX((SI_Long)9L)) = temp;
	temp = nconc2(ISVREF(existing_category_of_token_qm,(SI_Long)8L),
		gensym_cons_1(category_specifically_for_token,Nil));
	SVREF(existing_category_of_token_qm,FIX((SI_Long)8L)) = temp;
    }
    return set_category_of_token(token,category_specifically_for_token);
}

/* GET-OR-MAKE-CATEGORY-FOR-RULE-ELEMENT */
Object get_or_make_category_for_rule_element(rule_element)
    Object rule_element;
{
    Object category_of_token_qm;

    x_note_fn_call(78,87);
    if (SYMBOLP(rule_element))
	return get_or_make_category_for_category_symbol(rule_element);
    else {
	category_of_token_qm = get_category_of_token(SECOND(rule_element));
	if (category_of_token_qm && SIMPLE_VECTOR_P(category_of_token_qm) 
		&& EQ(ISVREF(category_of_token_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_category_for_token_g2_struct))
	    return VALUES_1(category_of_token_qm);
	else
	    return make_category_for_token(SECOND(rule_element),
		    category_of_token_qm);
    }
}

Object The_type_description_of_category_set = UNBOUND;

Object Chain_of_available_category_sets = UNBOUND;

Object Category_set_count = UNBOUND;

/* CATEGORY-SET-STRUCTURE-MEMORY-USAGE */
Object category_set_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,88);
    temp = Category_set_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CATEGORY-SET-COUNT */
Object outstanding_category_set_count()
{
    Object def_structure_category_set_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,89);
    gensymed_symbol = IFIX(Category_set_count);
    def_structure_category_set_variable = Chain_of_available_category_sets;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_category_set_variable))
	goto end_loop;
    def_structure_category_set_variable = 
	    ISVREF(def_structure_category_set_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-CATEGORY-SET-1 */
Object reclaim_category_set_1(category_set)
    Object category_set;
{
    Object svref_new_value;

    x_note_fn_call(78,90);
    inline_note_reclaim_cons(category_set,Nil);
    svref_new_value = Chain_of_available_category_sets;
    SVREF(category_set,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_category_sets = category_set;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CATEGORY-SET */
Object reclaim_structure_for_category_set(category_set)
    Object category_set;
{
    x_note_fn_call(78,91);
    return reclaim_category_set_1(category_set);
}

static Object Qg2_defstruct_structure_name_category_set_g2_struct;  /* g2-defstruct-structure-name::category-set-g2-struct */

/* MAKE-PERMANENT-CATEGORY-SET-STRUCTURE-INTERNAL */
Object make_permanent_category_set_structure_internal()
{
    Object def_structure_category_set_variable, category_set_count_new_value;
    Object defstruct_g2_category_set_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,92);
    def_structure_category_set_variable = Nil;
    category_set_count_new_value = FIXNUM_ADD1(Category_set_count);
    Category_set_count = category_set_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_category_set_variable = Nil;
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
	defstruct_g2_category_set_variable = the_array;
	SVREF(defstruct_g2_category_set_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_set_g2_struct;
	def_structure_category_set_variable = 
		defstruct_g2_category_set_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_category_set_variable);
}

/* MAKE-CATEGORY-SET-1 */
Object make_category_set_1(category_set_list_1,category_vector)
    Object category_set_list_1, category_vector;
{
    Object def_structure_category_set_variable;

    x_note_fn_call(78,93);
    def_structure_category_set_variable = Chain_of_available_category_sets;
    if (def_structure_category_set_variable) {
	Chain_of_available_category_sets = 
		ISVREF(def_structure_category_set_variable,(SI_Long)0L);
	SVREF(def_structure_category_set_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_category_set_g2_struct;
    }
    else
	def_structure_category_set_variable = 
		make_permanent_category_set_structure_internal();
    inline_note_allocate_cons(def_structure_category_set_variable,Nil);
    SVREF(def_structure_category_set_variable,FIX((SI_Long)1L)) = 
	    category_set_list_1;
    SVREF(def_structure_category_set_variable,FIX((SI_Long)2L)) = 
	    category_vector;
    return VALUES_1(def_structure_category_set_variable);
}

/* ADD-CATEGORY-TO-BIT-SET */
Object add_category_to_bit_set(category,category_list)
    Object category, category_list;
{
    Object size, vector_1, new_vector, index_1;
    SI_Long i, ab_loop_bind_, aref_new_value, vector_index;

    x_note_fn_call(78,94);
    size = FIXNUM_ADD1(ISVREF(Current_grammar,(SI_Long)9L));
    vector_1 = ISVREF(category_list,(SI_Long)2L);
    if ( !(VECTORP(vector_1) && FIXNUM_LE(size,length(vector_1)))) {
	new_vector = allocate_byte_vector_16(ceiling(size,FIX((SI_Long)16L)));
	if (vector_1) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length(vector_1));
	  next_loop:
	    if (i >= ab_loop_bind_)
		goto end_loop;
	    aref_new_value = UBYTE_16_ISAREF_1(vector_1,i);
	    UBYTE_16_ISASET_1(new_vector,i,aref_new_value);
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	i = vector_1 ? IFIX(length(vector_1)) : (SI_Long)0L;
	ab_loop_bind_ = IFIX(length(new_vector));
      next_loop_1:
	if (i >= ab_loop_bind_)
	    goto end_loop_1;
	UBYTE_16_ISASET_1(new_vector,i,(SI_Long)0L);
	i = i + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	if (vector_1)
	    reclaim_byte_vector_16(vector_1);
	vector_1 = new_vector;
	SVREF(category_list,FIX((SI_Long)2L)) = vector_1;
    }
    index_1 = ISVREF(category,(SI_Long)1L);
    vector_index = IFIX(index_1) >>  -  - (SI_Long)4L;
    aref_new_value = UBYTE_16_ISAREF_1(vector_1,vector_index) | 
	    (SI_Long)1L << (IFIX(index_1) & (SI_Long)15L);
    UBYTE_16_ISASET_1(vector_1,vector_index,aref_new_value);
    return VALUES_1(Nil);
}

/* INDICES-OF-BITS-IN-CATEGORY-VECTOR */
Object indices_of_bits_in_category_vector(vector_1)
    Object vector_1;
{
    Object bits, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loopvar__3;
    Object ab_loopvar__4, temp;
    SI_Long vector_index, ab_loop_bind_, j;

    x_note_fn_call(78,95);
    vector_index = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(vector_1));
    bits = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (vector_index >= ab_loop_bind_)
	goto end_loop;
    bits = FIX(UBYTE_16_ISAREF_1(vector_1,vector_index));
    j = (SI_Long)0L;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if (j > (SI_Long)15L)
	goto end_loop_1;
    if ((SI_Long)1L == ((SI_Long)1L & IFIX(bits) >>  -  - j)) {
	ab_loopvar__4 = gensym_cons_1(FIX(vector_index * (SI_Long)16L + j),
		Nil);
	if (ab_loopvar__3)
	    M_CDR(ab_loopvar__3) = ab_loopvar__4;
	else
	    ab_loopvar__2 = ab_loopvar__4;
	ab_loopvar__3 = ab_loopvar__4;
    }
    j = j + (SI_Long)1L;
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
    vector_index = vector_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_2;
    temp = Qnil;
  end_2:;
    return VALUES_1(temp);
}

/* PRINT-INDICES-OF-BITS-IN-CATEGORY-VECTOR */
Object print_indices_of_bits_in_category_vector(vector_1,stream)
    Object vector_1, stream;
{
    Object indices, temp;

    x_note_fn_call(78,96);
    indices = indices_of_bits_in_category_vector(vector_1);
    format((SI_Long)3L,stream,"{~{~D~^,~}}",indices);
    temp = reclaim_gensym_list_1(indices);
    return VALUES_1(temp);
}

/* CONVERT-TO-CATEGORY-SET */
Object convert_to_category_set(category_list)
    Object category_list;
{
    Object set_1, category, ab_loop_list_;

    x_note_fn_call(78,97);
    set_1 = make_category_set_1(category_list,Nil);
    category = Nil;
    ab_loop_list_ = category_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    add_category_to_bit_set(category,set_1);
    goto next_loop;
  end_loop:;
    return VALUES_1(set_1);
}

/* CATEGORY-SET-MEMQ */
Object category_set_memq(category,category_list)
    Object category, category_list;
{
    Object gensymed_symbol, temp, index_1, vector_1;
    SI_Long vector_index, bits;

    x_note_fn_call(78,98);
    if (LISTP(category_list)) {
	gensymed_symbol = category_list;
      next_loop:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop;
	if (EQ(M_CAR(gensymed_symbol),category)) {
	    temp = gensymed_symbol;
	    goto end_1;
	}
	gensymed_symbol = M_CDR(gensymed_symbol);
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
    }
    else {
	index_1 = ISVREF(category,(SI_Long)1L);
	vector_1 = ISVREF(category_list,(SI_Long)2L);
	vector_index = IFIX(index_1) >>  -  - (SI_Long)4L;
	bits = vector_index < IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(vector_1)) ? 
		UBYTE_16_ISAREF_1(vector_1,vector_index) : (SI_Long)0L;
	temp = (SI_Long)1L == ((SI_Long)1L & bits >>  -  - (IFIX(index_1) 
		& (SI_Long)15L)) ? T : Nil;
    }
    return VALUES_1(temp);
}

/* CATEGORY-SET-PUSH-1 */
Object category_set_push_1(category,category_list)
    Object category, category_list;
{
    Object temp, gensym_push_modify_macro_arg, car_1, cdr_1, svref_new_value;

    x_note_fn_call(78,99);
    if (LISTP(category_list) && FIXNUM_LE(length(category_list),
	    Maximum_size_of_category_set_as_list))
	temp = gensym_cons_1(category,category_list);
    else {
	if (LISTP(category_list))
	    category_list = convert_to_category_set(category_list);
	add_category_to_bit_set(category,category_list);
	gensym_push_modify_macro_arg = category;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = ISVREF(category_list,(SI_Long)1L);
	svref_new_value = gensym_cons_1(car_1,cdr_1);
	SVREF(category_list,FIX((SI_Long)1L)) = svref_new_value;
	temp = category_list;
    }
    return VALUES_1(temp);
}

Object Current_subcategory_path = UNBOUND;

Object Currently_tracking_subcategory_path_max = UNBOUND;

/* STRICT-SUBCATEGORYP-1 */
Object strict_subcategoryp_1(category_1,category_2)
    Object category_1, category_2;
{
    Object more_general_category, ab_loop_list_;
    Object corresponding_transformation_lists, ab_loop_it_, ab_loop_iter_flag_;
    Object temp, transformation_list_or_t_qm;

    x_note_fn_call(78,100);
    more_general_category = Nil;
    ab_loop_list_ = ISVREF(category_1,(SI_Long)2L);
    corresponding_transformation_lists = ISVREF(category_1,(SI_Long)3L);
    ab_loop_it_ = Nil;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    more_general_category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	corresponding_transformation_lists = 
		CDR(corresponding_transformation_lists);
    if (EQ(more_general_category,category_2)) {
	temp = CAR(corresponding_transformation_lists);
	if (temp);
	else
	    temp = T;
	ab_loop_it_ = temp;
    }
    else {
	transformation_list_or_t_qm = 
		strict_subcategoryp_1(more_general_category,category_2);
	if (transformation_list_or_t_qm) {
	    temp = CAR(corresponding_transformation_lists);
	    if (temp);
	    else
		temp = transformation_list_or_t_qm;
	    ab_loop_it_ = temp;
	}
	else
	    ab_loop_it_ = Nil;
    }
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* STRICT-SUBCATEGORY-PATH-1 */
Object strict_subcategory_path_1(category_1,category_2)
    Object category_1, category_2;
{
    Object more_general_category, ab_loop_list_, ab_loop_it_, path;
    char found_it;

    x_note_fn_call(78,101);
    more_general_category = Nil;
    ab_loop_list_ = ISVREF(category_1,(SI_Long)2L);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    more_general_category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    found_it = EQ(more_general_category,category_2);
    path =  !found_it ? strict_subcategory_path_1(more_general_category,
	    category_2) : Nil;
    ab_loop_it_ = found_it || path ? gensym_cons_1(category_1,path) : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object The_type_description_of_strict_subcategory_info = UNBOUND;

Object Chain_of_available_strict_subcategory_infos = UNBOUND;

Object Strict_subcategory_info_count = UNBOUND;

/* STRICT-SUBCATEGORY-INFO-STRUCTURE-MEMORY-USAGE */
Object strict_subcategory_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,102);
    temp = Strict_subcategory_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-STRICT-SUBCATEGORY-INFO-COUNT */
Object outstanding_strict_subcategory_info_count()
{
    Object def_structure_strict_subcategory_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,103);
    gensymed_symbol = IFIX(Strict_subcategory_info_count);
    def_structure_strict_subcategory_info_variable = 
	    Chain_of_available_strict_subcategory_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_strict_subcategory_info_variable))
	goto end_loop;
    def_structure_strict_subcategory_info_variable = 
	    ISVREF(def_structure_strict_subcategory_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-STRICT-SUBCATEGORY-INFO-1 */
Object reclaim_strict_subcategory_info_1(strict_subcategory_info_2)
    Object strict_subcategory_info_2;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(78,104);
    inline_note_reclaim_cons(strict_subcategory_info_2,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = strict_subcategory_info_2;
    reclaim_gensym_list_1(ISVREF(strict_subcategory_info_2,(SI_Long)3L));
    SVREF(strict_subcategory_info_2,FIX((SI_Long)3L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_strict_subcategory_infos;
    SVREF(strict_subcategory_info_2,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_strict_subcategory_infos = strict_subcategory_info_2;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-STRICT-SUBCATEGORY-INFO */
Object reclaim_structure_for_strict_subcategory_info(strict_subcategory_info_2)
    Object strict_subcategory_info_2;
{
    x_note_fn_call(78,105);
    return reclaim_strict_subcategory_info_1(strict_subcategory_info_2);
}

static Object Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct;  /* g2-defstruct-structure-name::strict-subcategory-info-g2-struct */

/* MAKE-PERMANENT-STRICT-SUBCATEGORY-INFO-STRUCTURE-INTERNAL */
Object make_permanent_strict_subcategory_info_structure_internal()
{
    Object def_structure_strict_subcategory_info_variable;
    Object strict_subcategory_info_count_new_value;
    Object defstruct_g2_strict_subcategory_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,106);
    def_structure_strict_subcategory_info_variable = Nil;
    strict_subcategory_info_count_new_value = 
	    FIXNUM_ADD1(Strict_subcategory_info_count);
    Strict_subcategory_info_count = strict_subcategory_info_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_strict_subcategory_info_variable = Nil;
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
	defstruct_g2_strict_subcategory_info_variable = the_array;
	SVREF(defstruct_g2_strict_subcategory_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct;
	def_structure_strict_subcategory_info_variable = 
		defstruct_g2_strict_subcategory_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_strict_subcategory_info_variable);
}

/* MAKE-STRICT-SUBCATEGORY-INFO-1 */
Object make_strict_subcategory_info_1(strict_subcategory_info_category,
	    strict_subcategory_info_subcategoryp,strict_subcategory_info_path)
    Object strict_subcategory_info_category;
    Object strict_subcategory_info_subcategoryp, strict_subcategory_info_path;
{
    Object def_structure_strict_subcategory_info_variable;

    x_note_fn_call(78,107);
    def_structure_strict_subcategory_info_variable = 
	    Chain_of_available_strict_subcategory_infos;
    if (def_structure_strict_subcategory_info_variable) {
	Chain_of_available_strict_subcategory_infos = 
		ISVREF(def_structure_strict_subcategory_info_variable,
		(SI_Long)0L);
	SVREF(def_structure_strict_subcategory_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct;
    }
    else
	def_structure_strict_subcategory_info_variable = 
		make_permanent_strict_subcategory_info_structure_internal();
    inline_note_allocate_cons(def_structure_strict_subcategory_info_variable,
	    Nil);
    SVREF(def_structure_strict_subcategory_info_variable,FIX((SI_Long)1L)) 
	    = strict_subcategory_info_category;
    SVREF(def_structure_strict_subcategory_info_variable,FIX((SI_Long)2L)) 
	    = strict_subcategory_info_subcategoryp;
    SVREF(def_structure_strict_subcategory_info_variable,FIX((SI_Long)3L)) 
	    = strict_subcategory_info_path;
    return VALUES_1(def_structure_strict_subcategory_info_variable);
}

/* RECLAIM-CACHED-STRICT-SUBCATEGORY-INFO */
Object reclaim_cached_strict_subcategory_info(cons_1)
    Object cons_1;
{
    Object info, ab_loop_list_;

    x_note_fn_call(78,108);
    if (cons_1) {
	reclaim_gensym_list_1(CAR(cons_1));
	info = Nil;
	ab_loop_list_ = CDR(cons_1);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	reclaim_strict_subcategory_info_1(info);
	goto next_loop;
      end_loop:;
	reclaim_gensym_list_1(CDR(cons_1));
	return reclaim_gensym_cons_1(cons_1);
    }
    else
	return VALUES_1(Nil);
}

Object Strict_subcategory_infos_exist_p = UNBOUND;

Object Strict_subcategory_info_last_category_1 = UNBOUND;

Object Strict_subcategory_info_last_category_2 = UNBOUND;

Object Strict_subcategory_info_last_result = UNBOUND;

Object Names_of_grammars_to_add_rules_to = UNBOUND;

/* DECACHE-ALL-STRICT-SUBCATEGORY-INFOS */
Object decache_all_strict_subcategory_infos()
{
    Object grammar_name, ab_loop_list_, current_grammar;
    Object current_indicator_for_category_of_symbol_token;
    Object current_indicator_for_category_of_this_name, category_symbol;
    Object ab_loop_list__1, category, token;
    Declare_special(3);

    x_note_fn_call(78,109);
    if (Strict_subcategory_infos_exist_p) {
	Strict_subcategory_infos_exist_p = Nil;
	Strict_subcategory_info_last_category_1 = Nil;
	Strict_subcategory_info_last_category_2 = Nil;
	Strict_subcategory_info_last_result = Nil;
	grammar_name = Nil;
	ab_loop_list_ = Names_of_grammars_to_add_rules_to;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	grammar_name = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	current_grammar = get_gensym_grammar(grammar_name);
	PUSH_SPECIAL(Current_grammar,current_grammar,2);
	  current_indicator_for_category_of_symbol_token = 
		  ISVREF(Current_grammar,(SI_Long)4L);
	  PUSH_SPECIAL(Current_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
		  1);
	    current_indicator_for_category_of_this_name = 
		    ISVREF(Current_grammar,(SI_Long)3L);
	    PUSH_SPECIAL(Current_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
		    0);
	      category_symbol = Nil;
	      ab_loop_list__1 = ISVREF(Current_grammar,(SI_Long)7L);
	      category = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_1;
	      category_symbol = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      category = make_category_for_category_symbol_1(category_symbol);
	      reclaim_cached_strict_subcategory_info(ISVREF(category,
		      (SI_Long)6L));
	      SVREF(category,FIX((SI_Long)6L)) = Nil;
	      goto next_loop_1;
	    end_loop_1:;
	      token = Nil;
	      ab_loop_list__1 = ISVREF(Current_grammar,(SI_Long)6L);
	      category = Nil;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_2;
	      token = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      category = get_category_of_token(token);
	      reclaim_cached_strict_subcategory_info(ISVREF(category,
		      (SI_Long)6L));
	      SVREF(category,FIX((SI_Long)6L)) = Nil;
	      goto next_loop_2;
	    end_loop_2:;
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* STRICT-SUBCATEGORY-INFO-1 */
Object strict_subcategory_info_1(category_1,category_2)
    Object category_1, category_2;
{
    Object category_info, info, ab_loop_list_, temp, strict_subcategoryp_2;
    Object temp_1, path, gensym_push_modify_macro_arg, car_1, cdr_1;

    x_note_fn_call(78,110);
    category_info = ISVREF(category_1,(SI_Long)6L);
    if (category_info);
    else {
	category_info = gensym_cons_1(Nil,Nil);
	SVREF(category_1,FIX((SI_Long)6L)) = category_info;
    }
    if (category_set_memq(category_2,CAR(category_info)))
	return VALUES_1(Nil);
    else {
	info = Nil;
	ab_loop_list_ = CDR(category_info);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(category_2,ISVREF(info,(SI_Long)1L))) {
	    temp = info;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	if (temp)
	    return VALUES_1(temp);
	else {
	    strict_subcategoryp_2 = strict_subcategoryp_1(category_1,
		    category_2);
	    if ( !TRUEP(strict_subcategoryp_2)) {
		temp_1 = category_set_push_1(category_2,CAR(category_info));
		M_CAR(category_info) = temp_1;
		return VALUES_1(Nil);
	    }
	    else {
		path = strict_subcategory_path_1(category_1,category_2);
		info = make_strict_subcategory_info_1(category_2,
			strict_subcategoryp_2,path);
		gensym_push_modify_macro_arg = info;
		car_1 = gensym_push_modify_macro_arg;
		cdr_1 = CDR(category_info);
		temp_1 = gensym_cons_1(car_1,cdr_1);
		M_CDR(category_info) = temp_1;
		return VALUES_1(info);
	    }
	}
    }
}

/* STRICT-SUBCATEGORY-INFO */
Object strict_subcategory_info(category_1,category_2)
    Object category_1, category_2;
{
    Object result_1;

    x_note_fn_call(78,111);
    if (EQ(category_1,Strict_subcategory_info_last_category_1) && 
	    EQ(category_2,Strict_subcategory_info_last_category_2))
	return VALUES_1(Strict_subcategory_info_last_result);
    else {
	result_1 = strict_subcategory_info_1(category_1,category_2);
	Strict_subcategory_info_last_category_1 = category_1;
	Strict_subcategory_info_last_category_2 = category_2;
	Strict_subcategory_info_last_result = result_1;
	return VALUES_1(Strict_subcategory_info_last_result);
    }
}

/* SUBCATEGORYP */
Object subcategoryp(category_1,category_2)
    Object category_1, category_2;
{
    x_note_fn_call(78,112);
    if (EQ(category_1,category_2))
	return VALUES_1(T);
    else if (SIMPLE_VECTOR_P(category_2) && EQ(ISVREF(category_2,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct))
	return strict_subcategoryp(category_1,category_2);
    else
	return VALUES_1(Qnil);
}

/* STRICT-SUBCATEGORYP */
Object strict_subcategoryp(category_1,category_2)
    Object category_1, category_2;
{
    Object info_qm;

    x_note_fn_call(78,113);
    info_qm = strict_subcategory_info(category_1,category_2);
    if (info_qm)
	return VALUES_1(ISVREF(info_qm,(SI_Long)2L));
    else
	return VALUES_1(Nil);
}

/* STRICT-SUBCATEGORY-PATH */
Object strict_subcategory_path(category_1,category_2)
    Object category_1, category_2;
{
    Object info_qm;

    x_note_fn_call(78,114);
    info_qm = strict_subcategory_info(category_1,category_2);
    if (info_qm)
	return VALUES_1(ISVREF(info_qm,(SI_Long)3L));
    else
	return VALUES_1(Nil);
}

/* SET-CURRENT-SUBCATEGORY-PATH */
Object set_current_subcategory_path(category_1,category_2)
    Object category_1, category_2;
{
    Object path, category, ab_loop_list_, svref_arg_1;
    SI_Long index_1;

    x_note_fn_call(78,115);
    path =  !EQ(category_1,category_2) ? 
	    strict_subcategory_path(category_1,category_2) : Nil;
    Currently_tracking_subcategory_path_max = length(path);
    index_1 = (SI_Long)1L;
    category = Nil;
    ab_loop_list_ = path;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    svref_arg_1 = Current_subcategory_path;
    ISVREF(svref_arg_1,index_1) = category;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(path);
}

/* RECLAIM-TOKENS-WITH-SPECIFIC-CATEGORIES */
Object reclaim_tokens_with_specific_categories(tokens_with_specific_categories)
    Object tokens_with_specific_categories;
{
    Object current_grammar, current_indicator_for_category_of_this_name;
    Object current_indicator_for_category_of_symbol_token, token;
    Object ab_loop_list_;
    Declare_special(3);

    x_note_fn_call(78,116);
    current_grammar = Structure_being_reclaimed;
    PUSH_SPECIAL(Current_grammar,current_grammar,2);
      current_indicator_for_category_of_this_name = ISVREF(Current_grammar,
	      (SI_Long)3L);
      PUSH_SPECIAL(Current_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
	      1);
	current_indicator_for_category_of_symbol_token = 
		ISVREF(Current_grammar,(SI_Long)4L);
	PUSH_SPECIAL(Current_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
		0);
	  token = Nil;
	  ab_loop_list_ = tokens_with_specific_categories;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  token = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  reclaim_category_for_token_1(get_category_of_token(token));
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return reclaim_gensym_list_1(tokens_with_specific_categories);
}

/* RECLAIM-CATEGORY-SYMBOLS */
Object reclaim_category_symbols(category_symbols)
    Object category_symbols;
{
    Object category_symbol, ab_loop_list_, get_arg_2;

    x_note_fn_call(78,117);
    category_symbol = Nil;
    ab_loop_list_ = category_symbols;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_category_for_category_symbol_1(get(category_symbol,
	    Current_indicator_for_category_of_this_name,_));
    get_arg_2 = Current_indicator_for_category_of_this_name;
    set_get(category_symbol,get_arg_2,Nil);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(category_symbols);
}

/* RECLAIM-GRAMMAR-LIST-FUNCTION */
Object reclaim_grammar_list_function(list_1)
    Object list_1;
{
    Object last_1, next_qm, cdr_new_value;

    x_note_fn_call(78,118);
    if (list_1) {
	last_1 = list_1;
	next_qm = Nil;
      next_loop:
	next_qm = M_CDR(last_1);
	if ( !TRUEP(next_qm))
	    goto end_loop;
	inline_note_reclaim_cons(last_1,Qab_gensym);
	last_1 = next_qm;
	goto next_loop;
      end_loop:
	inline_note_reclaim_cons(last_1,Qab_gensym);
	cdr_new_value = Available_gensym_conses;
	M_CDR(last_1) = cdr_new_value;
	Available_gensym_conses = list_1;
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

Object Category_symbols_for_symbol_token_kbprop = UNBOUND;

Object Symbol_tokens_for_category_symbol_kbprop = UNBOUND;

/* ADD-KB-SPECIFIC-SYMBOL-TOKEN */
Object add_kb_specific_symbol_token(symbol,category_symbol)
    Object symbol, category_symbol;
{
    x_note_fn_call(78,119);
    mutate_kb_specific_property_value(symbol,gensym_cons_1(category_symbol,
	    lookup_kb_specific_property_value(symbol,
	    Category_symbols_for_symbol_token_kbprop)),
	    Category_symbols_for_symbol_token_kbprop);
    return mutate_kb_specific_property_value(category_symbol,
	    gensym_cons_1(symbol,
	    lookup_kb_specific_property_value(category_symbol,
	    Symbol_tokens_for_category_symbol_kbprop)),
	    Symbol_tokens_for_category_symbol_kbprop);
}

Object The_type_description_of_phrase_rule_completion = UNBOUND;

Object Chain_of_available_phrase_rule_completions = UNBOUND;

Object Phrase_rule_completion_count = UNBOUND;

/* PHRASE-RULE-COMPLETION-STRUCTURE-MEMORY-USAGE */
Object phrase_rule_completion_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,120);
    temp = Phrase_rule_completion_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PHRASE-RULE-COMPLETION-COUNT */
Object outstanding_phrase_rule_completion_count()
{
    Object def_structure_phrase_rule_completion_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,121);
    gensymed_symbol = IFIX(Phrase_rule_completion_count);
    def_structure_phrase_rule_completion_variable = 
	    Chain_of_available_phrase_rule_completions;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_phrase_rule_completion_variable))
	goto end_loop;
    def_structure_phrase_rule_completion_variable = 
	    ISVREF(def_structure_phrase_rule_completion_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-PHRASE-RULE-COMPLETION-1 */
Object reclaim_phrase_rule_completion_1(phrase_rule_completion)
    Object phrase_rule_completion;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(78,122);
    inline_note_reclaim_cons(phrase_rule_completion,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = phrase_rule_completion;
    reclaim_phrase_rule_completions(ISVREF(phrase_rule_completion,
	    (SI_Long)4L));
    SVREF(phrase_rule_completion,FIX((SI_Long)4L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_phrase_rule_completions;
    SVREF(phrase_rule_completion,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_phrase_rule_completions = phrase_rule_completion;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PHRASE-RULE-COMPLETION */
Object reclaim_structure_for_phrase_rule_completion(phrase_rule_completion)
    Object phrase_rule_completion;
{
    x_note_fn_call(78,123);
    return reclaim_phrase_rule_completion_1(phrase_rule_completion);
}

static Object Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct;  /* g2-defstruct-structure-name::phrase-rule-completion-g2-struct */

/* MAKE-PERMANENT-PHRASE-RULE-COMPLETION-STRUCTURE-INTERNAL */
Object make_permanent_phrase_rule_completion_structure_internal()
{
    Object def_structure_phrase_rule_completion_variable;
    Object defstruct_g2_phrase_rule_completion_variable, the_array;
    Object svref_new_value;
    SI_Long phrase_rule_completion_count_new_value, gensymed_symbol;
    SI_Long gensymed_symbol_1, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,124);
    def_structure_phrase_rule_completion_variable = Nil;
    phrase_rule_completion_count_new_value = 
	    IFIX(Phrase_rule_completion_count) + (SI_Long)100L;
    Phrase_rule_completion_count = FIX(phrase_rule_completion_count_new_value);
    if (PUSH_AREA(Dynamic_area,0)) {
	gensymed_symbol = (SI_Long)1L;
      next_loop:
	defstruct_g2_phrase_rule_completion_variable = Nil;
	gensymed_symbol_1 = (SI_Long)5L;
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
	defstruct_g2_phrase_rule_completion_variable = the_array;
	SVREF(defstruct_g2_phrase_rule_completion_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct;
	def_structure_phrase_rule_completion_variable = 
		defstruct_g2_phrase_rule_completion_variable;
	if (gensymed_symbol >= (SI_Long)100L)
	    goto end_loop_1;
	svref_new_value = Chain_of_available_phrase_rule_completions;
	SVREF(def_structure_phrase_rule_completion_variable,
		FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_phrase_rule_completions = 
		def_structure_phrase_rule_completion_variable;
	gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	goto next_loop;
      end_loop_1:;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_phrase_rule_completion_variable);
}

/* MAKE-PHRASE-RULE-COMPLETION-1 */
Object make_phrase_rule_completion_1(category_for_completed_phrase,
	    category_of_next_constituent,
	    phrase_rule_completions_past_next_constituent)
    Object category_for_completed_phrase, category_of_next_constituent;
    Object phrase_rule_completions_past_next_constituent;
{
    Object def_structure_phrase_rule_completion_variable;

    x_note_fn_call(78,125);
    def_structure_phrase_rule_completion_variable = 
	    Chain_of_available_phrase_rule_completions;
    if (def_structure_phrase_rule_completion_variable) {
	Chain_of_available_phrase_rule_completions = 
		ISVREF(def_structure_phrase_rule_completion_variable,
		(SI_Long)0L);
	SVREF(def_structure_phrase_rule_completion_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct;
    }
    else
	def_structure_phrase_rule_completion_variable = 
		make_permanent_phrase_rule_completion_structure_internal();
    inline_note_allocate_cons(def_structure_phrase_rule_completion_variable,
	    Nil);
    SVREF(def_structure_phrase_rule_completion_variable,FIX((SI_Long)2L)) 
	    = category_for_completed_phrase;
    SVREF(def_structure_phrase_rule_completion_variable,FIX((SI_Long)1L)) 
	    = category_of_next_constituent;
    SVREF(def_structure_phrase_rule_completion_variable,FIX((SI_Long)4L)) 
	    = phrase_rule_completions_past_next_constituent;
    SVREF(def_structure_phrase_rule_completion_variable,FIX((SI_Long)3L)) 
	    = Nil;
    return VALUES_1(def_structure_phrase_rule_completion_variable);
}

/* RECLAIM-PHRASE-RULE-COMPLETIONS */
Object reclaim_phrase_rule_completions(phrase_rule_completions)
    Object phrase_rule_completions;
{
    Object phrase_rule_completion, ab_loop_list_;

    x_note_fn_call(78,126);
    phrase_rule_completion = Nil;
    ab_loop_list_ = phrase_rule_completions;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    phrase_rule_completion = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_phrase_rule_completion_1(phrase_rule_completion);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(phrase_rule_completions);
}

Object Batch_parsing_engaged_p = UNBOUND;

/* ADD-GRAMMAR-RULES-FUNCTION */
Object add_grammar_rules_function(grammar_rules)
    Object grammar_rules;
{
    Object grammar_rule, ab_loop_list_, grammar_name, current_grammar;
    Object current_indicator_for_category_of_symbol_token;
    Object current_indicator_for_category_of_this_name, ab_loop_list__1;
    Declare_special(3);

    x_note_fn_call(78,127);
    if (Batch_parsing_engaged_p) {
	grammar_rule = Nil;
	ab_loop_list_ = grammar_rules;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	grammar_rule = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_batch_grammar_rule(grammar_rule);
	goto next_loop;
      end_loop:;
    }
    grammar_name = Nil;
    ab_loop_list_ = Names_of_grammars_to_add_rules_to;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    grammar_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    current_grammar = get_gensym_grammar(grammar_name);
    PUSH_SPECIAL(Current_grammar,current_grammar,2);
      current_indicator_for_category_of_symbol_token = 
	      ISVREF(Current_grammar,(SI_Long)4L);
      PUSH_SPECIAL(Current_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
	      1);
	current_indicator_for_category_of_this_name = 
		ISVREF(Current_grammar,(SI_Long)3L);
	PUSH_SPECIAL(Current_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
		0);
	  grammar_rule = Nil;
	  ab_loop_list__1 = grammar_rules;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_2;
	  grammar_rule = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  add_grammar_rule_1(grammar_rule);
	  goto next_loop_2;
	end_loop_2:;
	  if (ISVREF(Current_grammar,(SI_Long)8L))
	      compile_grammar(Current_grammar);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* ADD-GRAMMAR-RULE */
Object add_grammar_rule(grammar_rule)
    Object grammar_rule;
{
    Object grammar_name, ab_loop_list_, current_grammar;
    Object current_indicator_for_category_of_symbol_token;
    Object current_indicator_for_category_of_this_name;
    Declare_special(3);

    x_note_fn_call(78,128);
    if (Batch_parsing_engaged_p)
	add_batch_grammar_rule(grammar_rule);
    grammar_name = Nil;
    ab_loop_list_ = Names_of_grammars_to_add_rules_to;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    grammar_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    current_grammar = get_gensym_grammar(grammar_name);
    PUSH_SPECIAL(Current_grammar,current_grammar,2);
      current_indicator_for_category_of_symbol_token = 
	      ISVREF(Current_grammar,(SI_Long)4L);
      PUSH_SPECIAL(Current_indicator_for_category_of_symbol_token,current_indicator_for_category_of_symbol_token,
	      1);
	current_indicator_for_category_of_this_name = 
		ISVREF(Current_grammar,(SI_Long)3L);
	PUSH_SPECIAL(Current_indicator_for_category_of_this_name,current_indicator_for_category_of_this_name,
		0);
	  add_grammar_rule_1(grammar_rule);
	  if (ISVREF(Current_grammar,(SI_Long)8L))
	      compile_grammar(Current_grammar);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* PHRASE-FLATTEN-TREE */
Object phrase_flatten_tree(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(78,129);
    if ( !TRUEP(tree))
	return VALUES_1(Nil);
    else if (ATOM(tree))
	return phrase_cons(tree,Nil);
    else {
	temp = phrase_flatten_tree(M_CAR(tree));
	return VALUES_1(nconc2(temp,phrase_flatten_tree(M_CDR(tree))));
    }
}

/* ADD-BATCH-GRAMMAR-RULE */
Object add_batch_grammar_rule(rule)
    Object rule;
{
    x_note_fn_call(78,130);
    return VALUES_1(Nil);
}

/* INSTANCE-RULE-P */
Object instance_rule_p(grammar_rule)
    Object grammar_rule;
{
    Object temp;

    x_note_fn_call(78,131);
    temp = SECOND(grammar_rule);
    temp = ATOM(temp) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = SECOND(grammar_rule);
	return VALUES_1(EQ(CAR(temp),Qquote) ? T : Nil);
    }
}

/* ADD-GRAMMAR-RULE-1 */
Object add_grammar_rule_1(grammar_rule)
    Object grammar_rule;
{
    Object category, instance_or_phrase_rule_elements, transformation_list;

    x_note_fn_call(78,132);
    process_grammar_rule_for_development_if_appropriate(grammar_rule);
    category = get_or_make_category_for_category_symbol(FIRST(grammar_rule));
    instance_or_phrase_rule_elements = SECOND(grammar_rule);
    transformation_list = CDDR(grammar_rule);
    if (instance_rule_p(grammar_rule))
	return add_grammar_instance_rule(category,
		instance_or_phrase_rule_elements,transformation_list);
    else
	return add_grammar_phrase_rule(category,
		instance_or_phrase_rule_elements,transformation_list);
}

/* ADD-GRAMMAR-INSTANCE-RULE */
Object add_grammar_instance_rule(category,instance_rule_element,
	    transformation_list)
    Object category, instance_rule_element, transformation_list;
{
    Object category_for_instance_qm, token, category_of_token_qm;
    Object svref_new_value, l, temp;

    x_note_fn_call(78,133);
    if (SYMBOLP(instance_rule_element))
	category_for_instance_qm = 
		get_or_make_category_for_category_symbol(instance_rule_element);
    else {
	token = SECOND(instance_rule_element);
	category_of_token_qm = get_category_of_token(token);
	if ( !TRUEP(category_of_token_qm) &&  !TRUEP(transformation_list)) {
	    set_category_of_token(token,category);
	    svref_new_value = nconc2(ISVREF(category,(SI_Long)9L),
		    gensym_cons_1(token,Nil));
	    SVREF(category,FIX((SI_Long)9L)) = svref_new_value;
	    category_for_instance_qm = Nil;
	}
	else if (category_of_token_qm && 
		SIMPLE_VECTOR_P(category_of_token_qm) && 
		EQ(ISVREF(category_of_token_qm,(SI_Long)0L),
		Qg2_defstruct_structure_name_category_for_token_g2_struct))
	    category_for_instance_qm = category_of_token_qm;
	else if (category_of_token_qm &&  !EQ(ISVREF(category_of_token_qm,
		(SI_Long)7L),category) || transformation_list)
	    category_for_instance_qm = 
		    make_category_for_token(SECOND(instance_rule_element),
		    category_of_token_qm);
	else
	    category_for_instance_qm = Qnil;
    }
    if (category_for_instance_qm) {
	l = ISVREF(category,(SI_Long)8L);
	if ( !TRUEP(l)) {
	    svref_new_value = gensym_cons_1(category_for_instance_qm,Nil);
	    SVREF(category,FIX((SI_Long)8L)) = svref_new_value;
	}
	else if ( !TRUEP(memq_function(category_for_instance_qm,l)))
	    nconc2(l,gensym_cons_1(category_for_instance_qm,Nil));
	l = ISVREF(category,(SI_Long)10L);
	if ( !TRUEP(l)) {
	    svref_new_value = gensym_cons_1(category_for_instance_qm,Nil);
	    SVREF(category,FIX((SI_Long)10L)) = svref_new_value;
	}
	else if ( !TRUEP(memq_function(category_for_instance_qm,l)))
	    nconc2(l,gensym_cons_1(category_for_instance_qm,Nil));
	l = ISVREF(category_for_instance_qm,(SI_Long)2L);
	if ( !TRUEP(l)) {
	    svref_new_value = gensym_cons_1(category,Nil);
	    SVREF(category_for_instance_qm,FIX((SI_Long)2L)) = svref_new_value;
	}
	else if ( !TRUEP(memq_function(category,l)))
	    nconc2(l,gensym_cons_1(category,Nil));
	temp = ISVREF(category_for_instance_qm,(SI_Long)3L);
	svref_new_value = 
		set_nth_element_of_variable_length_grammar_list(3,temp,
		position(2,category,ISVREF(category_for_instance_qm,
		(SI_Long)2L)),transformation_list);
	return VALUES_1(SVREF(category_for_instance_qm,FIX((SI_Long)3L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* ADD-GRAMMAR-PHRASE-RULE */
Object add_grammar_phrase_rule(phrase_category,phrase_rule_elements,
	    transformation_list)
    Object phrase_category, phrase_rule_elements, transformation_list;
{
    Object phrase_rule_elements_old_value, temp;
    Object category_for_first_rule_element;
    Object phrase_rule_completions_for_each_category_this_may_begin;
    Object category_for_rule_element, second_rule_element_qm;
    Object existing_phrase_rule_completions, phrase_rule_completion;
    Object ab_loop_iter_flag_, l, svref_new_value, phrase_rule_completions;
    Object ab_loop_list_, existing_phrase_rule_completion;
    Object phrase_rule_completion_1, listed_new_phrase_rule_completion;

    x_note_fn_call(78,134);
    phrase_rule_elements_old_value = phrase_rule_elements;
    temp = FIRST(phrase_rule_elements_old_value);
    phrase_rule_elements = REST(phrase_rule_elements_old_value);
    category_for_first_rule_element = 
	    get_or_make_category_for_rule_element(temp);
    phrase_rule_completions_for_each_category_this_may_begin = 
	    ISVREF(category_for_first_rule_element,(SI_Long)4L);
    category_for_rule_element = Nil;
    second_rule_element_qm = T;
    existing_phrase_rule_completions = Nil;
    phrase_rule_completion = Nil;
    ab_loop_iter_flag_ = T;
    l = ISVREF(phrase_category,(SI_Long)10L);
    if ( !TRUEP(l)) {
	svref_new_value = gensym_cons_1(category_for_first_rule_element,Nil);
	SVREF(phrase_category,FIX((SI_Long)10L)) = svref_new_value;
    }
    else if ( !TRUEP(memq_function(category_for_first_rule_element,l)))
	nconc2(l,gensym_cons_1(category_for_first_rule_element,Nil));
  next_loop:
    phrase_rule_elements_old_value = phrase_rule_elements;
    temp = FIRST(phrase_rule_elements_old_value);
    phrase_rule_elements = REST(phrase_rule_elements_old_value);
    category_for_rule_element = get_or_make_category_for_rule_element(temp);
    if ( !TRUEP(ab_loop_iter_flag_))
	second_rule_element_qm = Nil;
    if (second_rule_element_qm) {
	phrase_rule_completions = Nil;
	ab_loop_list_ = 
		phrase_rule_completions_for_each_category_this_may_begin;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	phrase_rule_completions = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(CAR(phrase_rule_completions),(SI_Long)2L),
		phrase_category)) {
	    existing_phrase_rule_completions = phrase_rule_completions;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop:
	existing_phrase_rule_completions = Qnil;
      end_1:;
    }
    else
	existing_phrase_rule_completions = ISVREF(phrase_rule_completion,
		(SI_Long)4L);
    existing_phrase_rule_completion = Nil;
    ab_loop_list_ = existing_phrase_rule_completions;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    existing_phrase_rule_completion = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(existing_phrase_rule_completion,(SI_Long)1L),
	    category_for_rule_element)) {
	phrase_rule_completion_1 = existing_phrase_rule_completion;
	goto end_2;
    }
    goto next_loop_2;
  end_loop_1:
    phrase_rule_completion_1 = Qnil;
  end_2:;
    if (phrase_rule_completion_1)
	phrase_rule_completion = phrase_rule_completion_1;
    else {
	listed_new_phrase_rule_completion = 
		gensym_cons_1(make_phrase_rule_completion_1(phrase_category,
		category_for_rule_element,Nil),Nil);
	if (EQ(ISVREF(phrase_category,(SI_Long)11L),Qnot_a_result_category))
	    SVREF(phrase_category,FIX((SI_Long)11L)) = Nil;
	if (existing_phrase_rule_completions)
	    nconc2(existing_phrase_rule_completions,
		    listed_new_phrase_rule_completion);
	else if (second_rule_element_qm) {
	    svref_new_value = 
		    nconc2(phrase_rule_completions_for_each_category_this_may_begin,
		    gensym_cons_1(listed_new_phrase_rule_completion,Nil));
	    SVREF(category_for_first_rule_element,FIX((SI_Long)4L)) = 
		    svref_new_value;
	}
	else
	    SVREF(phrase_rule_completion,FIX((SI_Long)4L)) = 
		    listed_new_phrase_rule_completion;
	phrase_rule_completion = CAR(listed_new_phrase_rule_completion);
    }
    if ( !TRUEP(phrase_rule_elements))
	goto end_loop_2;
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop_2:
    svref_new_value = transformation_list;
    if (svref_new_value);
    else
	svref_new_value = T;
    SVREF(phrase_rule_completion,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(phrase_rule_completion);
    return VALUES_1(Qnil);
}

/* PROCESS-GRAMMAR-RULE-FOR-DEVELOPMENT-IF-APPROPRIATE */
Object process_grammar_rule_for_development_if_appropriate(grammar_rule)
    Object grammar_rule;
{
    x_note_fn_call(78,135);
    return VALUES_1(grammar_rule);
}

Object The_type_description_of_incomplete_phrase = UNBOUND;

Object Chain_of_available_incomplete_phrases = UNBOUND;

Object Incomplete_phrase_count = UNBOUND;

/* INCOMPLETE-PHRASE-STRUCTURE-MEMORY-USAGE */
Object incomplete_phrase_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(78,136);
    temp = Incomplete_phrase_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INCOMPLETE-PHRASE-COUNT */
Object outstanding_incomplete_phrase_count()
{
    Object def_structure_incomplete_phrase_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(78,137);
    gensymed_symbol = IFIX(Incomplete_phrase_count);
    def_structure_incomplete_phrase_variable = 
	    Chain_of_available_incomplete_phrases;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_incomplete_phrase_variable))
	goto end_loop;
    def_structure_incomplete_phrase_variable = 
	    ISVREF(def_structure_incomplete_phrase_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INCOMPLETE-PHRASE-1 */
Object reclaim_incomplete_phrase_1(incomplete_phrase)
    Object incomplete_phrase;
{
    Object svref_new_value;

    x_note_fn_call(78,138);
    inline_note_reclaim_cons(incomplete_phrase,Nil);
    svref_new_value = Chain_of_available_incomplete_phrases;
    SVREF(incomplete_phrase,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_incomplete_phrases = incomplete_phrase;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INCOMPLETE-PHRASE */
Object reclaim_structure_for_incomplete_phrase(incomplete_phrase)
    Object incomplete_phrase;
{
    x_note_fn_call(78,139);
    return reclaim_incomplete_phrase_1(incomplete_phrase);
}

static Object Qg2_defstruct_structure_name_incomplete_phrase_g2_struct;  /* g2-defstruct-structure-name::incomplete-phrase-g2-struct */

/* MAKE-PERMANENT-INCOMPLETE-PHRASE-STRUCTURE-INTERNAL */
Object make_permanent_incomplete_phrase_structure_internal()
{
    Object def_structure_incomplete_phrase_variable;
    Object incomplete_phrase_count_new_value;
    Object defstruct_g2_incomplete_phrase_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(78,140);
    def_structure_incomplete_phrase_variable = Nil;
    incomplete_phrase_count_new_value = FIXNUM_ADD1(Incomplete_phrase_count);
    Incomplete_phrase_count = incomplete_phrase_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_incomplete_phrase_variable = Nil;
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
	defstruct_g2_incomplete_phrase_variable = the_array;
	SVREF(defstruct_g2_incomplete_phrase_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_incomplete_phrase_g2_struct;
	def_structure_incomplete_phrase_variable = 
		defstruct_g2_incomplete_phrase_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_incomplete_phrase_variable);
}

/* MAKE-INCOMPLETE-PHRASE-STRUCTURE-1 */
Object make_incomplete_phrase_structure_1(phrase_rule_completions,
	    incomplete_stack_of_constituents,
	    incomplete_phrases_as_of_the_beginning_of_this,
	    incomplete_phrase_link_qm)
    Object phrase_rule_completions, incomplete_stack_of_constituents;
    Object incomplete_phrases_as_of_the_beginning_of_this;
    Object incomplete_phrase_link_qm;
{
    Object def_structure_incomplete_phrase_variable;

    x_note_fn_call(78,141);
    def_structure_incomplete_phrase_variable = 
	    Chain_of_available_incomplete_phrases;
    if (def_structure_incomplete_phrase_variable) {
	Chain_of_available_incomplete_phrases = 
		ISVREF(def_structure_incomplete_phrase_variable,(SI_Long)0L);
	SVREF(def_structure_incomplete_phrase_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_incomplete_phrase_g2_struct;
    }
    else
	def_structure_incomplete_phrase_variable = 
		make_permanent_incomplete_phrase_structure_internal();
    inline_note_allocate_cons(def_structure_incomplete_phrase_variable,Nil);
    SVREF(def_structure_incomplete_phrase_variable,FIX((SI_Long)1L)) = 
	    phrase_rule_completions;
    SVREF(def_structure_incomplete_phrase_variable,FIX((SI_Long)2L)) = 
	    incomplete_stack_of_constituents;
    SVREF(def_structure_incomplete_phrase_variable,FIX((SI_Long)3L)) = 
	    incomplete_phrases_as_of_the_beginning_of_this;
    SVREF(def_structure_incomplete_phrase_variable,FIX((SI_Long)4L)) = 
	    incomplete_phrase_link_qm;
    return VALUES_1(def_structure_incomplete_phrase_variable);
}

/* RECLAIM-CHAIN-OF-INCOMPLETE-PHRASES */
Object reclaim_chain_of_incomplete_phrases(chain_of_incomplete_phrases_qm)
    Object chain_of_incomplete_phrases_qm;
{
    Object incomplete_phrase_qm;

    x_note_fn_call(78,142);
    incomplete_phrase_qm = Nil;
  next_loop:
    incomplete_phrase_qm = chain_of_incomplete_phrases_qm;
    if ( !TRUEP(incomplete_phrase_qm))
	goto end_loop;
    chain_of_incomplete_phrases_qm = ISVREF(incomplete_phrase_qm,(SI_Long)4L);
    reclaim_incomplete_phrase_1(incomplete_phrase_qm);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object Incomplete_phrases_at_frontier = UNBOUND;

Object The_transform = UNBOUND;

/* TRANSFORM-CONSTITUENT-COMPLETELY */
Object transform_constituent_completely(constituent,subcategory_path,
	    category_of_completion,number_of_transforms)
    Object constituent, subcategory_path, category_of_completion;
    Object number_of_transforms;
{
    Object transformed_constituent, category, next_category;
    Object more_general_catgory_index, the_transform, more_general_category;
    Object ab_loop_list_, ab_loop_iter_flag_;
    SI_Long i, ab_loop_bind_, i_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(78,143);
    transformed_constituent = constituent;
    i = (SI_Long)1L;
    ab_loop_bind_ = IFIX(number_of_transforms);
    category = Nil;
    next_category = Nil;
    more_general_catgory_index = Nil;
    the_transform = Nil;
    PUSH_SPECIAL(The_transform,the_transform,0);
    next_loop:
      if (i > ab_loop_bind_)
	  goto end_loop;
      category = ISVREF(subcategory_path,i);
      next_category = i == IFIX(number_of_transforms) ? 
	      category_of_completion : ISVREF(subcategory_path,i + 
	      (SI_Long)1L);
      more_general_category = Nil;
      ab_loop_list_ = ISVREF(category,(SI_Long)2L);
      i_1 = (SI_Long)0L;
      ab_loop_iter_flag_ = T;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      more_general_category = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if ( !TRUEP(ab_loop_iter_flag_))
	  i_1 = i_1 + (SI_Long)1L;
      if (EQ(more_general_category,next_category)) {
	  more_general_catgory_index = FIX(i_1);
	  goto end_1;
      }
      ab_loop_iter_flag_ = Nil;
      goto next_loop_1;
    end_loop_1:
      more_general_catgory_index = Qnil;
    end_1:;
      The_transform = more_general_catgory_index ? 
	      nth(more_general_catgory_index,ISVREF(category,(SI_Long)3L)) 
	      : Qnil;
      transformed_constituent = The_transform ? 
	      transform_constituent(transformed_constituent,The_transform) 
	      : transformed_constituent;
      if (EQ(transformed_constituent,Bad_phrase)) {
	  result = VALUES_1(Bad_phrase);
	  POP_SPECIAL();
	  goto end_transform_constituent_completely;
      }
      i = i + (SI_Long)1L;
      goto next_loop;
    end_loop:;
    POP_SPECIAL();
    result = VALUES_1(transformed_constituent);
  end_transform_constituent_completely:
    return result;
}

static Object Qproc_compound_statement;  /* proc-compound-statement */

static Object Qproc_simple_statement;  /* proc-simple-statement */

static Object Qunique_literal;     /* unique-literal */

/* HAVE-CONSTITUENT-TO-ANNOTATE-P */
Object have_constituent_to_annotate_p(constituent,category_of_constituent)
    Object constituent, category_of_constituent;
{
    Object temp;

    x_note_fn_call(78,144);
    if (CONSP(constituent) &&  !EQ(ISVREF(category_of_constituent,
	    (SI_Long)7L),Qproc_compound_statement)) {
	temp = subcategoryp(category_of_constituent,
		get(Qproc_simple_statement,
		Current_indicator_for_category_of_this_name,_));
	if (temp);
	else
	    temp = subcategoryp(category_of_constituent,
		    get(Qunique_literal,
		    Current_indicator_for_category_of_this_name,_));
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

Object Generate_source_annotation_info = UNBOUND;

static Object Qprocedure_definition;  /* procedure-definition */

static Object Qprocedure;          /* procedure */

/* MAYBE-ANNOTATE-CONSTITUENT */
Object maybe_annotate_constituent(constituent,category_of_constituent)
    Object constituent, category_of_constituent;
{
    Object frame_qm, temp_1, position_for_annotation_hash, annotation;
    char temp;

    x_note_fn_call(78,145);
    if (Generate_source_annotation_info) {
	if (EQ(ISVREF(Current_edit_state,(SI_Long)5L),Qprocedure_definition)) {
	    frame_qm = ISVREF(Current_edit_state,(SI_Long)3L);
	    temp = frame_qm &&  
		    !TRUEP(frame_has_been_reprocessed_p_function(frame_qm,
		    ISVREF(Current_edit_state,(SI_Long)4L))) ? 
		    TRUEP(of_class_p_function(frame_qm,Qprocedure)) : 
		    TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(have_constituent_to_annotate_p(constituent,
	    category_of_constituent)) : TRUEP(Nil)) {
	temp_1 = ISVREF(Current_edit_state,(SI_Long)29L);
	position_for_annotation_hash = CAR(temp_1);
	if (position_for_annotation_hash) {
	    annotation = 
		    make_annotation_1(FIRST(position_for_annotation_hash),
		    SECOND(position_for_annotation_hash));
	    set_current_annotation_context(constituent,annotation);
	}
    }
    return VALUES_1(Nil);
}

/* ADD-CONSTITUENT-TO-INCOMPLETE-PHRASES */
Object add_constituent_to_incomplete_phrases(constituent,
	    category_of_constituent,incomplete_phrases)
    Object constituent, category_of_constituent, incomplete_phrases;
{
    Object incomplete_phrase, ab_loop_list_, phrase_rule_completion;
    Object ab_loop_list__1, transformation_list_for_constituent_or_t_qm;
    Object transformed_constituent_or_bad_phrase, transformation_list_or_t_qm;
    Object second_transformed_constituent_or_bad_phrase, info, e;

    x_note_fn_call(78,146);
    if ( !EQ(constituent,Bad_phrase))
	maybe_annotate_constituent(constituent,category_of_constituent);
    incomplete_phrase = Nil;
    ab_loop_list_ = incomplete_phrases;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    incomplete_phrase = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    phrase_rule_completion = Nil;
    ab_loop_list__1 = ISVREF(incomplete_phrase,(SI_Long)1L);
    transformation_list_for_constituent_or_t_qm = Nil;
    transformed_constituent_or_bad_phrase = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    phrase_rule_completion = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    transformation_list_for_constituent_or_t_qm = 
	    subcategoryp(category_of_constituent,
	    ISVREF(phrase_rule_completion,(SI_Long)1L));
    transformed_constituent_or_bad_phrase = 
	    transformation_list_for_constituent_or_t_qm ? 
	    transform_constituent_for_add_constituent_to_incomplete_phrase(constituent,
	    category_of_constituent,phrase_rule_completion,
	    transformation_list_for_constituent_or_t_qm) : Bad_phrase;
    if ( !EQ(transformed_constituent_or_bad_phrase,Bad_phrase)) {
	transformation_list_or_t_qm = ISVREF(phrase_rule_completion,
		(SI_Long)3L);
	if (transformation_list_or_t_qm) {
	    second_transformed_constituent_or_bad_phrase = 
		    transform_constituent_for_incomplete_phrase(transformed_constituent_or_bad_phrase,
		    transformation_list_or_t_qm,ISVREF(incomplete_phrase,
		    (SI_Long)2L));
	    if ( !EQ(second_transformed_constituent_or_bad_phrase,Bad_phrase))
		add_constituent_to_incomplete_phrases(second_transformed_constituent_or_bad_phrase,
			ISVREF(phrase_rule_completion,(SI_Long)2L),
			ISVREF(incomplete_phrase,(SI_Long)3L));
	}
	add_constituent_to_incomplete_phrase_per_transformation(incomplete_phrase,
		ISVREF(phrase_rule_completion,(SI_Long)4L),
		transformed_constituent_or_bad_phrase);
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:;
    info = 
	    phrase_rule_completions_addable_to_some_incomplete_phrase(category_of_constituent,
	    incomplete_phrases);
    begin_phrases_addable_to_some_incomplete_phrase_with_agenda(info,
	    constituent,incomplete_phrases);
    e = Nil;
    ab_loop_list_ = info;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    e = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(e);
    goto next_loop_2;
  end_loop_2:;
    return reclaim_gensym_list_1(info);
}

/* ADD-CONSTITUENT-TO-INCOMPLETE-PHRASE-PER-TRANSFORMATION */
Object add_constituent_to_incomplete_phrase_per_transformation(incomplete_phrase,
	    phrase_rule_completions_past_next_constituent,
	    transformed_constituent_or_bad_phrase)
    Object incomplete_phrase, phrase_rule_completions_past_next_constituent;
    Object transformed_constituent_or_bad_phrase;
{
    Object stack, beginning_phrases, svref_arg_1, temp;

    x_note_fn_call(78,147);
    stack = ISVREF(incomplete_phrase,(SI_Long)2L);
    beginning_phrases = ISVREF(incomplete_phrase,(SI_Long)3L);
    if (phrase_rule_completions_past_next_constituent &&  
	    !TRUEP(phrases_addable_to_some_incomplete_phrase_inner_2(phrase_rule_completions_past_next_constituent,
	    beginning_phrases,stack,transformed_constituent_or_bad_phrase))) {
	svref_arg_1 = Current_edit_state;
	temp = 
		make_incomplete_phrase_structure_1(phrase_rule_completions_past_next_constituent,
		phrase_cons(transformed_constituent_or_bad_phrase,stack),
		beginning_phrases,ISVREF(Current_edit_state,(SI_Long)36L));
	SVREF(svref_arg_1,FIX((SI_Long)36L)) = temp;
	Incomplete_phrases_at_frontier = phrase_cons(temp,
		Incomplete_phrases_at_frontier);
	return VALUES_1(Incomplete_phrases_at_frontier);
    }
    else
	return VALUES_1(Nil);
}

/* BEGIN-PHRASES-ADDABLE-TO-SOME-INCOMPLETE-PHRASE-WITH-AGENDA */
Object begin_phrases_addable_to_some_incomplete_phrase_with_agenda(info,
	    constituent,incomplete_phrases)
    Object info, constituent, incomplete_phrases;
{
    Object category_or_category_plus_transformation_list, completions;
    Object ab_loop_list_, ab_loop_desetq_, transformation_considered_yet_qm;
    Object constituent_or_bad_phrase, phrase_rule_completions, ab_loop_list__1;
    Object temp_1, svref_arg_1;
    char temp;

    x_note_fn_call(78,148);
    category_or_category_plus_transformation_list = Nil;
    completions = Nil;
    ab_loop_list_ = info;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    category_or_category_plus_transformation_list = CAR(ab_loop_desetq_);
    completions = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    transformation_considered_yet_qm = Nil;
    constituent_or_bad_phrase = Nil;
    phrase_rule_completions = Nil;
    ab_loop_list__1 = completions;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    phrase_rule_completions = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp = 
	    TRUEP(phrases_addable_to_some_incomplete_phrase_inner_2(phrase_rule_completions,
	    incomplete_phrases,Nil,constituent));
    if (temp);
    else {
	if (transformation_considered_yet_qm)
	    temp_1 = constituent_or_bad_phrase;
	else {
	    transformation_considered_yet_qm = T;
	    constituent_or_bad_phrase = 
		    CONSP(category_or_category_plus_transformation_list) ? 
		    transform_constituent(constituent,
		    CDR(category_or_category_plus_transformation_list)) : 
		    constituent;
	    temp_1 = constituent_or_bad_phrase;
	}
	temp = EQ(temp_1,Bad_phrase);
    }
    if ( !temp) {
	svref_arg_1 = Current_edit_state;
	temp_1 = 
		make_incomplete_phrase_structure_1(phrase_rule_completions,
		phrase_cons(constituent_or_bad_phrase,Nil),
		incomplete_phrases,ISVREF(Current_edit_state,(SI_Long)36L));
	SVREF(svref_arg_1,FIX((SI_Long)36L)) = temp_1;
	Incomplete_phrases_at_frontier = phrase_cons(temp_1,
		Incomplete_phrases_at_frontier);
    }
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object list_constant;       /* # */

/* PHRASE-RULE-COMPLETIONS-ADDABLE-TO-SOME-INCOMPLETE-PHRASE */
Object phrase_rule_completions_addable_to_some_incomplete_phrase(category_of_constituent,
	    incomplete_phrases)
    Object category_of_constituent, incomplete_phrases;
{
    Object agenda, agenda_item_qm, ab_loop_list_;
    Object category_or_category_plus_transformation_list;
    Object category_of_agenda_constituent, completions_list, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(78,149);
    agenda = ISVREF(category_of_constituent,(SI_Long)5L);
    agenda_item_qm = Nil;
    ab_loop_list_ = LISTP(agenda) ? agenda : list_constant;
    category_or_category_plus_transformation_list = Nil;
    category_of_agenda_constituent = Nil;
    completions_list = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    agenda_item_qm = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = agenda_item_qm;
    if (temp);
    else
	temp = agenda;
    category_or_category_plus_transformation_list = temp;
    category_of_agenda_constituent = 
	    ATOM(category_or_category_plus_transformation_list) ? 
	    category_or_category_plus_transformation_list : 
	    CAR(category_or_category_plus_transformation_list);
    completions_list = 
	    phrase_rule_completions_addable_to_some_incomplete_phrase_1(category_of_agenda_constituent,
	    incomplete_phrases);
    if (completions_list) {
	ab_loopvar__2 = 
		gensym_cons_1(gensym_cons_1(category_or_category_plus_transformation_list,
		completions_list),Nil);
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
    return VALUES_1(temp);
}

/* PHRASE-RULE-COMPLETIONS-ADDABLE-TO-SOME-INCOMPLETE-PHRASE-1 */
Object phrase_rule_completions_addable_to_some_incomplete_phrase_1(category_of_agenda_constituent,
	    incomplete_phrases)
    Object category_of_agenda_constituent, incomplete_phrases;
{
    Object phrase_rule_completions, ab_loop_list_;
    Object category_for_completed_phrase;
    Object categories_completed_phrase_can_be_or_begin, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, incomplete_phrase, ab_loop_list__1;
    Object ab_loop_it_, phrase_rule_completion, ab_loop_list__2;
    Object category_of_next_constituent, temp;
    char temp_1;

    x_note_fn_call(78,150);
    phrase_rule_completions = Nil;
    ab_loop_list_ = ISVREF(category_of_agenda_constituent,(SI_Long)4L);
    category_for_completed_phrase = Nil;
    categories_completed_phrase_can_be_or_begin = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    phrase_rule_completions = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_for_completed_phrase = ISVREF(CAR(phrase_rule_completions),
	    (SI_Long)2L);
    categories_completed_phrase_can_be_or_begin = 
	    ISVREF(category_for_completed_phrase,(SI_Long)11L);
    incomplete_phrase = Nil;
    ab_loop_list__1 = incomplete_phrases;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    incomplete_phrase = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    phrase_rule_completion = Nil;
    ab_loop_list__2 = ISVREF(incomplete_phrase,(SI_Long)1L);
    category_of_next_constituent = Nil;
    ab_loop_it_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list__2))
	goto end_loop_2;
    phrase_rule_completion = M_CAR(ab_loop_list__2);
    ab_loop_list__2 = M_CDR(ab_loop_list__2);
    category_of_next_constituent = ISVREF(phrase_rule_completion,(SI_Long)1L);
    temp = EQ(category_of_next_constituent,category_for_completed_phrase) ?
	     T : Nil;
    if (temp);
    else
	temp = SIMPLE_VECTOR_P(category_of_next_constituent) && 
		EQ(ISVREF(category_of_next_constituent,(SI_Long)0L),
		Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct) 
		? category_set_memq(category_of_next_constituent,
		categories_completed_phrase_can_be_or_begin) : Qnil;
    ab_loop_it_ = temp;
    if (ab_loop_it_)
	goto end_1;
    goto next_loop_2;
  end_loop_2:
    ab_loop_it_ = Qnil;
  end_1:;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_2;
    }
    goto next_loop_1;
  end_loop_1:
    temp_1 = TRUEP(Qnil);
  end_2:;
    if (temp_1) {
	ab_loopvar__2 = gensym_cons_1(phrase_rule_completions,Nil);
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

/* PHRASES-ADDABLE-TO-SOME-INCOMPLETE-PHRASE-INNER-2 */
Object phrases_addable_to_some_incomplete_phrase_inner_2(phrase_rule_completions,
	    incomplete_phrases,more_constituents,constituent)
    Object phrase_rule_completions, incomplete_phrases, more_constituents;
    Object constituent;
{
    Object incomplete_phrase_at_frontier, ab_loop_list_, ab_loop_it_, temp;
    char temp_1;

    x_note_fn_call(78,151);
    incomplete_phrase_at_frontier = Nil;
    ab_loop_list_ = Incomplete_phrases_at_frontier;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    incomplete_phrase_at_frontier = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(incomplete_phrase_at_frontier,(SI_Long)1L),
	    phrase_rule_completions) && 
	    EQ(ISVREF(incomplete_phrase_at_frontier,(SI_Long)3L),
	    incomplete_phrases)) {
	temp = ISVREF(incomplete_phrase_at_frontier,(SI_Long)2L);
	temp_1 = EQ(CDR(temp),more_constituents);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	temp = ISVREF(incomplete_phrase_at_frontier,(SI_Long)2L);
	temp = CAR(temp);
	ab_loop_it_ = EQUAL(temp,constituent) ? T : Nil;
    }
    else
	ab_loop_it_ = Nil;
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

/* TRANSFORM-CONSTITUENT-FOR-ADD-CONSTITUENT-TO-INCOMPLETE-PHRASE */
Object transform_constituent_for_add_constituent_to_incomplete_phrase(constituent,
	    category_of_constituent,phrase_rule_completion,
	    transformation_list_for_constituent_or_t_qm)
    Object constituent, category_of_constituent, phrase_rule_completion;
    Object transformation_list_for_constituent_or_t_qm;
{
    Object svref_arg_1, number_of_category_generalizations_qm;
    SI_Long i;

    x_note_fn_call(78,152);
    i = (SI_Long)0L;
  next_loop:
    if (i >= IFIX(Max_instance_rule_chaining))
	goto end_loop;
    svref_arg_1 = Current_subcategory_path;
    ISVREF(svref_arg_1,i) = Nil;
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    set_current_subcategory_path(category_of_constituent,
	    ISVREF(phrase_rule_completion,(SI_Long)1L));
    number_of_category_generalizations_qm = 
	    Currently_tracking_subcategory_path_max;
    if (EQ(transformation_list_for_constituent_or_t_qm,T))
	return VALUES_1(constituent);
    else if (number_of_category_generalizations_qm && 
	    IFIX(number_of_category_generalizations_qm) > (SI_Long)1L)
	return transform_constituent_completely(constituent,
		Current_subcategory_path,ISVREF(phrase_rule_completion,
		(SI_Long)1L),number_of_category_generalizations_qm);
    else
	return transform_constituent(constituent,
		transformation_list_for_constituent_or_t_qm);
}

/* TRANSFORM-CONSTITUENT-FOR-INCOMPLETE-PHRASE */
Object transform_constituent_for_incomplete_phrase(transformed_constituent,
	    transformation_list_or_t_qm,stack)
    Object transformed_constituent, transformation_list_or_t_qm, stack;
{
    Object initial_result, constituents, stack_old_value, temp;

    x_note_fn_call(78,153);
    if (EQ(transformed_constituent,Bad_phrase))
	return VALUES_1(Bad_phrase);
    else {
	if ( !EQ(transformation_list_or_t_qm,T) && 
		CAR(transformation_list_or_t_qm))
	    initial_result = 
		    make_constituent_per_template(CAR(transformation_list_or_t_qm),
		    stack,transformed_constituent,length(stack));
	else {
	    constituents = phrase_cons(transformed_constituent,Nil);
	  next_loop:
	    if ( !TRUEP(stack))
		goto end_loop;
	    stack_old_value = stack;
	    temp = FIRST(stack_old_value);
	    stack = REST(stack_old_value);
	    constituents = phrase_cons(temp,constituents);
	    goto next_loop;
	  end_loop:
	    initial_result = constituents;
	    goto end_1;
	    initial_result = Qnil;
	  end_1:;
	}
	if (EQ(transformation_list_or_t_qm,T) ||  
		!TRUEP(CDR(transformation_list_or_t_qm)))
	    return VALUES_1(initial_result);
	else
	    return perform_transformation_operations(initial_result,
		    CDR(transformation_list_or_t_qm));
    }
}

/* SET-UP-AGENDAS-OF-MORE-GENERAL-CATEGORIES-TO-SEARCH */
Object set_up_agendas_of_more_general_categories_to_search()
{
    Object category_symbol, ab_loop_list_, token;

    x_note_fn_call(78,154);
    category_symbol = Nil;
    ab_loop_list_ = ISVREF(Current_grammar,(SI_Long)7L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_up_agendas_1(get(category_symbol,
	    Current_indicator_for_category_of_this_name,_));
    goto next_loop;
  end_loop:;
    token = Nil;
    ab_loop_list_ = ISVREF(Current_grammar,(SI_Long)6L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    token = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    set_up_agendas_1(get_category_of_token(token));
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* SET-UP-AGENDAS-1 */
Object set_up_agendas_1(category)
    Object category;
{
    Object agenda, temp;
    char temp_1;

    x_note_fn_call(78,155);
    reclaim_agenda_of_more_general_categories(ISVREF(category,(SI_Long)5L));
    SVREF(category,FIX((SI_Long)5L)) = Nil;
    agenda = get_more_general_categories_and_transformations(category);
    if ( !TRUEP(agenda))
	temp = Nil;
    else {
	if ( !TRUEP(CDR(agenda))) {
	    temp = CAR(agenda);
	    temp_1 = ATOM(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = CAR(agenda);
	    M_CAR(agenda) = Nil;
	    reclaim_gensym_cons_1(agenda);
	}
	else
	    temp = agenda;
    }
    return VALUES_1(SVREF(category,FIX((SI_Long)5L)) = temp);
}

Object Current_agenda_accumulating = UNBOUND;

/* GET-MORE-GENERAL-CATEGORIES-AND-TRANSFORMATIONS */
Object get_more_general_categories_and_transformations(category)
    Object category;
{
    Object current_agenda_accumulating;
    Declare_special(1);
    Object result;

    x_note_fn_call(78,156);
    current_agenda_accumulating = Nil;
    PUSH_SPECIAL(Current_agenda_accumulating,current_agenda_accumulating,0);
      get_more_general_categories_and_transformations_1(category,Nil);
      result = VALUES_1(Current_agenda_accumulating);
    POP_SPECIAL();
    return result;
}

/* GET-MORE-GENERAL-CATEGORIES-AND-TRANSFORMATIONS-1 */
Object get_more_general_categories_and_transformations_1(category,
	    transformation_list_for_constituent_qm)
    Object category, transformation_list_for_constituent_qm;
{
    Object agenda_item, ab_loop_list_, temp, more_general_category;
    Object corresponding_transformation_lists, ab_loop_iter_flag_, temp_2;
    char temp_1;

    x_note_fn_call(78,157);
    if (ISVREF(category,(SI_Long)4L)) {
	agenda_item = Nil;
	ab_loop_list_ = Current_agenda_accumulating;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	agenda_item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (ATOM(agenda_item))
	    temp =  !TRUEP(transformation_list_for_constituent_qm) ? 
		    (EQ(agenda_item,category) ? T : Nil) : Qnil;
	else {
	    if (transformation_list_for_constituent_qm && 
		    EQ(CAR(agenda_item),category)) {
		temp = CDR(agenda_item);
		temp = EQUAL(temp,transformation_list_for_constituent_qm) ?
			 T : Nil;
	    }
	    else
		temp = Nil;
	    if (temp);
	    else
		temp = Qnil;
	}
	if (temp) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	Current_agenda_accumulating = 
		gensym_cons_1(transformation_list_for_constituent_qm ? 
		gensym_cons_1(category,
		transformation_list_for_constituent_qm) : category,
		Current_agenda_accumulating);
    more_general_category = Nil;
    ab_loop_list_ = ISVREF(category,(SI_Long)2L);
    corresponding_transformation_lists = ISVREF(category,(SI_Long)3L);
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    more_general_category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	corresponding_transformation_lists = 
		CDR(corresponding_transformation_lists);
    temp = more_general_category;
    temp_2 = transformation_list_for_constituent_qm;
    if (temp_2);
    else
	temp_2 = CAR(corresponding_transformation_lists);
    get_more_general_categories_and_transformations_1(temp,temp_2);
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* RECLAIM-AGENDA-OF-MORE-GENERAL-CATEGORIES */
Object reclaim_agenda_of_more_general_categories(agenda)
    Object agenda;
{
    Object agenda_items, temp;

    x_note_fn_call(78,158);
    if (CONSP(agenda)) {
	agenda_items = agenda;
      next_loop:
	if ( !TRUEP(agenda_items))
	    goto end_loop;
	temp = CAR(agenda_items);
	if (CONSP(temp))
	    reclaim_gensym_cons_1(CAR(agenda_items));
	M_CAR(agenda_items) = Nil;
	agenda_items = M_CDR(agenda_items);
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(agenda);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qirrelevant;         /* irrelevant */

/* COMPILE-GRAMMAR */
Object compile_grammar(grammar)
    Object grammar;
{
    Object category_symbol, ab_loop_list_, category;

    x_note_fn_call(78,159);
    decache_all_strict_subcategory_infos();
    get_or_make_category_for_category_symbol(Qirrelevant);
    category_symbol = Nil;
    ab_loop_list_ = ISVREF(grammar,(SI_Long)7L);
    category = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category = get(category_symbol,
	    Current_indicator_for_category_of_this_name,_);
    if ( !EQ(ISVREF(category,(SI_Long)11L),Qnot_a_result_category)) {
	SVREF(category,FIX((SI_Long)11L)) = Nil;
	fill_in_categories_this_can_be_or_begin(get(category_symbol,
		Current_indicator_for_category_of_this_name,_),
		get(category_symbol,
		Current_indicator_for_category_of_this_name,_));
    }
    goto next_loop;
  end_loop:;
    set_up_agendas_of_more_general_categories_to_search();
    return VALUES_1(SVREF(grammar,FIX((SI_Long)8L)) = T);
}

/* FILL-IN-CATEGORIES-THIS-CAN-BE-OR-BEGIN */
Object fill_in_categories_this_can_be_or_begin(category,
	    category_for_category_symbol)
    Object category, category_for_category_symbol;
{
    Object svref_new_value, more_general_category, ab_loop_list_;
    Object phrase_rule_completions, category_for_completed_phrase;

    x_note_fn_call(78,160);
    if ( !TRUEP(category_set_memq(category,
	    ISVREF(category_for_category_symbol,(SI_Long)11L)))) {
	if ( !EQ(category,category_for_category_symbol)) {
	    svref_new_value = category_set_push_1(category,
		    ISVREF(category_for_category_symbol,(SI_Long)11L));
	    SVREF(category_for_category_symbol,FIX((SI_Long)11L)) = 
		    svref_new_value;
	}
	more_general_category = Nil;
	ab_loop_list_ = ISVREF(category,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	more_general_category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !EQ(more_general_category,category_for_category_symbol))
	    fill_in_categories_this_can_be_or_begin(more_general_category,
		    category_for_category_symbol);
	goto next_loop;
      end_loop:;
	phrase_rule_completions = Nil;
	ab_loop_list_ = ISVREF(category,(SI_Long)4L);
	category_for_completed_phrase = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	phrase_rule_completions = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	category_for_completed_phrase = 
		ISVREF(CAR(phrase_rule_completions),(SI_Long)2L);
	if ( !EQ(category_for_completed_phrase,category_for_category_symbol))
	    fill_in_categories_this_can_be_or_begin(category_for_completed_phrase,
		    category_for_category_symbol);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

Object Current_parsing_context_qm = UNBOUND;

/* INSTANCE-OF-CATEGORY-ACCEPTABLE-P */
Object instance_of_category_acceptable_p(category_symbol,
	    incomplete_phrases,category_is_a_token_p)
    Object category_symbol, incomplete_phrases, category_is_a_token_p;
{
    Object cursor_token, incomplete_phrases_at_frontier, category;
    Declare_special(1);
    Object result;

    x_note_fn_call(78,161);
    if ( !TRUEP(incomplete_phrases) && Current_parsing_context_qm) {
	cursor_token = 
		parsing_context_cursor_token_function(Current_parsing_context_qm);
	if (cursor_token)
	    incomplete_phrases = 
		    parsing_token_incomplete_phrases_function(cursor_token);
    }
    if (incomplete_phrases) {
	incomplete_phrases_at_frontier = Nil;
	category = category_is_a_token_p ? 
		get_category_of_token(category_symbol) : 
		get(category_symbol,
		Current_indicator_for_category_of_this_name,_);
	PUSH_SPECIAL(Incomplete_phrases_at_frontier,incomplete_phrases_at_frontier,
		0);
	  if (category) {
	      add_constituent_to_incomplete_phrases(Nil,category,
		      incomplete_phrases);
	      result = VALUES_1(Incomplete_phrases_at_frontier);
	  }
	  else
	      result = VALUES_1(Nil);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

Object Registered_directory_of_names_p_prop = UNBOUND;

Object Registered_abstract_integer_category_p_prop = UNBOUND;

/* RECLAIM-MENU-CONTENT-STRUCTURE */
Object reclaim_menu_content_structure(menu_content_structure)
    Object menu_content_structure;
{
    x_note_fn_call(78,162);
    reclaim_gensym_tree_1(menu_content_structure);
    return VALUES_1(Nil);
}

Object Maximum_size_of_token_sequence = UNBOUND;

static Object Qend;                /* end */

static Object Qpunctuation_mark;   /* punctuation-mark */

static Object Qunreserved_symbol;  /* unreserved-symbol */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object Qright_string;       /* right-string */

static Object Qwhole_string;       /* whole-string */

/* MAKE-MENU-CONTENT-STRUCTURE-FOR-CHARACTER-POSITION */
Object make_menu_content_structure_for_character_position(menu_content_structure_for_token_position,
	    potential_token_types,prefix_simple_string)
    Object menu_content_structure_for_token_position, potential_token_types;
    Object prefix_simple_string;
{
    Object old_menus, category_symbols_for_menu, category_menu;
    Object category_symbol, ab_loop_list_, category, type_of_token;
    Object ab_loop_list__1, ab_loop_it_, temp, new_cons, gensymed_symbol;
    Object temp_2, length_of_prefix_simple_string, menu_1, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, menu_element, new_menu_elements;
    Object ab_loopvar__3, initial_token, string_for_initial_token;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object write_symbols_parsably_qm, write_strings_parsably_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    char temp_1;
    Declare_special(7);

    x_note_fn_call(78,163);
    old_menus = EQ(CAR(menu_content_structure_for_token_position),Qend) ? 
	    CDR(menu_content_structure_for_token_position) : 
	    menu_content_structure_for_token_position;
    category_symbols_for_menu = Nil;
    category_menu = CAR(old_menus);
    category_symbol = Nil;
    ab_loop_list_ = category_menu;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category = get_or_make_category_for_category_symbol(category_symbol);
    type_of_token = Nil;
    ab_loop_list__1 = potential_token_types;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    type_of_token = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp =  !EQ(type_of_token,Qpunctuation_mark) ? 
	    subcategoryp(get_or_make_category_for_category_symbol(type_of_token),
	    category) : Nil;
    if (temp);
    else
	temp = EQ(type_of_token,Qsymbol) ? 
		subcategoryp(get_or_make_category_for_category_symbol(Qunreserved_symbol),
		category) : Nil;
    ab_loop_it_ = temp;
    if (ab_loop_it_) {
	temp_1 = TRUEP(ab_loop_it_);
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    temp_1 = TRUEP(Qnil);
  end_1:;
    if (temp_1) {
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = category_symbol;
	M_CDR(gensymed_symbol) = category_symbols_for_menu;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	category_symbols_for_menu = gensymed_symbol;
    }
    goto next_loop;
  end_loop:;
    temp_2 = nreverse(category_symbols_for_menu);
    length_of_prefix_simple_string = lengthw(prefix_simple_string);
    menu_1 = Nil;
    ab_loop_list_ = CDR(old_menus);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    menu_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    menu_element = Nil;
    ab_loop_list__1 = menu_1;
    new_menu_elements = Nil;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_3;
    menu_element = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    temp_1 = EQ(menu_element,Kupcase);
    if (temp_1);
    else {
	initial_token = ATOM(menu_element) ? menu_element : 
		FIRST(menu_element);
	if (SYMBOLP(initial_token))
	    string_for_initial_token = symbol_name_text_string(initial_token);
	else {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,6);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,5);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			4);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  3);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    2);
		      write_symbols_parsably_qm = T;
		      write_strings_parsably_qm = T;
		      PUSH_SPECIAL(Write_strings_parsably_qm,write_strings_parsably_qm,
			      1);
			PUSH_SPECIAL(Write_symbols_parsably_qm,write_symbols_parsably_qm,
				0);
			  twrite(initial_token);
			POP_SPECIAL();
		      POP_SPECIAL();
		      string_for_initial_token = 
			      copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	if ( !TRUEP(memq_function(Qright_string,potential_token_types)) && 
		( !TRUEP(memq_function(Qwhole_string,
		potential_token_types)) || text_string_p(initial_token)) 
		&& FIXNUM_LE(length_of_prefix_simple_string,
		lengthw(string_for_initial_token))) {
	    i = (SI_Long)0L;
	    ab_loop_bind_ = IFIX(length_of_prefix_simple_string);
	  next_loop_4:
	    if (i >= ab_loop_bind_)
		goto end_loop_4;
	    if ( !(UBYTE_16_ISAREF_1(string_for_initial_token,i) == 
		    UBYTE_16_ISAREF_1(prefix_simple_string,i))) {
		temp = Nil;
		goto end_2;
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:
	    temp = T;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	}
	else
	    temp = Nil;
	if ( !SYMBOLP(initial_token))
	    reclaim_text_string(string_for_initial_token);
	temp_1 = TRUEP(temp);
    }
    if (temp_1) {
	ab_loopvar__3 = gensym_cons_1(ATOM(menu_element) ? menu_element : 
		copy_list_using_gensym_conses_1(menu_element),Nil);
	if (ab_loopvar__2)
	    M_CDR(ab_loopvar__2) = ab_loopvar__3;
	else
	    new_menu_elements = ab_loopvar__3;
	ab_loopvar__2 = ab_loopvar__3;
    }
    goto next_loop_3;
  end_loop_3:
    ab_loopvar__2 = new_menu_elements ? gensym_cons_1(new_menu_elements,
	    Nil) : Nil;
    goto end_3;
    ab_loopvar__2 = Qnil;
  end_3:;
    if (ab_loopvar__2) {
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = last(ab_loopvar__2,_);
    }
    goto next_loop_2;
  end_loop_2:
    temp = ab_loopvar_;
    goto end_4;
    temp = Qnil;
  end_4:;
    return gensym_cons_1(temp_2,temp);
}

Object Menu_too_many_instances = UNBOUND;

Object Editor_parameters = UNBOUND;

static Object Qobject_name;        /* object-name */

static Object Qobject_name_menus_in_upper_case_qm;  /* object-name-menus-in-upper-case? */

/* MAKE-CATEGORY-INSTANCE-MENUS */
Object make_category_instance_menus(category_menu,prefix_simple_string_qm,
	    maximum_number_of_instances)
    Object category_menu, prefix_simple_string_qm, maximum_number_of_instances;
{
    Object category_symbol, ab_loop_list_, number_of_instances_remaining;
    Object all_instances_so_far, category_instance_menus_so_far;
    Object pruned_category_instance_menu, length_of_pruned_menu;
    Object category_instance_menu_qm, temp, instance, ab_loop_list__1;
    Object decff_1_arg;

    x_note_fn_call(78,164);
    category_symbol = Nil;
    ab_loop_list_ = category_menu;
    number_of_instances_remaining = maximum_number_of_instances;
    all_instances_so_far = Qnil;
    category_instance_menus_so_far = Qnil;
    pruned_category_instance_menu = Nil;
    length_of_pruned_menu = Nil;
    category_instance_menu_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    category_symbol = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    pruned_category_instance_menu = Qnil;
    length_of_pruned_menu = FIX((SI_Long)0L);
    category_instance_menu_qm = 
	    make_menu_of_names_from_directory_if_few_enough(category_symbol,
	    prefix_simple_string_qm,number_of_instances_remaining);
    if ( ! !TRUEP(category_instance_menu_qm)) {
	if (EQ(category_instance_menu_qm,Menu_too_many_instances)) {
	    reclaim_menu_content_structure(category_instance_menus_so_far);
	    reclaim_gensym_list_1(all_instances_so_far);
	    temp = Nil;
	    goto end_1;
	}
	instance = Nil;
	ab_loop_list__1 = category_instance_menu_qm;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	instance = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if ( !TRUEP(memq_function(instance,all_instances_so_far))) {
	    pruned_category_instance_menu = gensym_cons_1(instance,
		    pruned_category_instance_menu);
	    length_of_pruned_menu = FIXNUM_ADD1(length_of_pruned_menu);
	    all_instances_so_far = gensym_cons_1(instance,
		    all_instances_so_far);
	}
	goto next_loop_1;
      end_loop_1:;
	reclaim_gensym_list_1(category_instance_menu_qm);
	decff_1_arg = length_of_pruned_menu;
	number_of_instances_remaining = 
		FIXNUM_MINUS(number_of_instances_remaining,decff_1_arg);
	if (EQ(category_symbol,Qobject_name) && 
		get_slot_value_function(Editor_parameters,
		Qobject_name_menus_in_upper_case_qm,Nil) && 
		pruned_category_instance_menu)
	    pruned_category_instance_menu = gensym_cons_1(Kupcase,
		    pruned_category_instance_menu);
	if ( ! !TRUEP(pruned_category_instance_menu))
	    category_instance_menus_so_far = 
		    gensym_cons_1(pruned_category_instance_menu,
		    category_instance_menus_so_far);
    }
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(all_instances_so_far);
    temp = nreverse(category_instance_menus_so_far);
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Omit_from_quoted_token_menus_p_prop = UNBOUND;

Object Overriding_token_instances_without_specific_categories_prop = UNBOUND;

Object Months_of_the_year = UNBOUND;

Object Category_symbols_for_non_contributing_categories = UNBOUND;

Object Collected_menu_content_structure = UNBOUND;

Object Menu_items_for_parsing = UNBOUND;

Object Token_sequence_location_plist = UNBOUND;

/* SKIP-MENU-ITEMS-IF-ALL-ARE-REPEATS */
Object skip_menu_items_if_all_are_repeats(menu_items_for_parsing,
	    collected_menu_content_structure)
    Object menu_items_for_parsing, collected_menu_content_structure;
{
    Object item_list, ab_loop_list_, menu_items, ab_loop_list__1, ab_loop_it_;
    Object menu_item_list, ab_loop_list__2;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(78,165);
    PUSH_SPECIAL(Collected_menu_content_structure,collected_menu_content_structure,
	    1);
      PUSH_SPECIAL(Menu_items_for_parsing,menu_items_for_parsing,0);
	item_list = Nil;
	ab_loop_list_ = Menu_items_for_parsing;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	item_list = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	menu_items = Nil;
	ab_loop_list__1 = Collected_menu_content_structure;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	menu_items = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	menu_item_list = Nil;
	ab_loop_list__2 = menu_items;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	menu_item_list = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	ab_loop_it_ = EQUAL(menu_item_list,item_list) ? T : Nil;
	if (ab_loop_it_)
	    goto end_1;
	goto next_loop_2;
      end_loop_2:
	ab_loop_it_ = Qnil;
      end_1:;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	temp = TRUEP(Qnil);
      end_2:;
	if ( !temp) {
	    result = VALUES_1(Nil);
	    goto end_3;
	}
	goto next_loop;
      end_loop:
	result = VALUES_1(T);
	goto end_3;
	result = VALUES_1(Qnil);
      end_3:;
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* MAKE-MENU-CONTENT-STRUCTURE-FOR-TOKEN-POSITION */
Object make_menu_content_structure_for_token_position(incomplete_phrases_at_this_position,
	    phrase_rule_completions_past_instance_of_category)
    Object incomplete_phrases_at_this_position;
    Object phrase_rule_completions_past_instance_of_category;
{
    Object category_symbols_for_non_contributing_categories;
    Object collected_menu_content_structure, token_sequence_location_plist;
    Object irrelevant_category, incomplete_phrase, ab_loop_list_;
    Object phrase_rule_completion, ab_loop_list__1;
    Object category_of_next_constituent, temp, i, l, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp_1, menus, ab_loop_it_;
    char temp_2;
    Declare_special(3);
    Object result;

    x_note_fn_call(78,166);
    set_up_category_visit();
    category_symbols_for_non_contributing_categories = Nil;
    PUSH_SPECIAL(Category_symbols_for_non_contributing_categories,category_symbols_for_non_contributing_categories,
	    2);
      collected_menu_content_structure = Nil;
      PUSH_SPECIAL(Collected_menu_content_structure,collected_menu_content_structure,
	      1);
	token_sequence_location_plist = Nil;
	PUSH_SPECIAL(Token_sequence_location_plist,token_sequence_location_plist,
		0);
	  irrelevant_category = 
		  get_or_make_category_for_category_symbol(Qirrelevant);
	  incomplete_phrase = Nil;
	  ab_loop_list_ = incomplete_phrases_at_this_position;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  incomplete_phrase = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  phrase_rule_completion = Nil;
	  ab_loop_list__1 = ISVREF(incomplete_phrase,(SI_Long)1L);
	  category_of_next_constituent = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  phrase_rule_completion = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  category_of_next_constituent = ISVREF(phrase_rule_completion,
		  (SI_Long)1L);
	  if ( !EQ(category_of_next_constituent,irrelevant_category))
	      add_menu_items_for_category(category_of_next_constituent,Nil,
		      Nil,ISVREF(phrase_rule_completion,(SI_Long)4L));
	  goto next_loop_1;
	end_loop_1:;
	  goto next_loop;
	end_loop:;
	  temp = nreverse(Category_symbols_for_non_contributing_categories);
	  i = Nil;
	  l = Nil;
	  ab_loop_list_ = Token_sequence_location_plist;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	next_loop_2:
	  i = CAR(ab_loop_list_);
	  temp_1 = CDR(ab_loop_list_);
	  l = CAR(temp_1);
	  ab_loopvar__2 = gensym_cons_1(l,Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  ab_loop_list_ = CDDR(ab_loop_list_);
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  goto next_loop_2;
	end_loop_2:
	  temp_1 = ab_loopvar_;
	  goto end_1;
	  temp_1 = Qnil;
	end_1:;
	  menus = gensym_cons_1(temp,nreverse(temp_1));
	  reclaim_gensym_list_1(Token_sequence_location_plist);
	  incomplete_phrase = Nil;
	  ab_loop_list_ = incomplete_phrases_at_this_position;
	  ab_loop_it_ = Nil;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  incomplete_phrase = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loop_it_ = EQ(ISVREF(incomplete_phrase,(SI_Long)1L),
		  phrase_rule_completions_past_instance_of_category) ? T : Nil;
	  if (ab_loop_it_) {
	      temp_2 = TRUEP(ab_loop_it_);
	      goto end_2;
	  }
	  goto next_loop_3;
	end_loop_3:
	  temp_2 = TRUEP(Qnil);
	end_2:;
	  if (temp_2)
	      result = gensym_cons_1(Qend,menus);
	  else
	      result = VALUES_1(menus);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

/* REMOVE-GRAMMAR-PLIST-ELEMENT */
Object remove_grammar_plist_element(plist,indicator)
    Object plist, indicator;
{
    Object l_trailer_qm, l, cdr_new_value, temp;

    x_note_fn_call(78,167);
    l_trailer_qm = Nil;
    l = plist;
  next_loop:
    if (EQ(CAR(l),indicator)) {
	if (l_trailer_qm) {
	    cdr_new_value = CDDR(l);
	    M_CDR(l_trailer_qm) = cdr_new_value;
	}
	else
	    plist = CDDR(l);
	M_CDDR(l) = Nil;
	reclaim_gensym_list_1(l);
	temp = plist;
	goto end_1;
    }
    l_trailer_qm = CDR(l);
    l = CDR(l_trailer_qm);
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* APPROXIMATE-SIZE-OF-TOKEN */
Object approximate_size_of_token(token)
    Object token;
{
    x_note_fn_call(78,168);
    if (SYMBOLP(token))
	return text_string_length(symbol_name_text_string(token));
    else
	return VALUES_1(FIX((SI_Long)5L));
}

Object One_sequence_of_following_tokens_only_p = UNBOUND;

/* GET-LISTS-OF-FOLLOWING-TOKENS */
Object get_lists_of_following_tokens(token,
	    phrase_rule_completions_past_this_qm,
	    approximate_size_of_token_sequence)
    Object token, phrase_rule_completions_past_this_qm;
    Object approximate_size_of_token_sequence;
{
    Object incff_1_arg, temp, completion, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;

    x_note_fn_call(78,169);
    incff_1_arg = approximate_size_of_token(token);
    approximate_size_of_token_sequence = 
	    FIXNUM_ADD(approximate_size_of_token_sequence,incff_1_arg);
    if (FIXNUM_LE(approximate_size_of_token_sequence,
	    Maximum_size_of_token_sequence)) {
	if (One_sequence_of_following_tokens_only_p)
	    temp = phrase_rule_completions_past_this_qm &&  
		    !TRUEP(CDR(phrase_rule_completions_past_this_qm)) ? 
		    extend_lists_of_following_tokens(token,
		    CAR(phrase_rule_completions_past_this_qm),
		    approximate_size_of_token_sequence) : Nil;
	else {
	    completion = Nil;
	    ab_loop_list_ = phrase_rule_completions_past_this_qm;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    completion = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loopvar__2 = extend_lists_of_following_tokens(token,
		    completion,approximate_size_of_token_sequence);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	    goto next_loop;
	  end_loop:
	    temp = ab_loopvar_;
	    goto end_1;
	    temp = Qnil;
	  end_1:;
	}
	return remove_duplicates_from_lists_of_token_lists(temp);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-DUPLICATES-FROM-LISTS-OF-TOKEN-LISTS */
Object remove_duplicates_from_lists_of_token_lists(lists_of_token_lists)
    Object lists_of_token_lists;
{
    Object tail, list_1, ab_loop_list_, collectp, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, temp;

    x_note_fn_call(78,170);
    tail = lists_of_token_lists;
    list_1 = Nil;
    ab_loop_list_ = lists_of_token_lists;
    collectp = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(tail))
	goto end_loop;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    list_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    collectp =  !TRUEP(member_equal(list_1,CDR(tail))) ? T : Nil;
    if (collectp) {
	ab_loopvar__2 = gensym_cons_1(list_1,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    if ( !TRUEP(collectp))
	reclaim_gensym_list_1(list_1);
    tail = M_CDR(tail);
    goto next_loop;
  end_loop:
    temp = ab_loopvar_;
    goto end_1;
    temp = Qnil;
  end_1:;
    reclaim_gensym_list_1(lists_of_token_lists);
    return VALUES_1(temp);
}

/* ALL-TOKEN-LISTS-ARE-PRE-EXISTING-P */
Object all_token_lists_are_pre_existing_p(lists)
    Object lists;
{
    Object list_1, ab_loop_list_, category, c_lists, ab_loop_list__1;
    Object ab_loop_it_, temp;
    char temp_1;

    x_note_fn_call(78,171);
    list_1 = Nil;
    ab_loop_list_ = lists;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    list_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category = Nil;
    c_lists = Nil;
    ab_loop_list__1 = Token_sequence_location_plist;
    ab_loop_it_ = Nil;
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
  next_loop_1:
    category = CAR(ab_loop_list__1);
    temp = CDR(ab_loop_list__1);
    c_lists = CAR(temp);
    ab_loop_it_ = member_equal(list_1,c_lists);
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
    if ( !temp_1)
	return VALUES_1(Nil);
    goto next_loop;
  end_loop:
    return VALUES_1(T);
    return VALUES_1(Qnil);
}

/* EXTEND-LISTS-OF-FOLLOWING-TOKENS */
Object extend_lists_of_following_tokens(token,phrase_rule_completion,
	    approximate_size_of_token_sequence)
    Object token, phrase_rule_completion, approximate_size_of_token_sequence;
{
    Object category_of_next_constituent, next_token, lists, lists_tail;
    Object gensym_push_modify_macro_arg, car_1, cdr_1, car_new_value;

    x_note_fn_call(78,172);
    category_of_next_constituent = ISVREF(phrase_rule_completion,(SI_Long)1L);
    if (SIMPLE_VECTOR_P(category_of_next_constituent) && 
	    EQ(ISVREF(category_of_next_constituent,(SI_Long)0L),
	    Qg2_defstruct_structure_name_category_for_token_g2_struct)) {
	next_token = ISVREF(category_of_next_constituent,(SI_Long)7L);
	lists = get_lists_of_following_tokens(next_token, 
		!TRUEP(ISVREF(phrase_rule_completion,(SI_Long)3L)) ? 
		ISVREF(phrase_rule_completion,(SI_Long)4L) : Nil,
		FIXNUM_ADD1(approximate_size_of_token_sequence));
	if (lists);
	else
	    lists = gensym_cons_1(gensym_cons_1(next_token,Nil),Nil);
	lists_tail = lists;
      next_loop:
	if ( !TRUEP(lists_tail))
	    goto end_loop;
	gensym_push_modify_macro_arg = token;
	car_1 = gensym_push_modify_macro_arg;
	cdr_1 = CAR(lists_tail);
	car_new_value = gensym_cons_1(car_1,cdr_1);
	M_CAR(lists_tail) = car_new_value;
	lists_tail = M_CDR(lists_tail);
	goto next_loop;
      end_loop:
	return VALUES_1(lists);
	return VALUES_1(Qnil);
    }
    else
	return gensym_cons_1(gensym_cons_1(token,Nil),Nil);
}

/* ADD-MENU-ITEMS-FOR-PARSING-FOR-CATEGORY */
Object add_menu_items_for_parsing_for_category(category,lists)
    Object category, lists;
{
    Object existing_lists, list_1, ab_loop_list_, temp_1, temp_2;
    char temp;

    x_note_fn_call(78,173);
    if (all_token_lists_are_pre_existing_p(lists)) {
	reclaim_gensym_tree_1(lists);
	return VALUES_1(Nil);
    }
    else {
	existing_lists = 
		getfq_function_no_default(Token_sequence_location_plist,
		category);
	if (existing_lists) {
	    list_1 = Nil;
	    ab_loop_list_ = existing_lists;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    list_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(member_equal(list_1,lists))) {
		temp = TRUEP(Nil);
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    temp = TRUEP(T);
	    goto end_1;
	    temp = TRUEP(Qnil);
	  end_1:;
	    if (temp) {
		temp_1 = CDR(existing_lists);
		temp_2 = CAR(lists);
		M_CAR(existing_lists) = temp_2;
		temp_2 = CDR(lists);
		M_CDR(existing_lists) = temp_2;
		reclaim_gensym_cons_1(lists);
		reclaim_gensym_tree_1(temp_1);
		return VALUES_1(Nil);
	    }
	    else
		return VALUES_1(nconc2(existing_lists,lists));
	}
	else {
	    Token_sequence_location_plist = gensym_cons_1(category,
		    gensym_cons_1(lists,Token_sequence_location_plist));
	    return VALUES_1(Token_sequence_location_plist);
	}
    }
}

/* ADD-TOKEN-FOR-PARSING-FOR-CATEGORY */
Object add_token_for_parsing_for_category(category,token)
    Object category, token;
{
    x_note_fn_call(78,174);
    return add_menu_items_for_parsing_for_category(category,
	    gensym_cons_1(gensym_cons_1(token,Nil),Nil));
}

static Object Qomit_from_quoted_token_menus_p;  /* omit-from-quoted-token-menus-p */

static Object Qfunction_name;      /* function-name */

static Object list_constant_1;     /* # */

/* ADD-MENU-ITEMS-FOR-NOT-YET-VISITED-TOKEN-CATEGORY */
Object add_menu_items_for_not_yet_visited_token_category(category,
	    phrase_rule_completions_past_this_qm,more_general_category_qm)
    Object category, phrase_rule_completions_past_this_qm;
    Object more_general_category_qm;
{
    Object token, lists;

    x_note_fn_call(78,175);
    token = ISVREF(category,(SI_Long)7L);
    if ( !(SYMBOLP(token) && 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(token),
	    Qomit_from_quoted_token_menus_p))) {
	lists = get_lists_of_following_tokens(token,
		phrase_rule_completions_past_this_qm,FIX((SI_Long)0L));
	if (lists)
	    return add_menu_items_for_parsing_for_category(category,lists);
	else if ( !(more_general_category_qm && 
		EQ(ISVREF(more_general_category_qm,(SI_Long)7L),
		Qfunction_name) && memq_function(token,list_constant_1)))
	    return add_token_for_parsing_for_category(category,token);
	else
	    return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qoverriding_token_instances_without_specific_categories;  /* overriding-token-instances-without-specific-categories */

static Object Qregistered_directory_of_names_p;  /* registered-directory-of-names-p */

static Object list_constant_2;     /* # */

static Object Qregistered_abstract_integer_category_p;  /* registered-abstract-integer-category-p */

/* ADD-MENU-ITEMS-FOR-NOT-YET-VISITED-NON-TOKEN-CATEGORY */
Object add_menu_items_for_not_yet_visited_non_token_category(category,
	    more_general_category_for_which_there_are_no_menu_items_qm)
    Object category;
    Object more_general_category_for_which_there_are_no_menu_items_qm;
{
    Object more_specific_categories;
    Object categories_that_can_begin_a_phrase_of_this_category;
    Object category_symbol, number_of_menu_items_added, token, gensymed_symbol;
    Object ab_loop_list_, more_specific_category, incff_1_arg;
    Object beginning_category, completions;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_it_;
    Object category_symbols_for_non_contributing_categories_new_value;
    char temp;

    x_note_fn_call(78,176);
    more_specific_categories = ISVREF(category,(SI_Long)8L);
    categories_that_can_begin_a_phrase_of_this_category = ISVREF(category,
	    (SI_Long)10L);
    category_symbol = ISVREF(category,(SI_Long)7L);
    number_of_menu_items_added = FIX((SI_Long)0L);
    if (ISVREF(category,(SI_Long)9L)) {
	token = Nil;
	gensymed_symbol = ISVREF(category,(SI_Long)7L);
	ab_loop_list_ = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qoverriding_token_instances_without_specific_categories);
	if (ab_loop_list_);
	else
	    ab_loop_list_ = ISVREF(category,(SI_Long)9L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	token = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_token_for_parsing_for_category(category,token);
	number_of_menu_items_added = FIXNUM_ADD1(number_of_menu_items_added);
	goto next_loop;
      end_loop:;
    }
    if (lookup_kb_specific_property_value(category_symbol,
	    Symbol_tokens_for_category_symbol_kbprop)) {
	token = Nil;
	ab_loop_list_ = lookup_kb_specific_property_value(category_symbol,
		Symbol_tokens_for_category_symbol_kbprop);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	token = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_token_for_parsing_for_category(category,token);
	number_of_menu_items_added = FIXNUM_ADD1(number_of_menu_items_added);
	goto next_loop_1;
      end_loop_1:;
    }
    if (more_specific_categories) {
	more_specific_category = Nil;
	ab_loop_list_ = more_specific_categories;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	more_specific_category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(more_specific_category) && 
		EQ(ISVREF(more_specific_category,(SI_Long)0L),
		Qg2_defstruct_structure_name_category_for_token_g2_struct)) {
	    incff_1_arg = 
		    add_menu_items_for_category(more_specific_category,
		    category,IFIX(number_of_menu_items_added) == 
		    (SI_Long)0L ? category : Nil,Nil);
	    number_of_menu_items_added = 
		    FIXNUM_ADD(number_of_menu_items_added,incff_1_arg);
	}
	goto next_loop_2;
      end_loop_2:;
	more_specific_category = Nil;
	ab_loop_list_ = more_specific_categories;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	more_specific_category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SIMPLE_VECTOR_P(more_specific_category) && 
		EQ(ISVREF(more_specific_category,(SI_Long)0L),
		Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct)) 
		    {
	    incff_1_arg = 
		    add_menu_items_for_category(more_specific_category,
		    category,IFIX(number_of_menu_items_added) == 
		    (SI_Long)0L ? category : Nil,Nil);
	    number_of_menu_items_added = 
		    FIXNUM_ADD(number_of_menu_items_added,incff_1_arg);
	}
	goto next_loop_3;
      end_loop_3:;
    }
    beginning_category = Nil;
    ab_loop_list_ = categories_that_can_begin_a_phrase_of_this_category;
    completions = Nil;
  next_loop_4:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_4;
    beginning_category = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    completions = 
	    sole_completion_for_beginning_category_to_category(beginning_category,
	    category);
    incff_1_arg = add_menu_items_for_category(beginning_category,Nil,Nil,
	    completions);
    number_of_menu_items_added = FIXNUM_ADD(number_of_menu_items_added,
	    incff_1_arg);
    goto next_loop_4;
  end_loop_4:;
    if (categories_that_can_begin_a_phrase_of_this_category && 
	    IFIX(number_of_menu_items_added) == (SI_Long)0L)
	number_of_menu_items_added = FIX((SI_Long)1L);
    temp = TRUEP(lookup_kb_specific_property_value(category_symbol,
	    Directory_of_names_kbprop));
    if (temp);
    else
	temp = 
		TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(category_symbol),
		Qregistered_directory_of_names_p));
    if (temp);
    else if (IFIX(number_of_menu_items_added) == (SI_Long)0L || 
	    EQ(category_symbol,Qnumber)) {
	temp =  
		!TRUEP(more_general_category_for_which_there_are_no_menu_items_qm);
	if (temp);
	else
	    temp = 
		    TRUEP(ISVREF(more_general_category_for_which_there_are_no_menu_items_qm,
		    (SI_Long)10L));
	if (temp);
	else if (memq_function(category_symbol,list_constant_2)) {
	    gensymed_symbol = 
		    ISVREF(more_general_category_for_which_there_are_no_menu_items_qm,
		    (SI_Long)7L);
	    temp =  
		    !TRUEP(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		    Qregistered_abstract_integer_category_p));
	}
	else
	    temp = TRUEP(Nil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	gensym_modify_macro_using_test_arg_1 = category_symbol;
	car_1 = gensym_modify_macro_using_test_arg_1;
	cdr_1 = Category_symbols_for_non_contributing_categories;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list_ = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	x_element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_5;
      end_loop_5:
	temp = TRUEP(Qnil);
      end_1:;
	category_symbols_for_non_contributing_categories_new_value = temp ?
		 cdr_1 : gensym_cons_1(car_1,cdr_1);
	Category_symbols_for_non_contributing_categories = 
		category_symbols_for_non_contributing_categories_new_value;
	number_of_menu_items_added = FIXNUM_ADD1(number_of_menu_items_added);
    }
    return VALUES_1(number_of_menu_items_added);
}

/* SOLE-COMPLETION-FOR-BEGINNING-CATEGORY-TO-CATEGORY */
Object sole_completion_for_beginning_category_to_category(beginning_category,
	    category)
    Object beginning_category, category;
{
    Object phrase_rule_completions_qm, phrase_rule_completions, ab_loop_list_;
    Object temp;

    x_note_fn_call(78,177);
    phrase_rule_completions_qm = Nil;
    phrase_rule_completions = Nil;
    ab_loop_list_ = ISVREF(beginning_category,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    phrase_rule_completions = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (subcategoryp(ISVREF(CAR(phrase_rule_completions),(SI_Long)2L),
	    category)) {
	if (phrase_rule_completions_qm) {
	    temp = Nil;
	    goto end_1;
	}
	else
	    phrase_rule_completions_qm = phrase_rule_completions;
    }
    goto next_loop;
  end_loop:
    temp = phrase_rule_completions_qm;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

Object Prune_token_categories_visited_more_than_once_p = UNBOUND;

Object List_of_argument_lists_to_add_menu_items_for_category = UNBOUND;

/* ADD-MENU-ITEMS-FOR-CATEGORY */
Object add_menu_items_for_category(category,more_general_category_qm,
	    more_general_category_for_which_there_are_no_menu_items_qm,
	    phrase_rule_completions_past_this_qm)
    Object category, more_general_category_qm;
    Object more_general_category_for_which_there_are_no_menu_items_qm;
    Object phrase_rule_completions_past_this_qm;
{
    Object entry, category_index, category_visit_vector_qm;
    Object current_category_visit_stamp, category_visit_stamp_and_flag;
    Object desired_value;
    Object list_of_argument_lists_to_add_menu_items_for_category, svref_arg_1;
    Object temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(78,178);
    entry = SIMPLE_VECTOR_P(category) && EQ(ISVREF(category,(SI_Long)0L),
	    Qg2_defstruct_structure_name_category_for_token_g2_struct) ? 
	    (more_general_category_qm || 
	    phrase_rule_completions_past_this_qm ? gensym_list_3(category,
	    more_general_category_qm,phrase_rule_completions_past_this_qm) 
	    : category) : 
	    more_general_category_for_which_there_are_no_menu_items_qm ? 
	    gensym_list_2(category,
	    more_general_category_for_which_there_are_no_menu_items_qm) : 
	    category;
    category_index = ISVREF(category,(SI_Long)1L);
    category_visit_vector_qm = ISVREF(Current_grammar,(SI_Long)10L);
    PUSH_SPECIAL(Category_visit_vector_qm,category_visit_vector_qm,2);
      current_category_visit_stamp = ISVREF(Current_grammar,(SI_Long)11L);
      PUSH_SPECIAL(Current_category_visit_stamp,current_category_visit_stamp,
	      1);
	category_visit_stamp_and_flag = ISVREF(Category_visit_vector_qm,
		IFIX(category_index));
	desired_value = FIXNUM_ADD1(Current_category_visit_stamp);
	if (CONSP(entry) ? TRUEP(member_equal(entry,
		List_of_argument_lists_to_add_menu_items_for_category)) : 
		FIXNUM_EQ(category_visit_stamp_and_flag,desired_value))
	    result = VALUES_1(FIX((SI_Long)0L));
	else {
	    list_of_argument_lists_to_add_menu_items_for_category = 
		    CONSP(entry) ? gensym_cons_1(entry,
		    List_of_argument_lists_to_add_menu_items_for_category) 
		    : List_of_argument_lists_to_add_menu_items_for_category;
	    PUSH_SPECIAL(List_of_argument_lists_to_add_menu_items_for_category,list_of_argument_lists_to_add_menu_items_for_category,
		    0);
	      if (ATOM(entry)) {
		  svref_arg_1 = Category_visit_vector_qm;
		  SVREF(svref_arg_1,category_index) = desired_value;
	      }
	      temp = SIMPLE_VECTOR_P(category) && EQ(ISVREF(category,
		      (SI_Long)0L),
		      Qg2_defstruct_structure_name_category_for_token_g2_struct) 
		      ? 
		      (add_menu_items_for_not_yet_visited_token_category(category,
		      phrase_rule_completions_past_this_qm,
		      more_general_category_qm) ? FIX((SI_Long)1L) : 
		      FIX((SI_Long)0L)) : 
		      add_menu_items_for_not_yet_visited_non_token_category(category,
		      more_general_category_for_which_there_are_no_menu_items_qm);
	      if (CONSP(entry)) {
		  reclaim_gensym_cons_1(List_of_argument_lists_to_add_menu_items_for_category);
		  reclaim_gensym_list_1(entry);
	      }
	      result = VALUES_1(temp);
	    POP_SPECIAL();
	}
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qcm;                 /* \, */

static Object list_constant_3;     /* # */

static Object string_constant;     /* "~a-TAIL" */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object string_constant_1;   /* "~a-1" */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

/* ADD-GRAMMAR-RULES-FOR-LIST */
Object add_grammar_rules_for_list varargs_1(int, n)
{
    Object list_category_symbol, symbol_category_symbol;
    Object separator_qm, conjunction_qm, empty_list_symbol_qm;
    Object simplify_piecemeal_p, separator, simplify_splice_form, tail_symbol;
    Object list_category_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(78,179);
    INIT_ARGS_nonrelocating();
    list_category_symbol = REQUIRED_ARG_nonrelocating();
    symbol_category_symbol = REQUIRED_ARG_nonrelocating();
    separator_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    conjunction_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    empty_list_symbol_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    simplify_piecemeal_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    separator = separator_qm;
    if (separator);
    else
	separator = Qcm;
    simplify_splice_form = simplify_piecemeal_p ? list_constant_3 : Nil;
    if ( !TRUEP(conjunction_qm)) {
	tail_symbol = format_symbol(2,string_constant,list_category_symbol);
	return add_grammar_rules_function(list_star(4,
		LIST_2(list_category_symbol,tail_symbol),
		LIST_3(tail_symbol,symbol_category_symbol,CONS(separator,
		list_constant_4)),list_star(4,tail_symbol,
		LIST_3(tail_symbol,LIST_2(Qquote,separator),
		symbol_category_symbol),CONS(separator,list_constant_5),
		simplify_splice_form),empty_list_symbol_qm ? 
		LIST_1(list_star(3,list_category_symbol,LIST_2(Qquote,
		empty_list_symbol_qm),list_constant_6)) : Nil));
    }
    else {
	list_category_symbol_1 = format_symbol(2,string_constant_1,
		list_category_symbol);
	tail_symbol = format_symbol(2,string_constant,list_category_symbol);
	return add_grammar_rules_function(list_star(4,
		LIST_2(list_category_symbol,tail_symbol),
		LIST_3(tail_symbol,symbol_category_symbol,CONS(separator,
		list_constant_4)),LIST_3(tail_symbol,
		LIST_3(symbol_category_symbol,LIST_2(Qquote,
		conjunction_qm),symbol_category_symbol),CONS(separator,
		list_constant_5)),append2(EQ(separator,conjunction_qm) ? 
		LIST_1(list_star(4,tail_symbol,
		LIST_3(list_category_symbol_1,LIST_2(Qquote,
		conjunction_qm),symbol_category_symbol),list_constant_7,
		simplify_splice_form)) : LIST_1(list_star(4,tail_symbol,
		LIST_4(list_category_symbol_1,LIST_2(Qquote,separator),
		LIST_2(Qquote,conjunction_qm),symbol_category_symbol),
		list_constant_8,simplify_splice_form)),list_star(3,
		list_star(4,list_category_symbol_1,
		LIST_3(list_category_symbol_1,LIST_2(Qquote,separator),
		symbol_category_symbol),list_constant_7,
		simplify_splice_form),list_star(4,list_category_symbol_1,
		LIST_3(symbol_category_symbol,LIST_2(Qquote,separator),
		symbol_category_symbol),list_constant_7,
		simplify_splice_form),empty_list_symbol_qm ? 
		LIST_1(list_star(3,list_category_symbol,LIST_2(Qquote,
		empty_list_symbol_qm),list_constant_6)) : Nil))));
    }
}

Object List_phrase_noise_symbols = UNBOUND;

/* REMOVE-NOISE-AT-HEAD-OF-LIST-PHRASE */
Object remove_noise_at_head_of_list_phrase(list_phrase)
    Object list_phrase;
{
    x_note_fn_call(78,180);
    if (CONSP(list_phrase) && memq_function(CAR(list_phrase),
	    List_phrase_noise_symbols))
	return VALUES_1(CDR(list_phrase));
    else
	return VALUES_1(list_phrase);
}

/* SIMPLIFY-ASSOCIATIVE-LIST-OPERATION-ALL-AT-ONCE */
Object simplify_associative_list_operation_all_at_once(parse_result)
    Object parse_result;
{
    Object enclosing_operand, new_tail, first_operand, second_operand_qm;

    x_note_fn_call(78,181);
    if (CDR(parse_result)) {
	enclosing_operand = parse_result;
	new_tail = Nil;
	first_operand = Nil;
	second_operand_qm = Nil;
      next_loop:
	first_operand = SECOND(enclosing_operand);
	second_operand_qm = THIRD(enclosing_operand);
	if ( !TRUEP(second_operand_qm))
	    goto end_loop;
	new_tail = phrase_cons(second_operand_qm,new_tail);
	if ( !(CONSP(first_operand) && EQ(CAR(first_operand),Qcm)))
	    goto end_loop;
	enclosing_operand = first_operand;
	goto next_loop;
      end_loop:
	new_tail = phrase_cons(first_operand,new_tail);
	M_CDR(parse_result) = new_tail;
    }
    return VALUES_1(Nil);
}

Object Semi_open_category_map = UNBOUND;

/* DEF-SEMI-OPEN-CATEGORY-1 */
Object def_semi_open_category_1 varargs_1(int, n)
{
    Object category, instances;
    Object base_category, string_to_display_function_qm;
    Object string_to_insert_function_qm, push_arg;
    Object semi_open_category_map_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(78,182);
    INIT_ARGS_nonrelocating();
    category = REQUIRED_ARG_nonrelocating();
    instances = REQUIRED_ARG_nonrelocating();
    base_category = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Qunreserved_symbol;
    string_to_display_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    string_to_insert_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    add_grammar_rule(LIST_2(category,base_category));
    Semi_open_category_map = lremove(4,category,Semi_open_category_map,
	    Kkey,SYMBOL_FUNCTION(Qcar));
    push_arg = CONS(category,instances);
    semi_open_category_map_new_value = CONS(push_arg,Semi_open_category_map);
    Semi_open_category_map = semi_open_category_map_new_value;
    if (string_to_display_function_qm)
	set_token_menu_string_to_display_function(category,
		string_to_display_function_qm);
    if (string_to_insert_function_qm)
	set_token_menu_string_to_insert_function(category,
		string_to_insert_function_qm);
    return VALUES_1(category);
}

static Object Qremote_process_initialization_string;  /* remote-process-initialization-string */

static Object Qsystem_attribute;   /* system-attribute */

/* SEMI-OPEN-CATEGORY-P */
Object semi_open_category_p varargs_1(int, n)
{
    Object symbol_or_name_denotation;
    Object category_or_categories_qm, symbol, symbols, ab_loop_list_;
    Object ab_loop_it_, ab_loop_desetq_, temp, category;
    Declare_varargs_nonrelocating;

    x_note_fn_call(78,183);
    INIT_ARGS_nonrelocating();
    symbol_or_name_denotation = REQUIRED_ARG_nonrelocating();
    category_or_categories_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    symbol = CONSP(symbol_or_name_denotation) ? 
	    THIRD(symbol_or_name_denotation) : symbol_or_name_denotation;
    if ( !TRUEP(category_or_categories_qm)) {
	symbols = Nil;
	ab_loop_list_ = Semi_open_category_map;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	symbols = CDR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = memq_function(symbol,symbols);
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (EQ(symbol,Qremote_process_initialization_string) && 
	    EQ(category_or_categories_qm,Qsystem_attribute))
	return VALUES_1(Nil);
    else if (SYMBOLP(category_or_categories_qm)) {
	temp = assq_function(category_or_categories_qm,Semi_open_category_map);
	return memq_function(symbol,CDR(temp));
    }
    else {
	category = Nil;
	ab_loop_list_ = category_or_categories_qm;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	category = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = assq_function(category,Semi_open_category_map);
	ab_loop_it_ = memq_function(symbol,CDR(temp));
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

Object Symbols_not_to_add_to_semi_open_category_directories = UNBOUND;

/* ADD-SEMI-OPEN-CATEGORIES-TO-DIRECTORIES */
Object add_semi_open_categories_to_directories()
{
    Object category, instances, ab_loop_list_, ab_loop_desetq_, instance;
    Object ab_loop_list__1;

    x_note_fn_call(78,184);
    category = Nil;
    instances = Nil;
    ab_loop_list_ = Semi_open_category_map;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    category = CAR(ab_loop_desetq_);
    instances = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    instance = Nil;
    ab_loop_list__1 = instances;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    instance = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(memq_function(instance,
	    Symbols_not_to_add_to_semi_open_category_directories)))
	add_to_directory_of_names(instance,category);
    goto next_loop_1;
  end_loop_1:;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

void parse_INIT()
{
    Object named_dynamic_extent_description, temp;
    Object reclaim_structure_for_annotation_1;
    Object reclaim_structure_for_edit_state_1;
    Object reclaim_structure_for_edit_box_change_1;
    Object reclaim_structure_for_gensym_grammar_1;
    Object reclaim_structure_for_category_for_token_1;
    Object reclaim_structure_for_category_for_category_symbol_1;
    Object reclaim_structure_for_category_set_1;
    Object reclaim_structure_for_strict_subcategory_info_1;
    Object reclaim_structure_for_phrase_rule_completion_1;
    Object reclaim_structure_for_incomplete_phrase_1;
    Object AB_package, list_constant_13, Qlist_phrase_noise_symbols, Qcol, Qsc;
    Object Qab_or, Qnil_function, Qsimplify_associative_operation, Qminute;
    Object Qhour, Qaverage, Qmonth, list_constant_12, Qdec, Qnov, Qoct, Qsep;
    Object Qaug, Qjul, Qjun, Qmay, Qapr, Qmar, Qfeb, Qjan, list_constant_11;
    Object Qmenu_too_many_instances, Qtoo_many_instances, Qpositive_integer;
    Object Qnon_negative_integer, Qpriority, Qincomplete_phrase;
    Object Qreclaim_structure, Qoutstanding_incomplete_phrase_count;
    Object Qincomplete_phrase_structure_memory_usage, Qutilities2;
    Object Qincomplete_phrase_count, Qchain_of_available_incomplete_phrases;
    Object string_constant_21, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_20, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qphrase_rule_completion;
    Object Qoutstanding_phrase_rule_completion_count;
    Object Qphrase_rule_completion_structure_memory_usage;
    Object Qphrase_rule_completion_count;
    Object Qchain_of_available_phrase_rule_completions, string_constant_19;
    Object string_constant_18, Qsymbol_tokens_for_category_symbol;
    Object Qfunction_to_reclaim_kb_specific_property_value_qm;
    Object Qreclaim_grammar_list_function;
    Object Qdo_not_carry_global_property_value_into_kbs_qm;
    Object Qcategory_symbols_for_symbol_token, Qstrict_subcategory_info;
    Object list_constant_10, Qglobal_grammar;
    Object Qoutstanding_strict_subcategory_info_count;
    Object Qstrict_subcategory_info_structure_memory_usage;
    Object Qstrict_subcategory_info_count;
    Object Qchain_of_available_strict_subcategory_infos, string_constant_17;
    Object string_constant_16, Qcategory_set, Qoutstanding_category_set_count;
    Object Qcategory_set_structure_memory_usage, Qcategory_set_count;
    Object Qchain_of_available_category_sets, string_constant_15;
    Object string_constant_14, Qcategory_for_category_symbol;
    Object Qoutstanding_category_for_category_symbol_count;
    Object Qcategory_for_category_symbol_structure_memory_usage;
    Object Qcategory_for_category_symbol_count;
    Object Qchain_of_available_category_for_category_symbols;
    Object string_constant_13, string_constant_12, Qcategory_for_token;
    Object Qoutstanding_category_for_token_count;
    Object Qcategory_for_token_structure_memory_usage;
    Object Qcategory_for_token_count, Qchain_of_available_category_for_tokens;
    Object string_constant_11, string_constant_10;
    Object Qmost_positive_fixnum_minus_2, Kno_initial_value, Qparse;
    Object Qcurrent_indicator_for_category_of_symbol_token;
    Object Qcurrent_indicator_for_category_of_this_name, Qcurrent_grammar;
    Object list_constant_9, Qmiddle_string, Qleft_string;
    Object Qcurrent_category_visit_stamp, Qcategory_visit_vector_qm;
    Object Qoutstanding_gensym_grammar_count;
    Object Qgensym_grammar_structure_memory_usage, Qgensym_grammar_count;
    Object Qchain_of_available_gensym_grammars, string_constant_9;
    Object string_constant_8, Qcheck_range_of_element, Qbad_phrase;
    Object Qphrase_cons, Qedit_box_change, Qoutstanding_edit_box_change_count;
    Object Qedit_box_change_structure_memory_usage, Qedit_box_change_count;
    Object Qchain_of_available_edit_box_changes, string_constant_7;
    Object string_constant_6, Qphrase_item, Qphrase_item_denotation;
    Object Qphrase_structure, Qphrase_sequence;
    Object Qselection_style_of_workstation_context_type;
    Object Qediting_and_top_level_is_selection_style, Qedit_state;
    Object Qoutstanding_edit_state_count, Qedit_state_structure_memory_usage;
    Object Qedit_state_count, Qchain_of_available_edit_states;
    Object string_constant_5, string_constant_4, Qannotation;
    Object Qoutstanding_annotation_count, Qannotation_structure_memory_usage;
    Object Qannotation_count, Qchain_of_available_annotations;
    Object string_constant_3, string_constant_2, Qdirectory_of_names;
    Object Qreclaim_grammar_tree_function, Qnamed_dynamic_extent_description;
    Object Qediting_context, Qedit;

    x_note_fn_call(78,185);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qediting_context = STATIC_SYMBOL("EDITING-CONTEXT",AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qediting_context,Qedit,
	    Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qediting_context,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Current_edit_state == UNBOUND)
	Current_edit_state = Nil;
    if (Keep_edit_workspace_hidden_no_matter_what_qm == UNBOUND)
	Keep_edit_workspace_hidden_no_matter_what_qm = Nil;
    Qdirectory_of_names = STATIC_SYMBOL("DIRECTORY-OF-NAMES",AB_package);
    Kb_specific_property_names = CONS(Qdirectory_of_names,
	    Kb_specific_property_names);
    Qdo_not_carry_global_property_value_into_kbs_qm = 
	    STATIC_SYMBOL("DO-NOT-CARRY-GLOBAL-PROPERTY-VALUE-INTO-KBS\?",
	    AB_package);
    mutate_global_property(Qdirectory_of_names,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_grammar_tree_function = 
	    STATIC_SYMBOL("RECLAIM-GRAMMAR-TREE-FUNCTION",AB_package);
    Qfunction_to_reclaim_kb_specific_property_value_qm = 
	    STATIC_SYMBOL("FUNCTION-TO-RECLAIM-KB-SPECIFIC-PROPERTY-VALUE\?",
	    AB_package);
    mutate_global_property(Qdirectory_of_names,
	    Qreclaim_grammar_tree_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Directory_of_names_kbprop = Qdirectory_of_names;
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_annotation_g2_struct = 
	    STATIC_SYMBOL("ANNOTATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qannotation = STATIC_SYMBOL("ANNOTATION",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_annotation_g2_struct,
	    Qannotation,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qannotation,
	    Qg2_defstruct_structure_name_annotation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_annotation == UNBOUND)
	The_type_description_of_annotation = Nil;
    string_constant_2 = 
	    STATIC_STRING("43Dy8m83fAy1n83fAy8n8k1l8n0000001l1n8y83-2py1m83qXy83qWyknk0k0");
    temp = The_type_description_of_annotation;
    The_type_description_of_annotation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_2));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_annotation_g2_struct,
	    The_type_description_of_annotation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qannotation,The_type_description_of_annotation,
	    Qtype_description_of_type);
    Qoutstanding_annotation_count = 
	    STATIC_SYMBOL("OUTSTANDING-ANNOTATION-COUNT",AB_package);
    Qannotation_structure_memory_usage = 
	    STATIC_SYMBOL("ANNOTATION-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_3 = STATIC_STRING("1q83fAy8s83-Jky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_annotation_count);
    push_optimized_constant(Qannotation_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_3));
    Qchain_of_available_annotations = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-ANNOTATIONS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_annotations,
	    Chain_of_available_annotations);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_annotations,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qannotation_count = STATIC_SYMBOL("ANNOTATION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qannotation_count,Annotation_count);
    record_system_variable(Qannotation_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qannotation_structure_memory_usage,
	    STATIC_FUNCTION(annotation_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_annotation_count,
	    STATIC_FUNCTION(outstanding_annotation_count,NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_annotation_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_annotation,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qannotation,
	    reclaim_structure_for_annotation_1);
    Qreclaim_annotation_qm = STATIC_SYMBOL("RECLAIM-ANNOTATION\?",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_annotation_qm,
	    STATIC_FUNCTION(reclaim_annotation_qm,NIL,FALSE,1,1));
    Qg2_defstruct_structure_name_edit_state_g2_struct = 
	    STATIC_SYMBOL("EDIT-STATE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qedit_state = STATIC_SYMBOL("EDIT-STATE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_edit_state_g2_struct,
	    Qedit_state,Qab_name_of_unique_structure_type);
    mutate_global_property(Qedit_state,
	    Qg2_defstruct_structure_name_edit_state_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_edit_state == UNBOUND)
	The_type_description_of_edit_state = Nil;
    string_constant_4 = 
	    STATIC_STRING("43Dy8m83Bsy1o83Bsy83-Sy8n8k1l83-Sy0000001l1m8x83-Syk3-Zyk0k0");
    temp = The_type_description_of_edit_state;
    The_type_description_of_edit_state = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_4));
    mutate_global_property(Qg2_defstruct_structure_name_edit_state_g2_struct,
	    The_type_description_of_edit_state,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qedit_state,The_type_description_of_edit_state,
	    Qtype_description_of_type);
    Qoutstanding_edit_state_count = 
	    STATIC_SYMBOL("OUTSTANDING-EDIT-STATE-COUNT",AB_package);
    Qedit_state_structure_memory_usage = 
	    STATIC_SYMBOL("EDIT-STATE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_5 = STATIC_STRING("1q83Bsy8s83-SEy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_edit_state_count);
    push_optimized_constant(Qedit_state_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_5));
    Qchain_of_available_edit_states = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EDIT-STATES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_edit_states,
	    Chain_of_available_edit_states);
    record_system_variable(Qchain_of_available_edit_states,Qutilities2,Nil,
	    Qnil,Qt,Qnil,Qnil);
    Qedit_state_count = STATIC_SYMBOL("EDIT-STATE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qedit_state_count,Edit_state_count);
    record_system_variable(Qedit_state_count,Qutilities2,FIX((SI_Long)0L),
	    Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qedit_state_structure_memory_usage,
	    STATIC_FUNCTION(edit_state_structure_memory_usage,NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_edit_state_count,
	    STATIC_FUNCTION(outstanding_edit_state_count,NIL,FALSE,0,0));
    reclaim_structure_for_edit_state_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_edit_state,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qedit_state,
	    reclaim_structure_for_edit_state_1);
    Qediting_and_top_level_is_selection_style = 
	    STATIC_SYMBOL("EDITING-AND-TOP-LEVEL-IS-SELECTION-STYLE",
	    AB_package);
    Qselection_style_of_workstation_context_type = 
	    STATIC_SYMBOL("SELECTION-STYLE-OF-WORKSTATION-CONTEXT-TYPE",
	    AB_package);
    mutate_global_property(Qedit_state,
	    Qediting_and_top_level_is_selection_style,
	    Qselection_style_of_workstation_context_type);
    Qphrase_sequence = STATIC_SYMBOL("PHRASE-SEQUENCE",AB_package);
    if (Phrase_sequence_marker == UNBOUND)
	Phrase_sequence_marker = LIST_1(Qphrase_sequence);
    Qphrase_structure = STATIC_SYMBOL("PHRASE-STRUCTURE",AB_package);
    if (Phrase_structure_marker == UNBOUND)
	Phrase_structure_marker = LIST_1(Qphrase_structure);
    Qphrase_item_denotation = STATIC_SYMBOL("PHRASE-ITEM-DENOTATION",
	    AB_package);
    if (Phrase_item_denotation_marker == UNBOUND)
	Phrase_item_denotation_marker = LIST_1(Qphrase_item_denotation);
    Qphrase_item = STATIC_SYMBOL("PHRASE-ITEM",AB_package);
    if (Phrase_item_marker == UNBOUND)
	Phrase_item_marker = LIST_1(Qphrase_item);
    Qg2_defstruct_structure_name_edit_box_change_g2_struct = 
	    STATIC_SYMBOL("EDIT-BOX-CHANGE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qedit_box_change = STATIC_SYMBOL("EDIT-BOX-CHANGE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_edit_box_change_g2_struct,
	    Qedit_box_change,Qab_name_of_unique_structure_type);
    mutate_global_property(Qedit_box_change,
	    Qg2_defstruct_structure_name_edit_box_change_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_edit_box_change == UNBOUND)
	The_type_description_of_edit_box_change = Nil;
    string_constant_6 = 
	    STATIC_STRING("43Dy8m83h+y1n83h+y8n8k1l8n0000001l1n8y83-3Wy1v83-DZy83-2By83-2Ey83s0y83-2Dy83-2Cy83-89y83-8Ay83-87y83-86y83-88ykwk0k0");
    temp = The_type_description_of_edit_box_change;
    The_type_description_of_edit_box_change = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_6));
    mutate_global_property(Qg2_defstruct_structure_name_edit_box_change_g2_struct,
	    The_type_description_of_edit_box_change,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qedit_box_change,
	    The_type_description_of_edit_box_change,Qtype_description_of_type);
    Qoutstanding_edit_box_change_count = 
	    STATIC_SYMBOL("OUTSTANDING-EDIT-BOX-CHANGE-COUNT",AB_package);
    Qedit_box_change_structure_memory_usage = 
	    STATIC_SYMBOL("EDIT-BOX-CHANGE-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_7 = STATIC_STRING("1q83h+y8s83-S3y09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_edit_box_change_count);
    push_optimized_constant(Qedit_box_change_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_7));
    Qchain_of_available_edit_box_changes = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EDIT-BOX-CHANGES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_edit_box_changes,
	    Chain_of_available_edit_box_changes);
    record_system_variable(Qchain_of_available_edit_box_changes,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qedit_box_change_count = STATIC_SYMBOL("EDIT-BOX-CHANGE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qedit_box_change_count,Edit_box_change_count);
    record_system_variable(Qedit_box_change_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qedit_box_change_structure_memory_usage,
	    STATIC_FUNCTION(edit_box_change_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_edit_box_change_count,
	    STATIC_FUNCTION(outstanding_edit_box_change_count,NIL,FALSE,0,0));
    reclaim_structure_for_edit_box_change_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_edit_box_change,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qedit_box_change,
	    reclaim_structure_for_edit_box_change_1);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qphrase_cons = STATIC_SYMBOL("PHRASE-CONS",AB_package);
    SET_SYMBOL_FUNCTION(Qphrase_cons,STATIC_FUNCTION(phrase_cons,NIL,FALSE,
	    2,2));
    if (Phrase_copying_needs_annotation_rehashing == UNBOUND)
	Phrase_copying_needs_annotation_rehashing = Nil;
    Qbad_phrase = STATIC_SYMBOL("BAD-PHRASE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qbad_phrase,Bad_phrase);
    if (Bad_phrase == UNBOUND)
	Bad_phrase = LIST_1(Qbad_phrase);
    if (Current_transform_constituent_array == UNBOUND)
	Current_transform_constituent_array = Nil;
    if (Current_transform_constituent_count == UNBOUND)
	Current_transform_constituent_count = Nil;
    Qwhole = STATIC_SYMBOL("WHOLE",AB_package);
    Qat = STATIC_SYMBOL("@",AB_package);
    Qgrammar_transform_can_return_bad_phrase_p = 
	    STATIC_SYMBOL("GRAMMAR-TRANSFORM-CAN-RETURN-BAD-PHRASE-P",
	    AB_package);
    Grammar_transform_can_return_bad_phrase_p_prop = 
	    Qgrammar_transform_can_return_bad_phrase_p;
    Qcheck_range_of_element = STATIC_SYMBOL("CHECK-RANGE-OF-ELEMENT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_range_of_element,
	    STATIC_FUNCTION(check_range_of_element,NIL,FALSE,4,4));
    set_grammar_transform_can_return_bad_phrase_p(Qcheck_range_of_element);
    Qreserved_word_p = STATIC_SYMBOL("RESERVED-WORD-P",AB_package);
    Reserved_word_p_prop = Qreserved_word_p;
    if (Last_assigned_grammar_number == UNBOUND)
	Last_assigned_grammar_number = FIX((SI_Long)0L);
    Qg2_defstruct_structure_name_gensym_grammar_g2_struct = 
	    STATIC_SYMBOL("GENSYM-GRAMMAR-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qgensym_grammar = STATIC_SYMBOL("GENSYM-GRAMMAR",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_gensym_grammar_g2_struct,
	    Qgensym_grammar,Qab_name_of_unique_structure_type);
    mutate_global_property(Qgensym_grammar,
	    Qg2_defstruct_structure_name_gensym_grammar_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_gensym_grammar == UNBOUND)
	The_type_description_of_gensym_grammar = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83i-y1n83i-y8n8k1l8n0000001l1n8y83-4=y1l83--Kykwk0k0");
    temp = The_type_description_of_gensym_grammar;
    The_type_description_of_gensym_grammar = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    mutate_global_property(Qg2_defstruct_structure_name_gensym_grammar_g2_struct,
	    The_type_description_of_gensym_grammar,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qgensym_grammar,
	    The_type_description_of_gensym_grammar,Qtype_description_of_type);
    Qoutstanding_gensym_grammar_count = 
	    STATIC_SYMBOL("OUTSTANDING-GENSYM-GRAMMAR-COUNT",AB_package);
    Qgensym_grammar_structure_memory_usage = 
	    STATIC_SYMBOL("GENSYM-GRAMMAR-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_9 = STATIC_STRING("1q83i-y8s83-Vny09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_gensym_grammar_count);
    push_optimized_constant(Qgensym_grammar_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_gensym_grammars = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-GENSYM-GRAMMARS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_gensym_grammars,
	    Chain_of_available_gensym_grammars);
    record_system_variable(Qchain_of_available_gensym_grammars,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qgensym_grammar_count = STATIC_SYMBOL("GENSYM-GRAMMAR-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgensym_grammar_count,Gensym_grammar_count);
    record_system_variable(Qgensym_grammar_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qgensym_grammar_structure_memory_usage,
	    STATIC_FUNCTION(gensym_grammar_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_gensym_grammar_count,
	    STATIC_FUNCTION(outstanding_gensym_grammar_count,NIL,FALSE,0,0));
    reclaim_structure_for_gensym_grammar_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_gensym_grammar,NIL,FALSE,
	    1,1);
    record_direct_structure_method(Qreclaim_structure,Qgensym_grammar,
	    reclaim_structure_for_gensym_grammar_1);
    Qcategory_visit_vector_qm = STATIC_SYMBOL("CATEGORY-VISIT-VECTOR\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcategory_visit_vector_qm,
	    Category_visit_vector_qm);
    Qparse = STATIC_SYMBOL("PARSE",AB_package);
    record_system_variable(Qcategory_visit_vector_qm,Qparse,Nil,Qnil,Qt,
	    Qnil,Qnil);
    Qcurrent_category_visit_stamp = 
	    STATIC_SYMBOL("CURRENT-CATEGORY-VISIT-STAMP",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_category_visit_stamp,
	    Current_category_visit_stamp);
    record_system_variable(Qcurrent_category_visit_stamp,Qparse,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Last_assigned_category_index == UNBOUND)
	Last_assigned_category_index = FIX((SI_Long)-1L);
    Gensym_grammar_prop = Qgensym_grammar;
    Qpunctuation_mark = STATIC_SYMBOL("PUNCTUATION-MARK",AB_package);
    Qwhole_string = STATIC_SYMBOL("WHOLE-STRING",AB_package);
    Qleft_string = STATIC_SYMBOL("LEFT-STRING",AB_package);
    Qmiddle_string = STATIC_SYMBOL("MIDDLE-STRING",AB_package);
    Qright_string = STATIC_SYMBOL("RIGHT-STRING",AB_package);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    list_constant_9 = STATIC_LIST((SI_Long)9L,Qsymbol,Qpunctuation_mark,
	    Qinteger,Qfloat,Qwhole_string,Qleft_string,Qmiddle_string,
	    Qright_string,Qunreserved_symbol);
    if (Required_token_types == UNBOUND)
	Required_token_types = list_constant_9;
    Qglobal_grammar = STATIC_SYMBOL("GLOBAL-GRAMMAR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qglobal_grammar,Global_grammar);
    if (Global_grammar == UNBOUND)
	Global_grammar = make_gensym_grammar(Qglobal_grammar);
    Qcurrent_grammar = STATIC_SYMBOL("CURRENT-GRAMMAR",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_grammar,Current_grammar);
    Kno_initial_value = STATIC_SYMBOL("NO-INITIAL-VALUE",Pkeyword);
    record_system_variable(Qcurrent_grammar,Qparse,Kno_initial_value,Qnil,
	    Qnil,Qnil,Qnil);
    Qcurrent_indicator_for_category_of_this_name = 
	    STATIC_SYMBOL("CURRENT-INDICATOR-FOR-CATEGORY-OF-THIS-NAME",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_indicator_for_category_of_this_name,
	    Current_indicator_for_category_of_this_name);
    record_system_variable(Qcurrent_indicator_for_category_of_this_name,
	    Qparse,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    Qcurrent_indicator_for_category_of_symbol_token = 
	    STATIC_SYMBOL("CURRENT-INDICATOR-FOR-CATEGORY-OF-SYMBOL-TOKEN",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcurrent_indicator_for_category_of_symbol_token,
	    Current_indicator_for_category_of_symbol_token);
    record_system_variable(Qcurrent_indicator_for_category_of_symbol_token,
	    Qparse,Kno_initial_value,Qnil,Qnil,Qnil,Qnil);
    set_current_grammar(Global_grammar);
    Qmost_positive_fixnum_minus_2 = 
	    STATIC_SYMBOL("MOST-POSITIVE-FIXNUM-MINUS-2",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmost_positive_fixnum_minus_2,
	    Most_positive_fixnum_minus_2);
    SET_SYMBOL_VALUE(Qmost_positive_fixnum_minus_2,
	    FIX(IFIX(Most_positive_fixnum) - (SI_Long)2L));
    Qg2_defstruct_structure_name_category_for_token_g2_struct = 
	    STATIC_SYMBOL("CATEGORY-FOR-TOKEN-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcategory_for_token = STATIC_SYMBOL("CATEGORY-FOR-TOKEN",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_category_for_token_g2_struct,
	    Qcategory_for_token,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcategory_for_token,
	    Qg2_defstruct_structure_name_category_for_token_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_category_for_token == UNBOUND)
	The_type_description_of_category_for_token = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83fky1n83fky8n8k1l8n0000001m1n8y83-37y1l83rpy1m830ly83rjyksk0k0");
    temp = The_type_description_of_category_for_token;
    The_type_description_of_category_for_token = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_category_for_token_g2_struct,
	    The_type_description_of_category_for_token,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcategory_for_token,
	    The_type_description_of_category_for_token,
	    Qtype_description_of_type);
    Qoutstanding_category_for_token_count = 
	    STATIC_SYMBOL("OUTSTANDING-CATEGORY-FOR-TOKEN-COUNT",AB_package);
    Qcategory_for_token_structure_memory_usage = 
	    STATIC_SYMBOL("CATEGORY-FOR-TOKEN-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_11 = STATIC_STRING("1q83fky8s83-Ley09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_category_for_token_count);
    push_optimized_constant(Qcategory_for_token_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_category_for_tokens = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CATEGORY-FOR-TOKENS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_category_for_tokens,
	    Chain_of_available_category_for_tokens);
    record_system_variable(Qchain_of_available_category_for_tokens,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcategory_for_token_count = STATIC_SYMBOL("CATEGORY-FOR-TOKEN-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcategory_for_token_count,
	    Category_for_token_count);
    record_system_variable(Qcategory_for_token_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcategory_for_token_structure_memory_usage,
	    STATIC_FUNCTION(category_for_token_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_category_for_token_count,
	    STATIC_FUNCTION(outstanding_category_for_token_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_category_for_token_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_category_for_token,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qcategory_for_token,
	    reclaim_structure_for_category_for_token_1);
    Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct = 
	    STATIC_SYMBOL("CATEGORY-FOR-CATEGORY-SYMBOL-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcategory_for_category_symbol = 
	    STATIC_SYMBOL("CATEGORY-FOR-CATEGORY-SYMBOL",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct,
	    Qcategory_for_category_symbol,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcategory_for_category_symbol,
	    Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_category_for_category_symbol == UNBOUND)
	The_type_description_of_category_for_category_symbol = Nil;
    string_constant_12 = 
	    STATIC_STRING("43Dy8m83fjy1n83fjy8n8k1l8n0000001m1n8y83-36y1l83roy1m830ly83riykxk0k0");
    temp = The_type_description_of_category_for_category_symbol;
    The_type_description_of_category_for_category_symbol = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_12));
    mutate_global_property(Qg2_defstruct_structure_name_category_for_category_symbol_g2_struct,
	    The_type_description_of_category_for_category_symbol,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcategory_for_category_symbol,
	    The_type_description_of_category_for_category_symbol,
	    Qtype_description_of_type);
    Qoutstanding_category_for_category_symbol_count = 
	    STATIC_SYMBOL("OUTSTANDING-CATEGORY-FOR-CATEGORY-SYMBOL-COUNT",
	    AB_package);
    Qcategory_for_category_symbol_structure_memory_usage = 
	    STATIC_SYMBOL("CATEGORY-FOR-CATEGORY-SYMBOL-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_13 = STATIC_STRING("1q83fjy8s83-Ldy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_category_for_category_symbol_count);
    push_optimized_constant(Qcategory_for_category_symbol_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_13));
    Qchain_of_available_category_for_category_symbols = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CATEGORY-FOR-CATEGORY-SYMBOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_category_for_category_symbols,
	    Chain_of_available_category_for_category_symbols);
    record_system_variable(Qchain_of_available_category_for_category_symbols,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcategory_for_category_symbol_count = 
	    STATIC_SYMBOL("CATEGORY-FOR-CATEGORY-SYMBOL-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcategory_for_category_symbol_count,
	    Category_for_category_symbol_count);
    record_system_variable(Qcategory_for_category_symbol_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcategory_for_category_symbol_structure_memory_usage,
	    STATIC_FUNCTION(category_for_category_symbol_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_category_for_category_symbol_count,
	    STATIC_FUNCTION(outstanding_category_for_category_symbol_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_category_for_category_symbol_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_category_for_category_symbol,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcategory_for_category_symbol,
	    reclaim_structure_for_category_for_category_symbol_1);
    Qnot_a_result_category = STATIC_SYMBOL("NOT-A-RESULT-CATEGORY",AB_package);
    Qg2_defstruct_structure_name_category_set_g2_struct = 
	    STATIC_SYMBOL("CATEGORY-SET-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcategory_set = STATIC_SYMBOL("CATEGORY-SET",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_category_set_g2_struct,
	    Qcategory_set,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcategory_set,
	    Qg2_defstruct_structure_name_category_set_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_category_set == UNBOUND)
	The_type_description_of_category_set = Nil;
    string_constant_14 = 
	    STATIC_STRING("43Dy8m83fmy1n83fmy8n8k1l8n0000001l1n8y83-38y1m83rny83rqyknk0k0");
    temp = The_type_description_of_category_set;
    The_type_description_of_category_set = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_14));
    mutate_global_property(Qg2_defstruct_structure_name_category_set_g2_struct,
	    The_type_description_of_category_set,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcategory_set,
	    The_type_description_of_category_set,Qtype_description_of_type);
    Qoutstanding_category_set_count = 
	    STATIC_SYMBOL("OUTSTANDING-CATEGORY-SET-COUNT",AB_package);
    Qcategory_set_structure_memory_usage = 
	    STATIC_SYMBOL("CATEGORY-SET-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_15 = STATIC_STRING("1q83fmy8s83-Liy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_category_set_count);
    push_optimized_constant(Qcategory_set_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_15));
    Qchain_of_available_category_sets = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CATEGORY-SETS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_category_sets,
	    Chain_of_available_category_sets);
    record_system_variable(Qchain_of_available_category_sets,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qcategory_set_count = STATIC_SYMBOL("CATEGORY-SET-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcategory_set_count,Category_set_count);
    record_system_variable(Qcategory_set_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcategory_set_structure_memory_usage,
	    STATIC_FUNCTION(category_set_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_category_set_count,
	    STATIC_FUNCTION(outstanding_category_set_count,NIL,FALSE,0,0));
    reclaim_structure_for_category_set_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_category_set,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qcategory_set,
	    reclaim_structure_for_category_set_1);
    if (Current_subcategory_path == UNBOUND)
	Current_subcategory_path = make_array(1,Max_instance_rule_chaining);
    if (Currently_tracking_subcategory_path_max == UNBOUND)
	Currently_tracking_subcategory_path_max = FIX((SI_Long)0L);
    Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct = 
	    STATIC_SYMBOL("STRICT-SUBCATEGORY-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qstrict_subcategory_info = STATIC_SYMBOL("STRICT-SUBCATEGORY-INFO",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct,
	    Qstrict_subcategory_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qstrict_subcategory_info,
	    Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_strict_subcategory_info == UNBOUND)
	The_type_description_of_strict_subcategory_info = Nil;
    string_constant_16 = 
	    STATIC_STRING("43Dy8m9k1n9k8n8k1l8n0000001l1n8y83-60y1n83-Dry83-Dty83-Dsykok0k0");
    temp = The_type_description_of_strict_subcategory_info;
    clear_optimized_constants();
    push_optimized_constant(Qstrict_subcategory_info);
    The_type_description_of_strict_subcategory_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_16));
    mutate_global_property(Qg2_defstruct_structure_name_strict_subcategory_info_g2_struct,
	    The_type_description_of_strict_subcategory_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qstrict_subcategory_info,
	    The_type_description_of_strict_subcategory_info,
	    Qtype_description_of_type);
    Qoutstanding_strict_subcategory_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-STRICT-SUBCATEGORY-INFO-COUNT",
	    AB_package);
    Qstrict_subcategory_info_structure_memory_usage = 
	    STATIC_SYMBOL("STRICT-SUBCATEGORY-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_17 = STATIC_STRING("1q9k8s83-pWy09l9m");
    clear_optimized_constants();
    push_optimized_constant(Qstrict_subcategory_info);
    push_optimized_constant(Qoutstanding_strict_subcategory_info_count);
    push_optimized_constant(Qstrict_subcategory_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_17));
    Qchain_of_available_strict_subcategory_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-STRICT-SUBCATEGORY-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_strict_subcategory_infos,
	    Chain_of_available_strict_subcategory_infos);
    record_system_variable(Qchain_of_available_strict_subcategory_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qstrict_subcategory_info_count = 
	    STATIC_SYMBOL("STRICT-SUBCATEGORY-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qstrict_subcategory_info_count,
	    Strict_subcategory_info_count);
    record_system_variable(Qstrict_subcategory_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qstrict_subcategory_info_structure_memory_usage,
	    STATIC_FUNCTION(strict_subcategory_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_strict_subcategory_info_count,
	    STATIC_FUNCTION(outstanding_strict_subcategory_info_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_strict_subcategory_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_strict_subcategory_info,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qstrict_subcategory_info,
	    reclaim_structure_for_strict_subcategory_info_1);
    if (Strict_subcategory_infos_exist_p == UNBOUND)
	Strict_subcategory_infos_exist_p = Nil;
    if (Strict_subcategory_info_last_category_1 == UNBOUND)
	Strict_subcategory_info_last_category_1 = Nil;
    if (Strict_subcategory_info_last_category_2 == UNBOUND)
	Strict_subcategory_info_last_category_2 = Nil;
    if (Strict_subcategory_info_last_result == UNBOUND)
	Strict_subcategory_info_last_result = Nil;
    list_constant_10 = STATIC_CONS(Qglobal_grammar,Qnil);
    if (Names_of_grammars_to_add_rules_to == UNBOUND)
	Names_of_grammars_to_add_rules_to = list_constant_10;
    SET_SYMBOL_FUNCTION(Qstrict_subcategory_info,
	    STATIC_FUNCTION(strict_subcategory_info,NIL,FALSE,2,2));
    Qcategory_symbols_for_symbol_token = 
	    STATIC_SYMBOL("CATEGORY-SYMBOLS-FOR-SYMBOL-TOKEN",AB_package);
    Kb_specific_property_names = CONS(Qcategory_symbols_for_symbol_token,
	    Kb_specific_property_names);
    mutate_global_property(Qcategory_symbols_for_symbol_token,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    Qreclaim_grammar_list_function = 
	    STATIC_SYMBOL("RECLAIM-GRAMMAR-LIST-FUNCTION",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_grammar_list_function,
	    STATIC_FUNCTION(reclaim_grammar_list_function,NIL,FALSE,1,1));
    mutate_global_property(Qcategory_symbols_for_symbol_token,
	    Qreclaim_grammar_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Category_symbols_for_symbol_token_kbprop = 
	    Qcategory_symbols_for_symbol_token;
    Qsymbol_tokens_for_category_symbol = 
	    STATIC_SYMBOL("SYMBOL-TOKENS-FOR-CATEGORY-SYMBOL",AB_package);
    Kb_specific_property_names = CONS(Qsymbol_tokens_for_category_symbol,
	    Kb_specific_property_names);
    mutate_global_property(Qsymbol_tokens_for_category_symbol,T,
	    Qdo_not_carry_global_property_value_into_kbs_qm);
    mutate_global_property(Qsymbol_tokens_for_category_symbol,
	    Qreclaim_grammar_list_function,
	    Qfunction_to_reclaim_kb_specific_property_value_qm);
    Symbol_tokens_for_category_symbol_kbprop = 
	    Qsymbol_tokens_for_category_symbol;
    Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct = 
	    STATIC_SYMBOL("PHRASE-RULE-COMPLETION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qphrase_rule_completion = STATIC_SYMBOL("PHRASE-RULE-COMPLETION",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct,
	    Qphrase_rule_completion,Qab_name_of_unique_structure_type);
    mutate_global_property(Qphrase_rule_completion,
	    Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_phrase_rule_completion == UNBOUND)
	The_type_description_of_phrase_rule_completion = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83lZy1n83lZy8n8k1l8n0000001m1n8y83-56y1n83rgy83rmy83-8ty1m83=ey3-Wykpk0k0");
    temp = The_type_description_of_phrase_rule_completion;
    The_type_description_of_phrase_rule_completion = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_18));
    mutate_global_property(Qg2_defstruct_structure_name_phrase_rule_completion_g2_struct,
	    The_type_description_of_phrase_rule_completion,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qphrase_rule_completion,
	    The_type_description_of_phrase_rule_completion,
	    Qtype_description_of_type);
    Qoutstanding_phrase_rule_completion_count = 
	    STATIC_SYMBOL("OUTSTANDING-PHRASE-RULE-COMPLETION-COUNT",
	    AB_package);
    Qphrase_rule_completion_structure_memory_usage = 
	    STATIC_SYMBOL("PHRASE-RULE-COMPLETION-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q83lZy8s83-hly09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_phrase_rule_completion_count);
    push_optimized_constant(Qphrase_rule_completion_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_phrase_rule_completions = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PHRASE-RULE-COMPLETIONS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_phrase_rule_completions,
	    Chain_of_available_phrase_rule_completions);
    record_system_variable(Qchain_of_available_phrase_rule_completions,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qphrase_rule_completion_count = 
	    STATIC_SYMBOL("PHRASE-RULE-COMPLETION-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qphrase_rule_completion_count,
	    Phrase_rule_completion_count);
    record_system_variable(Qphrase_rule_completion_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qphrase_rule_completion_structure_memory_usage,
	    STATIC_FUNCTION(phrase_rule_completion_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_phrase_rule_completion_count,
	    STATIC_FUNCTION(outstanding_phrase_rule_completion_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_phrase_rule_completion_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_phrase_rule_completion,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qphrase_rule_completion,
	    reclaim_structure_for_phrase_rule_completion_1);
    Batch_parsing_engaged_p = Nil;
    Qg2_defstruct_structure_name_incomplete_phrase_g2_struct = 
	    STATIC_SYMBOL("INCOMPLETE-PHRASE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qincomplete_phrase = STATIC_SYMBOL("INCOMPLETE-PHRASE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_incomplete_phrase_g2_struct,
	    Qincomplete_phrase,Qab_name_of_unique_structure_type);
    mutate_global_property(Qincomplete_phrase,
	    Qg2_defstruct_structure_name_incomplete_phrase_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_incomplete_phrase == UNBOUND)
	The_type_description_of_incomplete_phrase = Nil;
    string_constant_20 = 
	    STATIC_STRING("43Dy8m83j1y1n83j1y8n8k1l8n0000001l1n8y83-4cy1o83-8sy83-=Qy83-=Py83-=Oykpk0k0");
    temp = The_type_description_of_incomplete_phrase;
    The_type_description_of_incomplete_phrase = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_20));
    mutate_global_property(Qg2_defstruct_structure_name_incomplete_phrase_g2_struct,
	    The_type_description_of_incomplete_phrase,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qincomplete_phrase,
	    The_type_description_of_incomplete_phrase,
	    Qtype_description_of_type);
    Qoutstanding_incomplete_phrase_count = 
	    STATIC_SYMBOL("OUTSTANDING-INCOMPLETE-PHRASE-COUNT",AB_package);
    Qincomplete_phrase_structure_memory_usage = 
	    STATIC_SYMBOL("INCOMPLETE-PHRASE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_21 = STATIC_STRING("1q83j1y8s83-Yoy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_incomplete_phrase_count);
    push_optimized_constant(Qincomplete_phrase_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_21));
    Qchain_of_available_incomplete_phrases = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INCOMPLETE-PHRASES",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_incomplete_phrases,
	    Chain_of_available_incomplete_phrases);
    record_system_variable(Qchain_of_available_incomplete_phrases,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qincomplete_phrase_count = STATIC_SYMBOL("INCOMPLETE-PHRASE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qincomplete_phrase_count,
	    Incomplete_phrase_count);
    record_system_variable(Qincomplete_phrase_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qincomplete_phrase_structure_memory_usage,
	    STATIC_FUNCTION(incomplete_phrase_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_incomplete_phrase_count,
	    STATIC_FUNCTION(outstanding_incomplete_phrase_count,NIL,FALSE,
	    0,0));
    reclaim_structure_for_incomplete_phrase_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_incomplete_phrase,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qincomplete_phrase,
	    reclaim_structure_for_incomplete_phrase_1);
    Qproc_compound_statement = STATIC_SYMBOL("PROC-COMPOUND-STATEMENT",
	    AB_package);
    Qproc_simple_statement = STATIC_SYMBOL("PROC-SIMPLE-STATEMENT",AB_package);
    Qunique_literal = STATIC_SYMBOL("UNIQUE-LITERAL",AB_package);
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    list_constant = STATIC_CONS(Qnil,Qnil);
    Qirrelevant = STATIC_SYMBOL("IRRELEVANT",AB_package);
    Qregistered_directory_of_names_p = 
	    STATIC_SYMBOL("REGISTERED-DIRECTORY-OF-NAMES-P",AB_package);
    Registered_directory_of_names_p_prop = Qregistered_directory_of_names_p;
    Qregistered_abstract_integer_category_p = 
	    STATIC_SYMBOL("REGISTERED-ABSTRACT-INTEGER-CATEGORY-P",AB_package);
    Registered_abstract_integer_category_p_prop = 
	    Qregistered_abstract_integer_category_p;
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    mutate_global_property(Qpriority,T,
	    Qregistered_abstract_integer_category_p);
    Qnon_negative_integer = STATIC_SYMBOL("NON-NEGATIVE-INTEGER",AB_package);
    mutate_global_property(Qnon_negative_integer,T,
	    Qregistered_abstract_integer_category_p);
    Qpositive_integer = STATIC_SYMBOL("POSITIVE-INTEGER",AB_package);
    mutate_global_property(Qpositive_integer,T,
	    Qregistered_abstract_integer_category_p);
    Maximum_size_of_token_sequence = FIX((SI_Long)60L);
    Qend = STATIC_SYMBOL("END",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    Qmenu_too_many_instances = STATIC_SYMBOL("MENU-TOO-MANY-INSTANCES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qmenu_too_many_instances,
	    Menu_too_many_instances);
    Qtoo_many_instances = STATIC_SYMBOL("TOO-MANY-INSTANCES",AB_package);
    list_constant_11 = STATIC_CONS(Qtoo_many_instances,Qnil);
    SET_SYMBOL_VALUE(Qmenu_too_many_instances,list_constant_11);
    Qobject_name = STATIC_SYMBOL("OBJECT-NAME",AB_package);
    Qobject_name_menus_in_upper_case_qm = 
	    STATIC_SYMBOL("OBJECT-NAME-MENUS-IN-UPPER-CASE\?",AB_package);
    Qomit_from_quoted_token_menus_p = 
	    STATIC_SYMBOL("OMIT-FROM-QUOTED-TOKEN-MENUS-P",AB_package);
    Omit_from_quoted_token_menus_p_prop = Qomit_from_quoted_token_menus_p;
    Qoverriding_token_instances_without_specific_categories = 
	    STATIC_SYMBOL("OVERRIDING-TOKEN-INSTANCES-WITHOUT-SPECIFIC-CATEGORIES",
	    AB_package);
    Overriding_token_instances_without_specific_categories_prop = 
	    Qoverriding_token_instances_without_specific_categories;
    Qjan = STATIC_SYMBOL("JAN",AB_package);
    Qfeb = STATIC_SYMBOL("FEB",AB_package);
    Qmar = STATIC_SYMBOL("MAR",AB_package);
    Qapr = STATIC_SYMBOL("APR",AB_package);
    Qmay = STATIC_SYMBOL("MAY",AB_package);
    Qjun = STATIC_SYMBOL("JUN",AB_package);
    Qjul = STATIC_SYMBOL("JUL",AB_package);
    Qaug = STATIC_SYMBOL("AUG",AB_package);
    Qsep = STATIC_SYMBOL("SEP",AB_package);
    Qoct = STATIC_SYMBOL("OCT",AB_package);
    Qnov = STATIC_SYMBOL("NOV",AB_package);
    Qdec = STATIC_SYMBOL("DEC",AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)12L,Qjan,Qfeb,Qmar,Qapr,Qmay,
	    Qjun,Qjul,Qaug,Qsep,Qoct,Qnov,Qdec);
    Months_of_the_year = list_constant_12;
    Qmonth = STATIC_SYMBOL("MONTH",AB_package);
    mutate_global_property(Qmonth,Months_of_the_year,
	    Qoverriding_token_instances_without_specific_categories);
    if (One_sequence_of_following_tokens_only_p == UNBOUND)
	One_sequence_of_following_tokens_only_p = Nil;
    Qfunction_name = STATIC_SYMBOL("FUNCTION-NAME",AB_package);
    Qaverage = STATIC_SYMBOL("AVERAGE",AB_package);
    Qhour = STATIC_SYMBOL("HOUR",AB_package);
    Qminute = STATIC_SYMBOL("MINUTE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qaverage,Qhour,Qminute,
	    Qsecond,Qsymbol);
    list_constant_2 = STATIC_CONS(Qinteger,Qnil);
    if (Prune_token_categories_visited_more_than_once_p == UNBOUND)
	Prune_token_categories_visited_more_than_once_p = Nil;
    if (List_of_argument_lists_to_add_menu_items_for_category == UNBOUND)
	List_of_argument_lists_to_add_menu_items_for_category = Nil;
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    SET_SYMBOL_FUNCTION(Qsimplify_associative_operation,
	    STATIC_FUNCTION(simplify_associative_operation,NIL,FALSE,1,1));
    list_constant_3 = STATIC_CONS(Qsimplify_associative_operation,Qnil);
    string_constant = STATIC_STRING("~a-TAIL");
    list_constant_4 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_5 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1L),
	    FIX((SI_Long)3L));
    Qnil_function = STATIC_SYMBOL("NIL-FUNCTION",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qnil,Qnil_function);
    string_constant_1 = STATIC_STRING("~a-1");
    list_constant_7 = STATIC_CONS(FIX((SI_Long)2L),list_constant_5);
    list_constant_8 = STATIC_LIST((SI_Long)3L,FIX((SI_Long)2L),
	    FIX((SI_Long)1L),FIX((SI_Long)4L));
    Qlist_phrase_noise_symbols = STATIC_SYMBOL("LIST-PHRASE-NOISE-SYMBOLS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qlist_phrase_noise_symbols,
	    List_phrase_noise_symbols);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qcol = STATIC_SYMBOL(":",AB_package);
    list_constant_13 = STATIC_LIST((SI_Long)5L,Qand,Qab_or,Qcm,Qsc,Qcol);
    SET_SYMBOL_VALUE(Qlist_phrase_noise_symbols,list_constant_13);
    if (Semi_open_category_map == UNBOUND)
	Semi_open_category_map = Nil;
    Qremote_process_initialization_string = 
	    STATIC_SYMBOL("REMOTE-PROCESS-INITIALIZATION-STRING",AB_package);
    Qsystem_attribute = STATIC_SYMBOL("SYSTEM-ATTRIBUTE",AB_package);
    if (Symbols_not_to_add_to_semi_open_category_directories == UNBOUND)
	Symbols_not_to_add_to_semi_open_category_directories = Nil;
}
