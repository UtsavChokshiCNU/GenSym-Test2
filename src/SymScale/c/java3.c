/* java3.c
 * Input file:  java3.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "java3.h"


Object The_type_description_of_external_class_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_external_class_infos, Qchain_of_available_external_class_infos);

DEFINE_VARIABLE_WITH_SYMBOL(External_class_info_count, Qexternal_class_info_count);

Object Chain_of_available_external_class_infos_vector = UNBOUND;

/* EXTERNAL-CLASS-INFO-STRUCTURE-MEMORY-USAGE */
Object external_class_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(251,0);
    temp = External_class_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)4L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EXTERNAL-CLASS-INFO-COUNT */
Object outstanding_external_class_info_count()
{
    Object def_structure_external_class_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(251,1);
    gensymed_symbol = IFIX(External_class_info_count);
    def_structure_external_class_info_variable = 
	    Chain_of_available_external_class_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_external_class_info_variable))
	goto end_loop;
    def_structure_external_class_info_variable = 
	    ISVREF(def_structure_external_class_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EXTERNAL-CLASS-INFO-1 */
Object reclaim_external_class_info_1(external_class_info)
    Object external_class_info;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(251,2);
    inline_note_reclaim_cons(external_class_info,Nil);
    structure_being_reclaimed = external_class_info;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_list_of_external_methods(ISVREF(external_class_info,
	      (SI_Long)2L));
      SVREF(external_class_info,FIX((SI_Long)2L)) = Nil;
      reclaim_list_of_external_methods(ISVREF(external_class_info,
	      (SI_Long)3L));
      SVREF(external_class_info,FIX((SI_Long)3L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_external_class_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(external_class_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_external_class_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = external_class_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EXTERNAL-CLASS-INFO */
Object reclaim_structure_for_external_class_info(external_class_info)
    Object external_class_info;
{
    x_note_fn_call(251,3);
    return reclaim_external_class_info_1(external_class_info);
}

static Object Qg2_defstruct_structure_name_external_class_info_g2_struct;  /* g2-defstruct-structure-name::external-class-info-g2-struct */

/* MAKE-PERMANENT-EXTERNAL-CLASS-INFO-STRUCTURE-INTERNAL */
Object make_permanent_external_class_info_structure_internal()
{
    Object def_structure_external_class_info_variable;
    Object defstruct_g2_external_class_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(251,4);
    def_structure_external_class_info_variable = Nil;
    atomic_incff_symval(Qexternal_class_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_external_class_info_variable = Nil;
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
	defstruct_g2_external_class_info_variable = the_array;
	SVREF(defstruct_g2_external_class_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_external_class_info_g2_struct;
	def_structure_external_class_info_variable = 
		defstruct_g2_external_class_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_external_class_info_variable);
}

/* MAKE-EXTERNAL-CLASS-INFO-1 */
Object make_external_class_info_1(external_class_name,
	    external_static_methods,external_instance_methods)
    Object external_class_name, external_static_methods;
    Object external_instance_methods;
{
    Object def_structure_external_class_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(251,5);
    def_structure_external_class_info_variable = 
	    ISVREF(Chain_of_available_external_class_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_external_class_info_variable) {
	svref_arg_1 = Chain_of_available_external_class_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_external_class_info_variable,(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_external_class_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_external_class_info_g2_struct;
    }
    else
	def_structure_external_class_info_variable = 
		make_permanent_external_class_info_structure_internal();
    inline_note_allocate_cons(def_structure_external_class_info_variable,Nil);
    SVREF(def_structure_external_class_info_variable,FIX((SI_Long)1L)) = 
	    external_class_name;
    SVREF(def_structure_external_class_info_variable,FIX((SI_Long)2L)) = 
	    external_static_methods;
    SVREF(def_structure_external_class_info_variable,FIX((SI_Long)3L)) = 
	    external_instance_methods;
    return VALUES_1(def_structure_external_class_info_variable);
}

/* RECLAIM-EXTERNAL-CLASS-INFO-LIST */
Object reclaim_external_class_info_list(external_class_info_list)
    Object external_class_info_list;
{
    Object external_class_info, ab_loop_list_;

    x_note_fn_call(251,6);
    external_class_info = Nil;
    ab_loop_list_ = external_class_info_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    external_class_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_external_class_info_1(external_class_info);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(external_class_info_list);
    return VALUES_1(Nil);
}

/* DELETE-EXPORT-FRAME-IF-ANY */
Object delete_export_frame_if_any(frame_qm)
    Object frame_qm;
{
    Object analyzing_export_definition_for_consistency_p;
    Declare_special(1);

    x_note_fn_call(251,7);
    if (frame_qm) {
	analyzing_export_definition_for_consistency_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Analyzing_export_definition_for_consistency_p,Qanalyzing_export_definition_for_consistency_p,analyzing_export_definition_for_consistency_p,
		0);
	  delete_frame(frame_qm);
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

Object The_type_description_of_external_method_info = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_external_method_infos, Qchain_of_available_external_method_infos);

DEFINE_VARIABLE_WITH_SYMBOL(External_method_info_count, Qexternal_method_info_count);

Object Chain_of_available_external_method_infos_vector = UNBOUND;

/* EXTERNAL-METHOD-INFO-STRUCTURE-MEMORY-USAGE */
Object external_method_info_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(251,8);
    temp = External_method_info_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)11L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-EXTERNAL-METHOD-INFO-COUNT */
Object outstanding_external_method_info_count()
{
    Object def_structure_external_method_info_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(251,9);
    gensymed_symbol = IFIX(External_method_info_count);
    def_structure_external_method_info_variable = 
	    Chain_of_available_external_method_infos;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_external_method_info_variable))
	goto end_loop;
    def_structure_external_method_info_variable = 
	    ISVREF(def_structure_external_method_info_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-EXTERNAL-METHOD-INFO-1 */
Object reclaim_external_method_info_1(external_method_info)
    Object external_method_info;
{
    Object structure_being_reclaimed, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(251,10);
    inline_note_reclaim_cons(external_method_info,Nil);
    structure_being_reclaimed = external_method_info;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_gensym_list_1(ISVREF(external_method_info,(SI_Long)4L));
      SVREF(external_method_info,FIX((SI_Long)4L)) = Nil;
      reclaim_gensym_list_1(ISVREF(external_method_info,(SI_Long)5L));
      SVREF(external_method_info,FIX((SI_Long)5L)) = Nil;
      reclaim_gensym_list_1(ISVREF(external_method_info,(SI_Long)6L));
      SVREF(external_method_info,FIX((SI_Long)6L)) = Nil;
      delete_export_frame_if_any(ISVREF(external_method_info,(SI_Long)8L));
      SVREF(external_method_info,FIX((SI_Long)8L)) = Nil;
      delete_export_frame_if_any(ISVREF(external_method_info,(SI_Long)9L));
      SVREF(external_method_info,FIX((SI_Long)9L)) = Nil;
      reclaim_text_or_gensym_string_if_any(ISVREF(external_method_info,
	      (SI_Long)10L));
      SVREF(external_method_info,FIX((SI_Long)10L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_external_method_infos_vector,
	    IFIX(Current_thread_index));
    SVREF(external_method_info,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_external_method_infos_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = external_method_info;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-EXTERNAL-METHOD-INFO */
Object reclaim_structure_for_external_method_info(external_method_info)
    Object external_method_info;
{
    x_note_fn_call(251,11);
    return reclaim_external_method_info_1(external_method_info);
}

static Object Qg2_defstruct_structure_name_external_method_info_g2_struct;  /* g2-defstruct-structure-name::external-method-info-g2-struct */

/* MAKE-PERMANENT-EXTERNAL-METHOD-INFO-STRUCTURE-INTERNAL */
Object make_permanent_external_method_info_structure_internal()
{
    Object def_structure_external_method_info_variable;
    Object defstruct_g2_external_method_info_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(251,12);
    def_structure_external_method_info_variable = Nil;
    atomic_incff_symval(Qexternal_method_info_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_external_method_info_variable = Nil;
	gensymed_symbol = (SI_Long)11L;
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
	defstruct_g2_external_method_info_variable = the_array;
	SVREF(defstruct_g2_external_method_info_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_external_method_info_g2_struct;
	def_structure_external_method_info_variable = 
		defstruct_g2_external_method_info_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_external_method_info_variable);
}

/* MAKE-EXTERNAL-METHOD-INFO-INTERNAL-1 */
Object make_external_method_info_internal_1(cached_external_method_class,
	    cached_external_method_name,external_method_static_p,
	    instance_method_declaration_frame,instance_method_frame_qm,
	    external_method_signature)
    Object cached_external_method_class, cached_external_method_name;
    Object external_method_static_p, instance_method_declaration_frame;
    Object instance_method_frame_qm, external_method_signature;
{
    Object def_structure_external_method_info_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(251,13);
    def_structure_external_method_info_variable = 
	    ISVREF(Chain_of_available_external_method_infos_vector,
	    IFIX(Current_thread_index));
    if (def_structure_external_method_info_variable) {
	svref_arg_1 = Chain_of_available_external_method_infos_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_external_method_info_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	SVREF(def_structure_external_method_info_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_external_method_info_g2_struct;
    }
    else
	def_structure_external_method_info_variable = 
		make_permanent_external_method_info_structure_internal();
    inline_note_allocate_cons(def_structure_external_method_info_variable,Nil);
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)1L)) = 
	    cached_external_method_class;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)2L)) = 
	    cached_external_method_name;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)7L)) = 
	    external_method_static_p;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)8L)) = 
	    instance_method_declaration_frame;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)9L)) = 
	    instance_method_frame_qm;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)4L)) = 
	    external_method_signature;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)5L)) = Nil;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)6L)) = Nil;
    SVREF(def_structure_external_method_info_variable,FIX((SI_Long)10L)) = Nil;
    return VALUES_1(def_structure_external_method_info_variable);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* RECLAIM-CLASS-EXPORT-INFORMATION-IF-ANY */
Object reclaim_class_export_information_if_any(export_info)
    Object export_info;
{
    Object x2;
    char temp;

    x_note_fn_call(251,14);
    if (SIMPLE_VECTOR_P(export_info) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(export_info)) > (SI_Long)2L &&  
	    !EQ(ISVREF(export_info,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(export_info,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	delete_frame(export_info);
    return VALUES_1(Nil);
}

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "~A::~A" */

static Object string_constant_1;   /* "KEYWORD" */

/* MAKE-EXTERNAL-METHOD-INFO */
Object make_external_method_info(method_class,method_name,g2_procedure,
	    external_method_static_p,method_declaration_frame_qm,
	    method_frame_qm)
    Object method_class, method_name, g2_procedure, external_method_static_p;
    Object method_declaration_frame_qm, method_frame_qm;
{
    Object external_method_info, svref_new_value, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(251,15);
    external_method_info = 
	    make_external_method_info_internal_1(method_class,method_name,
	    external_method_static_p,method_declaration_frame_qm,
	    method_frame_qm,
	    collect_types_into_list_using_gensym_conses(ISVREF(g2_procedure,
	    (SI_Long)24L)));
    if (external_method_static_p)
	svref_new_value = method_name;
    else {
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
		  tformat(3,string_constant,method_class,method_name);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	svref_new_value = intern_text_string(2,temp,string_constant_1);
    }
    SVREF(external_method_info,FIX((SI_Long)3L)) = svref_new_value;
    return VALUES_1(external_method_info);
}

/* RECLAIM-LIST-OF-EXTERNAL-METHODS */
Object reclaim_list_of_external_methods(external_methods)
    Object external_methods;
{
    Object external_method, ab_loop_list_;

    x_note_fn_call(251,16);
    external_method = Nil;
    ab_loop_list_ = external_methods;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    external_method = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_external_method_info_1(external_method);
    goto next_loop;
  end_loop:;
    reclaim_slot_value_list_1(external_methods);
    return VALUES_1(Nil);
}

static Object Qsignal_statement_new;  /* signal-statement-new */

/* WALK-FOR-SIGNALED-DESIGNATIONS */
Object walk_for_signaled_designations(parsed_definition,accum)
    Object parsed_definition, accum;
{
    Object temp;

    x_note_fn_call(251,17);
    if (ATOM(parsed_definition))
	temp = accum;
    else if (EQ(CAR(parsed_definition),Qsignal_statement_new))
	temp = gensym_cons_1(CADR(parsed_definition),accum);
    else {
	temp = CAR(parsed_definition);
	temp = walk_for_signaled_designations(temp,
		walk_for_signaled_designations(CDR(parsed_definition),accum));
    }
    return VALUES_1(temp);
}

static Object Qab_class;           /* class */

static Object Qitem;               /* item */

/* CHASE-SIGNALED-CLASS-IF-ANY */
Object chase_signaled_class_if_any(designation,parsed_definition)
    Object designation, parsed_definition;
{
    Object local_name, local_type, ab_loop_list_, ab_loop_it_, ab_loop_desetq_;
    Object temp, arg_name, arg_type, global_qm;

    x_note_fn_call(251,18);
    if (SYMBOLP(designation)) {
	local_name = Nil;
	local_type = Nil;
	ab_loop_list_ = FOURTH(parsed_definition);
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	local_name = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	local_type = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQ(local_name,designation) && CONSP(local_type) && 
		EQ(CAR(local_type),Qab_class) ? SECOND(local_type) : Qnil;
	if (ab_loop_it_) {
	    temp = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp = Qnil;
      end_1:;
	if (temp);
	else {
	    arg_name = Nil;
	    arg_type = Nil;
	    ab_loop_list_ = SECOND(parsed_definition);
	    ab_loop_it_ = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    arg_name = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    arg_type = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = EQ(arg_name,designation) && CONSP(arg_type) && 
		    EQ(CAR(arg_type),Qab_class) ? SECOND(arg_type) : Qnil;
	    if (ab_loop_it_) {
		temp = ab_loop_it_;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = Qnil;
	  end_2:;
	}
	if (temp);
	else {
	    global_qm = get_instance_with_name_if_any(Qitem,designation);
	    temp = global_qm ? ISVREF(ISVREF(global_qm,(SI_Long)1L),
		    (SI_Long)1L) : Qnil;
	}
    }
    else
	temp = Qerror;
    return VALUES_1(temp);
}

static Object Qprocedure_definition;  /* procedure-definition */

/* COLLECT-CLASSES-SIGNALED-IN-PROCEDURE */
Object collect_classes_signaled_in_procedure(g2_procedure)
    Object g2_procedure;
{
    Object signaled_classes, temp, procedure_text_qm, gensymed_symbol;
    Object gensymed_symbol_1, current_edit_state, svref_arg_1;
    Object definition_as_text_string, parsed_definition, signaled_designations;
    Object designation, ab_loop_list_, known_class_qm;
    Object gensym_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__1, ab_loop_it_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(251,19);
    signaled_classes = Nil;
    temp = ISVREF(g2_procedure,(SI_Long)27L);
    procedure_text_qm = CDR(temp);
    if (procedure_text_qm) {
	gensymed_symbol = Current_edit_state;
	if (Generate_source_annotation_info) {
	    gensymed_symbol_1 = Current_edit_state ? 
		    get_current_sexp_annotation_hash() : Nil;
	    if (gensymed_symbol_1);
	    else
		gensymed_symbol_1 = make_sexp_annotation_hash();
	}
	else
	    gensymed_symbol_1 = Nil;
	current_edit_state = make_edit_state_1();
	PUSH_SPECIAL_WITH_SYMBOL(Current_edit_state,Qcurrent_edit_state,current_edit_state,
		0);
	  svref_arg_1 = Current_edit_state;
	  SVREF(svref_arg_1,FIX((SI_Long)90L)) = gensymed_symbol_1;
	  definition_as_text_string = convert_text_to_text_string(1,
		  procedure_text_qm);
	  parsed_definition = parse_text_string(2,
		  definition_as_text_string,Qprocedure_definition);
	  signaled_designations = 
		  walk_for_signaled_designations(parsed_definition,Nil);
	  reclaim_text_string(definition_as_text_string);
	  designation = Nil;
	  ab_loop_list_ = signaled_designations;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  designation = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  known_class_qm = chase_signaled_class_if_any(designation,
		  parsed_definition);
	  if (known_class_qm) {
	      gensym_modify_macro_using_test_arg_1 = known_class_qm;
	      car_1 = gensym_modify_macro_using_test_arg_1;
	      cdr_1 = signaled_classes;
	      key_result = car_1;
	      x_element = Nil;
	      ab_loop_list__1 = cdr_1;
	      ab_loop_it_ = Nil;
	    next_loop_1:
	      if ( !TRUEP(ab_loop_list__1))
		  goto end_loop_1;
	      x_element = M_CAR(ab_loop_list__1);
	      ab_loop_list__1 = M_CDR(ab_loop_list__1);
	      ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	      if (ab_loop_it_) {
		  temp_1 = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop_1;
	    end_loop_1:
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	      signaled_classes = temp_1 ? cdr_1 : gensym_cons_1(car_1,cdr_1);
	  }
	  goto next_loop;
	end_loop:;
	  reclaim_gensym_list_1(signaled_designations);
	  if (gensymed_symbol) {
	      svref_arg_1 = Current_edit_state;
	      SVREF(svref_arg_1,FIX((SI_Long)90L)) = Nil;
	  }
	  reclaim_edit_state_1(Current_edit_state);
	POP_SPECIAL();
    }
    temp = nreverse(signaled_classes);
    return VALUES_1(temp);
}

static Object Qexport_definition_specification;  /* export-definition-specification */

static Object Qjava;               /* java */

static Object list_constant;       /* # */

/* COLLECT-EXPORT-INFO-FOR-ALL-CLASSES */
Object collect_export_info_for_all_classes(export_definition)
    Object export_definition;
{
    Object definition_spec, language, export_specs, export_class, export_type;
    Object options, ab_loop_list_, classes_encountered, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_, temp;

    x_note_fn_call(251,20);
    definition_spec = 
	    get_lookup_slot_value_given_default(export_definition,
	    Qexport_definition_specification,Nil);
    language = CAR(definition_spec);
    export_specs = CADR(definition_spec);
    if (EQ(language,Qjava)) {
	export_class = Nil;
	export_type = Nil;
	options = Nil;
	ab_loop_list_ = export_specs;
	classes_encountered = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	export_class = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	export_type = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	options = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	classes_encountered = java_cons_1(export_class,classes_encountered);
	if (memq_function(export_type,list_constant) &&  
		!TRUEP(memq_function(export_class,CDR(classes_encountered)))) {
	    ab_loopvar__2 = 
		    slot_value_cons_1(make_export_info_for_one_class(export_class,
		    options),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	reclaim_java_list_1(classes_encountered);
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qstatic_methods;     /* static-methods */

/* MAKE-EXPORT-INFO-FOR-ONE-CLASS */
Object make_export_info_for_one_class(export_class,options)
    Object export_class, options;
{
    Object temp, static_methods, instance_methods;

    x_note_fn_call(251,21);
    temp = assq_function(Qstatic_methods,options);
    static_methods = collect_static_method_export_info(export_class,
	    CADR(temp));
    instance_methods = collect_instance_method_export_info(2,export_class,
	    options);
    temp = make_external_class_info_1(export_class,static_methods,
	    instance_methods);
    return VALUES_1(temp);
}

static Object Qprocedure;          /* procedure */

/* COLLECT-STATIC-METHOD-EXPORT-INFO */
Object collect_static_method_export_info(export_class,procedure_names)
    Object export_class, procedure_names;
{
    Object procedure_name, ab_loop_list_, g2_procedure_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp;

    x_note_fn_call(251,22);
    procedure_name = Nil;
    ab_loop_list_ = procedure_names;
    g2_procedure_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    procedure_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_procedure_qm = get_instance_with_name_if_any(Qprocedure,procedure_name);
    if (g2_procedure_qm) {
	ab_loopvar__2 = 
		slot_value_cons_1(make_external_method_info_for_g2_method(export_class,
		g2_procedure_qm,T,T),Nil);
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

static Object Qexternal_method_declaration;  /* external-method-declaration */

static Object Qexternal_procedure;  /* external-procedure */

static Object Qexternal_method;    /* external-method */

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

/* MAKE-EXTERNAL-METHOD-INFO-FOR-G2-METHOD */
Object make_external_method_info_for_g2_method(export_class,g2_method,
	    static_p,try_parse_p)
    Object export_class, g2_method, static_p, try_parse_p;
{
    Object declaration_frame, method_frame, method_name, external_method_info;
    Object temp;

    x_note_fn_call(251,23);
    declaration_frame = make_frame(Qexternal_method_declaration);
    method_frame = static_p ? make_frame(Qexternal_procedure) : 
	    make_frame(Qexternal_method);
    method_name = static_p ? get_lookup_slot_value_given_default(g2_method,
	    Qname_or_names_for_frame,Nil) : ISVREF(g2_method,(SI_Long)30L);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(declaration_frame,Qname_or_names_for_frame);
    set_lookup_slot_value_1(declaration_frame,Qname_or_names_for_frame,
	    method_name);
    external_method_info = make_external_method_info(export_class,
	    method_name,g2_method,static_p,declaration_frame,method_frame);
    if (try_parse_p) {
	temp = ISVREF(g2_method,(SI_Long)27L);
	try_to_parse_external_method_definition(external_method_info,
		method_frame,copy_text(CDR(temp)),static_p);
    }
    return VALUES_1(external_method_info);
}

static Object Qincluded_instance_methods;  /* included-instance-methods */

static Object Qexcluded_instance_methods;  /* excluded-instance-methods */

static Object Qab_method;          /* method */

/* COLLECT-INSTANCE-METHOD-EXPORT-INFO */
Object collect_instance_method_export_info varargs_1(int, n)
{
    Object export_class, options;
    Object try_parse_p, cached_instance_info, cache_existed_p, temp;
    Object included_instance_methods_qm, excluded_instance_methods_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_method, method_name;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(251,24);
    INIT_ARGS_nonrelocating();
    export_class = REQUIRED_ARG_nonrelocating();
    options = REQUIRED_ARG_nonrelocating();
    try_parse_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    END_ARGS_nonrelocating();
    result = decache_implicit_external_instance_method_info_if_any(export_class);
    MVS_2(result,cached_instance_info,cache_existed_p);
    if (cache_existed_p)
	return VALUES_1(cached_instance_info);
    else {
	temp = assq_function(Qincluded_instance_methods,options);
	included_instance_methods_qm = CDR(temp);
	temp = assq_function(Qexcluded_instance_methods,options);
	excluded_instance_methods_qm = CDR(temp);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	g2_method = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  method_name = Nil;
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar_ = collect_subclasses(Qab_method);
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
	      temp_1 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      goto end_loop_1;
	  g2_method = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  method_name = ISVREF(g2_method,(SI_Long)30L);
	  if (EQ(ISVREF(g2_method,(SI_Long)31L),export_class)) {
	      if (included_instance_methods_qm)
		  temp_1 = TRUEP(memq_function(method_name,
			  included_instance_methods_qm));
	      else if (included_instance_methods_qm)
		  temp_1 =  !TRUEP(memq_function(method_name,
			  excluded_instance_methods_qm));
	      else
		  temp_1 = TRUEP(T);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      ab_loopvar__4 = 
		      slot_value_cons_1(make_external_method_info_for_g2_method(export_class,
		      g2_method,Nil,try_parse_p),Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__4;
	      else
		  ab_loopvar__2 = ab_loopvar__4;
	      ab_loopvar__3 = ab_loopvar__4;
	  }
	  goto next_loop;
	end_loop_1:
	  result = VALUES_1(ab_loopvar__2);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

/* ANALYZE-EXPORT-INFO-FOR-PARSABILITY */
Object analyze_export_info_for_parsability(g2_method_or_procedure,
	    definition_text)
    Object g2_method_or_procedure, definition_text;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(251,25);
    sub_class_bit_vector = ISVREF(ISVREF(g2_method_or_procedure,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Method_class_description,
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
    if (temp)
	analyze_export_methods_for_parsability(g2_method_or_procedure,
		definition_text);
    else
	analyze_export_procedures_for_parsability(g2_method_or_procedure,
		definition_text);
    return VALUES_1(Nil);
}

DEFINE_VARIABLE_WITH_SYMBOL(Bypass_fix_for_exported_method_overloading_p, Qbypass_fix_for_exported_method_overloading_p);

/* G2-SWITCH-FIX-FOR-EXPORTED-METHOD-OVERLOADING */
Object g2_switch_fix_for_exported_method_overloading(bypass)
    Object bypass;
{
    x_note_fn_call(251,26);
    Bypass_fix_for_exported_method_overloading_p = FIXNUM_GE(M_CAR(bypass),
	    ISVREF(Inference_engine_parameters,(SI_Long)26L)) ? T : Nil;
    return VALUES_1(bypass);
}

/* MATCHING-INSTANCE-METHOD-INFO-P */
Object matching_instance_method_info_p(method_info,g2_method)
    Object method_info, g2_method;
{
    Object arg_description, arg_description_as_tree, temp;

    x_note_fn_call(251,27);
    if (EQ(ISVREF(method_info,(SI_Long)1L),ISVREF(g2_method,(SI_Long)31L)) 
	    && EQ(ISVREF(method_info,(SI_Long)2L),ISVREF(g2_method,
	    (SI_Long)30L))) {
	arg_description = ISVREF(g2_method,(SI_Long)24L);
	arg_description_as_tree = 
		collect_types_into_list_using_gensym_conses(arg_description);
	temp = ISVREF(method_info,(SI_Long)4L);
	temp = EQUAL(arg_description_as_tree,temp) ? T : Nil;
	reclaim_gensym_list_1(arg_description_as_tree);
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qexport_definition;  /* export-definition */

static Object Qvisible_class_export_information_qm;  /* visible-class-export-information? */

/* ANALYZE-EXPORT-METHODS-FOR-PARSABILITY */
Object analyze_export_methods_for_parsability(g2_method,
	    g2_method_definition_text)
    Object g2_method, g2_method_definition_text;
{
    Object class_name, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object export_definition, class_info, ab_loop_list_, method_info;
    Object ab_loop_it_, method_info_qm, slot_value_push_modify_macro_arg;
    Object car_1, cdr_1, svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(251,28);
    if (Bypass_fix_for_exported_method_overloading_p)
	old_analyze_export_methods_for_parsability(g2_method,
		g2_method_definition_text);
    else {
	class_name = ISVREF(g2_method,(SI_Long)31L);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	export_definition = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qexport_definition);
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
	  export_definition = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  class_info = Nil;
	  ab_loop_list_ = 
		  get_lookup_slot_value_given_default(export_definition,
		  Qvisible_class_export_information_qm,Nil);
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  class_info = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (EQ(class_name,ISVREF(class_info,(SI_Long)1L))) {
	      method_info = Nil;
	      ab_loop_list_ = ISVREF(class_info,(SI_Long)3L);
	      ab_loop_it_ = Nil;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      method_info = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loop_it_ = matching_instance_method_info_p(method_info,
		      g2_method) ? method_info : Qnil;
	      if (ab_loop_it_) {
		  method_info_qm = ab_loop_it_;
		  goto end_1;
	      }
	      goto next_loop_3;
	    end_loop_3:
	      method_info_qm = Qnil;
	    end_1:;
	      if ( !TRUEP(method_info_qm)) {
		  method_info_qm = 
			  make_external_method_info_for_g2_method(class_name,
			  g2_method,Nil,T);
		  slot_value_push_modify_macro_arg = method_info_qm;
		  car_1 = slot_value_push_modify_macro_arg;
		  cdr_1 = ISVREF(class_info,(SI_Long)3L);
		  svref_new_value = slot_value_cons_1(car_1,cdr_1);
		  SVREF(class_info,FIX((SI_Long)3L)) = svref_new_value;
	      }
	      clear_problem_mapping_g2_to_java_source_particulars(export_definition,
		      class_name);
	      analyze_exported_executable_for_parsability(export_definition,
		      method_info_qm,g2_method_definition_text,Nil);
	      goto end_loop_2;
	  }
	  goto next_loop_2;
	end_loop_2:;
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

/* OLD-ANALYZE-EXPORT-METHODS-FOR-PARSABILITY */
Object old_analyze_export_methods_for_parsability(g2_method,
	    g2_method_definition_text)
    Object g2_method, g2_method_definition_text;
{
    Object class_name, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object export_definition, class_info, ab_loop_list_, g2_method_name;
    Object method_info, ab_loop_it_, method_info_qm;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1, svref_new_value;
    char temp;
    Declare_special(1);

    x_note_fn_call(251,29);
    class_name = ISVREF(g2_method,(SI_Long)31L);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    export_definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qexport_definition);
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
      export_definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      class_info = Nil;
      ab_loop_list_ = 
	      get_lookup_slot_value_given_default(export_definition,
	      Qvisible_class_export_information_qm,Nil);
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      class_info = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (EQ(class_name,ISVREF(class_info,(SI_Long)1L))) {
	  g2_method_name = ISVREF(g2_method,(SI_Long)30L);
	  method_info = Nil;
	  ab_loop_list_ = ISVREF(class_info,(SI_Long)3L);
	  ab_loop_it_ = Nil;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  method_info = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loop_it_ = EQ(ISVREF(method_info,(SI_Long)2L),g2_method_name) 
		  ? method_info : Qnil;
	  if (ab_loop_it_) {
	      method_info_qm = ab_loop_it_;
	      goto end_1;
	  }
	  goto next_loop_3;
	end_loop_3:
	  method_info_qm = Qnil;
	end_1:;
	  if ( !TRUEP(method_info_qm)) {
	      method_info_qm = 
		      make_external_method_info_for_g2_method(class_name,
		      g2_method,Nil,T);
	      slot_value_push_modify_macro_arg = method_info_qm;
	      car_1 = slot_value_push_modify_macro_arg;
	      cdr_1 = ISVREF(class_info,(SI_Long)3L);
	      svref_new_value = slot_value_cons_1(car_1,cdr_1);
	      SVREF(class_info,FIX((SI_Long)3L)) = svref_new_value;
	  }
	  clear_problem_mapping_g2_to_java_source_particulars(export_definition,
		  class_name);
	  analyze_exported_executable_for_parsability(export_definition,
		  method_info_qm,g2_method_definition_text,Nil);
	  goto end_loop_2;
      }
      goto next_loop_2;
    end_loop_2:;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

static Object Qinstallation;       /* installation */

/* ANALYZE-EXPORTED-EXECUTABLE-FOR-PARSABILITY */
Object analyze_exported_executable_for_parsability(export_definition,
	    method_info_struct,definition_text,static_p)
    Object export_definition, method_info_struct, definition_text, static_p;
{
    Object temp, qualified_name, method_name, gensymed_symbol;
    Object gensymed_symbol_1, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_2;

    x_note_fn_call(251,30);
    temp = ISVREF(method_info_struct,(SI_Long)9L);
    try_to_parse_external_method_definition(method_info_struct,temp,
	    copy_text(CDR(definition_text)),static_p);
    update_unexportable_external_method_frame_note_if_appropriate(export_definition,
	    method_info_struct);
    if ( !TRUEP(static_p))
	update_instance_methods_attribute(export_definition);
    qualified_name = ISVREF(method_info_struct,(SI_Long)3L);
    method_name = ISVREF(method_info_struct,(SI_Long)2L);
    gensymed_symbol = lookup_kb_specific_property_value(qualified_name,
	    Compiled_items_referring_to_this_name_kbprop);
    gensymed_symbol_1 = export_definition;
    if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	new_cons = ISVREF(Available_installation_conses_vector,
		IFIX(Current_thread_index));
	if (new_cons) {
	    svref_arg_1 = Available_installation_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    svref_new_value = M_CDR(new_cons);
	    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
	    if ( !TRUEP(ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index)))) {
		svref_arg_1 = Available_installation_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(svref_arg_1,svref_arg_2) = Nil;
	    }
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_installation_cons_pool();
	M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	M_CDR(gensymed_symbol_2) = gensymed_symbol;
	inline_note_allocate_cons(gensymed_symbol_2,Qinstallation);
	mutate_kb_specific_property_value(qualified_name,gensymed_symbol_2,
		Compiled_items_referring_to_this_name_kbprop);
    }
    if ( !EQ(qualified_name,method_name)) {
	gensymed_symbol = 
		lookup_kb_specific_property_value(ISVREF(method_info_struct,
		(SI_Long)2L),Compiled_items_referring_to_this_name_kbprop);
	gensymed_symbol_1 = export_definition;
	if ( !TRUEP(memq_function(gensymed_symbol_1,gensymed_symbol))) {
	    temp = ISVREF(method_info_struct,(SI_Long)2L);
	    new_cons = ISVREF(Available_installation_conses_vector,
		    IFIX(Current_thread_index));
	    if (new_cons) {
		svref_arg_1 = Available_installation_conses_vector;
		svref_arg_2 = Current_thread_index;
		svref_new_value = M_CDR(new_cons);
		SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
		if ( !TRUEP(ISVREF(Available_installation_conses_vector,
			IFIX(Current_thread_index)))) {
		    svref_arg_1 = Available_installation_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(svref_arg_1,svref_arg_2) = Nil;
		}
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_installation_cons_pool();
	    M_CAR(gensymed_symbol_2) = gensymed_symbol_1;
	    M_CDR(gensymed_symbol_2) = gensymed_symbol;
	    inline_note_allocate_cons(gensymed_symbol_2,Qinstallation);
	    mutate_kb_specific_property_value(temp,gensymed_symbol_2,
		    Compiled_items_referring_to_this_name_kbprop);
	}
    }
    return VALUES_1(Nil);
}

/* ANALYZE-EXPORT-PROCEDURES-FOR-PARSABILITY */
Object analyze_export_procedures_for_parsability(g2_procedure,
	    g2_procedure_definition_text)
    Object g2_procedure, g2_procedure_definition_text;
{
    Object g2_procedure_name, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object export_definition, class_info, ab_loop_list_, method_info;
    Object ab_loop_list__1, method_info_qm;
    char temp;
    Declare_special(1);

    x_note_fn_call(251,31);
    g2_procedure_name = get_lookup_slot_value_given_default(g2_procedure,
	    Qname_or_names_for_frame,Nil);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    export_definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qexport_definition);
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
      export_definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      add_newborn_external_static_methods_as_appropriate(g2_procedure_name,
	      export_definition);
      class_info = Nil;
      ab_loop_list_ = 
	      get_lookup_slot_value_given_default(export_definition,
	      Qvisible_class_export_information_qm,Nil);
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      class_info = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      method_info = Nil;
      ab_loop_list__1 = ISVREF(class_info,(SI_Long)2L);
    next_loop_3:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_3;
      method_info = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      method_info_qm = EQ(ISVREF(method_info,(SI_Long)3L),
	      g2_procedure_name) ? method_info : Qnil;
      if (method_info_qm) {
	  clear_problem_mapping_g2_to_java_source_particulars(export_definition,
		  ISVREF(class_info,(SI_Long)1L));
	  analyze_exported_executable_for_parsability(export_definition,
		  method_info_qm,g2_procedure_definition_text,T);
	  goto end_loop_3;
      }
      goto next_loop_3;
    end_loop_3:;
      goto next_loop_2;
    end_loop_2:;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return VALUES_1(Nil);
}

/* ADD-NEWBORN-EXTERNAL-STATIC-METHODS-AS-APPROPRIATE */
Object add_newborn_external_static_methods_as_appropriate(g2_procedure_name,
	    export_definition)
    Object g2_procedure_name, export_definition;
{
    Object export_specs, class_info, ab_loop_list_, class_name, temp, options;
    Object desired_static_names, method_info, ab_loop_list__1;
    char temp_1;

    x_note_fn_call(251,32);
    export_specs = get_lookup_slot_value_given_default(export_definition,
	    Qexport_definition_specification,Nil);
    class_info = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(export_definition,
	    Qvisible_class_export_information_qm,Nil);
    class_name = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    class_name = ISVREF(class_info,(SI_Long)1L);
    temp = assq_function(class_name,CADR(export_specs));
    options = THIRD(temp);
    temp = assq_function(Qstatic_methods,options);
    desired_static_names = CADR(temp);
    if (memq_function(g2_procedure_name,desired_static_names)) {
	method_info = Nil;
	ab_loop_list__1 = ISVREF(class_info,(SI_Long)2L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(ISVREF(method_info,(SI_Long)2L),g2_procedure_name)) {
	    temp_1 = TRUEP(Nil);
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	temp_1 = TRUEP(T);
	goto end_1;
	temp_1 = TRUEP(Qnil);
      end_1:;
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	update_external_static_method_info(class_info,class_name,options,Nil);
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qunexportable_external_method;  /* unexportable-external-method */

/* CLEAR-UNEXPORTABLE-EXTERNAL-METHOD-FRAME-NOTE */
Object clear_unexportable_external_method_frame_note(export_definition,
	    method_info)
    Object export_definition, method_info;
{
    Object particular_key, particulars, temp, flawed_method, ab_loop_list_;
    Object particular, ab_loop_list__1, ab_loop_desetq_;

    x_note_fn_call(251,33);
    particular_key = ISVREF(method_info,(SI_Long)3L);
    if (Current_computation_component_particulars)
	particulars = 
		get_particulars_of_frame_note_from_component_particulars(Qunexportable_external_method,
		export_definition,Current_computation_component_particulars);
    else {
	temp = ISVREF(export_definition,(SI_Long)8L);
	particulars = getfq_function_no_default(CDR(temp),
		Qunexportable_external_method);
    }
    flawed_method = Nil;
    ab_loop_list_ = particulars;
    particular = Nil;
    ab_loop_list__1 = particulars;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    flawed_method = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    particular = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(particular_key,flawed_method)) {
	delete_from_frame_note_particulars_list(particular,
		Qunexportable_external_method,export_definition);
	goto end_loop;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* NSTRING-DOWNCASEW-OUTSIDE-DOUBLE-QUOTES */
Object nstring_downcasew_outside_double_quotes(wide_string)
    Object wide_string;
{
    Object this_char, inside_double_quote_p, aref_new_value, code;
    SI_Long i, length_1, ab_loop_bind_;

    x_note_fn_call(251,34);
    i = (SI_Long)0L;
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string));
    ab_loop_bind_ = UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)2L) 
	    + ((UBYTE_16_ISAREF_1(wide_string,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L);
    this_char = Nil;
    inside_double_quote_p = Nil;
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    this_char = FIX(UBYTE_16_ISAREF_1(wide_string,i));
    if (IFIX(this_char) == (SI_Long)34L)
	inside_double_quote_p =  !TRUEP(inside_double_quote_p) ? T : Nil;
    if (inside_double_quote_p)
	aref_new_value = this_char;
    else {
	code = this_char;
	if (IFIX(code) < (SI_Long)127L)
	    aref_new_value = (SI_Long)65L <= IFIX(code) && IFIX(code) <= 
		    (SI_Long)90L ? FIX(IFIX(code) + (SI_Long)32L) : code;
	else {
	    aref_new_value = unicode_lowercase_if_uppercase(code);
	    if (aref_new_value);
	    else
		aref_new_value = code;
	}
    }
    UBYTE_16_ISASET_1(wide_string,i,IFIX(aref_new_value));
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(wide_string);
}

/* UPDATE-UNEXPORTABLE-EXTERNAL-METHOD-FRAME-NOTE-IF-APPROPRIATE */
Object update_unexportable_external_method_frame_note_if_appropriate(export_definition,
	    method_info)
    Object export_definition, method_info;
{
    Object frame_note_qm, particular_key;

    x_note_fn_call(251,35);
    clear_unexportable_external_method_frame_note(export_definition,
	    method_info);
    frame_note_qm = ISVREF(method_info,(SI_Long)10L);
    if (frame_note_qm) {
	particular_key = ISVREF(method_info,(SI_Long)3L);
	add_to_frame_note_particulars_list_if_necessary(slot_value_list_2(particular_key,
		nstring_downcasew(copy_text_string_without_newlines(frame_note_qm,
		Nil))),Qunexportable_external_method,export_definition);
    }
    return VALUES_1(Nil);
}

static Object Qmethod_declaration;  /* method-declaration */

static Object Qexternal_procedure_definition;  /* external-procedure-definition */

static Object string_constant_2;   /* "there is no method-declaration named ~A" */

/* TRY-TO-PARSE-EXTERNAL-METHOD-DEFINITION */
Object try_to_parse_external_method_definition(external_method_info,
	    external_method_frame,method_definition_text,static_p)
    Object external_method_info, external_method_frame, method_definition_text;
    Object static_p;
{
    Object method_name_qm, method_declaration_qm, reason_for_failure_qm;
    Object gensymed_symbol, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(251,36);
    method_name_qm = static_p ? Nil : ISVREF(external_method_info,(SI_Long)2L);
    method_declaration_qm = method_name_qm ? 
	    get_instance_with_name_if_any(Qmethod_declaration,
	    method_name_qm) : Qnil;
    reason_for_failure_qm = Nil;
    if (static_p || method_declaration_qm) {
	result = parse_text_for_slot(8,method_definition_text,
		external_method_frame,
		get_slot_description_of_class_description_function(Qexternal_procedure_definition,
		ISVREF(external_method_frame,(SI_Long)1L),Nil),T,Nil,Nil,
		Nil,T);
	gensymed_symbol = NTH_VALUE((SI_Long)1L, result);
	reason_for_failure_qm = gensymed_symbol;
    }
    else if (method_name_qm) {
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
		  tformat(2,string_constant_2,method_name_qm);
		  reason_for_failure_qm = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    reclaim_text_or_gensym_string_if_any(ISVREF(external_method_info,
	    (SI_Long)10L));
    SVREF(external_method_info,FIX((SI_Long)10L)) = reason_for_failure_qm;
    return VALUES_1(Nil);
}

static Object Qduplicate_class_export;  /* duplicate-class-export */

static Object Qclass_definition;   /* class-definition */

static Object Qnonexistent_classes_for_export;  /* nonexistent-classes-for-export */

/* CHECK-EXPORTED-CLASSES */
Object check_exported_classes(export_definition,exported_class)
    Object export_definition, exported_class;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, this_export_definition;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, this_exported_class;
    Object temp_1, ab_loop_list_, ab_loop_it_, ab_loop_desetq_, duplicates_qm;
    Object java_pop_store, cons_1, next_cons, temp_2, svref_arg_2;
    Object noted_here_p;
    char temp;
    Declare_special(1);

    x_note_fn_call(251,37);
    add_or_delete_as_item_referring_to_name(exported_class);
    if (Delete_as_item_referring_to_name_qm) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	this_export_definition = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar_ = collect_subclasses(Qexport_definition);
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
	  this_export_definition = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ( !EQ(this_export_definition,export_definition)) {
	      this_exported_class = Nil;
	      temp_1 = 
		      get_lookup_slot_value_given_default(this_export_definition,
		      Qexport_definition_specification,Nil);
	      ab_loop_list_ = CADR(temp_1);
	      ab_loop_it_ = Nil;
	      ab_loop_desetq_ = Nil;
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      ab_loop_desetq_ = M_CAR(ab_loop_list_);
	      this_exported_class = CAR(ab_loop_desetq_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      ab_loop_it_ = EQ(this_exported_class,exported_class) ? T : Nil;
	      if (ab_loop_it_) {
		  temp = TRUEP(ab_loop_it_);
		  goto end_1;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      temp = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp) {
	      ab_loopvar__4 = java_cons_1(this_export_definition,Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__4;
	      else
		  ab_loopvar__2 = ab_loopvar__4;
	      ab_loopvar__3 = ab_loopvar__4;
	  }
	  goto next_loop;
	end_loop_1:
	  duplicates_qm = ab_loopvar__2;
	  goto end_2;
	  duplicates_qm = Qnil;
	end_2:;
	POP_SPECIAL();
	if (CDR(duplicates_qm))
	    reclaim_java_list_1(duplicates_qm);
	else if (duplicates_qm) {
	    java_pop_store = Nil;
	    cons_1 = duplicates_qm;
	    if (cons_1) {
		java_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qjava);
		if (ISVREF(Available_java_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_2 = ISVREF(Available_java_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_2) = cons_1;
		    temp_2 = Available_java_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		else {
		    temp_2 = Available_java_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		    temp_2 = Available_java_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_2,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    duplicates_qm = next_cons;
	    delete_from_frame_note_particulars_list(exported_class,
		    Qduplicate_class_export,java_pop_store);
	}
    }
    else {
	if ( !TRUEP(get_instance_with_name_if_any(Qclass_definition,
		exported_class)))
	    add_to_frame_note_particulars_list_if_necessary(exported_class,
		    Qnonexistent_classes_for_export,export_definition);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	this_export_definition = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  noted_here_p = Nil;
	  ab_loopvar_ = collect_subclasses(Qexport_definition);
	next_loop_3:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_4:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_3;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_3;
	      goto next_loop_4;
	    end_loop_3:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_4;
	  this_export_definition = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ( !EQ(this_export_definition,export_definition)) {
	      this_exported_class = Nil;
	      temp_1 = 
		      get_lookup_slot_value_given_default(this_export_definition,
		      Qexport_definition_specification,Nil);
	      ab_loop_list_ = CADR(temp_1);
	      ab_loop_desetq_ = Nil;
	    next_loop_5:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_5;
	      ab_loop_desetq_ = M_CAR(ab_loop_list_);
	      this_exported_class = CAR(ab_loop_desetq_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (EQ(this_exported_class,exported_class)) {
		  if ( !TRUEP(noted_here_p)) {
		      add_to_frame_note_particulars_list_if_necessary(exported_class,
			      Qduplicate_class_export,export_definition);
		      noted_here_p = T;
		  }
		  add_to_frame_note_particulars_list_if_necessary(this_exported_class,
			  Qduplicate_class_export,this_export_definition);
	      }
	      goto next_loop_5;
	    end_loop_5:;
	  }
	  goto next_loop_3;
	end_loop_4:;
	POP_SPECIAL();
    }
    return VALUES_1(Nil);
}

static Object Qnonexistent_static_methods_for_export;  /* nonexistent-static-methods-for-export */

/* CHECK-EXTERNAL-STATIC-METHODS */
Object check_external_static_methods(export_definition,exported_class,options)
    Object export_definition, exported_class, options;
{
    Object temp, static_methods, static_method, ab_loop_list_;
    Object nonexistent_static_methods_qm;

    x_note_fn_call(251,38);
    temp = assq_function(Qstatic_methods,options);
    static_methods = CADR(temp);
    if (Delete_as_item_referring_to_name_qm) {
	static_method = Nil;
	ab_loop_list_ = static_methods;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	static_method = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(get_instance_with_name_if_any(Qprocedure,static_method)))
	    add_or_delete_as_item_referring_to_name(static_method);
	goto next_loop;
      end_loop:;
    }
    else {
	nonexistent_static_methods_qm = Nil;
	static_method = Nil;
	ab_loop_list_ = static_methods;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	static_method = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	add_or_delete_as_item_referring_to_name(static_method);
	if ( !TRUEP(get_instance_with_name_if_any(Qprocedure,static_method)))
	    nonexistent_static_methods_qm = 
		    slot_value_cons_1(static_method,
		    nonexistent_static_methods_qm);
	goto next_loop_1;
      end_loop_1:;
	if (nonexistent_static_methods_qm) {
	    nonexistent_static_methods_qm = 
		    nreverse(nonexistent_static_methods_qm);
	    add_to_frame_note_particulars_list_if_necessary(slot_value_cons_1(exported_class,
		    nonexistent_static_methods_qm),
		    Qnonexistent_static_methods_for_export,export_definition);
	}
    }
    return VALUES_1(Nil);
}

/* CHECK-EXTERNAL-INSTANCE-METHOD-INFO */
Object check_external_instance_method_info(export_definition)
    Object export_definition;
{
    x_note_fn_call(251,39);
    shared_check_external_method_info(export_definition,Nil);
    update_instance_methods_attribute(export_definition);
    return VALUES_1(Nil);
}

/* SHARED-CHECK-EXTERNAL-METHOD-INFO */
Object shared_check_external_method_info(export_definition,static_p)
    Object export_definition, static_p;
{
    x_note_fn_call(251,40);
    if (Bypass_fix_for_exported_method_overloading_p)
	old_shared_check_external_method_info(export_definition,static_p);
    else
	new_shared_check_external_method_info(export_definition,static_p);
    return VALUES_1(Nil);
}

/* OLD-SHARED-CHECK-EXTERNAL-METHOD-INFO */
Object old_shared_check_external_method_info(export_definition,static_p)
    Object export_definition, static_p;
{
    Object class_info, ab_loop_list_, method_info, ab_loop_list__1, class_name;
    Object old_method_info_list, qualified_name, g2_procedure_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, new_method_info_list;

    x_note_fn_call(251,41);
    if (Add_as_item_referring_to_name_qm) {
	class_info = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(export_definition,
		Qvisible_class_export_information_qm,Nil);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	method_info = Nil;
	ab_loop_list__1 = static_p ? ISVREF(class_info,(SI_Long)2L) : 
		ISVREF(class_info,(SI_Long)3L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	add_or_delete_as_item_referring_to_name(ISVREF(method_info,
		(SI_Long)3L));
	update_unexportable_external_method_frame_note_if_appropriate(export_definition,
		method_info);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    else {
	class_info = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(export_definition,
		Qvisible_class_export_information_qm,Nil);
	class_name = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_name = ISVREF(class_info,(SI_Long)1L);
	old_method_info_list = static_p ? ISVREF(class_info,(SI_Long)2L) : 
		ISVREF(class_info,(SI_Long)3L);
	method_info = Nil;
	ab_loop_list__1 = old_method_info_list;
	qualified_name = Nil;
	g2_procedure_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	qualified_name = ISVREF(method_info,(SI_Long)3L);
	g2_procedure_qm = get_instance_with_name_if_any(Qprocedure,
		qualified_name);
	ab_loopvar__2 = 
		make_listed_external_method_info_if_valid(g2_procedure_qm,
		export_definition,class_name,qualified_name,method_info,
		static_p);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop_3;
      end_loop_3:
	new_method_info_list = ab_loopvar_;
	goto end_1;
	new_method_info_list = Qnil;
      end_1:;
	reclaim_slot_value_list_1(old_method_info_list);
	if (static_p)
	    SVREF(class_info,FIX((SI_Long)2L)) = new_method_info_list;
	else
	    SVREF(class_info,FIX((SI_Long)3L)) = new_method_info_list;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(Nil);
}

/* GET-INSTANCE-OR-INSTANCES-WITH-NAME-IF-ANY */
Object get_instance_or_instances_with_name_if_any(class_1,name)
    Object class_1, name;
{
    Object list_1, frame_or_frames_with_this_name, gensymed_symbol;
    Object sub_class_bit_vector, temp_1, frame, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(251,42);
    list_1 = INLINE_SYMBOL_PLIST(name);
  next_loop:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Current_kb_specific_property_list_property_name))
	goto end_loop;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop;
  end_loop:
    list_1 = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
  next_loop_1:
    if ( !TRUEP(list_1) || EQ(M_CAR(list_1),
	    Frame_or_frames_with_this_name_kbprop))
	goto end_loop_1;
    list_1 = M_CDR(M_CDR(list_1));
    goto next_loop_1;
  end_loop_1:
    frame_or_frames_with_this_name = list_1 ? M_CAR(M_CDR(list_1)) : Nil;
    if (frame_or_frames_with_this_name) {
	if (ATOM(frame_or_frames_with_this_name)) {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = 
			ISVREF(ISVREF(frame_or_frames_with_this_name,
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
	    temp_1 = temp ? 
		    slot_value_cons_1(frame_or_frames_with_this_name,Nil) :
		     Nil;
	}
	else {
	    frame = Nil;
	    ab_loop_list_ = frame_or_frames_with_this_name;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    frame = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),
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
		ab_loopvar__2 = slot_value_cons_1(frame,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

/* GET-MATCHING-G2-PROCEDURE-IF-ANY */
Object get_matching_g2_procedure_if_any(method_info,static_p)
    Object method_info, static_p;
{
    Object qualified_name, temp, g2_methods_qm, g2_method, ab_loop_list_;
    Object ab_loop_it_, matching_method_if_any;

    x_note_fn_call(251,43);
    qualified_name = ISVREF(method_info,(SI_Long)3L);
    if (static_p)
	temp = get_instance_with_name_if_any(Qprocedure,qualified_name);
    else {
	g2_methods_qm = 
		get_instance_or_instances_with_name_if_any(Qab_method,
		qualified_name);
	g2_method = Nil;
	ab_loop_list_ = g2_methods_qm;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	g2_method = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = matching_instance_method_info_p(method_info,
		g2_method) ? g2_method : Qnil;
	if (ab_loop_it_) {
	    matching_method_if_any = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	matching_method_if_any = Qnil;
      end_1:;
	reclaim_slot_value_list_1(g2_methods_qm);
	temp = matching_method_if_any;
    }
    return VALUES_1(temp);
}

/* NEW-SHARED-CHECK-EXTERNAL-METHOD-INFO */
Object new_shared_check_external_method_info(export_definition,static_p)
    Object export_definition, static_p;
{
    Object class_info, ab_loop_list_, method_info, ab_loop_list__1, class_name;
    Object old_method_info_list, qualified_name, g2_procedure_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, new_method_info_list;

    x_note_fn_call(251,44);
    if (Add_as_item_referring_to_name_qm) {
	class_info = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(export_definition,
		Qvisible_class_export_information_qm,Nil);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	method_info = Nil;
	ab_loop_list__1 = static_p ? ISVREF(class_info,(SI_Long)2L) : 
		ISVREF(class_info,(SI_Long)3L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	add_or_delete_as_item_referring_to_name(ISVREF(method_info,
		(SI_Long)3L));
	update_unexportable_external_method_frame_note_if_appropriate(export_definition,
		method_info);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:;
    }
    else {
	class_info = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(export_definition,
		Qvisible_class_export_information_qm,Nil);
	class_name = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	class_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_name = ISVREF(class_info,(SI_Long)1L);
	old_method_info_list = static_p ? ISVREF(class_info,(SI_Long)2L) : 
		ISVREF(class_info,(SI_Long)3L);
	method_info = Nil;
	ab_loop_list__1 = old_method_info_list;
	qualified_name = Nil;
	g2_procedure_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	qualified_name = ISVREF(method_info,(SI_Long)3L);
	g2_procedure_qm = get_matching_g2_procedure_if_any(method_info,
		static_p);
	ab_loopvar__2 = 
		make_listed_external_method_info_if_valid(g2_procedure_qm,
		export_definition,class_name,qualified_name,method_info,
		static_p);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop_3;
      end_loop_3:
	new_method_info_list = ab_loopvar_;
	goto end_1;
	new_method_info_list = Qnil;
      end_1:;
	reclaim_slot_value_list_1(old_method_info_list);
	if (static_p)
	    SVREF(class_info,FIX((SI_Long)2L)) = new_method_info_list;
	else
	    SVREF(class_info,FIX((SI_Long)3L)) = new_method_info_list;
	goto next_loop_2;
      end_loop_2:;
    }
    return VALUES_1(Nil);
}

/* MAKE-LISTED-EXTERNAL-METHOD-INFO-IF-VALID */
Object make_listed_external_method_info_if_valid(g2_procedure_qm,
	    export_definition,class_name,qualified_name,method_info,static_p)
    Object g2_procedure_qm, export_definition, class_name, qualified_name;
    Object method_info, static_p;
{
    Object definition_text, new_method_info, temp_1;
    char temp;

    x_note_fn_call(251,45);
    definition_text = Nil;
    if (g2_procedure_qm) {
	definition_text = ISVREF(g2_procedure_qm,(SI_Long)27L);
	temp =  !TRUEP(same_definition_text_p(definition_text,method_info));
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	new_method_info = 
		make_external_method_info_for_g2_method(class_name,
		g2_procedure_qm,static_p,Nil);
	analyze_exported_executable_for_parsability(export_definition,
		new_method_info,definition_text,static_p);
	reclaim_external_method_info_1(method_info);
	temp_1 = slot_value_cons_1(new_method_info,Nil);
    }
    else if (g2_procedure_qm)
	temp_1 = slot_value_cons_1(method_info,Nil);
    else {
	clear_unexportable_external_method_frame_note(export_definition,
		method_info);
	add_or_delete_as_item_referring_to_name(qualified_name);
	reclaim_external_method_info_1(method_info);
	temp_1 = Nil;
    }
    return VALUES_1(temp_1);
}

/* SAME-DEFINITION-TEXT-P */
Object same_definition_text_p(g2_procedure_definition_text,method_info)
    Object g2_procedure_definition_text, method_info;
{
    Object temp;

    x_note_fn_call(251,46);
    temp = equalw(g2_procedure_definition_text,ISVREF(ISVREF(method_info,
	    (SI_Long)9L),(SI_Long)20L));
    return VALUES_1(temp);
}

/* CHECK-EXTERNAL-STATIC-METHOD-INFO */
Object check_external_static_method_info(export_definition)
    Object export_definition;
{
    x_note_fn_call(251,47);
    shared_check_external_method_info(export_definition,T);
    return VALUES_1(Nil);
}

static Object string_constant_3;   /* "(~A) " */

static Object string_constant_4;   /* "method ~A could not be exported: ~A;" */

static Object array_constant;      /* # */

/* WRITE-UNEXPORTABLE-EXTERNAL-METHOD-NOTE */
Object write_unexportable_external_method_note(particulars,gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    Object enumerate_p, method_name, note, ab_loop_list_, particulars_cons;
    Object ab_loop_iter_flag_, ab_loop_desetq_, temp;
    SI_Long index_1;

    x_note_fn_call(251,48);
    enumerate_p = CDR(particulars);
    method_name = Nil;
    note = Nil;
    ab_loop_list_ = particulars;
    particulars_cons = particulars;
    index_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    method_name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    note = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	particulars_cons = M_CDR(particulars_cons);
    if ( !TRUEP(particulars_cons))
	goto end_loop;
    if ( !TRUEP(ab_loop_iter_flag_))
	index_1 = index_1 + (SI_Long)1L;
    if (enumerate_p)
	tformat(2,string_constant_3,FIX(index_1 + IFIX(Frame_note_index)));
    tformat(3,string_constant_4,method_name,note);
    if (enumerate_p) {
	if (CDR(particulars_cons)) {
	    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
	    twrite_line_separator();
	}
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    if (enumerate_p)
	Frame_note_index_skip = FIX(index_1 - (SI_Long)1L);
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

/* UPDATE-INSTANCE-METHODS-ATTRIBUTE */
Object update_instance_methods_attribute(export_definition)
    Object export_definition;
{
    Object class_info, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, methods_for_this_class, method_info, ab_loop_list__1;
    Object slot_value_modify_macro_using_test_arg_1, car_1, cdr_1, key_result;
    Object x_element, ab_loop_list__2, ab_loop_it_;
    char temp;

    x_note_fn_call(251,49);
    if (Bypass_fix_for_exported_method_overloading_p)
	old_update_instance_methods_attribute(export_definition);
    else {
	reclaim_slot_value(ISVREF(export_definition,(SI_Long)20L));
	class_info = Nil;
	ab_loop_list_ = 
		get_lookup_slot_value_given_default(export_definition,
		Qvisible_class_export_information_qm,Nil);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	methods_for_this_class = Nil;
	method_info = Nil;
	ab_loop_list__1 = ISVREF(class_info,(SI_Long)3L);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	slot_value_modify_macro_using_test_arg_1 = ISVREF(method_info,
		(SI_Long)3L);
	car_1 = slot_value_modify_macro_using_test_arg_1;
	cdr_1 = methods_for_this_class;
	key_result = car_1;
	x_element = Nil;
	ab_loop_list__2 = cdr_1;
	ab_loop_it_ = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list__2))
	    goto end_loop_2;
	x_element = M_CAR(ab_loop_list__2);
	ab_loop_list__2 = M_CDR(ab_loop_list__2);
	ab_loop_it_ = EQL(key_result,x_element) ? T : Nil;
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_2:
	temp = TRUEP(Qnil);
      end_1:;
	methods_for_this_class = temp ? cdr_1 : slot_value_cons_1(car_1,cdr_1);
	goto next_loop_1;
      end_loop_1:;
	ab_loopvar__2 = methods_for_this_class;
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop;
      end_loop:
	goto end_2;
	ab_loopvar_ = Qnil;
      end_2:;
	ISVREF(export_definition,(SI_Long)20L) = ab_loopvar_;
    }
    return VALUES_1(Nil);
}

/* OLD-UPDATE-INSTANCE-METHODS-ATTRIBUTE */
Object old_update_instance_methods_attribute(export_definition)
    Object export_definition;
{
    Object class_info, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, method_info, ab_loop_list__1, ab_loopvar__3;
    Object ab_loopvar__4;

    x_note_fn_call(251,50);
    reclaim_slot_value(ISVREF(export_definition,(SI_Long)20L));
    class_info = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(export_definition,
	    Qvisible_class_export_information_qm,Nil);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    method_info = Nil;
    ab_loop_list__1 = ISVREF(class_info,(SI_Long)3L);
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    method_info = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loopvar__4 = slot_value_cons_1(ISVREF(method_info,(SI_Long)3L),Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
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
    goto next_loop;
  end_loop:
    goto end_2;
    ab_loopvar_ = Qnil;
  end_2:;
    ISVREF(export_definition,(SI_Long)20L) = ab_loopvar_;
    return VALUES_1(Nil);
}

static Object Qinterface;          /* interface */

static Object Qcode;               /* code */

/* UPDATE-ALL-EXTERNAL-METHOD-INFO */
Object update_all_external_method_info(export_definition)
    Object export_definition;
{
    Object definition_spec, language, export_specs, exported_class;
    Object export_type, options, ab_loop_list_, ab_loop_desetq_, temp;

    x_note_fn_call(251,51);
    definition_spec = 
	    get_lookup_slot_value_given_default(export_definition,
	    Qexport_definition_specification,Nil);
    language = CAR(definition_spec);
    export_specs = CADR(definition_spec);
    if (EQ(language,Qjava)) {
	reconcile_exported_classes(export_definition,export_specs);
	exported_class = Nil;
	export_type = Nil;
	options = Nil;
	ab_loop_list_ = export_specs;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	exported_class = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	export_type = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	options = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	clear_problem_mapping_g2_to_java_source_particulars(export_definition,
		exported_class);
	if (EQ(export_type,Qinterface) || EQ(export_type,Qcode) || 
		EQ(export_type,Qnil))
	    update_external_method_info(export_definition,exported_class,
		    options);
	goto next_loop;
      end_loop:;
    }
    update_instance_methods_attribute(export_definition);
    return VALUES_1(Nil);
}

/* RECONCILE-EXPORTED-CLASSES */
Object reconcile_exported_classes(export_definition,export_specs)
    Object export_definition, export_specs;
{
    Object old_class_info, exported_class, options, ab_loop_list_;
    Object extant_class_struct_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp, external_class_struct, ab_loop_list__1;
    Object ab_loop_it_, new_class_info;

    x_note_fn_call(251,52);
    old_class_info = get_lookup_slot_value_given_default(export_definition,
	    Qvisible_class_export_information_qm,Nil);
    exported_class = Nil;
    options = Nil;
    ab_loop_list_ = export_specs;
    extant_class_struct_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    exported_class = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    options = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    external_class_struct = Nil;
    ab_loop_list__1 = old_class_info;
    ab_loop_it_ = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    external_class_struct = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQ(ISVREF(external_class_struct,(SI_Long)1L),
	    exported_class) ? external_class_struct : Qnil;
    if (ab_loop_it_) {
	extant_class_struct_qm = ab_loop_it_;
	goto end_1;
    }
    goto next_loop_1;
  end_loop_1:
    extant_class_struct_qm = Qnil;
  end_1:;
    temp = extant_class_struct_qm;
    if (temp);
    else
	temp = make_export_info_for_one_class(exported_class,options);
    ab_loopvar__2 = slot_value_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    new_class_info = ab_loopvar_;
    goto end_2;
    new_class_info = Qnil;
  end_2:;
    external_class_struct = Nil;
    ab_loop_list_ = old_class_info;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    external_class_struct = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(external_class_struct,new_class_info)))
	reclaim_external_class_info_1(external_class_struct);
    goto next_loop_2;
  end_loop_2:;
    reclaim_slot_value_list_1(old_class_info);
    set_non_savable_lookup_slot_value(export_definition,
	    Qvisible_class_export_information_qm,new_class_info);
    return VALUES_1(Nil);
}

/* UPDATE-EXTERNAL-METHOD-INFO */
Object update_external_method_info(export_definition,export_class,options)
    Object export_definition, export_class, options;
{
    Object all_class_export_information_qm, export_info, ab_loop_list_;
    Object ab_loop_it_, export_info_for_this_class_qm;
    Object slot_value_push_modify_macro_arg, car_1, cdr_1;
    Object visible_class_export_information_qm_new_value;

    x_note_fn_call(251,53);
    all_class_export_information_qm = 
	    get_lookup_slot_value_given_default(export_definition,
	    Qvisible_class_export_information_qm,Nil);
    if (all_class_export_information_qm) {
	export_info = Nil;
	ab_loop_list_ = all_class_export_information_qm;
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	export_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = EQ(ISVREF(export_info,(SI_Long)1L),export_class) ? 
		export_info : Qnil;
	if (ab_loop_it_) {
	    export_info_for_this_class_qm = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	export_info_for_this_class_qm = Qnil;
      end_1:;
    }
    else
	export_info_for_this_class_qm = Nil;
    if ( !TRUEP(all_class_export_information_qm))
	set_non_savable_lookup_slot_value(export_definition,
		Qvisible_class_export_information_qm,
		collect_export_info_for_all_classes(export_definition));
    else if ( !TRUEP(export_info_for_this_class_qm)) {
	export_info_for_this_class_qm = 
		make_export_info_for_one_class(export_class,options);
	slot_value_push_modify_macro_arg = export_info_for_this_class_qm;
	car_1 = slot_value_push_modify_macro_arg;
	cdr_1 = get_lookup_slot_value_given_default(export_definition,
		Qvisible_class_export_information_qm,Nil);
	visible_class_export_information_qm_new_value = 
		slot_value_cons_1(car_1,cdr_1);
	set_non_savable_lookup_slot_value(export_definition,
		Qvisible_class_export_information_qm,
		visible_class_export_information_qm_new_value);
    }
    else {
	update_external_static_method_info(export_info_for_this_class_qm,
		export_class,options,T);
	update_external_instance_method_info(export_info_for_this_class_qm,
		export_class,options);
    }
    return VALUES_1(Nil);
}

/* UPDATE-EXTERNAL-STATIC-METHOD-INFO */
Object update_external_static_method_info(export_info_for_this_class,
	    export_class,options,try_parse_p)
    Object export_info_for_this_class, export_class, options, try_parse_p;
{
    Object old_static_method_info_list, g2_procedure_name, temp, ab_loop_list_;
    Object g2_procedure_qm, old_method_info_qm, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, old_method_info, ab_loop_list__1, ab_loop_it_;
    Object new_static_method_info_list;

    x_note_fn_call(251,54);
    old_static_method_info_list = ISVREF(export_info_for_this_class,
	    (SI_Long)2L);
    g2_procedure_name = Nil;
    temp = assq_function(Qstatic_methods,options);
    ab_loop_list_ = CADR(temp);
    g2_procedure_qm = Nil;
    old_method_info_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    g2_procedure_name = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    g2_procedure_qm = get_instance_with_name_if_any(Qprocedure,
	    g2_procedure_name);
    if (g2_procedure_qm) {
	old_method_info = Nil;
	ab_loop_list__1 = old_static_method_info_list;
	ab_loop_it_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	old_method_info = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loop_it_ = EQ(ISVREF(old_method_info,(SI_Long)3L),
		g2_procedure_name) ? old_method_info : Qnil;
	if (ab_loop_it_) {
	    old_method_info_qm = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop_1;
      end_loop_1:
	old_method_info_qm = Qnil;
      end_1:;
    }
    else
	old_method_info_qm = Nil;
    if (g2_procedure_qm) {
	temp = old_method_info_qm;
	if (temp);
	else
	    temp = make_external_method_info_for_g2_method(export_class,
		    g2_procedure_qm,T,try_parse_p);
	ab_loopvar__2 = slot_value_cons_1(temp,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    new_static_method_info_list = ab_loopvar_;
    goto end_2;
    new_static_method_info_list = Qnil;
  end_2:;
    old_method_info = Nil;
    ab_loop_list_ = old_static_method_info_list;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    old_method_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(memq_function(old_method_info,new_static_method_info_list)))
	reclaim_external_method_info_1(old_method_info);
    goto next_loop_2;
  end_loop_2:;
    reclaim_slot_value_list_1(old_static_method_info_list);
    SVREF(export_info_for_this_class,FIX((SI_Long)2L)) = 
	    new_static_method_info_list;
    return VALUES_1(Nil);
}

/* UPDATE-EXTERNAL-INSTANCE-METHOD-INFO */
Object update_external_instance_method_info(export_info_for_this_class,
	    export_class,options)
    Object export_info_for_this_class, export_class, options;
{
    x_note_fn_call(251,55);
    if (Bypass_fix_for_exported_method_overloading_p)
	old_update_external_instance_method_info(export_info_for_this_class,
		export_class,options);
    else
	new_update_external_instance_method_info(export_info_for_this_class,
		export_class,options);
    return VALUES_1(Nil);
}

/* OLD-UPDATE-EXTERNAL-INSTANCE-METHOD-INFO */
Object old_update_external_instance_method_info(export_info_for_this_class,
	    export_class,options)
    Object export_info_for_this_class, export_class, options;
{
    Object old_methods, external_method_struct, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, gleaned_methods, old_methods_qm;
    Object cached_instance_info, cache_existed_p, temp, cdr_new_value;
    Object result;

    x_note_fn_call(251,56);
    old_methods = ISVREF(export_info_for_this_class,(SI_Long)3L);
    external_method_struct = Nil;
    ab_loop_list_ = old_methods;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    external_method_struct = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (get_instance_with_name_if_any(Qab_method,
	    ISVREF(external_method_struct,(SI_Long)3L))) {
	ab_loopvar__2 = slot_value_cons_1(external_method_struct,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else
	reclaim_external_method_info_1(external_method_struct);
    goto next_loop;
  end_loop:
    gleaned_methods = ab_loopvar_;
    goto end_1;
    gleaned_methods = Qnil;
  end_1:;
    reclaim_slot_value_list_1(old_methods);
    SVREF(export_info_for_this_class,FIX((SI_Long)3L)) = gleaned_methods;
    old_methods_qm = ISVREF(export_info_for_this_class,(SI_Long)3L);
    result = decache_implicit_external_instance_method_info_if_any(export_class);
    MVS_2(result,cached_instance_info,cache_existed_p);
    if (cache_existed_p) {
	reclaim_list_of_external_methods(old_methods_qm);
	SVREF(export_info_for_this_class,FIX((SI_Long)3L)) = 
		cached_instance_info;
    }
    else if (old_methods_qm) {
	temp = last(old_methods_qm,_);
	cdr_new_value = 
		maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
		export_class,options);
	M_CDR(temp) = cdr_new_value;
    }
    else {
	temp = 
		maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
		export_class,options);
	SVREF(export_info_for_this_class,FIX((SI_Long)3L)) = temp;
    }
    return VALUES_1(Nil);
}

/* NEW-UPDATE-EXTERNAL-INSTANCE-METHOD-INFO */
Object new_update_external_instance_method_info(export_info_for_this_class,
	    export_class,options)
    Object export_info_for_this_class, export_class, options;
{
    Object old_methods, external_method_struct, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, gleaned_methods, old_methods_qm;
    Object cached_instance_info, cache_existed_p, temp, cdr_new_value;
    Object result;

    x_note_fn_call(251,57);
    old_methods = ISVREF(export_info_for_this_class,(SI_Long)3L);
    external_method_struct = Nil;
    ab_loop_list_ = old_methods;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    external_method_struct = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (get_matching_g2_procedure_if_any(external_method_struct,Nil)) {
	ab_loopvar__2 = slot_value_cons_1(external_method_struct,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    else
	reclaim_external_method_info_1(external_method_struct);
    goto next_loop;
  end_loop:
    gleaned_methods = ab_loopvar_;
    goto end_1;
    gleaned_methods = Qnil;
  end_1:;
    reclaim_slot_value_list_1(old_methods);
    SVREF(export_info_for_this_class,FIX((SI_Long)3L)) = gleaned_methods;
    old_methods_qm = ISVREF(export_info_for_this_class,(SI_Long)3L);
    result = decache_implicit_external_instance_method_info_if_any(export_class);
    MVS_2(result,cached_instance_info,cache_existed_p);
    if (cache_existed_p) {
	reclaim_list_of_external_methods(old_methods_qm);
	SVREF(export_info_for_this_class,FIX((SI_Long)3L)) = 
		cached_instance_info;
    }
    else if (old_methods_qm) {
	temp = last(old_methods_qm,_);
	cdr_new_value = 
		maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
		export_class,options);
	M_CDR(temp) = cdr_new_value;
    }
    else {
	temp = 
		maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
		export_class,options);
	SVREF(export_info_for_this_class,FIX((SI_Long)3L)) = temp;
    }
    return VALUES_1(Nil);
}

/* MAYBE-GET-MORE-EXTERNAL-INSTANCE-METHODS-FOR-CLASS */
Object maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
	    export_class,options)
    Object export_info_for_this_class, export_class, options;
{
    Object temp, included_instance_methods_qm, excluded_instance_methods_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_method, method_name;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, external_method_struct;
    Object ab_loop_list_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(251,58);
    if (Bypass_fix_for_exported_method_overloading_p)
	temp = 
		old_maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
		export_class,options);
    else {
	temp = assq_function(Qincluded_instance_methods,options);
	included_instance_methods_qm = CDR(temp);
	temp = assq_function(Qexcluded_instance_methods,options);
	excluded_instance_methods_qm = CDR(temp);
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	g2_method = Nil;
	PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
	  method_name = Nil;
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar_ = collect_subclasses(Qab_method);
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
	      temp_1 =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1)
	      goto end_loop_1;
	  g2_method = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  method_name = ISVREF(g2_method,(SI_Long)30L);
	  if (EQ(ISVREF(g2_method,(SI_Long)31L),export_class)) {
	      if (included_instance_methods_qm)
		  temp_1 = TRUEP(memq_function(method_name,
			  included_instance_methods_qm));
	      else if (included_instance_methods_qm)
		  temp_1 =  !TRUEP(memq_function(method_name,
			  excluded_instance_methods_qm));
	      else
		  temp_1 = TRUEP(T);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      external_method_struct = Nil;
	      ab_loop_list_ = ISVREF(export_info_for_this_class,(SI_Long)3L);
	    next_loop_2:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_2;
	      external_method_struct = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if (matching_instance_method_info_p(external_method_struct,
		      g2_method)) {
		  temp_1 = TRUEP(Nil);
		  goto end_1;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      temp_1 = TRUEP(T);
	      goto end_1;
	      temp_1 = TRUEP(Qnil);
	    end_1:;
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      ab_loopvar__4 = 
		      slot_value_cons_1(make_external_method_info_for_g2_method(export_class,
		      g2_method,Nil,T),Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__4;
	      else
		  ab_loopvar__2 = ab_loopvar__4;
	      ab_loopvar__3 = ab_loopvar__4;
	  }
	  goto next_loop;
	end_loop_1:
	  temp = ab_loopvar__2;
	  goto end_2;
	  temp = Qnil;
	end_2:;
	POP_SPECIAL();
    }
    return VALUES_1(temp);
}

/* OLD-MAYBE-GET-MORE-EXTERNAL-INSTANCE-METHODS-FOR-CLASS */
Object old_maybe_get_more_external_instance_methods_for_class(export_info_for_this_class,
	    export_class,options)
    Object export_info_for_this_class, export_class, options;
{
    Object temp, included_instance_methods_qm, excluded_instance_methods_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, g2_method, method_name;
    Object ab_loopvar__2, ab_loopvar__3, ab_loopvar__4, external_method_struct;
    Object ab_loop_list_;
    char temp_1;
    Declare_special(1);

    x_note_fn_call(251,59);
    temp = assq_function(Qincluded_instance_methods,options);
    included_instance_methods_qm = CDR(temp);
    temp = assq_function(Qexcluded_instance_methods,options);
    excluded_instance_methods_qm = CDR(temp);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    g2_method = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      method_name = Nil;
      ab_loopvar__2 = Nil;
      ab_loopvar__3 = Nil;
      ab_loopvar__4 = Nil;
      ab_loopvar_ = collect_subclasses(Qab_method);
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
	  temp_1 =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1)
	  goto end_loop_1;
      g2_method = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      method_name = ISVREF(g2_method,(SI_Long)30L);
      if (EQ(ISVREF(g2_method,(SI_Long)31L),export_class)) {
	  if (included_instance_methods_qm)
	      temp_1 = TRUEP(memq_function(method_name,
		      included_instance_methods_qm));
	  else if (included_instance_methods_qm)
	      temp_1 =  !TRUEP(memq_function(method_name,
		      excluded_instance_methods_qm));
	  else
	      temp_1 = TRUEP(T);
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  external_method_struct = Nil;
	  ab_loop_list_ = ISVREF(export_info_for_this_class,(SI_Long)3L);
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  external_method_struct = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  temp = get_lookup_slot_value_given_default(g2_method,
		  Qname_or_names_for_frame,Nil);
	  if (EQ(temp,ISVREF(external_method_struct,(SI_Long)3L))) {
	      temp_1 = TRUEP(Nil);
	      goto end_1;
	  }
	  goto next_loop_2;
	end_loop_2:
	  temp_1 = TRUEP(T);
	  goto end_1;
	  temp_1 = TRUEP(Qnil);
	end_1:;
      }
      else
	  temp_1 = TRUEP(Nil);
      if (temp_1) {
	  ab_loopvar__4 = 
		  slot_value_cons_1(make_external_method_info_for_g2_method(export_class,
		  g2_method,Nil,T),Nil);
	  if (ab_loopvar__3)
	      M_CDR(ab_loopvar__3) = ab_loopvar__4;
	  else
	      ab_loopvar__2 = ab_loopvar__4;
	  ab_loopvar__3 = ab_loopvar__4;
      }
      goto next_loop;
    end_loop_1:
      temp = ab_loopvar__2;
      goto end_2;
      temp = Qnil;
    end_2:;
    POP_SPECIAL();
    return VALUES_1(temp);
}

DEFINE_VARIABLE_WITH_SYMBOL(Bypass_add_class_export_info_attributes_p, Qbypass_add_class_export_info_attributes_p);

/* G2-ADD-CLASS-EXPORT-INFO-ATTRIBUTES */
Object g2_add_class_export_info_attributes(bypass)
    Object bypass;
{
    x_note_fn_call(251,60);
    Bypass_add_class_export_info_attributes_p = FIXNUM_GE(M_CAR(bypass),
	    ISVREF(Inference_engine_parameters,(SI_Long)26L)) ? T : Nil;
    return VALUES_1(bypass);
}

static Object Qinstance_methods;   /* instance-methods */

static Object Qexported_source;    /* exported-source */

static Object Qhand_coded_methods;  /* hand-coded-methods */

/* ADD-CLASS-EXPORT-INFO-ATTRIBUTES */
Object add_class_export_info_attributes(class_name,class_info_attributes)
    Object class_name, class_info_attributes;
{
    Object export_definition_qm, class_info, hand_coded_methods_qm;
    Object collecting_exported_method_text_p, list_of_exported_method_texts;
    Object exported_source_qm, list_of_exported_method_texts_new_value;
    Object static_method_info, instance_method_info, method_info_list;
    Declare_special(3);
    Object result;

    x_note_fn_call(251,61);
    PUSH_SPECIAL_WITH_SYMBOL(Class_info_attributes,Qclass_info_attributes,class_info_attributes,
	    2);
      if ( !TRUEP(Bypass_add_class_export_info_attributes_p)) {
	  if (lookup_global_or_kb_specific_property_value(class_name,
		  Class_description_gkbprop)) {
	      result = get_export_definition_and_info_for_class_if_any(class_name);
	      MVS_2(result,export_definition_qm,class_info);
	      if (export_definition_qm) {
		  hand_coded_methods_qm = 
			  get_hand_coded_methods_for_class_if_any(export_definition_qm);
		  collecting_exported_method_text_p = T;
		  PUSH_SPECIAL_WITH_SYMBOL(Collecting_exported_method_text_p,Qcollecting_exported_method_text_p,collecting_exported_method_text_p,
			  1);
		    list_of_exported_method_texts = Nil;
		    PUSH_SPECIAL_WITH_SYMBOL(List_of_exported_method_texts,Qlist_of_exported_method_texts,list_of_exported_method_texts,
			    0);
		      exported_source_qm = 
			      get_exported_source_for_class_if_possible(export_definition_qm,
			      class_name,hand_coded_methods_qm);
		      list_of_exported_method_texts_new_value = 
			      nreverse(List_of_exported_method_texts);
		      List_of_exported_method_texts = 
			      list_of_exported_method_texts_new_value;
		      static_method_info = 
			      get_external_static_method_info_for_class(class_info);
		      instance_method_info = 
			      get_external_instance_method_info_for_class(class_info);
		      Class_info_attributes = eval_cons_1(Qstatic_methods,
			      Class_info_attributes);
		      Class_info_attributes = 
			      eval_cons_1(static_method_info,
			      Class_info_attributes);
		      Class_info_attributes = 
			      eval_cons_1(Qinstance_methods,
			      Class_info_attributes);
		      Class_info_attributes = 
			      eval_cons_1(instance_method_info,
			      Class_info_attributes);
		      if (exported_source_qm) {
			  Class_info_attributes = 
				  eval_cons_1(Qexported_source,
				  Class_info_attributes);
			  Class_info_attributes = 
				  eval_cons_1(exported_source_qm,
				  Class_info_attributes);
		      }
		      if (hand_coded_methods_qm) {
			  Class_info_attributes = 
				  eval_cons_1(Qhand_coded_methods,
				  Class_info_attributes);
			  Class_info_attributes = 
				  eval_cons_1(hand_coded_methods_qm,
				  Class_info_attributes);
		      }
		    POP_SPECIAL();
		  POP_SPECIAL();
	      }
	      else {
		  method_info_list = collect_instance_method_export_info(3,
			  class_name,Nil,Nil);
		  instance_method_info = 
			  get_evaluation_sequence_from_external_method_info_list(method_info_list);
		  Class_info_attributes = eval_cons_1(Qinstance_methods,
			  Class_info_attributes);
		  Class_info_attributes = eval_cons_1(instance_method_info,
			  Class_info_attributes);
		  reclaim_list_of_external_methods(method_info_list);
	      }
	  }
      }
      result = VALUES_1(Class_info_attributes);
    POP_SPECIAL();
    return result;
}

/* GET-EXPORT-DEFINITION-AND-INFO-FOR-CLASS-IF-ANY */
Object get_export_definition_and_info_for_class_if_any(class_name)
    Object class_name;
{
    Object export_definition_qm, class_info;
    Object result;

    x_note_fn_call(251,62);
    result = get_user_visible_export_definition_and_info_for_class_if_any(class_name);
    MVS_2(result,export_definition_qm,class_info);
    if (export_definition_qm)
	return VALUES_2(export_definition_qm,class_info);
    else {
	result = get_implicit_export_definition_and_info_for_class_if_possible(class_name);
	MVS_2(result,export_definition_qm,class_info);
	return VALUES_2(export_definition_qm,class_info);
    }
}

static Object Qinclude_method_text_in_class_export;  /* include-method-text-in-class-export */

static Object Qmethod_name;        /* method-name */

static Object Qis_static;          /* is-static */

static Object Qargument_types;     /* argument-types */

static Object Qresult_types;       /* result-types */

static Object Qg2_method_text;     /* g2-method-text */

static Object Qtext;               /* text */

static Object Qmethod_source;      /* method-source */

/* GET-EVALUATION-STRUCTURE-FOR-ONE-EXTERNAL-METHOD */
Object get_evaluation_structure_for_one_external_method(method_info,
	    method_text_qm)
    Object method_info, method_text_qm;
{
    Object method_info_attributes, method_name, static_p, is_static;
    Object g2_internal_method_qm, argument_types, result_types;
    Object interface_frame_qm, x2, gensymed_symbol, x, y, xa, ya;
    Object include_method_text_p, temp_1;
    char temp;

    x_note_fn_call(251,63);
    method_info_attributes = Nil;
    method_name = ISVREF(method_info,(SI_Long)2L);
    static_p = ISVREF(method_info,(SI_Long)7L);
    is_static = static_p ? Evaluation_true_value : Evaluation_false_value;
    g2_internal_method_qm = get_matching_g2_procedure_if_any(method_info,
	    static_p);
    if ( !TRUEP(g2_internal_method_qm)) {
	if ( !(EQ(is_static,Evaluation_true_value) || EQ(is_static,
		Evaluation_false_value)))
	    reclaim_eval_cons_1(is_static);
    }
    else {
	argument_types = 
		export_types_in_arguments_or_results_as_sequence(ISVREF(g2_internal_method_qm,
		(SI_Long)24L));
	result_types = 
		export_types_in_arguments_or_results_as_sequence(ISVREF(g2_internal_method_qm,
		(SI_Long)25L));
	interface_frame_qm = Current_system_rpc_icp_socket_qm ? 
		ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)5L) : Nil;
	if (SIMPLE_VECTOR_P(interface_frame_qm) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(interface_frame_qm)) > 
		(SI_Long)2L &&  !EQ(ISVREF(interface_frame_qm,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(interface_frame_qm,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    gensymed_symbol = ISVREF(interface_frame_qm,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(interface_frame_qm) ? 
		    EQ(ISVREF(interface_frame_qm,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)6L);
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
	include_method_text_p = temp ? 
		get_lookup_slot_value_given_default(interface_frame_qm,
		Qinclude_method_text_in_class_export,Nil) : Nil;
	method_info_attributes = eval_cons_1(Qmethod_name,
		method_info_attributes);
	method_info_attributes = eval_cons_1(method_name,
		method_info_attributes);
	method_info_attributes = eval_cons_1(Qis_static,
		method_info_attributes);
	method_info_attributes = eval_cons_1(is_static,method_info_attributes);
	method_info_attributes = eval_cons_1(Qargument_types,
		method_info_attributes);
	method_info_attributes = eval_cons_1(argument_types,
		method_info_attributes);
	method_info_attributes = eval_cons_1(Qresult_types,
		method_info_attributes);
	method_info_attributes = eval_cons_1(result_types,
		method_info_attributes);
	if (include_method_text_p) {
	    method_info_attributes = eval_cons_1(Qg2_method_text,
		    method_info_attributes);
	    temp_1 = get_text_of_attribute(g2_internal_method_qm,Qtext,
		    ISVREF(ISVREF(g2_internal_method_qm,(SI_Long)1L),
		    (SI_Long)1L));
	    method_info_attributes = eval_cons_1(temp_1,
		    method_info_attributes);
	}
	if (method_text_qm) {
	    method_info_attributes = eval_cons_1(Qmethod_source,
		    method_info_attributes);
	    method_info_attributes = eval_cons_1(method_text_qm,
		    method_info_attributes);
	}
    }
    temp_1 = allocate_evaluation_structure(nreverse(method_info_attributes));
    return VALUES_1(temp_1);
}

static Object list_constant_1;     /* # */

static Object Qquantity;           /* quantity */

static Object Qdatum;              /* datum */

static Object Qvalue;              /* value */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qitem_or_value;      /* item-or-value */

static Object Qab_structure;       /* structure */

/* EXPORT-TYPES-IN-ARGUMENTS-OR-RESULTS-AS-SEQUENCE */
Object export_types_in_arguments_or_results_as_sequence(arguments_or_results)
    Object arguments_or_results;
{
    Object gensym_list_of_types, type, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp, tag, eval_list_of_java_types;

    x_note_fn_call(251,64);
    gensym_list_of_types = 
	    collect_types_into_list_using_gensym_conses(arguments_or_results);
    type = Nil;
    ab_loop_list_ = gensym_list_of_types;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    type = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (member_eql(type,list_constant_1))
	temp = type;
    else if (EQ(type,Qnumber))
	temp = Qquantity;
    else if (EQ(type,Qdatum))
	temp = Qvalue;
    else if (EQ(type,Qitem_or_datum))
	temp = Qitem_or_value;
    else if (CONSP(type)) {
	tag = CAR(type);
	if (EQ(tag,Qsequence) || EQ(tag,Qab_structure))
	    temp = tag;
	else if (EQ(tag,Qab_class))
	    temp = allocate_evaluation_structure(eval_list_2(Qab_class,
		    CADR(type)));
	else {
	    cerror((SI_Long)3L,"use ITEM-OR-VALUE",
		    "ADD-CLASS-EXPORT-INFO-ATTRIBUTES: unknown compound type ~S",
		    type);
	    temp = Qitem_or_value;
	}
    }
    else {
	cerror((SI_Long)3L,"use ITEM-OR-VALUE",
		"ADD-CLASS-EXPORT-INFO-ATTRIBUTES: refractory type spec ~S",
		type);
	temp = Qitem_or_value;
    }
    ab_loopvar__2 = eval_cons_1(temp,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    eval_list_of_java_types = ab_loopvar_;
    goto end_1;
    eval_list_of_java_types = Qnil;
  end_1:;
    reclaim_gensym_list_1(gensym_list_of_types);
    temp = allocate_evaluation_sequence(eval_list_of_java_types);
    return VALUES_1(temp);
}

static Object Qab_slot_value;      /* slot-value */

/* GET-EXTERNAL-STATIC-METHOD-INFO-FOR-CLASS */
Object get_external_static_method_info_for_class(class_info)
    Object class_info;
{
    Object method_info, ab_loop_list_, method_text_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, slot_value_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2, eval_list_of_sequence_elements;
    Object temp_1;

    x_note_fn_call(251,65);
    method_info = Nil;
    ab_loop_list_ = ISVREF(class_info,(SI_Long)2L);
    method_text_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    method_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_value_pop_store = Nil;
    cons_1 = List_of_exported_method_texts;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    List_of_exported_method_texts = next_cons;
    method_text_qm = slot_value_pop_store;
    ab_loopvar__2 = 
	    eval_cons_1(get_evaluation_structure_for_one_external_method(method_info,
	    method_text_qm),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    eval_list_of_sequence_elements = ab_loopvar_;
    goto end_1;
    eval_list_of_sequence_elements = Qnil;
  end_1:;
    temp_1 = 
	    allocate_evaluation_sequence(nreverse(eval_list_of_sequence_elements));
    return VALUES_1(temp_1);
}

/* GET-EXTERNAL-INSTANCE-METHOD-INFO-FOR-CLASS */
Object get_external_instance_method_info_for_class(class_info)
    Object class_info;
{
    Object temp;

    x_note_fn_call(251,66);
    temp = 
	    get_evaluation_sequence_from_external_method_info_list(ISVREF(class_info,
	    (SI_Long)3L));
    return VALUES_1(temp);
}

/* GET-EVALUATION-SEQUENCE-FROM-EXTERNAL-METHOD-INFO-LIST */
Object get_evaluation_sequence_from_external_method_info_list(method_info_list)
    Object method_info_list;
{
    Object method_info, ab_loop_list_, method_text_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, slot_value_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2, eval_list_of_sequence_elements;
    Object temp_1;

    x_note_fn_call(251,67);
    method_info = Nil;
    ab_loop_list_ = method_info_list;
    method_text_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    method_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    slot_value_pop_store = Nil;
    cons_1 = List_of_exported_method_texts;
    if (cons_1) {
	slot_value_pop_store = M_CAR(cons_1);
	next_cons = M_CDR(cons_1);
	inline_note_reclaim_cons(cons_1,Qab_slot_value);
	if (ISVREF(Available_slot_value_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	else {
	    temp = Available_slot_value_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	    temp = Available_slot_value_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = cons_1;
	}
	M_CDR(cons_1) = Nil;
    }
    else
	next_cons = Nil;
    List_of_exported_method_texts = next_cons;
    method_text_qm = slot_value_pop_store;
    ab_loopvar__2 = 
	    eval_cons_1(get_evaluation_structure_for_one_external_method(method_info,
	    method_text_qm),Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop;
  end_loop:
    eval_list_of_sequence_elements = ab_loopvar_;
    goto end_1;
    eval_list_of_sequence_elements = Qnil;
  end_1:;
    temp_1 = 
	    allocate_evaluation_sequence(nreverse(eval_list_of_sequence_elements));
    return VALUES_1(temp_1);
}

/* GET-EXPORTED-STATIC-METHODS-IF-ANY */
Object get_exported_static_methods_if_any(export_definition,class_name)
    Object export_definition, class_name;
{
    Object class_info, ab_loop_list_, ab_loop_it_, class_info_qm, method_info;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object extant_static_methods_list, temp;

    x_note_fn_call(251,68);
    class_info = Nil;
    ab_loop_list_ = get_lookup_slot_value_given_default(export_definition,
	    Qvisible_class_export_information_qm,Nil);
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_info = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = EQ(ISVREF(class_info,(SI_Long)1L),class_name) ? 
	    class_info : Qnil;
    if (ab_loop_it_) {
	class_info_qm = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    class_info_qm = Qnil;
  end_1:;
    if (class_info_qm) {
	method_info = Nil;
	ab_loop_list_ = ISVREF(class_info_qm,(SI_Long)2L);
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	method_info = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ISVREF(method_info,(SI_Long)10L))) {
	    ab_loopvar__2 = slot_value_cons_1(ISVREF(method_info,
		    (SI_Long)9L),Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	extant_static_methods_list = ab_loopvar_;
	goto end_2;
	extant_static_methods_list = Qnil;
      end_2:;
	temp = extant_static_methods_list ? extant_static_methods_list : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

/* GET-EXTERNAL-CLASS-SPECIFIC-METHODS */
Object get_external_class_specific_methods(class_name)
    Object class_name;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, export_definition;
    Object class_info, ab_loop_list_, method_info, ab_loopvar__2, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(251,69);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    export_definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qexport_definition);
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
      export_definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      class_info = Nil;
      ab_loop_list_ = 
	      get_lookup_slot_value_given_default(export_definition,
	      Qvisible_class_export_information_qm,Nil);
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      class_info = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (EQ(ISVREF(class_info,(SI_Long)1L),class_name)) {
	  method_info = Nil;
	  ab_loop_list_ = ISVREF(class_info,(SI_Long)3L);
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop_3:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_3;
	  method_info = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  ab_loopvar__2 = gensym_cons_1(ISVREF(method_info,(SI_Long)9L),Nil);
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop_3;
	end_loop_3:
	  temp_1 = ab_loopvar_;
	  goto end_1;
	  temp_1 = Qnil;
	end_1:;
	  POP_SPECIAL();
	  goto end_got_methods;
      }
      goto next_loop_2;
    end_loop_2:;
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    temp_1 = Nil;
  end_got_methods:
    return VALUES_1(temp_1);
}

static Object Qimports;            /* imports */

static Object Qsuperior_class_override;  /* superior-class-override */

static Object Qjwith_output_to_text_string;  /* jwith-output-to-text-string */

static Object Kjemit_error;        /* :jemit-error */

/* GET-EXPORTED-SOURCE-FOR-CLASS-IF-POSSIBLE */
Object get_exported_source_for_class_if_possible(export_definition,
	    class_name,additional_methods_qm)
    Object export_definition, class_name, additional_methods_qm;
{
    Object temp, class_export_specs, export_class, ab_loop_list_;
    Object class_export_spec, ab_loop_list__1, ab_loop_it_, ab_loop_desetq_;
    Object class_export_tree, gensymed_symbol, options;
    Object extant_static_methods_list, imports_qm, package_qm;
    Object superior_class_override_qm, error_string_qm, valid_string_qm;
    Object collecting_frame_notes_for_class_export_p;
    Object collected_frame_notes_for_class_export_qm, jemit_error_qm;
    Object text_string_stream, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_text_string, success_string, error_string_qm_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_catch(1);
    Declare_special(7);
    Object result;

    x_note_fn_call(251,70);
    temp = get_lookup_slot_value_given_default(export_definition,
	    Qexport_definition_specification,Nil);
    class_export_specs = CADR(temp);
    export_class = Nil;
    ab_loop_list_ = class_export_specs;
    class_export_spec = Nil;
    ab_loop_list__1 = class_export_specs;
    ab_loop_it_ = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    export_class = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    class_export_spec = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    ab_loop_it_ = EQ(export_class,class_name) ? class_export_spec : Qnil;
    if (ab_loop_it_) {
	class_export_tree = ab_loop_it_;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    class_export_tree = Qnil;
  end_1:;
    gensymed_symbol = class_export_tree;
    class_name = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    options = CAR(gensymed_symbol);
    if (lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop)) {
	extant_static_methods_list = 
		get_exported_static_methods_if_any(export_definition,
		class_name);
	temp = assq_function(Qimports,options);
	imports_qm = CADR(temp);
	temp = assq_function(Qpackage_type,options);
	package_qm = CADR(temp);
	temp = assq_function(Qsuperior_class_override,options);
	superior_class_override_qm = CADR(temp);
	error_string_qm = Nil;
	valid_string_qm = Nil;
	collecting_frame_notes_for_class_export_p = T;
	PUSH_SPECIAL_WITH_SYMBOL(Collecting_frame_notes_for_class_export_p,Qcollecting_frame_notes_for_class_export_p,collecting_frame_notes_for_class_export_p,
		6);
	  collected_frame_notes_for_class_export_qm = Nil;
	  PUSH_SPECIAL_WITH_SYMBOL(Collected_frame_notes_for_class_export_qm,Qcollected_frame_notes_for_class_export_qm,collected_frame_notes_for_class_export_qm,
		  5);
	    jemit_error_qm = Nil;
	    text_string_stream = Qjwith_output_to_text_string;
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
		      if (PUSH_CATCH(Kjemit_error,0)) {
			  jemit_class_to_stream(class_name,
				  extant_static_methods_list,package_qm,
				  imports_qm,Nil,Nil,
				  superior_class_override_qm,
				  additional_methods_qm,text_string_stream);
			  POP_CATCH(0);
			  goto end_gensymed_symbol;
		      }
		      else
			  error_text_string = CATCH_VALUES();
		      POP_CATCH(0);
		      jemit_error_qm = error_text_string;
		    end_gensymed_symbol:
		      success_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    if (jemit_error_qm) {
		if (INLINE_UNSIGNED_BYTE_16_VECTOR_P(success_string) != 
			(SI_Long)0L)
		    reclaim_wide_string(success_string);
		result = VALUES_2(Nil,jemit_error_qm);
	    }
	    else
		result = VALUES_2(success_string,Nil);
	    MVS_2(result,valid_string_qm,error_string_qm);
	    error_string_qm_1 = error_string_qm;
	    update_mapping_problem_frame_notes_if_necessary(export_definition,
		    class_name,error_string_qm_1);
	  POP_SPECIAL();
	POP_SPECIAL();
	reclaim_slot_value_list_1(extant_static_methods_list);
	return VALUES_1(valid_string_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object Qproblem_mapping_g2_to_java_source;  /* problem-mapping-g2-to-java-source */

/* UPDATE-MAPPING-PROBLEM-FRAME-NOTES-IF-NECESSARY */
Object update_mapping_problem_frame_notes_if_necessary(export_definition,
	    class_name,error_string_qm)
    Object export_definition, class_name, error_string_qm;
{
    Object temp, tail_value_1_qm, cdr_new_value, temp_1;

    x_note_fn_call(251,71);
    clear_problem_mapping_g2_to_java_source_particulars(export_definition,
	    class_name);
    if (error_string_qm || Collected_frame_notes_for_class_export_qm) {
	temp = nreverse(Collected_frame_notes_for_class_export_qm);
	Collected_frame_notes_for_class_export_qm = temp;
	tail_value_1_qm = error_string_qm ? 
		slot_value_cons_1(error_string_qm,Nil) : Nil;
	if (tail_value_1_qm) {
	    temp = last(tail_value_1_qm,_);
	    cdr_new_value = Collected_frame_notes_for_class_export_qm;
	    M_CDR(temp) = cdr_new_value;
	    temp_1 = tail_value_1_qm;
	}
	else
	    temp_1 = Collected_frame_notes_for_class_export_qm;
	add_to_frame_note_particulars_list_if_necessary(slot_value_cons_1(class_name,
		temp_1),Qproblem_mapping_g2_to_java_source,export_definition);
    }
    return VALUES_1(Nil);
}

/* CLEAR-PROBLEM-MAPPING-G2-TO-JAVA-SOURCE-PARTICULARS */
Object clear_problem_mapping_g2_to_java_source_particulars(export_definition,
	    class_name)
    Object export_definition, class_name;
{
    Object particulars, temp, flawed_class, ab_loop_list_, particular;
    Object ab_loop_list__1, ab_loop_desetq_;

    x_note_fn_call(251,72);
    if (Current_computation_component_particulars)
	particulars = 
		get_particulars_of_frame_note_from_component_particulars(Qproblem_mapping_g2_to_java_source,
		export_definition,Current_computation_component_particulars);
    else {
	temp = ISVREF(export_definition,(SI_Long)8L);
	particulars = getfq_function_no_default(CDR(temp),
		Qproblem_mapping_g2_to_java_source);
    }
    flawed_class = Nil;
    ab_loop_list_ = particulars;
    particular = Nil;
    ab_loop_list__1 = particulars;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    flawed_class = CAR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    particular = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(class_name,flawed_class)) {
	delete_from_frame_note_particulars_list(particular,
		Qproblem_mapping_g2_to_java_source,export_definition);
	goto end_loop;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object string_constant_5;   /* "a problem was encountered mapping the G2 class ~A to Java: ~A" */

/* WRITE-PROBLEM-MAPPING-G2-TO-JAVA-SOURCE-NOTE */
Object write_problem_mapping_g2_to_java_source_note(particulars,
	    gensymed_symbol)
    Object particulars, gensymed_symbol;
{
    Object enumerate_p, temp, flawed_class, flaws_in_class, ab_loop_list_;
    Object particulars_cons, index_1, ab_loop_iter_flag_, ab_loop_desetq_;
    Object flaw_in_class, ab_loop_list__1, flaw_in_class_cons;

    x_note_fn_call(251,73);
    enumerate_p = CDR(particulars);
    if (enumerate_p);
    else {
	temp = CAR(particulars);
	enumerate_p = CDDR(temp);
    }
    flawed_class = Nil;
    flaws_in_class = Nil;
    ab_loop_list_ = particulars;
    particulars_cons = particulars;
    index_1 = FIX((SI_Long)0L);
    ab_loop_iter_flag_ = T;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    flawed_class = CAR(ab_loop_desetq_);
    flaws_in_class = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	particulars_cons = M_CDR(particulars_cons);
    if ( !TRUEP(particulars_cons))
	goto end_loop;
    flaw_in_class = Nil;
    ab_loop_list__1 = flaws_in_class;
    flaw_in_class_cons = flaws_in_class;
    ab_loop_iter_flag_ = T;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    flaw_in_class = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if ( !TRUEP(ab_loop_iter_flag_))
	flaw_in_class_cons = M_CDR(flaw_in_class_cons);
    if ( !TRUEP(flaw_in_class_cons))
	goto end_loop_1;
    if (enumerate_p)
	tformat(2,string_constant_3,FIXNUM_ADD(index_1,Frame_note_index));
    tformat(3,string_constant_5,flawed_class,flaw_in_class);
    index_1 = FIXNUM_ADD1(index_1);
    if (enumerate_p) {
	if (CDR(particulars_cons) || CDR(flaw_in_class_cons)) {
	    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)1L));
	    twrite_line_separator();
	}
    }
    ab_loop_iter_flag_ = Nil;
    goto next_loop_1;
  end_loop_1:
    Frame_note_index_skip = FIXNUM_SUB1(index_1);
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:;
    GENSYM_RETURN_ONE(Qnil);
    return VALUES_1(Nil);
}

static Object Qadditional_java_methods;  /* additional-java-methods */

static Object Qnone;               /* none */

/* GET-HAND-CODED-METHODS-FOR-CLASS-IF-ANY */
Object get_hand_coded_methods_for_class_if_any(export_definition)
    Object export_definition;
{
    Object translation_and_text_qm, temp;

    x_note_fn_call(251,74);
    translation_and_text_qm = 
	    get_slot_value_if_any_function(export_definition,
	    Qadditional_java_methods,Nil);
    temp = translation_and_text_qm &&  !EQ(CAR(translation_and_text_qm),
	    Qnone) ? convert_text_to_text_string(1,
	    CDR(translation_and_text_qm)) : Qnil;
    return VALUES_1(temp);
}

/* GET-USER-VISIBLE-EXPORT-DEFINITION-AND-INFO-FOR-CLASS-IF-ANY */
Object get_user_visible_export_definition_and_info_for_class_if_any(class_name)
    Object class_name;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, export_definition;
    Object class_info, ab_loop_list_, ab_loop_it_, class_info_qm;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(251,75);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    export_definition = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qexport_definition);
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
      export_definition = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      class_info = Nil;
      ab_loop_list_ = 
	      get_lookup_slot_value_given_default(export_definition,
	      Qvisible_class_export_information_qm,Nil);
      ab_loop_it_ = Nil;
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      class_info = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      ab_loop_it_ = EQ(ISVREF(class_info,(SI_Long)1L),class_name) ? 
	      class_info : Qnil;
      if (ab_loop_it_) {
	  class_info_qm = ab_loop_it_;
	  goto end_1;
      }
      goto next_loop_2;
    end_loop_2:
      class_info_qm = Qnil;
    end_1:;
      if (class_info_qm) {
	  result = VALUES_2(export_definition,class_info_qm);
	  goto end_2;
      }
      goto next_loop;
    end_loop_1:
      result = VALUES_2(Nil,Nil);
      goto end_2;
      result = VALUES_1(Qnil);
    end_2:;
    POP_SPECIAL();
    return result;
}

/* DECACHE-IMPLICIT-EXTERNAL-INSTANCE-METHOD-INFO-IF-ANY */
Object decache_implicit_external_instance_method_info_if_any(class_name)
    Object class_name;
{
    Object description_qm, export_definition_qm, slot_value_pop_store, cons_1;
    Object next_cons, temp, svref_arg_2, external_class_info;
    Object external_instance_method_info;

    x_note_fn_call(251,76);
    description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    export_definition_qm = description_qm ? ISVREF(description_qm,
	    (SI_Long)21L) : Qnil;
    if (export_definition_qm) {
	slot_value_pop_store = Nil;
	cons_1 = get_lookup_slot_value_given_default(export_definition_qm,
		Qvisible_class_export_information_qm,Nil);
	if (cons_1) {
	    slot_value_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	set_non_savable_lookup_slot_value(export_definition_qm,
		Qvisible_class_export_information_qm,next_cons);
	external_class_info = slot_value_pop_store;
	external_instance_method_info = ISVREF(external_class_info,
		(SI_Long)3L);
	SVREF(external_class_info,FIX((SI_Long)3L)) = Nil;
	reclaim_external_class_info_1(external_class_info);
	set_non_savable_lookup_slot_value(export_definition_qm,
		Qvisible_class_export_information_qm,Nil);
	delete_frame(export_definition_qm);
	SVREF(description_qm,FIX((SI_Long)21L)) = Nil;
	return VALUES_2(external_instance_method_info,T);
    }
    else
	return VALUES_2(Nil,Nil);
}

Object Cache_implicit_class_export_info_p = UNBOUND;

/* GET-IMPLICIT-EXPORT-DEFINITION-AND-INFO-FOR-CLASS-IF-POSSIBLE */
Object get_implicit_export_definition_and_info_for_class_if_possible(class_name)
    Object class_name;
{
    Object description_qm, export_definition_qm, temp;

    x_note_fn_call(251,77);
    if (Cache_implicit_class_export_info_p) {
	description_qm = 
		lookup_global_or_kb_specific_property_value(class_name,
		Class_description_gkbprop);
	export_definition_qm = description_qm ? ISVREF(description_qm,
		(SI_Long)21L) : Qnil;
	if (export_definition_qm) {
	    temp = 
		    get_lookup_slot_value_given_default(export_definition_qm,
		    Qvisible_class_export_information_qm,Nil);
	    return VALUES_2(export_definition_qm,CAR(temp));
	}
	else
	    return make_implicit_export_definition_and_class_info(class_name);
    }
    else
	return VALUES_2(Nil,Nil);
}

/* MAKE-IMPLICIT-EXPORT-DEFINITION-AND-CLASS-INFO */
Object make_implicit_export_definition_and_class_info(class_name)
    Object class_name;
{
    Object export_definition, description_qm, external_method_info, class_info;
    Object svref_new_value;

    x_note_fn_call(251,78);
    export_definition = make_frame(Qexport_definition);
    description_qm = 
	    lookup_global_or_kb_specific_property_value(class_name,
	    Class_description_gkbprop);
    external_method_info = collect_instance_method_export_info(2,
	    class_name,Nil);
    class_info = make_external_class_info_1(class_name,Nil,
	    external_method_info);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(export_definition,
		Qexport_definition_specification);
    set_lookup_slot_value_1(export_definition,
	    Qexport_definition_specification,slot_value_cons_1(Qjava,
	    slot_value_cons_1(Qnil,
	    slot_value_cons_1(slot_value_cons_1(slot_value_cons_1(class_name,
	    Nil),Nil),Nil))));
    if (description_qm) {
	svref_new_value = slot_value_cons_1(class_info,Nil);
	SVREF(description_qm,FIX((SI_Long)21L)) = svref_new_value;
    }
    return VALUES_2(export_definition,class_info);
}

Object Syntax_tree_template_registry = UNBOUND;

/* PUSH-NEW-SYNTAX-TREE-TEMPLATE-ENTRY */
Object push_new_syntax_tree_template_entry(name,new_entry)
    Object name, new_entry;
{
    Object temp, syntax_tree_template_registry_old_value, temp_1, push_arg;
    Object extant_entry_qm;

    x_note_fn_call(251,79);
    if ( !TRUEP(Syntax_tree_template_registry)) {
	Syntax_tree_template_registry = LIST_1(new_entry);
	return VALUES_1(Syntax_tree_template_registry);
    }
    else {
	temp = FIRST(Syntax_tree_template_registry);
	if (EQ(name,FIRST(temp))) {
	    syntax_tree_template_registry_old_value = 
		    Syntax_tree_template_registry;
	    temp_1 = REST(syntax_tree_template_registry_old_value);
	    Syntax_tree_template_registry = temp_1;
	    push_arg = new_entry;
	    temp_1 = CONS(push_arg,Syntax_tree_template_registry);
	    Syntax_tree_template_registry = temp_1;
	    return VALUES_1(Syntax_tree_template_registry);
	}
	else {
	    extant_entry_qm = assoc_eql(name,Syntax_tree_template_registry);
	    if (extant_entry_qm) {
		temp_1 = CDR(new_entry);
		return VALUES_1(M_CDR(extant_entry_qm) = temp_1);
	    }
	    else {
		push_arg = new_entry;
		temp_1 = CONS(push_arg,Syntax_tree_template_registry);
		Syntax_tree_template_registry = temp_1;
		return VALUES_1(Syntax_tree_template_registry);
	    }
	}
    }
}

DEFINE_VARIABLE_WITH_SYMBOL(Global_output_stream_for_expand_syntax_template, Qglobal_output_stream_for_expand_syntax_template);

static Object Qtext_conversion_style;  /* text-conversion-style */

static Object Qutf_8_string;       /* utf-8-string */

static Object Qtext_conversion_style_for_purpose;  /* text-conversion-style-for-purpose */

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object string_constant_6;   /* "JEMIT ERROR: ~a" */

/* EXPAND-SYNTAX-TEMPLATE-GIVEN-BINDINGS */
Object expand_syntax_template_given_bindings(template_name,bindings,filename)
    Object template_name, bindings, filename;
{
    Object jemit_error_qm, temp, current_jemit_text_style_qm;
    Object global_output_stream_for_expand_syntax_template, error_text_string;
    Declare_stack_pointer;
    Declare_catch(2);
    Declare_special(2);
    Object result;

    x_note_fn_call(251,80);
    SAVE_STACK();
    jemit_error_qm = Nil;
    temp = 
	    get_text_conversion_style_structure_per_name(get_lookup_slot_value_given_default(Language_parameters,
	    Qtext_conversion_style,Nil));
    if (temp);
    else
	temp = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qutf_8_string),
		Qtext_conversion_style_for_purpose);
    current_jemit_text_style_qm = temp;
    PUSH_SPECIAL_WITH_SYMBOL(Current_jemit_text_style_qm,Qcurrent_jemit_text_style_qm,current_jemit_text_style_qm,
	    1);
      if (PUSH_CATCH(Kjemit_error,1)) {
	  global_output_stream_for_expand_syntax_template = 
		  Qunbound_in_protected_let;
	  PUSH_SPECIAL_WITH_SYMBOL(Global_output_stream_for_expand_syntax_template,Qglobal_output_stream_for_expand_syntax_template,global_output_stream_for_expand_syntax_template,
		  0);
	    if (PUSH_UNWIND_PROTECT(0)) {
		Global_output_stream_for_expand_syntax_template = 
			g2_stream_open_for_output(filename);
		if (Global_output_stream_for_expand_syntax_template)
		    expand_syntax_template_within_output_to_java_source_file(template_name,
			    bindings,FIX((SI_Long)2L));
	    }
	    POP_UNWIND_PROTECT(0);
	    if (Global_output_stream_for_expand_syntax_template) {
		if ( !EQ(Global_output_stream_for_expand_syntax_template,
			Qunbound_in_protected_let))
		    g2_stream_close(Global_output_stream_for_expand_syntax_template);
	    }
	    CONTINUE_UNWINDING(0);
	  POP_SPECIAL();
	  POP_CATCH(1);
	  goto end_gensymed_symbol;
      }
      else
	  error_text_string = CATCH_VALUES();
      POP_CATCH(1);
      jemit_error_qm = error_text_string;
    end_gensymed_symbol:
      if (jemit_error_qm) {
	  Suppress_warning_message_header_qm = T;
	  if ((SI_Long)1L <= IFIX(Warning_message_level))
	      give_warning_1(3,FIX((SI_Long)1L),string_constant_6,
		      jemit_error_qm);
	  Suppress_warning_message_header_qm = Nil;
	  result = VALUES_1(jemit_error_qm);
      }
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* LOOK-UP-RAW-SYNTAX-TREE-BINDING */
Object look_up_raw_syntax_tree_binding(key,bindings)
    Object key, bindings;
{
    Object temp;

    x_note_fn_call(251,81);
    temp = assq_function(key,bindings);
    return VALUES_1(temp);
}

/* LOOK-UP-ATOMIC-SYNTAX-TREE-BINDING */
Object look_up_atomic_syntax_tree_binding(key,bindings)
    Object key, bindings;
{
    Object temp, result_1;

    x_note_fn_call(251,82);
    temp = look_up_raw_syntax_tree_binding(key,bindings);
    result_1 = THIRD(temp);
    return VALUES_1(result_1);
}

/* LOOK-UP-ATOMIC-SYNTAX-TREE-BINDING-IF-ANY */
Object look_up_atomic_syntax_tree_binding_if_any(key,bindings)
    Object key, bindings;
{
    Object temp, result_1;

    x_note_fn_call(251,83);
    temp = look_up_raw_syntax_tree_binding(key,bindings);
    result_1 = THIRD(temp);
    return VALUES_1(CONSP(result_1) ? Nil : result_1);
}

Object Syntax_tree_no_binding_tag = UNBOUND;

static Object Qlist_expected;      /* list-expected */

static Object Qlist_of_lists_expected;  /* list-of-lists-expected */

/* LOOK-UP-LISTED-SYNTAX-TREE-BINDING */
Object look_up_listed_syntax_tree_binding(key,bindings,
	    expected_list_structure,destructive_p)
    Object key, bindings, expected_list_structure, destructive_p;
{
    Object correct_list_structure_p, raw_binding, raw_contents, result_1;
    Object slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object maybe_nested_list;

    x_note_fn_call(251,84);
    correct_list_structure_p = T;
    raw_binding = look_up_raw_syntax_tree_binding(key,bindings);
    raw_contents = THIRD(raw_binding);
    if (EQ(expected_list_structure,Qlist_expected)) {
	if ( !TRUEP(raw_contents))
	    result_1 = Syntax_tree_no_binding_tag;
	else if (CONSP(raw_contents)) {
	    if (destructive_p) {
		slot_value_pop_store = Nil;
		cons_1 = CADDR(raw_binding);
		if (cons_1) {
		    slot_value_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qab_slot_value);
		    if (ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp = 
				ISVREF(Available_slot_value_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp) = cons_1;
			temp = Available_slot_value_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    else {
			temp = Available_slot_value_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
			temp = Available_slot_value_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		M_CADDR(raw_binding) = next_cons;
		result_1 = slot_value_pop_store;
	    }
	    else
		result_1 = CAR(raw_contents);
	}
	else {
	    correct_list_structure_p = Nil;
	    result_1 = raw_contents;
	}
    }
    else if (EQ(expected_list_structure,Qlist_of_lists_expected)) {
	if ( !TRUEP(raw_contents))
	    result_1 = Syntax_tree_no_binding_tag;
	else {
	    maybe_nested_list = CAR(raw_contents);
	    if ( !TRUEP(maybe_nested_list)) {
		if (destructive_p) {
		    slot_value_pop_store = Nil;
		    cons_1 = CADDR(raw_binding);
		    if (cons_1) {
			slot_value_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qab_slot_value);
			if (ISVREF(Available_slot_value_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_slot_value_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_slot_value_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			else {
			    temp = Available_slot_value_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			    temp = Available_slot_value_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    M_CADDR(raw_binding) = next_cons;
		}
		result_1 = Syntax_tree_no_binding_tag;
	    }
	    else if (CONSP(maybe_nested_list)) {
		if (destructive_p) {
		    slot_value_pop_store = Nil;
		    cons_1 = CAADDR(raw_binding);
		    if (cons_1) {
			slot_value_pop_store = M_CAR(cons_1);
			next_cons = M_CDR(cons_1);
			inline_note_reclaim_cons(cons_1,Qab_slot_value);
			if (ISVREF(Available_slot_value_conses_tail_vector,
				IFIX(Current_thread_index))) {
			    temp = 
				    ISVREF(Available_slot_value_conses_tail_vector,
				    IFIX(Current_thread_index));
			    M_CDR(temp) = cons_1;
			    temp = Available_slot_value_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			else {
			    temp = Available_slot_value_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			    temp = Available_slot_value_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp,svref_arg_2) = cons_1;
			}
			M_CDR(cons_1) = Nil;
		    }
		    else
			next_cons = Nil;
		    M_CAADDR(raw_binding) = next_cons;
		    result_1 = slot_value_pop_store;
		}
		else
		    result_1 = CAR(maybe_nested_list);
	    }
	    else {
		correct_list_structure_p = Nil;
		result_1 = maybe_nested_list;
	    }
	}
    }
    else
	result_1 = Qnil;
    return VALUES_1(result_1);
}

/* LOOK-UP-NUMBER-OF-LISTED-BINDINGS */
Object look_up_number_of_listed_bindings(key,bindings)
    Object key, bindings;
{
    Object raw_binding, raw_contents, result_1;

    x_note_fn_call(251,85);
    raw_binding = look_up_raw_syntax_tree_binding(key,bindings);
    raw_contents = THIRD(raw_binding);
    result_1 = length(raw_contents);
    return VALUES_1(result_1);
}

static Object Qsimple;             /* simple */

static Object Qoptionals_list;     /* optionals-list */

static Object Qoptional;           /* optional */

static Object Qalternatives_list;  /* alternatives-list */

static Object Qoptional_alternative;  /* optional-alternative */

static Object Qlist_of_lists;      /* list-of-lists */

/* POP-LISTED-SYNTAX-TREE-BINDING-LAYER */
Object pop_listed_syntax_tree_binding_layer(key,bindings)
    Object key, bindings;
{
    Object raw_binding, gensymed_symbol, type, raw_contents;
    Object slot_value_pop_store, cons_1, next_cons, temp, svref_arg_2;
    Object demoted_contents, temp_1;

    x_note_fn_call(251,86);
    raw_binding = look_up_raw_syntax_tree_binding(key,bindings);
    gensymed_symbol = raw_binding;
    key = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    type = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    raw_contents = CAR(gensymed_symbol);
    if (CONSP(raw_contents)) {
	slot_value_pop_store = Nil;
	cons_1 = CADDR(raw_binding);
	if (cons_1) {
	    slot_value_pop_store = M_CAR(cons_1);
	    next_cons = M_CDR(cons_1);
	    inline_note_reclaim_cons(cons_1,Qab_slot_value);
	    if (ISVREF(Available_slot_value_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp = ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    else {
		temp = Available_slot_value_conses_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
		temp = Available_slot_value_conses_tail_vector;
		svref_arg_2 = Current_thread_index;
		SVREF(temp,svref_arg_2) = cons_1;
	    }
	    M_CDR(cons_1) = Nil;
	}
	else
	    next_cons = Nil;
	M_CADDR(raw_binding) = next_cons;
	demoted_contents = slot_value_pop_store;
    }
    else
	demoted_contents = Nil;
    if (EQ(type,Qlist))
	temp_1 = Qsimple;
    else if (EQ(type,Qoptionals_list))
	temp_1 = Qoptional;
    else if (EQ(type,Qalternatives_list))
	temp_1 = Qoptional_alternative;
    else if (EQ(type,Qlist_of_lists))
	temp_1 = Qlist;
    else
	temp_1 = Qnil;
    temp_1 = slot_value_list_4(key,temp_1,demoted_contents,
	    copy_tree_using_slot_value_conses_1(demoted_contents));
    return VALUES_1(temp_1);
}

/* LAST-LISTED-SYNTAX-TREE-BINDING-P */
Object last_listed_syntax_tree_binding_p(key,bindings,expected_list_structure)
    Object key, bindings, expected_list_structure;
{
    Object raw_binding, raw_contents, temp;

    x_note_fn_call(251,87);
    raw_binding = look_up_raw_syntax_tree_binding(key,bindings);
    raw_contents = THIRD(raw_binding);
    if (EQ(expected_list_structure,Qlist_expected))
	temp =  !TRUEP(CDR(raw_contents)) ? T : Nil;
    else if (EQ(expected_list_structure,Qlist_of_lists_expected))
	temp =  !TRUEP(CDAR(raw_contents)) ? T : Nil;
    else
	temp = Qnil;
    return VALUES_1(temp);
}

/* ENSURED-LOOK-UP-LISTED-SYNTAX-TREE-BINDING */
Object ensured_look_up_listed_syntax_tree_binding(key,bindings,
	    expected_list_structure,destructive_p)
    Object key, bindings, expected_list_structure, destructive_p;
{
    Object binding;

    x_note_fn_call(251,88);
    binding = look_up_listed_syntax_tree_binding(key,bindings,
	    expected_list_structure,destructive_p);
    return VALUES_1(EQ(binding,Syntax_tree_no_binding_tag) ? Nil : binding);
}

static Object list_constant_2;     /* # */

/* RETAIN-LISTED-BINDINGS */
Object retain_listed_bindings(bindings)
    Object bindings;
{
    Object key, type, ephemeral_binding, original_binding, ab_loop_list_;
    Object binding, ab_loop_list__1, ab_loop_desetq_, temp, cdr_arg;
    Object cdr_new_value;

    x_note_fn_call(251,89);
    key = Nil;
    type = Nil;
    ephemeral_binding = Nil;
    original_binding = Nil;
    ab_loop_list_ = bindings;
    binding = Nil;
    ab_loop_list__1 = bindings;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    key = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    ephemeral_binding = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    original_binding = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    binding = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (memq_function(type,list_constant_2)) {
	cdr_arg = last(binding,_);
	cdr_new_value = 
		slot_value_cons_1(copy_tree_using_slot_value_conses_1(ephemeral_binding),
		Nil);
	M_CDR(cdr_arg) = cdr_new_value;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

/* RESTORE-LISTED-BINDINGS */
Object restore_listed_bindings(bindings)
    Object bindings;
{
    Object key, type, exhausted_binding, original_binding, ab_loop_list_;
    Object binding, ab_loop_list__1, ab_loop_desetq_, temp, third_new_value;

    x_note_fn_call(251,90);
    key = Nil;
    type = Nil;
    exhausted_binding = Nil;
    original_binding = Nil;
    ab_loop_list_ = bindings;
    binding = Nil;
    ab_loop_list__1 = bindings;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    key = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    exhausted_binding = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    original_binding = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    binding = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (memq_function(type,list_constant_2)) {
	reclaim_slot_value_tree_1(exhausted_binding);
	third_new_value = 
		copy_tree_using_slot_value_conses_1(original_binding);
	M_THIRD(binding) = third_new_value;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Nil);
}

static Object Qatom_expected;      /* atom-expected */

/* TWRITE-SYNTAX-TREE-BINDING-IF-FOUND */
Object twrite_syntax_tree_binding_if_found(key,bindings,lookup_mode)
    Object key, bindings, lookup_mode;
{
    Object binding_qm, temp;

    x_note_fn_call(251,91);
    if (EQ(lookup_mode,Qatom_expected))
	binding_qm = look_up_atomic_syntax_tree_binding(key,bindings);
    else {
	binding_qm = look_up_atomic_syntax_tree_binding_if_any(key,bindings);
	if (binding_qm);
	else
	    binding_qm = ensured_look_up_listed_syntax_tree_binding(key,
		    bindings,lookup_mode,T);
    }
    if (binding_qm) {
	twrite_general_string(binding_qm);
	temp = T;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

static Object Qliteral;            /* literal */

static Object Qexpandable;         /* expandable */

static Object Qmidst_of_comma_series;  /* midst-of-comma-series */

static Object Qlast_of_comma_series;  /* last-of-comma-series */

static Object Qskip_line_unless_true;  /* skip-line-unless-true */

static Object Qsplice_out_unless_true;  /* splice-out-unless-true */

static Object Qsplicable_literal;  /* splicable-literal */

static Object Qreplicate_in_lines;  /* replicate-in-lines */

/* EXPAND-SYNTAX-TEMPLATE-LINE */
Object expand_syntax_template_line(tokens_in_line,bindings,
	    replicating_lines_p,indentation)
    Object tokens_in_line, bindings, replicating_lines_p, indentation;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, schar_arg_2, schar_new_value, token_cons_qm, token_type;
    Object key_or_literal, first_token_cons_in_comma_series_qm;
    Object splicable_literal_cons_qm, temp_1, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, i;
    SI_Long ab_loop_bind_;
    char thing;
    Declare_special(5);

    x_note_fn_call(251,92);
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
	      i = (SI_Long)1L;
	      ab_loop_bind_ = IFIX(indentation);
	    next_loop:
	      if (i > ab_loop_bind_)
		  goto end_loop;
	      if (EQ(Current_twriting_output_type,Qwide_string)) {
		  thing = ' ';
		  twrite_wide_character(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
	      }
	      else {
		  if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
			  Total_length_of_current_gensym_string))
		      extend_current_gensym_string(0);
		  temp = Current_gensym_string;
		  schar_arg_2 = Fill_pointer_for_current_gensym_string;
		  thing = ' ';
		  schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
			  CHAR_CODE(CHR(thing)) : CHR(thing));
		  SET_SCHAR(temp,schar_arg_2,schar_new_value);
		  temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
		  Fill_pointer_for_current_gensym_string = temp;
	      }
	      i = i + (SI_Long)1L;
	      goto next_loop;
	    end_loop:;
	      token_cons_qm = tokens_in_line;
	      token_type = Nil;
	      key_or_literal = Nil;
	      first_token_cons_in_comma_series_qm = Nil;
	      splicable_literal_cons_qm = Nil;
	    next_loop_1:
	      if ( !TRUEP(token_cons_qm))
		  goto end_loop_1;
	      if ( !TRUEP(token_cons_qm))
		  goto end_loop_1;
	      temp_1 = CAR(token_cons_qm);
	      token_type = CAR(temp_1);
	      temp_1 = CAR(token_cons_qm);
	      temp_1 = CDR(temp_1);
	      key_or_literal = CAR(temp_1);
	      if (EQ(token_type,Qliteral)) {
		  if ( !(first_token_cons_in_comma_series_qm || 
			  splicable_literal_cons_qm))
		      twrite_general_string(key_or_literal);
	      }
	      else if (EQ(token_type,Qexpandable))
		  twrite_general_string(symbol_name_text_string(key_or_literal));
	      else if (EQ(token_type,Qsubstitute))
		  twrite_syntax_tree_binding_if_found(key_or_literal,
			  bindings,replicating_lines_p ? Qlist_expected : 
			  Qatom_expected);
	      else if (EQ(token_type,Qmidst_of_comma_series)) {
		  if ( !TRUEP(first_token_cons_in_comma_series_qm))
		      first_token_cons_in_comma_series_qm = token_cons_qm;
	      }
	      else if (EQ(token_type,Qlast_of_comma_series)) {
		  expand_comma_series_in_syntax_template_line(bindings,
			  replicating_lines_p,
			  first_token_cons_in_comma_series_qm,token_cons_qm);
		  if ( !TRUEP(replicating_lines_p))
		      restore_listed_bindings(bindings);
		  first_token_cons_in_comma_series_qm = Nil;
	      }
	      else if (EQ(token_type,Qskip_line_unless_true))
		  twrite_syntax_tree_binding_if_found(key_or_literal,
			  bindings,replicating_lines_p ? Qlist_expected : 
			  Qatom_expected);
	      else if (EQ(token_type,Qoptional_alternative))
		  twrite_syntax_tree_binding_if_found(key_or_literal,
			  bindings,replicating_lines_p ? Qlist_expected : 
			  Qatom_expected);
	      else if (EQ(token_type,Qsplice_out_unless_true)) {
		  expand_splicable_syntax_template_line(key_or_literal,
			  bindings,replicating_lines_p,
			  splicable_literal_cons_qm,token_cons_qm);
		  splicable_literal_cons_qm = Nil;
	      }
	      else if (EQ(token_type,Qsplicable_literal))
		  splicable_literal_cons_qm = token_cons_qm;
	      else if (EQ(token_type,Qreplicate_in_lines));
	      token_cons_qm = M_CDR(token_cons_qm);
	      goto next_loop_1;
	    end_loop_1:
	      twrite_line_separator();
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(Global_output_stream_for_expand_syntax_template,text_string);
    reclaim_text_string(text_string);
    return VALUES_1(Nil);
}

static Object array_constant_1;    /* # */

/* EXPAND-COMMA-SERIES-IN-SYNTAX-TEMPLATE-LINE */
Object expand_comma_series_in_syntax_template_line(bindings,
	    replicating_lines_p,first_token_cons_in_comma_series_qm,
	    token_cons_qm)
    Object bindings, replicating_lines_p, first_token_cons_in_comma_series_qm;
    Object token_cons_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object initial_series_cons, first_token, key, expected_list_structure;
    Object typical_binding, last_series_p, series_cons, token_type;
    Object key_or_literal, temp, text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(251,93);
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
	      initial_series_cons = first_token_cons_in_comma_series_qm;
	      if (initial_series_cons);
	      else
		  initial_series_cons = token_cons_qm;
	      first_token = CAR(initial_series_cons);
	      key = SECOND(first_token);
	      expected_list_structure = replicating_lines_p ? 
		      Qlist_of_lists_expected : Qlist_expected;
	      typical_binding = Nil;
	      last_series_p = Nil;
	    next_loop:
	      typical_binding = look_up_listed_syntax_tree_binding(key,
		      bindings,expected_list_structure,Nil);
	      if (EQ(typical_binding,Syntax_tree_no_binding_tag))
		  goto end_loop;
	      last_series_p = last_listed_syntax_tree_binding_p(key,
		      bindings,expected_list_structure);
	      series_cons = initial_series_cons;
	      token_type = Nil;
	      key_or_literal = Nil;
	    next_loop_1:
	      if ( !TRUEP(series_cons))
		  goto end_loop_1;
	      temp = CAR(series_cons);
	      token_type = CAR(temp);
	      temp = CAR(series_cons);
	      temp = CDR(temp);
	      key_or_literal = CAR(temp);
	      if (EQ(token_type,Qlast_of_comma_series)) {
		  twrite_syntax_tree_binding_if_found(key_or_literal,
			  bindings,replicating_lines_p ? 
			  Qlist_of_lists_expected : Qlist_expected);
		  goto end_loop_1;
	      }
	      else if (EQ(token_type,Qmidst_of_comma_series))
		  twrite_syntax_tree_binding_if_found(key_or_literal,
			  bindings,replicating_lines_p ? 
			  Qlist_of_lists_expected : Qlist_expected);
	      else if (EQ(token_type,Qliteral))
		  twrite_general_string(key_or_literal);
	      series_cons = M_CDR(series_cons);
	      goto next_loop_1;
	    end_loop_1:;
	      if ( !TRUEP(last_series_p))
		  twrite_beginning_of_wide_string(array_constant_1,
			  FIX((SI_Long)2L));
	      goto next_loop;
	    end_loop:;
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(Global_output_stream_for_expand_syntax_template,text_string);
    reclaim_text_string(text_string);
    return VALUES_1(Nil);
}

/* EXPAND-SPLICABLE-SYNTAX-TEMPLATE-LINE */
Object expand_splicable_syntax_template_line(key,bindings,
	    replicating_lines_p,splicable_literal_cons_qm,token_cons_qm)
    Object key, bindings, replicating_lines_p, splicable_literal_cons_qm;
    Object token_cons_qm;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object binding_qm, not_spliced_cons, token_type, key_or_literal, temp;
    Object text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(251,94);
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
	      binding_qm = replicating_lines_p ? 
		      ensured_look_up_listed_syntax_tree_binding(key,
		      bindings,Qlist_expected,Nil) : 
		      look_up_atomic_syntax_tree_binding(key,bindings);
	      if (binding_qm) {
		  not_spliced_cons = splicable_literal_cons_qm;
		  if (not_spliced_cons);
		  else
		      not_spliced_cons = token_cons_qm;
		  token_type = Nil;
		  key_or_literal = Nil;
		next_loop:
		  if ( !TRUEP(not_spliced_cons))
		      goto end_loop;
		  temp = CAR(not_spliced_cons);
		  token_type = CAR(temp);
		  temp = CAR(not_spliced_cons);
		  temp = CDR(temp);
		  key_or_literal = CAR(temp);
		  if (EQ(token_type,Qsplice_out_unless_true)) {
		      twrite_syntax_tree_binding_if_found(key_or_literal,
			      bindings,replicating_lines_p ? 
			      Qlist_expected : Qatom_expected);
		      goto end_loop;
		  }
		  else if (EQ(token_type,Qsplicable_literal) || 
			  EQ(token_type,Qliteral))
		      twrite_general_string(key_or_literal);
		  not_spliced_cons = M_CDR(not_spliced_cons);
		  goto next_loop;
		end_loop:;
	      }
	      else if (replicating_lines_p)
		  ensured_look_up_listed_syntax_tree_binding(key,bindings,
			  Qlist_expected,T);
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    joutput_line(Global_output_stream_for_expand_syntax_template,text_string);
    reclaim_text_string(text_string);
    return VALUES_1(Nil);
}

/* LOOK-UP-TYPICAL-REPLICATED-BINDING-IF-ANY */
Object look_up_typical_replicated_binding_if_any varargs_1(int, n)
{
    Object tokens_in_line, bindings, line_number;
    Object look_outside_line_p, actual_list_structure, key, type;
    Object ab_loop_list_, ab_loop_it_, ab_loop_desetq_, temp, key_qm;
    Object token_type, token, ab_loop_list__1, gensymed_symbol;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(251,95);
    INIT_ARGS_nonrelocating();
    tokens_in_line = REQUIRED_ARG_nonrelocating();
    bindings = REQUIRED_ARG_nonrelocating();
    line_number = REQUIRED_ARG_nonrelocating();
    look_outside_line_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    actual_list_structure = Nil;
    if (look_outside_line_p) {
	key = Nil;
	type = Nil;
	ab_loop_list_ = bindings;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	key = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	type = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(type,Qlist) || EQ(type,Qlist_of_lists)) {
	    actual_list_structure = type;
	    temp_1 = TRUEP(actual_list_structure);
	}
	else
	    temp_1 = TRUEP(Nil);
	ab_loop_it_ = temp_1 ? key : Nil;
	if (ab_loop_it_) {
	    key_qm = ab_loop_it_;
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	key_qm = Qnil;
      end_1:;
    }
    else {
	token_type = Nil;
	key = Nil;
	ab_loop_list_ = tokens_in_line;
	token = Nil;
	ab_loop_list__1 = tokens_in_line;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	token_type = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	key = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	token = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	if (EQ(token_type,Qsubstitute)) {
	    gensymed_symbol = look_up_raw_syntax_tree_binding(key,bindings);
	    key_qm = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    type = CAR(gensymed_symbol);
	    if (key_qm && (EQ(type,Qlist) || EQ(type,Qlist_of_lists))) {
		actual_list_structure = type;
		temp_1 = TRUEP(actual_list_structure);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    ab_loop_it_ = temp_1 ? key_qm : Nil;
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    key_qm = ab_loop_it_;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	key_qm = Qnil;
      end_2:;
    }
    return VALUES_2(key_qm,actual_list_structure);
}

/* EXPAND-REPLICATED-SYNTAX-SUBTREE */
Object expand_replicated_syntax_subtree(subtree_to_insert,tokens_in_line,
	    bindings,line_number,indentation)
    Object subtree_to_insert, tokens_in_line, bindings, line_number;
    Object indentation;
{
    Object multi_line_p, listed_binding_qm, actual_list_structure;
    Object expected_list_structure, ignore, key, type, value, ab_loop_list_;
    Object binding, ab_loop_list__1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp, bindings_for_one_iteration;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string;
    SI_Long i, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(251,96);
    multi_line_p = multi_line_syntax_template_p(subtree_to_insert);
    result = look_up_typical_replicated_binding_if_any(4,tokens_in_line,
	    bindings,line_number,T);
    MVS_2(result,listed_binding_qm,actual_list_structure);
    if (listed_binding_qm) {
	if (EQ(actual_list_structure,Qlist))
	    expected_list_structure = Qlist_expected;
	else if (EQ(actual_list_structure,Qlist_of_lists))
	    expected_list_structure = Qlist_of_lists_expected;
	else
	    expected_list_structure = Qnil;
	i = (SI_Long)1L;
	ab_loop_bind_ = 
		IFIX(look_up_number_of_listed_bindings(listed_binding_qm,
		bindings));
	ignore = Nil;
      next_loop:
	if (i > ab_loop_bind_)
	    goto end_loop;
	ignore = look_up_listed_syntax_tree_binding(listed_binding_qm,
		bindings,expected_list_structure,Nil);
	if (EQ(ignore,Syntax_tree_no_binding_tag))
	    goto end_loop;
	key = Nil;
	type = Nil;
	value = Nil;
	ab_loop_list_ = bindings;
	binding = Nil;
	ab_loop_list__1 = bindings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	key = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	type = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	value = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	binding = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	ab_loopvar__2 = slot_value_cons_1(EQ(type,Qlist) || EQ(type,
		Qlist_of_lists) || EQ(type,Qoptionals_list) || EQ(type,
		Qalternatives_list) ? 
		pop_listed_syntax_tree_binding_layer(key,bindings) : 
		copy_list_using_slot_value_conses_1(binding),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	bindings_for_one_iteration = ab_loopvar_;
	goto end_1;
	bindings_for_one_iteration = Qnil;
      end_1:;
	expand_syntax_template_within_output_to_java_source_file(subtree_to_insert,
		bindings_for_one_iteration,multi_line_p ? 
		FIX(IFIX(indentation) + (SI_Long)2L) : indentation);
	if (multi_line_p) {
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
		      text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    joutput_line(Global_output_stream_for_expand_syntax_template,
		    text_string);
	    reclaim_text_string(text_string);
	}
	reclaim_slot_value_tree_1(bindings_for_one_iteration);
	i = i + (SI_Long)1L;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

static Object QLT_I_GT;            /* |<i>| */

static Object string_constant_7;   /* "" */

static Object Qgensym_string;      /* gensym-string */

/* EXPAND-OPTIONAL-SYNTAX-TREE-LINES */
Object expand_optional_syntax_tree_lines(controlling_key,
	    cons_holding_this_line,tokens_in_line,bindings,line_number,
	    indentation,replicate_lines_p,needs_index_binding_p)
    Object controlling_key, cons_holding_this_line, tokens_in_line, bindings;
    Object line_number, indentation, replicate_lines_p, needs_index_binding_p;
{
    Object index_1, index_binding_qm, listed_binding_qm, actual_list_structure;
    Object expected_list_structure, binding_qm, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp, next_line, slot_value_pop_store, cons_1, next_cons;
    Object svref_arg_2;
    SI_Long i, ab_loop_bind_;
    Declare_special(4);
    Object result;

    x_note_fn_call(251,97);
    if (replicate_lines_p) {
	index_1 = FIX((SI_Long)0L);
	index_binding_qm = needs_index_binding_p ? 
		slot_value_list_3(QLT_I_GT,Qsimple,
		copy_gensym_string(string_constant_7)) : Qnil;
	if (index_binding_qm)
	    bindings = slot_value_cons_1(index_binding_qm,bindings);
	result = look_up_typical_replicated_binding_if_any(4,
		tokens_in_line,bindings,line_number,Nil);
	MVS_2(result,listed_binding_qm,actual_list_structure);
	if (listed_binding_qm) {
	    if (EQ(actual_list_structure,Qlist))
		expected_list_structure = Qlist_expected;
	    else if (EQ(actual_list_structure,Qlist_of_lists))
		expected_list_structure = Qlist_of_lists_expected;
	    else
		expected_list_structure = Qnil;
	    i = (SI_Long)1L;
	    ab_loop_bind_ = 
		    IFIX(look_up_number_of_listed_bindings(listed_binding_qm,
		    bindings));
	    binding_qm = Nil;
	  next_loop:
	    if (i > ab_loop_bind_)
		goto end_loop;
	    binding_qm = 
		    look_up_listed_syntax_tree_binding(listed_binding_qm,
		    bindings,expected_list_structure,Nil);
	    if (EQ(binding_qm,Syntax_tree_no_binding_tag))
		goto end_loop;
	    if (index_binding_qm) {
		reclaim_gensym_string(THIRD(index_binding_qm));
		current_gensym_string = 
			obtain_simple_gensym_string(FIX((SI_Long)2048L));
		PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
			3);
		  fill_pointer_for_current_gensym_string = FIX((SI_Long)0L);
		  PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
			  2);
		    total_length_of_current_gensym_string = 
			    FIX((SI_Long)2048L);
		    PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
			    1);
		      current_twriting_output_type = Qgensym_string;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
			      0);
			twrite_fixnum(index_1);
			temp = copy_out_current_gensym_string();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		M_THIRD(index_binding_qm) = temp;
		index_1 = FIXNUM_ADD1(index_1);
	    }
	    if (binding_qm)
		expand_syntax_template_line(tokens_in_line,bindings,T,
			indentation);
	    else {
		next_line = CADR(cons_holding_this_line);
		if (FOURTH(next_line))
		    expand_syntax_template_line(nthcdr(FIX((SI_Long)7L),
			    next_line),bindings,T,indentation);
	    }
	    i = i + (SI_Long)1L;
	    goto next_loop;
	  end_loop:;
	}
	if (index_binding_qm) {
	    slot_value_pop_store = Nil;
	    cons_1 = bindings;
	    if (cons_1) {
		slot_value_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp = ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp) = cons_1;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		else {
		    temp = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		    temp = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    bindings = next_cons;
	    reclaim_slot_value(index_binding_qm);
	}
    }
    else {
	binding_qm = look_up_atomic_syntax_tree_binding(controlling_key,
		bindings);
	if (binding_qm)
	    expand_syntax_template_line(tokens_in_line,bindings,Nil,
		    indentation);
	else {
	    next_line = CADR(cons_holding_this_line);
	    if (FOURTH(next_line))
		expand_syntax_template_line(nthcdr(FIX((SI_Long)7L),
			next_line),bindings,Nil,indentation);
	}
    }
    return VALUES_1(Nil);
}

/* EXPAND-SYNTAX-TEMPLATE-WITHIN-OUTPUT-TO-JAVA-SOURCE-FILE */
Object expand_syntax_template_within_output_to_java_source_file(template_name,
	    bindings,indentation)
    Object template_name, bindings, indentation;
{
    Object registry_entry_qm, tokenized_template, subtree_to_insert_qm;
    Object skip_line_unless_true_qm, optional_alternative_line_p;
    Object replicate_lines_p, needs_index_binding_p, entirely_whitespace_p;
    Object tokens_in_line, ab_loop_list_, cons_holding_this_line;
    Object suppress_next_whitespace_line_p, ab_loop_iter_flag_;
    Object ab_loop_desetq_, temp, temp_1, index_1, index_binding_qm;
    Object listed_binding_qm, actual_list_structure, expected_list_structure;
    Object ignore, current_gensym_string;
    Object fill_pointer_for_current_gensym_string;
    Object total_length_of_current_gensym_string, current_twriting_output_type;
    Object temp_2, slot_value_pop_store, cons_1, next_cons, svref_arg_2;
    SI_Long line_number, i, ab_loop_bind_;
    Declare_special(4);
    Object result;

    x_note_fn_call(251,98);
    registry_entry_qm = assq_function(template_name,
	    Syntax_tree_template_registry);
    if (registry_entry_qm) {
	tokenized_template = SIXTH(registry_entry_qm);
	subtree_to_insert_qm = Nil;
	skip_line_unless_true_qm = Nil;
	optional_alternative_line_p = Nil;
	replicate_lines_p = Nil;
	needs_index_binding_p = Nil;
	entirely_whitespace_p = Nil;
	tokens_in_line = Nil;
	ab_loop_list_ = tokenized_template;
	cons_holding_this_line = tokenized_template;
	line_number = (SI_Long)1L;
	suppress_next_whitespace_line_p = Nil;
	ab_loop_iter_flag_ = T;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	temp = CDR(ab_loop_desetq_);
	temp = CAR(temp);
	temp = CDR(temp);
	subtree_to_insert_qm = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CAR(temp);
	temp = CDR(temp);
	skip_line_unless_true_qm = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	optional_alternative_line_p = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	replicate_lines_p = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	needs_index_binding_p = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	entirely_whitespace_p = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	tokens_in_line = CDR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_iter_flag_))
	    cons_holding_this_line = M_CDR(cons_holding_this_line);
	if ( !TRUEP(cons_holding_this_line))
	    goto end_loop;
	if ( !TRUEP(ab_loop_iter_flag_))
	    line_number = line_number + (SI_Long)1L;
	if (replicate_lines_p && subtree_to_insert_qm) {
	    expand_replicated_syntax_subtree(subtree_to_insert_qm,
		    tokens_in_line,bindings,FIX(line_number),indentation);
	    restore_listed_bindings(bindings);
	}
	else if (subtree_to_insert_qm) {
	    temp = subtree_to_insert_qm;
	    temp_1 = bindings;
	    expand_syntax_template_within_output_to_java_source_file(temp,
		    temp_1,
		    multi_line_syntax_template_p(subtree_to_insert_qm) ? 
		    FIX(IFIX(indentation) + (SI_Long)2L) : indentation);
	}
	else if (skip_line_unless_true_qm)
	    expand_optional_syntax_tree_lines(skip_line_unless_true_qm,
		    cons_holding_this_line,tokens_in_line,bindings,
		    FIX(line_number),indentation,replicate_lines_p,
		    needs_index_binding_p);
	else if (optional_alternative_line_p);
	else if (replicate_lines_p) {
	    suppress_next_whitespace_line_p = T;
	    index_1 = FIX((SI_Long)0L);
	    index_binding_qm = needs_index_binding_p ? 
		    slot_value_list_3(QLT_I_GT,Qsimple,
		    copy_gensym_string(string_constant_7)) : Qnil;
	    if (index_binding_qm)
		bindings = slot_value_cons_1(index_binding_qm,bindings);
	    result = look_up_typical_replicated_binding_if_any(4,
		    tokens_in_line,bindings,FIX(line_number),Nil);
	    MVS_2(result,listed_binding_qm,actual_list_structure);
	    if (listed_binding_qm) {
		if (EQ(actual_list_structure,Qlist))
		    expected_list_structure = Qlist_expected;
		else if (EQ(actual_list_structure,Qlist_of_lists))
		    expected_list_structure = Qlist_of_lists_expected;
		else
		    expected_list_structure = Qnil;
		i = (SI_Long)1L;
		ab_loop_bind_ = 
			IFIX(look_up_number_of_listed_bindings(listed_binding_qm,
			bindings));
		ignore = Nil;
	      next_loop_1:
		if (i > ab_loop_bind_)
		    goto end_loop_1;
		ignore = 
			look_up_listed_syntax_tree_binding(listed_binding_qm,
			bindings,expected_list_structure,Nil);
		if (EQ(ignore,Syntax_tree_no_binding_tag))
		    goto end_loop_1;
		suppress_next_whitespace_line_p = Nil;
		if (index_binding_qm) {
		    reclaim_gensym_string(THIRD(index_binding_qm));
		    current_gensym_string = 
			    obtain_simple_gensym_string(FIX((SI_Long)2048L));
		    PUSH_SPECIAL_WITH_SYMBOL(Current_gensym_string,Qcurrent_gensym_string,current_gensym_string,
			    3);
		      fill_pointer_for_current_gensym_string = 
			      FIX((SI_Long)0L);
		      PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_gensym_string,Qfill_pointer_for_current_gensym_string,fill_pointer_for_current_gensym_string,
			      2);
			total_length_of_current_gensym_string = 
				FIX((SI_Long)2048L);
			PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_gensym_string,Qtotal_length_of_current_gensym_string,total_length_of_current_gensym_string,
				1);
			  current_twriting_output_type = Qgensym_string;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				  0);
			    twrite_fixnum(index_1);
			    temp_2 = copy_out_current_gensym_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    M_THIRD(index_binding_qm) = temp_2;
		    index_1 = FIXNUM_ADD1(index_1);
		}
		expand_syntax_template_line(tokens_in_line,bindings,T,
			indentation);
		i = i + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    if (index_binding_qm) {
		slot_value_pop_store = Nil;
		cons_1 = bindings;
		if (cons_1) {
		    slot_value_pop_store = M_CAR(cons_1);
		    next_cons = M_CDR(cons_1);
		    inline_note_reclaim_cons(cons_1,Qab_slot_value);
		    if (ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index))) {
			temp_2 = 
				ISVREF(Available_slot_value_conses_tail_vector,
				IFIX(Current_thread_index));
			M_CDR(temp_2) = cons_1;
			temp_2 = Available_slot_value_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
		    }
		    else {
			temp_2 = Available_slot_value_conses_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
			temp_2 = Available_slot_value_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = cons_1;
		    }
		    M_CDR(cons_1) = Nil;
		}
		else
		    next_cons = Nil;
		bindings = next_cons;
		reclaim_slot_value(index_binding_qm);
	    }
	    restore_listed_bindings(bindings);
	}
	else {
	    if ( !(entirely_whitespace_p && suppress_next_whitespace_line_p))
		expand_syntax_template_line(tokens_in_line,bindings,Nil,
			indentation);
	    if (suppress_next_whitespace_line_p)
		suppress_next_whitespace_line_p = Nil;
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

/* MULTI-LINE-SYNTAX-TEMPLATE-P */
Object multi_line_syntax_template_p(template_name)
    Object template_name;
{
    Object registry_entry_qm, tokenized_template, temp;

    x_note_fn_call(251,99);
    registry_entry_qm = assq_function(template_name,
	    Syntax_tree_template_registry);
    if (registry_entry_qm) {
	tokenized_template = SIXTH(registry_entry_qm);
	temp = nthcdr(FIX((SI_Long)7L),tokenized_template);
	temp = CDR(temp) ? T : Nil;
    }
    else
	temp = Nil;
    return VALUES_1(temp);
}

void java3_INIT()
{
    Object temp, reclaim_structure_for_external_class_info_1;
    Object reclaim_structure_for_external_method_info_1, gensymed_symbol;
    Object write_unexportable_external_method_note_1;
    Object write_problem_mapping_g2_to_java_source_note_1;
    Object AB_package, list_constant_3, list_constant_151, Qno_binding;
    Object list_constant_150, Qjava_exported_exception, list_constant_149;
    Object list_constant_148, Qjava_class_declaration, list_constant_147;
    Object list_constant_146, list_constant_145, list_constant_7;
    Object list_constant_144, list_constant_40, Qtemplate_line;
    Object string_constant_64, QException, QLT_EXCEPTION_GT, Qlt_exception_gt;
    Object list_constant_143, Qjava_exported_method_implementation;
    Object list_constant_142, list_constant_35, list_constant_141;
    Object list_constant_140, Qjava_method_declaration, list_constant_82;
    Object list_constant_139, list_constant_80, list_constant_130;
    Object list_constant_138, list_constant_137, list_constant_136;
    Object list_constant_135, list_constant_134, list_constant_133;
    Object list_constant_132, list_constant_30, list_constant_131;
    Object list_constant_129, list_constant_128, list_constant_127;
    Object list_constant_126, list_constant_125, list_constant_102;
    Object list_constant_124, list_constant_107, list_constant_18;
    Object list_constant_123, QLT_CONVERTED_RESULT_GT, string_constant_63;
    Object list_constant_122, list_constant_92, list_constant_97;
    Object string_constant_62, list_constant_121, list_constant_120;
    Object list_constant_14, list_constant_119, list_constant_118;
    Object list_constant_63, QE, QG2AccessException, string_constant_61;
    Object list_constant_117, list_constant_57, list_constant_116;
    Object list_constant_47, list_constant_115, list_constant_16;
    Object string_constant_60, string_constant_59, list_constant_90;
    Object list_constant_111, list_constant_114, string_constant_58;
    Object list_constant_112, list_constant_64, list_constant_113;
    Object string_constant_57, list_constant_17, QRESULT;
    Object QLT_RPC_RESULT_TYPE_GT, list_constant_110, list_constant_109;
    Object list_constant_12, list_constant_108, list_constant_106;
    Object list_constant_105, list_constant_104, list_constant_59;
    Object list_constant_51, list_constant_50, list_constant_103;
    Object QLT_ARG_NAME_GT, QconvertJavatoG2, string_constant_56;
    Object QLT_RPC_ARG_TYPE_GT, string_constant_55, list_constant_101;
    Object list_constant_100, list_constant_66, QOBT_TL_THROWS_CBT;
    Object string_constant_54, list_constant_99, list_constant_11;
    Object list_constant_98, string_constant_53, string_constant_52;
    Object string_constant_51, list_constant_96, list_constant_53;
    Object list_constant_95, string_constant_50, string_constant_49;
    Object list_constant_94, string_constant_48, list_constant_93;
    Object string_constant_47, list_constant_91, QOBT_THROWS_CBT;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object list_constant_89, list_constant_22, string_constant_46;
    Object list_constant_88, QCOM_dot_gensym_dot_jgi_dot_G2AccessException;
    Object Qlt_converted_result_gt, Qlt_method_symbol_gt;
    Object Qlt_rpc_result_type_gt, Qlt_rpc_arg_type_gt_dot_dot_dot;
    Object Qlt_init_name_gt, Qobt_tl_throws_cbt, Qobt_throws_cbt;
    Object Qlt_arg_name_gt_dot_dot_dot, Qlt_arg_type_gt_dot_dot_dot;
    Object Qlt_method_gt, Qlt_result_type_gt, list_constant_87;
    Object Qjava_exported_class_implementation, list_constant_86;
    Object list_constant_85, list_constant_84, list_constant_83;
    Object list_constant_81, list_constant_79, list_constant_78;
    Object list_constant_77, list_constant_76, list_constant_75;
    Object list_constant_74, list_constant_73, list_constant_32;
    Object list_constant_72, Qinsert_subtree, list_constant_71;
    Object string_constant_45, list_constant_70, list_constant_69;
    Object list_constant_68, list_constant_67, string_constant_44, QNULL;
    Object string_constant_43, string_constant_42, list_constant_15;
    Object list_constant_65, string_constant_41, string_constant_40;
    Object string_constant_39, list_constant_13, list_constant_62;
    Object string_constant_38, string_constant_37, list_constant_61;
    Object list_constant_60, list_constant_55, list_constant_58;
    Object list_constant_56, list_constant_52, string_constant_36;
    Object QLT_MAX_ARG_COUNT_GT, string_constant_35, string_constant_34;
    Object QmyArgArray, string_constant_33, QObject, list_constant_54;
    Object string_constant_32, QmyConnection, string_constant_31;
    Object list_constant_49, list_constant_48, list_constant_46;
    Object list_constant_45, list_constant_26, string_constant_30;
    Object QLT_METHOD_STRING_GT, string_constant_29, QLT_METHOD_SYMBOL_GT;
    Object QSymbol, string_constant_28, list_constant_44, list_constant_6;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_9, string_constant_27, QG2RMIready, QLT_CLASS_GT;
    Object string_constant_26, string_constant_25, list_constant_39;
    Object list_constant_4, list_constant_38;
    Object QCOM_dot_gensym_dot_jgi_dot_G2RMIready;
    Object QCOM_dot_gensym_dot_util_dot_Symbol, Qlt_max_arg_count_gt;
    Object Qlt_method_string_gt_dot_dot_dot, Qlt_method_symbol_gt_dot_dot_dot;
    Object Qlt_interface_gt, Qlt_class_gt, list_constant_37;
    Object Qjava_exported_class_interface, list_constant_36, list_constant_34;
    Object list_constant_33, Qjava_interface_declaration, list_constant_31;
    Object list_constant_29, list_constant_28, list_constant_27;
    Object string_constant_24, list_constant_25, list_constant_24;
    Object list_constant_23, string_constant_23, string_constant_22;
    Object string_constant_21, QLT_ARG_TYPE_GT, QLT_METHOD_GT;
    Object QLT_RESULT_TYPE_GT, string_constant_20, list_constant_10;
    Object string_constant_19, QCONNECTION, string_constant_18, QG2Connection;
    Object string_constant_17, QLT_INIT_NAME_GT, string_constant_16;
    Object list_constant_8, list_constant_5, string_constant_15, QRemote;
    Object string_constant_14, QLT_INTERFACE_GT, string_constant_13;
    Object string_constant_12, QCOM_dot_gensym_dot_jgi_dot_G2Connection;
    Object Qobt_throws_cbt_dot_dot_dot;
    Object Qlt_lt_arg_name_gt_dot_dot_dot_gt_dot_dot_dot;
    Object Qlt_lt_arg_type_gt_dot_dot_dot_gt_dot_dot_dot;
    Object Qlt_method_gt_dot_dot_dot, Qlt_result_type_gt_dot_dot_dot;
    Object Qframe_note_writer_1, Qtruth_value;
    Object Qg2_add_class_export_info_attributes;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object Qg2_switch_fix_for_exported_method_overloading;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qexternal_method_info;
    Object Qreclaim_structure, Qoutstanding_external_method_info_count;
    Object Qexternal_method_info_structure_memory_usage, Qutilities2;
    Object string_constant_11, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object string_constant_10, Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qexternal_class_info;
    Object Qoutstanding_external_class_info_count;
    Object Qexternal_class_info_structure_memory_usage, string_constant_9;
    Object string_constant_8;

    x_note_fn_call(251,100);
    SET_PACKAGE("AB");
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_external_class_info_g2_struct = 
	    STATIC_SYMBOL("EXTERNAL-CLASS-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    AB_package = STATIC_PACKAGE("AB");
    Qexternal_class_info = STATIC_SYMBOL("EXTERNAL-CLASS-INFO",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_class_info_g2_struct,
	    Qexternal_class_info,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qexternal_class_info,
	    Qg2_defstruct_structure_name_external_class_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_external_class_info == UNBOUND)
	The_type_description_of_external_class_info = Nil;
    string_constant_8 = 
	    STATIC_STRING("43Dy8m83hBy1n83hBy8n8k1l8n0000001l1n8y83-3by1n83w2y83w9y83w4ykok0k0");
    temp = The_type_description_of_external_class_info;
    The_type_description_of_external_class_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_8));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_class_info_g2_struct,
	    The_type_description_of_external_class_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qexternal_class_info,
	    The_type_description_of_external_class_info,
	    Qtype_description_of_type);
    Qoutstanding_external_class_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-EXTERNAL-CLASS-INFO-COUNT",AB_package);
    Qexternal_class_info_structure_memory_usage = 
	    STATIC_SYMBOL("EXTERNAL-CLASS-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_9 = STATIC_STRING("1q83hBy8s83-TVy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_external_class_info_count);
    push_optimized_constant(Qexternal_class_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_9));
    Qchain_of_available_external_class_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EXTERNAL-CLASS-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_external_class_infos,
	    Chain_of_available_external_class_infos);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_external_class_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qexternal_class_info_count = STATIC_SYMBOL("EXTERNAL-CLASS-INFO-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexternal_class_info_count,
	    External_class_info_count);
    record_system_variable(Qexternal_class_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_external_class_infos_vector == UNBOUND)
	Chain_of_available_external_class_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qexternal_class_info_structure_memory_usage,
	    STATIC_FUNCTION(external_class_info_structure_memory_usage,NIL,
	    FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_external_class_info_count,
	    STATIC_FUNCTION(outstanding_external_class_info_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_external_class_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_external_class_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qexternal_class_info,
	    reclaim_structure_for_external_class_info_1);
    Qg2_defstruct_structure_name_external_method_info_g2_struct = 
	    STATIC_SYMBOL("EXTERNAL-METHOD-INFO-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qexternal_method_info = STATIC_SYMBOL("EXTERNAL-METHOD-INFO",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_external_method_info_g2_struct,
	    Qexternal_method_info,Qab_name_of_unique_structure_type);
    mutate_global_property(Qexternal_method_info,
	    Qg2_defstruct_structure_name_external_method_info_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_external_method_info == UNBOUND)
	The_type_description_of_external_method_info = Nil;
    string_constant_10 = 
	    STATIC_STRING("43Dy8m83hCy1n83hCy8n8k1l8n0000001l1n8y83-3cy1q83rNy83rOy83w6y83-=dy83-=ey83w5ykvk0k0");
    temp = The_type_description_of_external_method_info;
    The_type_description_of_external_method_info = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_10));
    mutate_global_property(Qg2_defstruct_structure_name_external_method_info_g2_struct,
	    The_type_description_of_external_method_info,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qexternal_method_info,
	    The_type_description_of_external_method_info,
	    Qtype_description_of_type);
    Qoutstanding_external_method_info_count = 
	    STATIC_SYMBOL("OUTSTANDING-EXTERNAL-METHOD-INFO-COUNT",AB_package);
    Qexternal_method_info_structure_memory_usage = 
	    STATIC_SYMBOL("EXTERNAL-METHOD-INFO-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_11 = STATIC_STRING("1q83hCy8s83-TXy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_external_method_info_count);
    push_optimized_constant(Qexternal_method_info_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_11));
    Qchain_of_available_external_method_infos = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-EXTERNAL-METHOD-INFOS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_external_method_infos,
	    Chain_of_available_external_method_infos);
    record_system_variable(Qchain_of_available_external_method_infos,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qexternal_method_info_count = 
	    STATIC_SYMBOL("EXTERNAL-METHOD-INFO-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qexternal_method_info_count,
	    External_method_info_count);
    record_system_variable(Qexternal_method_info_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_external_method_infos_vector == UNBOUND)
	Chain_of_available_external_method_infos_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qexternal_method_info_structure_memory_usage,
	    STATIC_FUNCTION(external_method_info_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_external_method_info_count,
	    STATIC_FUNCTION(outstanding_external_method_info_count,NIL,
	    FALSE,0,0));
    reclaim_structure_for_external_method_info_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_external_method_info,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qexternal_method_info,
	    reclaim_structure_for_external_method_info_1);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("~A::~A");
    string_constant_1 = STATIC_STRING("KEYWORD");
    Qsignal_statement_new = STATIC_SYMBOL("SIGNAL-STATEMENT-NEW",AB_package);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    Qprocedure_definition = STATIC_SYMBOL("PROCEDURE-DEFINITION",AB_package);
    Qexport_definition_specification = 
	    STATIC_SYMBOL("EXPORT-DEFINITION-SPECIFICATION",AB_package);
    Qjava = STATIC_SYMBOL("JAVA",AB_package);
    Qinterface = STATIC_SYMBOL("INTERFACE",AB_package);
    Qcode = STATIC_SYMBOL("CODE",AB_package);
    list_constant = STATIC_LIST((SI_Long)3L,Qinterface,Qcode,Qnil);
    Qstatic_methods = STATIC_SYMBOL("STATIC-METHODS",AB_package);
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    Qexternal_method_declaration = 
	    STATIC_SYMBOL("EXTERNAL-METHOD-DECLARATION",AB_package);
    Qexternal_procedure = STATIC_SYMBOL("EXTERNAL-PROCEDURE",AB_package);
    Qexternal_method = STATIC_SYMBOL("EXTERNAL-METHOD",AB_package);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qincluded_instance_methods = STATIC_SYMBOL("INCLUDED-INSTANCE-METHODS",
	    AB_package);
    Qexcluded_instance_methods = STATIC_SYMBOL("EXCLUDED-INSTANCE-METHODS",
	    AB_package);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    if (Bypass_fix_for_exported_method_overloading_p == UNBOUND)
	Bypass_fix_for_exported_method_overloading_p = Nil;
    Qg2_switch_fix_for_exported_method_overloading = 
	    STATIC_SYMBOL("G2-SWITCH-FIX-FOR-EXPORTED-METHOD-OVERLOADING",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_switch_fix_for_exported_method_overloading,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_switch_fix_for_exported_method_overloading,
	    STATIC_FUNCTION(g2_switch_fix_for_exported_method_overloading,
	    NIL,FALSE,1,1));
    Qexport_definition = STATIC_SYMBOL("EXPORT-DEFINITION",AB_package);
    Qvisible_class_export_information_qm = 
	    STATIC_SYMBOL("VISIBLE-CLASS-EXPORT-INFORMATION\?",AB_package);
    Qinstallation = STATIC_SYMBOL("INSTALLATION",AB_package);
    Qunexportable_external_method = 
	    STATIC_SYMBOL("UNEXPORTABLE-EXTERNAL-METHOD",AB_package);
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    Qexternal_procedure_definition = 
	    STATIC_SYMBOL("EXTERNAL-PROCEDURE-DEFINITION",AB_package);
    string_constant_2 = 
	    STATIC_STRING("there is no method-declaration named ~A");
    Qduplicate_class_export = STATIC_SYMBOL("DUPLICATE-CLASS-EXPORT",
	    AB_package);
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    Qnonexistent_classes_for_export = 
	    STATIC_SYMBOL("NONEXISTENT-CLASSES-FOR-EXPORT",AB_package);
    Qnonexistent_static_methods_for_export = 
	    STATIC_SYMBOL("NONEXISTENT-STATIC-METHODS-FOR-EXPORT",AB_package);
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    string_constant_3 = STATIC_STRING("(~A) ");
    string_constant_4 = STATIC_STRING("method ~A could not be exported: ~A;");
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)59L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    write_unexportable_external_method_note_1 = 
	    STATIC_FUNCTION(write_unexportable_external_method_note,NIL,
	    FALSE,2,2);
    mutate_global_property(Qunexportable_external_method,
	    write_unexportable_external_method_note_1,Qframe_note_writer_1);
    if (Bypass_add_class_export_info_attributes_p == UNBOUND)
	Bypass_add_class_export_info_attributes_p = Nil;
    Qg2_add_class_export_info_attributes = 
	    STATIC_SYMBOL("G2-ADD-CLASS-EXPORT-INFO-ATTRIBUTES",AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_add_class_export_info_attributes,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_add_class_export_info_attributes,
	    STATIC_FUNCTION(g2_add_class_export_info_attributes,NIL,FALSE,
	    1,1));
    Qinstance_methods = STATIC_SYMBOL("INSTANCE-METHODS",AB_package);
    Qexported_source = STATIC_SYMBOL("EXPORTED-SOURCE",AB_package);
    Qhand_coded_methods = STATIC_SYMBOL("HAND-CODED-METHODS",AB_package);
    Qinclude_method_text_in_class_export = 
	    STATIC_SYMBOL("INCLUDE-METHOD-TEXT-IN-CLASS-EXPORT",AB_package);
    Qmethod_name = STATIC_SYMBOL("METHOD-NAME",AB_package);
    Qis_static = STATIC_SYMBOL("IS-STATIC",AB_package);
    Qargument_types = STATIC_SYMBOL("ARGUMENT-TYPES",AB_package);
    Qresult_types = STATIC_SYMBOL("RESULT-TYPES",AB_package);
    Qg2_method_text = STATIC_SYMBOL("G2-METHOD-TEXT",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qmethod_source = STATIC_SYMBOL("METHOD-SOURCE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)5L,Qtruth_value,Qinteger,Qfloat,
	    Qsymbol,Qtext);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    Qvalue = STATIC_SYMBOL("VALUE",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    Qimports = STATIC_SYMBOL("IMPORTS",AB_package);
    Qsuperior_class_override = STATIC_SYMBOL("SUPERIOR-CLASS-OVERRIDE",
	    AB_package);
    Qjwith_output_to_text_string = 
	    STATIC_SYMBOL("JWITH-OUTPUT-TO-TEXT-STRING",AB_package);
    Kjemit_error = STATIC_SYMBOL("JEMIT-ERROR",Pkeyword);
    Qproblem_mapping_g2_to_java_source = 
	    STATIC_SYMBOL("PROBLEM-MAPPING-G2-TO-JAVA-SOURCE",AB_package);
    string_constant_5 = 
	    STATIC_STRING("a problem was encountered mapping the G2 class ~A to Java: ~A");
    write_problem_mapping_g2_to_java_source_note_1 = 
	    STATIC_FUNCTION(write_problem_mapping_g2_to_java_source_note,
	    NIL,FALSE,2,2);
    mutate_global_property(Qproblem_mapping_g2_to_java_source,
	    write_problem_mapping_g2_to_java_source_note_1,
	    Qframe_note_writer_1);
    Qadditional_java_methods = STATIC_SYMBOL("ADDITIONAL-JAVA-METHODS",
	    AB_package);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Cache_implicit_class_export_info_p = Nil;
    Syntax_tree_template_registry = Nil;
    Qjava_exported_class_interface = 
	    STATIC_SYMBOL("JAVA-EXPORTED-CLASS-INTERFACE",AB_package);
    Qjava_interface_declaration = 
	    STATIC_SYMBOL("JAVA-INTERFACE-DECLARATION",AB_package);
    Qlt_interface_gt = STATIC_SYMBOL("<INTERFACE>",AB_package);
    Qlt_result_type_gt_dot_dot_dot = STATIC_SYMBOL("<RESULT-TYPE>...",
	    AB_package);
    Qlt_init_name_gt = STATIC_SYMBOL("<INIT-NAME>",AB_package);
    Qlt_method_gt_dot_dot_dot = STATIC_SYMBOL("<METHOD>...",AB_package);
    Qlt_lt_arg_type_gt_dot_dot_dot_gt_dot_dot_dot = 
	    STATIC_SYMBOL("<<ARG-TYPE>...>...",AB_package);
    Qlt_lt_arg_name_gt_dot_dot_dot_gt_dot_dot_dot = 
	    STATIC_SYMBOL("<<ARG-NAME>...>...",AB_package);
    Qobt_throws_cbt_dot_dot_dot = STATIC_SYMBOL("[THROWS]...",AB_package);
    list_constant_33 = STATIC_LIST((SI_Long)7L,Qlt_interface_gt,
	    Qlt_result_type_gt_dot_dot_dot,Qlt_init_name_gt,
	    Qlt_method_gt_dot_dot_dot,
	    Qlt_lt_arg_type_gt_dot_dot_dot_gt_dot_dot_dot,
	    Qlt_lt_arg_name_gt_dot_dot_dot_gt_dot_dot_dot,
	    Qobt_throws_cbt_dot_dot_dot);
    QG2Connection = STATIC_SYMBOL("G2Connection",AB_package);
    QCOM_dot_gensym_dot_jgi_dot_G2Connection = 
	    STATIC_SYMBOL("COM.gensym.jgi.G2Connection",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,QG2Connection,
	    QCOM_dot_gensym_dot_jgi_dot_G2Connection);
    list_constant_34 = STATIC_CONS(list_constant_4,Qnil);
    string_constant_12 = STATIC_STRING("COM.gensym.jgi");
    list_constant_35 = STATIC_CONS(string_constant_12,Qnil);
    Qtemplate_line = STATIC_SYMBOL("TEMPLATE-LINE",AB_package);
    Qliteral = STATIC_SYMBOL("LITERAL",AB_package);
    string_constant_13 = STATIC_STRING("interface ");
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_13);
    QLT_INTERFACE_GT = STATIC_SYMBOL("<interface>",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_INTERFACE_GT);
    string_constant_14 = STATIC_STRING(" extends ");
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_14);
    Qexpandable = STATIC_SYMBOL("EXPANDABLE",AB_package);
    QRemote = STATIC_SYMBOL("Remote",AB_package);
    list_constant_8 = STATIC_LIST((SI_Long)2L,Qexpandable,QRemote);
    string_constant_15 = STATIC_STRING(" {");
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_15);
    list_constant_28 = STATIC_LIST((SI_Long)12L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_5,list_constant_6,
	    list_constant_7,list_constant_8,list_constant_9);
    string_constant_16 = STATIC_STRING("     void ");
    list_constant_10 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_16);
    QLT_INIT_NAME_GT = STATIC_SYMBOL("<init-name>",AB_package);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_INIT_NAME_GT);
    string_constant_17 = STATIC_STRING("(");
    list_constant_12 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_17);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qexpandable,QG2Connection);
    string_constant_18 = STATIC_STRING(" ");
    list_constant_14 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_18);
    QCONNECTION = STATIC_SYMBOL("connection",AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qexpandable,QCONNECTION);
    string_constant_19 = STATIC_STRING(");");
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_19);
    list_constant_29 = STATIC_LIST((SI_Long)14L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_10,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_16);
    list_constant_30 = STATIC_LIST((SI_Long)7L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qt);
    string_constant_20 = STATIC_STRING("     ");
    list_constant_17 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_20);
    QLT_RESULT_TYPE_GT = STATIC_SYMBOL("<result-type>",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_RESULT_TYPE_GT);
    QLT_METHOD_GT = STATIC_SYMBOL("<method>",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_METHOD_GT);
    Qmidst_of_comma_series = STATIC_SYMBOL("MIDST-OF-COMMA-SERIES",AB_package);
    QLT_ARG_TYPE_GT = STATIC_SYMBOL("<arg-type>",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qmidst_of_comma_series,
	    QLT_ARG_TYPE_GT);
    Qlast_of_comma_series = STATIC_SYMBOL("LAST-OF-COMMA-SERIES",AB_package);
    QLT_ARG_NAME_GT = STATIC_SYMBOL("<arg-name>",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qlast_of_comma_series,
	    QLT_ARG_NAME_GT);
    string_constant_21 = STATIC_STRING(")");
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_21);
    Qsplicable_literal = STATIC_SYMBOL("SPLICABLE-LITERAL",AB_package);
    string_constant_22 = STATIC_STRING(" throws");
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qsplicable_literal,
	    string_constant_22);
    Qsplice_out_unless_true = STATIC_SYMBOL("SPLICE-OUT-UNLESS-TRUE",
	    AB_package);
    QOBT_THROWS_CBT = STATIC_SYMBOL("[throws]",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qsplice_out_unless_true,
	    QOBT_THROWS_CBT);
    string_constant_23 = STATIC_STRING("; ");
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_23);
    Qreplicate_in_lines = STATIC_SYMBOL("REPLICATE-IN-LINES",AB_package);
    list_constant_26 = STATIC_CONS(Qreplicate_in_lines,Qnil);
    list_constant_31 = STATIC_LIST((SI_Long)21L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qt,Qnil,Qnil,list_constant_17,list_constant_18,
	    list_constant_14,list_constant_19,list_constant_12,
	    list_constant_20,list_constant_14,list_constant_21,
	    list_constant_22,list_constant_23,list_constant_14,
	    list_constant_24,list_constant_25,list_constant_26);
    string_constant_24 = STATIC_STRING("   }");
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_24);
    list_constant_32 = STATIC_LIST((SI_Long)8L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_27);
    list_constant_36 = STATIC_LIST((SI_Long)5L,list_constant_28,
	    list_constant_29,list_constant_30,list_constant_31,
	    list_constant_32);
    list_constant_37 = STATIC_LIST((SI_Long)6L,
	    Qjava_exported_class_interface,Qjava_interface_declaration,
	    list_constant_33,list_constant_34,list_constant_35,
	    list_constant_36);
    push_new_syntax_tree_template_entry(Qjava_exported_class_interface,
	    list_constant_37);
    Qjava_exported_class_implementation = 
	    STATIC_SYMBOL("JAVA-EXPORTED-CLASS-IMPLEMENTATION",AB_package);
    Qjava_class_declaration = STATIC_SYMBOL("JAVA-CLASS-DECLARATION",
	    AB_package);
    Qlt_class_gt = STATIC_SYMBOL("<CLASS>",AB_package);
    Qlt_method_symbol_gt_dot_dot_dot = STATIC_SYMBOL("<METHOD-SYMBOL>...",
	    AB_package);
    Qlt_method_string_gt_dot_dot_dot = STATIC_SYMBOL("<METHOD-STRING>...",
	    AB_package);
    Qlt_max_arg_count_gt = STATIC_SYMBOL("<MAX-ARG-COUNT>",AB_package);
    list_constant_83 = STATIC_LIST((SI_Long)6L,Qlt_class_gt,
	    Qlt_interface_gt,Qlt_method_symbol_gt_dot_dot_dot,
	    Qlt_method_string_gt_dot_dot_dot,Qlt_max_arg_count_gt,
	    Qlt_init_name_gt);
    QSymbol = STATIC_SYMBOL("Symbol",AB_package);
    QCOM_dot_gensym_dot_util_dot_Symbol = 
	    STATIC_SYMBOL("COM.gensym.util.Symbol",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,QSymbol,
	    QCOM_dot_gensym_dot_util_dot_Symbol);
    QG2RMIready = STATIC_SYMBOL("G2RMIready",AB_package);
    QCOM_dot_gensym_dot_jgi_dot_G2RMIready = 
	    STATIC_SYMBOL("COM.gensym.jgi.G2RMIready",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)2L,QG2RMIready,
	    QCOM_dot_gensym_dot_jgi_dot_G2RMIready);
    list_constant_84 = STATIC_LIST((SI_Long)3L,list_constant_38,
	    list_constant_4,list_constant_39);
    string_constant_25 = STATIC_STRING("COM.gensym.util");
    list_constant_85 = STATIC_CONS(string_constant_25,list_constant_35);
    string_constant_26 = STATIC_STRING("public class ");
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_26);
    QLT_CLASS_GT = STATIC_SYMBOL("<class>",AB_package);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_CLASS_GT);
    list_constant_42 = STATIC_LIST((SI_Long)2L,Qexpandable,QG2RMIready);
    string_constant_27 = STATIC_STRING(" implements ");
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_27);
    list_constant_44 = STATIC_CONS(list_constant_9,Qnil);
    list_constant_73 = STATIC_LIST_STAR((SI_Long)14L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_40,list_constant_41,
	    list_constant_7,list_constant_42,list_constant_43,
	    list_constant_6,list_constant_44);
    string_constant_28 = STATIC_STRING("     private static ");
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_28);
    list_constant_46 = STATIC_LIST((SI_Long)2L,Qexpandable,QSymbol);
    QLT_METHOD_SYMBOL_GT = STATIC_SYMBOL("<method-symbol>",AB_package);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qsubstitute,
	    QLT_METHOD_SYMBOL_GT);
    string_constant_29 = STATIC_STRING(" = Symbol.intern(");
    list_constant_48 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_29);
    QLT_METHOD_STRING_GT = STATIC_SYMBOL("<method-string>",AB_package);
    list_constant_49 = STATIC_LIST((SI_Long)2L,Qsubstitute,
	    QLT_METHOD_STRING_GT);
    string_constant_30 = STATIC_STRING("); ");
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_30);
    list_constant_51 = STATIC_CONS(list_constant_26,Qnil);
    list_constant_74 = STATIC_LIST_STAR((SI_Long)15L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qt,Qnil,Qnil,list_constant_45,list_constant_46,
	    list_constant_14,list_constant_47,list_constant_48,
	    list_constant_49,list_constant_50,list_constant_51);
    string_constant_31 = STATIC_STRING("     private ");
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_31);
    QmyConnection = STATIC_SYMBOL("myConnection",AB_package);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qexpandable,QmyConnection);
    string_constant_32 = STATIC_STRING(" = null;");
    list_constant_54 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_32);
    list_constant_75 = STATIC_LIST((SI_Long)12L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_52,list_constant_13,
	    list_constant_14,list_constant_53,list_constant_54);
    QObject = STATIC_SYMBOL("Object",AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qexpandable,QObject);
    string_constant_33 = STATIC_STRING("[] ");
    list_constant_56 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_33);
    QmyArgArray = STATIC_SYMBOL("myArgArray",AB_package);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qexpandable,QmyArgArray);
    string_constant_34 = STATIC_STRING(" = new ");
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_34);
    string_constant_35 = STATIC_STRING("[");
    list_constant_59 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_35);
    QLT_MAX_ARG_COUNT_GT = STATIC_SYMBOL("<max-arg-count>",AB_package);
    list_constant_60 = STATIC_LIST((SI_Long)2L,Qsubstitute,
	    QLT_MAX_ARG_COUNT_GT);
    string_constant_36 = STATIC_STRING("];");
    list_constant_61 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_36);
    list_constant_76 = STATIC_LIST((SI_Long)16L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_52,list_constant_55,
	    list_constant_56,list_constant_57,list_constant_58,
	    list_constant_55,list_constant_59,list_constant_60,
	    list_constant_61);
    string_constant_37 = STATIC_STRING("     public void ");
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_37);
    string_constant_38 = STATIC_STRING(") {");
    list_constant_63 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_38);
    list_constant_77 = STATIC_LIST((SI_Long)14L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_62,list_constant_11,
	    list_constant_12,list_constant_13,list_constant_14,
	    list_constant_15,list_constant_63);
    string_constant_39 = STATIC_STRING("       ");
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_39);
    string_constant_40 = STATIC_STRING(" = ");
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_40);
    string_constant_41 = STATIC_STRING(";");
    list_constant_66 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_41);
    list_constant_78 = STATIC_LIST((SI_Long)12L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_64,list_constant_53,
	    list_constant_65,list_constant_15,list_constant_66);
    string_constant_42 = STATIC_STRING("       connection.declareRemoteRPC(");
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_42);
    string_constant_43 = STATIC_STRING(", 1, 1, ");
    list_constant_68 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_43);
    QNULL = STATIC_SYMBOL("null",AB_package);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qexpandable,QNULL);
    string_constant_44 = STATIC_STRING(", 1000); ");
    list_constant_70 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_44);
    list_constant_79 = STATIC_LIST_STAR((SI_Long)13L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qt,Qnil,Qnil,list_constant_67,list_constant_47,
	    list_constant_68,list_constant_69,list_constant_70,
	    list_constant_51);
    string_constant_45 = STATIC_STRING("     }");
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_45);
    list_constant_80 = STATIC_LIST((SI_Long)8L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_71);
    Qinsert_subtree = STATIC_SYMBOL("INSERT-SUBTREE",AB_package);
    Qjava_exported_method_implementation = 
	    STATIC_SYMBOL("JAVA-EXPORTED-METHOD-IMPLEMENTATION",AB_package);
    list_constant_72 = STATIC_LIST((SI_Long)2L,Qinsert_subtree,
	    Qjava_exported_method_implementation);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)10L,Qtemplate_line,
	    list_constant_72,Qnil,Qnil,Qt,Qnil,Qnil,list_constant_17,
	    list_constant_72,list_constant_51);
    list_constant_82 = STATIC_CONS(list_constant_32,Qnil);
    list_constant_86 = STATIC_LIST_STAR((SI_Long)15L,list_constant_73,
	    list_constant_74,list_constant_30,list_constant_75,
	    list_constant_30,list_constant_76,list_constant_30,
	    list_constant_77,list_constant_78,list_constant_30,
	    list_constant_79,list_constant_80,list_constant_30,
	    list_constant_81,list_constant_82);
    list_constant_87 = STATIC_LIST((SI_Long)6L,
	    Qjava_exported_class_implementation,Qjava_class_declaration,
	    list_constant_83,list_constant_84,list_constant_85,
	    list_constant_86);
    push_new_syntax_tree_template_entry(Qjava_exported_class_implementation,
	    list_constant_87);
    Qjava_method_declaration = STATIC_SYMBOL("JAVA-METHOD-DECLARATION",
	    AB_package);
    Qlt_result_type_gt = STATIC_SYMBOL("<RESULT-TYPE>",AB_package);
    Qlt_method_gt = STATIC_SYMBOL("<METHOD>",AB_package);
    Qlt_arg_type_gt_dot_dot_dot = STATIC_SYMBOL("<ARG-TYPE>...",AB_package);
    Qlt_arg_name_gt_dot_dot_dot = STATIC_SYMBOL("<ARG-NAME>...",AB_package);
    Qobt_throws_cbt = STATIC_SYMBOL("[THROWS]",AB_package);
    Qobt_tl_throws_cbt = STATIC_SYMBOL("[~THROWS]",AB_package);
    Qlt_rpc_arg_type_gt_dot_dot_dot = STATIC_SYMBOL("<RPC-ARG-TYPE>...",
	    AB_package);
    Qlt_rpc_result_type_gt = STATIC_SYMBOL("<RPC-RESULT-TYPE>",AB_package);
    Qlt_method_symbol_gt = STATIC_SYMBOL("<METHOD-SYMBOL>",AB_package);
    Qlt_converted_result_gt = STATIC_SYMBOL("<CONVERTED-RESULT>",AB_package);
    list_constant_140 = STATIC_LIST((SI_Long)11L,Qlt_result_type_gt,
	    Qlt_method_gt,Qlt_arg_type_gt_dot_dot_dot,
	    Qlt_arg_name_gt_dot_dot_dot,Qobt_throws_cbt,Qobt_tl_throws_cbt,
	    Qlt_init_name_gt,Qlt_rpc_arg_type_gt_dot_dot_dot,
	    Qlt_rpc_result_type_gt,Qlt_method_symbol_gt,
	    Qlt_converted_result_gt);
    QG2AccessException = STATIC_SYMBOL("G2AccessException",AB_package);
    QCOM_dot_gensym_dot_jgi_dot_G2AccessException = 
	    STATIC_SYMBOL("COM.gensym.jgi.G2AccessException",AB_package);
    list_constant_88 = STATIC_LIST((SI_Long)2L,QG2AccessException,
	    QCOM_dot_gensym_dot_jgi_dot_G2AccessException);
    list_constant_141 = STATIC_CONS(list_constant_88,Qnil);
    string_constant_46 = STATIC_STRING("public ");
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_46);
    list_constant_90 = STATIC_CONS(list_constant_22,Qnil);
    list_constant_125 = STATIC_LIST_STAR((SI_Long)16L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_89,list_constant_18,
	    list_constant_14,list_constant_19,list_constant_12,
	    list_constant_20,list_constant_14,list_constant_21,
	    list_constant_90);
    Qskip_line_unless_true = STATIC_SYMBOL("SKIP-LINE-UNLESS-TRUE",AB_package);
    list_constant_91 = STATIC_CONS(QOBT_THROWS_CBT,Qnil);
    list_constant_92 = STATIC_CONS(Qskip_line_unless_true,list_constant_91);
    string_constant_47 = STATIC_STRING("       throws ");
    list_constant_93 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_47);
    list_constant_126 = STATIC_LIST((SI_Long)9L,Qtemplate_line,Qnil,
	    list_constant_92,Qnil,Qnil,Qnil,Qnil,list_constant_93,
	    list_constant_92);
    string_constant_48 = STATIC_STRING("   {");
    list_constant_94 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_48);
    list_constant_127 = STATIC_LIST((SI_Long)8L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_94);
    string_constant_49 = STATIC_STRING("     if (");
    list_constant_95 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_49);
    string_constant_50 = STATIC_STRING(" == null) {");
    list_constant_96 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_50);
    list_constant_128 = STATIC_LIST((SI_Long)10L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_95,list_constant_53,
	    list_constant_96);
    string_constant_51 = STATIC_STRING("       throw new ");
    list_constant_97 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_51);
    string_constant_52 = STATIC_STRING("(\"no connection to G2 - run ");
    list_constant_98 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_52);
    string_constant_53 = STATIC_STRING("\");");
    list_constant_99 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_53);
    list_constant_129 = STATIC_LIST((SI_Long)12L,Qtemplate_line,Qnil,
	    list_constant_92,Qnil,Qnil,Qnil,Qnil,list_constant_97,
	    list_constant_92,list_constant_98,list_constant_11,
	    list_constant_99);
    string_constant_54 = STATIC_STRING("       return ");
    list_constant_100 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_54);
    Qoptional_alternative = STATIC_SYMBOL("OPTIONAL-ALTERNATIVE",AB_package);
    QOBT_TL_THROWS_CBT = STATIC_SYMBOL("[~throws]",AB_package);
    list_constant_101 = STATIC_LIST((SI_Long)2L,Qoptional_alternative,
	    QOBT_TL_THROWS_CBT);
    list_constant_102 = STATIC_CONS(list_constant_66,Qnil);
    list_constant_130 = STATIC_LIST_STAR((SI_Long)10L,Qtemplate_line,Qnil,
	    Qnil,Qt,Qnil,Qnil,Qnil,list_constant_100,list_constant_101,
	    list_constant_102);
    QLT_I_GT = STATIC_SYMBOL("<i>",AB_package);
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_I_GT);
    string_constant_55 = STATIC_STRING("] = (");
    list_constant_105 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_55);
    QLT_RPC_ARG_TYPE_GT = STATIC_SYMBOL("<rpc-arg-type>",AB_package);
    list_constant_106 = STATIC_LIST((SI_Long)2L,Qsubstitute,
	    QLT_RPC_ARG_TYPE_GT);
    string_constant_56 = STATIC_STRING(") ");
    list_constant_107 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_56);
    QconvertJavatoG2 = STATIC_SYMBOL("convertJavatoG2",AB_package);
    list_constant_108 = STATIC_LIST((SI_Long)2L,Qexpandable,QconvertJavatoG2);
    list_constant_103 = STATIC_CONS(QLT_ARG_NAME_GT,Qnil);
    list_constant_109 = STATIC_CONS(Qsubstitute,list_constant_103);
    list_constant_110 = STATIC_CONS(list_constant_50,list_constant_51);
    list_constant_131 = STATIC_LIST_STAR((SI_Long)18L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qt,Qt,Qnil,list_constant_17,list_constant_57,
	    list_constant_59,list_constant_104,list_constant_105,
	    list_constant_106,list_constant_107,list_constant_108,
	    list_constant_12,list_constant_109,list_constant_110);
    QLT_RPC_RESULT_TYPE_GT = STATIC_SYMBOL("<rpc-result-type>",AB_package);
    list_constant_111 = STATIC_LIST((SI_Long)2L,Qsubstitute,
	    QLT_RPC_RESULT_TYPE_GT);
    QRESULT = STATIC_SYMBOL("result",AB_package);
    list_constant_112 = STATIC_LIST((SI_Long)2L,Qexpandable,QRESULT);
    list_constant_132 = STATIC_LIST_STAR((SI_Long)12L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_17,list_constant_111,
	    list_constant_14,list_constant_112,list_constant_102);
    string_constant_57 = STATIC_STRING("     try {");
    list_constant_113 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_57);
    list_constant_133 = STATIC_LIST((SI_Long)8L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_113);
    list_constant_134 = STATIC_LIST((SI_Long)9L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_64,list_constant_112);
    string_constant_58 = STATIC_STRING("         = (");
    list_constant_114 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_58);
    list_constant_135 = STATIC_LIST_STAR((SI_Long)10L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_114,list_constant_111,
	    list_constant_90);
    string_constant_59 = STATIC_STRING("           myConnection.callRPC(");
    list_constant_115 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_59);
    string_constant_60 = STATIC_STRING(", ");
    list_constant_116 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_60);
    list_constant_117 = STATIC_CONS(list_constant_16,Qnil);
    list_constant_136 = STATIC_LIST_STAR((SI_Long)12L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_115,list_constant_47,
	    list_constant_116,list_constant_57,list_constant_117);
    string_constant_61 = STATIC_STRING("     } catch (");
    list_constant_118 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_61);
    list_constant_119 = STATIC_LIST((SI_Long)2L,Qexpandable,
	    QG2AccessException);
    QE = STATIC_SYMBOL("e",AB_package);
    list_constant_120 = STATIC_LIST((SI_Long)2L,Qexpandable,QE);
    list_constant_121 = STATIC_CONS(list_constant_63,Qnil);
    list_constant_137 = STATIC_LIST_STAR((SI_Long)12L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_118,list_constant_119,
	    list_constant_14,list_constant_120,list_constant_121);
    string_constant_62 = STATIC_STRING("(e.toString());");
    list_constant_122 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_62);
    list_constant_138 = STATIC_LIST((SI_Long)10L,Qtemplate_line,Qnil,
	    list_constant_92,Qnil,Qnil,Qnil,Qnil,list_constant_97,
	    list_constant_92,list_constant_122);
    string_constant_63 = STATIC_STRING("     return (");
    list_constant_123 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_63);
    QLT_CONVERTED_RESULT_GT = STATIC_SYMBOL("<converted-result>",AB_package);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qsubstitute,
	    QLT_CONVERTED_RESULT_GT);
    list_constant_139 = STATIC_LIST_STAR((SI_Long)12L,Qtemplate_line,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_123,list_constant_18,
	    list_constant_107,list_constant_124,list_constant_102);
    list_constant_142 = STATIC_LIST_STAR((SI_Long)21L,list_constant_125,
	    list_constant_126,list_constant_127,list_constant_128,
	    list_constant_129,list_constant_130,list_constant_80,
	    list_constant_30,list_constant_131,list_constant_30,
	    list_constant_132,list_constant_133,list_constant_134,
	    list_constant_135,list_constant_136,list_constant_137,
	    list_constant_138,list_constant_130,list_constant_80,
	    list_constant_139,list_constant_82);
    list_constant_143 = STATIC_LIST((SI_Long)6L,
	    Qjava_exported_method_implementation,Qjava_method_declaration,
	    list_constant_140,list_constant_141,list_constant_35,
	    list_constant_142);
    push_new_syntax_tree_template_entry(Qjava_exported_method_implementation,
	    list_constant_143);
    Qjava_exported_exception = STATIC_SYMBOL("JAVA-EXPORTED-EXCEPTION",
	    AB_package);
    Qlt_exception_gt = STATIC_SYMBOL("<EXCEPTION>",AB_package);
    list_constant_148 = STATIC_CONS(Qlt_exception_gt,Qnil);
    QLT_EXCEPTION_GT = STATIC_SYMBOL("<exception>",AB_package);
    list_constant_144 = STATIC_LIST((SI_Long)2L,Qsubstitute,QLT_EXCEPTION_GT);
    QException = STATIC_SYMBOL("Exception",AB_package);
    list_constant_145 = STATIC_LIST((SI_Long)2L,Qexpandable,QException);
    string_constant_64 = STATIC_STRING(" {}");
    list_constant_146 = STATIC_LIST((SI_Long)2L,Qliteral,string_constant_64);
    list_constant_147 = STATIC_LIST((SI_Long)12L,Qtemplate_line,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,list_constant_40,list_constant_144,
	    list_constant_7,list_constant_145,list_constant_146);
    list_constant_149 = STATIC_CONS(list_constant_147,Qnil);
    list_constant_150 = STATIC_LIST((SI_Long)6L,Qjava_exported_exception,
	    Qjava_class_declaration,list_constant_148,Qnil,Qnil,
	    list_constant_149);
    push_new_syntax_tree_template_entry(Qjava_exported_exception,
	    list_constant_150);
    if (Global_output_stream_for_expand_syntax_template == UNBOUND)
	Global_output_stream_for_expand_syntax_template = Nil;
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    Qutf_8_string = STATIC_SYMBOL("UTF-8-STRING",AB_package);
    Qtext_conversion_style_for_purpose = 
	    STATIC_SYMBOL("TEXT-CONVERSION-STYLE-FOR-PURPOSE",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    string_constant_6 = STATIC_STRING("JEMIT ERROR: ~a");
    Qno_binding = STATIC_SYMBOL("NO-BINDING",AB_package);
    list_constant_151 = STATIC_CONS(Qno_binding,Qnil);
    Syntax_tree_no_binding_tag = list_constant_151;
    Qlist_expected = STATIC_SYMBOL("LIST-EXPECTED",AB_package);
    Qlist_of_lists_expected = STATIC_SYMBOL("LIST-OF-LISTS-EXPECTED",
	    AB_package);
    Qsimple = STATIC_SYMBOL("SIMPLE",AB_package);
    Qoptionals_list = STATIC_SYMBOL("OPTIONALS-LIST",AB_package);
    Qoptional = STATIC_SYMBOL("OPTIONAL",AB_package);
    Qalternatives_list = STATIC_SYMBOL("ALTERNATIVES-LIST",AB_package);
    Qlist_of_lists = STATIC_SYMBOL("LIST-OF-LISTS",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qlist,Qlist_of_lists);
    Qatom_expected = STATIC_SYMBOL("ATOM-EXPECTED",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_3,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    string_constant_7 = STATIC_STRING("");
    Qgensym_string = STATIC_SYMBOL("GENSYM-STRING",AB_package);
}
