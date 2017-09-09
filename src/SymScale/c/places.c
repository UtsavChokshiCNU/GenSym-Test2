/* places.c
 * Input file:  places.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "places.h"


DEFINE_VARIABLE_WITH_SYMBOL(Current_include_denotation_for_block_flag, Qcurrent_include_denotation_for_block_flag);

static Object string_constant;     /* "" */

/* DENOTE-COMPONENT-OF-BLOCK */
Object denote_component_of_block varargs_1(int, n)
{
    Object include_denotation_for_block;
    Object component_particulars, block, current_computation_frame;
    Object current_include_denotation_for_block_flag, temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(91,0);
    INIT_ARGS_nonrelocating();
    include_denotation_for_block = REQUIRED_ARG_nonrelocating();
    component_particulars = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : 
	    Current_computation_component_particulars;
    block = OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Current_computation_frame;
    END_ARGS_nonrelocating();
    current_computation_frame = block;
    current_include_denotation_for_block_flag = include_denotation_for_block;
    PUSH_SPECIAL_WITH_SYMBOL(Current_include_denotation_for_block_flag,Qcurrent_include_denotation_for_block_flag,current_include_denotation_for_block_flag,
	    1);
      PUSH_SPECIAL_WITH_SYMBOL(Current_computation_frame,Qcurrent_computation_frame,current_computation_frame,
	      0);
	temp = component_particulars;
	if (temp);
	else
	    temp = Qcurrent_computation_frame;
	result = denote_component_of_block_1(temp,string_constant);
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object string_constant_1;   /* "~A~NF" */

static Object array_constant;      /* # */

static Object Qcell_array_element;  /* cell-array-element */

static Object Qslot_component;     /* slot-component */

static Object string_constant_2;   /* " of " */

static Object Qget_simple_part_feature;  /* get-simple-part-feature */

static Object string_constant_3;   /* "~(~Athe ~A~)" */

static Object Qget_subpart_of_collection;  /* get-subpart-of-collection */

static Object Qget_subpart;        /* get-subpart */

static Object string_constant_4;   /* "~(~A~A ~D~)" */

static Object Qpart_description_of_frame;  /* part-description-of-frame */

static Object Qaliased_attribute;  /* aliased-attribute */

static Object Qattribute;          /* attribute */

static Object string_constant_5;   /* "~(~Athe ~NQ~)" */

static Object Qelement;            /* element */

static Object string_constant_6;   /* "~a" */

static Object string_constant_7;   /* " [~a]" */

static Object Qprocedure_statement;  /* procedure-statement */

static Object string_constant_8;   /* " within " */

static Object Qgraph_expression;   /* graph-expression */

static Object string_constant_9;   /* "graph expression ~d" */

static Object string_constant_10;  /* "~a data-series ~a" */

static Object string_constant_11;  /* "~athe ~a data-series" */

static Object list_constant;       /* # */

static Object Qprocedure_invocation;  /* procedure-invocation */

static Object Qvirtual_attribute;  /* virtual-attribute */

static Object string_constant_12;  /* "~athe ~a" */

static Object Qrule_scan_interval;  /* rule-scan-interval */

static Object string_constant_13;  /* "~athe scan-interval" */

static Object Qsimulation_initial_value;  /* simulation-initial-value */

static Object string_constant_14;  /* "~athe simulation-initial-value" */

/* DENOTE-COMPONENT-OF-BLOCK-1 */
Object denote_component_of_block_1(component_particulars,preposition)
    Object component_particulars, preposition;
{
    Object temp, gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, slot_name, defining_class_qm;
    Object slot_component_indicator_qm, parent_1, part_feature, subpart_type;
    Object index_1, further_particulars, alias, attribute_name, defining_class;
    Object statement, count_1;

    x_note_fn_call(91,1);
    if (EQ(Qcurrent_computation_frame,component_particulars)) {
	if (Current_include_denotation_for_block_flag)
	    return tformat(3,string_constant_1,preposition,
		    Current_computation_frame);
	else
	    return VALUES_1(Nil);
    }
    else if (ATOM(component_particulars)) {
	twrite_general_string(preposition);
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)25L));
    }
    else {
	temp = M_CAR(component_particulars);
	if (EQ(temp,Qcell_array_element)) {
	    gensymed_symbol = 
		    ISVREF(ISVREF(ISVREF(ISVREF(Current_computation_frame,
		    (SI_Long)1L),(SI_Long)11L),(SI_Long)11L),(SI_Long)1L);
	    gensymed_symbol_1 = Current_computation_frame;
	    gensymed_symbol_2 = SECOND(component_particulars);
	    gensymed_symbol_3 = Current_include_denotation_for_block_flag;
	    return inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else if (EQ(temp,Qslot_component)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    slot_name = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    defining_class_qm = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    slot_component_indicator_qm = CAR(gensymed_symbol);
	    denote_slot_component_group(Current_computation_frame,
		    slot_name,defining_class_qm,slot_component_indicator_qm);
	    return denote_component_of_block_1(Qcurrent_computation_frame,
		    string_constant_2);
	}
	else if (EQ(temp,Qget_simple_part_feature)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    parent_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    part_feature = CAR(gensymed_symbol);
	    tformat(3,string_constant_3,preposition,part_feature);
	    return denote_component_of_block_1(parent_1,string_constant_2);
	}
	else if (EQ(temp,Qget_subpart_of_collection) || EQ(temp,
		    Qget_subpart)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    parent_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol_1 = CDR(gensymed_symbol_1);
	    subpart_type = CAR(gensymed_symbol_1);
	    index_1 = CAR(gensymed_symbol);
	    tformat(4,string_constant_4,preposition,subpart_type,index_1);
	    return denote_component_of_block_1(parent_1,string_constant_2);
	}
	else if (EQ(temp,Qpart_description_of_frame)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    further_particulars = CAR(gensymed_symbol);
	    return denote_component_of_block_1(further_particulars,
		    preposition);
	}
	else if (EQ(temp,Qaliased_attribute)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    alias = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    further_particulars = CAR(gensymed_symbol);
	    tformat(3,string_constant_3,preposition,alias);
	    return denote_component_of_block_1(further_particulars,
		    string_constant_2);
	}
	else if (EQ(temp,Qattribute)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    attribute_name = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    defining_class = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    further_particulars = CAR(gensymed_symbol);
	    tformat(4,string_constant_5,preposition,attribute_name,
		    defining_class);
	    return denote_component_of_block_1(further_particulars,
		    string_constant_2);
	}
	else if (EQ(temp,Qelement)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    index_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    further_particulars = CAR(gensymed_symbol);
	    tformat(2,string_constant_6,preposition);
	    denote_component_of_block_1(further_particulars,string_constant);
	    return tformat(2,string_constant_7,index_1);
	}
	else if (EQ(temp,Qprocedure_statement)) {
	    gensymed_symbol = component_particulars;
	    gensymed_symbol = CDR(gensymed_symbol);
	    statement = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    parent_1 = CAR(gensymed_symbol);
	    tformat(2,string_constant_6,preposition);
	    write_procedure_statement(statement);
	    return denote_component_of_block_1(parent_1,string_constant_8);
	}
	else if (EQ(temp,Qgraph_expression))
	    return tformat(2,string_constant_9,CDR(component_particulars));
	else if (EQ(temp,Qdata_series)) {
	    count_1 = SECOND(component_particulars);
	    if ( !(FIXNUMP(count_1) && FIXNUM_LE(FIX((SI_Long)-128L),
		    count_1) && FIXNUM_LE(count_1,FIX((SI_Long)127L))))
		tformat(3,string_constant_10,preposition,count_1);
	    else
		switch (INTEGER_TO_CHAR(count_1)) {
		  case 1:
		  case 2:
		  case 3:
		    tformat(3,string_constant_11,preposition,nth(count_1,
			    list_constant));
		    break;
		  default:
		    tformat(3,string_constant_10,preposition,count_1);
		    break;
		}
	    return denote_component_of_block_1(Qcurrent_computation_frame,
		    string_constant_2);
	}
	else if (EQ(temp,Qprocedure_invocation))
	    return denote_component_of_block_1_for_procedure_invocation();
	else if (EQ(temp,Qvirtual_attribute)) {
	    tformat(3,string_constant_12,preposition,
		    SECOND(component_particulars));
	    return denote_component_of_block_1(Qcurrent_computation_frame,
		    string_constant_2);
	}
	else if (EQ(temp,Qrule_scan_interval)) {
	    tformat(2,string_constant_13,preposition);
	    return denote_component_of_block_1(Qcurrent_computation_frame,
		    string_constant_2);
	}
	else if (EQ(temp,Qsimulation_initial_value)) {
	    tformat(2,string_constant_14,preposition);
	    return denote_component_of_block_1(Qcurrent_computation_frame,
		    string_constant_2);
	}
	else
	    return VALUES_1(Qnil);
    }
}

static Object array_constant_1;    /* # */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-ROOT */
Object denote_cell_array_element_for_root(root,component_particulars,
	    include_component_particulars_for_block)
    Object root, component_particulars;
    Object include_component_particulars_for_block;
{
    x_note_fn_call(91,2);
    twrite_beginning_of_wide_string(array_constant_1,FIX((SI_Long)16L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_2);
}

/* WRITE-STATUS-OF-COMPONENT-PARTICULARS */
Object write_status_of_component_particulars(component_particulars,status)
    Object component_particulars, status;
{
    x_note_fn_call(91,3);
    return VALUES_1(Nil);
}

Object The_type_description_of_place_reference_internals = UNBOUND;

DEFINE_VARIABLE_WITH_SYMBOL(Chain_of_available_place_reference_internalss, Qchain_of_available_place_reference_internalss);

DEFINE_VARIABLE_WITH_SYMBOL(Place_reference_internals_count, Qplace_reference_internals_count);

Object Chain_of_available_place_reference_internalss_vector = UNBOUND;

/* PLACE-REFERENCE-INTERNALS-STRUCTURE-MEMORY-USAGE */
Object place_reference_internals_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(91,4);
    temp = Place_reference_internals_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-PLACE-REFERENCE-INTERNALS-COUNT */
Object outstanding_place_reference_internals_count()
{
    Object def_structure_place_reference_internals_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(91,5);
    gensymed_symbol = IFIX(Place_reference_internals_count);
    def_structure_place_reference_internals_variable = 
	    Chain_of_available_place_reference_internalss;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_place_reference_internals_variable))
	goto end_loop;
    def_structure_place_reference_internals_variable = 
	    ISVREF(def_structure_place_reference_internals_variable,
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

static Object Qplace_reference;    /* place-reference */

/* RECLAIM-PLACE-REFERENCE-INTERNALS-1 */
Object reclaim_place_reference_internals_1(place_reference_internals)
    Object place_reference_internals;
{
    Object structure_being_reclaimed, thing, temp, svref_arg_2;
    Declare_special(1);

    x_note_fn_call(91,6);
    inline_note_reclaim_cons(place_reference_internals,Nil);
    structure_being_reclaimed = place_reference_internals;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value(ISVREF(place_reference_internals,(SI_Long)0L));
      SVREF(place_reference_internals,FIX((SI_Long)0L)) = Nil;
      thing = ISVREF(place_reference_internals,(SI_Long)1L);
      if (CONSP(thing) && EQ(M_CDR(thing),Qplace_reference))
	  reclaim_evaluation_place_reference(thing);
      SVREF(place_reference_internals,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(place_reference_internals,
	      (SI_Long)2L));
      SVREF(place_reference_internals,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_place_reference_internalss_vector,
	    IFIX(Current_thread_index));
    SVREF(place_reference_internals,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_place_reference_internalss_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = place_reference_internals;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-PLACE-REFERENCE-INTERNALS */
Object reclaim_structure_for_place_reference_internals(place_reference_internals)
    Object place_reference_internals;
{
    x_note_fn_call(91,7);
    return reclaim_place_reference_internals_1(place_reference_internals);
}

/* MAKE-PERMANENT-PLACE-REFERENCE-INTERNALS-STRUCTURE-INTERNAL */
Object make_permanent_place_reference_internals_structure_internal()
{
    Object def_structure_place_reference_internals_variable, the_array;
    Object defstruct_g2_place_reference_internals_variable;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(91,8);
    def_structure_place_reference_internals_variable = Nil;
    atomic_incff_symval(Qplace_reference_internals_count,FIX((SI_Long)1L));
    if (PUSH_AREA(Dynamic_area,0)) {
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
	defstruct_g2_place_reference_internals_variable = the_array;
	def_structure_place_reference_internals_variable = 
		defstruct_g2_place_reference_internals_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_place_reference_internals_variable);
}

/* MAKE-PLACE-REFERENCE-INTERNALS-1 */
Object make_place_reference_internals_1(place_reference_internals_particulars,
	    place_reference_internals_block_or_symbol,
	    place_reference_internals_frame_serial_number)
    Object place_reference_internals_particulars;
    Object place_reference_internals_block_or_symbol;
    Object place_reference_internals_frame_serial_number;
{
    Object def_structure_place_reference_internals_variable, svref_arg_1;
    Object svref_arg_2, svref_new_value;

    x_note_fn_call(91,9);
    def_structure_place_reference_internals_variable = 
	    ISVREF(Chain_of_available_place_reference_internalss_vector,
	    IFIX(Current_thread_index));
    if (def_structure_place_reference_internals_variable) {
	svref_arg_1 = Chain_of_available_place_reference_internalss_vector;
	svref_arg_2 = Current_thread_index;
	svref_new_value = 
		ISVREF(def_structure_place_reference_internals_variable,
		(SI_Long)0L);
	SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
    }
    else
	def_structure_place_reference_internals_variable = 
		make_permanent_place_reference_internals_structure_internal();
    inline_note_allocate_cons(def_structure_place_reference_internals_variable,
	    Nil);
    SVREF(def_structure_place_reference_internals_variable,
	    FIX((SI_Long)0L)) = place_reference_internals_particulars;
    SVREF(def_structure_place_reference_internals_variable,
	    FIX((SI_Long)1L)) = place_reference_internals_block_or_symbol;
    SVREF(def_structure_place_reference_internals_variable,
	    FIX((SI_Long)2L)) = place_reference_internals_frame_serial_number;
    return VALUES_1(def_structure_place_reference_internals_variable);
}

/* COPY-PLACE-REFERENCE-INTERNALS */
Object copy_place_reference_internals(place_reference_internals)
    Object place_reference_internals;
{
    Object temp, thing, temp_1;

    x_note_fn_call(91,10);
    temp = copy_for_slot_value(ISVREF(place_reference_internals,(SI_Long)0L));
    thing = ISVREF(place_reference_internals,(SI_Long)1L);
    temp_1 = CONSP(thing) && EQ(M_CDR(thing),Qplace_reference) ? 
	    copy_evaluation_place_reference(thing) : thing;
    temp_1 = make_place_reference_internals_1(temp,temp_1,
	    copy_frame_serial_number(ISVREF(place_reference_internals,
	    (SI_Long)2L)));
    return VALUES_1(temp_1);
}

/* MAKE-EVALUATION-PLACE-REFERENCE-TO-PLACE */
Object make_evaluation_place_reference_to_place(particulars,block_or_symbol)
    Object particulars, block_or_symbol;
{
    Object temp;

    x_note_fn_call(91,11);
    temp = eval_cons_1(make_place_reference_internals_1(particulars,
	    block_or_symbol,
	    copy_frame_serial_number(Current_frame_serial_number)),
	    Qplace_reference);
    return VALUES_1(temp);
}

static Object Qab_structure;       /* structure */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* EVALUATION-PLACE-REFERENCE-VALID-P */
Object evaluation_place_reference_valid_p(place_reference)
    Object place_reference;
{
    Object internals, block_or_symbol, temp, x2, gensymed_symbol, x, y, xa, ya;
    char temp_1;

    x_note_fn_call(91,12);
    internals = M_CAR(place_reference);
    block_or_symbol = ISVREF(internals,(SI_Long)1L);
    temp = SYMBOLP(block_or_symbol) ? T : Nil;
    if (temp);
    else
	temp = CONSP(block_or_symbol) ? (EQ(M_CDR(block_or_symbol),
		Qab_structure) ? T : Nil) : Qnil;
    if (temp);
    else {
	if (SIMPLE_VECTOR_P(block_or_symbol) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(block_or_symbol)) > 
		(SI_Long)2L &&  !EQ(ISVREF(block_or_symbol,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(block_or_symbol,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol = ISVREF(block_or_symbol,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(block_or_symbol) ? 
		    EQ(ISVREF(block_or_symbol,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
			== (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else {
		x = gensymed_symbol;
		y = ISVREF(internals,(SI_Long)2L);
		if (FIXNUMP(y))
		    temp_1 = FIXNUMP(x) ? FIXNUM_LT(y,x) : TRUEP(T);
		else if (FIXNUMP(x))
		    temp_1 = TRUEP(Nil);
		else {
		    xa = M_CAR(y);
		    ya = M_CAR(x);
		    temp_1 = FIXNUM_LT(xa,ya);
		    if (temp_1);
		    else
			temp_1 = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),
				M_CDR(x)) : TRUEP(Qnil);
		}
	    }
	    temp =  !temp_1 ? T : Nil;
	}
	else
	    temp = Nil;
    }
    if (temp);
    else
	temp = evaluation_place_reference_valid_p(block_or_symbol);
    return VALUES_1(temp);
}

/* RECLAIM-EVALUATION-PLACE-REFERENCE */
Object reclaim_evaluation_place_reference(place_reference)
    Object place_reference;
{
    Object place_reference_internals, structure_being_reclaimed, thing, temp;
    Object svref_arg_2;
    Declare_special(1);

    x_note_fn_call(91,13);
    place_reference_internals = M_CAR(place_reference);
    inline_note_reclaim_cons(place_reference_internals,Nil);
    structure_being_reclaimed = place_reference_internals;
    PUSH_SPECIAL_WITH_SYMBOL(Structure_being_reclaimed,Qstructure_being_reclaimed,structure_being_reclaimed,
	    0);
      reclaim_slot_value(ISVREF(place_reference_internals,(SI_Long)0L));
      SVREF(place_reference_internals,FIX((SI_Long)0L)) = Nil;
      thing = ISVREF(place_reference_internals,(SI_Long)1L);
      if (CONSP(thing) && EQ(M_CDR(thing),Qplace_reference))
	  reclaim_evaluation_place_reference(thing);
      SVREF(place_reference_internals,FIX((SI_Long)1L)) = Nil;
      reclaim_frame_serial_number(ISVREF(place_reference_internals,
	      (SI_Long)2L));
      SVREF(place_reference_internals,FIX((SI_Long)2L)) = Nil;
    POP_SPECIAL();
    temp = ISVREF(Chain_of_available_place_reference_internalss_vector,
	    IFIX(Current_thread_index));
    SVREF(place_reference_internals,FIX((SI_Long)0L)) = temp;
    temp = Chain_of_available_place_reference_internalss_vector;
    svref_arg_2 = Current_thread_index;
    SVREF(temp,svref_arg_2) = place_reference_internals;
    if (place_reference) {
	inline_note_reclaim_cons(place_reference,Qeval);
	if (ISVREF(Available_eval_conses_tail_vector,
		IFIX(Current_thread_index))) {
	    temp = ISVREF(Available_eval_conses_tail_vector,
		    IFIX(Current_thread_index));
	    M_CDR(temp) = place_reference;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = place_reference;
	}
	else {
	    temp = Available_eval_conses_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = place_reference;
	    temp = Available_eval_conses_tail_vector;
	    svref_arg_2 = Current_thread_index;
	    SVREF(temp,svref_arg_2) = place_reference;
	}
	M_CDR(place_reference) = Nil;
    }
    return VALUES_1(Nil);
}

/* COPY-EVALUATION-PLACE-REFERENCE */
Object copy_evaluation_place_reference(place_reference)
    Object place_reference;
{
    Object temp;

    x_note_fn_call(91,14);
    temp = 
	    eval_cons_1(copy_place_reference_internals(M_CAR(place_reference)),
	    Qplace_reference);
    return VALUES_1(temp);
}

/* VALIDATE-EVALUATION-PLACE-REFERENCE */
Object validate_evaluation_place_reference(place_reference,frame_serial_number)
    Object place_reference, frame_serial_number;
{
    Object temp;

    x_note_fn_call(91,15);
    if ( !TRUEP(evaluation_place_reference_valid_p(place_reference))) {
	reclaim_evaluation_place_reference(place_reference);
	temp = Nil;
    }
    else
	temp = place_reference;
    return VALUES_1(temp);
}

/* EVALUATION-PLACE-REFERENCE-EQL */
Object evaluation_place_reference_eql(place_reference_1,place_reference_2)
    Object place_reference_1, place_reference_2;
{
    x_note_fn_call(91,16);
    return VALUES_1(Nil);
}

static Object array_constant_2;    /* # */

static Object list_constant_1;     /* # */

static Object array_constant_3;    /* # */

/* WRITE-EVALUATION-PLACE-REFERENCE */
Object write_evaluation_place_reference(place_reference)
    Object place_reference;
{
    x_note_fn_call(91,17);
    if ( !TRUEP(evaluation_place_reference_valid_p(place_reference))) {
	denote_component_of_block(2,Nil,ISVREF(M_CAR(place_reference),
		(SI_Long)0L));
	twrite_beginning_of_wide_string(array_constant_2,FIX((SI_Long)18L));
    }
    else if (type_specification_type_p(ISVREF(M_CAR(place_reference),
	    (SI_Long)1L),list_constant_1))
	twrite_beginning_of_wide_string(array_constant_3,FIX((SI_Long)28L));
    else
	denote_component_of_block(3,T,ISVREF(M_CAR(place_reference),
		(SI_Long)0L),ISVREF(M_CAR(place_reference),(SI_Long)1L));
    return VALUES_1(Nil);
}

void places_INIT()
{
    Object temp, temp_1, gensymed_symbol;
    Object reclaim_structure_for_place_reference_internals_1;
    Object Qwrite_evaluation_place_reference, Qdefined_evaluation_type_writer;
    Object AB_package, list_constant_2, Qevaluation_place_reference_eql;
    Object Qdefined_evaluation_type_comparitor;
    Object Qvalidate_evaluation_place_reference;
    Object Qdefined_evaluation_type_validator;
    Object Qcopy_evaluation_place_reference, Qdefined_evaluation_type_copier;
    Object Qreclaim_evaluation_place_reference;
    Object Qdefined_evaluation_type_reclaimer;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qplace_reference_internals;
    Object Qreclaim_structure, Qoutstanding_place_reference_internals_count;
    Object Qplace_reference_internals_structure_memory_usage, Qutilities2;
    Object string_constant_19, Qtype_description_of_type;
    Object Qtype_description_of_unique_type_name_of_gensym_structure;
    Object Qg2_defstruct_structure_name_place_reference_internals_g2_struct;
    Object string_constant_18, Qtype_specification_of_defined_evaluation_type;
    Object Qclasses_which_define, Qdenote_cell_array_element, Qroot;
    Object Qdenote_cell_array_element_for_root, Qgeneric_method_lambda_list;
    Object list_constant_3, Qinclude_denotation_for_block, Qcell_index;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object Qcomponent_kind_description;

    x_note_fn_call(91,18);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qgraph_expression = STATIC_SYMBOL("GRAPH-EXPRESSION",AB_package);
    temp = adjoin(2,Qgraph_expression,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    Qcomponent_kind_description = 
	    STATIC_SYMBOL("COMPONENT-KIND-DESCRIPTION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qgraph_expression),
	    Qcomponent_kind_description,Nil);
    Qdata_series = STATIC_SYMBOL("DATA-SERIES",AB_package);
    temp = adjoin(2,Qdata_series,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qdata_series),
	    Qcomponent_kind_description,Nil);
    Qcell_array_element = STATIC_SYMBOL("CELL-ARRAY-ELEMENT",AB_package);
    temp = adjoin(2,Qcell_array_element,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qcell_array_element),
	    Qcomponent_kind_description,Nil);
    Qslot_component = STATIC_SYMBOL("SLOT-COMPONENT",AB_package);
    temp = adjoin(2,Qslot_component,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qslot_component),
	    Qcomponent_kind_description,Nil);
    Qget_simple_part_feature = STATIC_SYMBOL("GET-SIMPLE-PART-FEATURE",
	    AB_package);
    temp = adjoin(2,Qget_simple_part_feature,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qget_simple_part_feature),
	    Qcomponent_kind_description,Nil);
    Qget_subpart_of_collection = STATIC_SYMBOL("GET-SUBPART-OF-COLLECTION",
	    AB_package);
    temp = adjoin(2,Qget_subpart_of_collection,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qget_subpart_of_collection),
	    Qcomponent_kind_description,Nil);
    Qpart_description_of_frame = STATIC_SYMBOL("PART-DESCRIPTION-OF-FRAME",
	    AB_package);
    temp = adjoin(2,Qpart_description_of_frame,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qpart_description_of_frame),
	    Qcomponent_kind_description,Nil);
    Qaliased_attribute = STATIC_SYMBOL("ALIASED-ATTRIBUTE",AB_package);
    temp = adjoin(2,Qaliased_attribute,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qaliased_attribute),
	    Qcomponent_kind_description,Nil);
    Qattribute = STATIC_SYMBOL("ATTRIBUTE",AB_package);
    temp = adjoin(2,Qattribute,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qattribute),
	    Qcomponent_kind_description,Nil);
    Qelement = STATIC_SYMBOL("ELEMENT",AB_package);
    temp = adjoin(2,Qelement,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qelement),
	    Qcomponent_kind_description,Nil);
    Qprocedure_statement = STATIC_SYMBOL("PROCEDURE-STATEMENT",AB_package);
    temp = adjoin(2,Qprocedure_statement,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qprocedure_statement),
	    Qcomponent_kind_description,Nil);
    Qprocedure_invocation = STATIC_SYMBOL("PROCEDURE-INVOCATION",AB_package);
    temp = adjoin(2,Qprocedure_invocation,Set_of_all_component_kinds);
    Set_of_all_component_kinds = temp;
    set_property_value_function(get_symbol_properties_function(Qprocedure_invocation),
	    Qcomponent_kind_description,Nil);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant = STATIC_STRING("");
    string_constant_1 = STATIC_STRING("~A~NF");
    list_constant_2 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)13L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)17L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)18L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)19L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)24L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)30L,(SI_Long)25L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)31L,(SI_Long)57344L);
    string_constant_2 = STATIC_STRING(" of ");
    string_constant_3 = STATIC_STRING("~(~Athe ~A~)");
    Qget_subpart = STATIC_SYMBOL("GET-SUBPART",AB_package);
    string_constant_4 = STATIC_STRING("~(~A~A ~D~)");
    string_constant_5 = STATIC_STRING("~(~Athe ~NQ~)");
    string_constant_6 = STATIC_STRING("~a");
    string_constant_7 = STATIC_STRING(" [~a]");
    string_constant_8 = STATIC_STRING(" within ");
    string_constant_9 = STATIC_STRING("graph expression ~d");
    string_constant_10 = STATIC_STRING("~a data-series ~a");
    string_constant_11 = STATIC_STRING("~athe ~a data-series");
    string_constant_15 = STATIC_STRING("first");
    string_constant_16 = STATIC_STRING("second");
    string_constant_17 = STATIC_STRING("third");
    list_constant = STATIC_LIST((SI_Long)4L,Qnil,string_constant_15,
	    string_constant_16,string_constant_17);
    Qvirtual_attribute = STATIC_SYMBOL("VIRTUAL-ATTRIBUTE",AB_package);
    string_constant_12 = STATIC_STRING("~athe ~a");
    Qrule_scan_interval = STATIC_SYMBOL("RULE-SCAN-INTERVAL",AB_package);
    string_constant_13 = STATIC_STRING("~athe scan-interval");
    Qsimulation_initial_value = STATIC_SYMBOL("SIMULATION-INITIAL-VALUE",
	    AB_package);
    string_constant_14 = STATIC_STRING("~athe simulation-initial-value");
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    Qcell_index = STATIC_SYMBOL("CELL-INDEX",AB_package);
    Qinclude_denotation_for_block = 
	    STATIC_SYMBOL("INCLUDE-DENOTATION-FOR-BLOCK",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)3L,Qblock,Qcell_index,
	    Qinclude_denotation_for_block);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qdenote_cell_array_element,list_constant_3,
	    Qgeneric_method_lambda_list);
    array_constant_1 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)57344L);
    Qdenote_cell_array_element_for_root = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-ROOT",AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_root,
	    STATIC_FUNCTION(denote_cell_array_element_for_root,NIL,FALSE,3,3));
    Qroot = STATIC_SYMBOL("ROOT",AB_package);
    temp = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_root);
    set_get(Qroot,Qdenote_cell_array_element,temp);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp_1 = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp = CONS(Qroot,temp_1);
    mutate_global_property(Qdenote_cell_array_element,temp,
	    Qclasses_which_define);
    Qplace_reference = STATIC_SYMBOL("PLACE-REFERENCE",AB_package);
    gensymed_symbol = Qplace_reference;
    temp_1 = Defined_evaluation_value_types;
    set_skip_list_entry(temp_1,FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
	    FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
	    IFIX(Most_positive_fixnum)),Qplace_reference);
    Qtype_specification_of_defined_evaluation_type = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-OF-DEFINED-EVALUATION-TYPE",
	    AB_package);
    list_constant_1 = STATIC_CONS(Qplace_reference,Qnil);
    set_property_value_function(get_symbol_properties_function(Qplace_reference),
	    Qtype_specification_of_defined_evaluation_type,list_constant_1);
    if (The_type_description_of_place_reference_internals == UNBOUND)
	The_type_description_of_place_reference_internals = Nil;
    string_constant_18 = 
	    STATIC_STRING("43Dy8m83lWy1m83lWy8k1l8k0000001m1m83*gy9k1n8y83-55y1n83-9+y83-8wy83-8xyknk0k0");
    temp_1 = The_type_description_of_place_reference_internals;
    clear_optimized_constants();
    push_optimized_constant(Qvector);
    The_type_description_of_place_reference_internals = 
	    load_and_initialize_type_description(temp_1,
	    regenerate_optimized_constant(string_constant_18));
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_place_reference_internals_g2_struct = 
	    STATIC_SYMBOL("PLACE-REFERENCE-INTERNALS-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_place_reference_internals_g2_struct,
	    The_type_description_of_place_reference_internals,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qplace_reference_internals = STATIC_SYMBOL("PLACE-REFERENCE-INTERNALS",
	    AB_package);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qplace_reference_internals,
	    The_type_description_of_place_reference_internals,
	    Qtype_description_of_type);
    Qoutstanding_place_reference_internals_count = 
	    STATIC_SYMBOL("OUTSTANDING-PLACE-REFERENCE-INTERNALS-COUNT",
	    AB_package);
    Qplace_reference_internals_structure_memory_usage = 
	    STATIC_SYMBOL("PLACE-REFERENCE-INTERNALS-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_19 = STATIC_STRING("1q83lWy8s83-ity09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_place_reference_internals_count);
    push_optimized_constant(Qplace_reference_internals_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_19));
    Qchain_of_available_place_reference_internalss = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-PLACE-REFERENCE-INTERNALSS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_place_reference_internalss,
	    Chain_of_available_place_reference_internalss);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_place_reference_internalss,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qplace_reference_internals_count = 
	    STATIC_SYMBOL("PLACE-REFERENCE-INTERNALS-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qplace_reference_internals_count,
	    Place_reference_internals_count);
    record_system_variable(Qplace_reference_internals_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    if (Chain_of_available_place_reference_internalss_vector == UNBOUND)
	Chain_of_available_place_reference_internalss_vector = 
		make_thread_array(Nil);
    SET_SYMBOL_FUNCTION(Qplace_reference_internals_structure_memory_usage,
	    STATIC_FUNCTION(place_reference_internals_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_place_reference_internals_count,
	    STATIC_FUNCTION(outstanding_place_reference_internals_count,
	    NIL,FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_place_reference_internals_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_place_reference_internals,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qplace_reference_internals,
	    reclaim_structure_for_place_reference_internals_1);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qdefined_evaluation_type_reclaimer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-RECLAIMER",AB_package);
    Qreclaim_evaluation_place_reference = 
	    STATIC_SYMBOL("RECLAIM-EVALUATION-PLACE-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_evaluation_place_reference,
	    STATIC_FUNCTION(reclaim_evaluation_place_reference,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qplace_reference),
	    Qdefined_evaluation_type_reclaimer,
	    SYMBOL_FUNCTION(Qreclaim_evaluation_place_reference));
    Qdefined_evaluation_type_copier = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COPIER",AB_package);
    Qcopy_evaluation_place_reference = 
	    STATIC_SYMBOL("COPY-EVALUATION-PLACE-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qcopy_evaluation_place_reference,
	    STATIC_FUNCTION(copy_evaluation_place_reference,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qplace_reference),
	    Qdefined_evaluation_type_copier,
	    SYMBOL_FUNCTION(Qcopy_evaluation_place_reference));
    Qdefined_evaluation_type_validator = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-VALIDATOR",AB_package);
    Qvalidate_evaluation_place_reference = 
	    STATIC_SYMBOL("VALIDATE-EVALUATION-PLACE-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qvalidate_evaluation_place_reference,
	    STATIC_FUNCTION(validate_evaluation_place_reference,NIL,FALSE,
	    2,2));
    set_property_value_function(get_symbol_properties_function(Qplace_reference),
	    Qdefined_evaluation_type_validator,
	    SYMBOL_FUNCTION(Qvalidate_evaluation_place_reference));
    Qdefined_evaluation_type_comparitor = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-COMPARITOR",AB_package);
    Qevaluation_place_reference_eql = 
	    STATIC_SYMBOL("EVALUATION-PLACE-REFERENCE-EQL",AB_package);
    SET_SYMBOL_FUNCTION(Qevaluation_place_reference_eql,
	    STATIC_FUNCTION(evaluation_place_reference_eql,NIL,FALSE,2,2));
    set_property_value_function(get_symbol_properties_function(Qplace_reference),
	    Qdefined_evaluation_type_comparitor,
	    SYMBOL_FUNCTION(Qevaluation_place_reference_eql));
    array_constant_2 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)17L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_2,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)18L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)20L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)24L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)25L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)27L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)31L,(SI_Long)57344L);
    Qdefined_evaluation_type_writer = 
	    STATIC_SYMBOL("DEFINED-EVALUATION-TYPE-WRITER",AB_package);
    Qwrite_evaluation_place_reference = 
	    STATIC_SYMBOL("WRITE-EVALUATION-PLACE-REFERENCE",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_evaluation_place_reference,
	    STATIC_FUNCTION(write_evaluation_place_reference,NIL,FALSE,1,1));
    set_property_value_function(get_symbol_properties_function(Qplace_reference),
	    Qdefined_evaluation_type_writer,
	    SYMBOL_FUNCTION(Qwrite_evaluation_place_reference));
}
