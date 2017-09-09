/* gram6a.c
 * Input file:  grammar6a.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram6a.h"


/* FIX-STUB-INFO */
Object fix_stub_info(form)
    Object form;
{
    Object temp;

    x_note_fn_call(200,0);
    temp = copy_list_using_phrase_conses(CAR(form));
    return VALUES_1(nconc2(temp,copy_list_using_phrase_conses(CDR(form))));
}

static Object Qsolid;              /* solid */

/* FIX-CONNECTION-LINE-PATTERN-STUB-SPEC */
Object fix_connection_line_pattern_stub_spec(line_pattern)
    Object line_pattern;
{
    x_note_fn_call(200,1);
    if (EQ(line_pattern,Qsolid))
	return VALUES_1(Nil);
    else
	return VALUES_1(line_pattern);
}

static Object Qdefault;            /* default */

/* FIX-CONNECTION-ARROWS-STUB-SPEC */
Object fix_connection_arrows_stub_spec(connection_arrows)
    Object connection_arrows;
{
    x_note_fn_call(200,2);
    if (EQ(connection_arrows,Qdefault))
	return VALUES_1(Nil);
    else
	return VALUES_1(connection_arrows);
}

static Object Qorthogonal;         /* orthogonal */

/* FIX-CONNECTION-STYLE-STUB-SPEC */
Object fix_connection_style_stub_spec(style)
    Object style;
{
    x_note_fn_call(200,3);
    if (EQ(style,Qorthogonal))
	return VALUES_1(Nil);
    else
	return VALUES_1(style);
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* CONNECTION-INSTANCE-STYLE-EVALUATION-SETTER */
Object connection_instance_style_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(200,4);
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
			  list_constant))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_1,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_connection_instance_style_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_connection_instance_style_evaluation_setter:
    return result;
}

/* CONNECTION-INSTANCE-STYLE-EVALUATION-GETTER */
Object connection_instance_style_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(200,5);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

/* WRITE-CONNECTION-INSTANCE-STYLE-FROM-SLOT */
Object write_connection_instance_style_from_slot(connection_instance_style,
	    gensymed_symbol)
    Object connection_instance_style, gensymed_symbol;
{
    x_note_fn_call(200,6);
    return twrite(connection_instance_style);
}

static Object string_constant;     /* "inherited" */

static Object string_constant_1;   /* ", " */

/* WRITE-CROSS-SECTION-PATTERN-FROM-SLOT */
Object write_cross_section_pattern_from_slot(cross_section_pattern,
	    gensymed_symbol)
    Object cross_section_pattern, gensymed_symbol;
{
    Object temp, cross_section_regions, cross_section_stripes;
    Object cross_section_component, more_qm, ab_loop_list_;

    x_note_fn_call(200,7);
    if ( !TRUEP(cross_section_pattern))
	return tformat(1,string_constant);
    else {
	temp = CAAR(cross_section_pattern);
	cross_section_regions = CONSP(temp) ? CAR(cross_section_pattern) : Nil;
	temp = CAAR(cross_section_pattern);
	cross_section_stripes = CONSP(temp) ? CDR(cross_section_pattern) : 
		cross_section_pattern;
	if (cross_section_regions)
	    write_region_specification_list(cross_section_regions);
	temp = CAR(cross_section_stripes);
	if (ATOM(temp))
	    return write_cross_section_component(cross_section_stripes);
	else {
	    cross_section_component = Nil;
	    more_qm = Nil;
	    ab_loop_list_ = cross_section_stripes;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    cross_section_component = CAR(ab_loop_list_);
	    more_qm = CDR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    write_cross_section_component(cross_section_component);
	    if (more_qm)
		tformat(1,string_constant_1);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
    }
}

static Object string_constant_2;   /* "~(~a ~a~)" */

/* WRITE-CROSS-SECTION-COMPONENT */
Object write_cross_section_component(cross_section_component)
    Object cross_section_component;
{
    x_note_fn_call(200,8);
    return tformat(3,string_constant_2,CDR(cross_section_component),
	    CAR(cross_section_component));
}

/* WRITE-STUB-LENGTH-FROM-SLOT */
Object write_stub_length_from_slot(stub_length,gensymed_symbol)
    Object stub_length, gensymed_symbol;
{
    x_note_fn_call(200,9);
    if ( !TRUEP(stub_length))
	return tformat(1,string_constant);
    else
	return write_number_qm_from_slot(stub_length,Nil);
}

static Object Qinherited;          /* inherited */

/* COMPILE-STUB-LENGTH-FOR-SLOT */
Object compile_stub_length_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,10);
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
    if (EQ(parse_result,Qinherited))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

static Object Qforeground;         /* foreground */

static Object Qcopy;               /* copy */

static Object Qavailable_frame_vector;  /* available-frame-vector */

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* COMPILE-CROSS-SECTION-PATTERN-FOR-SLOT */
Object compile_cross_section_pattern_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Object superior_definition_qm, x2, sub_class_bit_vector, superior_qm;
    Object ab_loop_list_, compiled_cross_section_pattern, temp_1;
    Object cross_section_regions, cross_section_stripes, region_or_color;
    Object ab_loop_it_, ab_loop_desetq_, bad_region_or_color_or_metacolor_qm;
    Object temp_2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,11);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qinherited))
	return VALUES_1(Nil);
    else {
	if (INTEGERP(parse_result))
	    parse_result = phrase_cons(Qforeground,parse_result);
	if (CONSP(parse_result) && EQ(CAR(parse_result),Qcopy)) {
	    superior_definition_qm = Nil;
	    if (SIMPLE_VECTOR_P(definition) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(definition)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(definition,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(definition,(SI_Long)1L);
		gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? x2 : Qnil;
	    }
	    else
		gensymed_symbol = Nil;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Definition_class_description,
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
		superior_qm = Nil;
		ab_loop_list_ = ISVREF(definition,(SI_Long)21L);
	      next_loop:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop;
		superior_qm = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		superior_definition_qm = 
			lookup_global_or_kb_specific_property_value(superior_qm,
			Class_definition_gkbprop);
		if (SIMPLE_VECTOR_P(superior_definition_qm) && 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(superior_definition_qm)) 
			> (SI_Long)2L &&  
			!EQ(ISVREF(superior_definition_qm,(SI_Long)1L),
			Qavailable_frame_vector)) {
		    x2 = ISVREF(superior_definition_qm,(SI_Long)1L);
		    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
			    (SI_Long)0L),
			    Qg2_defstruct_structure_name_class_description_g2_struct) 
			    ? TRUEP(x2) : TRUEP(Qnil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(superior_definition_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Connection_definition_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_1 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_2 = (SI_Long)1L;
			gensymed_symbol_3 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_2 = gensymed_symbol_2 << 
				gensymed_symbol_3;
			gensymed_symbol_1 = gensymed_symbol_1 & 
				gensymed_symbol_2;
			temp = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp = TRUEP(Nil);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    temp = TRUEP(T);
		    goto end_1;
		}
		goto next_loop;
	      end_loop:
		temp = TRUEP(Nil);
		goto end_1;
		temp = TRUEP(Qnil);
	      end_1:;
	    }
	    else
		temp = TRUEP(Nil);
	    compiled_cross_section_pattern = temp ? 
		    ISVREF(superior_definition_qm,(SI_Long)30L) : 
		    slot_value_cons_1(slot_value_cons_1(Qforeground,
		    FIX((SI_Long)1L)),Nil);
	}
	else
	    compiled_cross_section_pattern = 
		    fix_up_cross_section_pattern(parse_result);
	temp_1 = CAAR(compiled_cross_section_pattern);
	cross_section_regions = CONSP(temp_1) ? 
		CAR(compiled_cross_section_pattern) : Nil;
	temp_1 = CAAR(compiled_cross_section_pattern);
	cross_section_stripes = CONSP(temp_1) ? 
		CDR(compiled_cross_section_pattern) : 
		compiled_cross_section_pattern;
	region_or_color = Nil;
	ab_loop_list_ = cross_section_stripes;
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	region_or_color = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ =  !TRUEP(color_or_metacolor_p(region_or_color)) && ( 
		!TRUEP(cross_section_regions) ||  
		!TRUEP(assq_function(region_or_color,
		cross_section_regions))) ? region_or_color : Nil;
	if (ab_loop_it_) {
	    bad_region_or_color_or_metacolor_qm = ab_loop_it_;
	    goto end_2;
	}
	goto next_loop_1;
      end_loop_1:
	bad_region_or_color_or_metacolor_qm = Qnil;
      end_2:;
	if (bad_region_or_color_or_metacolor_qm) {
	    temp_2 = Bad_phrase;
	    temp_1 = 
		    make_bad_region_text_string(bad_region_or_color_or_metacolor_qm);
	    return VALUES_2(temp_2,temp_1);
	}
	else
	    return VALUES_1(compiled_cross_section_pattern);
    }
}

static Object Qcm;                 /* \, */

static Object Qpolychrome;         /* polychrome */

/* FIX-UP-CROSS-SECTION-PATTERN */
Object fix_up_cross_section_pattern(cross_section_pattern_qm)
    Object cross_section_pattern_qm;
{
    Object temp;

    x_note_fn_call(200,12);
    if ( !TRUEP(cross_section_pattern_qm))
	return VALUES_1(Nil);
    else if (EQ(cross_section_pattern_qm,Qinherited))
	return VALUES_1(Nil);
    else if (EQ(CAR(cross_section_pattern_qm),Qcm))
	return VALUES_1(CDR(cross_section_pattern_qm));
    else {
	temp = CAR(cross_section_pattern_qm);
	if (ATOM(temp))
	    return phrase_cons(cross_section_pattern_qm,Nil);
	else {
	    temp = CAR(cross_section_pattern_qm);
	    if (EQ(CAR(temp),Qpolychrome)) {
		temp = CAR(cross_section_pattern_qm);
		temp = fix_up_cross_section_pattern(CDR(temp));
		return phrase_cons(temp,
			fix_up_cross_section_pattern(CDR(cross_section_pattern_qm)));
	    }
	    else
		return VALUES_1(cross_section_pattern_qm);
	}
    }
}

/* FLATTEN-PHRASE-TREE */
Object flatten_phrase_tree(tree)
    Object tree;
{
    Object temp;

    x_note_fn_call(200,13);
    if ( !TRUEP(tree))
	return VALUES_1(Nil);
    else if (ATOM(tree))
	return phrase_cons(tree,Nil);
    else if (CONSP(tree)) {
	temp = flatten_phrase_tree(CAR(tree));
	return VALUES_1(nconc2(temp,flatten_phrase_tree(CDR(tree))));
    }
    else
	return VALUES_1(Qnil);
}

static Object Qdash;               /* dash */

static Object list_constant_2;     /* # */

static Object Qab_dot;             /* dot */

static Object list_constant_3;     /* # */

static Object Qlong_dash;          /* long-dash */

static Object list_constant_4;     /* # */

static Object Qshort_dash;         /* short-dash */

static Object list_constant_5;     /* # */

static Object Qcoarse_dot;         /* coarse-dot */

static Object list_constant_6;     /* # */

static Object Qfine_dot;           /* fine-dot */

static Object list_constant_7;     /* # */

/* LOOKUP-STOCK-LINE-PATTERN-ELEMENT */
Object lookup_stock_line_pattern_element(symbol)
    Object symbol;
{
    x_note_fn_call(200,14);
    if (EQ(symbol,Qdash))
	return VALUES_1(list_constant_2);
    else if (EQ(symbol,Qab_dot))
	return VALUES_1(list_constant_3);
    else if (EQ(symbol,Qlong_dash))
	return VALUES_1(list_constant_4);
    else if (EQ(symbol,Qshort_dash))
	return VALUES_1(list_constant_5);
    else if (EQ(symbol,Qcoarse_dot))
	return VALUES_1(list_constant_6);
    else if (EQ(symbol,Qfine_dot))
	return VALUES_1(list_constant_7);
    else
	return VALUES_1(Qnil);
}

static Object array_constant;      /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

/* TWRITE-LINE-PATTERN-ELEMENT */
Object twrite_line_pattern_element(element)
    Object element;
{
    Object temp;

    x_note_fn_call(200,15);
    if (EQ(element,Qlong_dash))
	temp = twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)9L));
    else if (EQ(element,Qshort_dash))
	temp = twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)10L));
    else if (EQ(element,Qcoarse_dot))
	temp = twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)10L));
    else if (EQ(element,Qfine_dot))
	temp = twrite_beginning_of_wide_string(array_constant_3,
		FIX((SI_Long)8L));
    else
	temp = twrite(element);
    return VALUES_1(temp);
}

static Object Kabsolute;           /* :absolute */

/* CONNECTION-LINE-PATTERN-DASHES */
Object connection_line_pattern_dashes(connection_line_pattern_1)
    Object connection_line_pattern_1;
{
    x_note_fn_call(200,16);
    if ( !TRUEP(connection_line_pattern_1))
	return VALUES_1(Nil);
    else if (ATOM(connection_line_pattern_1))
	return lookup_stock_line_pattern_element(connection_line_pattern_1);
    else if (EQ(CAR(connection_line_pattern_1),Kabsolute))
	return VALUES_1(CDR(connection_line_pattern_1));
    else
	return VALUES_1(connection_line_pattern_1);
}

/* CONNECTION-LINE-PATTERN-EXPLICIT-P */
Object connection_line_pattern_explicit_p(connection_line_pattern_1)
    Object connection_line_pattern_1;
{
    x_note_fn_call(200,17);
    if (CONSP(connection_line_pattern_1)) {
	if (EQ(CAR(connection_line_pattern_1),Kabsolute))
	    return VALUES_1(FIXNUMP(CADR(connection_line_pattern_1)) ? T : 
		    Nil);
	else
	    return VALUES_1(FIXNUMP(CAR(connection_line_pattern_1)) ? T : Nil);
    }
    else
	return VALUES_1(Nil);
}

/* CONNECTION-LINE-PATTERN-ABSOLUTE-P */
Object connection_line_pattern_absolute_p(connection_line_pattern_1)
    Object connection_line_pattern_1;
{
    x_note_fn_call(200,18);
    if (CONSP(connection_line_pattern_1))
	return VALUES_1(EQ(CAR(connection_line_pattern_1),Kabsolute) ? T : 
		Nil);
    else
	return VALUES_1(Nil);
}

/* VALID-DASH-LENGTH */
Object valid_dash_length(length_1)
    Object length_1;
{
    x_note_fn_call(200,19);
    if (IFIX(length_1) > (SI_Long)0L)
	return VALUES_1(FIXNUM_LE(length_1,Maximum_connection_dash_length) 
		? T : Nil);
    else
	return VALUES_1(Nil);
}

/* VALID-DASH-SYMBOL */
Object valid_dash_symbol(symbol)
    Object symbol;
{
    x_note_fn_call(200,20);
    return memq_function(symbol,CDDR(Stock_line_pattern_type));
}

/* VALID-DASH-ELEMENT */
Object valid_dash_element(element)
    Object element;
{
    x_note_fn_call(200,21);
    if (FIXNUMP(element))
	return valid_dash_length(element);
    else if (SYMBOLP(element))
	return valid_dash_symbol(element);
    else
	return VALUES_1(Nil);
}

static Object list_constant_8;     /* # */

static Object string_constant_3;   /* "At most ~a line pattern elements are allowed." */

static Object string_constant_4;   /* "Each length must be a positive integer less than ~a." */

/* COMPILE-CONNECTION-LINE-PATTERN-FOR-SLOT */
Object compile_connection_line_pattern_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, temp_1, element, ab_loop_list_, ab_loop_it_;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,22);
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
    if ( !TRUEP(parse_result) || EQUAL(parse_result,list_constant_8))
	return VALUES_1(Nil);
    else if (ATOM(parse_result))
	return VALUES_1(parse_result);
    else if ( !TRUEP(CDR(parse_result)))
	return VALUES_1(CAR(parse_result));
    else if (FIXNUM_GT(length(connection_line_pattern_dashes(parse_result)),
	    Maximum_connection_dash_count)) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_3,
		Maximum_connection_dash_count);
	return VALUES_2(temp,temp_1);
    }
    else {
	element = Nil;
	ab_loop_list_ = connection_line_pattern_dashes(parse_result);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = NUMBERP(element) ? ( 
		!TRUEP(valid_dash_length(element)) ? T : Nil) : Qnil;
	if (ab_loop_it_) {
	    temp_2 = TRUEP(ab_loop_it_);
	    goto end_1;
	}
	goto next_loop;
      end_loop:
	temp_2 = TRUEP(Qnil);
      end_1:;
	if (temp_2) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(2,string_constant_4,
		    FIXNUM_ADD1(Maximum_connection_dash_length));
	    return VALUES_2(temp,temp_1);
	}
	else
	    return VALUES_1(parse_result);
    }
}

static Object array_constant_4;    /* # */

static Object string_constant_5;   /* "~d on, ~d off" */

static Object array_constant_5;    /* # */

static Object Qtwrite_line_pattern_element;  /* twrite-line-pattern-element */

static Object array_constant_6;    /* # */

/* WRITE-CONNECTION-LINE-PATTERN-FROM-SLOT */
Object write_connection_line_pattern_from_slot(line_pattern,gensymed_symbol)
    Object line_pattern, gensymed_symbol;
{
    Object dashes, temp, on, off, more, ab_loop_list_;

    x_note_fn_call(200,23);
    if ( !TRUEP(line_pattern))
	return twrite_beginning_of_wide_string(array_constant_4,
		FIX((SI_Long)5L));
    else if (ATOM(line_pattern))
	return twrite_line_pattern_element(line_pattern);
    else {
	dashes = connection_line_pattern_dashes(line_pattern);
	temp = FIRST(dashes);
	if (NUMBERP(temp)) {
	    on = Nil;
	    off = Nil;
	    more = Nil;
	    ab_loop_list_ = dashes;
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	  next_loop:
	    on = CAR(ab_loop_list_);
	    temp = CDR(ab_loop_list_);
	    off = CAR(temp);
	    temp = CDR(ab_loop_list_);
	    more = CDR(temp);
	    tformat(3,string_constant_5,on,off);
	    if (more)
		twrite_beginning_of_wide_string(array_constant_5,
			FIX((SI_Long)2L));
	    ab_loop_list_ = CDDR(ab_loop_list_);
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    goto next_loop;
	  end_loop:;
	}
	else
	    twrite_list_function(dashes,
		    SYMBOL_FUNCTION(Qtwrite_line_pattern_element),Nil,
		    string_constant_1,string_constant_1);
	if (connection_line_pattern_absolute_p(line_pattern))
	    return twrite_beginning_of_wide_string(array_constant_6,
		    FIX((SI_Long)26L));
	else
	    return VALUES_1(Nil);
    }
}

static Object Qline_pattern;       /* line-pattern */

/* PUT-LINE-PATTERN */
Object put_line_pattern(connection_frame_1,value,initializing_qm)
    Object connection_frame_1, value, initializing_qm;
{
    Object connection, workspace_qm;

    x_note_fn_call(200,24);
    set_non_savable_lookup_slot_value(connection_frame_1,Qline_pattern,value);
    if ( !TRUEP(initializing_qm)) {
	connection = ISVREF(connection_frame_1,(SI_Long)21L);
	workspace_qm = workspace_of_connection_qm(connection);
	update_connection_images(T,workspace_qm,connection);
	change_connection_attribute(connection,Qline_pattern,
		copy_for_slot_value(value));
	update_connection_images(Nil,workspace_qm,connection);
    }
    return VALUES_1(value);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

static Object Qab_structure;       /* structure */

static Object Qpattern;            /* pattern */

static Object string_constant_6;   /* "A line-pattern specified with a structure must contain a pattern attribute which must be a sequence." */

static Object string_constant_7;   /* "A pattern in a line-pattern structure must contain an even number of elements" */

static Object Qnot_scaled_by_line_width;  /* not-scaled-by-line-width */

static Object Qtruth_value;        /* truth-value */

static Object string_constant_8;   /* "A line-pattern specified with a structure must contain a not-scaled-by-line-width attribute which must be a truth-value." */

static Object string_constant_9;   /* "A numeric line-pattern must have even length." */

static Object string_constant_10;  /* "The line-pattern contains invalid elements." */

/* CONNECTION-LINE-PATTERN-EVALUATION-SETTER */
Object connection_line_pattern_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, gensymed_symbol_1;
    Object held_vector, elt_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_2, validated_elt, phrase, element, ab_loop_it_;
    SI_Long next_index, length_1, gensymed_symbol_2;
    char temp_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(200,25);
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
			  list_constant_9))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_10,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_connection_line_pattern_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (EQ(evaluation_value,Qsolid))
	result = VALUES_1(Nil);
    else if (ATOM(evaluation_value))
	result = VALUES_1(evaluation_value);
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qab_structure)) {
	gensymed_symbol = evaluation_value;
	temp_1 = estructure_slot(gensymed_symbol,Qpattern,Nil);
	if ( !(CONSP(temp_1) && EQ(M_CDR(estructure_slot(gensymed_symbol,
		Qpattern,Nil)),Qsequence))) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant_6);
	    result = VALUES_2(temp,temp_1);
	}
	else if ((SI_Long)1L == ((SI_Long)1L & 
		IFIX(FIXNUM_SUB1(ISVREF(M_CAR(estructure_slot(gensymed_symbol,
		Qpattern,Nil)),(SI_Long)1L))))) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant_7);
	    result = VALUES_2(temp,temp_1);
	}
	else {
	    temp_1 = estructure_slot(gensymed_symbol,
		    Qnot_scaled_by_line_width,Nil);
	    if ( !(CONSP(temp_1) && 
		    EQ(M_CDR(estructure_slot(gensymed_symbol,
		    Qnot_scaled_by_line_width,Nil)),Qtruth_value))) {
		temp = Bad_phrase;
		temp_1 = tformat_text_string(1,string_constant_8);
		result = VALUES_2(temp,temp_1);
	    }
	    else {
		gensymed_symbol_1 = estructure_slot(gensymed_symbol,
			Qpattern,Nil);
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		elt_1 = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		held_vector = M_CAR(gensymed_symbol_1);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop:
		if (next_index >= length_1)
		    goto end_loop;
		elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		validated_elt = elt_2 ? 
			validate_item_or_evaluation_value(elt_2,Nil,Nil) : Nil;
		next_index = next_index + (SI_Long)1L;
		elt_1 = validated_elt;
		ab_loopvar__2 = phrase_cons(elt_1,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop;
	      end_loop:
		phrase = ab_loopvar_;
		goto end_1;
		phrase = Qnil;
	      end_1:;
		if (evaluation_truth_value_is_true_p(estructure_slot(gensymed_symbol,
			Qnot_scaled_by_line_width,Nil)))
		    result = phrase_cons(Kabsolute,phrase);
		else
		    result = VALUES_1(phrase);
	    }
	}
    }
    else if ( !(CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
	    Qsequence)))
	result = VALUES_1(Nil);
    else {
	gensymed_symbol = M_CAR(evaluation_value);
	gensymed_symbol_2 = (SI_Long)0L + (SI_Long)1L;
	temp_1 = FIXNUM_LE(ISVREF(M_CAR(evaluation_value),(SI_Long)1L),
		Maximum_in_place_array_size) ? 
		ISVREF(M_CAR(evaluation_value),gensymed_symbol_2 + 
		IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(gensymed_symbol,(gensymed_symbol_2 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),gensymed_symbol_2 & 
		(SI_Long)1023L);
	if (NUMBERP(temp_1) ? (SI_Long)1L == ((SI_Long)1L & 
		IFIX(FIXNUM_SUB1(ISVREF(M_CAR(evaluation_value),
		(SI_Long)1L)))) : TRUEP(Nil)) {
	    temp = Bad_phrase;
	    temp_1 = tformat_text_string(1,string_constant_9);
	    result = VALUES_2(temp,temp_1);
	}
	else {
	    gensymed_symbol = evaluation_value;
	    held_vector = Nil;
	    next_index = (SI_Long)1L;
	    length_1 = (SI_Long)0L;
	    element = Nil;
	    ab_loop_it_ = Nil;
	    held_vector = M_CAR(gensymed_symbol);
	    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	  next_loop_1:
	    if (next_index >= length_1)
		goto end_loop_1;
	    elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		    Maximum_in_place_array_size) ? ISVREF(held_vector,
		    next_index + IFIX(Managed_array_index_offset)) : 
		    ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	    validated_elt = elt_2 ? 
		    validate_item_or_evaluation_value(elt_2,Nil,Nil) : Nil;
	    next_index = next_index + (SI_Long)1L;
	    element = validated_elt;
	    ab_loop_it_ =  !TRUEP(valid_dash_element(element)) ? T : Nil;
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = TRUEP(Qnil);
	  end_2:;
	    if (temp_2) {
		temp = Bad_phrase;
		temp_1 = tformat_text_string(1,string_constant_10);
		result = VALUES_2(temp,temp_1);
	    }
	    else {
		gensymed_symbol = evaluation_value;
		held_vector = Nil;
		next_index = (SI_Long)1L;
		length_1 = (SI_Long)0L;
		elt_1 = Nil;
		ab_loopvar_ = Nil;
		ab_loopvar__1 = Nil;
		ab_loopvar__2 = Nil;
		held_vector = M_CAR(gensymed_symbol);
		length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
	      next_loop_2:
		if (next_index >= length_1)
		    goto end_loop_2;
		elt_2 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
			Maximum_in_place_array_size) ? ISVREF(held_vector,
			next_index + IFIX(Managed_array_index_offset)) : 
			ISVREF(ISVREF(held_vector,(next_index >>  -  - 
			(SI_Long)10L) + (SI_Long)2L),next_index & 
			(SI_Long)1023L);
		validated_elt = elt_2 ? 
			validate_item_or_evaluation_value(elt_2,Nil,Nil) : Nil;
		next_index = next_index + (SI_Long)1L;
		elt_1 = validated_elt;
		ab_loopvar__2 = phrase_cons(elt_1,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
		goto next_loop_2;
	      end_loop_2:
		result = VALUES_1(ab_loopvar_);
		goto end_3;
		result = VALUES_1(Qnil);
	      end_3:;
	    }
	}
    }
  end_connection_line_pattern_evaluation_setter:
    return result;
}

/* CONNECTION-LINE-PATTERN-EVALUATION-GETTER */
Object connection_line_pattern_evaluation_getter(line_pattern,frame,
	    slot_description)
    Object line_pattern, frame, slot_description;
{
    Object temp, elt_1, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1;

    x_note_fn_call(200,26);
    if ( !TRUEP(line_pattern))
	temp = Qsolid;
    else if (ATOM(line_pattern))
	temp = line_pattern;
    else if ( !TRUEP(CDR(line_pattern)))
	temp = CAR(line_pattern);
    else if (connection_line_pattern_absolute_p(line_pattern)) {
	temp = 
		allocate_evaluation_sequence(copy_list_using_eval_conses_1(CDR(line_pattern)));
	temp = allocate_evaluation_structure(eval_list_4(Qpattern,temp,
		Qnot_scaled_by_line_width,Evaluation_true_value));
    }
    else {
	elt_1 = Nil;
	ab_loop_list_ = line_pattern;
	gensymed_symbol = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = eval_cons_1(elt_1,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    gensymed_symbol = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop;
      end_loop:
	temp = allocate_evaluation_sequence(gensymed_symbol);
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qnarrow;             /* narrow */

static Object Qwide;               /* wide */

static Object Qsmall;              /* small */

static Object Qlarge;              /* large */

static Object Qthin;               /* thin */

static Object Qthick;              /* thick */

static Object Qfilled;             /* filled */

/* ANTONYM-OF */
Object antonym_of(adjective)
    Object adjective;
{
    x_note_fn_call(200,27);
    if (EQ(adjective,Qnarrow))
	return VALUES_1(Qwide);
    else if (EQ(adjective,Qwide))
	return VALUES_1(Qnarrow);
    else if (EQ(adjective,Qsmall))
	return VALUES_1(Qlarge);
    else if (EQ(adjective,Qlarge))
	return VALUES_1(Qsmall);
    else if (EQ(adjective,Qthin))
	return VALUES_1(Qthick);
    else if (EQ(adjective,Qthick))
	return VALUES_1(Qthin);
    else if (EQ(adjective,Qfilled))
	return VALUES_1(Qopen);
    else if (EQ(adjective,Qopen))
	return VALUES_1(Qfilled);
    else
	return VALUES_1(Nil);
}

static Object Qcircle;             /* circle */

static Object string_constant_11;  /* "Wide or narrow used with circle." */

static Object Qvery;               /* very */

static Object string_constant_12;  /* "The modifier ~a is duplicated." */

static Object string_constant_13;  /* "The modifiers ~a and ~a conflict." */

/* COMPILE-CONNECTION-ARROWS-FOR-SLOT */
Object compile_connection_arrows_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Object temp, arrow, ab_loop_list_, placement, shape, adjectives;
    Object ellipse_qm, duplicate_qm, conflict_qm, ab_loop_desetq_, temp_2, adj;
    Object rest_1, ab_loop_list__1;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,28);
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
    if (ATOM(parse_result))
	return VALUES_1(parse_result);
    else {
	if ( !TRUEP(CDR(parse_result))) {
	    temp = CAR(parse_result);
	    temp_1 = ATOM(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(CAR(parse_result));
	else {
	    arrow = Nil;
	    ab_loop_list_ = parse_result;
	    placement = Nil;
	    shape = Nil;
	    adjectives = Nil;
	    ellipse_qm = Nil;
	    duplicate_qm = Nil;
	    conflict_qm = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    arrow = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_desetq_ = CONSP(arrow) ? arrow : Qnil;
	    placement = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    shape = CAR(temp);
	    temp = CDR(ab_loop_desetq_);
	    adjectives = CDR(temp);
	    if (EQ(shape,Qcircle)) {
		temp = memq_function(Qnarrow,adjectives);
		if (temp);
		else
		    temp = memq_function(Qwide,adjectives);
		ellipse_qm = temp;
	    }
	    else
		ellipse_qm = Nil;
	    if (ellipse_qm) {
		temp_2 = Bad_phrase;
		temp = tformat_text_string(1,string_constant_11);
		return VALUES_2(temp_2,temp);
	    }
	    adj = Nil;
	    rest_1 = Nil;
	    ab_loop_list__1 = adjectives;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    adj = CAR(ab_loop_list__1);
	    rest_1 = CDR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !EQ(adj,Qvery) && memq_function(adj,rest_1)) {
		duplicate_qm = adj;
		goto end_1;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    duplicate_qm = Qnil;
	  end_1:;
	    if (duplicate_qm) {
		temp_2 = Bad_phrase;
		temp = tformat_text_string(2,string_constant_12,duplicate_qm);
		return VALUES_2(temp_2,temp);
	    }
	    adj = Nil;
	    rest_1 = Nil;
	    ab_loop_list__1 = adjectives;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_2;
	    adj = CAR(ab_loop_list__1);
	    rest_1 = CDR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !EQ(adj,Qvery)) {
		temp = antonym_of(adj);
		temp_1 = TRUEP(memq_function(temp,rest_1));
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		conflict_qm = adj;
		goto end_2;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    conflict_qm = Qnil;
	  end_2:;
	    if (conflict_qm) {
		temp_2 = Bad_phrase;
		temp = conflict_qm;
		temp = tformat_text_string(3,string_constant_13,temp,
			antonym_of(conflict_qm));
		return VALUES_2(temp_2,temp);
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_1(parse_result);
	    return VALUES_1(Qnil);
	}
    }
}

static Object array_constant_7;    /* # */

static Object Qnone;               /* none */

static Object array_constant_8;    /* # */

/* WRITE-CONNECTION-ARROWS-FROM-SLOT */
Object write_connection_arrows_from_slot(arrows,gensymed_symbol)
    Object arrows, gensymed_symbol;
{
    Object arrow, more, ab_loop_list_;

    x_note_fn_call(200,29);
    if ( !TRUEP(arrows))
	return twrite_beginning_of_wide_string(array_constant_7,
		FIX((SI_Long)7L));
    else if (EQ(arrows,Qnone))
	return twrite_beginning_of_wide_string(array_constant_8,
		FIX((SI_Long)4L));
    else if (ATOM(arrows))
	return twrite_symbol(1,arrows);
    else {
	arrow = Nil;
	more = Nil;
	ab_loop_list_ = arrows;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arrow = CAR(ab_loop_list_);
	more = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	twrite_connection_arrow(arrow);
	if (more)
	    twrite_beginning_of_wide_string(array_constant_5,FIX((SI_Long)2L));
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_14;  /* "" */

static Object array_constant_9;    /* # */

static Object Qoutput;             /* output */

static Object string_constant_15;  /* " at the output end" */

static Object Qinput;              /* input */

static Object string_constant_16;  /* " at the input end" */

static Object Qboth;               /* both */

static Object string_constant_17;  /* " at both ends" */

/* TWRITE-CONNECTION-ARROW */
Object twrite_connection_arrow(arrow)
    Object arrow;
{
    Object gensymed_symbol, placement, shape, adjectives, temp;

    x_note_fn_call(200,30);
    if (ATOM(arrow))
	return twrite_symbol(1,arrow);
    else {
	gensymed_symbol = arrow;
	placement = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	shape = CAR(gensymed_symbol);
	adjectives = CDR(gensymed_symbol);
	if (adjectives) {
	    write_symbol_list(2,adjectives,string_constant_14);
	    twrite_beginning_of_wide_string(array_constant_9,FIX((SI_Long)1L));
	}
	twrite_symbol(1,shape);
	if (EQ(placement,Qoutput))
	    temp = string_constant_15;
	else if (EQ(placement,Qinput))
	    temp = string_constant_16;
	else if (EQ(placement,Qboth))
	    temp = string_constant_17;
	else if (EQ(placement,Qdefault))
	    temp = string_constant_14;
	else
	    temp = Qnil;
	return twrite(temp);
    }
}

static Object Qconnection_arrows;  /* connection-arrows */

/* PUT-CONNECTION-ARROWS */
Object put_connection_arrows(connection_frame_1,value,initializing_qm)
    Object connection_frame_1, value, initializing_qm;
{
    Object connection, workspace_qm;

    x_note_fn_call(200,31);
    set_non_savable_lookup_slot_value(connection_frame_1,
	    Qconnection_arrows,value);
    if ( !TRUEP(initializing_qm)) {
	connection = ISVREF(connection_frame_1,(SI_Long)21L);
	workspace_qm = workspace_of_connection_qm(connection);
	update_connection_images(T,workspace_qm,connection);
	change_connection_attribute(connection,Qconnection_arrows,
		copy_for_slot_value(value));
	update_connection_images(Nil,workspace_qm,connection);
    }
    return VALUES_1(value);
}

Object Connection_arrow_permitted_scales = UNBOUND;

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

/* CONNECTION-ARROWS-EVALUATION-SETTER */
Object connection_arrows_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object struct_1, arrow_qm, ab_loop_it_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(200,32);
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
			  list_constant_11))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_12,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_connection_arrows_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if ( !TRUEP(evaluation_value))
	result = VALUES_1(Qnone);
    else if (EQ(evaluation_value,Qdefault))
	result = VALUES_1(Nil);
    else if (ATOM(evaluation_value))
	result = VALUES_1(evaluation_value);
    else if (CONSP(evaluation_value) && EQ(M_CDR(evaluation_value),
		Qsequence)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	struct_1 = Nil;
	arrow_qm = Nil;
	ab_loop_it_ = Nil;
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
	struct_1 = validated_elt;
	arrow_qm = compute_connection_arrows_spec(struct_1);
	if (text_string_p(arrow_qm)) {
	    result = VALUES_2(Bad_phrase,arrow_qm);
	    goto end_1;
	}
	ab_loop_it_ = arrow_qm;
	if (ab_loop_it_) {
	    ab_loopvar__2 = phrase_cons(ab_loop_it_,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	result = VALUES_1(ab_loopvar_);
	goto end_1;
	result = VALUES_1(Qnil);
      end_1:;
    }
    else
	result = VALUES_1(Qnil);
  end_connection_arrows_evaluation_setter:
    return result;
}

/* CONNECTION-ARROWS-EVALUATION-GETTER */
Object connection_arrows_evaluation_getter(spec,frame,slot_description)
    Object spec, frame, slot_description;
{
    Object temp, arrow, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(200,33);
    if ( !TRUEP(spec))
	temp = Qdefault;
    else if (ATOM(spec))
	temp = spec;
    else {
	arrow = Nil;
	ab_loop_list_ = spec;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	arrow = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		eval_cons_1(compute_connection_arrows_structure(arrow),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	temp = ab_loopvar_;
	goto end_1;
	temp = Qnil;
      end_1:;
	temp = allocate_evaluation_sequence(temp);
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object Qshape;              /* shape */

static Object Qplacement;          /* placement */

static Object Qscale;              /* scale */

static Object Qfloat_array;        /* float-array */

static Object Qaspect_ratio;       /* aspect-ratio */

static Object Qline_weight;        /* line-weight */

/* COMPUTE-CONNECTION-ARROWS-STRUCTURE */
Object compute_connection_arrows_structure(arrow)
    Object arrow;
{
    Object shape, placement, thick, width, height, filled, gensymed_symbol;
    Object gensymed_symbol_1, temp, amf_available_array_cons_qm, amf_array;
    Object temp_1, amf_result, new_float, temp_2;
    double aref_new_value, temp_3, temp_4;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(200,34);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	result = decode_arrow_spec_1(arrow);
	MVS_6(result,shape,placement,thick,width,height,filled);
	gensymed_symbol = make_eval_list_1(FIX((SI_Long)12L));
	gensymed_symbol_1 = gensymed_symbol;
	M_CAR(gensymed_symbol_1) = Qshape;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = shape;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qplacement;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = placement;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qfilled;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	temp = filled ? Evaluation_true_value : Evaluation_false_value;
	M_CAR(gensymed_symbol_1) = temp;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qscale;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
	temp_2 = expt2(width);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	M_CAR(gensymed_symbol_1) = new_float;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qaspect_ratio;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
	temp_2 = expt2(height);
	temp_3 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	temp_2 = expt2(width);
	temp_4 = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	aref_new_value = temp_3 / temp_4;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	M_CAR(gensymed_symbol_1) = new_float;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	M_CAR(gensymed_symbol_1) = Qline_weight;
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
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
	temp_2 = expt2(thick);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_2);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	M_CAR(gensymed_symbol_1) = new_float;
	result = allocate_evaluation_structure(gensymed_symbol);
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

static Object float_constant;      /* 1.0 */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_18;  /* "The ~a must be one of " */

static Object Qtwrite;             /* twrite */

static Object string_constant_19;  /* " or " */

static Object list_constant_13;    /* # */

/* COMPUTE-CONNECTION-ARROWS-SPEC */
Object compute_connection_arrows_spec(struct_1)
    Object struct_1;
{
    Object shape, placement, filled, scale_qm, aspect_ratio_qm, line_weight_qm;
    Object offending_slot_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, temp_1, temp_2;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(200,35);
    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	shape = estructure_slot(struct_1,Qshape,Nil);
	placement = estructure_slot(struct_1,Qplacement,Qdefault);
	filled = estructure_slot(struct_1,Qfilled,Nil);
	scale_qm = connection_arrows_scale_index(estructure_slot(struct_1,
		Qscale,float_constant));
	aspect_ratio_qm = 
		connection_arrows_scale_index(estructure_slot(struct_1,
		Qaspect_ratio,float_constant));
	line_weight_qm = 
		connection_arrows_scale_index(estructure_slot(struct_1,
		Qline_weight,float_constant));
	if ( !TRUEP(scale_qm))
	    offending_slot_qm = Qscale;
	else if ( !TRUEP(aspect_ratio_qm))
	    offending_slot_qm = Qaspect_ratio;
	else if ( !TRUEP(line_weight_qm))
	    offending_slot_qm = Qline_weight;
	else
	    offending_slot_qm = Qnil;
	if (offending_slot_qm) {
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
		      tformat(2,string_constant_18,offending_slot_qm);
		      twrite_list_function(Connection_arrow_permitted_scales,
			      SYMBOL_FUNCTION(Qtwrite),Nil,
			      string_constant_19,string_constant_1);
		      result = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else if (memq_function(placement,list_constant_13) &&  
		!TRUEP(filled) && FIXNUM_EQ(scale_qm,aspect_ratio_qm) && 
		FIXNUM_EQ(aspect_ratio_qm,line_weight_qm) && 
		IFIX(line_weight_qm) == (SI_Long)0L)
	    result = VALUES_1(shape);
	else if ( !TRUEP(shape))
	    result = VALUES_1(Nil);
	else {
	    temp = CONSP(filled) && EQ(M_CDR(filled),Qtruth_value) && 
		    EQ(M_CAR(filled),Truth) ? phrase_cons(Qfilled,Nil) : Nil;
	    temp_1 = connection_arrows_adjective_phrase(Qlarge,scale_qm);
	    temp_2 = connection_arrows_adjective_phrase(Qwide,aspect_ratio_qm);
	    result = phrase_cons(placement,phrase_cons(shape,nconc2(temp,
		    nconc2(temp_1,nconc2(temp_2,
		    connection_arrows_adjective_phrase(Qthick,
		    line_weight_qm))))));
	}
    }
    POP_LOCAL_ALLOCATION(0,0);
    return result;
}

/* CONNECTION-ARROWS-ADJECTIVE-PHRASE */
Object connection_arrows_adjective_phrase(adjective,index_1)
    Object adjective, index_1;
{
    x_note_fn_call(200,36);
    if ( !(FIXNUMP(index_1) && FIXNUM_LE(FIX((SI_Long)-128L),index_1) && 
	    FIXNUM_LE(index_1,FIX((SI_Long)127L))))
	return VALUES_1(Nil);
    else
	switch (INTEGER_TO_CHAR(index_1)) {
	  case -2:
	    return phrase_list_2(Qvery,antonym_of(adjective));
	  case -1:
	    return phrase_cons(antonym_of(adjective),Nil);
	  case 0:
	    return VALUES_1(Nil);
	  case 1:
	    return phrase_cons(adjective,Nil);
	  case 2:
	    return phrase_list_2(Qvery,adjective);
	  default:
	    return VALUES_1(Nil);
	}
}

static Object float_constant_1;    /* 0.01 */

/* CONNECTION-ARROWS-SCALE-INDEX */
Object connection_arrows_scale_index(scale)
    Object scale;
{
    Object pos_qm;

    x_note_fn_call(200,37);
    pos_qm = position_in_float_list(scale,
	    Connection_arrow_permitted_scales,float_constant_1);
    if (pos_qm)
	return VALUES_1(FIX(IFIX(pos_qm) - (SI_Long)2L));
    else
	return VALUES_1(Nil);
}

/* EXPT2 */
Object expt2(n_1)
    Object n_1;
{
    Object gensymed_symbol_1;
    SI_Long gensymed_symbol;

    x_note_fn_call(200,38);
    if (IFIX(n_1) == (SI_Long)0L)
	return VALUES_1(float_constant);
    else if (IFIX(n_1) > (SI_Long)0L)
	return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(ash(FIX((SI_Long)1L),
		n_1))));
    else {
	gensymed_symbol = (SI_Long)1L;
	gensymed_symbol_1 = FIXNUM_NEGATE(n_1);
	return reciprocal(DOUBLE_TO_DOUBLE_FLOAT((double)IFIX(ash(FIX(gensymed_symbol),
		gensymed_symbol_1))));
    }
}

/* POSITION-IN-FLOAT-LIST */
Object position_in_float_list(float_1,list_1,eps)
    Object float_1, list_1, eps;
{
    Object f, v, ab_loop_list_, ab_loop_iter_flag_;
    SI_Long n_1;
    char temp_2;
    double temp, temp_1, arg, arg_1, arg_2;

    x_note_fn_call(200,39);
    f = INLINE_DOUBLE_FLOAT_VECTOR_P(float_1) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(float_1)) == (SI_Long)1L ? 
	    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(float_1,(SI_Long)0L)) : 
	    float_1;
    v = Nil;
    ab_loop_list_ = list_1;
    n_1 = (SI_Long)0L;
    ab_loop_iter_flag_ = T;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    v = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_iter_flag_))
	n_1 = n_1 + (SI_Long)1L;
    if (FLOATP(v)) {
	temp = DOUBLE_FLOAT_TO_DOUBLE(v);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(eps);
	arg = temp - temp_1;
	arg_1 = DOUBLE_FLOAT_TO_DOUBLE(f);
	temp = DOUBLE_FLOAT_TO_DOUBLE(v);
	temp_1 = DOUBLE_FLOAT_TO_DOUBLE(eps);
	arg_2 = temp + temp_1;
	temp_2 = arg < arg_1 && arg_1 < arg_2 &&  
		!inline_nanp_for_comparison(arg) &&  
		!inline_nanp_for_comparison(arg_1) ?  
		!inline_nanp_for_comparison(arg_2) : TRUEP(Qnil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2)
	return VALUES_1(FIX(n_1));
    ab_loop_iter_flag_ = Nil;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object System_class_overrides_for_object_definition = UNBOUND;

Object System_class_overrides_for_class_definition = UNBOUND;

/* SECOND-NONE */
Object second_none(form)
    Object form;
{
    x_note_fn_call(200,40);
    if (EQ(SECOND(form),Qnone))
	return phrase_list_2(FIRST(form),Nil);
    else
	return VALUES_1(form);
}

/* SIMULATION-FRAME?-EVALUATION-GETTER */
Object simulation_frame_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(200,41);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object Qsimulation_subtable;  /* simulation-subtable */

/* MAKE-SIMULATION-SUBTABLE-AND-INSTALL */
Object make_simulation_subtable_and_install()
{
    Object simulation_subtable;

    x_note_fn_call(200,42);
    simulation_subtable = make_frame(Qsimulation_subtable);
    return body_of_put_for_simulation_frame(Frame_being_made,
	    simulation_subtable,T);
}

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

/* MAKE-SIMULATION-SUBTABLE-WITH-SPECIFIC-CLASS-AND-INSTALL */
Object make_simulation_subtable_with_specific_class_and_install(class_1)
    Object class_1;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object simulation_subtable;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Object result;

    x_note_fn_call(200,43);
    skip_list = CDR(Symbol_properties_table);
    key_value = class_1;
    key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_2:
    if ( !TRUEP(marked))
	goto end_loop_1;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_2;
  end_loop_1:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if ( !TRUEP(gensymed_symbol)) {
	gensymed_symbol = class_1;
	temp = Symbol_properties_table;
	temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		IFIX(Most_positive_fixnum));
	tail = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		Nil);
	head = 
		make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
	    gensymed_symbol_2 = new_cons;
	}
	else
	    gensymed_symbol_2 = Nil;
	if ( !TRUEP(gensymed_symbol_2))
	    gensymed_symbol_2 = replenish_lookup_cons_pool();
	M_CAR(gensymed_symbol_2) = head;
	M_CDR(gensymed_symbol_2) = tail;
	inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),Qeq,
		Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
    }
    global_properties = gensymed_symbol;
    skip_list = CDR(global_properties);
    key_value = Current_kb_specific_property_list_property_name;
    key_hash_value = 
	    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
	    & IFIX(Most_positive_fixnum);
    bottom_level = (SI_Long)0L;
    marked = Nil;
    pred = M_CAR(skip_list);
    curr = Nil;
    succ = Nil;
    level = (SI_Long)31L;
    ab_loop_bind_ = bottom_level;
  next_loop_3:
    if (level < ab_loop_bind_)
	goto end_loop_3;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
  next_loop_4:
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
  next_loop_5:
    if ( !TRUEP(marked))
	goto end_loop_4;
    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
    temp = ATOMIC_REF_OBJECT(reference);
    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
    result = VALUES_2(temp,temp_1);
    MVS_2(result,succ,marked);
    goto next_loop_5;
  end_loop_4:
    entry_hash = ISVREF(curr,(SI_Long)1L);
    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
	    key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	pred = curr;
	curr = succ;
    }
    else
	goto end_2;
    goto next_loop_4;
  end_loop_5:
  end_2:
    level = level - (SI_Long)1L;
    goto next_loop_3;
  end_loop_3:;
    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
	    (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
	    (SI_Long)3L) : Nil) : Nil;
    if (kb_properties);
    else
	kb_properties = Nil;
    if (kb_properties) {
	skip_list = CDR(kb_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_6:
	if (level < ab_loop_bind_)
	    goto end_loop_6;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_7:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_8:
	if ( !TRUEP(marked))
	    goto end_loop_7;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_8;
      end_loop_7:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_3;
	goto next_loop_7;
      end_loop_8:
      end_3:
	level = level - (SI_Long)1L;
	goto next_loop_6;
      end_loop_6:;
	kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		key_hash_value ? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? 
		ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	if (kb_specific_value);
	else
	    kb_specific_value = No_specific_property_value;
    }
    else
	kb_specific_value = No_specific_property_value;
    if ( !EQ(kb_specific_value,No_specific_property_value))
	resulting_value = kb_specific_value;
    else {
	skip_list = CDR(global_properties);
	key_value = Class_description_gkbprop;
	key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_9:
	if (level < ab_loop_bind_)
	    goto end_loop_9;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_10:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_11:
	if ( !TRUEP(marked))
	    goto end_loop_10;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_11;
      end_loop_10:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_4;
	goto next_loop_10;
      end_loop_11:
      end_4:
	level = level - (SI_Long)1L;
	goto next_loop_9;
      end_loop_9:;
	resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (resulting_value);
	else
	    resulting_value = Nil;
    }
    gensymed_symbol = resulting_value;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
		(SI_Long)18L));
	sub_class_vector_index = superior_class_bit_number >>  -  - 
		(SI_Long)3L;
	if (sub_class_vector_index < 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
	    gensymed_symbol_3 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
		    sub_class_vector_index);
	    gensymed_symbol_4 = (SI_Long)1L;
	    gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
	    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
	    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
	    temp_2 = (SI_Long)0L < gensymed_symbol_3;
	}
	else
	    temp_2 = TRUEP(Nil);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	simulation_subtable = make_frame(class_1);
	return body_of_put_for_simulation_frame(Frame_being_made,
		simulation_subtable,T);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_20;  /* "The class ~A cannot be instantiated within ~
				    *        attribute ~NS because it is not a defined class."
				    */

/* CLASS-INSTANTIATION-WARNING-NOT-DEFINED */
Object class_instantiation_warning_not_defined(class_for_instantiation,
	    slot_description,class_1)
    Object class_for_instantiation, slot_description, class_1;
{
    x_note_fn_call(200,44);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(5,FIX((SI_Long)1L),string_constant_20,
		class_for_instantiation,slot_description,
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop));
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

static Object string_constant_21;  /* "The class ~A cannot be instantiated within attribute ~
				    *          ~NS because it is not a subclass of the type ~
				    *          specification for this attribute, class ~A."
				    */

/* CLASS-INSTANTIATION-WARNING-INCOMPATIBLE-CLASS */
Object class_instantiation_warning_incompatible_class(class_for_instantiation,
	    slot_description,class_1,type_specification_class)
    Object class_for_instantiation, slot_description, class_1;
    Object type_specification_class;
{
    x_note_fn_call(200,45);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(6,FIX((SI_Long)1L),string_constant_21,
		class_for_instantiation,slot_description,
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop),type_specification_class);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

static Object string_constant_22;  /* "The class ~A cannot be instantiated within attribute ~
				    *        ~NS because the type-specification class, ~A,  has not yet ~
				    *        been defined."
				    */

/* CLASS-INSTANTIATION-WARNING-UNDEFINED-TYPE-SPECIFICATION-CLASS */
Object class_instantiation_warning_undefined_type_specification_class(class_for_instantiation,
	    slot_description,class_1,type_specification_class)
    Object class_for_instantiation, slot_description, class_1;
    Object type_specification_class;
{
    x_note_fn_call(200,46);
    Suppress_warning_message_header_qm = T;
    if ((SI_Long)1L <= IFIX(Warning_message_level))
	give_warning_1(6,FIX((SI_Long)1L),string_constant_22,
		class_for_instantiation,slot_description,
		lookup_global_or_kb_specific_property_value(class_1,
		Class_description_gkbprop),type_specification_class);
    Suppress_warning_message_header_qm = Nil;
    return VALUES_1(Suppress_warning_message_header_qm);
}

/* INSTANTIATE-VARIABLE */
Object instantiate_variable(class_1)
    Object class_1;
{
    x_note_fn_call(200,47);
    return instantiate_object_in_attribute_1(class_1,T);
}

/* INSTANTIATE-OBJECT-IN-ATTRIBUTE */
Object instantiate_object_in_attribute(class_1)
    Object class_1;
{
    x_note_fn_call(200,48);
    return instantiate_object_in_attribute_1(class_1,Nil);
}

static Object string_constant_23;  /* "An infinite set of ~A nested inside each other cannot ~
				    *             be instantiated as attributes. The process has been stopped ~
				    *             at a depth of ~d.  This ~A is of class ~A."
				    */

static Object string_constant_24;  /* "variables or parameters" */

static Object string_constant_25;  /* "objects" */

static Object string_constant_26;  /* "variable or parameter" */

static Object string_constant_27;  /* "object" */

static Object Qnot_user_instantiable;  /* not-user-instantiable */

static Object string_constant_28;  /* "The class ~a is not instantiable." */

static Object string_constant_29;  /* "The class ~a cannot be instantiated because it is not an ~
				    *               instantiable variable or parameter.  If ~a is an instantiable ~
				    *               object class that is not a variable or parameter, You may want ~
				    *               to change the attribute declaration to use the IS AN INSTANCE ~
				    *               OF syntax instead of the IS GIVEN BY syntax."
				    */

static Object string_constant_30;  /* "~A cannot instantiated as an attribute because it is not ~
				    *             an instantiable object class."
				    */

static Object string_constant_31;  /* "~A cannot be instantiated within an attribute because ~
				    *               it is not a defined class."
				    */

/* INSTANTIATE-OBJECT-IN-ATTRIBUTE-1 */
Object instantiate_object_in_attribute_1(class_1,variable_or_parameter_p)
    Object class_1, variable_or_parameter_p;
{
    Object skip_list, key_value, marked, pred, curr, succ, reference, temp;
    Object temp_1, entry_hash, gensymed_symbol, tail, head, new_cons;
    Object svref_arg_1, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector;
    Object attribute_nesting_depth;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(200,49);
    if (Recursive_attribute_nesting_has_occurred_qm)
	return VALUES_1(Nil);
    else if (NUM_GE(Attribute_nesting_depth,Attribute_nesting_limit)) {
	Recursive_attribute_nesting_has_occurred_qm = T;
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(6,FIX((SI_Long)1L),string_constant_23,
		    variable_or_parameter_p ? string_constant_24 : 
		    string_constant_25,Attribute_nesting_limit,
		    variable_or_parameter_p ? string_constant_26 : 
		    string_constant_27,class_1);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    else if (get_class_feature_if_any(class_1,Qnot_user_instantiable)) {
	Suppress_warning_message_header_qm = T;
	if ((SI_Long)1L <= IFIX(Warning_message_level))
	    give_warning_1(3,FIX((SI_Long)1L),string_constant_28,class_1);
	Suppress_warning_message_header_qm = Nil;
	return VALUES_1(Nil);
    }
    else {
	if (variable_or_parameter_p) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
		    IFIX(Most_positive_fixnum);
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
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_2:
	    if ( !TRUEP(marked))
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_2;
	  end_loop_1:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = class_1;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_3:
	    if (level < ab_loop_bind_)
		goto end_loop_3;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_5;
	  end_loop_4:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_2;
	    goto next_loop_4;
	  end_loop_5:
	  end_2:
	    level = level - (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_6:
		if (level < ab_loop_bind_)
		    goto end_loop_6;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_7:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_8:
		if ( !TRUEP(marked))
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_8;
	      end_loop_7:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_7;
	      end_loop_8:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_6;
	      end_loop_6:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_9:
		if (level < ab_loop_bind_)
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_10;
	      end_loop_11:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_9;
	      end_loop_9:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Variable_or_parameter_class_description,
			(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	else {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = class_1;
	    key_hash_value = SXHASH_SYMBOL_1(class_1) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_12:
	    if (level < ab_loop_bind_)
		goto end_loop_12;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_13:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_14:
	    if ( !TRUEP(marked))
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_14;
	  end_loop_13:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_5;
	    goto next_loop_13;
	  end_loop_14:
	  end_5:
	    level = level - (SI_Long)1L;
	    goto next_loop_12;
	  end_loop_12:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = class_1;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_1,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_15:
	    if (level < ab_loop_bind_)
		goto end_loop_15;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_16:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_17:
	    if ( !TRUEP(marked))
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_17;
	  end_loop_16:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_6;
	    goto next_loop_16;
	  end_loop_17:
	  end_6:
	    level = level - (SI_Long)1L;
	    goto next_loop_15;
	  end_loop_15:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_18:
		if (level < ab_loop_bind_)
		    goto end_loop_18;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_19:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_20;
	      end_loop_19:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_19;
	      end_loop_20:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_18;
	      end_loop_18:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_21:
		if (level < ab_loop_bind_)
		    goto end_loop_21;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_22:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_23:
		if ( !TRUEP(marked))
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_23;
	      end_loop_22:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_8;
		goto next_loop_22;
	      end_loop_23:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_21;
	      end_loop_21:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Object_class_description,(SI_Long)18L));
		sub_class_vector_index = superior_class_bit_number >>  -  
			- (SI_Long)3L;
		if (sub_class_vector_index < 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
			    {
		    gensymed_symbol_3 = 
			    UBYTE_8_ISAREF_1(sub_class_bit_vector,
			    sub_class_vector_index);
		    gensymed_symbol_4 = (SI_Long)1L;
		    gensymed_symbol_5 = superior_class_bit_number & 
			    (SI_Long)7L;
		    gensymed_symbol_4 = gensymed_symbol_4 << gensymed_symbol_5;
		    gensymed_symbol_3 = gensymed_symbol_3 & gensymed_symbol_4;
		    temp_2 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_2 = TRUEP(Nil);
	    }
	    else
		temp_2 = TRUEP(Nil);
	}
	if (temp_2) {
	    attribute_nesting_depth = FIXNUM_ADD1(Attribute_nesting_depth);
	    PUSH_SPECIAL_WITH_SYMBOL(Attribute_nesting_depth,Qattribute_nesting_depth,attribute_nesting_depth,
		    0);
	      temp_1 = make_frame(class_1);
	    POP_SPECIAL();
	    if (IFIX(Attribute_nesting_depth) == (SI_Long)1L)
		Recursive_attribute_nesting_has_occurred_qm = Nil;
	    return VALUES_1(temp_1);
	}
	else {
	    if (SYMBOLP(class_1)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_1;
		key_hash_value = SXHASH_SYMBOL_1(class_1) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_24:
		if (level < ab_loop_bind_)
		    goto end_loop_24;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_25:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_26:
		if ( !TRUEP(marked))
		    goto end_loop_25;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_26;
	      end_loop_25:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_9;
		goto next_loop_25;
	      end_loop_26:
	      end_9:
		level = level - (SI_Long)1L;
		goto next_loop_24;
	      end_loop_24:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_1;
		    temp = Symbol_properties_table;
		    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_27:
		if (level < ab_loop_bind_)
		    goto end_loop_27;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_28:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_29:
		if ( !TRUEP(marked))
		    goto end_loop_28;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_29;
	      end_loop_28:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_10;
		goto next_loop_28;
	      end_loop_29:
	      end_10:
		level = level - (SI_Long)1L;
		goto next_loop_27;
	      end_loop_27:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_30:
		    if (level < ab_loop_bind_)
			goto end_loop_30;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_31:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_32:
		    if ( !TRUEP(marked))
			goto end_loop_31;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_32;
		  end_loop_31:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_11;
		    goto next_loop_31;
		  end_loop_32:
		  end_11:
		    level = level - (SI_Long)1L;
		    goto next_loop_30;
		  end_loop_30:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_33:
		    if (level < ab_loop_bind_)
			goto end_loop_33;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_34:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_35:
		    if ( !TRUEP(marked))
			goto end_loop_34;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_35;
		  end_loop_34:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_12;
		    goto next_loop_34;
		  end_loop_35:
		  end_12:
		    level = level - (SI_Long)1L;
		    goto next_loop_33;
		  end_loop_33:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_2 = TRUEP(resulting_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		if (variable_or_parameter_p) {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(4,FIX((SI_Long)1L),
				string_constant_29,class_1,class_1);
		    Suppress_warning_message_header_qm = Nil;
		}
		else {
		    Suppress_warning_message_header_qm = T;
		    if ((SI_Long)1L <= IFIX(Warning_message_level))
			give_warning_1(3,FIX((SI_Long)1L),
				string_constant_30,class_1);
		    Suppress_warning_message_header_qm = Nil;
		}
		return VALUES_1(Nil);
	    }
	    else {
		Suppress_warning_message_header_qm = T;
		if ((SI_Long)1L <= IFIX(Warning_message_level))
		    give_warning_1(3,FIX((SI_Long)1L),string_constant_31,
			    class_1);
		Suppress_warning_message_header_qm = Nil;
		return VALUES_1(Nil);
	    }
	}
    }
}

/* COMPILE-NEW-CLASS-FOR-SLOT */
Object compile_new_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,50);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_class_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-ITEM-CLASS-FOR-SLOT */
Object compile_item_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,51);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_class_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-CONNECTION-CLASS-FOR-SLOT */
Object compile_connection_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,52);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_class_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-OBJECT-CLASS-FOR-SLOT */
Object compile_object_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,53);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_class_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-MESSAGE-CLASS-FOR-SLOT */
Object compile_message_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,54);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_class_for_slot(3,parse_result,frame,slot_name);
}

Object Classes_for_object_definition = UNBOUND;

Object Classes_for_class_definition = UNBOUND;

static Object Qobject_definition;  /* object-definition */

static Object Qobject;             /* object */

static Object Qmessage_definition;  /* message-definition */

static Object Qmessage;            /* message */

static Object Qconnection_definition;  /* connection-definition */

static Object Qconnection;         /* connection */

static Object Qitem;               /* item */

static Object string_constant_32;  /* "The name of an instantiated class cannot revert to NONE. ~
				    *                    To make this change, the instances must be deleted first."
				    */

static Object Qclass_definition;   /* class-definition */

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object string_constant_33;  /* "This class cannot be named ~A because then the class-definition for ~A ~
				    *                          would have two direct superiors named ~A."
				    */

static Object string_constant_34;  /* "This class cannot be named ~A because then an unnamed class-definition ~
				    *                          would have two direct superiors named ~A."
				    */

static Object string_constant_35;  /* "You may not edit the attributes of an ~
				    *                      automatically created junction block"
				    */

static Object string_constant_36;  /* "You may not use ~a as the name of a class because it specifies a type in G2." */

static Object Qsubclass;           /* subclass */

/* COMPILE-CLASS-FOR-SLOT */
Object compile_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Object x2, gensymed_symbol, sub_class_bit_vector, name_of_defined_class;
    Object direct_superior_classes_qm, superior, ab_loop_list_, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp_1, temp_2;
    Object entry_hash, tail, head, new_cons, svref_arg_1, svref_arg_2;
    Object svref_new_value, gensymed_symbol_4, gensymed_symbol_5;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, undefined_direct_superior_qm;
    Object possible_class_inheritance_path_qm, foundation_class_qm;
    Object specialized_definition_class, class_primary_foundation_class;
    Object potential_definition_qm, potential_definition_definition_type_qm;
    Object potential_specialized_definition_class_qm, prohibited_superior_qm;
    Object preceding_superior_qm, following_superior_qm;
    Object first_foundation_class_qm, second_foundation_class_qm;
    Object colliding_superior_qm, problem_inferior_class_qm;
    Object inferior_potential_definition_qm, definition_with_this_name;
    Object potential_definition, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, ab_loopvar__3, potential_definition_name_qm;
    Object current_definitions_variable_set, sublist, direct_superiors;
    Object ab_loop_it_, preceding_superior, following_superior;
    Object following_superior_inheritance_path_qm, class_description;
    Object superior_foundation_class_qm, other_superior;
    Object other_superior_foundation_class_qm, direct_superiors_qm;
    Object potential_specialized_definition_class;
    Object potential_primary_foundation_class, potential_inferior_definition;
    Object other_direct_superiors_not_defined_qm, ab_loop_list__1, paths;
    Object class_inheritance_paths;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(1);
    Object result;

    x_note_fn_call(200,55);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (SIMPLE_VECTOR_P(frame) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(frame,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(frame,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
    if (temp) {
	name_of_defined_class = ISVREF(frame,(SI_Long)20L);
	direct_superior_classes_qm = ISVREF(frame,(SI_Long)21L);
	superior = Nil;
	ab_loop_list_ = direct_superior_classes_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SYMBOLP(superior)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = superior;
	    key_hash_value = SXHASH_SYMBOL_1(superior) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_1:
	    if (level < ab_loop_bind_)
		goto end_loop_1;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_2:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_3:
	    if ( !TRUEP(marked))
		goto end_loop_2;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_3;
	  end_loop_2:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_2;
	  end_loop_3:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop_1;
	  end_loop_1:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
		temp_1 = Symbol_properties_table;
		temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		    gensymed_symbol_4 = new_cons;
		}
		else
		    gensymed_symbol_4 = Nil;
		if ( !TRUEP(gensymed_symbol_4))
		    gensymed_symbol_4 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
		    gensymed_symbol_5 = new_cons;
		}
		else
		    gensymed_symbol_5 = Nil;
		if ( !TRUEP(gensymed_symbol_5))
		    gensymed_symbol_5 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_5) = head;
		M_CDR(gensymed_symbol_5) = tail;
		inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp_2,
			gensymed_symbol_4);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_4:
	    if (level < ab_loop_bind_)
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_5:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_6:
	    if ( !TRUEP(marked))
		goto end_loop_5;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_6;
	  end_loop_5:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_2;
	    goto next_loop_5;
	  end_loop_6:
	  end_2:
	    level = level - (SI_Long)1L;
	    goto next_loop_4;
	  end_loop_4:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_7:
		if (level < ab_loop_bind_)
		    goto end_loop_7;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_8:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_9:
		if ( !TRUEP(marked))
		    goto end_loop_8;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_9;
	      end_loop_8:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_8;
	      end_loop_9:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_7;
	      end_loop_7:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_10:
		if (level < ab_loop_bind_)
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_11:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_12:
		if ( !TRUEP(marked))
		    goto end_loop_11;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_12;
	      end_loop_11:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_11;
	      end_loop_12:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_10;
	      end_loop_10:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    temp = TRUEP(resulting_value);
	}
	else
	    temp = TRUEP(Nil);
	if ( !temp) {
	    undefined_direct_superior_qm = superior;
	    goto end_5;
	}
	goto next_loop;
      end_loop:
	undefined_direct_superior_qm = Qnil;
      end_5:;
	possible_class_inheritance_path_qm = direct_superior_classes_qm && 
		 !TRUEP(undefined_direct_superior_qm) ? 
		make_class_inheritance_path_for_user_defined_class(parse_result,
		direct_superior_classes_qm) : Nil;
	foundation_class_qm =  !TRUEP(undefined_direct_superior_qm) ? 
		most_refined_foundation_class_of_direct_superiors(1,
		direct_superior_classes_qm) : Nil;
	specialized_definition_class = get_specialized_definition_class(frame);
	if (EQ(specialized_definition_class,Qobject_definition))
	    class_primary_foundation_class = Qobject;
	else if (EQ(specialized_definition_class,Qmessage_definition))
	    class_primary_foundation_class = Qmessage;
	else if (EQ(specialized_definition_class,Qconnection_definition))
	    class_primary_foundation_class = Qconnection;
	else
	    class_primary_foundation_class = Qitem;
	potential_definition_qm = Nil;
	potential_definition_definition_type_qm = Nil;
	potential_specialized_definition_class_qm = Nil;
	prohibited_superior_qm = Nil;
	preceding_superior_qm = Nil;
	following_superior_qm = Nil;
	first_foundation_class_qm = Nil;
	second_foundation_class_qm = Nil;
	colliding_superior_qm = Nil;
	problem_inferior_class_qm = Nil;
	inferior_potential_definition_qm = Nil;
	if (EQ(parse_result,Qnone)) {
	    reclaim_slot_value(possible_class_inheritance_path_qm);
	    if (SYMBOLP(name_of_defined_class)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = name_of_defined_class;
		key_hash_value = SXHASH_SYMBOL_1(name_of_defined_class) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_13:
		if (level < ab_loop_bind_)
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_14:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_15:
		if ( !TRUEP(marked))
		    goto end_loop_14;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_15;
	      end_loop_14:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_6;
		goto next_loop_14;
	      end_loop_15:
	      end_6:
		level = level - (SI_Long)1L;
		goto next_loop_13;
	      end_loop_13:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = name_of_defined_class;
		    temp_1 = Symbol_properties_table;
		    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
			gensymed_symbol_4 = new_cons;
		    }
		    else
			gensymed_symbol_4 = Nil;
		    if ( !TRUEP(gensymed_symbol_4))
			gensymed_symbol_4 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_5 = new_cons;
		    }
		    else
			gensymed_symbol_5 = Nil;
		    if ( !TRUEP(gensymed_symbol_5))
			gensymed_symbol_5 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_5) = head;
		    M_CDR(gensymed_symbol_5) = tail;
		    inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
		    M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
		    inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_2,gensymed_symbol_4);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_16:
		if (level < ab_loop_bind_)
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_17:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
	      next_loop_18:
		if ( !TRUEP(marked))
		    goto end_loop_17;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp_1,temp_2);
		MVS_2(result,succ,marked);
		goto next_loop_18;
	      end_loop_17:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_17;
	      end_loop_18:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_16;
	      end_loop_16:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_19:
		    if (level < ab_loop_bind_)
			goto end_loop_19;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_20:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_21:
		    if ( !TRUEP(marked))
			goto end_loop_20;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_21;
		  end_loop_20:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_8;
		    goto next_loop_20;
		  end_loop_21:
		  end_8:
		    level = level - (SI_Long)1L;
		    goto next_loop_19;
		  end_loop_19:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_22:
		    if (level < ab_loop_bind_)
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_23:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		  next_loop_24:
		    if ( !TRUEP(marked))
			goto end_loop_23;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp_1,temp_2);
		    MVS_2(result,succ,marked);
		    goto next_loop_24;
		  end_loop_23:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_9;
		    goto next_loop_23;
		  end_loop_24:
		  end_9:
		    level = level - (SI_Long)1L;
		    goto next_loop_22;
		  end_loop_22:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp = TRUEP(resulting_value);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp ? TRUEP(instantiated_class_p(name_of_defined_class)) :
		     TRUEP(Nil)) {
		temp_1 = Bad_phrase;
		temp_2 = tformat_text_string(1,string_constant_32);
		return VALUES_2(temp_1,temp_2);
	    }
	    else {
		parse_result = Nil;
		return VALUES_1(parse_result);
	    }
	}
	else {
	    definition_with_this_name = 
		    get_instance_with_name_if_any(Qclass_definition,
		    parse_result);
	    if (definition_with_this_name &&  
		    !EQ(definition_with_this_name,frame)) {
		reclaim_slot_value(possible_class_inheritance_path_qm);
		temp_1 = Bad_phrase;
		temp_2 = 
			copy_constant_wide_string_given_length(array_constant_10,
			FIX((SI_Long)43L));
		return VALUES_2(temp_1,temp_2);
	    }
	    else {
		if (lookup_global_or_kb_specific_property_value(parse_result,
			Class_description_gkbprop)) {
		    temp_2 = 
			    lookup_global_or_kb_specific_property_value(parse_result,
			    Class_definition_gkbprop);
		    temp = CONSP(temp_2);
		}
		else
		    temp = TRUEP(Nil);
		if (temp) {
		    reclaim_slot_value(possible_class_inheritance_path_qm);
		    temp_1 = Bad_phrase;
		    temp_2 = 
			    copy_constant_wide_string_given_length(array_constant_11,
			    FIX((SI_Long)41L));
		    return VALUES_2(temp_1,temp_2);
		}
		else {
		    if ( !EQ(parse_result,Qnone)) {
			potential_definition = Nil;
			ab_loop_list_ = 
				lookup_global_or_kb_specific_property_value(name_of_defined_class,
				Potential_inferior_class_definitions_gkbprop);
		      next_loop_25:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_25;
			potential_definition = M_CAR(ab_loop_list_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if (memq_function(parse_result,
				ISVREF(potential_definition,(SI_Long)21L))) {
			    potential_definition_qm = potential_definition;
			    temp = TRUEP(potential_definition_qm);
			    goto end_10;
			}
			goto next_loop_25;
		      end_loop_25:
			temp = TRUEP(Qnil);
		      end_10:;
		    }
		    else
			temp = TRUEP(Nil);
		    if (temp) {
			temp_1 = Bad_phrase;
			temp_2 = ISVREF(potential_definition_qm,
				(SI_Long)20L) ? tformat_text_string(4,
				string_constant_33,parse_result,
				ISVREF(potential_definition_qm,
				(SI_Long)20L),parse_result) : 
				tformat_text_string(3,string_constant_34,
				parse_result,parse_result);
			return VALUES_2(temp_1,temp_2);
		    }
		    else {
			gensymed_symbol = ACCESS_ONCE(ISVREF(frame,
				(SI_Long)14L));
			gensymed_symbol = gensymed_symbol ? 
				ACCESS_ONCE(ISVREF(gensymed_symbol,
				(SI_Long)5L)) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    skip_list = CDR(Symbol_properties_table);
			    key_value = name_of_defined_class;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(name_of_defined_class) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_26:
			    if (level < ab_loop_bind_)
				goto end_loop_26;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_27:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_28:
			    if ( !TRUEP(marked))
				goto end_loop_27;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_28;
			  end_loop_27:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_11;
			    goto next_loop_27;
			  end_loop_28:
			  end_11:
			    level = level - (SI_Long)1L;
			    goto next_loop_26;
			  end_loop_26:;
			    gensymed_symbol = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if ( !TRUEP(gensymed_symbol)) {
				gensymed_symbol = name_of_defined_class;
				temp_1 = Symbol_properties_table;
				temp_2 = 
					FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
					& IFIX(Most_positive_fixnum));
				tail = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
					Nil);
				head = 
					make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
					tail);
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_4 = new_cons;
				}
				else
				    gensymed_symbol_4 = Nil;
				if ( !TRUEP(gensymed_symbol_4))
				    gensymed_symbol_4 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_4) = 
					Qsymbol_properties_hash_table;
				new_cons = 
					ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index));
				if (new_cons) {
				    svref_arg_1 = 
					    Available_lookup_conses_vector;
				    svref_arg_2 = Current_thread_index;
				    svref_new_value = M_CDR(new_cons);
				    SVREF(svref_arg_1,svref_arg_2) = 
					    svref_new_value;
				    if ( 
					    !TRUEP(ISVREF(Available_lookup_conses_vector,
					    IFIX(Current_thread_index)))) {
					svref_arg_1 = 
						Available_lookup_conses_tail_vector;
					svref_arg_2 = Current_thread_index;
					SVREF(svref_arg_1,svref_arg_2) = Nil;
				    }
				    gensymed_symbol_5 = new_cons;
				}
				else
				    gensymed_symbol_5 = Nil;
				if ( !TRUEP(gensymed_symbol_5))
				    gensymed_symbol_5 = 
					    replenish_lookup_cons_pool();
				M_CAR(gensymed_symbol_5) = head;
				M_CDR(gensymed_symbol_5) = tail;
				inline_note_allocate_cons(gensymed_symbol_5,
					Qlookup);
				M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
				inline_note_allocate_cons(gensymed_symbol_4,
					Qlookup);
				gensymed_symbol = 
					set_skip_list_entry(temp_1,
					FIX((SI_Long)31L),Qeq,Nil,T,
					gensymed_symbol,temp_2,
					gensymed_symbol_4);
			    }
			    global_properties = gensymed_symbol;
			    skip_list = CDR(global_properties);
			    key_value = 
				    Current_kb_specific_property_list_property_name;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_29:
			    if (level < ab_loop_bind_)
				goto end_loop_29;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_30:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			  next_loop_31:
			    if ( !TRUEP(marked))
				goto end_loop_30;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp_2 = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp_2);
			    MVS_2(result,succ,marked);
			    goto next_loop_31;
			  end_loop_30:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_12;
			    goto next_loop_30;
			  end_loop_31:
			  end_12:
			    level = level - (SI_Long)1L;
			    goto next_loop_29;
			  end_loop_29:;
			    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) 
				    == key_hash_value ? (EQ(key_value,
				    ISVREF(curr,(SI_Long)2L)) ? 
				    ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			    if (kb_properties);
			    else
				kb_properties = Nil;
			    if (kb_properties) {
				skip_list = CDR(kb_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_32:
				if (level < ab_loop_bind_)
				    goto end_loop_32;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_33:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_34:
				if ( !TRUEP(marked))
				    goto end_loop_33;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_34;
			      end_loop_33:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_13;
				goto next_loop_33;
			      end_loop_34:
			      end_13:
				level = level - (SI_Long)1L;
				goto next_loop_32;
			      end_loop_32:;
				kb_specific_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (kb_specific_value);
				else
				    kb_specific_value = 
					    No_specific_property_value;
			    }
			    else
				kb_specific_value = No_specific_property_value;
			    if ( !EQ(kb_specific_value,
				    No_specific_property_value))
				resulting_value = kb_specific_value;
			    else {
				skip_list = CDR(global_properties);
				key_value = Class_description_gkbprop;
				key_hash_value = 
					SXHASH_SYMBOL_1(Class_description_gkbprop) 
					& IFIX(Most_positive_fixnum);
				bottom_level = (SI_Long)0L;
				marked = Nil;
				pred = M_CAR(skip_list);
				curr = Nil;
				succ = Nil;
				level = (SI_Long)31L;
				ab_loop_bind_ = bottom_level;
			      next_loop_35:
				if (level < ab_loop_bind_)
				    goto end_loop_35;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
			      next_loop_36:
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
			      next_loop_37:
				if ( !TRUEP(marked))
				    goto end_loop_36;
				curr = 
					ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
					(SI_Long)0L),level));
				reference = ISVREF(ISVREF(curr,
					(SI_Long)0L),level);
				temp_1 = ATOMIC_REF_OBJECT(reference);
				temp_2 = (SI_Long)355L == 
					ATOMIC_REF_STAMP(reference) ? T : Nil;
				result = VALUES_2(temp_1,temp_2);
				MVS_2(result,succ,marked);
				goto next_loop_37;
			      end_loop_36:
				entry_hash = ISVREF(curr,(SI_Long)1L);
				if (IFIX(entry_hash) < key_hash_value || 
					IFIX(entry_hash) == key_hash_value 
					&&  !EQ(key_value,ISVREF(curr,
					(SI_Long)2L))) {
				    pred = curr;
				    curr = succ;
				}
				else
				    goto end_14;
				goto next_loop_36;
			      end_loop_37:
			      end_14:
				level = level - (SI_Long)1L;
				goto next_loop_35;
			      end_loop_35:;
				resulting_value = IFIX(ISVREF(curr,
					(SI_Long)1L)) == key_hash_value ? 
					(EQ(key_value,ISVREF(curr,
					(SI_Long)2L)) ? ISVREF(curr,
					(SI_Long)3L) : Nil) : Nil;
				if (resulting_value);
				else
				    resulting_value = Nil;
			    }
			    gensymed_symbol = resulting_value;
			    if (gensymed_symbol) {
				sub_class_bit_vector = 
					ISVREF(gensymed_symbol,(SI_Long)19L);
				superior_class_bit_number = 
					IFIX(ISVREF(Default_junction_class_description,
					(SI_Long)18L));
				sub_class_vector_index = 
					superior_class_bit_number >>  -  - 
					(SI_Long)3L;
				if (sub_class_vector_index < 
					IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
					    {
				    gensymed_symbol_1 = 
					    UBYTE_8_ISAREF_1(sub_class_bit_vector,
					    sub_class_vector_index);
				    gensymed_symbol_2 = (SI_Long)1L;
				    gensymed_symbol_3 = 
					    superior_class_bit_number & 
					    (SI_Long)7L;
				    gensymed_symbol_2 = gensymed_symbol_2 
					    << gensymed_symbol_3;
				    gensymed_symbol_1 = gensymed_symbol_1 
					    & gensymed_symbol_2;
				    temp = (SI_Long)0L < gensymed_symbol_1;
				}
				else
				    temp = TRUEP(Nil);
			    }
			    else
				temp = TRUEP(Nil);
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    reclaim_slot_value(possible_class_inheritance_path_qm);
			    temp_1 = Bad_phrase;
			    temp_2 = tformat_text_string(1,string_constant_35);
			    return VALUES_2(temp_1,temp_2);
			}
			else if (type_specification_for_user_or_datum_type(parse_result)) 
				    {
			    reclaim_slot_value(possible_class_inheritance_path_qm);
			    temp_1 = Bad_phrase;
			    temp_2 = tformat_text_string(2,
				    string_constant_36,parse_result);
			    return VALUES_2(temp_1,temp_2);
			}
			else {
			    scope_conses = Scope_conses;
			    ab_loopvar_ = parse_result;
			    ab_loopvar__1 = Nil;
			    ab_loopvar__2 = Nil;
			    ab_loopvar__3 = Nil;
			    potential_definition = Nil;
			    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
				    0);
			      potential_definition_name_qm = Nil;
			      ab_loopvar__3 = 
				      lookup_global_or_kb_specific_property_value(ab_loopvar_,
				      Potential_inferior_class_definitions_gkbprop);
			    next_loop_38:
			      if ( !TRUEP(ab_loopvar__3))
				  goto end_loop_38;
			      temp_2 = M_CAR(ab_loopvar__3);
			      ab_loopvar__2 = 
				      scope_cons(M_CAR(ab_loopvar__3),
				      ab_loopvar__2);
			      ab_loopvar_ = 
				      lookup_global_or_kb_specific_property_value(ISVREF(M_CAR(ab_loopvar__3),
				      (SI_Long)20L),
				      Potential_inferior_class_definitions_gkbprop);
			      if (ab_loopvar_) {
				  temp_1 = ab_loopvar__1;
				  ab_loopvar__1 = nconc2(temp_1,
					  scope_cons(ab_loopvar_,Nil));
			      }
			      ab_loopvar__3 = M_CDR(ab_loopvar__3);
			      current_definitions_variable_set = Nil;
			    next_loop_39:
			      if (current_definitions_variable_set)
				  goto end_loop_39;
			      sublist = ab_loopvar__3;
			    next_loop_40:
			      if ( !TRUEP(sublist))
				  goto end_loop_40;
			      if ( !TRUEP(sublist))
				  goto end_loop_40;
			      if ( !TRUEP(memq_function(M_CAR(sublist),
				      ab_loopvar__2))) {
				  ab_loopvar__3 = sublist;
				  current_definitions_variable_set = T;
				  goto end_loop_40;
			      }
			      sublist = M_CDR(sublist);
			      goto next_loop_40;
			    end_loop_40:
			      if ( !TRUEP(current_definitions_variable_set)) {
				  ab_loopvar__3 = CAR(ab_loopvar__1);
				  if (ab_loopvar__1)
				      ab_loopvar__1 = M_CDR(ab_loopvar__1);
				  else
				      current_definitions_variable_set = T;
			      }
			      goto next_loop_39;
			    end_loop_39:;
			      potential_definition = temp_2;
			      potential_definition_name_qm = 
				      ISVREF(potential_definition,
				      (SI_Long)20L);
			      if (potential_definition_name_qm && 
				      memq_function(potential_definition_name_qm,
				      direct_superior_classes_qm)) {
				  prohibited_superior_qm = 
					  potential_definition_name_qm;
				  temp = TRUEP(prohibited_superior_qm);
				  goto end_15;
			      }
			      goto next_loop_38;
			    end_loop_38:
			      temp = TRUEP(Qnil);
			    end_15:;
			    POP_SPECIAL();
			    if (temp) {
				reclaim_slot_value(possible_class_inheritance_path_qm);
				temp_1 = Bad_phrase;
				temp_2 = 
					circularity_in_potential_definition_inheritance(prohibited_superior_qm);
				return VALUES_2(temp_1,temp_2);
			    }
			    else {
				scope_conses = Scope_conses;
				ab_loopvar_ = parse_result;
				ab_loopvar__1 = Nil;
				ab_loopvar__2 = Nil;
				ab_loopvar__3 = Nil;
				potential_definition = Nil;
				PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
					0);
				  direct_superiors = Nil;
				  ab_loop_it_ = Nil;
				  ab_loopvar__3 = 
					  lookup_global_or_kb_specific_property_value(ab_loopvar_,
					  Potential_inferior_class_definitions_gkbprop);
				next_loop_41:
				  if ( !TRUEP(ab_loopvar__3))
				      goto end_loop_41;
				  temp_2 = M_CAR(ab_loopvar__3);
				  ab_loopvar__2 = 
					  scope_cons(M_CAR(ab_loopvar__3),
					  ab_loopvar__2);
				  ab_loopvar_ = 
					  lookup_global_or_kb_specific_property_value(ISVREF(M_CAR(ab_loopvar__3),
					  (SI_Long)20L),
					  Potential_inferior_class_definitions_gkbprop);
				  if (ab_loopvar_) {
				      temp_1 = ab_loopvar__1;
				      ab_loopvar__1 = nconc2(temp_1,
					      scope_cons(ab_loopvar_,Nil));
				  }
				  ab_loopvar__3 = M_CDR(ab_loopvar__3);
				  current_definitions_variable_set = Nil;
				next_loop_42:
				  if (current_definitions_variable_set)
				      goto end_loop_42;
				  sublist = ab_loopvar__3;
				next_loop_43:
				  if ( !TRUEP(sublist))
				      goto end_loop_43;
				  if ( !TRUEP(sublist))
				      goto end_loop_43;
				  if ( !TRUEP(memq_function(M_CAR(sublist),
					  ab_loopvar__2))) {
				      ab_loopvar__3 = sublist;
				      current_definitions_variable_set = T;
				      goto end_loop_43;
				  }
				  sublist = M_CDR(sublist);
				  goto next_loop_43;
				end_loop_43:
				  if ( 
					  !TRUEP(current_definitions_variable_set)) 
					      {
				      ab_loopvar__3 = CAR(ab_loopvar__1);
				      if (ab_loopvar__1)
					  ab_loopvar__1 = M_CDR(ab_loopvar__1);
				      else
					  current_definitions_variable_set = T;
				  }
				  goto next_loop_42;
				end_loop_42:;
				  potential_definition = temp_2;
				  direct_superiors = 
					  ISVREF(potential_definition,
					  (SI_Long)21L);
				  sublist = direct_superiors;
				  preceding_superior = Nil;
				  following_superior = Nil;
				  following_superior_inheritance_path_qm = Nil;
				  ab_loop_it_ = Nil;
				next_loop_44:
				  if ( !TRUEP(sublist))
				      goto end_loop_44;
				  if ( !TRUEP(SECOND(sublist)))
				      goto end_loop_44;
				  preceding_superior = FIRST(sublist);
				  following_superior = SECOND(sublist);
				  if (EQ(following_superior,parse_result))
				      following_superior_inheritance_path_qm 
					      = 
					      possible_class_inheritance_path_qm;
				  else {
				      class_description = Nil;
				      class_description = 
					      lookup_global_or_kb_specific_property_value(following_superior,
					      Class_description_gkbprop);
				      following_superior_inheritance_path_qm 
					      = class_description ? 
					      ISVREF(class_description,
					      (SI_Long)2L) : Qnil;
				  }
				  if (following_superior_inheritance_path_qm 
					  && 
					  memq_function(preceding_superior,
					  following_superior_inheritance_path_qm)) 
					      {
				      preceding_superior_qm = 
					      preceding_superior;
				      temp = TRUEP(preceding_superior_qm);
				  }
				  else
				      temp = TRUEP(Nil);
				  if (temp) {
				      following_superior_qm = 
					      following_superior;
				      temp = TRUEP(following_superior_qm);
				  }
				  else
				      temp = TRUEP(Nil);
				  if (temp) {
				      prohibited_superior_qm = 
					      ISVREF(potential_definition,
					      (SI_Long)20L);
				      ab_loop_it_ = prohibited_superior_qm;
				  }
				  else
				      ab_loop_it_ = Nil;
				  if (ab_loop_it_)
				      goto end_16;
				  sublist = M_CDR(sublist);
				  goto next_loop_44;
				end_loop_44:
				  ab_loop_it_ = Qnil;
				end_16:;
				  if (ab_loop_it_) {
				      temp = TRUEP(ab_loop_it_);
				      goto end_17;
				  }
				  goto next_loop_41;
				end_loop_41:
				  temp = TRUEP(Qnil);
				end_17:;
				POP_SPECIAL();
				if (temp) {
				    reclaim_slot_value(possible_class_inheritance_path_qm);
				    temp_1 = Bad_phrase;
				    temp_2 = 
					    subclass_appears_after_superior_for_potential_definition(preceding_superior_qm,
					    following_superior_qm,
					    prohibited_superior_qm);
				    return VALUES_2(temp_1,temp_2);
				}
				else {
				    scope_conses = Scope_conses;
				    ab_loopvar_ = parse_result;
				    ab_loopvar__1 = Nil;
				    ab_loopvar__2 = Nil;
				    ab_loopvar__3 = Nil;
				    potential_definition = Nil;
				    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
					    0);
				      direct_superiors = Nil;
				      ab_loop_it_ = Nil;
				      ab_loopvar__3 = 
					      lookup_global_or_kb_specific_property_value(ab_loopvar_,
					      Potential_inferior_class_definitions_gkbprop);
				    next_loop_45:
				      if ( !TRUEP(ab_loopvar__3))
					  goto end_loop_45;
				      temp_2 = M_CAR(ab_loopvar__3);
				      ab_loopvar__2 = 
					      scope_cons(M_CAR(ab_loopvar__3),
					      ab_loopvar__2);
				      ab_loopvar_ = 
					      lookup_global_or_kb_specific_property_value(ISVREF(M_CAR(ab_loopvar__3),
					      (SI_Long)20L),
					      Potential_inferior_class_definitions_gkbprop);
				      if (ab_loopvar_) {
					  temp_1 = ab_loopvar__1;
					  ab_loopvar__1 = nconc2(temp_1,
						  scope_cons(ab_loopvar_,Nil));
				      }
				      ab_loopvar__3 = M_CDR(ab_loopvar__3);
				      current_definitions_variable_set = Nil;
				    next_loop_46:
				      if (current_definitions_variable_set)
					  goto end_loop_46;
				      sublist = ab_loopvar__3;
				    next_loop_47:
				      if ( !TRUEP(sublist))
					  goto end_loop_47;
				      if ( !TRUEP(sublist))
					  goto end_loop_47;
				      if ( 
					      !TRUEP(memq_function(M_CAR(sublist),
					      ab_loopvar__2))) {
					  ab_loopvar__3 = sublist;
					  current_definitions_variable_set = T;
					  goto end_loop_47;
				      }
				      sublist = M_CDR(sublist);
				      goto next_loop_47;
				    end_loop_47:
				      if ( 
					      !TRUEP(current_definitions_variable_set)) 
						  {
					  ab_loopvar__3 = CAR(ab_loopvar__1);
					  if (ab_loopvar__1)
					      ab_loopvar__1 = 
						      M_CDR(ab_loopvar__1);
					  else
					      current_definitions_variable_set 
						      = T;
				      }
				      goto next_loop_46;
				    end_loop_46:;
				      potential_definition = temp_2;
				      direct_superiors = 
					      ISVREF(potential_definition,
					      (SI_Long)21L);
				      if (CDR(direct_superiors)) {
					  sublist = direct_superiors;
					  superior = Nil;
					  superior_foundation_class_qm = Nil;
					  ab_loop_it_ = Nil;
					next_loop_48:
					  if ( !TRUEP(sublist))
					      goto end_loop_48;
					  if ( !TRUEP(CDR(sublist)))
					      goto end_loop_48;
					  superior = CAR(sublist);
					  temp_2 = EQ(superior,
						  parse_result) ? 
						  foundation_class_qm : Qnil;
					  if (temp_2);
					  else {
					      if (SYMBOLP(superior)) {
						  skip_list = 
							  CDR(Symbol_properties_table);
						  key_value = superior;
						  key_hash_value = 
							  SXHASH_SYMBOL_1(superior) 
							  & 
							  IFIX(Most_positive_fixnum);
						  bottom_level = (SI_Long)0L;
						  marked = Nil;
						  pred = M_CAR(skip_list);
						  curr = Nil;
						  succ = Nil;
						  level = (SI_Long)31L;
						  ab_loop_bind_ = bottom_level;
						next_loop_49:
						  if (level < ab_loop_bind_)
						      goto end_loop_49;
						  curr = 
							  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							  (SI_Long)0L),level));
						next_loop_50:
						  reference = 
							  ISVREF(ISVREF(curr,
							  (SI_Long)0L),level);
						  temp_1 = 
							  ATOMIC_REF_OBJECT(reference);
						  temp_2 = (SI_Long)355L 
							  == 
							  ATOMIC_REF_STAMP(reference) 
							  ? T : Nil;
						  result = VALUES_2(temp_1,
							  temp_2);
						  MVS_2(result,succ,marked);
						next_loop_51:
						  if ( !TRUEP(marked))
						      goto end_loop_50;
						  curr = 
							  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							  (SI_Long)0L),level));
						  reference = 
							  ISVREF(ISVREF(curr,
							  (SI_Long)0L),level);
						  temp_1 = 
							  ATOMIC_REF_OBJECT(reference);
						  temp_2 = (SI_Long)355L 
							  == 
							  ATOMIC_REF_STAMP(reference) 
							  ? T : Nil;
						  result = VALUES_2(temp_1,
							  temp_2);
						  MVS_2(result,succ,marked);
						  goto next_loop_51;
						end_loop_50:
						  entry_hash = ISVREF(curr,
							  (SI_Long)1L);
						  if (IFIX(entry_hash) < 
							  key_hash_value 
							  || 
							  IFIX(entry_hash) 
							  == 
							  key_hash_value 
							  &&  
							  !EQ(key_value,
							  ISVREF(curr,
							  (SI_Long)2L))) {
						      pred = curr;
						      curr = succ;
						  }
						  else
						      goto end_18;
						  goto next_loop_50;
						end_loop_51:
						end_18:
						  level = level - (SI_Long)1L;
						  goto next_loop_49;
						end_loop_49:;
						  gensymed_symbol = 
							  IFIX(ISVREF(curr,
							  (SI_Long)1L)) == 
							  key_hash_value ? 
							  (EQ(key_value,
							  ISVREF(curr,
							  (SI_Long)2L)) ? 
							  ISVREF(curr,
							  (SI_Long)3L) : 
							  Nil) : Nil;
						  if ( 
							      !TRUEP(gensymed_symbol)) {
						      gensymed_symbol = 
							      superior;
						      temp_1 = 
							      Symbol_properties_table;
						      temp_2 = 
							      FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
							      & 
							      IFIX(Most_positive_fixnum));
						      tail = 
							      make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
							      Nil);
						      head = 
							      make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
							      tail);
						      new_cons = 
							      ISVREF(Available_lookup_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  svref_arg_1 = 
								  Available_lookup_conses_vector;
							  svref_arg_2 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(svref_arg_1,
								  svref_arg_2) 
								  = 
								  svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_lookup_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      svref_arg_1 
								      = 
								      Available_lookup_conses_tail_vector;
							      svref_arg_2 
								      = 
								      Current_thread_index;
							      SVREF(svref_arg_1,
								      svref_arg_2) 
								      = Nil;
							  }
							  gensymed_symbol_4 
								  = new_cons;
						      }
						      else
							  gensymed_symbol_4 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol_4))
							  gensymed_symbol_4 
								  = 
								  replenish_lookup_cons_pool();
						      M_CAR(gensymed_symbol_4) 
							      = 
							      Qsymbol_properties_hash_table;
						      new_cons = 
							      ISVREF(Available_lookup_conses_vector,
							      IFIX(Current_thread_index));
						      if (new_cons) {
							  svref_arg_1 = 
								  Available_lookup_conses_vector;
							  svref_arg_2 = 
								  Current_thread_index;
							  svref_new_value 
								  = 
								  M_CDR(new_cons);
							  SVREF(svref_arg_1,
								  svref_arg_2) 
								  = 
								  svref_new_value;
							  if ( 
								  !TRUEP(ISVREF(Available_lookup_conses_vector,
								  IFIX(Current_thread_index)))) 
								      {
							      svref_arg_1 
								      = 
								      Available_lookup_conses_tail_vector;
							      svref_arg_2 
								      = 
								      Current_thread_index;
							      SVREF(svref_arg_1,
								      svref_arg_2) 
								      = Nil;
							  }
							  gensymed_symbol_5 
								  = new_cons;
						      }
						      else
							  gensymed_symbol_5 
								  = Nil;
						      if ( 
							      !TRUEP(gensymed_symbol_5))
							  gensymed_symbol_5 
								  = 
								  replenish_lookup_cons_pool();
						      M_CAR(gensymed_symbol_5) 
							      = head;
						      M_CDR(gensymed_symbol_5) 
							      = tail;
						      inline_note_allocate_cons(gensymed_symbol_5,
							      Qlookup);
						      M_CDR(gensymed_symbol_4) 
							      = 
							      gensymed_symbol_5;
						      inline_note_allocate_cons(gensymed_symbol_4,
							      Qlookup);
						      gensymed_symbol = 
							      set_skip_list_entry(temp_1,
							      FIX((SI_Long)31L),
							      Qeq,Nil,T,
							      gensymed_symbol,
							      temp_2,
							      gensymed_symbol_4);
						  }
						  global_properties = 
							  gensymed_symbol;
						  skip_list = 
							  CDR(global_properties);
						  key_value = 
							  Current_kb_specific_property_list_property_name;
						  key_hash_value = 
							  SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
							  & 
							  IFIX(Most_positive_fixnum);
						  bottom_level = (SI_Long)0L;
						  marked = Nil;
						  pred = M_CAR(skip_list);
						  curr = Nil;
						  succ = Nil;
						  level = (SI_Long)31L;
						  ab_loop_bind_ = bottom_level;
						next_loop_52:
						  if (level < ab_loop_bind_)
						      goto end_loop_52;
						  curr = 
							  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							  (SI_Long)0L),level));
						next_loop_53:
						  reference = 
							  ISVREF(ISVREF(curr,
							  (SI_Long)0L),level);
						  temp_1 = 
							  ATOMIC_REF_OBJECT(reference);
						  temp_2 = (SI_Long)355L 
							  == 
							  ATOMIC_REF_STAMP(reference) 
							  ? T : Nil;
						  result = VALUES_2(temp_1,
							  temp_2);
						  MVS_2(result,succ,marked);
						next_loop_54:
						  if ( !TRUEP(marked))
						      goto end_loop_53;
						  curr = 
							  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							  (SI_Long)0L),level));
						  reference = 
							  ISVREF(ISVREF(curr,
							  (SI_Long)0L),level);
						  temp_1 = 
							  ATOMIC_REF_OBJECT(reference);
						  temp_2 = (SI_Long)355L 
							  == 
							  ATOMIC_REF_STAMP(reference) 
							  ? T : Nil;
						  result = VALUES_2(temp_1,
							  temp_2);
						  MVS_2(result,succ,marked);
						  goto next_loop_54;
						end_loop_53:
						  entry_hash = ISVREF(curr,
							  (SI_Long)1L);
						  if (IFIX(entry_hash) < 
							  key_hash_value 
							  || 
							  IFIX(entry_hash) 
							  == 
							  key_hash_value 
							  &&  
							  !EQ(key_value,
							  ISVREF(curr,
							  (SI_Long)2L))) {
						      pred = curr;
						      curr = succ;
						  }
						  else
						      goto end_19;
						  goto next_loop_53;
						end_loop_54:
						end_19:
						  level = level - (SI_Long)1L;
						  goto next_loop_52;
						end_loop_52:;
						  kb_properties = 
							  IFIX(ISVREF(curr,
							  (SI_Long)1L)) == 
							  key_hash_value ? 
							  (EQ(key_value,
							  ISVREF(curr,
							  (SI_Long)2L)) ? 
							  ISVREF(curr,
							  (SI_Long)3L) : 
							  Nil) : Nil;
						  if (kb_properties);
						  else
						      kb_properties = Nil;
						  if (kb_properties) {
						      skip_list = 
							      CDR(kb_properties);
						      key_value = 
							      Class_description_gkbprop;
						      key_hash_value = 
							      SXHASH_SYMBOL_1(Class_description_gkbprop) 
							      & 
							      IFIX(Most_positive_fixnum);
						      bottom_level = 
							      (SI_Long)0L;
						      marked = Nil;
						      pred = M_CAR(skip_list);
						      curr = Nil;
						      succ = Nil;
						      level = (SI_Long)31L;
						      ab_loop_bind_ = 
							      bottom_level;
						    next_loop_55:
						      if (level < 
							      ab_loop_bind_)
							  goto end_loop_55;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						    next_loop_56:
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						    next_loop_57:
						      if ( !TRUEP(marked))
							  goto end_loop_56;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						      goto next_loop_57;
						    end_loop_56:
						      entry_hash = 
							      ISVREF(curr,
							      (SI_Long)1L);
						      if (IFIX(entry_hash) 
							      < 
							      key_hash_value 
							      || 
							      IFIX(entry_hash) 
							      == 
							      key_hash_value 
							      &&  
							      !EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L))) {
							  pred = curr;
							  curr = succ;
						      }
						      else
							  goto end_20;
						      goto next_loop_56;
						    end_loop_57:
						    end_20:
						      level = level - 
							      (SI_Long)1L;
						      goto next_loop_55;
						    end_loop_55:;
						      kb_specific_value = 
							      IFIX(ISVREF(curr,
							      (SI_Long)1L)) 
							      == 
							      key_hash_value 
							      ? 
							      (EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L)) 
							      ? 
							      ISVREF(curr,
							      (SI_Long)3L) 
							      : Nil) : Nil;
						      if (kb_specific_value);
						      else
							  kb_specific_value 
								  = 
								  No_specific_property_value;
						  }
						  else
						      kb_specific_value = 
							      No_specific_property_value;
						  if ( 
							  !EQ(kb_specific_value,
							  No_specific_property_value))
						      resulting_value = 
							      kb_specific_value;
						  else {
						      skip_list = 
							      CDR(global_properties);
						      key_value = 
							      Class_description_gkbprop;
						      key_hash_value = 
							      SXHASH_SYMBOL_1(Class_description_gkbprop) 
							      & 
							      IFIX(Most_positive_fixnum);
						      bottom_level = 
							      (SI_Long)0L;
						      marked = Nil;
						      pred = M_CAR(skip_list);
						      curr = Nil;
						      succ = Nil;
						      level = (SI_Long)31L;
						      ab_loop_bind_ = 
							      bottom_level;
						    next_loop_58:
						      if (level < 
							      ab_loop_bind_)
							  goto end_loop_58;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						    next_loop_59:
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						    next_loop_60:
						      if ( !TRUEP(marked))
							  goto end_loop_59;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						      goto next_loop_60;
						    end_loop_59:
						      entry_hash = 
							      ISVREF(curr,
							      (SI_Long)1L);
						      if (IFIX(entry_hash) 
							      < 
							      key_hash_value 
							      || 
							      IFIX(entry_hash) 
							      == 
							      key_hash_value 
							      &&  
							      !EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L))) {
							  pred = curr;
							  curr = succ;
						      }
						      else
							  goto end_21;
						      goto next_loop_59;
						    end_loop_60:
						    end_21:
						      level = level - 
							      (SI_Long)1L;
						      goto next_loop_58;
						    end_loop_58:;
						      resulting_value = 
							      IFIX(ISVREF(curr,
							      (SI_Long)1L)) 
							      == 
							      key_hash_value 
							      ? 
							      (EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L)) 
							      ? 
							      ISVREF(curr,
							      (SI_Long)3L) 
							      : Nil) : Nil;
						      if (resulting_value);
						      else
							  resulting_value 
								  = Nil;
						  }
						  temp = 
							  TRUEP(resulting_value);
					      }
					      else
						  temp = TRUEP(Nil);
					      temp_2 = temp ? 
						      get_foundation_class_for_class(superior) 
						      : Nil;
					  }
					  superior_foundation_class_qm = 
						  temp_2;
					  if (superior_foundation_class_qm) {
					      other_superior = Nil;
					      ab_loop_list_ = CDR(sublist);
					      other_superior_foundation_class_qm 
						      = Nil;
					      ab_loop_it_ = Nil;
					    next_loop_61:
					      if ( !TRUEP(ab_loop_list_))
						  goto end_loop_61;
					      other_superior = 
						      M_CAR(ab_loop_list_);
					      ab_loop_list_ = 
						      M_CDR(ab_loop_list_);
					      temp_2 = EQ(other_superior,
						      parse_result) ? 
						      foundation_class_qm :
						       Qnil;
					      if (temp_2);
					      else {
						  if (SYMBOLP(other_superior)) 
							      {
						      skip_list = 
							      CDR(Symbol_properties_table);
						      key_value = 
							      other_superior;
						      key_hash_value = 
							      SXHASH_SYMBOL_1(other_superior) 
							      & 
							      IFIX(Most_positive_fixnum);
						      bottom_level = 
							      (SI_Long)0L;
						      marked = Nil;
						      pred = M_CAR(skip_list);
						      curr = Nil;
						      succ = Nil;
						      level = (SI_Long)31L;
						      ab_loop_bind_ = 
							      bottom_level;
						    next_loop_62:
						      if (level < 
							      ab_loop_bind_)
							  goto end_loop_62;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						    next_loop_63:
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						    next_loop_64:
						      if ( !TRUEP(marked))
							  goto end_loop_63;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						      goto next_loop_64;
						    end_loop_63:
						      entry_hash = 
							      ISVREF(curr,
							      (SI_Long)1L);
						      if (IFIX(entry_hash) 
							      < 
							      key_hash_value 
							      || 
							      IFIX(entry_hash) 
							      == 
							      key_hash_value 
							      &&  
							      !EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L))) {
							  pred = curr;
							  curr = succ;
						      }
						      else
							  goto end_22;
						      goto next_loop_63;
						    end_loop_64:
						    end_22:
						      level = level - 
							      (SI_Long)1L;
						      goto next_loop_62;
						    end_loop_62:;
						      gensymed_symbol = 
							      IFIX(ISVREF(curr,
							      (SI_Long)1L)) 
							      == 
							      key_hash_value 
							      ? 
							      (EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L)) 
							      ? 
							      ISVREF(curr,
							      (SI_Long)3L) 
							      : Nil) : Nil;
						      if ( 
							      !TRUEP(gensymed_symbol)) 
								  {
							  gensymed_symbol 
								  = 
								  other_superior;
							  temp_1 = 
								  Symbol_properties_table;
							  temp_2 = 
								  FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
								  & 
								  IFIX(Most_positive_fixnum));
							  tail = 
								  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
								  Nil);
							  head = 
								  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
								  tail);
							  new_cons = 
								  ISVREF(Available_lookup_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      svref_arg_1 
								      = 
								      Available_lookup_conses_vector;
							      svref_arg_2 
								      = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(svref_arg_1,
								      svref_arg_2) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_lookup_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  svref_arg_1 
									  = 
									  Available_lookup_conses_tail_vector;
								  svref_arg_2 
									  = 
									  Current_thread_index;
								  SVREF(svref_arg_1,
									  svref_arg_2) 
									  = 
									  Nil;
							      }
							      gensymed_symbol_4 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol_4 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol_4))
							      gensymed_symbol_4 
								      = 
								      replenish_lookup_cons_pool();
							  M_CAR(gensymed_symbol_4) 
								  = 
								  Qsymbol_properties_hash_table;
							  new_cons = 
								  ISVREF(Available_lookup_conses_vector,
								  IFIX(Current_thread_index));
							  if (new_cons) {
							      svref_arg_1 
								      = 
								      Available_lookup_conses_vector;
							      svref_arg_2 
								      = 
								      Current_thread_index;
							      svref_new_value 
								      = 
								      M_CDR(new_cons);
							      SVREF(svref_arg_1,
								      svref_arg_2) 
								      = 
								      svref_new_value;
							      if ( 
								      !TRUEP(ISVREF(Available_lookup_conses_vector,
								      IFIX(Current_thread_index)))) 
									  {
								  svref_arg_1 
									  = 
									  Available_lookup_conses_tail_vector;
								  svref_arg_2 
									  = 
									  Current_thread_index;
								  SVREF(svref_arg_1,
									  svref_arg_2) 
									  = 
									  Nil;
							      }
							      gensymed_symbol_5 
								      = 
								      new_cons;
							  }
							  else
							      gensymed_symbol_5 
								      = Nil;
							  if ( 
								  !TRUEP(gensymed_symbol_5))
							      gensymed_symbol_5 
								      = 
								      replenish_lookup_cons_pool();
							  M_CAR(gensymed_symbol_5) 
								  = head;
							  M_CDR(gensymed_symbol_5) 
								  = tail;
							  inline_note_allocate_cons(gensymed_symbol_5,
								  Qlookup);
							  M_CDR(gensymed_symbol_4) 
								  = 
								  gensymed_symbol_5;
							  inline_note_allocate_cons(gensymed_symbol_4,
								  Qlookup);
							  gensymed_symbol 
								  = 
								  set_skip_list_entry(temp_1,
								  FIX((SI_Long)31L),
								  Qeq,Nil,
								  T,
								  gensymed_symbol,
								  temp_2,
								  gensymed_symbol_4);
						      }
						      global_properties = 
							      gensymed_symbol;
						      skip_list = 
							      CDR(global_properties);
						      key_value = 
							      Current_kb_specific_property_list_property_name;
						      key_hash_value = 
							      SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
							      & 
							      IFIX(Most_positive_fixnum);
						      bottom_level = 
							      (SI_Long)0L;
						      marked = Nil;
						      pred = M_CAR(skip_list);
						      curr = Nil;
						      succ = Nil;
						      level = (SI_Long)31L;
						      ab_loop_bind_ = 
							      bottom_level;
						    next_loop_65:
						      if (level < 
							      ab_loop_bind_)
							  goto end_loop_65;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						    next_loop_66:
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						    next_loop_67:
						      if ( !TRUEP(marked))
							  goto end_loop_66;
						      curr = 
							      ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
							      (SI_Long)0L),
							      level));
						      reference = 
							      ISVREF(ISVREF(curr,
							      (SI_Long)0L),
							      level);
						      temp_1 = 
							      ATOMIC_REF_OBJECT(reference);
						      temp_2 = 
							      (SI_Long)355L 
							      == 
							      ATOMIC_REF_STAMP(reference) 
							      ? T : Nil;
						      result = VALUES_2(temp_1,
							      temp_2);
						      MVS_2(result,succ,
							      marked);
						      goto next_loop_67;
						    end_loop_66:
						      entry_hash = 
							      ISVREF(curr,
							      (SI_Long)1L);
						      if (IFIX(entry_hash) 
							      < 
							      key_hash_value 
							      || 
							      IFIX(entry_hash) 
							      == 
							      key_hash_value 
							      &&  
							      !EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L))) {
							  pred = curr;
							  curr = succ;
						      }
						      else
							  goto end_23;
						      goto next_loop_66;
						    end_loop_67:
						    end_23:
						      level = level - 
							      (SI_Long)1L;
						      goto next_loop_65;
						    end_loop_65:;
						      kb_properties = 
							      IFIX(ISVREF(curr,
							      (SI_Long)1L)) 
							      == 
							      key_hash_value 
							      ? 
							      (EQ(key_value,
							      ISVREF(curr,
							      (SI_Long)2L)) 
							      ? 
							      ISVREF(curr,
							      (SI_Long)3L) 
							      : Nil) : Nil;
						      if (kb_properties);
						      else
							  kb_properties = Nil;
						      if (kb_properties) {
							  skip_list = 
								  CDR(kb_properties);
							  key_value = 
								  Class_description_gkbprop;
							  key_hash_value = 
								  SXHASH_SYMBOL_1(Class_description_gkbprop) 
								  & 
								  IFIX(Most_positive_fixnum);
							  bottom_level = 
								  (SI_Long)0L;
							  marked = Nil;
							  pred = 
								  M_CAR(skip_list);
							  curr = Nil;
							  succ = Nil;
							  level = (SI_Long)31L;
							  ab_loop_bind_ = 
								  bottom_level;
							next_loop_68:
							  if (level < 
								  ab_loop_bind_)
							      goto end_loop_68;
							  curr = 
								  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								  (SI_Long)0L),
								  level));
							next_loop_69:
							  reference = 
								  ISVREF(ISVREF(curr,
								  (SI_Long)0L),
								  level);
							  temp_1 = 
								  ATOMIC_REF_OBJECT(reference);
							  temp_2 = 
								  (SI_Long)355L 
								  == 
								  ATOMIC_REF_STAMP(reference) 
								  ? T : Nil;
							  result = VALUES_2(temp_1,
								  temp_2);
							  MVS_2(result,
								  succ,marked);
							next_loop_70:
							  if ( !TRUEP(marked))
							      goto end_loop_69;
							  curr = 
								  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								  (SI_Long)0L),
								  level));
							  reference = 
								  ISVREF(ISVREF(curr,
								  (SI_Long)0L),
								  level);
							  temp_1 = 
								  ATOMIC_REF_OBJECT(reference);
							  temp_2 = 
								  (SI_Long)355L 
								  == 
								  ATOMIC_REF_STAMP(reference) 
								  ? T : Nil;
							  result = VALUES_2(temp_1,
								  temp_2);
							  MVS_2(result,
								  succ,marked);
							  goto next_loop_70;
							end_loop_69:
							  entry_hash = 
								  ISVREF(curr,
								  (SI_Long)1L);
							  if (IFIX(entry_hash) 
								  < 
								  key_hash_value 
								  || 
								  IFIX(entry_hash) 
								  == 
								  key_hash_value 
								  &&  
								  !EQ(key_value,
								  ISVREF(curr,
								  (SI_Long)2L))) 
								      {
							      pred = curr;
							      curr = succ;
							  }
							  else
							      goto end_24;
							  goto next_loop_69;
							end_loop_70:
							end_24:
							  level = level - 
								  (SI_Long)1L;
							  goto next_loop_68;
							end_loop_68:;
							  kb_specific_value 
								  = 
								  IFIX(ISVREF(curr,
								  (SI_Long)1L)) 
								  == 
								  key_hash_value 
								  ? 
								  (EQ(key_value,
								  ISVREF(curr,
								  (SI_Long)2L)) 
								  ? 
								  ISVREF(curr,
								  (SI_Long)3L) 
								  : Nil) : Nil;
							  if (kb_specific_value);
							  else
							      kb_specific_value 
								      = 
								      No_specific_property_value;
						      }
						      else
							  kb_specific_value 
								  = 
								  No_specific_property_value;
						      if ( 
							      !EQ(kb_specific_value,
							      No_specific_property_value))
							  resulting_value 
								  = 
								  kb_specific_value;
						      else {
							  skip_list = 
								  CDR(global_properties);
							  key_value = 
								  Class_description_gkbprop;
							  key_hash_value = 
								  SXHASH_SYMBOL_1(Class_description_gkbprop) 
								  & 
								  IFIX(Most_positive_fixnum);
							  bottom_level = 
								  (SI_Long)0L;
							  marked = Nil;
							  pred = 
								  M_CAR(skip_list);
							  curr = Nil;
							  succ = Nil;
							  level = (SI_Long)31L;
							  ab_loop_bind_ = 
								  bottom_level;
							next_loop_71:
							  if (level < 
								  ab_loop_bind_)
							      goto end_loop_71;
							  curr = 
								  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								  (SI_Long)0L),
								  level));
							next_loop_72:
							  reference = 
								  ISVREF(ISVREF(curr,
								  (SI_Long)0L),
								  level);
							  temp_1 = 
								  ATOMIC_REF_OBJECT(reference);
							  temp_2 = 
								  (SI_Long)355L 
								  == 
								  ATOMIC_REF_STAMP(reference) 
								  ? T : Nil;
							  result = VALUES_2(temp_1,
								  temp_2);
							  MVS_2(result,
								  succ,marked);
							next_loop_73:
							  if ( !TRUEP(marked))
							      goto end_loop_72;
							  curr = 
								  ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								  (SI_Long)0L),
								  level));
							  reference = 
								  ISVREF(ISVREF(curr,
								  (SI_Long)0L),
								  level);
							  temp_1 = 
								  ATOMIC_REF_OBJECT(reference);
							  temp_2 = 
								  (SI_Long)355L 
								  == 
								  ATOMIC_REF_STAMP(reference) 
								  ? T : Nil;
							  result = VALUES_2(temp_1,
								  temp_2);
							  MVS_2(result,
								  succ,marked);
							  goto next_loop_73;
							end_loop_72:
							  entry_hash = 
								  ISVREF(curr,
								  (SI_Long)1L);
							  if (IFIX(entry_hash) 
								  < 
								  key_hash_value 
								  || 
								  IFIX(entry_hash) 
								  == 
								  key_hash_value 
								  &&  
								  !EQ(key_value,
								  ISVREF(curr,
								  (SI_Long)2L))) 
								      {
							      pred = curr;
							      curr = succ;
							  }
							  else
							      goto end_25;
							  goto next_loop_72;
							end_loop_73:
							end_25:
							  level = level - 
								  (SI_Long)1L;
							  goto next_loop_71;
							end_loop_71:;
							  resulting_value 
								  = 
								  IFIX(ISVREF(curr,
								  (SI_Long)1L)) 
								  == 
								  key_hash_value 
								  ? 
								  (EQ(key_value,
								  ISVREF(curr,
								  (SI_Long)2L)) 
								  ? 
								  ISVREF(curr,
								  (SI_Long)3L) 
								  : Nil) : Nil;
							  if (resulting_value);
							  else
							      resulting_value 
								      = Nil;
						      }
						      temp = 
							      TRUEP(resulting_value);
						  }
						  else
						      temp = TRUEP(Nil);
						  temp_2 = temp ? 
							  get_foundation_class_for_class(other_superior) 
							  : Nil;
					      }
					      other_superior_foundation_class_qm 
						      = temp_2;
					      if (other_superior_foundation_class_qm) 
							  {
						  gensymed_symbol = 
							  lookup_global_or_kb_specific_property_value(superior_foundation_class_qm,
							  Class_description_gkbprop);
						  temp =  
							  !(gensymed_symbol 
							  ? 
							  TRUEP(memq_function(other_superior_foundation_class_qm,
							  ISVREF(gensymed_symbol,
							  (SI_Long)2L))) : 
							  TRUEP(Nil));
					      }
					      else
						  temp = TRUEP(Nil);
					      if (temp) {
						  gensymed_symbol = 
							  lookup_global_or_kb_specific_property_value(other_superior_foundation_class_qm,
							  Class_description_gkbprop);
						  temp =  
							  !(gensymed_symbol 
							  ? 
							  TRUEP(memq_function(superior_foundation_class_qm,
							  ISVREF(gensymed_symbol,
							  (SI_Long)2L))) : 
							  TRUEP(Nil));
					      }
					      else
						  temp = TRUEP(Nil);
					      if (temp) {
						  first_foundation_class_qm 
							  = 
							  superior_foundation_class_qm;
						  temp = 
							  TRUEP(first_foundation_class_qm);
					      }
					      else
						  temp = TRUEP(Nil);
					      if (temp) {
						  second_foundation_class_qm 
							  = 
							  other_superior_foundation_class_qm;
						  ab_loop_it_ = 
							  second_foundation_class_qm;
					      }
					      else
						  ab_loop_it_ = Nil;
					      if (ab_loop_it_)
						  goto end_26;
					      goto next_loop_61;
					    end_loop_61:
					      ab_loop_it_ = Qnil;
					    end_26:;
					  }
					  else
					      ab_loop_it_ = Nil;
					  if (ab_loop_it_)
					      goto end_27;
					  sublist = M_CDR(sublist);
					  goto next_loop_48;
					end_loop_48:
					  ab_loop_it_ = Qnil;
					end_27:;
				      }
				      else
					  ab_loop_it_ = Nil;
				      if (ab_loop_it_) {
					  temp = TRUEP(ab_loop_it_);
					  goto end_28;
				      }
				      goto next_loop_45;
				    end_loop_45:
				      temp = TRUEP(Qnil);
				    end_28:;
				    POP_SPECIAL();
				    if (temp) {
					reclaim_slot_value(possible_class_inheritance_path_qm);
					temp_1 = Bad_phrase;
					temp_2 = 
						invalidates_direct_superiors_for_potential_definition(parse_result,
						first_foundation_class_qm,
						second_foundation_class_qm);
					return VALUES_2(temp_1,temp_2);
				    }
				    else {
					scope_conses = Scope_conses;
					ab_loopvar_ = parse_result;
					ab_loopvar__1 = Nil;
					ab_loopvar__2 = Nil;
					ab_loopvar__3 = Nil;
					potential_definition = Nil;
					PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
						0);
					  ab_loopvar__3 = 
						  lookup_global_or_kb_specific_property_value(ab_loopvar_,
						  Potential_inferior_class_definitions_gkbprop);
					next_loop_74:
					  if ( !TRUEP(ab_loopvar__3))
					      goto end_loop_74;
					  temp_2 = M_CAR(ab_loopvar__3);
					  ab_loopvar__2 = 
						  scope_cons(M_CAR(ab_loopvar__3),
						  ab_loopvar__2);
					  ab_loopvar_ = 
						  lookup_global_or_kb_specific_property_value(ISVREF(M_CAR(ab_loopvar__3),
						  (SI_Long)20L),
						  Potential_inferior_class_definitions_gkbprop);
					  if (ab_loopvar_) {
					      temp_1 = ab_loopvar__1;
					      ab_loopvar__1 = 
						      nconc2(temp_1,
						      scope_cons(ab_loopvar_,
						      Nil));
					  }
					  ab_loopvar__3 = M_CDR(ab_loopvar__3);
					  current_definitions_variable_set 
						  = Nil;
					next_loop_75:
					  if (current_definitions_variable_set)
					      goto end_loop_75;
					  sublist = ab_loopvar__3;
					next_loop_76:
					  if ( !TRUEP(sublist))
					      goto end_loop_76;
					  if ( !TRUEP(sublist))
					      goto end_loop_76;
					  if ( 
						  !TRUEP(memq_function(M_CAR(sublist),
						  ab_loopvar__2))) {
					      ab_loopvar__3 = sublist;
					      current_definitions_variable_set 
						      = T;
					      goto end_loop_76;
					  }
					  sublist = M_CDR(sublist);
					  goto next_loop_76;
					end_loop_76:
					  if ( 
						  !TRUEP(current_definitions_variable_set)) 
						      {
					      ab_loopvar__3 = 
						      CAR(ab_loopvar__1);
					      if (ab_loopvar__1)
						  ab_loopvar__1 = 
							  M_CDR(ab_loopvar__1);
					      else
						  current_definitions_variable_set 
							  = T;
					  }
					  goto next_loop_75;
					end_loop_75:;
					  potential_definition = temp_2;
					  sub_class_bit_vector = 
						  ISVREF(ISVREF(frame,
						  (SI_Long)1L),(SI_Long)19L);
					  superior_class_bit_number = 
						  IFIX(ISVREF(Object_definition_class_description,
						  (SI_Long)18L));
					  sub_class_vector_index = 
						  superior_class_bit_number 
						  >>  -  - (SI_Long)3L;
					  if (sub_class_vector_index < 
						  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
						      {
					      gensymed_symbol_1 = 
						      UBYTE_8_ISAREF_1(sub_class_bit_vector,
						      sub_class_vector_index);
					      gensymed_symbol_2 = (SI_Long)1L;
					      gensymed_symbol_3 = 
						      superior_class_bit_number 
						      & (SI_Long)7L;
					      gensymed_symbol_2 = 
						      gensymed_symbol_2 << 
						      gensymed_symbol_3;
					      gensymed_symbol_1 = 
						      gensymed_symbol_1 & 
						      gensymed_symbol_2;
					      temp = (SI_Long)0L < 
						      gensymed_symbol_1;
					  }
					  else
					      temp = TRUEP(Nil);
					  if (temp) {
					      sub_class_bit_vector = 
						      ISVREF(ISVREF(potential_definition,
						      (SI_Long)1L),
						      (SI_Long)19L);
					      superior_class_bit_number = 
						      IFIX(ISVREF(Object_definition_class_description,
						      (SI_Long)18L));
					      sub_class_vector_index = 
						      superior_class_bit_number 
						      >>  -  - (SI_Long)3L;
					      if (sub_class_vector_index < 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							  {
						  gensymed_symbol_1 = 
							  UBYTE_8_ISAREF_1(sub_class_bit_vector,
							  sub_class_vector_index);
						  gensymed_symbol_2 = 
							  (SI_Long)1L;
						  gensymed_symbol_3 = 
							  superior_class_bit_number 
							  & (SI_Long)7L;
						  gensymed_symbol_2 = 
							  gensymed_symbol_2 
							  << gensymed_symbol_3;
						  gensymed_symbol_1 = 
							  gensymed_symbol_1 
							  & gensymed_symbol_2;
						  temp = (SI_Long)0L < 
							  gensymed_symbol_1;
					      }
					      else
						  temp = TRUEP(Nil);
					  }
					  else {
					      sub_class_bit_vector = 
						      ISVREF(ISVREF(frame,
						      (SI_Long)1L),
						      (SI_Long)19L);
					      superior_class_bit_number = 
						      IFIX(ISVREF(Connection_definition_class_description,
						      (SI_Long)18L));
					      sub_class_vector_index = 
						      superior_class_bit_number 
						      >>  -  - (SI_Long)3L;
					      if (sub_class_vector_index < 
						      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							  {
						  gensymed_symbol_1 = 
							  UBYTE_8_ISAREF_1(sub_class_bit_vector,
							  sub_class_vector_index);
						  gensymed_symbol_2 = 
							  (SI_Long)1L;
						  gensymed_symbol_3 = 
							  superior_class_bit_number 
							  & (SI_Long)7L;
						  gensymed_symbol_2 = 
							  gensymed_symbol_2 
							  << gensymed_symbol_3;
						  gensymed_symbol_1 = 
							  gensymed_symbol_1 
							  & gensymed_symbol_2;
						  temp = (SI_Long)0L < 
							  gensymed_symbol_1;
					      }
					      else
						  temp = TRUEP(Nil);
					      if (temp) {
						  sub_class_bit_vector = 
							  ISVREF(ISVREF(potential_definition,
							  (SI_Long)1L),
							  (SI_Long)19L);
						  superior_class_bit_number 
							  = 
							  IFIX(ISVREF(Connection_definition_class_description,
							  (SI_Long)18L));
						  sub_class_vector_index = 
							  superior_class_bit_number 
							  >>  -  - (SI_Long)3L;
						  if (sub_class_vector_index 
							  < 
							  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							      {
						      gensymed_symbol_1 = 
							      UBYTE_8_ISAREF_1(sub_class_bit_vector,
							      sub_class_vector_index);
						      gensymed_symbol_2 = 
							      (SI_Long)1L;
						      gensymed_symbol_3 = 
							      superior_class_bit_number 
							      & (SI_Long)7L;
						      gensymed_symbol_2 = 
							      gensymed_symbol_2 
							      << 
							      gensymed_symbol_3;
						      gensymed_symbol_1 = 
							      gensymed_symbol_1 
							      & 
							      gensymed_symbol_2;
						      temp = (SI_Long)0L < 
							      gensymed_symbol_1;
						  }
						  else
						      temp = TRUEP(Nil);
					      }
					      else {
						  sub_class_bit_vector = 
							  ISVREF(ISVREF(frame,
							  (SI_Long)1L),
							  (SI_Long)19L);
						  superior_class_bit_number 
							  = 
							  IFIX(ISVREF(Message_definition_class_description,
							  (SI_Long)18L));
						  sub_class_vector_index = 
							  superior_class_bit_number 
							  >>  -  - (SI_Long)3L;
						  if (sub_class_vector_index 
							  < 
							  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							      {
						      gensymed_symbol_1 = 
							      UBYTE_8_ISAREF_1(sub_class_bit_vector,
							      sub_class_vector_index);
						      gensymed_symbol_2 = 
							      (SI_Long)1L;
						      gensymed_symbol_3 = 
							      superior_class_bit_number 
							      & (SI_Long)7L;
						      gensymed_symbol_2 = 
							      gensymed_symbol_2 
							      << 
							      gensymed_symbol_3;
						      gensymed_symbol_1 = 
							      gensymed_symbol_1 
							      & 
							      gensymed_symbol_2;
						      temp = (SI_Long)0L < 
							      gensymed_symbol_1;
						  }
						  else
						      temp = TRUEP(Nil);
						  if (temp) {
						      sub_class_bit_vector 
							      = 
							      ISVREF(ISVREF(potential_definition,
							      (SI_Long)1L),
							      (SI_Long)19L);
						      superior_class_bit_number 
							      = 
							      IFIX(ISVREF(Message_definition_class_description,
							      (SI_Long)18L));
						      sub_class_vector_index 
							      = 
							      superior_class_bit_number 
							      >>  -  - 
							      (SI_Long)3L;
						      if (sub_class_vector_index 
							      < 
							      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								  {
							  gensymed_symbol_1 
								  = 
								  UBYTE_8_ISAREF_1(sub_class_bit_vector,
								  sub_class_vector_index);
							  gensymed_symbol_2 
								  = 
								  (SI_Long)1L;
							  gensymed_symbol_3 
								  = 
								  superior_class_bit_number 
								  & 
								  (SI_Long)7L;
							  gensymed_symbol_2 
								  = 
								  gensymed_symbol_2 
								  << 
								  gensymed_symbol_3;
							  gensymed_symbol_1 
								  = 
								  gensymed_symbol_1 
								  & 
								  gensymed_symbol_2;
							  temp = 
								  (SI_Long)0L 
								  < gensymed_symbol_1;
						      }
						      else
							  temp = TRUEP(Nil);
						  }
						  else {
						      sub_class_bit_vector 
							      = 
							      ISVREF(ISVREF(frame,
							      (SI_Long)1L),
							      (SI_Long)19L);
						      superior_class_bit_number 
							      = 
							      IFIX(ISVREF(Class_definition_class_description,
							      (SI_Long)18L));
						      sub_class_vector_index 
							      = 
							      superior_class_bit_number 
							      >>  -  - 
							      (SI_Long)3L;
						      if (sub_class_vector_index 
							      < 
							      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
								  {
							  gensymed_symbol_1 
								  = 
								  UBYTE_8_ISAREF_1(sub_class_bit_vector,
								  sub_class_vector_index);
							  gensymed_symbol_2 
								  = 
								  (SI_Long)1L;
							  gensymed_symbol_3 
								  = 
								  superior_class_bit_number 
								  & 
								  (SI_Long)7L;
							  gensymed_symbol_2 
								  = 
								  gensymed_symbol_2 
								  << 
								  gensymed_symbol_3;
							  gensymed_symbol_1 
								  = 
								  gensymed_symbol_1 
								  & 
								  gensymed_symbol_2;
							  temp = 
								  (SI_Long)0L 
								  < gensymed_symbol_1;
						      }
						      else
							  temp = TRUEP(Nil);
						      if (temp)
							  temp =  
								  !TRUEP(definition_class_is_subclass_of_obj_conn_mess_definition_p(potential_definition));
						      else
							  temp = TRUEP(Nil);
						  }
					      }
					  }
					  if (temp);
					  else
					      temp = 
						      EQ(specialized_definition_class,
						      Qclass_definition);
					  if (temp);
					  else
					      temp = 
						      EQ(get_specialized_definition_class(potential_definition),
						      Qclass_definition);
					  if ( !temp) {
					      potential_definition_qm = 
						      potential_definition;
					      potential_definition_definition_type_qm 
						      = 
						      get_specialized_definition_class(potential_definition);
					      temp = 
						      TRUEP(potential_definition_definition_type_qm);
					      goto end_29;
					  }
					  goto next_loop_74;
					end_loop_74:
					  temp = TRUEP(Qnil);
					end_29:;
					POP_SPECIAL();
					if (temp) {
					    reclaim_slot_value(possible_class_inheritance_path_qm);
					    temp_1 = Bad_phrase;
					    temp_2 = 
						    potential_definition_class_type_is_incompatible(potential_definition_qm,
						    potential_definition_definition_type_qm,
						    Qsubclass);
					    return VALUES_2(temp_1,temp_2);
					}
					else {
					    scope_conses = Scope_conses;
					    ab_loopvar_ = parse_result;
					    ab_loopvar__1 = Nil;
					    ab_loopvar__2 = Nil;
					    ab_loopvar__3 = Nil;
					    potential_definition = Nil;
					    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
						    0);
					      direct_superiors_qm = Nil;
					      ab_loopvar__3 = 
						      lookup_global_or_kb_specific_property_value(ab_loopvar_,
						      Potential_inferior_class_definitions_gkbprop);
					    next_loop_77:
					      if ( !TRUEP(ab_loopvar__3))
						  goto end_loop_77;
					      temp_2 = M_CAR(ab_loopvar__3);
					      ab_loopvar__2 = 
						      scope_cons(M_CAR(ab_loopvar__3),
						      ab_loopvar__2);
					      ab_loopvar_ = 
						      lookup_global_or_kb_specific_property_value(ISVREF(M_CAR(ab_loopvar__3),
						      (SI_Long)20L),
						      Potential_inferior_class_definitions_gkbprop);
					      if (ab_loopvar_) {
						  temp_1 = ab_loopvar__1;
						  ab_loopvar__1 = 
							  nconc2(temp_1,
							  scope_cons(ab_loopvar_,
							  Nil));
					      }
					      ab_loopvar__3 = 
						      M_CDR(ab_loopvar__3);
					      current_definitions_variable_set 
						      = Nil;
					    next_loop_78:
					      if (current_definitions_variable_set)
						  goto end_loop_78;
					      sublist = ab_loopvar__3;
					    next_loop_79:
					      if ( !TRUEP(sublist))
						  goto end_loop_79;
					      if ( !TRUEP(sublist))
						  goto end_loop_79;
					      if ( 
						      !TRUEP(memq_function(M_CAR(sublist),
						      ab_loopvar__2))) {
						  ab_loopvar__3 = sublist;
						  current_definitions_variable_set 
							  = T;
						  goto end_loop_79;
					      }
					      sublist = M_CDR(sublist);
					      goto next_loop_79;
					    end_loop_79:
					      if ( 
						      !TRUEP(current_definitions_variable_set)) 
							  {
						  ab_loopvar__3 = 
							  CAR(ab_loopvar__1);
						  if (ab_loopvar__1)
						      ab_loopvar__1 = 
							      M_CDR(ab_loopvar__1);
						  else
						      current_definitions_variable_set 
							      = T;
					      }
					      goto next_loop_78;
					    end_loop_78:;
					      potential_definition = temp_2;
					      direct_superiors_qm = 
						      ISVREF(potential_definition,
						      (SI_Long)21L);
					      prohibited_superior_qm = 
						      direct_superiors_qm ?
						       
						      incorrect_foundation_class_for_this_definition_p(direct_superiors_qm,
						      class_primary_foundation_class,
						      Nil) : Qnil;
					      if (prohibited_superior_qm) {
						  potential_definition_qm 
							  = 
							  potential_definition;
						  temp = 
							  TRUEP(potential_definition_qm);
						  goto end_30;
					      }
					      goto next_loop_77;
					    end_loop_77:
					      temp = TRUEP(Qnil);
					    end_30:;
					    POP_SPECIAL();
					    if (temp) {
						reclaim_slot_value(possible_class_inheritance_path_qm);
						temp_1 = Bad_phrase;
						sub_class_bit_vector = 
							ISVREF(ISVREF(potential_definition_qm,
							(SI_Long)1L),
							(SI_Long)19L);
						superior_class_bit_number 
							= 
							IFIX(ISVREF(Class_definition_class_description,
							(SI_Long)18L));
						sub_class_vector_index = 
							superior_class_bit_number 
							>>  -  - (SI_Long)3L;
						if (sub_class_vector_index 
							< 
							IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
							    {
						    gensymed_symbol_1 = 
							    UBYTE_8_ISAREF_1(sub_class_bit_vector,
							    sub_class_vector_index);
						    gensymed_symbol_2 = 
							    (SI_Long)1L;
						    gensymed_symbol_3 = 
							    superior_class_bit_number 
							    & (SI_Long)7L;
						    gensymed_symbol_2 = 
							    gensymed_symbol_2 
							    << 
							    gensymed_symbol_3;
						    gensymed_symbol_1 = 
							    gensymed_symbol_1 
							    & 
							    gensymed_symbol_2;
						    temp = (SI_Long)0L < 
							    gensymed_symbol_1;
						}
						else
						    temp = TRUEP(Nil);
						temp_2 = temp ? 
							potential_definition_superior_not_the_mixed_hierarchy_type(frame,
							potential_definition_qm,
							prohibited_superior_qm) 
							: 
							potential_definition_has_different_class_type(parse_result,
							specialized_definition_class,
							potential_definition_qm);
						return VALUES_2(temp_1,temp_2);
					    }
					    else {
						if (direct_superior_classes_qm) 
							    {
						    scope_conses = 
							    Scope_conses;
						    ab_loopvar_ = parse_result;
						    ab_loopvar__1 = Nil;
						    ab_loopvar__2 = Nil;
						    ab_loopvar__3 = Nil;
						    potential_definition = Nil;
						    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
							    0);
						      potential_specialized_definition_class 
							      = Nil;
						      potential_primary_foundation_class 
							      = Nil;
						      ab_loopvar__3 = 
							      lookup_global_or_kb_specific_property_value(ab_loopvar_,
							      Potential_inferior_class_definitions_gkbprop);
						    next_loop_80:
						      if ( 
							      !TRUEP(ab_loopvar__3))
							  goto end_loop_80;
						      temp_2 = 
							      M_CAR(ab_loopvar__3);
						      ab_loopvar__2 = 
							      scope_cons(M_CAR(ab_loopvar__3),
							      ab_loopvar__2);
						      ab_loopvar_ = 
							      lookup_global_or_kb_specific_property_value(ISVREF(M_CAR(ab_loopvar__3),
							      (SI_Long)20L),
							      Potential_inferior_class_definitions_gkbprop);
						      if (ab_loopvar_) {
							  temp_1 = 
								  ab_loopvar__1;
							  ab_loopvar__1 = 
								  nconc2(temp_1,
								  scope_cons(ab_loopvar_,
								  Nil));
						      }
						      ab_loopvar__3 = 
							      M_CDR(ab_loopvar__3);
						      current_definitions_variable_set 
							      = Nil;
						    next_loop_81:
						      if (current_definitions_variable_set)
							  goto end_loop_81;
						      sublist = ab_loopvar__3;
						    next_loop_82:
						      if ( !TRUEP(sublist))
							  goto end_loop_82;
						      if ( !TRUEP(sublist))
							  goto end_loop_82;
						      if ( 
							      !TRUEP(memq_function(M_CAR(sublist),
							      ab_loopvar__2))) 
								  {
							  ab_loopvar__3 = 
								  sublist;
							  current_definitions_variable_set 
								  = T;
							  goto end_loop_82;
						      }
						      sublist = M_CDR(sublist);
						      goto next_loop_82;
						    end_loop_82:
						      if ( 
							      !TRUEP(current_definitions_variable_set)) 
								  {
							  ab_loopvar__3 = 
								  CAR(ab_loopvar__1);
							  if (ab_loopvar__1)
							      ab_loopvar__1 
								      = 
								      M_CDR(ab_loopvar__1);
							  else
							      current_definitions_variable_set 
								      = T;
						      }
						      goto next_loop_81;
						    end_loop_81:;
						      potential_definition 
							      = temp_2;
						      potential_specialized_definition_class 
							      = 
							      get_specialized_definition_class(potential_definition);
						      if (EQ(potential_specialized_definition_class,
							      Qobject_definition))
							  potential_primary_foundation_class 
								  = Qobject;
						      else if (EQ(potential_specialized_definition_class,
							      Qmessage_definition))
							  potential_primary_foundation_class 
								  = Qmessage;
						      else if (EQ(potential_specialized_definition_class,
							      Qconnection_definition))
							  potential_primary_foundation_class 
								  = 
								  Qconnection;
						      else
							  potential_primary_foundation_class 
								  = Qitem;
						      prohibited_superior_qm 
							      = 
							      incorrect_foundation_class_for_this_definition_p(direct_superior_classes_qm,
							      potential_primary_foundation_class,
							      Nil);
						      if (prohibited_superior_qm) 
								  {
							  potential_specialized_definition_class_qm 
								  = 
								  potential_specialized_definition_class;
							  potential_definition_qm 
								  = 
								  potential_definition;
							  temp = 
								  TRUEP(potential_definition_qm);
							  goto end_31;
						      }
						      goto next_loop_80;
						    end_loop_80:
						      temp = TRUEP(Qnil);
						    end_31:;
						    POP_SPECIAL();
						}
						else
						    temp = TRUEP(Nil);
						if (temp) {
						    temp_1 = Bad_phrase;
						    temp_2 = 
							    potential_definition_cannot_inherit_foundation_class(prohibited_superior_qm,
							    potential_definition_qm,
							    potential_specialized_definition_class_qm);
						    return VALUES_2(temp_1,
							    temp_2);
						}
						else {
						    if (possible_class_inheritance_path_qm) 
								{
							potential_inferior_definition 
								= Nil;
							ab_loop_list_ = 
								lookup_global_or_kb_specific_property_value(parse_result,
								Potential_inferior_class_definitions_gkbprop);
							direct_superiors = Nil;
							other_direct_superiors_not_defined_qm 
								= Nil;
						      next_loop_83:
							if ( 
								!TRUEP(ab_loop_list_))
							    goto end_loop_83;
							potential_inferior_definition 
								= 
								M_CAR(ab_loop_list_);
							ab_loop_list_ = 
								M_CDR(ab_loop_list_);
							direct_superiors = 
								ISVREF(potential_inferior_definition,
								(SI_Long)21L);
							superior = Nil;
							ab_loop_list__1 = 
								direct_superiors;
							ab_loop_it_ = Nil;
						      next_loop_84:
							if ( 
								!TRUEP(ab_loop_list__1))
							    goto end_loop_84;
							superior = 
								M_CAR(ab_loop_list__1);
							ab_loop_list__1 = 
								M_CDR(ab_loop_list__1);
							temp = EQ(superior,
								parse_result);
							if (temp);
							else if (SYMBOLP(superior)) 
								    {
							    skip_list = 
								    CDR(Symbol_properties_table);
							    key_value = 
								    superior;
							    key_hash_value 
								    = 
								    SXHASH_SYMBOL_1(superior) 
								    & 
								    IFIX(Most_positive_fixnum);
							    bottom_level = 
								    (SI_Long)0L;
							    marked = Nil;
							    pred = 
								    M_CAR(skip_list);
							    curr = Nil;
							    succ = Nil;
							    level = 
								    (SI_Long)31L;
							    ab_loop_bind_ 
								    = 
								    bottom_level;
							  next_loop_85:
							    if (level < 
								    ab_loop_bind_)
								goto end_loop_85;
							    curr = 
								    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								    (SI_Long)0L),
								    level));
							  next_loop_86:
							    reference = 
								    ISVREF(ISVREF(curr,
								    (SI_Long)0L),
								    level);
							    temp_1 = 
								    ATOMIC_REF_OBJECT(reference);
							    temp_2 = 
								    (SI_Long)355L 
								    == 
								    ATOMIC_REF_STAMP(reference) 
								    ? T : Nil;
							    result = VALUES_2(temp_1,
								    temp_2);
							    MVS_2(result,
								    succ,
								    marked);
							  next_loop_87:
							    if ( 
								    !TRUEP(marked))
								goto end_loop_86;
							    curr = 
								    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								    (SI_Long)0L),
								    level));
							    reference = 
								    ISVREF(ISVREF(curr,
								    (SI_Long)0L),
								    level);
							    temp_1 = 
								    ATOMIC_REF_OBJECT(reference);
							    temp_2 = 
								    (SI_Long)355L 
								    == 
								    ATOMIC_REF_STAMP(reference) 
								    ? T : Nil;
							    result = VALUES_2(temp_1,
								    temp_2);
							    MVS_2(result,
								    succ,
								    marked);
							    goto next_loop_87;
							  end_loop_86:
							    entry_hash = 
								    ISVREF(curr,
								    (SI_Long)1L);
							    if (IFIX(entry_hash) 
								    < 
								    key_hash_value 
								    || 
								    IFIX(entry_hash) 
								    == 
								    key_hash_value 
								    &&  
								    !EQ(key_value,
								    ISVREF(curr,
								    (SI_Long)2L))) 
									{
								pred = curr;
								curr = succ;
							    }
							    else
								goto end_32;
							    goto next_loop_86;
							  end_loop_87:
							  end_32:
							    level = level 
								    - 
								    (SI_Long)1L;
							    goto next_loop_85;
							  end_loop_85:;
							    gensymed_symbol 
								    = 
								    IFIX(ISVREF(curr,
								    (SI_Long)1L)) 
								    == 
								    key_hash_value 
								    ? 
								    (EQ(key_value,
								    ISVREF(curr,
								    (SI_Long)2L)) 
								    ? 
								    ISVREF(curr,
								    (SI_Long)3L) 
								    : Nil) 
								    : Nil;
							    if ( 
								    !TRUEP(gensymed_symbol)) 
									{
								gensymed_symbol 
									= 
									superior;
								temp_1 = 
									Symbol_properties_table;
								temp_2 = 
									FIX(SXHASH_SYMBOL_1(gensymed_symbol) 
									& 
									IFIX(Most_positive_fixnum));
								tail = 
									make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
									Nil);
								head = 
									make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
									tail);
								new_cons = 
									ISVREF(Available_lookup_conses_vector,
									IFIX(Current_thread_index));
								if (new_cons) {
								    svref_arg_1 
									    = 
									    Available_lookup_conses_vector;
								    svref_arg_2 
									    = 
									    Current_thread_index;
								    svref_new_value 
									    = 
									    M_CDR(new_cons);
								    SVREF(svref_arg_1,
									    svref_arg_2) 
									    = 
									    svref_new_value;
								    if ( 
									    !TRUEP(ISVREF(Available_lookup_conses_vector,
									    IFIX(Current_thread_index)))) 
										{
									svref_arg_1 
										= 
										Available_lookup_conses_tail_vector;
									svref_arg_2 
										= 
										Current_thread_index;
									SVREF(svref_arg_1,
										svref_arg_2) 
										= 
										Nil;
								    }
								    gensymed_symbol_4 
									    = 
									    new_cons;
								}
								else
								    gensymed_symbol_4 
									    = 
									    Nil;
								if ( 
									!TRUEP(gensymed_symbol_4))
								    gensymed_symbol_4 
									    = 
									    replenish_lookup_cons_pool();
								M_CAR(gensymed_symbol_4) 
									= 
									Qsymbol_properties_hash_table;
								new_cons = 
									ISVREF(Available_lookup_conses_vector,
									IFIX(Current_thread_index));
								if (new_cons) {
								    svref_arg_1 
									    = 
									    Available_lookup_conses_vector;
								    svref_arg_2 
									    = 
									    Current_thread_index;
								    svref_new_value 
									    = 
									    M_CDR(new_cons);
								    SVREF(svref_arg_1,
									    svref_arg_2) 
									    = 
									    svref_new_value;
								    if ( 
									    !TRUEP(ISVREF(Available_lookup_conses_vector,
									    IFIX(Current_thread_index)))) 
										{
									svref_arg_1 
										= 
										Available_lookup_conses_tail_vector;
									svref_arg_2 
										= 
										Current_thread_index;
									SVREF(svref_arg_1,
										svref_arg_2) 
										= 
										Nil;
								    }
								    gensymed_symbol_5 
									    = 
									    new_cons;
								}
								else
								    gensymed_symbol_5 
									    = 
									    Nil;
								if ( 
									!TRUEP(gensymed_symbol_5))
								    gensymed_symbol_5 
									    = 
									    replenish_lookup_cons_pool();
								M_CAR(gensymed_symbol_5) 
									= head;
								M_CDR(gensymed_symbol_5) 
									= tail;
								inline_note_allocate_cons(gensymed_symbol_5,
									Qlookup);
								M_CDR(gensymed_symbol_4) 
									= 
									gensymed_symbol_5;
								inline_note_allocate_cons(gensymed_symbol_4,
									Qlookup);
								gensymed_symbol 
									= 
									set_skip_list_entry(temp_1,
									FIX((SI_Long)31L),
									Qeq,
									Nil,
									T,
									gensymed_symbol,
									temp_2,
									gensymed_symbol_4);
							    }
							    global_properties 
								    = 
								    gensymed_symbol;
							    skip_list = 
								    CDR(global_properties);
							    key_value = 
								    Current_kb_specific_property_list_property_name;
							    key_hash_value 
								    = 
								    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
								    & 
								    IFIX(Most_positive_fixnum);
							    bottom_level = 
								    (SI_Long)0L;
							    marked = Nil;
							    pred = 
								    M_CAR(skip_list);
							    curr = Nil;
							    succ = Nil;
							    level = 
								    (SI_Long)31L;
							    ab_loop_bind_ 
								    = 
								    bottom_level;
							  next_loop_88:
							    if (level < 
								    ab_loop_bind_)
								goto end_loop_88;
							    curr = 
								    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								    (SI_Long)0L),
								    level));
							  next_loop_89:
							    reference = 
								    ISVREF(ISVREF(curr,
								    (SI_Long)0L),
								    level);
							    temp_1 = 
								    ATOMIC_REF_OBJECT(reference);
							    temp_2 = 
								    (SI_Long)355L 
								    == 
								    ATOMIC_REF_STAMP(reference) 
								    ? T : Nil;
							    result = VALUES_2(temp_1,
								    temp_2);
							    MVS_2(result,
								    succ,
								    marked);
							  next_loop_90:
							    if ( 
								    !TRUEP(marked))
								goto end_loop_89;
							    curr = 
								    ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
								    (SI_Long)0L),
								    level));
							    reference = 
								    ISVREF(ISVREF(curr,
								    (SI_Long)0L),
								    level);
							    temp_1 = 
								    ATOMIC_REF_OBJECT(reference);
							    temp_2 = 
								    (SI_Long)355L 
								    == 
								    ATOMIC_REF_STAMP(reference) 
								    ? T : Nil;
							    result = VALUES_2(temp_1,
								    temp_2);
							    MVS_2(result,
								    succ,
								    marked);
							    goto next_loop_90;
							  end_loop_89:
							    entry_hash = 
								    ISVREF(curr,
								    (SI_Long)1L);
							    if (IFIX(entry_hash) 
								    < 
								    key_hash_value 
								    || 
								    IFIX(entry_hash) 
								    == 
								    key_hash_value 
								    &&  
								    !EQ(key_value,
								    ISVREF(curr,
								    (SI_Long)2L))) 
									{
								pred = curr;
								curr = succ;
							    }
							    else
								goto end_33;
							    goto next_loop_89;
							  end_loop_90:
							  end_33:
							    level = level 
								    - 
								    (SI_Long)1L;
							    goto next_loop_88;
							  end_loop_88:;
							    kb_properties 
								    = 
								    IFIX(ISVREF(curr,
								    (SI_Long)1L)) 
								    == 
								    key_hash_value 
								    ? 
								    (EQ(key_value,
								    ISVREF(curr,
								    (SI_Long)2L)) 
								    ? 
								    ISVREF(curr,
								    (SI_Long)3L) 
								    : Nil) 
								    : Nil;
							    if (kb_properties);
							    else
								kb_properties 
									= Nil;
							    if (kb_properties) 
									{
								skip_list 
									= 
									CDR(kb_properties);
								key_value 
									= 
									Class_description_gkbprop;
								key_hash_value 
									= 
									SXHASH_SYMBOL_1(Class_description_gkbprop) 
									& 
									IFIX(Most_positive_fixnum);
								bottom_level 
									= 
									(SI_Long)0L;
								marked = Nil;
								pred = 
									M_CAR(skip_list);
								curr = Nil;
								succ = Nil;
								level = 
									(SI_Long)31L;
								ab_loop_bind_ 
									= 
									bottom_level;
							      next_loop_91:
								if (level 
									< 
									ab_loop_bind_)
								    goto end_loop_91;
								curr = 
									ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
									(SI_Long)0L),
									level));
							      next_loop_92:
								reference 
									= 
									ISVREF(ISVREF(curr,
									(SI_Long)0L),
									level);
								temp_1 = 
									ATOMIC_REF_OBJECT(reference);
								temp_2 = 
									(SI_Long)355L 
									== 
									ATOMIC_REF_STAMP(reference) 
									? 
									T : Nil;
								result = VALUES_2(temp_1,
									temp_2);
								MVS_2(result,
									succ,
									marked);
							      next_loop_93:
								if ( 
									!TRUEP(marked))
								    goto end_loop_92;
								curr = 
									ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
									(SI_Long)0L),
									level));
								reference 
									= 
									ISVREF(ISVREF(curr,
									(SI_Long)0L),
									level);
								temp_1 = 
									ATOMIC_REF_OBJECT(reference);
								temp_2 = 
									(SI_Long)355L 
									== 
									ATOMIC_REF_STAMP(reference) 
									? 
									T : Nil;
								result = VALUES_2(temp_1,
									temp_2);
								MVS_2(result,
									succ,
									marked);
								goto next_loop_93;
							      end_loop_92:
								entry_hash 
									= 
									ISVREF(curr,
									(SI_Long)1L);
								if (IFIX(entry_hash) 
									< 
									key_hash_value 
									|| 
									IFIX(entry_hash) 
									== 
									key_hash_value 
									&& 
									 
									!EQ(key_value,
									ISVREF(curr,
									(SI_Long)2L))) 
									    {
								    pred = 
									    curr;
								    curr = 
									    succ;
								}
								else
								    goto end_34;
								goto next_loop_92;
							      end_loop_93:
							      end_34:
								level = 
									level 
									- 
									(SI_Long)1L;
								goto next_loop_91;
							      end_loop_91:;
								kb_specific_value 
									= 
									IFIX(ISVREF(curr,
									(SI_Long)1L)) 
									== 
									key_hash_value 
									? 
									(EQ(key_value,
									ISVREF(curr,
									(SI_Long)2L)) 
									? 
									ISVREF(curr,
									(SI_Long)3L) 
									: 
									Nil) 
									: Nil;
								if (kb_specific_value);
								else
								    kb_specific_value 
									    = 
									    No_specific_property_value;
							    }
							    else
								kb_specific_value 
									= 
									No_specific_property_value;
							    if ( 
								    !EQ(kb_specific_value,
								    No_specific_property_value))
								resulting_value 
									= 
									kb_specific_value;
							    else {
								skip_list 
									= 
									CDR(global_properties);
								key_value 
									= 
									Class_description_gkbprop;
								key_hash_value 
									= 
									SXHASH_SYMBOL_1(Class_description_gkbprop) 
									& 
									IFIX(Most_positive_fixnum);
								bottom_level 
									= 
									(SI_Long)0L;
								marked = Nil;
								pred = 
									M_CAR(skip_list);
								curr = Nil;
								succ = Nil;
								level = 
									(SI_Long)31L;
								ab_loop_bind_ 
									= 
									bottom_level;
							      next_loop_94:
								if (level 
									< 
									ab_loop_bind_)
								    goto end_loop_94;
								curr = 
									ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
									(SI_Long)0L),
									level));
							      next_loop_95:
								reference 
									= 
									ISVREF(ISVREF(curr,
									(SI_Long)0L),
									level);
								temp_1 = 
									ATOMIC_REF_OBJECT(reference);
								temp_2 = 
									(SI_Long)355L 
									== 
									ATOMIC_REF_STAMP(reference) 
									? 
									T : Nil;
								result = VALUES_2(temp_1,
									temp_2);
								MVS_2(result,
									succ,
									marked);
							      next_loop_96:
								if ( 
									!TRUEP(marked))
								    goto end_loop_95;
								curr = 
									ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
									(SI_Long)0L),
									level));
								reference 
									= 
									ISVREF(ISVREF(curr,
									(SI_Long)0L),
									level);
								temp_1 = 
									ATOMIC_REF_OBJECT(reference);
								temp_2 = 
									(SI_Long)355L 
									== 
									ATOMIC_REF_STAMP(reference) 
									? 
									T : Nil;
								result = VALUES_2(temp_1,
									temp_2);
								MVS_2(result,
									succ,
									marked);
								goto next_loop_96;
							      end_loop_95:
								entry_hash 
									= 
									ISVREF(curr,
									(SI_Long)1L);
								if (IFIX(entry_hash) 
									< 
									key_hash_value 
									|| 
									IFIX(entry_hash) 
									== 
									key_hash_value 
									&& 
									 
									!EQ(key_value,
									ISVREF(curr,
									(SI_Long)2L))) 
									    {
								    pred = 
									    curr;
								    curr = 
									    succ;
								}
								else
								    goto end_35;
								goto next_loop_95;
							      end_loop_96:
							      end_35:
								level = 
									level 
									- 
									(SI_Long)1L;
								goto next_loop_94;
							      end_loop_94:;
								resulting_value 
									= 
									IFIX(ISVREF(curr,
									(SI_Long)1L)) 
									== 
									key_hash_value 
									? 
									(EQ(key_value,
									ISVREF(curr,
									(SI_Long)2L)) 
									? 
									ISVREF(curr,
									(SI_Long)3L) 
									: 
									Nil) 
									: Nil;
								if (resulting_value);
								else
								    resulting_value 
									    = 
									    Nil;
							    }
							    temp = 
								    TRUEP(resulting_value);
							}
							else
							    temp = TRUEP(Nil);
							ab_loop_it_ =  
								!temp ? T :
								 Nil;
							if (ab_loop_it_) {
							    other_direct_superiors_not_defined_qm 
								    = 
								    ab_loop_it_;
							    goto end_36;
							}
							goto next_loop_84;
						      end_loop_84:
							other_direct_superiors_not_defined_qm 
								= Qnil;
						      end_36:;
							if ( !( 
								!TRUEP(CDR(direct_superiors)) 
								|| 
								other_direct_superiors_not_defined_qm)) 
								    {
							    paths = Nil;
							    superior = Nil;
							    ab_loop_list__1 
								    = 
								    direct_superiors;
							  next_loop_97:
							    if ( 
								    !TRUEP(ab_loop_list__1))
								goto end_loop_97;
							    superior = 
								    M_CAR(ab_loop_list__1);
							    ab_loop_list__1 
								    = 
								    M_CDR(ab_loop_list__1);
							    if (EQ(superior,
								    parse_result))
								paths = 
									nconc2(paths,
									frame_cons_1(possible_class_inheritance_path_qm,
									Nil));
							    else {
								class_description 
									= 
									lookup_global_or_kb_specific_property_value(superior,
									Class_description_gkbprop);
								paths = 
									nconc2(paths,
									frame_cons_1(ISVREF(class_description,
									(SI_Long)2L),
									Nil));
							    }
							    goto next_loop_97;
							  end_loop_97:;
							    class_inheritance_paths 
								    = paths;
							    result = merging_paths_common_ancestor_rule_2_violation_p(class_inheritance_paths);
							    MVS_2(result,
								    prohibited_superior_qm,
								    colliding_superior_qm);
							    reclaim_frame_list_1(class_inheritance_paths);
							}
							goto next_loop_83;
						      end_loop_83:
							temp = TRUEP(Qnil);
						    }
						    else
							temp = TRUEP(Nil);
						    if (temp) {
							reclaim_slot_value(possible_class_inheritance_path_qm);
							temp_1 = Bad_phrase;
							temp_2 = 
								direct_superiors_give_ancestors_different_precedence(prohibited_superior_qm,
								colliding_superior_qm,
								problem_inferior_class_qm,
								inferior_potential_definition_qm);
							return VALUES_2(temp_1,
								temp_2);
						    }
						    else {
							reclaim_slot_value(possible_class_inheritance_path_qm);
							return VALUES_1(parse_result);
						    }
						}
					    }
					}
				    }
				}
			    }
			}
		    }
		}
	    }
	}
    }
    else
	return VALUES_1(parse_result);
}

DEFINE_VARIABLE_WITH_SYMBOL(Grammar_categories_getting_choose_existing_class_feature, Qgrammar_categories_getting_choose_existing_class_feature);

/* WRITE-LIST-OF-CLASSES-FROM-SLOT */
Object write_list_of_classes_from_slot(class_list,gensymed_symbol)
    Object class_list, gensymed_symbol;
{
    x_note_fn_call(200,56);
    return write_symbol_list(4,class_list,Qcm,Nil,Qnone);
}

/* WRITE-LIST-OF-ITEM-CLASSES-FROM-SLOT */
Object write_list_of_item_classes_from_slot(class_list,gensymed_symbol)
    Object class_list, gensymed_symbol;
{
    x_note_fn_call(200,57);
    return write_symbol_list(4,class_list,Qcm,Nil,Qnone);
}

/* WRITE-LIST-OF-OBJECT-CLASSES-FROM-SLOT */
Object write_list_of_object_classes_from_slot(class_list,gensymed_symbol)
    Object class_list, gensymed_symbol;
{
    x_note_fn_call(200,58);
    return write_list_of_classes_from_slot(class_list,Nil);
}

/* WRITE-LIST-OF-CONNECTION-CLASSES-FROM-SLOT */
Object write_list_of_connection_classes_from_slot(class_list,gensymed_symbol)
    Object class_list, gensymed_symbol;
{
    x_note_fn_call(200,59);
    return write_list_of_classes_from_slot(class_list,Nil);
}

/* WRITE-LIST-OF-MESSAGE-CLASSES-FROM-SLOT */
Object write_list_of_message_classes_from_slot(class_list,gensymed_symbol)
    Object class_list, gensymed_symbol;
{
    x_note_fn_call(200,60);
    return write_list_of_classes_from_slot(class_list,Nil);
}

static Object Qfoundation_class;   /* foundation-class */

static Object Qthis_unnamed_class;  /* this-unnamed-class */

static Object string_constant_37;  /* "none" */

/* WRITE-CLASS-INHERITANCE-PATH-OF-DEFINITION-FROM-SLOT */
Object write_class_inheritance_path_of_definition_from_slot(class_list,
	    gensymed_symbol)
    Object class_list, gensymed_symbol;
{
    Object temp, first_superior_foundation_class, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp_1, entry_hash, tail, head;
    Object new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, item_class_qm;
    Object list_to_write, class_1, ab_loop_list_, class_description;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(200,61);
    if (class_list) {
	temp = get_class_feature_if_any(SECOND(class_list),Qfoundation_class);
	first_superior_foundation_class = SECOND(temp);
	skip_list = CDR(Symbol_properties_table);
	key_value = first_superior_foundation_class;
	key_hash_value = SXHASH_SYMBOL_1(first_superior_foundation_class) 
		& IFIX(Most_positive_fixnum);
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = first_superior_foundation_class;
	    temp_1 = Symbol_properties_table;
	    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_7;
	  end_loop_8:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_10;
	  end_loop_11:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	item_class_qm = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)16L) : Qnil;
	list_to_write = CAR(class_list) ? frame_cons_1(CAR(class_list),
		Nil) : frame_cons_1(Qthis_unnamed_class,Nil);
	class_1 = Nil;
	ab_loop_list_ = CDR(class_list);
      next_loop_12:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_12;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (item_class_qm)
	    temp_2 = EQ(class_1,Qitem);
	else {
	    class_description = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Class_description_gkbprop);
	    temp_2 =  !TRUEP(assq_function(Qfoundation_class,
		    ISVREF(class_description,(SI_Long)12L)));
	}
	if (temp_2)
	    goto end_loop_12;
	list_to_write = nconc2(list_to_write,frame_cons_1(class_1,Nil));
	goto next_loop_12;
      end_loop_12:;
	if (item_class_qm)
	    list_to_write = nconc2(list_to_write,frame_cons_1(Qitem,Nil));
	write_list_of_classes_from_slot(list_to_write,Nil);
	return reclaim_frame_list_1(list_to_write);
    }
    else
	return twrite(string_constant_37);
}

static Object string_constant_38;  /* ",~%" */

/* WRITE-LIST-OF-SLOTS-FROM-SLOT */
Object write_list_of_slots_from_slot(slot_list,gensymed_symbol)
    Object slot_list, gensymed_symbol;
{
    Object write_symbols_parsably_qm, first_slot_name_qm, slot_name;
    Object ab_loop_list_;
    Declare_special(1);
    Object result;

    x_note_fn_call(200,62);
    if (slot_list) {
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  first_slot_name_qm = T;
	  slot_name = Nil;
	  ab_loop_list_ = slot_list;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  slot_name = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  if (first_slot_name_qm)
	      first_slot_name_qm = Nil;
	  else
	      tformat(1,string_constant_38);
	  twrite_symbol(1,slot_name);
	  goto next_loop;
	end_loop:
	  result = VALUES_1(Qnil);
	POP_SPECIAL();
	return result;
    }
    else
	return twrite(string_constant_37);
}

/* PUT-CAPABILITIES-AND-RESTRICTIONS */
Object put_capabilities_and_restrictions(definition,new_value,gensymed_symbol)
    Object definition, new_value, gensymed_symbol;
{
    x_note_fn_call(200,63);
    return process_pre_4_dot_0_capabilities_of_class(definition,
	    ISVREF(definition,(SI_Long)20L),new_value,T);
}

static Object list_constant_14;    /* # */

static Object Qactivatable_subworkspace;  /* activatable-subworkspace */

static Object Qexternal_simulation;  /* external-simulation */

static Object Qmanual_connections;  /* manual-connections */

static Object Qsubworkspace_connection_posts;  /* subworkspace-connection-posts */

static Object Qactivatible_subworkspace;  /* activatible-subworkspace */

static Object Qno_manual_connections;  /* no-manual-connections */

/* WRITE-PREVIOUS-CAPABILITIES-FROM-SLOT */
Object write_previous_capabilities_from_slot(null_value,definition)
    Object null_value, definition;
{
    Object direct_superiors_qm, superior, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, capabilities_qm;
    Object instance_configuration_qm, clause;
    Object instance_configuration_property_declarations_qm, declaration;
    Object activatable_subworkspace_declaration_qm;
    Object external_simulation_declaration_qm;
    Object manual_connections_declaration_qm;
    Object subworkspace_connection_posts_declaration_qm;

    x_note_fn_call(200,64);
    direct_superiors_qm = ISVREF(definition,(SI_Long)21L);
    superior = Nil;
    ab_loop_list_ = direct_superiors_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    superior = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (memq_function(superior,list_constant_14)) {
	ab_loopvar__2 = frame_cons_1(superior,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    capabilities_qm = ab_loopvar_;
    goto end_1;
    capabilities_qm = Qnil;
  end_1:;
    instance_configuration_qm = ISVREF(definition,(SI_Long)23L);
    clause = Nil;
    ab_loop_list_ = instance_configuration_qm;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    clause = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(CAR(clause),Qdeclaration)) {
	ab_loopvar__2 = frame_cons_1(clause,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop_1;
  end_loop_1:
    instance_configuration_property_declarations_qm = ab_loopvar_;
    goto end_2;
    instance_configuration_property_declarations_qm = Qnil;
  end_2:;
    if (instance_configuration_property_declarations_qm) {
	declaration = Nil;
	ab_loop_list_ = instance_configuration_property_declarations_qm;
	activatable_subworkspace_declaration_qm = Nil;
	external_simulation_declaration_qm = Nil;
	manual_connections_declaration_qm = Nil;
	subworkspace_connection_posts_declaration_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	declaration = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	activatable_subworkspace_declaration_qm = 
		memq_function(Qactivatable_subworkspace,declaration);
	external_simulation_declaration_qm = 
		memq_function(Qexternal_simulation,declaration);
	manual_connections_declaration_qm = 
		memq_function(Qmanual_connections,declaration);
	subworkspace_connection_posts_declaration_qm = 
		memq_function(Qsubworkspace_connection_posts,declaration);
	if (activatable_subworkspace_declaration_qm && 
		SECOND(activatable_subworkspace_declaration_qm) &&  
		!TRUEP(memq_function(Qactivatable_subworkspace,
		capabilities_qm)))
	    capabilities_qm = nconc2(capabilities_qm,
		    frame_cons_1(Qactivatible_subworkspace,Nil));
	if (external_simulation_declaration_qm && 
		SECOND(external_simulation_declaration_qm) &&  
		!TRUEP(memq_function(Qexternal_simulation,capabilities_qm)))
	    capabilities_qm = nconc2(capabilities_qm,
		    frame_cons_1(Qexternal_simulation,Nil));
	if (manual_connections_declaration_qm &&  
		!TRUEP(SECOND(manual_connections_declaration_qm)) &&  
		!TRUEP(memq_function(Qno_manual_connections,capabilities_qm)))
	    capabilities_qm = nconc2(capabilities_qm,
		    frame_cons_1(Qno_manual_connections,Nil));
	if (subworkspace_connection_posts_declaration_qm && 
		SECOND(subworkspace_connection_posts_declaration_qm) &&  
		!TRUEP(memq_function(Qsubworkspace_connection_posts,
		capabilities_qm)))
	    capabilities_qm = nconc2(capabilities_qm,
		    frame_cons_1(Qsubworkspace_connection_posts,Nil));
	goto next_loop_2;
      end_loop_2:;
    }
    return write_symbol_list(4,capabilities_qm,Qcm,Nil,Qnone);
}

/* COMPILE-PREVIOUS-CAPABILITIES-FOR-SLOT */
Object compile_previous_capabilities_for_slot varargs_1(int, n)
{
    Object translation, definition, gensymed_symbol;
    Object declared_capabilities;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,65);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(translation,Qnone))
	declared_capabilities = Nil;
    else if (SYMBOLP(translation))
	declared_capabilities = phrase_cons(translation,Nil);
    else
	declared_capabilities = CDR(translation);
    if (declared_capabilities)
	return phrase_cons(declared_capabilities,Nil);
    else
	return VALUES_1(Nil);
}

/* COMPILE-OLD-DEFAULT-SETTINGS-FOR-SLOT */
Object compile_old_default_settings_for_slot varargs_1(int, n)
{
    Object translation, definition, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,66);
    INIT_ARGS_nonrelocating();
    translation = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_default_overrides_for_object_definitions_for_slot(3,
	    translation,definition,Nil);
}

/* PUT-DEFAULT-SETTINGS */
Object put_default_settings(definition,new_value,gensymed_symbol)
    Object definition, new_value, gensymed_symbol;
{
    x_note_fn_call(200,67);
    return process_pre_4_dot_0_attribute_descriptions_and_default_overrides(definition,
	    ISVREF(definition,(SI_Long)20L),Nil,ISVREF(definition,
	    (SI_Long)21L),new_value,Nil,T);
}

static Object Quser_defined;       /* user-defined */

static Object string_constant_39;  /* ";~%" */

/* WRITE-OLD-DEFAULT-SETTINGS-FROM-SLOT */
Object write_old_default_settings_from_slot(null_value,definition)
    Object null_value, definition;
{
    Object override, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object value, rest_qm;

    x_note_fn_call(200,68);
    override = Nil;
    ab_loop_list_ = ISVREF(definition,(SI_Long)27L);
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(THIRD(override),Quser_defined)) {
	ab_loopvar__2 = 
		frame_cons_1(copy_tree_using_frame_conses_1(override),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    goto next_loop;
  end_loop:
    value = ab_loopvar_;
    goto end_1;
    value = Qnil;
  end_1:;
    if ( !TRUEP(value))
	return twrite_beginning_of_wide_string(array_constant_8,
		FIX((SI_Long)4L));
    else {
	override = Nil;
	rest_qm = Nil;
	ab_loop_list_ = value;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	override = CAR(ab_loop_list_);
	rest_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_default_override(override,definition);
	if (rest_qm)
	    tformat(1,string_constant_39);
	goto next_loop_1;
      end_loop_1:;
	if (CDR(value))
	    Leave_text_representation_as_a_single_line_qm = Nil;
	return reclaim_frame_tree_1(value);
    }
}

static Object Qdirect_superiors_of_defined_class;  /* direct-superiors-of-defined-class */

/* PUT-SUPERIOR-CLASS */
Object put_superior_class(definition,parse_value,gensymed_symbol)
    Object definition, parse_value, gensymed_symbol;
{
    x_note_fn_call(200,69);
    return change_slot_value(3,definition,
	    Qdirect_superiors_of_defined_class,parse_value);
}

/* COMPILE-OLD-SUPERIOR-CLASS-FOR-SLOT */
Object compile_old_superior_class_for_slot varargs_1(int, n)
{
    Object parse_result, frame, gensymed_symbol;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,70);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_list_of_classes_for_slot(3,phrase_list_2(Qcm,
	    parse_result),frame,Qdirect_superiors_of_defined_class);
}

static Object list_constant_15;    /* # */

/* WRITE-OLD-SUPERIOR-CLASS-FROM-SLOT */
Object write_old_superior_class_from_slot(null_value,definition)
    Object null_value, definition;
{
    Object direct_superiors_qm, superior_class, symbol_to_write, superior;
    Object ab_loop_list_;

    x_note_fn_call(200,71);
    direct_superiors_qm = ISVREF(definition,(SI_Long)21L);
    if ( !TRUEP(direct_superiors_qm))
	return twrite_beginning_of_wide_string(array_constant_8,
		FIX((SI_Long)4L));
    else {
	if ( !TRUEP(CDR(direct_superiors_qm))) {
	    superior_class = CAR(direct_superiors_qm);
	    symbol_to_write = memq_function(superior_class,
		    list_constant_15) ? Qobject : superior_class;
	}
	else {
	    superior = Nil;
	    ab_loop_list_ = direct_superiors_qm;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    superior = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(memq_function(superior,list_constant_14))) {
		symbol_to_write = superior;
		goto end_1;
	    }
	    goto next_loop;
	  end_loop:
	    symbol_to_write = Qnil;
	  end_1:;
	}
	return twrite_symbol(1,symbol_to_write);
    }
}

/* PUT-ATTRIBUTES-SPECIFIC-TO-CLASS */
Object put_attributes_specific_to_class(definition,new_value,gensymed_symbol)
    Object definition, new_value, gensymed_symbol;
{
    x_note_fn_call(200,72);
    return process_pre_4_dot_0_attribute_descriptions_and_default_overrides(definition,
	    ISVREF(definition,(SI_Long)20L),new_value,ISVREF(definition,
	    (SI_Long)21L),Nil,T,Nil);
}

static Object Kfuncall;            /* :funcall */

/* WRITE-OLD-ATTRIBUTE-DESCRIPTIONS-FROM-SLOT */
Object write_old_attribute_descriptions_from_slot(null_value,definition)
    Object null_value, definition;
{
    Object class_specific_attributes, default_overrides, override;
    Object ab_loop_list_, overrides_for_user_defined_attributes_qm;
    Object old_descriptions_to_write, attribute_description, attribute_name;
    Object cddr_of_attribute_description, name_denotation, second_component;
    Object temp, funcalled_attribute_qm, attribute_value, value;
    Object attribute_type, sublist;

    x_note_fn_call(200,73);
    class_specific_attributes = ISVREF(definition,(SI_Long)22L);
    default_overrides = ISVREF(definition,(SI_Long)27L);
    override = Nil;
    ab_loop_list_ = default_overrides;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    override = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(THIRD(override),Quser_defined)) {
	overrides_for_user_defined_attributes_qm = T;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    overrides_for_user_defined_attributes_qm = Qnil;
  end_1:;
    if (class_specific_attributes || 
		overrides_for_user_defined_attributes_qm) {
	old_descriptions_to_write = Nil;
	attribute_description = Nil;
	ab_loop_list_ = class_specific_attributes;
	attribute_name = Nil;
	cddr_of_attribute_description = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	attribute_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	attribute_name = CAR(attribute_description);
	cddr_of_attribute_description = CDDR(attribute_description);
	old_descriptions_to_write = nconc2(old_descriptions_to_write,
		frame_cons_1(frame_cons_1(attribute_name,
		copy_tree_using_frame_conses_1(cddr_of_attribute_description)),
		Nil));
	goto next_loop_1;
      end_loop_1:;
	override = Nil;
	ab_loop_list_ = default_overrides;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	override = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(THIRD(override),Quser_defined)) {
	    name_denotation = FIRST(override);
	    attribute_name = CONSP(name_denotation) ? 
		    M_CAR(M_CDR(M_CDR(name_denotation))) : name_denotation;
	    second_component = SECOND(override);
	    temp = CAR(second_component);
	    if (CONSP(temp)) {
		temp = CAR(second_component);
		funcalled_attribute_qm = EQ(FIRST(temp),Kfuncall) ? T : Nil;
	    }
	    else
		funcalled_attribute_qm = Nil;
	    if (funcalled_attribute_qm)
		attribute_value = 
			copy_list_using_frame_conses_1(CAR(second_component));
	    else {
		value = FIRST(second_component);
		attribute_value = CONSP(value) ? 
			copy_list_using_frame_conses_1(value) : value;
	    }
	    attribute_type = funcalled_attribute_qm ? Nil : 
		    SECOND(second_component);
	    old_descriptions_to_write = nconc2(old_descriptions_to_write,
		    frame_cons_1(frame_list_3(attribute_name,
		    attribute_value,attribute_type),Nil));
	}
	goto next_loop_2;
      end_loop_2:;
	sublist = old_descriptions_to_write;
      next_loop_3:
	if ( !TRUEP(sublist))
	    goto end_loop_3;
	write_old_attribute_description(CAR(sublist),definition);
	if (CDR(sublist))
	    tformat(1,string_constant_39);
	sublist = M_CDR(sublist);
	goto next_loop_3;
      end_loop_3:;
	return reclaim_frame_tree_1(old_descriptions_to_write);
    }
    else
	return twrite_beginning_of_wide_string(array_constant_8,
		FIX((SI_Long)4L));
}

static Object Qindexed_attributes_for_definition;  /* indexed-attributes-for-definition */

static Object string_constant_40;  /* " is " */

static Object string_constant_41;  /* " is a symbol" */

static Object string_constant_42;  /* "~( has values ~a or ~a~)" */

static Object string_constant_43;  /* " (default is ~A)" */

static Object string_constant_44;  /* " has values " */

static Object string_constant_45;  /* "or" */

static Object Qtext;               /* text */

static Object string_constant_46;  /* " and" */

static Object Qinstantiate_variable;  /* instantiate-variable */

static Object string_constant_47;  /* " is given by " */

static Object string_constant_48;  /* " is an instance of " */

static Object string_constant_49;  /* ", with an index" */

/* WRITE-OLD-ATTRIBUTE-DESCRIPTION */
Object write_old_attribute_description(description,definition)
    Object description, definition;
{
    Object name, value, funcalled_value_qm, type, indexed_attributes;
    Object write_symbols_parsably_qm, write_strings_parsably_qm;
    Declare_special(1);

    x_note_fn_call(200,74);
    name = FIRST(description);
    value = SECOND(description);
    funcalled_value_qm = CONSP(value) ? (EQ(CAR(value),Kfuncall) ? T : 
	    Nil) : Qnil;
    type = THIRD(description);
    indexed_attributes = get_lookup_slot_value_given_default(definition,
	    Qindexed_attributes_for_definition,Nil);
    twrite_symbol(1,name);
    if (EQ(type,Qsymbol)) {
	write_symbols_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_symbols_parsably_qm,Qwrite_symbols_parsably_qm,write_symbols_parsably_qm,
		0);
	  if (IFIX(length(description)) == (SI_Long)3L) {
	      if (value) {
		  twrite(string_constant_40);
		  twrite_symbol(1,value);
	      }
	      else
		  twrite(string_constant_41);
	  }
	  else if (IFIX(length(description)) == (SI_Long)5L) {
	      tformat(3,string_constant_42,FOURTH(description),
		      FIFTH(description));
	      if (value && ATOM(value))
		  tformat(2,string_constant_43,value);
	  }
	  else {
	      twrite(string_constant_44);
	      write_list_in_chicago_style(2,CDDDR(description),
		      string_constant_45);
	      if (value && ATOM(value))
		  tformat(2,string_constant_43,value);
	  }
	POP_SPECIAL();
    }
    else if (EQ(type,Qtext)) {
	twrite(string_constant_40);
	write_strings_parsably_qm = T;
	PUSH_SPECIAL_WITH_SYMBOL(Write_strings_parsably_qm,Qwrite_strings_parsably_qm,write_strings_parsably_qm,
		0);
	  twrite_general_string(value);
	POP_SPECIAL();
    }
    else if (type) {
	if ( !TRUEP(funcalled_value_qm)) {
	    twrite(string_constant_40);
	    print_constant(2,value,type);
	}
    }
    if (EQ(type,Qsymbol) && CONSP(value))
	twrite(string_constant_46);
    if (CONSP(value) && EQ(CAR(value),Kfuncall)) {
	twrite(EQ(SECOND(value),Qinstantiate_variable) ? 
		string_constant_47 : string_constant_48);
	write_symbol_with_a_or_an(1,THIRD(value));
    }
    if (memq_function(name,indexed_attributes))
	return twrite(string_constant_49);
    else
	return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

static Object Qtrue;               /* true */

static Object Qindexed;            /* indexed */

/* FIX-OLD-ATTRIBUTE-DESCRIPTION */
Object fix_old_attribute_description(phrase,indexed_qm)
    Object phrase, indexed_qm;
{
    Object temp, temp_1, phrase_number, temp_3, fixed_description;
    char temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(200,75);
    temp = CAR(phrase);
    if (phrase_number_p(CDR(phrase)))
	temp_1 = phrase_list_2(CDR(phrase),Qnumber);
    else if (memq_function(CDR(phrase),list_constant_16)) {
	temp_1 = CDR(phrase);
	temp_1 = phrase_list_2(EQ(temp_1,Qtrue) ? FIX((SI_Long)1000L) : 
		FIX((SI_Long)-1000L),Qtruth_value);
    }
    else {
	temp_1 = CDR(phrase);
	if (SYMBOLP(temp_1))
	    temp_1 = phrase_list_2(CDR(phrase),Qsymbol);
	else if (text_string_p(CDR(phrase)))
	    temp_1 = phrase_list_2(CDR(phrase),Qtext);
	else {
	    temp_1 = CDR(phrase);
	    if (phrase_number_p(CAR(temp_1))) {
		temp_1 = CDR(phrase);
		temp_2 = EQ(CDR(temp_1),Qtruth_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2) {
		if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		    temp_1 = CDR(phrase);
		    phrase_number = CAR(temp_1);
		    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) 
			    == (SI_Long)1L)
			temp_1 = 
				DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
				(SI_Long)0L));
		    else if (INLINE_LONG_VECTOR_P(phrase_number) != 
			    (SI_Long)0L && 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) 
			    == (SI_Long)1L)
			temp_1 = aref1(phrase_number,FIX((SI_Long)0L));
		    else
			temp_1 = phrase_number;
		    temp_1 = l_round(ltimes(FIX((SI_Long)1000L),temp_1),_);
		}
		POP_LOCAL_ALLOCATION(0,0);
		temp_1 = phrase_list_2(temp_1,Qtruth_value);
	    }
	    else {
		temp_1 = CDR(phrase);
		if (phrase_number_p(CAR(temp_1))) {
		    temp_1 = CDR(phrase);
		    temp_1 = CDR(temp_1);
		    temp_2 = SYMBOLP(temp_1);
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_3 = CDR(phrase);
		    temp_1 = CDR(phrase);
		    temp_1 = phrase_list_2(CAR(temp_3),CDR(temp_1));
		}
		else
		    temp_1 = Qnil;
	    }
	}
    }
    fixed_description = phrase_cons(temp,temp_1);
    if (indexed_qm)
	return VALUES_1(nconc2(fixed_description,
		phrase_cons(phrase_cons(Qindexed,Nil),Nil)));
    else
	return VALUES_1(fixed_description);
}

static Object Qsc;                 /* \; */

static Object Qcar_eq;             /* car-eq */

static Object array_constant_12;   /* # */

static Object list_constant_17;    /* # */

static Object Qold_value_of_indexed_attributes;  /* old-value-of-indexed-attributes */

/* COMPILE-OLD-ATTRIBUTE-DESCRIPTIONS-FOR-SLOT */
Object compile_old_attribute_descriptions_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Object transformed_value, temp, listed_attribute_description, temp_1;
    Object car_new_value, attribute_description, ab_loop_list_, attribute_name;
    Object indexed_qm, rest_1, indexed_attributes, ab_loopvar_, ab_loopvar__1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,76);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	transformed_value = Nil;
    else if (SYMBOLP(parse_result))
	transformed_value = phrase_cons(phrase_list_3(parse_result,Nil,
		Nil),Nil);
    else if (EQ(CAR(parse_result),Qsc)) {
	temp = CDR(parse_result);
	listed_attribute_description = CDR(parse_result);
      next_loop:
	if ( !TRUEP(listed_attribute_description))
	    goto end_loop;
	temp_1 = CAR(listed_attribute_description);
	if (SYMBOLP(temp_1)) {
	    car_new_value = 
		    phrase_list_3(CAR(listed_attribute_description),Nil,Nil);
	    M_CAR(listed_attribute_description) = car_new_value;
	}
	listed_attribute_description = M_CDR(listed_attribute_description);
	goto next_loop;
      end_loop:;
	transformed_value = temp;
    }
    else
	transformed_value = phrase_cons(parse_result,Nil);
    listed_attribute_description = transformed_value;
    attribute_description = Nil;
  next_loop_1:
    if ( !TRUEP(listed_attribute_description))
	goto end_loop_1;
    attribute_description = CAR(listed_attribute_description);
    if (member(4,CAR(attribute_description),
	    CDR(listed_attribute_description),Ktest,Qcar_eq)) {
	temp_1 = Bad_phrase;
	temp = copy_constant_wide_string_given_length(array_constant_12,
		FIX((SI_Long)40L));
	return VALUES_2(temp_1,temp);
    }
    listed_attribute_description = M_CDR(listed_attribute_description);
    goto next_loop_1;
  end_loop_1:;
    attribute_description = Nil;
    ab_loop_list_ = transformed_value;
    attribute_name = Nil;
    indexed_qm = Nil;
    rest_1 = Nil;
    indexed_attributes = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    attribute_description = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    attribute_name = CAR(attribute_description);
    temp = CDR(attribute_description);
    temp = CDR(temp);
    temp = CDR(temp);
    indexed_qm = CAR(temp);
    temp = CDR(attribute_description);
    temp = CDR(temp);
    temp = CDR(temp);
    rest_1 = CDR(temp);
    if (EQUAL(indexed_qm,list_constant_17)) {
	ab_loopvar__1 = slot_value_cons_1(attribute_name,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    indexed_attributes = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	M_CDDDR(attribute_description) = rest_1;
    }
    goto next_loop_2;
  end_loop_2:
    set_non_savable_lookup_slot_value(definition,
	    Qold_value_of_indexed_attributes,
	    get_lookup_slot_value_given_default(definition,
	    Qindexed_attributes_for_definition,Nil));
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(definition,Qindexed_attributes_for_definition);
    set_lookup_slot_value_1(definition,Qindexed_attributes_for_definition,
	    indexed_attributes);
    return VALUES_1(transformed_value);
}

/* COMPILE-LIST-OF-ITEM-CLASSES-FOR-SLOT */
Object compile_list_of_item_classes_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,77);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_list_of_classes_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-LIST-OF-OBJECT-CLASSES-FOR-SLOT */
Object compile_list_of_object_classes_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,78);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_list_of_classes_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-LIST-OF-CONNECTION-CLASSES-FOR-SLOT */
Object compile_list_of_connection_classes_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,79);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_list_of_classes_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-LIST-OF-MESSAGE-CLASSES-FOR-SLOT */
Object compile_list_of_message_classes_for_slot varargs_1(int, n)
{
    Object parse_result, frame, slot_name;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,80);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return compile_list_of_classes_for_slot(3,parse_result,frame,slot_name);
}

/* COMPILE-LIST-OF-CLASSES-FOR-SLOT */
Object compile_list_of_classes_for_slot varargs_1(int, n)
{
    Object parse_result, definition, slot_name;
    Object direct_superior_classes_qm, temp;
    Object possible_class_inheritance_path_qm, error_string_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,81);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    direct_superior_classes_qm = CONSP(parse_result) ? CDR(parse_result) : Nil;
    temp = ISVREF(definition,(SI_Long)21L);
    if (EQUAL(direct_superior_classes_qm,temp))
	return VALUES_1(direct_superior_classes_qm);
    else {
	possible_class_inheritance_path_qm = 
		direct_superiors_are_defined_p(direct_superior_classes_qm) 
		? 
		make_class_inheritance_path_for_user_defined_class(ISVREF(definition,
		(SI_Long)20L),direct_superior_classes_qm) : Nil;
	error_string_qm = 
		do_valid_superior_tests(direct_superior_classes_qm,
		definition,possible_class_inheritance_path_qm);
	if (error_string_qm)
	    return VALUES_2(Bad_phrase,error_string_qm);
	else
	    return VALUES_1(direct_superior_classes_qm);
    }
}

/* CUT-OUT-FOURTH-ELEMENT */
Object cut_out_fourth_element(list_1)
    Object list_1;
{
    Object temp;

    x_note_fn_call(200,82);
    temp = phrase_list_3(FIRST(list_1),SECOND(list_1),THIRD(list_1));
    return VALUES_1(nconc2(temp,
	    copy_list_using_phrase_conses(CDDDDR(list_1))));
}

/* CUT-OUT-FIFTH-ELEMENT */
Object cut_out_fifth_element(list_1)
    Object list_1;
{
    Object temp, temp_1;

    x_note_fn_call(200,83);
    temp = phrase_list_4(FIRST(list_1),SECOND(list_1),THIRD(list_1),
	    FOURTH(list_1));
    temp_1 = CDDR(list_1);
    return VALUES_1(nconc2(temp,copy_list_using_phrase_conses(CDDDR(temp_1))));
}

/* CUT-OUT-SIXTH-ELEMENT */
Object cut_out_sixth_element(list_1)
    Object list_1;
{
    Object gensymed_symbol, gensymed_symbol_1, car_new_value, temp;

    x_note_fn_call(200,84);
    gensymed_symbol = make_phrase_list(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = FIRST(list_1);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = SECOND(list_1);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = THIRD(list_1);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = FOURTH(list_1);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = FIFTH(list_1);
    M_CAR(gensymed_symbol_1) = car_new_value;
    temp = CDDDR(list_1);
    return VALUES_1(nconc2(gensymed_symbol,
	    copy_list_using_phrase_conses(CDDDR(temp))));
}

/* MEMQ-2-CDDDR */
Object memq_2_cdddr(list_1)
    Object list_1;
{
    x_note_fn_call(200,85);
    if (memq_function(SECOND(list_1),CDDDR(list_1)))
	return VALUES_1(list_1);
    else
	return VALUES_1(Bad_phrase);
}

/* MEMQ-2-CDDDDR */
Object memq_2_cddddr(list_1)
    Object list_1;
{
    x_note_fn_call(200,86);
    if (memq_function(SECOND(list_1),CDDDDR(list_1)))
	return VALUES_1(list_1);
    else
	return VALUES_1(Bad_phrase);
}

/* MEMQ-3-CDDDDR */
Object memq_3_cddddr(list_1)
    Object list_1;
{
    x_note_fn_call(200,87);
    if (memq_function(THIRD(list_1),CDDDDR(list_1)))
	return VALUES_1(list_1);
    else
	return VALUES_1(Bad_phrase);
}

/* MEMQ-3-CDR-CDDDDR */
Object memq_3_cdr_cddddr(list_1)
    Object list_1;
{
    Object temp;

    x_note_fn_call(200,88);
    temp = CDDDDR(list_1);
    if (memq_function(THIRD(list_1),CDR(temp)))
	return VALUES_1(list_1);
    else
	return VALUES_1(Bad_phrase);
}

static Object Qnormalized_parse;   /* normalized-parse */

static Object Qab_class;           /* class */

static Object string_constant_50;  /* "The class given for attribute ~A (~(~a~)) is not an ~
				    *                   instantiable variable or parameter."
				    */

static Object string_constant_51;  /* "The class type-specification given for attribute ~A ~
				    *                   (~(~a~)) is not an instantiable variable or parameter."
				    */

static Object string_constant_52;  /* "The initial value for attribute ~A does not conform to ~
				    *                 the given type specification."
				    */

static Object string_constant_53;  /* "The initial value for attribute ~A is not a subclass ~
				    *                   of its declared type."
				    */

static Object string_constant_54;  /* "The class given for attribute ~A (~(~a~)) is not an ~
				    *                   instantiable object."
				    */

static Object string_constant_55;  /* "The class type-specification given for attribute ~A ~
				    *                   (~(~a~)) is not an instantiable object."
				    */

static Object string_constant_56;  /* "~A cannot be the name of a class because it specifies a ~
				    *                   type in G2."
				    */

/* COMPILE-ATTRIBUTE-DESCRIPTIONS-FOR-SLOT */
Object compile_attribute_descriptions_for_slot varargs_1(int, n)
{
    Object parse_result, definition, gensymed_symbol;
    Object transformed_value, temp, listed_attribute_description, temp_1;
    Object temp_2, attribute_description, bad_attribute_name_qm;
    Object not_a_variable_or_parameter_qm, type_not_a_variable_or_parameter_qm;
    Object not_an_instantiable_variable_or_parameter_class_qm;
    Object not_an_object_qm, type_not_an_object_qm;
    Object not_an_instantiable_object_class_qm;
    Object initial_value_does_not_conform_to_type_qm;
    Object non_type_conforming_class_value_qm;
    Object class_type_designation_specifies_a_g2_type, name;
    Object attribute_definition_type, initial_value, initial_type;
    Object ab_loop_list_, type_specification, ab_loop_desetq_, skip_list;
    Object key_value, marked, pred, curr, succ, reference, entry_hash, tail;
    Object head, new_cons, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value;
    Object initial_value_is_defined_class_qm, class_type_qm;
    Object sub_class_bit_vector, attribute_name, indexed_qm, rest_1;
    Object indexed_attributes, ab_loopvar_, ab_loopvar__1;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    char temp_3;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(200,89);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    definition = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (EQ(parse_result,Qnone))
	transformed_value = Nil;
    else if (SYMBOLP(parse_result))
	transformed_value = phrase_cons(phrase_list_3(parse_result,Nil,
		Nil),Nil);
    else if (EQ(CAR(parse_result),Qnormalized_parse))
	transformed_value = CDR(parse_result);
    else if (EQ(CAR(parse_result),Qsc)) {
	temp = CDR(parse_result);
	listed_attribute_description = CDR(parse_result);
      next_loop:
	if ( !TRUEP(listed_attribute_description))
	    goto end_loop;
	temp_1 = CAR(listed_attribute_description);
	if (SYMBOLP(temp_1)) {
	    temp_2 = phrase_list_3(CAR(listed_attribute_description),Nil,Nil);
	    M_CAR(listed_attribute_description) = temp_2;
	}
	listed_attribute_description = M_CDR(listed_attribute_description);
	goto next_loop;
      end_loop:;
	transformed_value = temp;
    }
    else
	transformed_value = phrase_cons(parse_result,Nil);
    listed_attribute_description = transformed_value;
    attribute_description = Nil;
  next_loop_1:
    if ( !TRUEP(listed_attribute_description))
	goto end_loop_1;
    attribute_description = CAR(listed_attribute_description);
    if (member(4,CAR(attribute_description),
	    CDR(listed_attribute_description),Ktest,Qcar_eq)) {
	temp_1 = Bad_phrase;
	temp = copy_constant_wide_string_given_length(array_constant_12,
		FIX((SI_Long)40L));
	return VALUES_2(temp_1,temp);
    }
    listed_attribute_description = M_CDR(listed_attribute_description);
    goto next_loop_1;
  end_loop_1:;
    bad_attribute_name_qm = Nil;
    not_a_variable_or_parameter_qm = Nil;
    type_not_a_variable_or_parameter_qm = Nil;
    not_an_instantiable_variable_or_parameter_class_qm = Nil;
    not_an_object_qm = Nil;
    type_not_an_object_qm = Nil;
    not_an_instantiable_object_class_qm = Nil;
    initial_value_does_not_conform_to_type_qm = Nil;
    non_type_conforming_class_value_qm = Nil;
    class_type_designation_specifies_a_g2_type = Nil;
    name = Nil;
    attribute_definition_type = Nil;
    initial_value = Nil;
    initial_type = Nil;
    ab_loop_list_ = transformed_value;
    type_specification = Nil;
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    attribute_definition_type = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    initial_value = CAR(temp);
    temp = CDR(ab_loop_desetq_);
    temp = CDR(temp);
    temp = CDR(temp);
    initial_type = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    type_specification = 
	    attribute_definition_type_specification(attribute_definition_type);
    if ( 
	    !TRUEP(parsed_attribute_initial_value_matches_type_p(initial_value,
	    type_specification))) {
	initial_value_does_not_conform_to_type_qm = name;
	goto end_loop_2;
    }
    else if (reserved_system_slot_name_p(definition,name)) {
	bad_attribute_name_qm = name;
	goto end_loop_2;
    }
    else if (CONSP(initial_value) && EQ(M_CAR(initial_value),Kfuncall)) {
	if (SYMBOLP(initial_type)) {
	    skip_list = CDR(Symbol_properties_table);
	    key_value = initial_type;
	    key_hash_value = SXHASH_SYMBOL_1(initial_type) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_3:
	    if (level < ab_loop_bind_)
		goto end_loop_3;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_4:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_5:
	    if ( !TRUEP(marked))
		goto end_loop_4;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_5;
	  end_loop_4:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_1;
	    goto next_loop_4;
	  end_loop_5:
	  end_1:
	    level = level - (SI_Long)1L;
	    goto next_loop_3;
	  end_loop_3:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = initial_type;
		temp_1 = Symbol_properties_table;
		temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			IFIX(Most_positive_fixnum));
		tail = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			Nil);
		head = 
			make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			tail);
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_1 = new_cons;
		}
		else
		    gensymed_symbol_1 = Nil;
		if ( !TRUEP(gensymed_symbol_1))
		    gensymed_symbol_1 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		new_cons = ISVREF(Available_lookup_conses_vector,
			IFIX(Current_thread_index));
		if (new_cons) {
		    temp_2 = Available_lookup_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    svref_new_value = M_CDR(new_cons);
		    SVREF(temp_2,svref_arg_2) = svref_new_value;
		    if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index)))) {
			temp_2 = Available_lookup_conses_tail_vector;
			svref_arg_2 = Current_thread_index;
			SVREF(temp_2,svref_arg_2) = Nil;
		    }
		    gensymed_symbol_2 = new_cons;
		}
		else
		    gensymed_symbol_2 = Nil;
		if ( !TRUEP(gensymed_symbol_2))
		    gensymed_symbol_2 = replenish_lookup_cons_pool();
		M_CAR(gensymed_symbol_2) = head;
		M_CDR(gensymed_symbol_2) = tail;
		inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		gensymed_symbol = set_skip_list_entry(temp_1,
			FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,temp,
			gensymed_symbol_1);
	    }
	    global_properties = gensymed_symbol;
	    skip_list = CDR(global_properties);
	    key_value = Current_kb_specific_property_list_property_name;
	    key_hash_value = 
		    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		    & IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_2;
	    goto next_loop_7;
	  end_loop_8:
	  end_2:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_properties);
	    else
		kb_properties = Nil;
	    if (kb_properties) {
		skip_list = CDR(kb_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_9:
		if (level < ab_loop_bind_)
		    goto end_loop_9;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_10:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_11:
		if ( !TRUEP(marked))
		    goto end_loop_10;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_11;
	      end_loop_10:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_3;
		goto next_loop_10;
	      end_loop_11:
	      end_3:
		level = level - (SI_Long)1L;
		goto next_loop_9;
	      end_loop_9:;
		kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_specific_value);
		else
		    kb_specific_value = No_specific_property_value;
	    }
	    else
		kb_specific_value = No_specific_property_value;
	    if ( !EQ(kb_specific_value,No_specific_property_value))
		resulting_value = kb_specific_value;
	    else {
		skip_list = CDR(global_properties);
		key_value = Class_description_gkbprop;
		key_hash_value = 
			SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_12:
		if (level < ab_loop_bind_)
		    goto end_loop_12;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_13:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_14:
		if ( !TRUEP(marked))
		    goto end_loop_13;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_14;
	      end_loop_13:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_4;
		goto next_loop_13;
	      end_loop_14:
	      end_4:
		level = level - (SI_Long)1L;
		goto next_loop_12;
	      end_loop_12:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    initial_value_is_defined_class_qm = resulting_value;
	}
	else
	    initial_value_is_defined_class_qm = Nil;
	class_type_qm = CONSP(type_specification) && 
		EQ(M_CAR(type_specification),Qab_class) ? 
		SECOND(type_specification) : Qnil;
	if (type_specification_for_user_or_datum_type(initial_type)) {
	    class_type_designation_specifies_a_g2_type = initial_type;
	    goto end_loop_2;
	}
	else if (EQ(SECOND(initial_value),Qinstantiate_variable)) {
	    if (SYMBOLP(class_type_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_type_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_type_qm) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_15:
		if (level < ab_loop_bind_)
		    goto end_loop_15;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_16:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_17:
		if ( !TRUEP(marked))
		    goto end_loop_16;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_17;
	      end_loop_16:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_5;
		goto next_loop_16;
	      end_loop_17:
	      end_5:
		level = level - (SI_Long)1L;
		goto next_loop_15;
	      end_loop_15:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_type_qm;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			    tail);
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_18:
		if (level < ab_loop_bind_)
		    goto end_loop_18;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_19:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_20:
		if ( !TRUEP(marked))
		    goto end_loop_19;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_20;
	      end_loop_19:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_6;
		goto next_loop_19;
	      end_loop_20:
	      end_6:
		level = level - (SI_Long)1L;
		goto next_loop_18;
	      end_loop_18:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_21:
		    if (level < ab_loop_bind_)
			goto end_loop_21;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_22:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_23:
		    if ( !TRUEP(marked))
			goto end_loop_22;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_23;
		  end_loop_22:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_7;
		    goto next_loop_22;
		  end_loop_23:
		  end_7:
		    level = level - (SI_Long)1L;
		    goto next_loop_21;
		  end_loop_21:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_24:
		    if (level < ab_loop_bind_)
			goto end_loop_24;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_25:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_26:
		    if ( !TRUEP(marked))
			goto end_loop_25;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_26;
		  end_loop_25:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_8;
		    goto next_loop_25;
		  end_loop_26:
		  end_8:
		    level = level - (SI_Long)1L;
		    goto next_loop_24;
		  end_loop_24:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_3 = TRUEP(resulting_value);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_type_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_type_qm) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_27:
		if (level < ab_loop_bind_)
		    goto end_loop_27;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_28:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_29:
		if ( !TRUEP(marked))
		    goto end_loop_28;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_29;
	      end_loop_28:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_9;
		goto next_loop_28;
	      end_loop_29:
	      end_9:
		level = level - (SI_Long)1L;
		goto next_loop_27;
	      end_loop_27:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_type_qm;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			    tail);
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_30:
		if (level < ab_loop_bind_)
		    goto end_loop_30;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_31:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_32:
		if ( !TRUEP(marked))
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_32;
	      end_loop_31:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_10;
		goto next_loop_31;
	      end_loop_32:
	      end_10:
		level = level - (SI_Long)1L;
		goto next_loop_30;
	      end_loop_30:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_33:
		    if (level < ab_loop_bind_)
			goto end_loop_33;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_34:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_35:
		    if ( !TRUEP(marked))
			goto end_loop_34;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_35;
		  end_loop_34:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_11;
		    goto next_loop_34;
		  end_loop_35:
		  end_11:
		    level = level - (SI_Long)1L;
		    goto next_loop_33;
		  end_loop_33:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_36:
		    if (level < ab_loop_bind_)
			goto end_loop_36;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_37:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_38:
		    if ( !TRUEP(marked))
			goto end_loop_37;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_38;
		  end_loop_37:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_12;
		    goto next_loop_37;
		  end_loop_38:
		  end_12:
		    level = level - (SI_Long)1L;
		    goto next_loop_36;
		  end_loop_36:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_3 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 =  !temp_3;
		if (temp_3);
		else
		    temp_3 = TRUEP(get_class_feature_if_any(class_type_qm,
			    Qnot_user_instantiable));
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		type_not_a_variable_or_parameter_qm = name;
		not_an_instantiable_variable_or_parameter_class_qm = 
			class_type_qm;
		goto end_loop_2;
	    }
	    else if (initial_value_is_defined_class_qm) {
		skip_list = CDR(Symbol_properties_table);
		key_value = initial_type;
		key_hash_value = SXHASH_SYMBOL_1(initial_type) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_39:
		if (level < ab_loop_bind_)
		    goto end_loop_39;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_40:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_41:
		if ( !TRUEP(marked))
		    goto end_loop_40;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_41;
	      end_loop_40:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_13;
		goto next_loop_40;
	      end_loop_41:
	      end_13:
		level = level - (SI_Long)1L;
		goto next_loop_39;
	      end_loop_39:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = initial_type;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			    tail);
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_42:
		if (level < ab_loop_bind_)
		    goto end_loop_42;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_43:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_44:
		if ( !TRUEP(marked))
		    goto end_loop_43;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_44;
	      end_loop_43:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_14;
		goto next_loop_43;
	      end_loop_44:
	      end_14:
		level = level - (SI_Long)1L;
		goto next_loop_42;
	      end_loop_42:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_45:
		    if (level < ab_loop_bind_)
			goto end_loop_45;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_46:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_47:
		    if ( !TRUEP(marked))
			goto end_loop_46;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_47;
		  end_loop_46:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_15;
		    goto next_loop_46;
		  end_loop_47:
		  end_15:
		    level = level - (SI_Long)1L;
		    goto next_loop_45;
		  end_loop_45:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_48:
		    if (level < ab_loop_bind_)
			goto end_loop_48;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_49:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_50:
		    if ( !TRUEP(marked))
			goto end_loop_49;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_50;
		  end_loop_49:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_16;
		    goto next_loop_49;
		  end_loop_50:
		  end_16:
		    level = level - (SI_Long)1L;
		    goto next_loop_48;
		  end_loop_48:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Variable_or_parameter_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_3 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 =  !temp_3;
		if (temp_3);
		else
		    temp_3 = TRUEP(get_class_feature_if_any(initial_type,
			    Qnot_user_instantiable));
		if (temp_3) {
		    not_a_variable_or_parameter_qm = name;
		    not_an_instantiable_variable_or_parameter_class_qm = 
			    initial_type;
		    goto end_loop_2;
		}
		else {
		    if (SYMBOLP(class_type_qm)) {
			skip_list = CDR(Symbol_properties_table);
			key_value = class_type_qm;
			key_hash_value = SXHASH_SYMBOL_1(class_type_qm) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_51:
			if (level < ab_loop_bind_)
			    goto end_loop_51;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_52:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_53:
			if ( !TRUEP(marked))
			    goto end_loop_52;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_53;
		      end_loop_52:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_17;
			goto next_loop_52;
		      end_loop_53:
		      end_17:
			level = level - (SI_Long)1L;
			goto next_loop_51;
		      end_loop_51:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = class_type_qm;
			    temp_1 = Symbol_properties_table;
			    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				    IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_2 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_2,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_2 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_2 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_2,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_2 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp_1,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
			key_hash_value = 
				SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_54:
			if (level < ab_loop_bind_)
			    goto end_loop_54;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_55:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_56:
			if ( !TRUEP(marked))
			    goto end_loop_55;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_56;
		      end_loop_55:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_18;
			goto next_loop_55;
		      end_loop_56:
		      end_18:
			level = level - (SI_Long)1L;
			goto next_loop_54;
		      end_loop_54:;
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_57:
			    if (level < ab_loop_bind_)
				goto end_loop_57;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_58:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_59:
			    if ( !TRUEP(marked))
				goto end_loop_58;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_59;
			  end_loop_58:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_19;
			    goto next_loop_58;
			  end_loop_59:
			  end_19:
			    level = level - (SI_Long)1L;
			    goto next_loop_57;
			  end_loop_57:;
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (kb_specific_value);
			    else
				kb_specific_value = No_specific_property_value;
			}
			else
			    kb_specific_value = No_specific_property_value;
			if ( !EQ(kb_specific_value,No_specific_property_value))
			    resulting_value = kb_specific_value;
			else {
			    skip_list = CDR(global_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_60:
			    if (level < ab_loop_bind_)
				goto end_loop_60;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_61:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_62:
			    if ( !TRUEP(marked))
				goto end_loop_61;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_62;
			  end_loop_61:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_20;
			    goto next_loop_61;
			  end_loop_62:
			  end_20:
			    level = level - (SI_Long)1L;
			    goto next_loop_60;
			  end_loop_60:;
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			temp_3 = TRUEP(resulting_value);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (temp_3) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(initial_type,
				Class_description_gkbprop);
			temp_3 =  !(gensymed_symbol ? 
				TRUEP(memq_function(class_type_qm,
				ISVREF(gensymed_symbol,(SI_Long)2L))) : 
				TRUEP(Nil));
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (temp_3) {
			non_type_conforming_class_value_qm = name;
			goto end_loop_2;
		    }
		    else;
		}
	    }
	    else;
	}
	else {
	    if (SYMBOLP(class_type_qm)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_type_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_type_qm) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_63:
		if (level < ab_loop_bind_)
		    goto end_loop_63;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_64:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_65:
		if ( !TRUEP(marked))
		    goto end_loop_64;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_65;
	      end_loop_64:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_21;
		goto next_loop_64;
	      end_loop_65:
	      end_21:
		level = level - (SI_Long)1L;
		goto next_loop_63;
	      end_loop_63:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_type_qm;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			    tail);
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_66:
		if (level < ab_loop_bind_)
		    goto end_loop_66;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_67:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_68:
		if ( !TRUEP(marked))
		    goto end_loop_67;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_68;
	      end_loop_67:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_22;
		goto next_loop_67;
	      end_loop_68:
	      end_22:
		level = level - (SI_Long)1L;
		goto next_loop_66;
	      end_loop_66:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_69:
		    if (level < ab_loop_bind_)
			goto end_loop_69;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_70:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_71:
		    if ( !TRUEP(marked))
			goto end_loop_70;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_71;
		  end_loop_70:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_23;
		    goto next_loop_70;
		  end_loop_71:
		  end_23:
		    level = level - (SI_Long)1L;
		    goto next_loop_69;
		  end_loop_69:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_72:
		    if (level < ab_loop_bind_)
			goto end_loop_72;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_73:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_74:
		    if ( !TRUEP(marked))
			goto end_loop_73;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_74;
		  end_loop_73:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_24;
		    goto next_loop_73;
		  end_loop_74:
		  end_24:
		    level = level - (SI_Long)1L;
		    goto next_loop_72;
		  end_loop_72:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_3 = TRUEP(resulting_value);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_type_qm;
		key_hash_value = SXHASH_SYMBOL_1(class_type_qm) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_75:
		if (level < ab_loop_bind_)
		    goto end_loop_75;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_76:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_77:
		if ( !TRUEP(marked))
		    goto end_loop_76;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_77;
	      end_loop_76:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_25;
		goto next_loop_76;
	      end_loop_77:
	      end_25:
		level = level - (SI_Long)1L;
		goto next_loop_75;
	      end_loop_75:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_type_qm;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			    tail);
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_78:
		if (level < ab_loop_bind_)
		    goto end_loop_78;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_79:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_80:
		if ( !TRUEP(marked))
		    goto end_loop_79;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_80;
	      end_loop_79:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_26;
		goto next_loop_79;
	      end_loop_80:
	      end_26:
		level = level - (SI_Long)1L;
		goto next_loop_78;
	      end_loop_78:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_81:
		    if (level < ab_loop_bind_)
			goto end_loop_81;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_82:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_83:
		    if ( !TRUEP(marked))
			goto end_loop_82;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_83;
		  end_loop_82:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_27;
		    goto next_loop_82;
		  end_loop_83:
		  end_27:
		    level = level - (SI_Long)1L;
		    goto next_loop_81;
		  end_loop_81:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_84:
		    if (level < ab_loop_bind_)
			goto end_loop_84;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_85:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_86:
		    if ( !TRUEP(marked))
			goto end_loop_85;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_86;
		  end_loop_85:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_28;
		    goto next_loop_85;
		  end_loop_86:
		  end_28:
		    level = level - (SI_Long)1L;
		    goto next_loop_84;
		  end_loop_84:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Object_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_3 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 =  !temp_3;
		if (temp_3);
		else
		    temp_3 = TRUEP(get_class_feature_if_any(class_type_qm,
			    Qnot_user_instantiable));
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if (temp_3) {
		type_not_an_object_qm = name;
		not_an_instantiable_object_class_qm = class_type_qm;
		goto end_loop_2;
	    }
	    else if (initial_value_is_defined_class_qm) {
		skip_list = CDR(Symbol_properties_table);
		key_value = initial_type;
		key_hash_value = SXHASH_SYMBOL_1(initial_type) & 
			IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_87:
		if (level < ab_loop_bind_)
		    goto end_loop_87;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_88:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_89:
		if ( !TRUEP(marked))
		    goto end_loop_88;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_89;
	      end_loop_88:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_29;
		goto next_loop_88;
	      end_loop_89:
	      end_29:
		level = level - (SI_Long)1L;
		goto next_loop_87;
	      end_loop_87:;
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = initial_type;
		    temp_1 = Symbol_properties_table;
		    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
			    tail);
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
		    new_cons = ISVREF(Available_lookup_conses_vector,
			    IFIX(Current_thread_index));
		    if (new_cons) {
			temp_2 = Available_lookup_conses_vector;
			svref_arg_2 = Current_thread_index;
			svref_new_value = M_CDR(new_cons);
			SVREF(temp_2,svref_arg_2) = svref_new_value;
			if ( !TRUEP(ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index)))) {
			    temp_2 = Available_lookup_conses_tail_vector;
			    svref_arg_2 = Current_thread_index;
			    SVREF(temp_2,svref_arg_2) = Nil;
			}
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp_1,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_90:
		if (level < ab_loop_bind_)
		    goto end_loop_90;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_91:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
	      next_loop_92:
		if ( !TRUEP(marked))
		    goto end_loop_91;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp_1 = ATOMIC_REF_OBJECT(reference);
		temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
		result = VALUES_2(temp_1,temp);
		MVS_2(result,succ,marked);
		goto next_loop_92;
	      end_loop_91:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_30;
		goto next_loop_91;
	      end_loop_92:
	      end_30:
		level = level - (SI_Long)1L;
		goto next_loop_90;
	      end_loop_90:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_93:
		    if (level < ab_loop_bind_)
			goto end_loop_93;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_94:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_95:
		    if ( !TRUEP(marked))
			goto end_loop_94;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_95;
		  end_loop_94:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_31;
		    goto next_loop_94;
		  end_loop_95:
		  end_31:
		    level = level - (SI_Long)1L;
		    goto next_loop_93;
		  end_loop_93:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_96:
		    if (level < ab_loop_bind_)
			goto end_loop_96;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_97:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		  next_loop_98:
		    if ( !TRUEP(marked))
			goto end_loop_97;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp_1 = ATOMIC_REF_OBJECT(reference);
		    temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? 
			    T : Nil;
		    result = VALUES_2(temp_1,temp);
		    MVS_2(result,succ,marked);
		    goto next_loop_98;
		  end_loop_97:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_32;
		    goto next_loop_97;
		  end_loop_98:
		  end_32:
		    level = level - (SI_Long)1L;
		    goto next_loop_96;
		  end_loop_96:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		gensymed_symbol = resulting_value;
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Object_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol_3 = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_4 = (SI_Long)1L;
			gensymed_symbol_5 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_4 = gensymed_symbol_4 << 
				gensymed_symbol_5;
			gensymed_symbol_3 = gensymed_symbol_3 & 
				gensymed_symbol_4;
			temp_3 = (SI_Long)0L < gensymed_symbol_3;
		    }
		    else
			temp_3 = TRUEP(Nil);
		}
		else
		    temp_3 = TRUEP(Nil);
		temp_3 =  !temp_3;
		if (temp_3);
		else
		    temp_3 = TRUEP(get_class_feature_if_any(initial_type,
			    Qnot_user_instantiable));
		if (temp_3) {
		    not_an_object_qm = name;
		    not_an_instantiable_object_class_qm = initial_type;
		    goto end_loop_2;
		}
		else {
		    if (SYMBOLP(class_type_qm)) {
			skip_list = CDR(Symbol_properties_table);
			key_value = class_type_qm;
			key_hash_value = SXHASH_SYMBOL_1(class_type_qm) & 
				IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_99:
			if (level < ab_loop_bind_)
			    goto end_loop_99;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_100:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_101:
			if ( !TRUEP(marked))
			    goto end_loop_100;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_101;
		      end_loop_100:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_33;
			goto next_loop_100;
		      end_loop_101:
		      end_33:
			level = level - (SI_Long)1L;
			goto next_loop_99;
		      end_loop_99:;
			gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if ( !TRUEP(gensymed_symbol)) {
			    gensymed_symbol = class_type_qm;
			    temp_1 = Symbol_properties_table;
			    temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				    IFIX(Most_positive_fixnum));
			    tail = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				    Nil);
			    head = 
				    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				    tail);
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_2 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_2,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_2 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = Nil;
				}
				gensymed_symbol_1 = new_cons;
			    }
			    else
				gensymed_symbol_1 = Nil;
			    if ( !TRUEP(gensymed_symbol_1))
				gensymed_symbol_1 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_1) = 
				    Qsymbol_properties_hash_table;
			    new_cons = 
				    ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index));
			    if (new_cons) {
				temp_2 = Available_lookup_conses_vector;
				svref_arg_2 = Current_thread_index;
				svref_new_value = M_CDR(new_cons);
				SVREF(temp_2,svref_arg_2) = svref_new_value;
				if ( 
					!TRUEP(ISVREF(Available_lookup_conses_vector,
					IFIX(Current_thread_index)))) {
				    temp_2 = 
					    Available_lookup_conses_tail_vector;
				    svref_arg_2 = Current_thread_index;
				    SVREF(temp_2,svref_arg_2) = Nil;
				}
				gensymed_symbol_2 = new_cons;
			    }
			    else
				gensymed_symbol_2 = Nil;
			    if ( !TRUEP(gensymed_symbol_2))
				gensymed_symbol_2 = 
					replenish_lookup_cons_pool();
			    M_CAR(gensymed_symbol_2) = head;
			    M_CDR(gensymed_symbol_2) = tail;
			    inline_note_allocate_cons(gensymed_symbol_2,
				    Qlookup);
			    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			    inline_note_allocate_cons(gensymed_symbol_1,
				    Qlookup);
			    gensymed_symbol = set_skip_list_entry(temp_1,
				    FIX((SI_Long)31L),Qeq,Nil,T,
				    gensymed_symbol,temp,gensymed_symbol_1);
			}
			global_properties = gensymed_symbol;
			skip_list = CDR(global_properties);
			key_value = 
				Current_kb_specific_property_list_property_name;
			key_hash_value = 
				SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_102:
			if (level < ab_loop_bind_)
			    goto end_loop_102;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_103:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
		      next_loop_104:
			if ( !TRUEP(marked))
			    goto end_loop_103;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp_1 = ATOMIC_REF_OBJECT(reference);
			temp = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp_1,temp);
			MVS_2(result,succ,marked);
			goto next_loop_104;
		      end_loop_103:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_34;
			goto next_loop_103;
		      end_loop_104:
		      end_34:
			level = level - (SI_Long)1L;
			goto next_loop_102;
		      end_loop_102:;
			kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
				key_hash_value ? (EQ(key_value,ISVREF(curr,
				(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
				Nil) : Nil;
			if (kb_properties);
			else
			    kb_properties = Nil;
			if (kb_properties) {
			    skip_list = CDR(kb_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_105:
			    if (level < ab_loop_bind_)
				goto end_loop_105;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_106:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_107:
			    if ( !TRUEP(marked))
				goto end_loop_106;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_107;
			  end_loop_106:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_35;
			    goto next_loop_106;
			  end_loop_107:
			  end_35:
			    level = level - (SI_Long)1L;
			    goto next_loop_105;
			  end_loop_105:;
			    kb_specific_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (kb_specific_value);
			    else
				kb_specific_value = No_specific_property_value;
			}
			else
			    kb_specific_value = No_specific_property_value;
			if ( !EQ(kb_specific_value,No_specific_property_value))
			    resulting_value = kb_specific_value;
			else {
			    skip_list = CDR(global_properties);
			    key_value = Class_description_gkbprop;
			    key_hash_value = 
				    SXHASH_SYMBOL_1(Class_description_gkbprop) 
				    & IFIX(Most_positive_fixnum);
			    bottom_level = (SI_Long)0L;
			    marked = Nil;
			    pred = M_CAR(skip_list);
			    curr = Nil;
			    succ = Nil;
			    level = (SI_Long)31L;
			    ab_loop_bind_ = bottom_level;
			  next_loop_108:
			    if (level < ab_loop_bind_)
				goto end_loop_108;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			  next_loop_109:
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			  next_loop_110:
			    if ( !TRUEP(marked))
				goto end_loop_109;
			    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				    (SI_Long)0L),level));
			    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			    temp_1 = ATOMIC_REF_OBJECT(reference);
			    temp = (SI_Long)355L == 
				    ATOMIC_REF_STAMP(reference) ? T : Nil;
			    result = VALUES_2(temp_1,temp);
			    MVS_2(result,succ,marked);
			    goto next_loop_110;
			  end_loop_109:
			    entry_hash = ISVREF(curr,(SI_Long)1L);
			    if (IFIX(entry_hash) < key_hash_value || 
				    IFIX(entry_hash) == key_hash_value &&  
				    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
				pred = curr;
				curr = succ;
			    }
			    else
				goto end_36;
			    goto next_loop_109;
			  end_loop_110:
			  end_36:
			    level = level - (SI_Long)1L;
			    goto next_loop_108;
			  end_loop_108:;
			    resulting_value = IFIX(ISVREF(curr,
				    (SI_Long)1L)) == key_hash_value ? 
				    (EQ(key_value,ISVREF(curr,
				    (SI_Long)2L)) ? ISVREF(curr,
				    (SI_Long)3L) : Nil) : Nil;
			    if (resulting_value);
			    else
				resulting_value = Nil;
			}
			temp_3 = TRUEP(resulting_value);
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (temp_3) {
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(initial_type,
				Class_description_gkbprop);
			temp_3 =  !(gensymed_symbol ? 
				TRUEP(memq_function(class_type_qm,
				ISVREF(gensymed_symbol,(SI_Long)2L))) : 
				TRUEP(Nil));
		    }
		    else
			temp_3 = TRUEP(Nil);
		    if (temp_3) {
			non_type_conforming_class_value_qm = name;
			goto end_loop_2;
		    }
		    else;
		}
	    }
	    else;
	}
    }
    else;
    goto next_loop_2;
  end_loop_2:;
    if (bad_attribute_name_qm)
	return bad_attribute_name(bad_attribute_name_qm);
    else if (not_a_variable_or_parameter_qm) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(3,string_constant_50,
		not_a_variable_or_parameter_qm,
		not_an_instantiable_variable_or_parameter_class_qm);
	return VALUES_2(temp_1,temp);
    }
    else if (type_not_a_variable_or_parameter_qm) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(3,string_constant_51,
		type_not_a_variable_or_parameter_qm,
		not_an_instantiable_variable_or_parameter_class_qm);
	return VALUES_2(temp_1,temp);
    }
    else if (initial_value_does_not_conform_to_type_qm) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_52,
		initial_value_does_not_conform_to_type_qm);
	return VALUES_2(temp_1,temp);
    }
    else if (non_type_conforming_class_value_qm) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_53,
		non_type_conforming_class_value_qm);
	return VALUES_2(temp_1,temp);
    }
    else if (not_an_object_qm) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(3,string_constant_54,not_an_object_qm,
		not_an_instantiable_object_class_qm);
	return VALUES_2(temp_1,temp);
    }
    else if (type_not_an_object_qm) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(3,string_constant_55,
		type_not_an_object_qm,not_an_instantiable_object_class_qm);
	return VALUES_2(temp_1,temp);
    }
    else if (class_type_designation_specifies_a_g2_type) {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_56,
		class_type_designation_specifies_a_g2_type);
	return VALUES_2(temp_1,temp);
    }
    else {
	attribute_description = Nil;
	ab_loop_list_ = transformed_value;
	attribute_name = Nil;
	initial_value = Nil;
	indexed_qm = Nil;
	rest_1 = Nil;
	indexed_attributes = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_111:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_111;
	attribute_description = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	attribute_name = CAR(attribute_description);
	temp = CDR(attribute_description);
	temp = CDR(temp);
	initial_value = CAR(temp);
	temp = CDR(attribute_description);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	indexed_qm = CAR(temp);
	temp = CDR(attribute_description);
	temp = CDR(temp);
	temp = CDR(temp);
	temp = CDR(temp);
	rest_1 = CDR(temp);
	if (EQUAL(indexed_qm,list_constant_17)) {
	    ab_loopvar__1 = slot_value_cons_1(attribute_name,Nil);
	    if (ab_loopvar_)
		M_CDR(ab_loopvar_) = ab_loopvar__1;
	    else
		indexed_attributes = ab_loopvar__1;
	    ab_loopvar_ = ab_loopvar__1;
	    M_CDDDDR(attribute_description) = rest_1;
	}
	goto next_loop_111;
      end_loop_111:
	temp = get_lookup_slot_value_given_default(definition,
		Qindexed_attributes_for_definition,Nil);
	prepare_for_indexed_attributes_moveage(definition,temp,
		indexed_attributes);
	return VALUES_1(transformed_value);
    }
}

/* SYSTEM-CLASS-IS-NOT-USER-SUBCLASSABLE-P */
Object system_class_is_not_user_subclassable_p(class_1)
    Object class_1;
{
    Object scope_conses, ab_loopvar_, subclass, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(200,90);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = class_1;
    subclass = Nil;
    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      if (get_foundation_class_for_class(subclass)) {
	  result = VALUES_1(Nil);
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(T);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

Object Cached_system_slot_is_present_only_on_non_user_subclassable_system_slots_prop = UNBOUND;

static Object Qcached_system_slot_is_present_only_on_non_user_subclassable_system_slots;  /* cached-system-slot-is-present-only-on-non-user-subclassable-system-slots */

static Object Qunknown;            /* unknown */

/* SYSTEM-SLOT-IS-PRESENT-ONLY-ON-NON-USER-SUBCLASSABLE-SYSTEM-SLOTS */
Object system_slot_is_present_only_on_non_user_subclassable_system_slots(symbol)
    Object symbol;
{
    Object value;

    x_note_fn_call(200,91);
    value = getfq_function(INLINE_SYMBOL_PLIST(symbol),
	    Qcached_system_slot_is_present_only_on_non_user_subclassable_system_slots,
	    Qunknown);
    if (EQ(value,Qunknown)) {
	value =  !TRUEP(system_slot_is_user_subclassable_1(Qitem,symbol)) ?
		 T : Nil;
	mutate_global_property(symbol,value,
		Qcached_system_slot_is_present_only_on_non_user_subclassable_system_slots);
    }
    return VALUES_1(value);
}

/* SYSTEM-SLOT-IS-USER-SUBCLASSABLE-1 */
Object system_slot_is_user_subclassable_1(class_1,symbol)
    Object class_1, symbol;
{
    Object class_description_qm, skip_list, key_value, marked, pred, curr;
    Object succ, reference, temp_1, temp_2, entry_hash, gensymed_symbol, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_1, gensymed_symbol_2, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, subclass;
    Object ab_loop_list_, ab_loop_it_;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp;
    Object result;

    x_note_fn_call(200,92);
    class_description_qm = 
	    lookup_global_or_kb_specific_property_value(class_1,
	    Class_description_gkbprop);
    temp = class_description_qm ?  !TRUEP(ISVREF(class_description_qm,
	    (SI_Long)20L)) : TRUEP(Qnil);
    if (temp);
    else
	temp = TRUEP(system_class_is_not_user_subclassable_p(class_1));
    if ( !temp) {
	skip_list = CDR(Symbol_properties_table);
	key_value = class_1;
	key_hash_value = SXHASH_SYMBOL_1(class_1) & IFIX(Most_positive_fixnum);
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
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_2:
	if ( !TRUEP(marked))
	    goto end_loop_1;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
	goto next_loop_2;
      end_loop_1:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = class_1;
	    temp_1 = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
		    IFIX(Most_positive_fixnum));
	    tail = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
		    Nil);
	    head = 
		    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
		gensymed_symbol_2 = new_cons;
	    }
	    else
		gensymed_symbol_2 = Nil;
	    if ( !TRUEP(gensymed_symbol_2))
		gensymed_symbol_2 = replenish_lookup_cons_pool();
	    M_CAR(gensymed_symbol_2) = head;
	    M_CDR(gensymed_symbol_2) = tail;
	    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
	    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
	    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
	    gensymed_symbol = set_skip_list_entry(temp_1,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_2,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	skip_list = CDR(global_properties);
	key_value = Current_kb_specific_property_list_property_name;
	key_hash_value = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	bottom_level = (SI_Long)0L;
	marked = Nil;
	pred = M_CAR(skip_list);
	curr = Nil;
	succ = Nil;
	level = (SI_Long)31L;
	ab_loop_bind_ = bottom_level;
      next_loop_3:
	if (level < ab_loop_bind_)
	    goto end_loop_3;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
      next_loop_4:
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
      next_loop_5:
	if ( !TRUEP(marked))
	    goto end_loop_4;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp_1 = ATOMIC_REF_OBJECT(reference);
	temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp_1,temp_2);
	MVS_2(result,succ,marked);
	goto next_loop_5;
      end_loop_4:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
	    pred = curr;
	    curr = succ;
	}
	else
	    goto end_2;
	goto next_loop_4;
      end_loop_5:
      end_2:
	level = level - (SI_Long)1L;
	goto next_loop_3;
      end_loop_3:;
	kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value ? 
		(EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if (kb_properties);
	else
	    kb_properties = Nil;
	if (kb_properties) {
	    skip_list = CDR(kb_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_6:
	    if (level < ab_loop_bind_)
		goto end_loop_6;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_7:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_8:
	    if ( !TRUEP(marked))
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_8;
	  end_loop_7:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_3;
	    goto next_loop_7;
	  end_loop_8:
	  end_3:
	    level = level - (SI_Long)1L;
	    goto next_loop_6;
	  end_loop_6:;
	    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (kb_specific_value);
	    else
		kb_specific_value = No_specific_property_value;
	}
	else
	    kb_specific_value = No_specific_property_value;
	if ( !EQ(kb_specific_value,No_specific_property_value))
	    resulting_value = kb_specific_value;
	else {
	    skip_list = CDR(global_properties);
	    key_value = Class_description_gkbprop;
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    bottom_level = (SI_Long)0L;
	    marked = Nil;
	    pred = M_CAR(skip_list);
	    curr = Nil;
	    succ = Nil;
	    level = (SI_Long)31L;
	    ab_loop_bind_ = bottom_level;
	  next_loop_9:
	    if (level < ab_loop_bind_)
		goto end_loop_9;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_10:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	  next_loop_11:
	    if ( !TRUEP(marked))
		goto end_loop_10;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp_1 = ATOMIC_REF_OBJECT(reference);
	    temp_2 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp_1,temp_2);
	    MVS_2(result,succ,marked);
	    goto next_loop_11;
	  end_loop_10:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_4;
	    goto next_loop_10;
	  end_loop_11:
	  end_4:
	    level = level - (SI_Long)1L;
	    goto next_loop_9;
	  end_loop_9:;
	    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if (resulting_value);
	    else
		resulting_value = Nil;
	}
	gensymed_symbol = resulting_value;
	temp_2 = get_slot_description_of_class_description_function(symbol,
		gensymed_symbol,Nil);
	if (temp_2)
	    return VALUES_1(temp_2);
	else {
	    subclass = Nil;
	    ab_loop_list_ = 
		    lookup_global_or_kb_specific_property_value(class_1,
		    Inferior_classes_gkbprop);
	    ab_loop_it_ = Nil;
	  next_loop_12:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_12;
	    subclass = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = system_slot_is_user_subclassable_1(subclass,symbol);
	    if (ab_loop_it_)
		return VALUES_1(ab_loop_it_);
	    goto next_loop_12;
	  end_loop_12:
	    return VALUES_1(Qnil);
	}
    }
    else
	return VALUES_1(Nil);
}

static Object Qslot_category;      /* slot-category */

static Object Qslot_names_for_alias;  /* slot-names-for-alias */

/* RESERVED-SYSTEM-SLOT-NAME-P */
Object reserved_system_slot_name_p(definition,symbol)
    Object definition, symbol;
{
    Object temp, list_1, sub_class_bit_vector, object_definition_qm;
    Object message_definition_qm, connection_definition_qm, class_1;
    Object ab_loop_list_, ab_loop_it_, ab_loop_desetq_, scope_conses;
    Object ab_loopvar_, class_description, skip_list, key_value, marked, pred;
    Object curr, succ, reference, temp_1, entry_hash, gensymed_symbol_3, tail;
    Object head, new_cons, svref_arg_1, svref_arg_2, svref_new_value;
    Object gensymed_symbol_4, gensymed_symbol_5, global_properties;
    Object kb_properties, kb_specific_value, resulting_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, key_hash_value, bottom_level;
    SI_Long level, ab_loop_bind_;
    char temp_2;
    Declare_special(1);
    Object result;

    x_note_fn_call(200,93);
    temp = EQ(symbol,Qab_class) ? T : Nil;
    if (temp);
    else {
	list_1 = INLINE_SYMBOL_PLIST(symbol);
      next_loop:
	if ( !TRUEP(list_1) || EQ(M_CAR(list_1),Qslot_category))
	    goto end_loop;
	list_1 = M_CDR(M_CDR(list_1));
	goto next_loop;
      end_loop:;
	temp = (list_1 ? TRUEP(M_CAR(M_CDR(list_1))) : TRUEP(Nil)) ? ( 
		!TRUEP(system_slot_is_present_only_on_non_user_subclassable_system_slots(symbol)) 
		? T : Nil) : Nil;
    }
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(definition,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Object_definition_class_description,(SI_Long)18L));
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
	    object_definition_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    object_definition_qm = Nil;
	sub_class_bit_vector = ISVREF(ISVREF(definition,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Message_definition_class_description,
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
	    message_definition_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    message_definition_qm = Nil;
	sub_class_bit_vector = ISVREF(ISVREF(definition,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Connection_definition_class_description,
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
	    connection_definition_qm = (SI_Long)0L < gensymed_symbol ? T : Nil;
	}
	else
	    connection_definition_qm = Nil;
	class_1 = Nil;
	ab_loop_list_ = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(symbol),
		Qslot_names_for_alias);
	ab_loop_it_ = Nil;
	ab_loop_desetq_ = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	class_1 = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp =  !TRUEP(class_1) ? T : Nil;
	if (temp);
	else {
	    scope_conses = Scope_conses;
	    ab_loopvar_ = Nil;
	    ab_loopvar_ = class_1;
	    class_1 = Nil;
	    PUSH_SPECIAL_WITH_SYMBOL(Scope_conses,Qscope_conses,scope_conses,
		    0);
	      class_description = Nil;
	      ab_loop_it_ = Nil;
	      ab_loopvar_ = collect_subclasses(ab_loopvar_);
	    next_loop_2:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_2;
	      temp = M_CAR(ab_loopvar_);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      class_1 = temp;
	      class_description = 
		      lookup_global_or_kb_specific_property_value(class_1,
		      Class_description_gkbprop);
	      if (class_description) {
		  if (object_definition_qm) {
		      skip_list = CDR(Symbol_properties_table);
		      key_value = class_1;
		      key_hash_value = SXHASH_SYMBOL_1(class_1) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_3:
		      if (level < ab_loop_bind_)
			  goto end_loop_3;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_4:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		    next_loop_5:
		      if ( !TRUEP(marked))
			  goto end_loop_4;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		      goto next_loop_5;
		    end_loop_4:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_1;
		      goto next_loop_4;
		    end_loop_5:
		    end_1:
		      level = level - (SI_Long)1L;
		      goto next_loop_3;
		    end_loop_3:;
		      gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) 
			      == key_hash_value ? (EQ(key_value,
			      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
			      (SI_Long)3L) : Nil) : Nil;
		      if ( !TRUEP(gensymed_symbol_3)) {
			  gensymed_symbol_3 = class_1;
			  temp_1 = Symbol_properties_table;
			  temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
				  IFIX(Most_positive_fixnum));
			  tail = 
				  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				  Nil);
			  head = 
				  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				  tail);
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_4 = new_cons;
			  }
			  else
			      gensymed_symbol_4 = Nil;
			  if ( !TRUEP(gensymed_symbol_4))
			      gensymed_symbol_4 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_4) = 
				  Qsymbol_properties_hash_table;
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_5 = new_cons;
			  }
			  else
			      gensymed_symbol_5 = Nil;
			  if ( !TRUEP(gensymed_symbol_5))
			      gensymed_symbol_5 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_5) = head;
			  M_CDR(gensymed_symbol_5) = tail;
			  inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			  inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			  gensymed_symbol_3 = set_skip_list_entry(temp_1,
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol_3,temp,gensymed_symbol_4);
		      }
		      global_properties = gensymed_symbol_3;
		      skip_list = CDR(global_properties);
		      key_value = 
			      Current_kb_specific_property_list_property_name;
		      key_hash_value = 
			      SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			      & IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_6:
		      if (level < ab_loop_bind_)
			  goto end_loop_6;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_7:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		    next_loop_8:
		      if ( !TRUEP(marked))
			  goto end_loop_7;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		      goto next_loop_8;
		    end_loop_7:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_2;
		      goto next_loop_7;
		    end_loop_8:
		    end_2:
		      level = level - (SI_Long)1L;
		      goto next_loop_6;
		    end_loop_6:;
		      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (kb_properties);
		      else
			  kb_properties = Nil;
		      if (kb_properties) {
			  skip_list = CDR(kb_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_9:
			  if (level < ab_loop_bind_)
			      goto end_loop_9;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_10:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			next_loop_11:
			  if ( !TRUEP(marked))
			      goto end_loop_10;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_11;
			end_loop_10:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_3;
			  goto next_loop_10;
			end_loop_11:
			end_3:
			  level = level - (SI_Long)1L;
			  goto next_loop_9;
			end_loop_9:;
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			  if (kb_specific_value);
			  else
			      kb_specific_value = No_specific_property_value;
		      }
		      else
			  kb_specific_value = No_specific_property_value;
		      if ( !EQ(kb_specific_value,No_specific_property_value))
			  resulting_value = kb_specific_value;
		      else {
			  skip_list = CDR(global_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_12:
			  if (level < ab_loop_bind_)
			      goto end_loop_12;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_13:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			next_loop_14:
			  if ( !TRUEP(marked))
			      goto end_loop_13;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_14;
			end_loop_13:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_4;
			  goto next_loop_13;
			end_loop_14:
			end_4:
			  level = level - (SI_Long)1L;
			  goto next_loop_12;
			end_loop_12:;
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
			  if (resulting_value);
			  else
			      resulting_value = Nil;
		      }
		      gensymed_symbol_3 = resulting_value;
		      if (gensymed_symbol_3) {
			  sub_class_bit_vector = ISVREF(gensymed_symbol_3,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Object_class_description,
				  (SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_1 = (SI_Long)1L;
			      gensymed_symbol_2 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_1 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol = gensymed_symbol & 
				      gensymed_symbol_1;
			      temp_2 = (SI_Long)0L < gensymed_symbol;
			  }
			  else
			      temp_2 = TRUEP(Nil);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else if (message_definition_qm) {
		      skip_list = CDR(Symbol_properties_table);
		      key_value = class_1;
		      key_hash_value = SXHASH_SYMBOL_1(class_1) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_15:
		      if (level < ab_loop_bind_)
			  goto end_loop_15;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_16:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		    next_loop_17:
		      if ( !TRUEP(marked))
			  goto end_loop_16;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		      goto next_loop_17;
		    end_loop_16:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_5;
		      goto next_loop_16;
		    end_loop_17:
		    end_5:
		      level = level - (SI_Long)1L;
		      goto next_loop_15;
		    end_loop_15:;
		      gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) 
			      == key_hash_value ? (EQ(key_value,
			      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
			      (SI_Long)3L) : Nil) : Nil;
		      if ( !TRUEP(gensymed_symbol_3)) {
			  gensymed_symbol_3 = class_1;
			  temp_1 = Symbol_properties_table;
			  temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
				  IFIX(Most_positive_fixnum));
			  tail = 
				  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				  Nil);
			  head = 
				  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				  tail);
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_4 = new_cons;
			  }
			  else
			      gensymed_symbol_4 = Nil;
			  if ( !TRUEP(gensymed_symbol_4))
			      gensymed_symbol_4 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_4) = 
				  Qsymbol_properties_hash_table;
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_5 = new_cons;
			  }
			  else
			      gensymed_symbol_5 = Nil;
			  if ( !TRUEP(gensymed_symbol_5))
			      gensymed_symbol_5 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_5) = head;
			  M_CDR(gensymed_symbol_5) = tail;
			  inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			  inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			  gensymed_symbol_3 = set_skip_list_entry(temp_1,
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol_3,temp,gensymed_symbol_4);
		      }
		      global_properties = gensymed_symbol_3;
		      skip_list = CDR(global_properties);
		      key_value = 
			      Current_kb_specific_property_list_property_name;
		      key_hash_value = 
			      SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			      & IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_18:
		      if (level < ab_loop_bind_)
			  goto end_loop_18;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_19:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		    next_loop_20:
		      if ( !TRUEP(marked))
			  goto end_loop_19;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		      goto next_loop_20;
		    end_loop_19:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_6;
		      goto next_loop_19;
		    end_loop_20:
		    end_6:
		      level = level - (SI_Long)1L;
		      goto next_loop_18;
		    end_loop_18:;
		      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (kb_properties);
		      else
			  kb_properties = Nil;
		      if (kb_properties) {
			  skip_list = CDR(kb_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_21:
			  if (level < ab_loop_bind_)
			      goto end_loop_21;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_22:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			next_loop_23:
			  if ( !TRUEP(marked))
			      goto end_loop_22;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_23;
			end_loop_22:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_7;
			  goto next_loop_22;
			end_loop_23:
			end_7:
			  level = level - (SI_Long)1L;
			  goto next_loop_21;
			end_loop_21:;
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			  if (kb_specific_value);
			  else
			      kb_specific_value = No_specific_property_value;
		      }
		      else
			  kb_specific_value = No_specific_property_value;
		      if ( !EQ(kb_specific_value,No_specific_property_value))
			  resulting_value = kb_specific_value;
		      else {
			  skip_list = CDR(global_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_24:
			  if (level < ab_loop_bind_)
			      goto end_loop_24;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_25:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			next_loop_26:
			  if ( !TRUEP(marked))
			      goto end_loop_25;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_26;
			end_loop_25:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_8;
			  goto next_loop_25;
			end_loop_26:
			end_8:
			  level = level - (SI_Long)1L;
			  goto next_loop_24;
			end_loop_24:;
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
			  if (resulting_value);
			  else
			      resulting_value = Nil;
		      }
		      gensymed_symbol_3 = resulting_value;
		      if (gensymed_symbol_3) {
			  sub_class_bit_vector = ISVREF(gensymed_symbol_3,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Message_class_description,
				  (SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_1 = (SI_Long)1L;
			      gensymed_symbol_2 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_1 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol = gensymed_symbol & 
				      gensymed_symbol_1;
			      temp_2 = (SI_Long)0L < gensymed_symbol;
			  }
			  else
			      temp_2 = TRUEP(Nil);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else if (connection_definition_qm) {
		      skip_list = CDR(Symbol_properties_table);
		      key_value = class_1;
		      key_hash_value = SXHASH_SYMBOL_1(class_1) & 
			      IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_27:
		      if (level < ab_loop_bind_)
			  goto end_loop_27;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_28:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		    next_loop_29:
		      if ( !TRUEP(marked))
			  goto end_loop_28;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		      goto next_loop_29;
		    end_loop_28:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_9;
		      goto next_loop_28;
		    end_loop_29:
		    end_9:
		      level = level - (SI_Long)1L;
		      goto next_loop_27;
		    end_loop_27:;
		      gensymed_symbol_3 = IFIX(ISVREF(curr,(SI_Long)1L)) 
			      == key_hash_value ? (EQ(key_value,
			      ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
			      (SI_Long)3L) : Nil) : Nil;
		      if ( !TRUEP(gensymed_symbol_3)) {
			  gensymed_symbol_3 = class_1;
			  temp_1 = Symbol_properties_table;
			  temp = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
				  IFIX(Most_positive_fixnum));
			  tail = 
				  make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				  Nil);
			  head = 
				  make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				  tail);
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_4 = new_cons;
			  }
			  else
			      gensymed_symbol_4 = Nil;
			  if ( !TRUEP(gensymed_symbol_4))
			      gensymed_symbol_4 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_4) = 
				  Qsymbol_properties_hash_table;
			  new_cons = ISVREF(Available_lookup_conses_vector,
				  IFIX(Current_thread_index));
			  if (new_cons) {
			      svref_arg_1 = Available_lookup_conses_vector;
			      svref_arg_2 = Current_thread_index;
			      svref_new_value = M_CDR(new_cons);
			      SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			      if ( 
				      !TRUEP(ISVREF(Available_lookup_conses_vector,
				      IFIX(Current_thread_index)))) {
				  svref_arg_1 = 
					  Available_lookup_conses_tail_vector;
				  svref_arg_2 = Current_thread_index;
				  SVREF(svref_arg_1,svref_arg_2) = Nil;
			      }
			      gensymed_symbol_5 = new_cons;
			  }
			  else
			      gensymed_symbol_5 = Nil;
			  if ( !TRUEP(gensymed_symbol_5))
			      gensymed_symbol_5 = replenish_lookup_cons_pool();
			  M_CAR(gensymed_symbol_5) = head;
			  M_CDR(gensymed_symbol_5) = tail;
			  inline_note_allocate_cons(gensymed_symbol_5,Qlookup);
			  M_CDR(gensymed_symbol_4) = gensymed_symbol_5;
			  inline_note_allocate_cons(gensymed_symbol_4,Qlookup);
			  gensymed_symbol_3 = set_skip_list_entry(temp_1,
				  FIX((SI_Long)31L),Qeq,Nil,T,
				  gensymed_symbol_3,temp,gensymed_symbol_4);
		      }
		      global_properties = gensymed_symbol_3;
		      skip_list = CDR(global_properties);
		      key_value = 
			      Current_kb_specific_property_list_property_name;
		      key_hash_value = 
			      SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			      & IFIX(Most_positive_fixnum);
		      bottom_level = (SI_Long)0L;
		      marked = Nil;
		      pred = M_CAR(skip_list);
		      curr = Nil;
		      succ = Nil;
		      level = (SI_Long)31L;
		      ab_loop_bind_ = bottom_level;
		    next_loop_30:
		      if (level < ab_loop_bind_)
			  goto end_loop_30;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		    next_loop_31:
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		    next_loop_32:
		      if ( !TRUEP(marked))
			  goto end_loop_31;
		      curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			      (SI_Long)0L),level));
		      reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		      temp_1 = ATOMIC_REF_OBJECT(reference);
		      temp = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			       T : Nil;
		      result = VALUES_2(temp_1,temp);
		      MVS_2(result,succ,marked);
		      goto next_loop_32;
		    end_loop_31:
		      entry_hash = ISVREF(curr,(SI_Long)1L);
		      if (IFIX(entry_hash) < key_hash_value || 
			      IFIX(entry_hash) == key_hash_value &&  
			      !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			  pred = curr;
			  curr = succ;
		      }
		      else
			  goto end_10;
		      goto next_loop_31;
		    end_loop_32:
		    end_10:
		      level = level - (SI_Long)1L;
		      goto next_loop_30;
		    end_loop_30:;
		      kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			      key_hash_value ? (EQ(key_value,ISVREF(curr,
			      (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			      Nil) : Nil;
		      if (kb_properties);
		      else
			  kb_properties = Nil;
		      if (kb_properties) {
			  skip_list = CDR(kb_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_33:
			  if (level < ab_loop_bind_)
			      goto end_loop_33;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_34:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			next_loop_35:
			  if ( !TRUEP(marked))
			      goto end_loop_34;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_35;
			end_loop_34:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_11;
			  goto next_loop_34;
			end_loop_35:
			end_11:
			  level = level - (SI_Long)1L;
			  goto next_loop_33;
			end_loop_33:;
			  kb_specific_value = IFIX(ISVREF(curr,
				  (SI_Long)1L)) == key_hash_value ? 
				  (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ?
				   ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
			  if (kb_specific_value);
			  else
			      kb_specific_value = No_specific_property_value;
		      }
		      else
			  kb_specific_value = No_specific_property_value;
		      if ( !EQ(kb_specific_value,No_specific_property_value))
			  resulting_value = kb_specific_value;
		      else {
			  skip_list = CDR(global_properties);
			  key_value = Class_description_gkbprop;
			  key_hash_value = 
				  SXHASH_SYMBOL_1(Class_description_gkbprop) 
				  & IFIX(Most_positive_fixnum);
			  bottom_level = (SI_Long)0L;
			  marked = Nil;
			  pred = M_CAR(skip_list);
			  curr = Nil;
			  succ = Nil;
			  level = (SI_Long)31L;
			  ab_loop_bind_ = bottom_level;
			next_loop_36:
			  if (level < ab_loop_bind_)
			      goto end_loop_36;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			next_loop_37:
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			next_loop_38:
			  if ( !TRUEP(marked))
			      goto end_loop_37;
			  curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				  (SI_Long)0L),level));
			  reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			  temp_1 = ATOMIC_REF_OBJECT(reference);
			  temp = (SI_Long)355L == 
				  ATOMIC_REF_STAMP(reference) ? T : Nil;
			  result = VALUES_2(temp_1,temp);
			  MVS_2(result,succ,marked);
			  goto next_loop_38;
			end_loop_37:
			  entry_hash = ISVREF(curr,(SI_Long)1L);
			  if (IFIX(entry_hash) < key_hash_value || 
				  IFIX(entry_hash) == key_hash_value &&  
				  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			      pred = curr;
			      curr = succ;
			  }
			  else
			      goto end_12;
			  goto next_loop_37;
			end_loop_38:
			end_12:
			  level = level - (SI_Long)1L;
			  goto next_loop_36;
			end_loop_36:;
			  resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				  == key_hash_value ? (EQ(key_value,
				  ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				  (SI_Long)3L) : Nil) : Nil;
			  if (resulting_value);
			  else
			      resulting_value = Nil;
		      }
		      gensymed_symbol_3 = resulting_value;
		      if (gensymed_symbol_3) {
			  sub_class_bit_vector = ISVREF(gensymed_symbol_3,
				  (SI_Long)19L);
			  superior_class_bit_number = 
				  IFIX(ISVREF(Connection_class_description,
				  (SI_Long)18L));
			  sub_class_vector_index = 
				  superior_class_bit_number >>  -  - 
				  (SI_Long)3L;
			  if (sub_class_vector_index < 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				      {
			      gensymed_symbol = 
				      UBYTE_8_ISAREF_1(sub_class_bit_vector,
				      sub_class_vector_index);
			      gensymed_symbol_1 = (SI_Long)1L;
			      gensymed_symbol_2 = 
				      superior_class_bit_number & (SI_Long)7L;
			      gensymed_symbol_1 = gensymed_symbol_1 << 
				      gensymed_symbol_2;
			      gensymed_symbol = gensymed_symbol & 
				      gensymed_symbol_1;
			      temp_2 = (SI_Long)0L < gensymed_symbol;
			  }
			  else
			      temp_2 = TRUEP(Nil);
		      }
		      else
			  temp_2 = TRUEP(Nil);
		  }
		  else
		      temp_2 = TRUEP(T);
	      }
	      else
		  temp_2 = TRUEP(Nil);
	      ab_loop_it_ = temp_2 ? assq_function(Qfoundation_class,
		      ISVREF(class_description,(SI_Long)12L)) : Nil;
	      if (ab_loop_it_) {
		  temp = ab_loop_it_;
		  goto end_13;
	      }
	      goto next_loop_2;
	    end_loop_2:
	      temp = Qnil;
	    end_13:;
	    POP_SPECIAL();
	}
	ab_loop_it_ = temp;
	if (ab_loop_it_)
	    return VALUES_1(ab_loop_it_);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_57;  /* "There is a badly formed class-qualified attribute name." */

/* BADLY-FORMED-ATTRIBUTE-NAME */
Object badly_formed_attribute_name()
{
    Object temp, temp_1;

    x_note_fn_call(200,94);
    temp = Bad_phrase;
    temp_1 = tformat_text_string(1,string_constant_57);
    return VALUES_2(temp,temp_1);
}

static Object string_constant_58;  /* "~A is the name of a G2 system attribute and cannot be a user-defined attribute." */

/* BAD-ATTRIBUTE-NAME */
Object bad_attribute_name(attribute_name)
    Object attribute_name;
{
    Object temp, temp_1;

    x_note_fn_call(200,95);
    temp = Bad_phrase;
    temp_1 = tformat_text_string(2,string_constant_58,attribute_name);
    return VALUES_2(temp,temp_1);
}

static Object string_constant_59;  /* "The direct superiors of a class must be complete before ~
				    *                           placing an initialization on ~a because it is a built-in ~
				    *                           attribute that requires specific built-in class inheritance."
				    */

/* SYSTEM-SLOT-OVERRIDE-BUT-NO-FOUNDATION-CLASS */
Object system_slot_override_but_no_foundation_class(slot_name)
    Object slot_name;
{
    Object temp, temp_1;

    x_note_fn_call(200,96);
    temp = Bad_phrase;
    temp_1 = tformat_text_string(2,string_constant_59,slot_name);
    return VALUES_2(temp,temp_1);
}

static Object list_constant_18;    /* # */

static Object Qitem_or_datum;      /* item-or-datum */

static Object Qdatum;              /* datum */

/* PARSED-ATTRIBUTE-INITIAL-VALUE-MATCHES-TYPE-P */
Object parsed_attribute_initial_value_matches_type_p(initial_value,
	    type_specification)
    Object initial_value, type_specification;
{
    Object type_specification_class, class_for_instantiation, skip_list;
    Object key_value, marked, pred, curr, succ, reference, temp, temp_1;
    Object entry_hash, gensymed_symbol, tail, head, new_cons, svref_arg_1;
    Object svref_arg_2, svref_new_value, gensymed_symbol_1, gensymed_symbol_2;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    char temp_2;
    Object result;

    x_note_fn_call(200,97);
    if (CONSP(initial_value) && EQ(M_CAR(initial_value),Kfuncall)) {
	if (class_type_specification_p(type_specification)) {
	    type_specification_class = M_CAR(M_CDR(type_specification));
	    class_for_instantiation = THIRD(initial_value);
	    if (SYMBOLP(class_for_instantiation)) {
		skip_list = CDR(Symbol_properties_table);
		key_value = class_for_instantiation;
		key_hash_value = SXHASH_SYMBOL_1(class_for_instantiation) 
			& IFIX(Most_positive_fixnum);
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_1:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_2:
		if ( !TRUEP(marked))
		    goto end_loop_1;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_2;
	      end_loop_1:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
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
		gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if ( !TRUEP(gensymed_symbol)) {
		    gensymed_symbol = class_for_instantiation;
		    temp = Symbol_properties_table;
		    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
			    IFIX(Most_positive_fixnum));
		    tail = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
			    Nil);
		    head = 
			    make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
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
			gensymed_symbol_1 = new_cons;
		    }
		    else
			gensymed_symbol_1 = Nil;
		    if ( !TRUEP(gensymed_symbol_1))
			gensymed_symbol_1 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_1) = Qsymbol_properties_hash_table;
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
			gensymed_symbol_2 = new_cons;
		    }
		    else
			gensymed_symbol_2 = Nil;
		    if ( !TRUEP(gensymed_symbol_2))
			gensymed_symbol_2 = replenish_lookup_cons_pool();
		    M_CAR(gensymed_symbol_2) = head;
		    M_CDR(gensymed_symbol_2) = tail;
		    inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
		    M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
		    inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
		    gensymed_symbol = set_skip_list_entry(temp,
			    FIX((SI_Long)31L),Qeq,Nil,T,gensymed_symbol,
			    temp_1,gensymed_symbol_1);
		}
		global_properties = gensymed_symbol;
		skip_list = CDR(global_properties);
		key_value = Current_kb_specific_property_list_property_name;
		key_hash_value = 
			SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			& IFIX(Most_positive_fixnum);
		bottom_level = (SI_Long)0L;
		marked = Nil;
		pred = M_CAR(skip_list);
		curr = Nil;
		succ = Nil;
		level = (SI_Long)31L;
		ab_loop_bind_ = bottom_level;
	      next_loop_3:
		if (level < ab_loop_bind_)
		    goto end_loop_3;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_4:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_5:
		if ( !TRUEP(marked))
		    goto end_loop_4;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_5;
	      end_loop_4:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_2;
		goto next_loop_4;
	      end_loop_5:
	      end_2:
		level = level - (SI_Long)1L;
		goto next_loop_3;
	      end_loop_3:;
		kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (kb_properties);
		else
		    kb_properties = Nil;
		if (kb_properties) {
		    skip_list = CDR(kb_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_6:
		    if (level < ab_loop_bind_)
			goto end_loop_6;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_7:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_8:
		    if ( !TRUEP(marked))
			goto end_loop_7;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_8;
		  end_loop_7:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_3;
		    goto next_loop_7;
		  end_loop_8:
		  end_3:
		    level = level - (SI_Long)1L;
		    goto next_loop_6;
		  end_loop_6:;
		    kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_specific_value);
		    else
			kb_specific_value = No_specific_property_value;
		}
		else
		    kb_specific_value = No_specific_property_value;
		if ( !EQ(kb_specific_value,No_specific_property_value))
		    resulting_value = kb_specific_value;
		else {
		    skip_list = CDR(global_properties);
		    key_value = Class_description_gkbprop;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Class_description_gkbprop) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_9:
		    if (level < ab_loop_bind_)
			goto end_loop_9;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_10:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_11:
		    if ( !TRUEP(marked))
			goto end_loop_10;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_11;
		  end_loop_10:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_4;
		    goto next_loop_10;
		  end_loop_11:
		  end_4:
		    level = level - (SI_Long)1L;
		    goto next_loop_9;
		  end_loop_9:;
		    resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (resulting_value);
		    else
			resulting_value = Nil;
		}
		temp_2 = TRUEP(resulting_value);
	    }
	    else
		temp_2 = TRUEP(Nil);
	    temp_1 =  !temp_2 ? T : Nil;
	    if (temp_1);
	    else {
		if (SYMBOLP(type_specification_class)) {
		    skip_list = CDR(Symbol_properties_table);
		    key_value = type_specification_class;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(type_specification_class) & 
			    IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_12:
		    if (level < ab_loop_bind_)
			goto end_loop_12;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_13:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_14:
		    if ( !TRUEP(marked))
			goto end_loop_13;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_14;
		  end_loop_13:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_5;
		    goto next_loop_13;
		  end_loop_14:
		  end_5:
		    level = level - (SI_Long)1L;
		    goto next_loop_12;
		  end_loop_12:;
		    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if ( !TRUEP(gensymed_symbol)) {
			gensymed_symbol = type_specification_class;
			temp = Symbol_properties_table;
			temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
				IFIX(Most_positive_fixnum));
			tail = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_positive_fixnum,
				Nil);
			head = 
				make_symbol_properties_hash_table_skip_list_sentinel(Most_negative_fixnum,
				tail);
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_1 = new_cons;
			}
			else
			    gensymed_symbol_1 = Nil;
			if ( !TRUEP(gensymed_symbol_1))
			    gensymed_symbol_1 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_1) = 
				Qsymbol_properties_hash_table;
			new_cons = ISVREF(Available_lookup_conses_vector,
				IFIX(Current_thread_index));
			if (new_cons) {
			    svref_arg_1 = Available_lookup_conses_vector;
			    svref_arg_2 = Current_thread_index;
			    svref_new_value = M_CDR(new_cons);
			    SVREF(svref_arg_1,svref_arg_2) = svref_new_value;
			    if ( 
				    !TRUEP(ISVREF(Available_lookup_conses_vector,
				    IFIX(Current_thread_index)))) {
				svref_arg_1 = 
					Available_lookup_conses_tail_vector;
				svref_arg_2 = Current_thread_index;
				SVREF(svref_arg_1,svref_arg_2) = Nil;
			    }
			    gensymed_symbol_2 = new_cons;
			}
			else
			    gensymed_symbol_2 = Nil;
			if ( !TRUEP(gensymed_symbol_2))
			    gensymed_symbol_2 = replenish_lookup_cons_pool();
			M_CAR(gensymed_symbol_2) = head;
			M_CDR(gensymed_symbol_2) = tail;
			inline_note_allocate_cons(gensymed_symbol_2,Qlookup);
			M_CDR(gensymed_symbol_1) = gensymed_symbol_2;
			inline_note_allocate_cons(gensymed_symbol_1,Qlookup);
			gensymed_symbol = set_skip_list_entry(temp,
				FIX((SI_Long)31L),Qeq,Nil,T,
				gensymed_symbol,temp_1,gensymed_symbol_1);
		    }
		    global_properties = gensymed_symbol;
		    skip_list = CDR(global_properties);
		    key_value = 
			    Current_kb_specific_property_list_property_name;
		    key_hash_value = 
			    SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
			    & IFIX(Most_positive_fixnum);
		    bottom_level = (SI_Long)0L;
		    marked = Nil;
		    pred = M_CAR(skip_list);
		    curr = Nil;
		    succ = Nil;
		    level = (SI_Long)31L;
		    ab_loop_bind_ = bottom_level;
		  next_loop_15:
		    if (level < ab_loop_bind_)
			goto end_loop_15;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		  next_loop_16:
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		  next_loop_17:
		    if ( !TRUEP(marked))
			goto end_loop_16;
		    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
			    (SI_Long)0L),level));
		    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		    temp = ATOMIC_REF_OBJECT(reference);
		    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ?
			     T : Nil;
		    result = VALUES_2(temp,temp_1);
		    MVS_2(result,succ,marked);
		    goto next_loop_17;
		  end_loop_16:
		    entry_hash = ISVREF(curr,(SI_Long)1L);
		    if (IFIX(entry_hash) < key_hash_value || 
			    IFIX(entry_hash) == key_hash_value &&  
			    !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			pred = curr;
			curr = succ;
		    }
		    else
			goto end_6;
		    goto next_loop_16;
		  end_loop_17:
		  end_6:
		    level = level - (SI_Long)1L;
		    goto next_loop_15;
		  end_loop_15:;
		    kb_properties = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			    key_hash_value ? (EQ(key_value,ISVREF(curr,
			    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : 
			    Nil) : Nil;
		    if (kb_properties);
		    else
			kb_properties = Nil;
		    if (kb_properties) {
			skip_list = CDR(kb_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_18:
			if (level < ab_loop_bind_)
			    goto end_loop_18;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_19:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_20:
			if ( !TRUEP(marked))
			    goto end_loop_19;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_20;
		      end_loop_19:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_7;
			goto next_loop_19;
		      end_loop_20:
		      end_7:
			level = level - (SI_Long)1L;
			goto next_loop_18;
		      end_loop_18:;
			kb_specific_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (kb_specific_value);
			else
			    kb_specific_value = No_specific_property_value;
		    }
		    else
			kb_specific_value = No_specific_property_value;
		    if ( !EQ(kb_specific_value,No_specific_property_value))
			resulting_value = kb_specific_value;
		    else {
			skip_list = CDR(global_properties);
			key_value = Class_description_gkbprop;
			key_hash_value = 
				SXHASH_SYMBOL_1(Class_description_gkbprop) 
				& IFIX(Most_positive_fixnum);
			bottom_level = (SI_Long)0L;
			marked = Nil;
			pred = M_CAR(skip_list);
			curr = Nil;
			succ = Nil;
			level = (SI_Long)31L;
			ab_loop_bind_ = bottom_level;
		      next_loop_21:
			if (level < ab_loop_bind_)
			    goto end_loop_21;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
		      next_loop_22:
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
		      next_loop_23:
			if ( !TRUEP(marked))
			    goto end_loop_22;
			curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,
				(SI_Long)0L),level));
			reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
			temp = ATOMIC_REF_OBJECT(reference);
			temp_1 = (SI_Long)355L == 
				ATOMIC_REF_STAMP(reference) ? T : Nil;
			result = VALUES_2(temp,temp_1);
			MVS_2(result,succ,marked);
			goto next_loop_23;
		      end_loop_22:
			entry_hash = ISVREF(curr,(SI_Long)1L);
			if (IFIX(entry_hash) < key_hash_value || 
				IFIX(entry_hash) == key_hash_value &&  
				!EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
			    pred = curr;
			    curr = succ;
			}
			else
			    goto end_8;
			goto next_loop_22;
		      end_loop_23:
		      end_8:
			level = level - (SI_Long)1L;
			goto next_loop_21;
		      end_loop_21:;
			resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) 
				== key_hash_value ? (EQ(key_value,
				ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
				(SI_Long)3L) : Nil) : Nil;
			if (resulting_value);
			else
			    resulting_value = Nil;
		    }
		    temp_2 = TRUEP(resulting_value);
		}
		else
		    temp_2 = TRUEP(Nil);
		temp_1 =  !temp_2 ? T : Nil;
	    }
	    if (temp_1);
	    else {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_for_instantiation,
			Class_description_gkbprop);
		temp_1 = gensymed_symbol ? 
			memq_function(type_specification_class,
			ISVREF(gensymed_symbol,(SI_Long)2L)) : Nil;
	    }
	}
	else {
	    temp_1 = EQUAL(type_specification,list_constant_18) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 = EQ(type_specification,Qitem_or_datum) ? T : Nil;
	}
    }
    else if (CONSP(initial_value) && EQ(M_CDR(initial_value),
	    Phrase_structure_marker)) {
	temp_1 = structure_type_specification_p(type_specification);
	if (temp_1);
	else
	    temp_1 = EQ(type_specification,Qdatum) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = EQ(type_specification,Qitem_or_datum) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = EQUAL(type_specification,list_constant_18) ? T : Nil;
    }
    else if (CONSP(initial_value) && EQ(M_CDR(initial_value),
	    Phrase_sequence_marker)) {
	temp_1 = sequence_type_specification_p(type_specification);
	if (temp_1);
	else
	    temp_1 = EQ(type_specification,Qdatum) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = EQ(type_specification,Qitem_or_datum) ? T : Nil;
	if (temp_1);
	else
	    temp_1 = EQUAL(type_specification,list_constant_18) ? T : Nil;
    }
    else if (EQ(type_specification,Qtruth_value))
	temp_1 = (SI_Long)-1000L <= IFIX(initial_value) ? 
		(IFIX(initial_value) <= (SI_Long)1000L ? T : Nil) : Qnil;
    else
	temp_1 = type_specification_type_p(initial_value,type_specification);
    return VALUES_1(temp_1);
}

/* CHECK-VALUE-ATTRIBUTE-INITIALIZATION-TYPE */
Object check_value_attribute_initialization_type(list_1)
    Object list_1;
{
    Object temp, attribute_name, initial_value_phrase, initial_value;
    Object attribute_definition_type, type_specification;
    Object type_matches_initial_value_p, temp_1;

    x_note_fn_call(200,98);
    temp = CAR(list_1);
    attribute_name = FIRST(temp);
    temp = CAR(list_1);
    initial_value_phrase = SECOND(temp);
    initial_value = CONSP(initial_value_phrase) &&  
	    !(CONSP(initial_value_phrase) && 
	    EQ(M_CDR(initial_value_phrase),Phrase_sequence_marker)) &&  
	    !(CONSP(initial_value_phrase) && 
	    EQ(M_CDR(initial_value_phrase),Phrase_structure_marker)) &&  
	    !TRUEP(truth_value_phrase_p(initial_value_phrase)) ? 
	    M_CAR(initial_value_phrase) : initial_value_phrase;
    attribute_definition_type = SECOND(list_1);
    type_specification = 
	    attribute_definition_type_specification(attribute_definition_type);
    if (CONSP(initial_value) && EQ(M_CDR(initial_value),
	    Phrase_structure_marker)) {
	type_matches_initial_value_p = 
		structure_type_specification_p(type_specification);
	if (type_matches_initial_value_p);
	else
	    type_matches_initial_value_p = EQ(type_specification,Qdatum) ? 
		    T : Nil;
	if (type_matches_initial_value_p);
	else
	    type_matches_initial_value_p = EQ(type_specification,
		    Qitem_or_datum) ? T : Nil;
    }
    else if (CONSP(initial_value) && EQ(M_CDR(initial_value),
	    Phrase_sequence_marker)) {
	type_matches_initial_value_p = 
		sequence_type_specification_p(type_specification);
	if (type_matches_initial_value_p);
	else
	    type_matches_initial_value_p = EQ(type_specification,Qdatum) ? 
		    T : Nil;
	if (type_matches_initial_value_p);
	else
	    type_matches_initial_value_p = EQ(type_specification,
		    Qitem_or_datum) ? T : Nil;
    }
    else if (EQ(type_specification,Qtruth_value))
	type_matches_initial_value_p = truth_value_phrase_p(initial_value);
    else
	type_matches_initial_value_p = 
		type_specification_type_p(initial_value,type_specification);
    if (type_matches_initial_value_p)
	return VALUES_1(list_1);
    else {
	temp_1 = Bad_phrase;
	temp = tformat_text_string(2,string_constant_52,attribute_name);
	return VALUES_2(temp_1,temp);
    }
}

static Object array_constant_13;   /* # */

static Object Qg2;                 /* g2 */

static Object Qzero;               /* zero */

/* ADD-INITIAL-VALUE-FOR-DECLARED-TYPE */
Object add_initial_value_for_declared_type(list_1)
    Object list_1;
{
    Object attribute_definition_type, type_specification, initial_value;
    Object amf_available_array_cons_qm, amf_array, temp, temp_1, amf_result;
    Object new_float, temp_2;

    x_note_fn_call(200,99);
    attribute_definition_type = CADR(list_1);
    type_specification = 
	    attribute_definition_type_specification(attribute_definition_type);
    if (symbolic_type_specification_p(type_specification)) {
	if (EQ(type_specification,Qtext))
	    initial_value = copy_for_phrase(array_constant_13);
	else if (EQ(type_specification,Qtruth_value))
	    initial_value = phrase_cons(Truth,Qtruth_value);
	else if (EQ(type_specification,Qsymbol))
	    initial_value = Qg2;
	else if (EQ(type_specification,Qinteger))
	    initial_value = Qzero;
	else {
	    amf_available_array_cons_qm = 
		    ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	    if (amf_available_array_cons_qm) {
		amf_array = M_CAR(amf_available_array_cons_qm);
		temp = Vector_of_simple_float_array_pools;
		temp_1 = M_CDR(amf_available_array_cons_qm);
		SVREF(temp,FIX((SI_Long)1L)) = temp_1;
		inline_note_reclaim_cons(amf_available_array_cons_qm,
			Qfloat_array);
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
	    DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	    initial_value = note_use_of_managed_float_in_phrase(new_float);
	}
    }
    else if (structure_type_specification_p(type_specification))
	initial_value = phrase_cons(Qnil,Phrase_structure_marker);
    else if (sequence_type_specification_p(type_specification))
	initial_value = phrase_cons(Qnil,Phrase_sequence_marker);
    else {
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
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,0.0);
	initial_value = note_use_of_managed_float_in_phrase(new_float);
    }
    temp_2 = CAR(list_1);
    return phrase_list_2(phrase_list_3(CAR(temp_2),initial_value,
	    attribute_definition_type),attribute_definition_type);
}

/* FIX-ATTRIBUTE-DESCRIPTION */
Object fix_attribute_description(phrase,indexed_qm)
    Object phrase, indexed_qm;
{
    Object initialization_phrase, attribute_name, initial_value;
    Object type_specification, temp, temp_1, temp_2;

    x_note_fn_call(200,100);
    initialization_phrase = CAR(phrase);
    attribute_name = CAR(initialization_phrase);
    initial_value = EQ(SECOND(initialization_phrase),Qzero) ? 
	    FIX((SI_Long)0L) : SECOND(initialization_phrase);
    type_specification = SECOND(phrase);
    if (type_specification);
    else
	type_specification = copy_list_using_phrase_conses(list_constant_18);
    temp = phrase_cons(attribute_name,Nil);
    temp_1 = phrase_cons(type_specification,Nil);
    temp_2 = fix_attribute_description_initial_value(initial_value,indexed_qm);
    return VALUES_1(nconc2(temp,nconc2(temp_1,nconc2(temp_2,indexed_qm ? 
	    phrase_cons(phrase_cons(Qindexed,Nil),Nil) : Nil))));
}

static Object list_constant_19;    /* # */

static Object list_constant_20;    /* # */

static Object Qinstantiate_object_in_attribute;  /* instantiate-object-in-attribute */

/* FIX-ATTRIBUTE-DESCRIPTION-INITIAL-VALUE */
Object fix_attribute_description_initial_value(initial_value,indexed_qm)
    Object initial_value, indexed_qm;
{
    Object temp;
    char temp_1;

    x_note_fn_call(200,101);
    if (truth_value_phrase_p(initial_value))
	temp = phrase_list_2(CAR(initial_value),Qtruth_value);
    else if (phrase_number_p(initial_value))
	temp = phrase_list_2(initial_value,Qnumber);
    else if ( !TRUEP(initial_value))
	temp = indexed_qm ? phrase_list_2(Nil,Nil) : Nil;
    else if (SYMBOLP(initial_value))
	temp = phrase_list_2(initial_value,Qsymbol);
    else if (text_string_p(initial_value))
	temp = phrase_list_2(initial_value,Qtext);
    else {
	if (CONSP(initial_value) && phrase_number_p(CAR(initial_value))) {
	    temp = CDR(initial_value);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = phrase_list_2(CAR(initial_value),CDR(initial_value));
	else if (CONSP(initial_value) && EQ(M_CDR(initial_value),
		Phrase_sequence_marker))
	    temp = phrase_list_2(initial_value,
		    copy_for_phrase(list_constant_19));
	else if (CONSP(initial_value) && EQ(M_CDR(initial_value),
		Phrase_structure_marker))
	    temp = phrase_list_2(initial_value,
		    copy_for_phrase(list_constant_20));
	else {
	    if (CONSP(initial_value) && EQ(CAR(initial_value),Kfuncall)) {
		temp = CDR(initial_value);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ? EQ(CADR(initial_value),
		    Qinstantiate_object_in_attribute) || 
		    EQ(CADR(initial_value),Qinstantiate_variable) : 
			TRUEP(Nil)) {
		temp = CDDR(initial_value);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ?  !TRUEP(CDDDR(initial_value)) : TRUEP(Nil))
		temp = phrase_list_2(initial_value,CADDR(initial_value));
	    else if (LISTP(initial_value) && EQ(Qtruth_value,
		    CADR(initial_value)))
		temp = initial_value;
	    else
		temp = Qnil;
	}
    }
    return VALUES_1(temp);
}

/* COMPILE-SYMBOLIC-VALUE-LIST-FOR-SLOT */
Object compile_symbolic_value_list_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(200,102);
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
    return fix_up_symbolic_value_list(parse_result);
}

/* FIX-UP-SYMBOLIC-VALUE-LIST */
Object fix_up_symbolic_value_list(symbolic_value_list)
    Object symbolic_value_list;
{
    x_note_fn_call(200,103);
    if ( !TRUEP(symbolic_value_list))
	return VALUES_1(Nil);
    else if (EQ(symbolic_value_list,Qnone))
	return VALUES_1(Nil);
    else if (EQ(CAR(symbolic_value_list),Qcm))
	return VALUES_1(CDR(symbolic_value_list));
    else
	return phrase_cons(symbolic_value_list,Nil);
}

/* VARIABLE-SPEC-TRANSFORM */
Object variable_spec_transform(variable_specification_list)
    Object variable_specification_list;
{
    Object result_1, spec_list, name, value, ab_loop_list_, ab_loop_desetq_;
    Object temp;

    x_note_fn_call(200,104);
    result_1 = Nil;
    spec_list = CDR(variable_specification_list);
    name = Nil;
    value = Nil;
    ab_loop_list_ = spec_list;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    name = CAR(ab_loop_desetq_);
    temp = CDR(ab_loop_desetq_);
    value = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    result_1 = phrase_cons(name,result_1);
    result_1 = phrase_cons(value,result_1);
    goto next_loop;
  end_loop:
    return nreverse(result_1);
    return VALUES_1(Qnil);
}

void grammar6a_INIT()
{
    Object connection_instance_style_evaluation_setter_1;
    Object connection_instance_style_evaluation_getter_1;
    Object connection_line_pattern_evaluation_setter_1;
    Object connection_line_pattern_evaluation_getter_1;
    Object connection_arrows_evaluation_setter_1;
    Object connection_arrows_evaluation_getter_1;
    Object simulation_frame_qm_evaluation_getter_1;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qsymbolic_value_list, Qslot_value_compiler;
    Object Qcompile_symbolic_value_list_for_slot, AB_package;
    Object Qfix_attribute_description, Qadd_initial_value_for_declared_type;
    Object list_constant_23, Qcheck_value_attribute_initialization_type;
    Object list_constant_24, Qab_or, Qattribute_descriptions;
    Object Qcompile_attribute_descriptions_for_slot, Qmemq_3_cdr_cddddr;
    Object Qmemq_3_cddddr, Qmemq_2_cddddr, Qmemq_2_cdddr;
    Object Qcut_out_sixth_element, Qcut_out_fifth_element;
    Object Qcut_out_fourth_element, Qslot_value_writer;
    Object Qwrite_symbol_from_slot, Qobject_name, Qconnection_class;
    Object Qnew_class, Qsimulation_subtable_class, Qjunction_class;
    Object Qobject_class, Qmessage_class, Qitem_class, string_constant_305;
    Object string_constant_304, string_constant_303, Qlist_of_classes;
    Object Qcompile_list_of_classes_for_slot, Qlist_of_message_classes;
    Object Qcompile_list_of_message_classes_for_slot;
    Object Qlist_of_connection_classes;
    Object Qcompile_list_of_connection_classes_for_slot;
    Object Qlist_of_object_classes, Qcompile_list_of_object_classes_for_slot;
    Object Qlist_of_item_classes, Qcompile_list_of_item_classes_for_slot;
    Object Qold_attribute_descriptions;
    Object Qcompile_old_attribute_descriptions_for_slot, string_constant_302;
    Object string_constant_301, string_constant_300, string_constant_299;
    Object string_constant_298, string_constant_297, string_constant_296;
    Object string_constant_295, string_constant_294, string_constant_293;
    Object string_constant_292, string_constant_291, string_constant_290;
    Object string_constant_289, string_constant_288, string_constant_287;
    Object string_constant_286, string_constant_285, Qcheck_range_of_element;
    Object Qfix_old_attribute_description, Qsimplify_associative_operation;
    Object Qfalse, Qwrite_old_attribute_descriptions_from_slot, Qslot_putter;
    Object Qput_attributes_specific_to_class, Qattributes_specific_to_class;
    Object Qwrite_old_superior_class_from_slot, Qold_superior_class;
    Object Qgfi_output_interface, Qgfi_input_interface;
    Object Qg2_to_g2_data_interface, Qgsi_interface;
    Object Qcompile_old_superior_class_for_slot, Qput_superior_class;
    Object Qsuperior_class, string_constant_284;
    Object Qwrite_old_default_settings_from_slot, Qold_default_settings;
    Object Qput_default_settings, Qdefault_settings;
    Object Qcompile_old_default_settings_for_slot, string_constant_283;
    Object string_constant_282, string_constant_281, string_constant_280;
    Object string_constant_279, string_constant_278, string_constant_277;
    Object string_constant_276, string_constant_275, string_constant_274;
    Object string_constant_273, string_constant_272, string_constant_271;
    Object string_constant_270, string_constant_269, string_constant_268;
    Object string_constant_267, string_constant_266, string_constant_265;
    Object string_constant_264, Qsecond_none;
    Object Qmake_simulation_subtable_and_install, Qprevious_capabilities;
    Object Qcompile_previous_capabilities_for_slot;
    Object Qwrite_previous_capabilities_from_slot, Qg2_meter_data_service;
    Object Qg2_to_g2_data_service, Qgfi_data_service, Qgsi_message_service;
    Object Qgsi_data_service, Qput_capabilities_and_restrictions;
    Object Qcapabilities_and_restrictions, string_constant_263;
    Object string_constant_262, string_constant_261;
    Object Qwrite_list_of_slots_from_slot, Qlist_of_slots;
    Object Qwrite_class_inheritance_path_of_definition_from_slot;
    Object Qclass_inheritance_path_of_definition;
    Object Qwrite_list_of_message_classes_from_slot;
    Object Qwrite_list_of_connection_classes_from_slot;
    Object Qwrite_list_of_object_classes_from_slot;
    Object Qwrite_list_of_item_classes_from_slot;
    Object Qwrite_list_of_classes_from_slot, Qfoundation_message_class;
    Object Qfoundation_connection_class, Qfoundation_object_class;
    Object list_constant_55, Qcompile_class_for_slot, list_constant_54;
    Object list_constant_53, Qcompile_message_class_for_slot;
    Object Qcompile_object_class_for_slot, Qcompile_connection_class_for_slot;
    Object Qcompile_item_class_for_slot, Qcompile_new_class_for_slot;
    Object Qgrammar6a, Qrecursive_attribute_nesting_has_occurred_qm;
    Object Qmake_simulation_subtable_with_specific_class_and_install;
    Object Qsimulation_frame_qm, list_constant_52;
    Object Qtype_specification_simple_expansion, string_constant_260;
    Object string_constant_259, string_constant_258, string_constant_257;
    Object string_constant_256, string_constant_255, string_constant_254;
    Object string_constant_253, string_constant_252, string_constant_251;
    Object string_constant_250, string_constant_249, string_constant_248;
    Object string_constant_247, string_constant_246, string_constant_245;
    Object string_constant_244, string_constant_243, string_constant_242;
    Object string_constant_241, string_constant_240, string_constant_239;
    Object string_constant_238, string_constant_237, string_constant_236;
    Object string_constant_235, string_constant_234, string_constant_233;
    Object string_constant_232, string_constant_231, string_constant_230;
    Object string_constant_229, string_constant_228, string_constant_227;
    Object string_constant_226, string_constant_225, string_constant_224;
    Object string_constant_223, string_constant_222, string_constant_221;
    Object string_constant_220, string_constant_219, string_constant_218;
    Object string_constant_217, string_constant_216, string_constant_215;
    Object string_constant_214, string_constant_213, string_constant_212;
    Object string_constant_211, string_constant_210, string_constant_209;
    Object string_constant_208, string_constant_207, string_constant_206;
    Object string_constant_205, string_constant_204, string_constant_203;
    Object string_constant_202, string_constant_201, string_constant_200;
    Object string_constant_199, string_constant_198, string_constant_197;
    Object string_constant_196, string_constant_195, string_constant_194;
    Object string_constant_193, string_constant_192, string_constant_191;
    Object string_constant_190, string_constant_189, string_constant_188;
    Object string_constant_187, Qfix_default_override_on_user_defined_slot;
    Object string_constant_186, string_constant_185, string_constant_184;
    Object string_constant_183, string_constant_182, string_constant_181;
    Object string_constant_180, string_constant_179, string_constant_178;
    Object string_constant_177, string_constant_176, string_constant_175;
    Object string_constant_174, string_constant_173, string_constant_172;
    Object string_constant_171, string_constant_170, string_constant_169;
    Object string_constant_168, string_constant_167, string_constant_166;
    Object string_constant_165, string_constant_164, string_constant_163;
    Object string_constant_162, string_constant_161, string_constant_160;
    Object string_constant_159, string_constant_158, string_constant_157;
    Object string_constant_156, string_constant_155, string_constant_154;
    Object string_constant_153, string_constant_152, string_constant_151;
    Object string_constant_150, string_constant_149, string_constant_148;
    Object string_constant_147, string_constant_146, string_constant_145;
    Object string_constant_144, string_constant_143, string_constant_142;
    Object string_constant_141, string_constant_140, string_constant_139;
    Object string_constant_138, string_constant_137, string_constant_136;
    Object string_constant_135, string_constant_134, string_constant_133;
    Object string_constant_132, string_constant_131, string_constant_130;
    Object string_constant_129, Qunreserved_symbol, list_constant_51;
    Object Qdefaulted_attribute_name, Qg2_array_initial_values;
    Object Qg2_array_length, Qg2_array_element_type, Qsimulation_details;
    Object Qlist_type, Qallow_duplicate_elements, Qinitial_value;
    Object Qhistory_keeping_spec, Qdefault_update_interval, Qvalidity_interval;
    Object Qdata_server, Qdata_type, Qnamed, list_constant_50;
    Object list_constant_49, list_constant_48, list_constant_47;
    Object list_constant_46, list_constant_45, list_constant_44;
    Object list_constant_43, list_constant_42, list_constant_41;
    Object list_constant_40, list_constant_39, list_constant_38;
    Object list_constant_37, list_constant_36, list_constant_35, Qdiamond;
    Object Qtriangle, Qarrow, list_constant_34, list_constant_33;
    Object float_constant_5, float_constant_4, float_constant_3;
    Object float_constant_2, Qput_connection_arrows;
    Object Qwrite_connection_arrows_from_slot;
    Object Qcompile_connection_arrows_for_slot, string_constant_128;
    Object Qflatten_phrase_tree, string_constant_127, string_constant_126;
    Object string_constant_125, string_constant_124, Qend, string_constant_123;
    Object string_constant_122, string_constant_121, string_constant_120;
    Object Qconnection_line_pattern, list_constant_32, list_constant_26;
    Object list_constant_31, list_constant_30, list_constant_29;
    Object list_constant_28, list_constant_27, list_constant_22;
    Object list_constant_25, Qno_item, Qput_line_pattern;
    Object Qwrite_connection_line_pattern_from_slot;
    Object Qcompile_connection_line_pattern_for_slot, list_constant_21;
    Object string_constant_119, string_constant_118, string_constant_117;
    Object string_constant_116, string_constant_115, string_constant_114;
    Object Qcross_section_pattern, Qcompile_cross_section_pattern_for_slot;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qstub_length;
    Object Qcompile_stub_length_for_slot, Qwrite_stub_length_from_slot;
    Object Qwrite_cross_section_pattern_from_slot;
    Object Qwrite_connection_instance_style_from_slot;
    Object Qconnection_instance_style, Qdiagonal;
    Object Qfix_connection_style_stub_spec, Qfix_connection_arrows_stub_spec;
    Object Qfix_connection_line_pattern_stub_spec, Qfix_stub_info;
    Object string_constant_113, string_constant_112, string_constant_111;
    Object string_constant_110, string_constant_109, string_constant_108;
    Object string_constant_107, string_constant_106, string_constant_105;
    Object string_constant_104, string_constant_103, string_constant_102;
    Object string_constant_101, string_constant_100, string_constant_99;
    Object string_constant_98, string_constant_97, string_constant_96;
    Object string_constant_95, string_constant_94, string_constant_93;
    Object string_constant_92, string_constant_91, string_constant_90;
    Object string_constant_89, string_constant_88, string_constant_87;
    Object string_constant_86, string_constant_85, string_constant_84;
    Object string_constant_83, string_constant_82, string_constant_81;
    Object string_constant_80, string_constant_79, string_constant_78;
    Object string_constant_77, string_constant_76, string_constant_75;
    Object string_constant_74, string_constant_73, string_constant_72;
    Object string_constant_71, string_constant_70, string_constant_69;
    Object string_constant_68, string_constant_67, string_constant_66;
    Object string_constant_65, string_constant_64, string_constant_63;
    Object string_constant_62, string_constant_61, string_constant_60;

    x_note_fn_call(200,105);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    Qcheck_value_attribute_initialization_type = 
	    STATIC_SYMBOL("CHECK-VALUE-ATTRIBUTE-INITIALIZATION-TYPE",
	    AB_package);
    Qfix_attribute_description = STATIC_SYMBOL("FIX-ATTRIBUTE-DESCRIPTION",
	    AB_package);
    Qadd_initial_value_for_declared_type = 
	    STATIC_SYMBOL("ADD-INITIAL-VALUE-FOR-DECLARED-TYPE",AB_package);
    Qinstantiate_variable = STATIC_SYMBOL("INSTANTIATE-VARIABLE",AB_package);
    Qinstantiate_object_in_attribute = 
	    STATIC_SYMBOL("INSTANTIATE-OBJECT-IN-ATTRIBUTE",AB_package);
    Qmemq_3_cddddr = STATIC_SYMBOL("MEMQ-3-CDDDDR",AB_package);
    Qcut_out_fifth_element = STATIC_SYMBOL("CUT-OUT-FIFTH-ELEMENT",AB_package);
    Qmemq_3_cdr_cddddr = STATIC_SYMBOL("MEMQ-3-CDR-CDDDDR",AB_package);
    Qcut_out_sixth_element = STATIC_SYMBOL("CUT-OUT-SIXTH-ELEMENT",AB_package);
    string_constant_60 = 
	    STATIC_STRING("13my1m83=Zy1m9k83=Yy1m83=Zy1m9k83=ay1m83Ajy1m9k83Zy1m83Ajy83-K*y1m83-K*y83-K-y1o83-K*y1n83-K-y1m9k83-Zy83-K*y1nmln9l1n83-K-y83*m");
    string_constant_61 = 
	    STATIC_STRING("y1ml1n83=Uy83=Ky1l83l5y1p83-K-y1s83*my1m9k83*Iy83=Zy83pry1m9k83vy1m9k8396y1m9k83*Iy837ky1m1nlsoo9m1m9n01p83-K-y1o83*my1m9k83*Iy8");
    string_constant_62 = 
	    STATIC_STRING("3=Zy83pry1m1mloo9o1m9n01o83-K-y1o83*my1m9k8396y1m9k83*Iy837ky1l1mlo1m9n01n83-K-y1x83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k");
    string_constant_63 = 
	    STATIC_STRING("83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1ol1m83-Gyq1n83*Ay9pxx1n83-K-y1v83*my1m9k83*Iy83=Zy83psy1m9k83vy1m9k8396y1m9k8");
    string_constant_64 = 
	    STATIC_STRING("3*Iy1m9k8344y1m9k83*ty83=Zy837dy1ol83=Ky1n83*Ay9pvv1n83-K-y1q83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1ol1m83-Gyq1n83*Ay9pqq1n8");
    string_constant_65 = 
	    STATIC_STRING("3-K-y1r83*my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1ol1n83=Uy83=Ky1l83l5y1n83*Ay9prr1n83-K-y1z83*my1m9k83*Iy1m9k83=ay1m9k");
    string_constant_66 = 
	    STATIC_STRING("831Ly1m9k83-Ty83=Zy832Cy1m9k83vy1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1ol1m83-Gyr1n83*Ay9qzz1n83-K-y1w83*my1m9k");
    string_constant_67 = 
	    STATIC_STRING("83*Iy83=Zy83psy1m9k83vy1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1ol83=Ky1n83*Ay9qww1n83-K-y1r83*my1m9k83*Iy1m9k83=");
    string_constant_68 = 
	    STATIC_STRING("ay1m9k831Ly1m9k83-Ty83=Zy832Cy1ol1m83-Gyr1n83*Ay9qrr1n83-K-y1s83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1ol1n8");
    string_constant_69 = 
	    STATIC_STRING("3=Uy83=Ky1l83l5y1n83*Ay9qss1n83-rZy1m9k83-2y83-2y1n83-rZy1m9k83*ly83=oy1o83-K-y1y83*my1m9k83*Iy1m9k83=Yy83-rZy1m9k83vy1m9k831by1");
    string_constant_70 = 
	    STATIC_STRING("m9k9r83nYy1m9k83=Uy83nYy1m9k83vy1m9k8396y1m9k83*Iy83nYy1qloy83-2ysu9s1n83-K-y1q83*my1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1ql1n83=Uy");
    string_constant_71 = 
	    STATIC_STRING("83=Ky1l83l5y083-2yoq1o83-K-y1u83*my1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1m9k83vy1m9k8396y1m9k83*Iy83nYy1ql1n83=Uy83=Ky1l83l5yu83-2y");
    string_constant_72 = 
	    STATIC_STRING("oq9s1p83-K-y1w83*my1m9k83*Iy1m9k83=Yy83-rZy1m9k83vy1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy83nYy2olow83-2ys9s9t1o83-K-y1o8");
    string_constant_73 = 
	    STATIC_STRING("3*my1m9k831by1m9k9r83nZy2ol1n83=Uy83=Ky1l83l5y083-2yo9t1p83-K-y1s83*my1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy83nYy2ol1n83");
    string_constant_74 = 
	    STATIC_STRING("=Uy83=Ky1l83l5ys83-2yo9s9t1n83-K-y13Fy83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1m9k83");
    string_constant_75 = 
	    STATIC_STRING("vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1ql1m83-Gyq1n83*Ay9p3Fy3Fyuw1n83-K-y1x83*my1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1m9");
    string_constant_76 = 
	    STATIC_STRING("k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1ql1n83=Uy83=Ky1l83l5y1n83*Ay9pxxoq1o83-K-y13Dy83*my1m9k83*Iy1m9k8344y1m9k83*");
    string_constant_77 = 
	    STATIC_STRING("ty83=Zy837dy1m9k83vy1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy2ol1m83-Gyq1n83*Ay9p3Dy3Dyu9t1o83-");
    string_constant_78 = 
	    STATIC_STRING("K-y1v83*my1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy2ol1n83=Uy83=Ky1l83l5y1n83*Ay9pvvo9t1n83-K-y");
    string_constant_79 = 
	    STATIC_STRING("1p83*my1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1pl1n83=Uy83=Ky1l83l5y001l83-=Ry1p83-K-y1w83*my1m9k83*Iy83=Zy83pry1m9k83vy1m9k8396y1m");
    string_constant_80 = 
	    STATIC_STRING("9k83*Iy837ky1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1m1nlsoo9m1m9n8k1p83-K-y1s83*my1m9k83*Iy83=Zy83pry1m9k83vy1m9k83=Fy1m9k83=ay1m9k");
    string_constant_81 = 
	    STATIC_STRING("83-=Oy1m1mloo9o1m9n8k1o83-K-y1s83*my1m9k8396y1m9k83*Iy837ky1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1l1mlo1m9n8k1n83-K-y13Dy83*my1m9k");
    string_constant_82 = 
	    STATIC_STRING("83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1pl1m");
    string_constant_83 = 
	    STATIC_STRING("83-Gyq1n83*Ay9pxx1l83-=Ry1n83-K-y1z83*my1m9k83*Iy83=Zy83psy1m9k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=");
    string_constant_84 = 
	    STATIC_STRING("Fy1m9k83=ay1m9k83-=Oy1pl83=Ky1n83*Ay9pvv1l83-=Ry1n83-K-y1u83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m");
    string_constant_85 = 
	    STATIC_STRING("9k83-=Oy1pl1m83-Gyq1n83*Ay9pqq1l83-=Ry1n83-K-y1v83*my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m9");
    string_constant_86 = 
	    STATIC_STRING("k83-=Oy1pl1n83=Uy83=Ky1l83l5y1n83*Ay9prr1l83-=Ry1n83-K-y13Fy83*my1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1m9k83vy1m9k8396y");
    string_constant_87 = 
	    STATIC_STRING("1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1pl1m83-Gyr1n83*Ay9qzz1l83-=Ry1n83-K-y13Cy83*m");
    string_constant_88 = 
	    STATIC_STRING("y1m9k83*Iy83=Zy83psy1m9k83vy1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1pl83=Ky1");
    string_constant_89 = 
	    STATIC_STRING("n83*Ay9qww1l83-=Ry1n83-K-y1v83*my1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1pl1m83-Gyr1n");
    string_constant_90 = 
	    STATIC_STRING("83*Ay9qrr1l83-=Ry1n83-K-y1w83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1pl1n");
    string_constant_91 = 
	    STATIC_STRING("83=Uy83=Ky1l83l5y1n83*Ay9qss1l83-=Ry1o83-K-y13Ey83*my1m9k83*Iy1m9k83=Yy1m9k83-2y1m9k83vy1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1m9k83");
    string_constant_92 = 
	    STATIC_STRING("vy1m9k8396y1m9k83*Iy83nYy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1rl83-2yy83-2y1l83-=Rysu9u1n83-K-y1u83*my1m9k831by1m9k9r83nYy1m9k83");
    string_constant_93 = 
	    STATIC_STRING("=Uy83nYy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1rl1n83=Uy83=Ky1l83l5y083-2y1l83-=Ryoq1o83-K-y1y83*my1m9k831by1m9k9r83nYy1m9k83=Uy83");
    string_constant_94 = 
	    STATIC_STRING("nYy1m9k83vy1m9k8396y1m9k83*Iy83nYy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1rl1n83=Uy83=Ky1l83l5yu83-2y1l83-=Ryoq9u1p83-K-y13Cy83*my1");
    string_constant_95 = 
	    STATIC_STRING("m9k83*Iy1m9k83=Yy1m9k83-2y1m9k83vy1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy83nYy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2pl83-2");
    string_constant_96 = 
	    STATIC_STRING("yw83-2y1l83-=Rys9u9v1o83-K-y1s83*my1m9k831by1m9k9r83nZy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2pl1n83=Uy83=Ky1l83l5y083-2y1l83-=Ryo");
    string_constant_97 = 
	    STATIC_STRING("9v1p83-K-y1w83*my1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy83nYy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2pl1n83=Uy83=Ky1l83l5ys8");
    string_constant_98 = 
	    STATIC_STRING("3-2y1l83-=Ryo9s9v1n83-K-y13Jy83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1m9k83vy1m9k839");
    string_constant_99 = 
	    STATIC_STRING("6y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1rl1m83-Gyq1n83*Ay9p3Fy3Fy1l83-=Ryuw1n83-K-y13Dy83*my");
    string_constant_100 = 
	    STATIC_STRING("1m9k831by1m9k9r83nYy1m9k83=Uy83nYy1m9k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1rl1");
    string_constant_101 = 
	    STATIC_STRING("n83=Uy83=Ky1l83l5y1n83*Ay9pxx1l83-=Ryoq1o83-K-y13Hy83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k831by1m9k9r83nZy1m9k83v");
    string_constant_102 = 
	    STATIC_STRING("y1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2pl1m83-Gyq1n83*Ay9p3Dy3Dy1l83-=Ryu9v1o83-K-y");
    string_constant_103 = 
	    STATIC_STRING("1z83*my1m9k831by1m9k9r83nZy1m9k83vy1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2pl1n83=Uy8");
    string_constant_104 = STATIC_STRING("3=Ky1l83l5y1n83*Ay9pvv1l83-=Ryo9v");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qcheck_value_attribute_initialization_type);
    push_optimized_constant(Qfix_attribute_description);
    push_optimized_constant(Qadd_initial_value_for_declared_type);
    push_optimized_constant(Qinstantiate_variable);
    push_optimized_constant(Qinstantiate_object_in_attribute);
    push_optimized_constant(Qvalues);
    push_optimized_constant(Qmemq_3_cddddr);
    push_optimized_constant(Qcut_out_fifth_element);
    push_optimized_constant(Qmemq_3_cdr_cddddr);
    push_optimized_constant(Qcut_out_sixth_element);
    add_grammar_rules_function(regenerate_optimized_constant(list(45,
	    string_constant_60,string_constant_61,string_constant_62,
	    string_constant_63,string_constant_64,string_constant_65,
	    string_constant_66,string_constant_67,string_constant_68,
	    string_constant_69,string_constant_70,string_constant_71,
	    string_constant_72,string_constant_73,string_constant_74,
	    string_constant_75,string_constant_76,string_constant_77,
	    string_constant_78,string_constant_79,string_constant_80,
	    string_constant_81,string_constant_82,string_constant_83,
	    string_constant_84,string_constant_85,string_constant_86,
	    string_constant_87,string_constant_88,string_constant_89,
	    string_constant_90,string_constant_91,string_constant_92,
	    string_constant_93,string_constant_94,string_constant_95,
	    string_constant_96,string_constant_97,string_constant_98,
	    string_constant_99,string_constant_100,string_constant_101,
	    string_constant_102,string_constant_103,string_constant_104)));
    Qfix_stub_info = STATIC_SYMBOL("FIX-STUB-INFO",AB_package);
    Qfix_connection_style_stub_spec = 
	    STATIC_SYMBOL("FIX-CONNECTION-STYLE-STUB-SPEC",AB_package);
    Qconnection_line_pattern = STATIC_SYMBOL("CONNECTION-LINE-PATTERN",
	    AB_package);
    Qfix_connection_line_pattern_stub_spec = 
	    STATIC_SYMBOL("FIX-CONNECTION-LINE-PATTERN-STUB-SPEC",AB_package);
    Qfix_connection_arrows_stub_spec = 
	    STATIC_SYMBOL("FIX-CONNECTION-ARROWS-STUB-SPEC",AB_package);
    string_constant_105 = 
	    STATIC_STRING("13Vy1m83nYy83-2y1o83nZy1n83nYy1m9k83vy83-rdy1n83=Uyln9l1n83-rdy1o83nYy1m9k83vy1m9k83=Uy83nYy1n83=Uylo1o83-rdy1n83nYy1m9k83vy83-r");
    string_constant_106 = 
	    STATIC_STRING("dy1n83=Uyln9l1m8381y1m9k83Zy1m8381y1m9k83S6y1m8381y83-OAy1o83-OAy1n83-Duy1m9k83-Zy83-OAy1nmln9l1m83-OAy83-Duy1o83-Duy83-rHy1ml09");
    string_constant_107 = 
	    STATIC_STRING("m1o83-Duy1m83-rHy83-O6y1mlm9m1o83-Duy1m83-rHy83-O1y1nl0m9m1o83-Duy1o83-rHy83-O6y1m9k83-ty83-O1y1nlmo9m1o83-Duy1m83-rHy83-Nsy1ol0");
    string_constant_108 = 
	    STATIC_STRING("0m9m1o83-Duy1o83-rHy83-O6y1m9k83-ty83-Nsy1olm0o9m1o83-Duy1o83-rHy83-O1y1m9k83-ty83-Nsy1ol0mo9m1o83-Duy1q83-rHy83-O6y1m9k83-ty83-");
    string_constant_109 = 
	    STATIC_STRING("O1y1m9k83-ty83-Nsy1olmoq9m1n83-rHy1r83=Zy83BOy839jy1m9k83-2Ty1m9k83=Gy83gsy83Sy1pnm0qr1n83-rHy1q83=Zy83BOy1m9k83-2Ty1m9k83=Gy83g");
    string_constant_110 = 
	    STATIC_STRING("sy83Sy1p0m0pq1n83-rHy1s83=Zy83gjy83BOy839jy1m9k83-2Ty1m9k83=Gy83gsy83Sy1ponmrs1n83-rHy1r83=Zy83gjy83BOy1m9k83-2Ty1m9k83=Gy83gsy8");
    string_constant_111 = 
	    STATIC_STRING("3Sy1p0nmqr1o83-O6y1n1m9k83=Fy1m9k83-Dvy8380yn9n1o83-O1y1n1m9k83=Fy1m9k839Iy9on9p1o83-Nsy1n1m9k83=Fy1m9k838-y838-yn9q1m839jy83-6y");
    string_constant_112 = 
	    STATIC_STRING("1m83BOy83-6y1m83gjy1m9k83dy1m83gjy1m9k83py1m83v7y83gjy1m83v7y1m9k83Zy1m83gsy1m9k83hy1m83gsy1m9k83gy1m83gsy1m9k83-by1m83gsy1m9k83");
    string_constant_113 = STATIC_STRING("*hy1m83BPy8380y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_stub_info);
    push_optimized_constant(Qfix_connection_style_stub_spec);
    push_optimized_constant(Qconnection_line_pattern);
    push_optimized_constant(Qfix_connection_line_pattern_stub_spec);
    push_optimized_constant(Qfix_connection_arrows_stub_spec);
    add_grammar_rules_function(regenerate_optimized_constant(list(9,
	    string_constant_105,string_constant_106,string_constant_107,
	    string_constant_108,string_constant_109,string_constant_110,
	    string_constant_111,string_constant_112,string_constant_113)));
    SET_SYMBOL_FUNCTION(Qfix_stub_info,STATIC_FUNCTION(fix_stub_info,NIL,
	    FALSE,1,1));
    Qsolid = STATIC_SYMBOL("SOLID",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_connection_line_pattern_stub_spec,
	    STATIC_FUNCTION(fix_connection_line_pattern_stub_spec,NIL,
	    FALSE,1,1));
    Qdefault = STATIC_SYMBOL("DEFAULT",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_connection_arrows_stub_spec,
	    STATIC_FUNCTION(fix_connection_arrows_stub_spec,NIL,FALSE,1,1));
    Qorthogonal = STATIC_SYMBOL("ORTHOGONAL",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_connection_style_stub_spec,
	    STATIC_FUNCTION(fix_connection_style_stub_spec,NIL,FALSE,1,1));
    Qconnection_instance_style = STATIC_SYMBOL("CONNECTION-INSTANCE-STYLE",
	    AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qconnection_instance_style),
	    Qtype_specification_simple_expansion,Qnil);
    Qdiagonal = STATIC_SYMBOL("DIAGONAL",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qmember,Qorthogonal,Qdiagonal);
    define_type_specification_explicit_complex_type(Qconnection_instance_style,
	    list_constant_1);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qnamed,Qconnection_instance_style);
    connection_instance_style_evaluation_setter_1 = 
	    STATIC_FUNCTION(connection_instance_style_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconnection_instance_style,
	    connection_instance_style_evaluation_setter_1);
    connection_instance_style_evaluation_getter_1 = 
	    STATIC_FUNCTION(connection_instance_style_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconnection_instance_style,
	    connection_instance_style_evaluation_getter_1);
    Qwrite_connection_instance_style_from_slot = 
	    STATIC_SYMBOL("WRITE-CONNECTION-INSTANCE-STYLE-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_connection_instance_style_from_slot,
	    STATIC_FUNCTION(write_connection_instance_style_from_slot,NIL,
	    FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qconnection_instance_style,
	    SYMBOL_FUNCTION(Qwrite_connection_instance_style_from_slot),
	    Qslot_value_writer);
    string_constant = STATIC_STRING("inherited");
    string_constant_1 = STATIC_STRING(", ");
    Qcross_section_pattern = STATIC_SYMBOL("CROSS-SECTION-PATTERN",AB_package);
    Qwrite_cross_section_pattern_from_slot = 
	    STATIC_SYMBOL("WRITE-CROSS-SECTION-PATTERN-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_cross_section_pattern_from_slot,
	    STATIC_FUNCTION(write_cross_section_pattern_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qcross_section_pattern,
	    SYMBOL_FUNCTION(Qwrite_cross_section_pattern_from_slot),
	    Qslot_value_writer);
    string_constant_2 = STATIC_STRING("~(~a ~a~)");
    Qstub_length = STATIC_SYMBOL("STUB-LENGTH",AB_package);
    Qwrite_stub_length_from_slot = 
	    STATIC_SYMBOL("WRITE-STUB-LENGTH-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_stub_length_from_slot,
	    STATIC_FUNCTION(write_stub_length_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qstub_length,
	    SYMBOL_FUNCTION(Qwrite_stub_length_from_slot),Qslot_value_writer);
    Qinherited = STATIC_SYMBOL("INHERITED",AB_package);
    Qcompile_stub_length_for_slot = 
	    STATIC_SYMBOL("COMPILE-STUB-LENGTH-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_stub_length_for_slot,
	    STATIC_FUNCTION(compile_stub_length_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qstub_length,
	    SYMBOL_FUNCTION(Qcompile_stub_length_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qstub_length,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    Qcopy = STATIC_SYMBOL("COPY",AB_package);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcompile_cross_section_pattern_for_slot = 
	    STATIC_SYMBOL("COMPILE-CROSS-SECTION-PATTERN-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_cross_section_pattern_for_slot,
	    STATIC_FUNCTION(compile_cross_section_pattern_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qcross_section_pattern,
	    SYMBOL_FUNCTION(Qcompile_cross_section_pattern_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qcross_section_pattern,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcm = STATIC_SYMBOL(",",AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    string_constant_114 = 
	    STATIC_STRING("1o1n9k1m9l83-DOy01m9k83suy1m9k83swy1n9k1r83swy1m9l83vy1m9l9m1m9l83-CJy1m9l83*ty1m9l83kUy1m9l83*4y2l83-J=yl");
    clear_optimized_constants();
    push_optimized_constant(Qconnection_line_pattern);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_114));
    string_constant_115 = 
	    STATIC_STRING("1m1n83suy83gCy1ll1n83suy1n83gCy1m9k83vy83suy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_115));
    string_constant_116 = 
	    STATIC_STRING("1q1m83gCy1m9k83-Pky1m83gCy1m9k83vHy1n83gCy1m1m9k83=By1m9k83-Pky83-dIy1n83gCy1m1m9k83-oay1m9k83-Pky834cy1n83gCy1m1m9k83-Moy1m9k83");
    string_constant_117 = 
	    STATIC_STRING("vHy83-Mpy1n83gCy1m1m9k83-U3y1m9k83vHy83-U4y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_116,
	    string_constant_117)));
    Qflatten_phrase_tree = STATIC_SYMBOL("FLATTEN-PHRASE-TREE",AB_package);
    string_constant_118 = 
	    STATIC_STRING("1m1m83swy83svy1o83swy1n83svy1m9k83vy83swy2lln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qflatten_phrase_tree);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_118));
    string_constant_119 = 
	    STATIC_STRING("1l1n83svy1p83Sy1m9k830Py1m9k83vy83Sy1m9k83-8-y1mlo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_119));
    SET_SYMBOL_FUNCTION(Qflatten_phrase_tree,
	    STATIC_FUNCTION(flatten_phrase_tree,NIL,FALSE,1,1));
    Qdash = STATIC_SYMBOL("DASH",AB_package);
    list_constant_21 = STATIC_CONS(FIX((SI_Long)2L),Qnil);
    list_constant_2 = STATIC_CONS(FIX((SI_Long)5L),list_constant_21);
    Qab_dot = STATIC_SYMBOL("DOT",AB_package);
    list_constant_3 = STATIC_CONS(FIX((SI_Long)1L),list_constant_21);
    Qlong_dash = STATIC_SYMBOL("LONG-DASH",AB_package);
    list_constant_4 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)7L),
	    FIX((SI_Long)3L));
    Qshort_dash = STATIC_SYMBOL("SHORT-DASH",AB_package);
    list_constant_22 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_5 = STATIC_CONS(FIX((SI_Long)3L),list_constant_22);
    Qcoarse_dot = STATIC_SYMBOL("COARSE-DOT",AB_package);
    list_constant_6 = STATIC_LIST((SI_Long)2L,FIX((SI_Long)1L),
	    FIX((SI_Long)5L));
    Qfine_dot = STATIC_SYMBOL("FINE-DOT",AB_package);
    list_constant_7 = STATIC_CONS(FIX((SI_Long)1L),list_constant_22);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    array_constant_1 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Kabsolute = STATIC_SYMBOL("ABSOLUTE",Pkeyword);
    list_constant_8 = STATIC_CONS(Qsolid,Qnil);
    string_constant_3 = 
	    STATIC_STRING("At most ~a line pattern elements are allowed.");
    string_constant_4 = 
	    STATIC_STRING("Each length must be a positive integer less than ~a.");
    Qcompile_connection_line_pattern_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONNECTION-LINE-PATTERN-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_connection_line_pattern_for_slot,
	    STATIC_FUNCTION(compile_connection_line_pattern_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qconnection_line_pattern,
	    SYMBOL_FUNCTION(Qcompile_connection_line_pattern_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qconnection_line_pattern,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_4 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)57344L);
    string_constant_5 = STATIC_STRING("~d on, ~d off");
    array_constant_5 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    Qtwrite_line_pattern_element = 
	    STATIC_SYMBOL("TWRITE-LINE-PATTERN-ELEMENT",AB_package);
    SET_SYMBOL_FUNCTION(Qtwrite_line_pattern_element,
	    STATIC_FUNCTION(twrite_line_pattern_element,NIL,FALSE,1,1));
    array_constant_6 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)26L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)57344L);
    Qwrite_connection_line_pattern_from_slot = 
	    STATIC_SYMBOL("WRITE-CONNECTION-LINE-PATTERN-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_connection_line_pattern_from_slot,
	    STATIC_FUNCTION(write_connection_line_pattern_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qconnection_line_pattern,
	    SYMBOL_FUNCTION(Qwrite_connection_line_pattern_from_slot),
	    Qslot_value_writer);
    Qline_pattern = STATIC_SYMBOL("LINE-PATTERN",AB_package);
    Qput_line_pattern = STATIC_SYMBOL("PUT-LINE-PATTERN",AB_package);
    SET_SYMBOL_FUNCTION(Qput_line_pattern,STATIC_FUNCTION(put_line_pattern,
	    NIL,FALSE,3,3));
    Qslot_putter = STATIC_SYMBOL("SLOT-PUTTER",AB_package);
    mutate_global_property(Qline_pattern,
	    SYMBOL_FUNCTION(Qput_line_pattern),Qslot_putter);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_24 = STATIC_CONS(Qno_item,Qnil);
    list_constant_19 = STATIC_CONS(Qsequence,Qnil);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_20 = STATIC_CONS(Qab_structure,Qnil);
    list_constant_25 = STATIC_LIST((SI_Long)6L,Qab_or,list_constant_24,
	    Qnil,list_constant_19,list_constant_19,list_constant_20);
    set_property_value_function(get_symbol_properties_function(Qconnection_line_pattern),
	    Qtype_specification_simple_expansion,list_constant_25);
    list_constant_30 = STATIC_LIST((SI_Long)8L,Qmember,Qsolid,Qdash,
	    Qab_dot,Qlong_dash,Qshort_dash,Qcoarse_dot,Qfine_dot);
    list_constant_31 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qsymbol,
	    list_constant_22);
    list_constant_26 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,Qinteger,
	    list_constant_22);
    Qpattern = STATIC_SYMBOL("PATTERN",AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qpattern,list_constant_26);
    Qnot_scaled_by_line_width = STATIC_SYMBOL("NOT-SCALED-BY-LINE-WIDTH",
	    AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qnot_scaled_by_line_width,
	    Qtruth_value);
    list_constant_29 = STATIC_LIST((SI_Long)2L,list_constant_27,
	    list_constant_28);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qab_structure,list_constant_29);
    list_constant_10 = STATIC_LIST((SI_Long)6L,Qab_or,list_constant_24,
	    list_constant_30,list_constant_31,list_constant_26,
	    list_constant_32);
    define_type_specification_explicit_complex_type(Qconnection_line_pattern,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,Qconnection_line_pattern);
    string_constant_6 = 
	    STATIC_STRING("A line-pattern specified with a structure must contain a pattern attribute which must be a sequence.");
    string_constant_7 = 
	    STATIC_STRING("A pattern in a line-pattern structure must contain an even number of elements");
    string_constant_8 = 
	    STATIC_STRING("A line-pattern specified with a structure must contain a not-scaled-by-line-width attribute which must be a truth-value.");
    string_constant_9 = 
	    STATIC_STRING("A numeric line-pattern must have even length.");
    string_constant_10 = 
	    STATIC_STRING("The line-pattern contains invalid elements.");
    connection_line_pattern_evaluation_setter_1 = 
	    STATIC_FUNCTION(connection_line_pattern_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qconnection_line_pattern,
	    connection_line_pattern_evaluation_setter_1);
    connection_line_pattern_evaluation_getter_1 = 
	    STATIC_FUNCTION(connection_line_pattern_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconnection_line_pattern,
	    connection_line_pattern_evaluation_getter_1);
    string_constant_120 = 
	    STATIC_STRING("1n1n838-y1m9k83Py01n838-y1m9k83Zy83Zy1m838-y83sny");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_120));
    string_constant_121 = 
	    STATIC_STRING("1m1n83sny83smy1ll1n83sny1n83smy1m9k83vy83sny2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_121));
    string_constant_122 = 
	    STATIC_STRING("1o1n83smy83spyl1n83smy1m83spy83soy1mml1n83smy1m83-Cgy83spy2m83Pyml1n83smy1n83-Cgy83spy83soy2mnml");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_122));
    string_constant_123 = 
	    STATIC_STRING("1o1m83spy1m9k83-Joy1m83spy1m9k83ly1m83spy1m9k83-RHy1m83spy1m9k83*fy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_123));
    Qend = STATIC_SYMBOL("END",AB_package);
    string_constant_124 = 
	    STATIC_STRING("1n1n83soy1o1m9k83=Gy1m9k9l1m9k83py1m9k9m83py1n83soy1o1m9k83=Gy1m9k9l1m9k83dy1m9k9m83dy1n83soy1n1m9k83=Gy1m9k83-Kwy1m9k83-Sly83-K");
    string_constant_125 = STATIC_STRING("wy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qend);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_124,
	    string_constant_125)));
    string_constant_126 = 
	    STATIC_STRING("1q1m83--+y1m9k83-Vy1m83--+y1m9k83=Ay1m83--+y1m9k83-soy1m83--+y1m9k83-spy1m83--+y1m9k83-x6y1m83--+y1m9k83-g3y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_126));
    Qnarrow = STATIC_SYMBOL("NARROW",AB_package);
    Qwide = STATIC_SYMBOL("WIDE",AB_package);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qthin = STATIC_SYMBOL("THIN",AB_package);
    Qthick = STATIC_SYMBOL("THICK",AB_package);
    Qfilled = STATIC_SYMBOL("FILLED",AB_package);
    string_constant_127 = 
	    STATIC_STRING("1o1m83-Cfy1m9k83oy1m83-Cfy1m9k9l1m83-Cfy83--+y1n83-Cfy1m1m9k83-wYy83--+y1m83-wYym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qopen);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_127));
    string_constant_128 = 
	    STATIC_STRING("1m1o83-Cgy83-Cfy1ll9k1o83-Cgy1m83-Cfy83-Cgy2llm9k");
    clear_optimized_constants();
    push_optimized_constant(Qflatten_phrase_tree);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_128));
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    string_constant_11 = STATIC_STRING("Wide or narrow used with circle.");
    Qvery = STATIC_SYMBOL("VERY",AB_package);
    string_constant_12 = STATIC_STRING("The modifier ~a is duplicated.");
    string_constant_13 = STATIC_STRING("The modifiers ~a and ~a conflict.");
    Qconnection_arrows = STATIC_SYMBOL("CONNECTION-ARROWS",AB_package);
    Qcompile_connection_arrows_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONNECTION-ARROWS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_connection_arrows_for_slot,
	    STATIC_FUNCTION(compile_connection_arrows_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qconnection_arrows,
	    SYMBOL_FUNCTION(Qcompile_connection_arrows_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qconnection_arrows,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    array_constant_7 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)7L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qwrite_connection_arrows_from_slot = 
	    STATIC_SYMBOL("WRITE-CONNECTION-ARROWS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_connection_arrows_from_slot,
	    STATIC_FUNCTION(write_connection_arrows_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qconnection_arrows,
	    SYMBOL_FUNCTION(Qwrite_connection_arrows_from_slot),
	    Qslot_value_writer);
    string_constant_14 = STATIC_STRING("");
    array_constant_9 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    string_constant_15 = STATIC_STRING(" at the output end");
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    string_constant_16 = STATIC_STRING(" at the input end");
    Qboth = STATIC_SYMBOL("BOTH",AB_package);
    string_constant_17 = STATIC_STRING(" at both ends");
    Qput_connection_arrows = STATIC_SYMBOL("PUT-CONNECTION-ARROWS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_connection_arrows,
	    STATIC_FUNCTION(put_connection_arrows,NIL,FALSE,3,3));
    mutate_global_property(Qconnection_arrows,
	    SYMBOL_FUNCTION(Qput_connection_arrows),Qslot_putter);
    float_constant_2 = STATIC_FLOAT(0.25);
    float_constant_3 = STATIC_FLOAT(0.5);
    float_constant = STATIC_FLOAT(1.0);
    float_constant_4 = STATIC_FLOAT(2.0);
    float_constant_5 = STATIC_FLOAT(4.0);
    list_constant_33 = STATIC_LIST((SI_Long)5L,float_constant_2,
	    float_constant_3,float_constant,float_constant_4,float_constant_5);
    Connection_arrow_permitted_scales = list_constant_33;
    list_constant_34 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_24,
	    Qnil,list_constant_19);
    set_property_value_function(get_symbol_properties_function(Qconnection_arrows),
	    Qtype_specification_simple_expansion,list_constant_34);
    Qarrow = STATIC_SYMBOL("ARROW",AB_package);
    Qtriangle = STATIC_SYMBOL("TRIANGLE",AB_package);
    Qdiamond = STATIC_SYMBOL("DIAMOND",AB_package);
    list_constant_35 = STATIC_LIST((SI_Long)4L,Qarrow,Qtriangle,Qdiamond,
	    Qcircle);
    list_constant_49 = STATIC_LIST_STAR((SI_Long)4L,Qmember,Qdefault,Qnone,
	    list_constant_35);
    Qshape = STATIC_SYMBOL("SHAPE",AB_package);
    list_constant_36 = STATIC_CONS(Qmember,list_constant_35);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qshape,list_constant_36);
    list_constant_37 = STATIC_CONS(Qtruth_value,Qnil);
    list_constant_41 = STATIC_CONS(Qfilled,list_constant_37);
    Qscale = STATIC_SYMBOL("SCALE",AB_package);
    list_constant_38 = STATIC_CONS(Qfloat,Qnil);
    list_constant_42 = STATIC_CONS(Qscale,list_constant_38);
    Qaspect_ratio = STATIC_SYMBOL("ASPECT-RATIO",AB_package);
    list_constant_43 = STATIC_CONS(Qaspect_ratio,list_constant_38);
    Qline_weight = STATIC_SYMBOL("LINE-WEIGHT",AB_package);
    list_constant_44 = STATIC_CONS(Qline_weight,list_constant_38);
    Qplacement = STATIC_SYMBOL("PLACEMENT",AB_package);
    list_constant_39 = STATIC_LIST((SI_Long)5L,Qmember,Qdefault,Qoutput,
	    Qinput,Qboth);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qplacement,list_constant_39);
    list_constant_46 = STATIC_LIST((SI_Long)6L,list_constant_40,
	    list_constant_41,list_constant_42,list_constant_43,
	    list_constant_44,list_constant_45);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qab_or,Qshape);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_46,list_constant_47);
    list_constant_50 = STATIC_LIST((SI_Long)2L,Qsequence,list_constant_48);
    list_constant_12 = STATIC_LIST((SI_Long)4L,Qab_or,list_constant_24,
	    list_constant_49,list_constant_50);
    define_type_specification_explicit_complex_type(Qconnection_arrows,
	    list_constant_12);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnamed,Qconnection_arrows);
    connection_arrows_evaluation_setter_1 = 
	    STATIC_FUNCTION(connection_arrows_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qconnection_arrows,
	    connection_arrows_evaluation_setter_1);
    connection_arrows_evaluation_getter_1 = 
	    STATIC_FUNCTION(connection_arrows_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qconnection_arrows,
	    connection_arrows_evaluation_getter_1);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_18 = STATIC_STRING("The ~a must be one of ");
    Qtwrite = STATIC_SYMBOL("TWRITE",AB_package);
    SET_SYMBOL_FUNCTION(Qtwrite,STATIC_FUNCTION(twrite,NIL,FALSE,1,1));
    string_constant_19 = STATIC_STRING(" or ");
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qoutput,Qdefault);
    float_constant_1 = STATIC_FLOAT(0.01);
    Qdefaulted_attribute_name = STATIC_SYMBOL("DEFAULTED-ATTRIBUTE-NAME",
	    AB_package);
    Qdata_type = STATIC_SYMBOL("DATA-TYPE",AB_package);
    Qdata_server = STATIC_SYMBOL("DATA-SERVER",AB_package);
    Qvalidity_interval = STATIC_SYMBOL("VALIDITY-INTERVAL",AB_package);
    Qdefault_update_interval = STATIC_SYMBOL("DEFAULT-UPDATE-INTERVAL",
	    AB_package);
    Qhistory_keeping_spec = STATIC_SYMBOL("HISTORY-KEEPING-SPEC",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    Qallow_duplicate_elements = STATIC_SYMBOL("ALLOW-DUPLICATE-ELEMENTS",
	    AB_package);
    Qlist_type = STATIC_SYMBOL("LIST-TYPE",AB_package);
    Qsimulation_details = STATIC_SYMBOL("SIMULATION-DETAILS",AB_package);
    Qg2_array_element_type = STATIC_SYMBOL("G2-ARRAY-ELEMENT-TYPE",AB_package);
    Qg2_array_length = STATIC_SYMBOL("G2-ARRAY-LENGTH",AB_package);
    Qg2_array_initial_values = STATIC_SYMBOL("G2-ARRAY-INITIAL-VALUES",
	    AB_package);
    list_constant_51 = STATIC_LIST((SI_Long)12L,Qdata_type,Qdata_server,
	    Qvalidity_interval,Qdefault_update_interval,
	    Qhistory_keeping_spec,Qinitial_value,Qallow_duplicate_elements,
	    Qlist_type,Qsimulation_details,Qg2_array_element_type,
	    Qg2_array_length,Qg2_array_initial_values);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    def_semi_open_category_1(5,Qdefaulted_attribute_name,list_constant_51,
	    Qunreserved_symbol,Nil,Nil);
    Qfix_default_override_on_user_defined_slot = 
	    STATIC_SYMBOL("FIX-DEFAULT-OVERRIDE-ON-USER-DEFINED-SLOT",
	    AB_package);
    string_constant_129 = 
	    STATIC_STRING("1x1m83Bcy1m9k83Zy1m83Bcy83-cty1m83-cty83-i6y1o83-cty1n83-i6y1m9k83-Zy83-cty1nmln9l1o83-i6y83*my1nl083ANy9m1o83-i6y1n83-Gy1m9k83=");
    string_constant_130 = 
	    STATIC_STRING("my83*my1n1n830=yln083ANy9m1o83-i6y1q83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy830Ty1n1n830=ylnq83ANy9m1o83-i6y1o83*my1m9k8396y1m9k83*");
    string_constant_131 = 
	    STATIC_STRING("Iy837ky1nlo83ANy9m1o83-i6y1q83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy837ky1n1n830=ylnq83ANy9m1o83-i6y1r83*my1m9k8396y1m9k83*Iy1m9k83");
    string_constant_132 = 
	    STATIC_STRING("44y1m9k83*ty83=Zy837dy1nl1n83*Ay9nr83ANy9m1o83-i6y1t83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1n1n830=yln");
    string_constant_133 = 
	    STATIC_STRING("1n83*Ay9nt83ANy9m1o83-i6y1s83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1nl1n83*Ay9os83ANy9m1o83-i6y1u83-Gy1m9k83");
    string_constant_134 = 
	    STATIC_STRING("=my83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1n1n830=yln1n83*Ay9ou83ANy9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_default_override_on_user_defined_slot);
    push_optimized_constant(Qinstantiate_variable);
    push_optimized_constant(Qinstantiate_object_in_attribute);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_129,string_constant_130,string_constant_131,
	    string_constant_132,string_constant_133,string_constant_134)));
    string_constant_135 = 
	    STATIC_STRING("1w1m83Bdy1m9k83Zy1m83Bdy83-cuy1m83-cuy83-i7y1o83-cuy1n83-i7y1m9k83-Zy83-cuy1nmln9l1o83-i7y83*my1nl083ANy9m1o83-i7y1n83-Gy1m9k83=");
    string_constant_136 = 
	    STATIC_STRING("my83*my1n1n830=yln083ANy9m1o83-i7y1o83*my1m9k8396y1m9k83*Iy837ky1nlo83ANy9m1o83-i7y1q83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy837ky1");
    string_constant_137 = 
	    STATIC_STRING("n1n830=ylnq83ANy9m1o83-i7y1r83*my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1nl1n83*Ay9nr83ANy9m1o83-i7y1t83-Gy1m9k83=my83*my");
    string_constant_138 = 
	    STATIC_STRING("1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1n1n830=yln1n83*Ay9nt83ANy9m1o83-i7y1s83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9");
    string_constant_139 = 
	    STATIC_STRING("k83-Ty83=Zy832Cy1nl1n83*Ay9os83ANy9m1o83-i7y1u83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1n1n830=");
    string_constant_140 = STATIC_STRING("yln1n83*Ay9ou83ANy9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_default_override_on_user_defined_slot);
    push_optimized_constant(Qinstantiate_variable);
    push_optimized_constant(Qinstantiate_object_in_attribute);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_135,string_constant_136,string_constant_137,
	    string_constant_138,string_constant_139,string_constant_140)));
    string_constant_141 = 
	    STATIC_STRING("13Dy1m83Bey1m9k83Zy1m83Bey83-cvy1m83-cvy83-8Ky1o83-cvy1n83-8Ky1m9k83-Zy83-cvy1nmln9l1o83-8Ky83*my1nl083ANy9m1o83-8Ky1n83-Gy1m9k8");
    string_constant_142 = 
	    STATIC_STRING("3=my83*my1n1n830=yln083ANy9m1o83-8Ky1o83*my1m9k8396y1m9k83*Iy837ky1nlo83ANy9m1o83-8Ky1q83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy837k");
    string_constant_143 = 
	    STATIC_STRING("y1n1n830=ylnq83ANy9m1o83-8Ky1r83*my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1nl1n83*Ay9nr83ANy9m1o83-8Ky1t83-Gy1m9k83=my83*");
    string_constant_144 = 
	    STATIC_STRING("my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1n1n830=yln1n83*Ay9nt83ANy9m1o83-8Ky1s83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1");
    string_constant_145 = 
	    STATIC_STRING("m9k83-Ty83=Zy832Cy1nl1n83*Ay9os83ANy9m1o83-8Ky1u83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1n1n83");
    string_constant_146 = 
	    STATIC_STRING("0=yln1n83*Ay9ou83ANy9m1m835Vy1m9k83Zy1m835Vy83-hy1m835Vy830my1m835Vy83-2y1m835Vy83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_default_override_on_user_defined_slot);
    push_optimized_constant(Qinstantiate_variable);
    push_optimized_constant(Qinstantiate_object_in_attribute);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_141,string_constant_142,string_constant_143,
	    string_constant_144,string_constant_145,string_constant_146)));
    Qmake_simulation_subtable_and_install = 
	    STATIC_SYMBOL("MAKE-SIMULATION-SUBTABLE-AND-INSTALL",AB_package);
    Qmake_simulation_subtable_with_specific_class_and_install = 
	    STATIC_SYMBOL("MAKE-SIMULATION-SUBTABLE-WITH-SPECIFIC-CLASS-AND-INSTALL",
	    AB_package);
    Qsecond_none = STATIC_SYMBOL("SECOND-NONE",AB_package);
    string_constant_147 = 
	    STATIC_STRING("13-By1n83-8Ky1n1m9k837hy1m9k83-Py83Ky1n837hyn831Yy1n83-8Ky1n1m9k839Jy1m9k83-Py83Ky1n839Jyn831Zy1n83-8Ky1q1m9k831Dy1m9k8p1m9k83=I");
    string_constant_148 = 
	    STATIC_STRING("y1m9k834ay1m9k83-Py831ry1n831ryq834ay1n83-8Ky1p1m9k831ry1m9k83=Iy1m9k834ay1m9k83-Py831ry1n831ryp834ay1n83-8Ky1q1m9k831Dy1m9k8p1m");
    string_constant_149 = 
	    STATIC_STRING("9k83=Iy1m9k8315y1m9k83-Py832Fy1n831ryq8315y1n83-8Ky1p1m9k831ry1m9k83=Iy1m9k8315y1m9k83-Py832Fy1n831ryp8315y1n83-8Ky1q1m9k831Dy1m");
    string_constant_150 = 
	    STATIC_STRING("9k8p1m9k83=Iy1m9k8314y1m9k83-Py832Fy1n831ryq8314y1n83-8Ky1p1m9k831ry1m9k83=Iy1m9k8314y1m9k83-Py832Fy1n831ryp8314y1n83-8Ky1o1m9k8");
    string_constant_151 = 
	    STATIC_STRING("3-GJy1m9k83-oy1m9k83-Py830uy1m830uyo1n83-8Ky1n1m9k830uy1m9k83-Py830uy1m830uyn1n83-8Ky1n1m9k83-E3y1m9k83n4y1m9k83b3y1m837Py1m83*A");
    string_constant_152 = 
	    STATIC_STRING("y9l1n83-8Ky1n1m9k83-E4y1m9k83-Py83n9y1m837Py1n83*Ay9mn1n83-8Ky1o1m9k831Dy1m9k839wy1m9k83-Py83*My1m83*Myo1n83-8Ky1n1m9k83BVy1m9k8");
    string_constant_153 = 
	    STATIC_STRING("3-Py83*My1m83*Myn1o83-8Ky1p1m9k83Py1m9k837cy1m9k83-oy1m9k83-Py832gy1m83gYyp9n1o83-8Ky1n1m9k83gYy1m9k83-Py832gy1m83gYyn9n1n83-8Ky");
    string_constant_154 = 
	    STATIC_STRING("1p1m9k836xy1m9k83-1ay1m9k83-DVy1m9k83-Py830hy1m83iTyp1n83-8Ky1p1m9k83iTy1m9k83=Iy1m9k830Cy1m9k83-Py830hy1m83iTyp1n83-8Ky1s1m9k83");
    string_constant_155 = 
	    STATIC_STRING("6xy1m9k83-1ay1m9k83-DVy1m9k83=Iy1m9k83n4y1m9k83b3y1m9k83-Py830hy1m83-Y7ys1n83-8Ky1p1m9k83iTy1m9k83=Iy1m9k832Ly1m9k83-Py830hy1m83");
    string_constant_156 = 
	    STATIC_STRING("-Y7yp1n83-8Ky1p1m9k83-89y1m9k83=Iy1m9k83*dy1m9k83vy83*Ey1n83-Eyp83*dy1n83-8Ky1n1m9k83-8By1m9k83-Py83*Ey1n83-Eyn83*dy1n83-8Ky1p1m");
    string_constant_157 = 
	    STATIC_STRING("9k83-89y1m9k83=Iy1m9k83=vy1m9k83-Py83=Cy1n83-Eyp83=vy1n83-8Ky1n1m9k83-8Ay1m9k83-Py83=Cy1n83-Eyn83=vy1n83-8Ky1q1m9k83Cxy1m9k83*ly");
    string_constant_158 = 
	    STATIC_STRING("1m9k83=Iy1m9k834Ky1m9k83-Py836Ny1n83j0yq834Ky1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834Ky1m9k83-Py836Ny1n83j0yp834Ky1n83-8Ky1q1m9k83Cxy");
    string_constant_159 = 
	    STATIC_STRING("1m9k83*ly1m9k83=Iy1m9k8315y1m9k83-Py837Iy1n83j0yq8315y1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k8315y1m9k83-Py837Iy1n83j0yp8315y1n83-8Ky1q");
    string_constant_160 = 
	    STATIC_STRING("1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834-y1m9k83-Py8370y1n83j0yq834-y1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834-y1m9k83-Py8370y1n83j0yp834-y1");
    string_constant_161 = 
	    STATIC_STRING("n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k835iy1m9k83-Py8374y1n83j0yq835iy1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k835iy1m9k83-Py8374y1n83j");
    string_constant_162 = 
	    STATIC_STRING("0yp835iy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834Ey1m9k83-Py8372y1n83j0yq834Ey1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834Ey1m9k83-Py8");
    string_constant_163 = 
	    STATIC_STRING("372y1n83j0yp834Ey1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834fy1m9k83-Py837Sy1n83j0yq834fy1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834fy1");
    string_constant_164 = 
	    STATIC_STRING("m9k83-Py837Sy1n83j0yp834fy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834jy1m9k83-Py83-xy1n83j0yq834jy1n83-8Ky1p1m9k83j0y1m9k83=Iy1");
    string_constant_165 = 
	    STATIC_STRING("m9k834jy1m9k83-Py83-xy1n83j0yp834jy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834Jy1m9k83-Py83-hy1n83j0yq834Jy1n83-8Ky1p1m9k83j0y1");
    string_constant_166 = 
	    STATIC_STRING("m9k83=Iy1m9k834Jy1m9k83-Py83-hy1n83j0yp834Jy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k8314y1m9k83-Py830my1n83j0yq8314y1n83-8Ky1p1");
    string_constant_167 = 
	    STATIC_STRING("m9k83j0y1m9k83=Iy1m9k8314y1m9k83-Py830my1n83j0yp8314y1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834+y1m9k83-Py837=y1n83j0yq834+y1n");
    string_constant_168 = 
	    STATIC_STRING("83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834+y1m9k83-Py837=y1n83j0yp834+y1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k835hy1m9k83-Py8373y1n83j0");
    string_constant_169 = 
	    STATIC_STRING("yq835hy1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k835hy1m9k83-Py8373y1n83j0yp835hy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834Dy1m9k83-Py83");
    string_constant_170 = 
	    STATIC_STRING("71y1n83j0yq834Dy1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834Dy1m9k83-Py8371y1n83j0yp834Dy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834ey1m");
    string_constant_171 = 
	    STATIC_STRING("9k83-Py830Ty1n83j0yq834ey1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834ey1m9k83-Py830Ty1n83j0yp834ey1n83-8Ky1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m");
    string_constant_172 = 
	    STATIC_STRING("9k834iy1m9k83-Py83-Uy1n83j0yq834iy1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834iy1m9k83-Py83-Uy1n83j0yp834iy1n83-8Ky1q1m9k83Cxy1m9k83*ly1m");
    string_constant_173 = 
	    STATIC_STRING("9k83=Iy1m9k834ay1m9k83-Py835Vy1n83j0yq834ay1n83-8Ky1p1m9k83j0y1m9k83=Iy1m9k834ay1m9k83-Py835Vy1n83j0yp834ay1n83-8Ky1q1m9k83Buy1m");
    string_constant_174 = 
	    STATIC_STRING("9k8p1m9k83=Iy1m9k834Gy1m9k83-Py83-Gy1n83*6yq834Gy1n83-8Ky1p1m9k83-Xy1m9k83=Iy1m9k834Gy1m9k83-Py83-Gy1n83*6yp834Gy1n83-8Ky1r1m9k8");
    string_constant_175 = 
	    STATIC_STRING("37gy1m9k83gpy1m9k83h-y1m9k83=Iy1m9k831Zy1m9k83-Py83Ky1n8375yr831Zy1n83-8Ky1n1m9k83pey1m9k83-Py83Ky1n8375yn831Zy1n83-8Ky1q1m9k83B");
    string_constant_176 = 
	    STATIC_STRING("uy1m9k8p1m9k83=Iy1m9k834Fy1m9k83-Py83-Gy1n83-vyq834Fy1n83-8Ky1p1m9k83-Xy1m9k83=Iy1m9k834Fy1m9k83-Py83-Gy1n83-vyp834Fy1n83-8Ky1p1");
    string_constant_177 = 
	    STATIC_STRING("m9k837iy1m9k83=Iy1m9k831Yy1m9k83-Py835Ey1n835Eyp831Yy1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=Iy1m9k831Yy1m9k83-Py839Ly1n83-wyq831Yy1n83-");
    string_constant_178 = 
	    STATIC_STRING("8Ky1p1m9k83-=Xy1m9k83=Iy1m9k831Yy1m9k83-Py839Ly1n83-wyp831Yy1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=Iy1m9k830vy1m9k83-Py839Ky1n83-wyq830");
    string_constant_179 = 
	    STATIC_STRING("vy1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k830vy1m9k83-Py839Ky1n83-wyp830vy1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=Iy1m9k834Fy1m9k83-Py836jy1n83");
    string_constant_180 = 
	    STATIC_STRING("-wyq834Fy1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k834Fy1m9k83-Py836jy1n83-wyp834Fy1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=Iy1m9k8316y1m9k83-Py83");
    string_constant_181 = 
	    STATIC_STRING("0Qy1n83-wyq8316y1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k8316y1m9k83-Py830Qy1n83-wyp8316y1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=Iy1m9k831cy1m9k");
    string_constant_182 = 
	    STATIC_STRING("83-Py831dy1n83-wyq831cy1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k831cy1m9k83-Py831dy1n83-wyp831cy1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=Iy1m9k83");
    string_constant_183 = 
	    STATIC_STRING("3wy1m9k83-Py831Xy1n83-wyq833wy1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k833wy1m9k83-Py831Xy1n83-wyp833wy1n83-8Ky1q1m9k83Cxy1m9k9o1m9k83=I");
    string_constant_184 = 
	    STATIC_STRING("y1m9k834dy1m9k83-Py831ky1n83-wyq834dy1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k834dy1m9k83-Py831ky1n83-wyp834dy1n83-8Ky1q1m9k83Cxy1m9k9o1");
    string_constant_185 = 
	    STATIC_STRING("m9k83=Iy1m9k834hy1m9k83-Py837fy1n83-wyq834hy1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k834hy1m9k83-Py837fy1n83-wyp834hy1n83-8Ky1q1m9k83Cxy");
    string_constant_186 = 
	    STATIC_STRING("1m9k9o1m9k83=Iy1m9k834ly1m9k83-Py831my1n83-wyq834ly1n83-8Ky1p1m9k83-=Xy1m9k83=Iy1m9k834ly1m9k83-Py831my1n83-wyp834ly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_simulation_subtable_and_install);
    push_optimized_constant(Qmake_simulation_subtable_with_specific_class_and_install);
    push_optimized_constant(Qsecond_none);
    push_optimized_constant(Qvalues);
    System_class_overrides_for_object_definition = 
	    regenerate_optimized_constant(list(40,string_constant_147,
	    string_constant_148,string_constant_149,string_constant_150,
	    string_constant_151,string_constant_152,string_constant_153,
	    string_constant_154,string_constant_155,string_constant_156,
	    string_constant_157,string_constant_158,string_constant_159,
	    string_constant_160,string_constant_161,string_constant_162,
	    string_constant_163,string_constant_164,string_constant_165,
	    string_constant_166,string_constant_167,string_constant_168,
	    string_constant_169,string_constant_170,string_constant_171,
	    string_constant_172,string_constant_173,string_constant_174,
	    string_constant_175,string_constant_176,string_constant_177,
	    string_constant_178,string_constant_179,string_constant_180,
	    string_constant_181,string_constant_182,string_constant_183,
	    string_constant_184,string_constant_185,string_constant_186));
    add_grammar_rules_function(System_class_overrides_for_object_definition);
    string_constant_187 = 
	    STATIC_STRING("1w1m83Bby1m9k83Zy1m83Bby83-csy1m83-csy83lIy1o83-csy1n83lIy1m9k83-Zy83-csy1nmln9l1o83lIy83*my1nl083ANy9m1o83lIy1n83-Gy1m9k83=my83");
    string_constant_188 = 
	    STATIC_STRING("*my1n1n830=yln083ANy9m1o83lIy1o83*my1m9k8396y1m9k83*Iy837ky1nlo83ANy9m1o83lIy1q83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy837ky1n1n830");
    string_constant_189 = 
	    STATIC_STRING("=ylnq83ANy9m1o83lIy1r83*my1m9k8396y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1nl1n83*Ay9nr83ANy9m1o83lIy1t83-Gy1m9k83=my83*my1m9k8396");
    string_constant_190 = 
	    STATIC_STRING("y1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1n1n830=yln1n83*Ay9nt83ANy9m1o83lIy1s83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=");
    string_constant_191 = 
	    STATIC_STRING("Zy832Cy1nl1n83*Ay9os83ANy9m1o83lIy1u83-Gy1m9k83=my83*my1m9k8396y1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy832Cy1n1n830=yln1n83*Ay");
    string_constant_192 = STATIC_STRING("9ou83ANy9m");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_default_override_on_user_defined_slot);
    push_optimized_constant(Qinstantiate_variable);
    push_optimized_constant(Qinstantiate_object_in_attribute);
    add_grammar_rules_function(regenerate_optimized_constant(list(6,
	    string_constant_187,string_constant_188,string_constant_189,
	    string_constant_190,string_constant_191,string_constant_192)));
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_193 = 
	    STATIC_STRING("13*Ly1n83lIy1n1m9k83Egy1m9k83-Py83Ky1n83Egyn1m1l837Ky01n83lIy1n1m9k837hy1m9k83-Py83Ky1n837hyn1m1l831Yy01n83lIy1n1m9k839Jy1m9k83-");
    string_constant_194 = 
	    STATIC_STRING("Py83Ky1n839Jyn1m1l831Zy01n83lIy1n1m9k83-=fy1m9k83-Py83Ky1n834Byn1m1l831Ry01n83lIy1n1m9k83-ZRy1m9k83-Py83Ky1n834Ayn1m1l831Ry01n83");
    string_constant_195 = 
	    STATIC_STRING("lIy1p1m9k83-Xy1m9k83=Iy1m9k834Gy1m9k83-Py83-Gy1n83*6yp1m1l834Gy01n83lIy1p1m9k83-Xy1m9k83=Iy1m9k834Fy1m9k83-Py83-Gy1n83-vyp1m1l83");
    string_constant_196 = 
	    STATIC_STRING("4Fy01n83lIy1p1m9k831ry1m9k83=Iy1m9k834ay1m9k83-Py831ry1n83-Iyp1m1l834ay01n83lIy1p1m9k831ry1m9k83=Iy1m9k8315y1m9k83-Py832Fy1n83-I");
    string_constant_197 = 
	    STATIC_STRING("yp1m1l8315y01n83lIy1p1m9k831ry1m9k83=Iy1m9k8314y1m9k83-Py832Fy1n83-Iyp1m1l8314y01n83lIy1n1m9k830uy1m9k83-Py830uy1n830uyn1m1l83*d");
    string_constant_198 = 
	    STATIC_STRING("y01n83lIy1n1m9k83-E4y1m9k83-Py83n9y1n837Py1n83*Ay9ln1m1l83*dy01n83lIy1n1m9k83BVy1m9k83-Py83*My1n83*Myn1m1l83*dy01n83lIy1n1m9k833");
    string_constant_199 = 
	    STATIC_STRING("oy1m9k83-Py83-2y1n833oyn1m1l839*y01n83lIy1n1m9k83gYy1m9k83-Py832gy1n83Auyn1m1l83*dy01n83lIy1p1m9k83iTy1m9k83=Iy1m9k830Cy1m9k83-P");
    string_constant_200 = 
	    STATIC_STRING("y830hy1n83Fqyp1m1l830Cy01n83lIy1p1m9k83iTy1m9k83=Iy1m9k832Ly1m9k83-Py830hy1n83Cfyp1m1l83*dy01n83lIy1n1m9k83-8By1m9k83-Py83*Ey1n8");
    string_constant_201 = 
	    STATIC_STRING("3-Eyn1m1l83*dy01n83lIy1n1m9k83-8Ay1m9k83-Py83=Cy1n83-Eyn1m1l83=vy01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834Ky1m9k83-Py836Ny1n83-Kyp1m1l");
    string_constant_202 = 
	    STATIC_STRING("834Ky01n83lIy1p1m9k83j0y1m9k83=Iy1m9k8315y1m9k83-Py837Iy1n83-Kyp1m1l8315y01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834-y1m9k83-Py8370y1n83");
    string_constant_203 = 
	    STATIC_STRING("-Kyp1m1l834-y01n83lIy1p1m9k83j0y1m9k83=Iy1m9k835iy1m9k83-Py8374y1n83-Kyp1m1l835iy01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834Ey1m9k83-Py8");
    string_constant_204 = 
	    STATIC_STRING("372y1n83-Kyp1m1l834Ey01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834fy1m9k83-Py837Sy1n83-Kyp1m1l834fy01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834jy1m");
    string_constant_205 = 
	    STATIC_STRING("9k83-Py83-xy1n83-Kyp1m1l834jy01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834Jy1m9k83-Py83-hy1n83-Kyp1m1l834Jy01n83lIy1p1m9k83j0y1m9k83=Iy1m9");
    string_constant_206 = 
	    STATIC_STRING("k8314y1m9k83-Py830my1n83-Kyp1m1l8314y01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834+y1m9k83-Py837=y1n83-Kyp1m1l834+y01n83lIy1p1m9k83j0y1m9k");
    string_constant_207 = 
	    STATIC_STRING("83=Iy1m9k835hy1m9k83-Py8373y1n83-Kyp1m1l835hy01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834Dy1m9k83-Py8371y1n83-Kyp1m1l834Dy01n83lIy1p1m9k8");
    string_constant_208 = 
	    STATIC_STRING("3j0y1m9k83=Iy1m9k834ey1m9k83-Py830Ty1n83-Kyp1m1l834ey01n83lIy1p1m9k83j0y1m9k83=Iy1m9k834iy1m9k83-Py83-Uy1n83-Kyp1m1l834iy01n83lI");
    string_constant_209 = 
	    STATIC_STRING("y1p1m9k83j0y1m9k83=Iy1m9k834ay1m9k83-Py835Vy1n83-Kyp1m1l834ay01n83lIy1n1m9k83pey1m9k83-Py83Ky1n8375yn1m1l831Zy01n83lIy1p1m9k837i");
    string_constant_210 = 
	    STATIC_STRING("y1m9k83=Iy1m9k831Yy1m9k83-Py835Ey1n835Eyp1m1l831Yy01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k831Yy1m9k83-Py839Ly1n83-wyp1m1l831Yy01n83lIy1");
    string_constant_211 = 
	    STATIC_STRING("p1m9k83-=Xy1m9k83=Iy1m9k830vy1m9k83-Py839Ky1n83-wyp1m1l830vy01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k834Fy1m9k83-Py836jy1n83-wyp1m1l834F");
    string_constant_212 = 
	    STATIC_STRING("y01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k8316y1m9k83-Py830Qy1n83-wyp1m1l8316y01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k831cy1m9k83-Py831dy1n83-w");
    string_constant_213 = 
	    STATIC_STRING("yp1m1l831cy01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k833wy1m9k83-Py831Xy1n83-wyp1m1l833wy01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k834dy1m9k83-Py8");
    string_constant_214 = 
	    STATIC_STRING("31ky1n83-wyp1m1l834dy01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k834hy1m9k83-Py837fy1n83-wyp1m1l834hy01n83lIy1p1m9k83-=Xy1m9k83=Iy1m9k834ly");
    string_constant_215 = 
	    STATIC_STRING("1m9k83-Py831my1n83-wyp1m1l834ly01n83lIy1n1m9k83*ey1m9k83-Py837ly1n83Amyn1m13Cy83-Oy837-y837Ky836ry834oy834gy83=Vy836ky835my831jy");
    string_constant_216 = 
	    STATIC_STRING("837Dy836oy836Zy836ey837Jy837Qy01n83lIy1n1m9k83Vy1m9k83-Py8381y1n83FGyn1m13Cy83-Oy837-y837Ky836ry834oy834gy83=Vy836ky835my831jy83");
    string_constant_217 = 
	    STATIC_STRING("7Dy836oy836Zy836ey837Jy837Qy01n83lIy1n1m9k83-a*y1m9k83-Py83-ey1n83DMyn1m1l83=uy01n83lIy1n1m9k83-Zwy1m9k83-Py83-ey1n83DLyn1m1l83=");
    string_constant_218 = 
	    STATIC_STRING("uy01n83lIy1n1m9k83wWy1m9k83-Py832Yy1n834tyn1m1l83=uy01n83lIy1n1m9k83Avy1m9k83-Py832Yy1n834syn1m1l83=uy01n83lIy1n1m9k83*Ly1m9k83-");
    string_constant_219 = 
	    STATIC_STRING("Py83*7y1n83*Lyn1m1l83=uy01n83lIy1n1m9k8340y1m9k83-Py8337y1n8340yn1m1l83=uy01n83lIy1n1m9k834ky1m9k83-Py833cy1n834kyn1m1l83=uy01n8");
    string_constant_220 = 
	    STATIC_STRING("3lIy1n1m9k83-fWy1m9k83-Py8313y1n83Dxyn1m1l83=uy01n83lIy1n1m9k83=Hy1m9k83-Py83=Hy1n83BQyn1m1l83=+y01n83lIy1n1m9k833Zy1m9k83-Py833");
    string_constant_221 = 
	    STATIC_STRING("Zy1n83FFyn1m1l83=+y01n83lIy1n1m9k83-bjy1m9k83-Py833Qy1n83DJyn1m1l83=+y01n83lIy1n1m9k8387y1m9k83-Py833Sy1n83Bayn1m1l9m01n83lIy1n1");
    string_constant_222 = 
	    STATIC_STRING("m9k83-QYy1m9k83-Py83A9y1n83Bhyn1m1l83-ly01n83lIy1n1m9k83-py1m9k83-Py83-py1n83-pyn1m1s83=Vy830Cy835Ty832Jy832Ly836ky835my834Ty1m8");
    string_constant_223 = 
	    STATIC_STRING("37Cy836ly1n83lIy1n1m9k833ky1m9k83-Py837xy1n833kyn1m1l83=Vy1l837Cy1n83lIy1n1m9k833ry1m9k83-Py83-Yy1n833ryn1m1l83=Vy1l837Cy1n83lIy");
    string_constant_224 = 
	    STATIC_STRING("1n1m9k83-v*y1m9k83-Py838Gy1n834nyn1m1l83=Vy1l837Cy1n83lIy1n1m9k83-RXy1m9k83-Py83*Wy1n834*yn1m1l834Ty1l836ly1n83lIy1n1m9k8300y1m9");
    string_constant_225 = 
	    STATIC_STRING("k83-Py83=Qy1n8300yn1m1o834Ty836ky835my833My01n83lIy1n1m9k830Hy1m9k83-Py83=Qy1n830Hyn1m1o834Ty836ky835my833My01n83lIy1n1m9k830Gy1");
    string_constant_226 = 
	    STATIC_STRING("m9k83-Py83-Yy1n830Gyn1m1o834Ty836ky835my833My01n83lIy1n1m9k83-p3y1m9k83-Py83Ky1n83=Pyn1m1o834Ty836ky835my833My1l836ly1n83lIy1n1m");
    string_constant_227 = 
	    STATIC_STRING("9k83DYy1m9k83-Py8388y1n83DYyn1m1l836ky01n83lIy1n1m9k83Cty1m9k83-Py8388y1n83Ctyn1m1l836ky01n83lIy1n1m9k83DZy1m9k83-Py839Ry1n83DZy");
    string_constant_228 = 
	    STATIC_STRING("n1m1l835my01n83lIy1n1m9k83Cuy1m9k83-Py839Ry1n83Cuyn1m1l835my01n83lIy1n1m9k83-R2y1m9k83-Py8391y1n83Bmyn1m1l833My01n83lIy1n1m9k83-");
    string_constant_229 = 
	    STATIC_STRING("R3y1m9k83-Py83ARy1n83Bnyn1m1l833My01n83lIy1n1m9k83Ewy1m9k83-Py83Ky1n83Ewyn1m1l833My01n83lIy1n1m9k83ELy1m9k83-Py83Sy1n83ELyn1m1l8");
    string_constant_230 = 
	    STATIC_STRING("33My01n83lIy1n1m9k83F*y1m9k83-Py83Ky1n83F*yn1m1l833My01n83lIy1n1m9k83D5y1m9k83-Py8392y1n83D5yn1m1l833My01n83lIy1n1m9k83C=y1m9k83");
    string_constant_231 = 
	    STATIC_STRING("-Py838Jy1n83C=yn1m1l833My01n83lIy1n1m9k83Awy1m9k83-Py838xy1n83Awyn1m1l833My01n83lIy1n1m9k837wy1m9k83-Py837wy1n837wyn1m1l836dy01n");
    string_constant_232 = 
	    STATIC_STRING("83lIy1n1m9k8385y1m9k83-Py83BUy1n8385yn1m1l836dy01n83lIy1n1m9k83Afy1m9k83-Py83B6y1n83Afyn1m1l836dy01n83lIy1n1m9k83-s3y1m9k83-Py83");
    string_constant_233 = 
	    STATIC_STRING("A7y1n833jyn1m1l836sy01n83lIy1n1m9k833py1m9k83-Py832vy1n833pyn1m1l836sy01n83lIy1n1m9k833qy1m9k83-Py832wy1n833qyn1m1l836sy01n83lIy");
    string_constant_234 = 
	    STATIC_STRING("1n1m9k83-Tqy1m9k83-Py83-xy1n83C1yn1m1l837-y01n83lIy1n1m9k83Evy1m9k83-Py83Ky1n83Evyn1m1l837-y01n83lIy1n1m9k83Fxy1m9k83-Py832fy1n8");
    string_constant_235 = 
	    STATIC_STRING("3Fxyn1m1l837-y01n83lIy1n1m9k83Cdy1m9k83-Py832fy1n83Cdyn1m1l837-y01n83lIy1n1m9k83Bky1m9k83-Py832fy1n83Bkyn1m1l837-y01n83lIy1n1m9k");
    string_constant_236 = 
	    STATIC_STRING("83-Jky1m9k83-Py83AOy1n83B9yn1m1l834oy01n83lIy1n1m9k83-Nky1m9k83-Py83APy1n83BMyn1m1l834oy01n83lIy1p1m9k83-J6y1m9k83=Iy1m9k834oy1m");
    string_constant_237 = 
	    STATIC_STRING("9k83-Py83-Yy1n83Fkyp1m1l834oy01n83lIy1n1m9k83-bxy1m9k83-Py839Ey1n839Eyn1m1l837Uy01n83lIy1n1m9k83-aRy1m9k83-Py83Ky1n83FLyn1m1l837");
    string_constant_238 = 
	    STATIC_STRING("Uy01n83lIy1n1m9k83-U7y1m9k83-Py83-Gy1n83BDyn1m1l837Ky01n83lIy1n1m9k83-nry1m9k83-Py83-Gy1n83BAyn1m1l837Ky01n83lIy1n1m9k83Bly1m9k8");
    string_constant_239 = 
	    STATIC_STRING("3-Py838Qy1n83Blyn1m1l836ry01n83lIy1n1m9k83FQy1m9k83-Py8336y1n83FQyn1m1l835Cy01n83lIy1n1m9k83Bfy1m9k83-Py832iy1n83Bgyn1m1l837Dy01");
    string_constant_240 = 
	    STATIC_STRING("n83lIy1n1m9k83D*y1m9k83-Py833Py1n83D=yn1m1l837Dy01n83lIy1n1m9k83F3y1m9k83-Py8306y1n83F4yn1m1l837Dy01n83lIy1n1m9k83-o7y1m9k83-Py8");
    string_constant_241 = 
	    STATIC_STRING("3Ky1n83Exyn1m1l837Dy01n83lIy1n1m9k83F1y1m9k83-Py839xy1n83F1yn1m1l837Dy01n83lIy1n1m9k83BBy1m9k83-Py833Vy1n83BByn1m1l836oy01n83lIy");
    string_constant_242 = 
	    STATIC_STRING("1n1m9k83COy1m9k83-Py838vy1n83COyn1m1l838ty01n83lIy1n1m9k831ay1m9k83-Py831ay1n831ayn1m1m839-y839*y01n83lIy1n1m9k838Xy1m9k83-Py838");
    string_constant_243 = 
	    STATIC_STRING("Xy1n838Xyn1m1l838Wy01n83lIy1n1m9k83*Dy1m9k83-Py83*Dy1n83*Dyn1m1l838Vy01n83lIy1n1m9k83Dby1m9k83-Py832fy1n83Dbyn1m1l8305y01n83lIy1");
    string_constant_244 = 
	    STATIC_STRING("n1m9k838wy1m9k83-Py838wy1n838wyn1m1l8305y01n83lIy1n1m9k83CSy1m9k83-Py833Ky1n83CSyn1m1l8305y01n83lIy1n1m9k83CQy1m9k83-Py833Iy1n83");
    string_constant_245 = 
	    STATIC_STRING("CQyn1m1l8305y01n83lIy1n1m9k83-mGy1m9k83-Py833Jy1n83Elyn1m1l8305y01n83lIy1n1m9k83CRy1m9k83-Py833Jy1n83CRyn1m1l8305y01n83lIy1n1m9k");
    string_constant_246 = 
	    STATIC_STRING("83-Z1y1m9k83-Py833Ly1n83Clyn1m1l8304y01n83lIy1n1m9k838uy1m9k83-Py838uy1n838uyn1m1l8304y01n83lIy1n1m9k83CPy1m9k83-Py833Ky1n83CPyn");
    string_constant_247 = 
	    STATIC_STRING("1m1l8304y01n83lIy1n1m9k83CMy1m9k83-Py833Iy1n83CMyn1m1l8304y01n83lIy1n1m9k83CNy1m9k83-Py833Jy1n83CNyn1m1l8304y01n83lIy1n1m9k83C*y");
    string_constant_248 = 
	    STATIC_STRING("1m9k83-Py83Ky1n83C*yn1m1l83=8y01n83lIy1n1m9k83ENy1m9k83-Py83Ky1n83ENyn1m1l83=8y01n83lIy1n1m9k83Ejy1m9k83-Py839oy1n83Ejyn1m1l83=8");
    string_constant_249 = 
	    STATIC_STRING("y01n83lIy1n1m9k83CYy1m9k83-Py839=y1n83CYyn1m1l83=8y01n83lIy1n1m9k8347y1m9k83-Py832uy1n8347yn1m1l8328y01n83lIy1n1m9k8397y1m9k83-P");
    string_constant_250 = 
	    STATIC_STRING("y8397y1n8397yn1m1l8328y01n83lIy1n1m9k83D4y1m9k83-Py833by1n83D4yn1m1m83=8y8301y01n83lIy1n1m9k83D2y1m9k83-Py83AEy1n83D2yn1m1m83=8y");
    string_constant_251 = 
	    STATIC_STRING("8301y01n83lIy1n1m9k83D7y1m9k83-Py833by1n83D7yn1m1l83=8y01n83lIy1n1m9k833ty1m9k83-Py83Ky1n833tyn1m1l8328y01n83lIy1p1m9k83-J6y1m9k");
    string_constant_252 = 
	    STATIC_STRING("83=Iy1m9k836Zy1m9k83-Py83-Yy1n833dyp1m1l836Zy01n83lIy1n1m9k83-wAy1m9k83-Py83-qy1n83Fpyn1m1l832ey01n83lIy1n1m9k830Cy1m9k83-Py8383");
    string_constant_253 = 
	    STATIC_STRING("y1n83Aiyn1m1l832ey01n83lIy1p1m9k83-hfy1m9k83=Iy1m9k836ey1m9k83-Py83-qy1n83ECyp1m1l836ey01n83lIy1p1m9k83-hRy1m9k83=Iy1m9k836ey1m9");
    string_constant_254 = 
	    STATIC_STRING("k83-Py83-qy1n83E8yp1m1l836ey01n83lIy1p1m9k83-hfy1m9k83=Iy1m9k837Jy1m9k83-Py83-qy1n83Foyp1m1l837Jy01n83lIy1n1m9k83-6Sy1m9k83-Py83");
    string_constant_255 = 
	    STATIC_STRING("7Gy1n83Dcyn1m1l837Qy01n83lIy1n1m9k83-6ly1m9k83-Py837Gy1n83Doyn1m1l837Qy01n83lIy1n1m9k83F-y1m9k83-Py83Ky1n83F-yn1m1l837Qy01n83lIy");
    string_constant_256 = 
	    STATIC_STRING("1n1m9k83ATy1m9k83-Py83ATy1n83ATyn1m1l837Qy01n83lIy1n1m9k83C5y1m9k83-Py83AJy1n83C5yn1m1l837ay01n83lIy1n1m9k83B+y1m9k83-Py83Ky1n83");
    string_constant_257 = 
	    STATIC_STRING("B+yn1m1l837ay01n83lIy1n1m9k83Ccy1m9k83-Py83Ky1n83Ccyn1m1l837ay01n83lIy1n1m9k83-CNy1m9k83-Py832gy1n83Etyn1m1l832Jy01n83lIy1n1m9k8");
    string_constant_258 = 
	    STATIC_STRING("38My1m9k83-Py838My1n838Myn1m1l832Jy01n83lIy1n1m9k838Ny1m9k83-Py838Ny1n838Nyn1m1l832Jy01n83lIy1n1m9k837sy1m9k83-Py837sy1n83Eqyn1m");
    string_constant_259 = 
	    STATIC_STRING("1l832Jy01n83lIy1n1m9k83Esy1m9k83-Py83-Yy1n83Esyn1m1l832Jy01n83lIy1n1m9k83-Quy1m9k83-Py83-ey1n83Axyn1m1l832Jy01n83lIy1n1m9k83FPy1");
    string_constant_260 = 
	    STATIC_STRING("m9k83-Py8398y1n83FPyn1m1l832Jy01n83lIy1n1m9k83-tAy1m9k83-Py83A+y1n83FNyn1m1l832Ly0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_simulation_subtable_with_specific_class_and_install);
    push_optimized_constant(Qmessage);
    System_class_overrides_for_class_definition = 
	    regenerate_optimized_constant(nconc2(list(50,
	    string_constant_193,string_constant_194,string_constant_195,
	    string_constant_196,string_constant_197,string_constant_198,
	    string_constant_199,string_constant_200,string_constant_201,
	    string_constant_202,string_constant_203,string_constant_204,
	    string_constant_205,string_constant_206,string_constant_207,
	    string_constant_208,string_constant_209,string_constant_210,
	    string_constant_211,string_constant_212,string_constant_213,
	    string_constant_214,string_constant_215,string_constant_216,
	    string_constant_217,string_constant_218,string_constant_219,
	    string_constant_220,string_constant_221,string_constant_222,
	    string_constant_223,string_constant_224,string_constant_225,
	    string_constant_226,string_constant_227,string_constant_228,
	    string_constant_229,string_constant_230,string_constant_231,
	    string_constant_232,string_constant_233,string_constant_234,
	    string_constant_235,string_constant_236,string_constant_237,
	    string_constant_238,string_constant_239,string_constant_240,
	    string_constant_241,string_constant_242),list(18,
	    string_constant_243,string_constant_244,string_constant_245,
	    string_constant_246,string_constant_247,string_constant_248,
	    string_constant_249,string_constant_250,string_constant_251,
	    string_constant_252,string_constant_253,string_constant_254,
	    string_constant_255,string_constant_256,string_constant_257,
	    string_constant_258,string_constant_259,string_constant_260)));
    add_grammar_rules_function(System_class_overrides_for_class_definition);
    SET_SYMBOL_FUNCTION(Qsecond_none,STATIC_FUNCTION(second_none,NIL,FALSE,
	    1,1));
    Qsimulation_frame_qm = STATIC_SYMBOL("SIMULATION-FRAME\?",AB_package);
    set_property_value_function(get_symbol_properties_function(Qsimulation_frame_qm),
	    Qtype_specification_simple_expansion,Qnil);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    Qsimulation_subtable = STATIC_SYMBOL("SIMULATION-SUBTABLE",AB_package);
    list_constant_52 = STATIC_LIST((SI_Long)2L,Qab_class,Qsimulation_subtable);
    define_type_specification_explicit_complex_type(Qsimulation_frame_qm,
	    list_constant_52);
    simulation_frame_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(simulation_frame_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsimulation_frame_qm,
	    simulation_frame_qm_evaluation_getter_1);
    SET_SYMBOL_FUNCTION(Qmake_simulation_subtable_and_install,
	    STATIC_FUNCTION(make_simulation_subtable_and_install,NIL,FALSE,
	    0,0));
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    SET_SYMBOL_FUNCTION(Qmake_simulation_subtable_with_specific_class_and_install,
	    STATIC_FUNCTION(make_simulation_subtable_with_specific_class_and_install,
	    NIL,FALSE,1,1));
    string_constant_20 = 
	    STATIC_STRING("The class ~A cannot be instantiated within ~\n       attribute ~NS because it is not a defined class.");
    string_constant_21 = 
	    STATIC_STRING("The class ~A cannot be instantiated within attribute ~\n         ~NS because it is not a subclass of the type ~\n         specification for this attribute, class ~A.");
    string_constant_22 = 
	    STATIC_STRING("The class ~A cannot be instantiated within attribute ~\n       ~NS because the type-specification class, ~A,  has not yet ~\n       been defined.");
    Qattribute_nesting_depth = STATIC_SYMBOL("ATTRIBUTE-NESTING-DEPTH",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qattribute_nesting_depth,
	    Attribute_nesting_depth);
    Qgrammar6a = STATIC_SYMBOL("GRAMMAR6A",AB_package);
    record_system_variable(Qattribute_nesting_depth,Qgrammar6a,
	    FIX((SI_Long)1L),Qnil,Qnil,Qnil,Qnil);
    Qrecursive_attribute_nesting_has_occurred_qm = 
	    STATIC_SYMBOL("RECURSIVE-ATTRIBUTE-NESTING-HAS-OCCURRED\?",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qrecursive_attribute_nesting_has_occurred_qm,
	    Recursive_attribute_nesting_has_occurred_qm);
    record_system_variable(Qrecursive_attribute_nesting_has_occurred_qm,
	    Qgrammar6a,Nil,Qnil,Qnil,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinstantiate_variable,
	    STATIC_FUNCTION(instantiate_variable,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qinstantiate_object_in_attribute,
	    STATIC_FUNCTION(instantiate_object_in_attribute,NIL,FALSE,1,1));
    string_constant_23 = 
	    string_append2(STATIC_STRING("An infinite set of ~A nested inside each other cannot ~\n            be instantiated as attributes. The process has been stopped ~\n            at a depth of ~d.  This ~A is of "),
	    STATIC_STRING("class ~A."));
    string_constant_24 = STATIC_STRING("variables or parameters");
    string_constant_25 = STATIC_STRING("objects");
    string_constant_26 = STATIC_STRING("variable or parameter");
    string_constant_27 = STATIC_STRING("object");
    Qnot_user_instantiable = STATIC_SYMBOL("NOT-USER-INSTANTIABLE",AB_package);
    string_constant_28 = STATIC_STRING("The class ~a is not instantiable.");
    string_constant_29 = string_appendn(3,
	    STATIC_STRING("The class ~a cannot be instantiated because it is not an ~\n              instantiable variable or parameter.  If ~a is an instantiable ~\n              object class that is not"),
	    STATIC_STRING(" a variable or parameter, You may want ~\n              to change the attribute declaration to use the IS AN INSTANCE ~\n              OF syntax instead of the IS GIVEN BY synta"),
	    STATIC_STRING("x."));
    string_constant_30 = 
	    STATIC_STRING("~A cannot instantiated as an attribute because it is not ~\n            an instantiable object class.");
    string_constant_31 = 
	    STATIC_STRING("~A cannot be instantiated within an attribute because ~\n              it is not a defined class.");
    Qnew_class = STATIC_SYMBOL("NEW-CLASS",AB_package);
    Qcompile_new_class_for_slot = 
	    STATIC_SYMBOL("COMPILE-NEW-CLASS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_new_class_for_slot,
	    STATIC_FUNCTION(compile_new_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qnew_class,
	    SYMBOL_FUNCTION(Qcompile_new_class_for_slot),Qslot_value_compiler);
    mutate_global_property(Qnew_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qitem_class = STATIC_SYMBOL("ITEM-CLASS",AB_package);
    Qcompile_item_class_for_slot = 
	    STATIC_SYMBOL("COMPILE-ITEM-CLASS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_item_class_for_slot,
	    STATIC_FUNCTION(compile_item_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qitem_class,
	    SYMBOL_FUNCTION(Qcompile_item_class_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qitem_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qconnection_class = STATIC_SYMBOL("CONNECTION-CLASS",AB_package);
    Qcompile_connection_class_for_slot = 
	    STATIC_SYMBOL("COMPILE-CONNECTION-CLASS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_connection_class_for_slot,
	    STATIC_FUNCTION(compile_connection_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qconnection_class,
	    SYMBOL_FUNCTION(Qcompile_connection_class_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qconnection_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qobject_class = STATIC_SYMBOL("OBJECT-CLASS",AB_package);
    Qcompile_object_class_for_slot = 
	    STATIC_SYMBOL("COMPILE-OBJECT-CLASS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_object_class_for_slot,
	    STATIC_FUNCTION(compile_object_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qobject_class,
	    SYMBOL_FUNCTION(Qcompile_object_class_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qobject_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qmessage_class = STATIC_SYMBOL("MESSAGE-CLASS",AB_package);
    Qcompile_message_class_for_slot = 
	    STATIC_SYMBOL("COMPILE-MESSAGE-CLASS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_message_class_for_slot,
	    STATIC_FUNCTION(compile_message_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qmessage_class,
	    SYMBOL_FUNCTION(Qcompile_message_class_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qmessage_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    list_constant_53 = STATIC_CONS(Qobject,Qnil);
    Classes_for_object_definition = list_constant_53;
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_54 = STATIC_CONS(Qitem,Qnil);
    Classes_for_class_definition = list_constant_54;
    Qobject_definition = STATIC_SYMBOL("OBJECT-DEFINITION",AB_package);
    Qmessage_definition = STATIC_SYMBOL("MESSAGE-DEFINITION",AB_package);
    Qconnection_definition = STATIC_SYMBOL("CONNECTION-DEFINITION",AB_package);
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    string_constant_32 = 
	    STATIC_STRING("The name of an instantiated class cannot revert to NONE. ~\n                   To make this change, the instances must be deleted first.");
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    array_constant_10 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)11L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)13L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)14L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)15L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)17L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)21L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)22L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)25L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)28L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)29L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)30L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)31L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)33L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)34L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)36L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)37L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)38L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)39L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)40L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)41L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)42L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)46L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)47L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)8L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)11L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)16L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)18L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)20L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)21L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)23L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)24L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)25L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)26L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)28L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)29L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)30L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)31L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)33L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)34L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)35L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)36L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)37L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)39L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)40L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)46L,(SI_Long)41L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)47L,(SI_Long)57344L);
    string_constant_33 = 
	    STATIC_STRING("This class cannot be named ~A because then the class-definition for ~A ~\n                         would have two direct superiors named ~A.");
    string_constant_34 = 
	    STATIC_STRING("This class cannot be named ~A because then an unnamed class-definition ~\n                         would have two direct superiors named ~A.");
    string_constant_35 = 
	    STATIC_STRING("You may not edit the attributes of an ~\n                     automatically created junction block");
    string_constant_36 = 
	    STATIC_STRING("You may not use ~a as the name of a class because it specifies a type in G2.");
    Qsubclass = STATIC_SYMBOL("SUBCLASS",AB_package);
    Qcompile_class_for_slot = STATIC_SYMBOL("COMPILE-CLASS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_class_for_slot,
	    STATIC_FUNCTION(compile_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qab_class,
	    SYMBOL_FUNCTION(Qcompile_class_for_slot),Qslot_value_compiler);
    mutate_global_property(Qab_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qlist_of_classes = STATIC_SYMBOL("LIST-OF-CLASSES",AB_package);
    Qlist_of_item_classes = STATIC_SYMBOL("LIST-OF-ITEM-CLASSES",AB_package);
    Qlist_of_object_classes = STATIC_SYMBOL("LIST-OF-OBJECT-CLASSES",
	    AB_package);
    Qlist_of_connection_classes = 
	    STATIC_SYMBOL("LIST-OF-CONNECTION-CLASSES",AB_package);
    Qlist_of_message_classes = STATIC_SYMBOL("LIST-OF-MESSAGE-CLASSES",
	    AB_package);
    list_constant_55 = STATIC_LIST((SI_Long)5L,Qlist_of_classes,
	    Qlist_of_item_classes,Qlist_of_object_classes,
	    Qlist_of_connection_classes,Qlist_of_message_classes);
    if (Grammar_categories_getting_choose_existing_class_feature == UNBOUND)
	Grammar_categories_getting_choose_existing_class_feature = 
		list_constant_55;
    Qfoundation_class = STATIC_SYMBOL("FOUNDATION-CLASS",AB_package);
    add_grammar_rules_for_list(5,Qlist_of_classes,Qfoundation_class,Qcm,
	    Nil,Qnone);
    add_grammar_rules_for_list(5,Qlist_of_item_classes,Qfoundation_class,
	    Qcm,Nil,Qnone);
    Qfoundation_object_class = STATIC_SYMBOL("FOUNDATION-OBJECT-CLASS",
	    AB_package);
    add_grammar_rules_for_list(5,Qlist_of_object_classes,
	    Qfoundation_object_class,Qcm,Nil,Qnone);
    Qfoundation_connection_class = 
	    STATIC_SYMBOL("FOUNDATION-CONNECTION-CLASS",AB_package);
    add_grammar_rules_for_list(5,Qlist_of_connection_classes,
	    Qfoundation_connection_class,Qcm,Nil,Qnone);
    Qfoundation_message_class = STATIC_SYMBOL("FOUNDATION-MESSAGE-CLASS",
	    AB_package);
    add_grammar_rules_for_list(5,Qlist_of_message_classes,
	    Qfoundation_message_class,Qcm,Nil,Qnone);
    Qwrite_list_of_classes_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-CLASSES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_classes_from_slot,
	    STATIC_FUNCTION(write_list_of_classes_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlist_of_classes,
	    SYMBOL_FUNCTION(Qwrite_list_of_classes_from_slot),
	    Qslot_value_writer);
    Qwrite_list_of_item_classes_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-ITEM-CLASSES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_item_classes_from_slot,
	    STATIC_FUNCTION(write_list_of_item_classes_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qlist_of_item_classes,
	    SYMBOL_FUNCTION(Qwrite_list_of_item_classes_from_slot),
	    Qslot_value_writer);
    Qwrite_list_of_object_classes_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-OBJECT-CLASSES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_object_classes_from_slot,
	    STATIC_FUNCTION(write_list_of_object_classes_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlist_of_object_classes,
	    SYMBOL_FUNCTION(Qwrite_list_of_object_classes_from_slot),
	    Qslot_value_writer);
    Qwrite_list_of_connection_classes_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-CONNECTION-CLASSES-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_connection_classes_from_slot,
	    STATIC_FUNCTION(write_list_of_connection_classes_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlist_of_connection_classes,
	    SYMBOL_FUNCTION(Qwrite_list_of_connection_classes_from_slot),
	    Qslot_value_writer);
    Qwrite_list_of_message_classes_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-MESSAGE-CLASSES-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_message_classes_from_slot,
	    STATIC_FUNCTION(write_list_of_message_classes_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qlist_of_message_classes,
	    SYMBOL_FUNCTION(Qwrite_list_of_message_classes_from_slot),
	    Qslot_value_writer);
    Qthis_unnamed_class = STATIC_SYMBOL("THIS-UNNAMED-CLASS",AB_package);
    string_constant_37 = STATIC_STRING("none");
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qwrite_class_inheritance_path_of_definition_from_slot = 
	    STATIC_SYMBOL("WRITE-CLASS-INHERITANCE-PATH-OF-DEFINITION-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_class_inheritance_path_of_definition_from_slot,
	    STATIC_FUNCTION(write_class_inheritance_path_of_definition_from_slot,
	    NIL,FALSE,2,2));
    mutate_global_property(Qclass_inheritance_path_of_definition,
	    SYMBOL_FUNCTION(Qwrite_class_inheritance_path_of_definition_from_slot),
	    Qslot_value_writer);
    string_constant_38 = STATIC_STRING(",~%");
    Qlist_of_slots = STATIC_SYMBOL("LIST-OF-SLOTS",AB_package);
    Qwrite_list_of_slots_from_slot = 
	    STATIC_SYMBOL("WRITE-LIST-OF-SLOTS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_list_of_slots_from_slot,
	    STATIC_FUNCTION(write_list_of_slots_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qlist_of_slots,
	    SYMBOL_FUNCTION(Qwrite_list_of_slots_from_slot),
	    Qslot_value_writer);
    string_constant_261 = 
	    STATIC_STRING("1x1m83-99y1m9k83pPy1m83-99y1m9k83w7y1m83-99y1m9k838Vy1m83-99y1m9k8301y1m83-99y1m9k838Wy1m83-99y1m9k838ty1m83-99y1m9k8304y1m83-99");
    string_constant_262 = 
	    STATIC_STRING("y1m9k8305y1m83-99y1m9k839-y1m83-99y1m9k83-XTy1m83-99y1m9k839*y1m83-99y1m9k83-goy1m83-99y1m9k83-E1y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_261,
	    string_constant_262)));
    string_constant_263 = 
	    STATIC_STRING("1o1m83EQy1m9k83Zy1m83EQy83-jZy1m83-jZy83-99y1o83-jZy1n83-99y1m9k83vy83-jZy1n83vyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_263));
    Qcapabilities_and_restrictions = 
	    STATIC_SYMBOL("CAPABILITIES-AND-RESTRICTIONS",AB_package);
    Qput_capabilities_and_restrictions = 
	    STATIC_SYMBOL("PUT-CAPABILITIES-AND-RESTRICTIONS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_capabilities_and_restrictions,
	    STATIC_FUNCTION(put_capabilities_and_restrictions,NIL,FALSE,3,3));
    mutate_global_property(Qcapabilities_and_restrictions,
	    SYMBOL_FUNCTION(Qput_capabilities_and_restrictions),Qslot_putter);
    Qgsi_interface = STATIC_SYMBOL("GSI-INTERFACE",AB_package);
    Qg2_to_g2_data_interface = STATIC_SYMBOL("G2-TO-G2-DATA-INTERFACE",
	    AB_package);
    Qgfi_input_interface = STATIC_SYMBOL("GFI-INPUT-INTERFACE",AB_package);
    Qgfi_output_interface = STATIC_SYMBOL("GFI-OUTPUT-INTERFACE",AB_package);
    Qgsi_data_service = STATIC_SYMBOL("GSI-DATA-SERVICE",AB_package);
    Qgsi_message_service = STATIC_SYMBOL("GSI-MESSAGE-SERVICE",AB_package);
    Qgfi_data_service = STATIC_SYMBOL("GFI-DATA-SERVICE",AB_package);
    Qg2_to_g2_data_service = STATIC_SYMBOL("G2-TO-G2-DATA-SERVICE",AB_package);
    Qg2_meter_data_service = STATIC_SYMBOL("G2-METER-DATA-SERVICE",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)9L,Qgsi_interface,
	    Qg2_to_g2_data_interface,Qgfi_input_interface,
	    Qgfi_output_interface,Qgsi_data_service,Qgsi_message_service,
	    Qgfi_data_service,Qg2_to_g2_data_service,Qg2_meter_data_service);
    Qactivatable_subworkspace = STATIC_SYMBOL("ACTIVATABLE-SUBWORKSPACE",
	    AB_package);
    Qexternal_simulation = STATIC_SYMBOL("EXTERNAL-SIMULATION",AB_package);
    Qmanual_connections = STATIC_SYMBOL("MANUAL-CONNECTIONS",AB_package);
    Qsubworkspace_connection_posts = 
	    STATIC_SYMBOL("SUBWORKSPACE-CONNECTION-POSTS",AB_package);
    Qactivatible_subworkspace = STATIC_SYMBOL("ACTIVATIBLE-SUBWORKSPACE",
	    AB_package);
    Qno_manual_connections = STATIC_SYMBOL("NO-MANUAL-CONNECTIONS",AB_package);
    Qprevious_capabilities = STATIC_SYMBOL("PREVIOUS-CAPABILITIES",AB_package);
    Qwrite_previous_capabilities_from_slot = 
	    STATIC_SYMBOL("WRITE-PREVIOUS-CAPABILITIES-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_previous_capabilities_from_slot,
	    STATIC_FUNCTION(write_previous_capabilities_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qprevious_capabilities,
	    SYMBOL_FUNCTION(Qwrite_previous_capabilities_from_slot),
	    Qslot_value_writer);
    Qcompile_previous_capabilities_for_slot = 
	    STATIC_SYMBOL("COMPILE-PREVIOUS-CAPABILITIES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_previous_capabilities_for_slot,
	    STATIC_FUNCTION(compile_previous_capabilities_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qprevious_capabilities,
	    SYMBOL_FUNCTION(Qcompile_previous_capabilities_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qprevious_capabilities,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_264 = 
	    STATIC_STRING("13ay1m83EAy1m9k83Zy1m83EAy83-d-y1m83-d-y83-hay1o83-d-y1n83-hay1m9k83-Zy83-d-y1nmln9l1n83-hay1q1m9k831Dy1m9k8p1m9k83=Iy1m9k834ay1");
    string_constant_265 = 
	    STATIC_STRING("m9k83-Py831ry1n831ryq834ay1n83-hay1q1m9k831Dy1m9k8p1m9k83=Iy1m9k8315y1m9k83-Py832Fy1n831ryq8315y1n83-hay1q1m9k831Dy1m9k8p1m9k83=");
    string_constant_266 = 
	    STATIC_STRING("Iy1m9k8314y1m9k83-Py832Fy1n831ryq8314y1n83-hay1o1m9k83-GJy1m9k83-oy1m9k83-Py83-oy1m830uyo1n83-hay1o1m9k83-GJy1m9k83-oy1m9k83-Py1");
    string_constant_267 = 
	    STATIC_STRING("m9k832by1m830uyo1n83-hay1o1m9k83-GJy1m9k83-oy1m9k83-Py1m9k83A3y1m830uyo1n83-hay1n1m9k83-E3y1m9k83n4y1m9k83b3y1m837Py1m83*Ay9m1n8");
    string_constant_268 = 
	    STATIC_STRING("3-hay1o1m9k831Dy1m9k839wy1m9k83-Py83*My1m83*Myo1o83-hay1p1m9k83Py1m9k837cy1m9k83-oy1m9k83-Py8376y1m83gYyp9n1n83-hay1p1m9k83Py1m9");
    string_constant_269 = 
	    STATIC_STRING("k837cy1m9k83-oy1m9k83-Py1m9k83Zy1m83gYy01n83-hay1p1m9k836xy1m9k83-1ay1m9k83-DVy1m9k83-Py830hy1m83iTyp1n83-hay1p1m9k83-89y1m9k83=");
    string_constant_270 = 
	    STATIC_STRING("Iy1m9k83*dy1m9k83-Py83*Ey1n83-Eyp83*dy1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834Ky1m9k83-Py836Ny1n83j0yq834Ky1n83-hay1q1m9k83C");
    string_constant_271 = 
	    STATIC_STRING("xy1m9k83*ly1m9k83=Iy1m9k8315y1m9k83-Py837Gy1n83j0yq8315y1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834-y1m9k83-Py83wRy1n83j0yq834-");
    string_constant_272 = 
	    STATIC_STRING("y1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834Ey1m9k83-Py830iy1n83j0yq834Ey1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834fy1m9k83-P");
    string_constant_273 = 
	    STATIC_STRING("y83A4y1n83j0yq834fy1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834jy1m9k83-Py83-xy1n83j0yq834jy1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=I");
    string_constant_274 = 
	    STATIC_STRING("y1m9k834Jy1m9k83-Py83-hy1n83j0yq834Jy1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k8314y1m9k83-Py83-Hy1n83j0yq8314y1n83-hay1q1m9k83Cx");
    string_constant_275 = 
	    STATIC_STRING("y1m9k83*ly1m9k83=Iy1m9k834+y1m9k83-Py9o1n83j0yq834+y1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834Dy1m9k83-Py83Sy1n83j0yq834Dy1n83");
    string_constant_276 = 
	    STATIC_STRING("-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834ey1m9k83-Py83-2y1n83j0yq834ey1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834iy1m9k83-Py83-U");
    string_constant_277 = 
	    STATIC_STRING("y1n83j0yq834iy1n83-hay1q1m9k83Cxy1m9k83*ly1m9k83=Iy1m9k834ay1m9k83-Py835Vy1n83j0yq834ay1n83-hay1q1m9k83Buy1m9k8p1m9k83=Iy1m9k834");
    string_constant_278 = 
	    STATIC_STRING("Gy1m9k83-Py83-Gy1n83*6yq834Gy1n83-hay1r1m9k837gy1m9k83gpy1m9k83h-y1m9k83=Iy1m9k831Zy1m9k83-Py83Ky1n8375yr831Zy1n83-hay1q1m9k83Bu");
    string_constant_279 = 
	    STATIC_STRING("y1m9k8p1m9k83=Iy1m9k834Fy1m9k83-Py83-Gy1n83-vyq834Fy1n83-hay1p1m9k837iy1m9k83=Iy1m9k831Yy1m9k83-Py835Ey1n835Eyp831Yy1n83-hay1q1m");
    string_constant_280 = 
	    STATIC_STRING("9k83Cxy1m9k9p1m9k83=Iy1m9k834Fy1m9k83-Py836jy1n83-wyq834Fy1n83-hay1q1m9k83Cxy1m9k9p1m9k83=Iy1m9k8316y1m9k83-Py830Qy1n83-wyq8316y");
    string_constant_281 = 
	    STATIC_STRING("1n83-hay1q1m9k83Cxy1m9k9p1m9k83=Iy1m9k831cy1m9k83-Py831dy1n83-wyq831cy1n83-hay1q1m9k83Cxy1m9k9p1m9k83=Iy1m9k833wy1m9k83-Py831Xy1");
    string_constant_282 = 
	    STATIC_STRING("n83-wyq833wy1n83-hay1q1m9k83Cxy1m9k9p1m9k83=Iy1m9k834dy1m9k83-Py831ky1n83-wyq834dy1n83-hay1q1m9k83Cxy1m9k9p1m9k83=Iy1m9k834hy1m9");
    string_constant_283 = 
	    STATIC_STRING("k83-Py837fy1n83-wyq834hy1n83-hay1q1m9k83Cxy1m9k9p1m9k83=Iy1m9k834ly1m9k83-Py831my1n83-wyq834ly");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qmake_simulation_subtable_and_install);
    push_optimized_constant(Qsecond_none);
    push_optimized_constant(Qfloat);
    push_optimized_constant(Qvalues);
    add_grammar_rules_function(regenerate_optimized_constant(list(20,
	    string_constant_264,string_constant_265,string_constant_266,
	    string_constant_267,string_constant_268,string_constant_269,
	    string_constant_270,string_constant_271,string_constant_272,
	    string_constant_273,string_constant_274,string_constant_275,
	    string_constant_276,string_constant_277,string_constant_278,
	    string_constant_279,string_constant_280,string_constant_281,
	    string_constant_282,string_constant_283)));
    Qold_default_settings = STATIC_SYMBOL("OLD-DEFAULT-SETTINGS",AB_package);
    Qcompile_old_default_settings_for_slot = 
	    STATIC_SYMBOL("COMPILE-OLD-DEFAULT-SETTINGS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_old_default_settings_for_slot,
	    STATIC_FUNCTION(compile_old_default_settings_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qold_default_settings,
	    SYMBOL_FUNCTION(Qcompile_old_default_settings_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qold_default_settings,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qdefault_settings = STATIC_SYMBOL("DEFAULT-SETTINGS",AB_package);
    Qput_default_settings = STATIC_SYMBOL("PUT-DEFAULT-SETTINGS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_default_settings,
	    STATIC_FUNCTION(put_default_settings,NIL,FALSE,3,3));
    mutate_global_property(Qdefault_settings,
	    SYMBOL_FUNCTION(Qput_default_settings),Qslot_putter);
    Quser_defined = STATIC_SYMBOL("USER-DEFINED",AB_package);
    string_constant_39 = STATIC_STRING(";~%");
    Qwrite_old_default_settings_from_slot = 
	    STATIC_SYMBOL("WRITE-OLD-DEFAULT-SETTINGS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_old_default_settings_from_slot,
	    STATIC_FUNCTION(write_old_default_settings_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qold_default_settings,
	    SYMBOL_FUNCTION(Qwrite_old_default_settings_from_slot),
	    Qslot_value_writer);
    string_constant_284 = STATIC_STRING("1l1m83EBy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_284));
    Qdirect_superiors_of_defined_class = 
	    STATIC_SYMBOL("DIRECT-SUPERIORS-OF-DEFINED-CLASS",AB_package);
    Qsuperior_class = STATIC_SYMBOL("SUPERIOR-CLASS",AB_package);
    Qput_superior_class = STATIC_SYMBOL("PUT-SUPERIOR-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_superior_class,
	    STATIC_FUNCTION(put_superior_class,NIL,FALSE,3,3));
    mutate_global_property(Qsuperior_class,
	    SYMBOL_FUNCTION(Qput_superior_class),Qslot_putter);
    Qold_superior_class = STATIC_SYMBOL("OLD-SUPERIOR-CLASS",AB_package);
    Qcompile_old_superior_class_for_slot = 
	    STATIC_SYMBOL("COMPILE-OLD-SUPERIOR-CLASS-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_old_superior_class_for_slot,
	    STATIC_FUNCTION(compile_old_superior_class_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qold_superior_class,
	    SYMBOL_FUNCTION(Qcompile_old_superior_class_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qold_superior_class,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    list_constant_15 = STATIC_LIST((SI_Long)4L,Qgsi_interface,
	    Qg2_to_g2_data_interface,Qgfi_input_interface,
	    Qgfi_output_interface);
    Qwrite_old_superior_class_from_slot = 
	    STATIC_SYMBOL("WRITE-OLD-SUPERIOR-CLASS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_old_superior_class_from_slot,
	    STATIC_FUNCTION(write_old_superior_class_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qold_superior_class,
	    SYMBOL_FUNCTION(Qwrite_old_superior_class_from_slot),
	    Qslot_value_writer);
    Qattributes_specific_to_class = 
	    STATIC_SYMBOL("ATTRIBUTES-SPECIFIC-TO-CLASS",AB_package);
    Qput_attributes_specific_to_class = 
	    STATIC_SYMBOL("PUT-ATTRIBUTES-SPECIFIC-TO-CLASS",AB_package);
    SET_SYMBOL_FUNCTION(Qput_attributes_specific_to_class,
	    STATIC_FUNCTION(put_attributes_specific_to_class,NIL,FALSE,3,3));
    mutate_global_property(Qattributes_specific_to_class,
	    SYMBOL_FUNCTION(Qput_attributes_specific_to_class),Qslot_putter);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    Qold_attribute_descriptions = 
	    STATIC_SYMBOL("OLD-ATTRIBUTE-DESCRIPTIONS",AB_package);
    Qwrite_old_attribute_descriptions_from_slot = 
	    STATIC_SYMBOL("WRITE-OLD-ATTRIBUTE-DESCRIPTIONS-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_old_attribute_descriptions_from_slot,
	    STATIC_FUNCTION(write_old_attribute_descriptions_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qold_attribute_descriptions,
	    SYMBOL_FUNCTION(Qwrite_old_attribute_descriptions_from_slot),
	    Qslot_value_writer);
    Qindexed_attributes_for_definition = 
	    STATIC_SYMBOL("INDEXED-ATTRIBUTES-FOR-DEFINITION",AB_package);
    string_constant_40 = STATIC_STRING(" is ");
    string_constant_41 = STATIC_STRING(" is a symbol");
    string_constant_42 = STATIC_STRING("~( has values ~a or ~a~)");
    string_constant_43 = STATIC_STRING(" (default is ~A)");
    string_constant_44 = STATIC_STRING(" has values ");
    string_constant_45 = STATIC_STRING("or");
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    string_constant_46 = STATIC_STRING(" and");
    string_constant_47 = STATIC_STRING(" is given by ");
    string_constant_48 = STATIC_STRING(" is an instance of ");
    string_constant_49 = STATIC_STRING(", with an index");
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qtrue,Qfalse);
    Qindexed = STATIC_SYMBOL("INDEXED",AB_package);
    Qfix_old_attribute_description = 
	    STATIC_SYMBOL("FIX-OLD-ATTRIBUTE-DESCRIPTION",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_old_attribute_description,
	    STATIC_FUNCTION(fix_old_attribute_description,NIL,FALSE,2,2));
    Qcheck_range_of_element = STATIC_SYMBOL("CHECK-RANGE-OF-ELEMENT",
	    AB_package);
    Qcut_out_fourth_element = STATIC_SYMBOL("CUT-OUT-FOURTH-ELEMENT",
	    AB_package);
    Qmemq_2_cdddr = STATIC_SYMBOL("MEMQ-2-CDDDR",AB_package);
    Qmemq_2_cddddr = STATIC_SYMBOL("MEMQ-2-CDDDDR",AB_package);
    string_constant_285 = 
	    STATIC_STRING("13Qy1m83=Zy1m9k83=Yy1m83=Zy1m9k83=ay1m83E9y1m9k83Zy1m83E9y83-hZy1m83-hZy83-hYy1o83-hZy1n83-hYy1m9k83-Zy83-hZy1nmln9l1m83-hYy83*m");
    string_constant_286 = 
	    STATIC_STRING("y1o83-hYy1n83*my1m9k83*Iy83-82y2lln1m9m01p83-hYy1o83*my1m9k83*Iy83-Hy1m9k83=Oy2mln83-hy1o9nmjl1m9m01o83-hYy1n83*my1m9k83*Iy83-2y");
    string_constant_287 = 
	    STATIC_STRING("2lln1m9m01n83-hYy1q83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1nl1n83*Ay9oq01n83-hYy1r83*my1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83");
    string_constant_288 = 
	    STATIC_STRING("=Zy83-Gy1nl1n83*Ay9pr01n83-hYy1q83*my1m9k831by1m9k9q83nYy1m9k83=Uy83nYy1pl083-2yoq1o83-hYy1o83*my1m9k831by1m9k9q83nZy2nl083-2yo9");
    string_constant_289 = 
	    STATIC_STRING("r1o83-hYy1v83*my1m9k831by1m9k9q83nYy1m9k83=Uy83nYy1m9k83-9y1m9k83Py1m9k83*Iy83nYy1m9k83-Ay1plu83-2yoq9s1p83-hYy1t83*my1m9k831by1");
    string_constant_290 = 
	    STATIC_STRING("m9k9q83nZy1m9k83-9y1m9k83Py1m9k83*Iy83nYy1m9k83-Ay2nls83-2yo9r9s1n83-hYy1w83*my1m9k831by1m9k9q83nYy1m9k83=Uy83nYy1m9k83-ty1m9k83");
    string_constant_291 = 
	    STATIC_STRING("*Iy1m9k8344y1m9k83*ty83=Zy837dy1pl1n83*Ay9ow83-2yoq1o83-hYy1u83*my1m9k831by1m9k9q83nZy1m9k83-ty1m9k83*Iy1m9k8344y1m9k83*ty83=Zy8");
    string_constant_292 = 
	    STATIC_STRING("37dy2nl1n83*Ay9ou83-2yo9r1n83-hYy1p83*my1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1ol001l83-=Ry1o83-hYy1r83*my1m9k83*Iy83-82y1m9k83vy1");
    string_constant_293 = 
	    STATIC_STRING("m9k83=Fy1m9k83=ay1m9k83-=Oy2lln1m9m8k1p83-hYy1s83*my1m9k83*Iy83-Hy1m9k83=Oy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2mln83-hy1o9nmjl1");
    string_constant_294 = 
	    STATIC_STRING("m9m8k1o83-hYy1r83*my1m9k83*Iy83-2y1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2lln1m9m8k1n83-hYy1u83*my1m9k83*Iy1m9k8344y1m9k83*ty83=Zy8");
    string_constant_295 = 
	    STATIC_STRING("37dy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1ol1n83*Ay9oq01l83-=Ry1n83-hYy1v83*my1m9k83*Iy1m9k83=ay1m9k831Ly1m9k83-Ty83=Zy83-Gy1m9k8");
    string_constant_296 = 
	    STATIC_STRING("3vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1ol1n83*Ay9pr01l83-=Ry1n83-hYy1u83*my1m9k831by1m9k9q83nYy1m9k83=Uy83nYy1m9k83vy1m9k83=Fy1m9k83=ay");
    string_constant_297 = 
	    STATIC_STRING("1m9k83-=Oy1ql083-2y1l83-=Ryoq1o83-hYy1s83*my1m9k831by1m9k9q83nZy1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2ol083-2y1l83-=Ryo9t1o83-hYy");
    string_constant_298 = 
	    STATIC_STRING("1z83*my1m9k831by1m9k9q83nYy1m9k83=Uy83nYy1m9k83-9y1m9k83Py1m9k83*Iy83nYy1m9k83-Ay1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy1qlu83-2y1l");
    string_constant_299 = 
	    STATIC_STRING("83-=Ryoq9u1p83-hYy1x83*my1m9k831by1m9k9q83nZy1m9k83-9y1m9k83Py1m9k83*Iy83nYy1m9k83-Ay1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2ols83-");
    string_constant_300 = 
	    STATIC_STRING("2y1l83-=Ryo9t9u1n83-hYy13Cy83*my1m9k831by1m9k9q83nYy1m9k83=Uy83nYy1m9k83-ty1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837dy1m9k83vy1m9k83=F");
    string_constant_301 = 
	    STATIC_STRING("y1m9k83=ay1m9k83-=Oy1ql1n83*Ay9ow83-2y1l83-=Ryoq1o83-hYy1y83*my1m9k831by1m9k9q83nZy1m9k83-ty1m9k83*Iy1m9k8344y1m9k83*ty83=Zy837d");
    string_constant_302 = 
	    STATIC_STRING("y1m9k83vy1m9k83=Fy1m9k83=ay1m9k83-=Oy2ol1n83*Ay9ou83-2y1l83-=Ryo9t");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qfix_old_attribute_description);
    push_optimized_constant(Qcheck_range_of_element);
    push_optimized_constant(Qinstantiate_variable);
    push_optimized_constant(Qinstantiate_object_in_attribute);
    push_optimized_constant(Qvalues);
    push_optimized_constant(Qcut_out_fourth_element);
    push_optimized_constant(Qmemq_2_cdddr);
    push_optimized_constant(Qcut_out_fifth_element);
    push_optimized_constant(Qmemq_2_cddddr);
    add_grammar_rules_function(regenerate_optimized_constant(list(18,
	    string_constant_285,string_constant_286,string_constant_287,
	    string_constant_288,string_constant_289,string_constant_290,
	    string_constant_291,string_constant_292,string_constant_293,
	    string_constant_294,string_constant_295,string_constant_296,
	    string_constant_297,string_constant_298,string_constant_299,
	    string_constant_300,string_constant_301,string_constant_302)));
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qcar_eq = STATIC_SYMBOL("CAR-EQ",AB_package);
    array_constant_12 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)10L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)17L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)20L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)21L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)22L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)24L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)25L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)26L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)27L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)28L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)29L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)35L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)39L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)46L,(SI_Long)40L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)47L,(SI_Long)57344L);
    list_constant_17 = STATIC_CONS(Qindexed,Qnil);
    Qold_value_of_indexed_attributes = 
	    STATIC_SYMBOL("OLD-VALUE-OF-INDEXED-ATTRIBUTES",AB_package);
    Qcompile_old_attribute_descriptions_for_slot = 
	    STATIC_SYMBOL("COMPILE-OLD-ATTRIBUTE-DESCRIPTIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_old_attribute_descriptions_for_slot,
	    STATIC_FUNCTION(compile_old_attribute_descriptions_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qold_attribute_descriptions,
	    SYMBOL_FUNCTION(Qcompile_old_attribute_descriptions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qold_attribute_descriptions,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_item_classes_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-ITEM-CLASSES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_item_classes_for_slot,
	    STATIC_FUNCTION(compile_list_of_item_classes_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qlist_of_item_classes,
	    SYMBOL_FUNCTION(Qcompile_list_of_item_classes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_item_classes,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_object_classes_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-OBJECT-CLASSES-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_object_classes_for_slot,
	    STATIC_FUNCTION(compile_list_of_object_classes_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qlist_of_object_classes,
	    SYMBOL_FUNCTION(Qcompile_list_of_object_classes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_object_classes,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_connection_classes_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-CONNECTION-CLASSES-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_connection_classes_for_slot,
	    STATIC_FUNCTION(compile_list_of_connection_classes_for_slot,
	    NIL,TRUE,3,6));
    mutate_global_property(Qlist_of_connection_classes,
	    SYMBOL_FUNCTION(Qcompile_list_of_connection_classes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_connection_classes,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_message_classes_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-MESSAGE-CLASSES-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_message_classes_for_slot,
	    STATIC_FUNCTION(compile_list_of_message_classes_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qlist_of_message_classes,
	    SYMBOL_FUNCTION(Qcompile_list_of_message_classes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_message_classes,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcompile_list_of_classes_for_slot = 
	    STATIC_SYMBOL("COMPILE-LIST-OF-CLASSES-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_list_of_classes_for_slot,
	    STATIC_FUNCTION(compile_list_of_classes_for_slot,NIL,TRUE,3,6));
    mutate_global_property(Qlist_of_classes,
	    SYMBOL_FUNCTION(Qcompile_list_of_classes_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qlist_of_classes,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_303 = 
	    STATIC_STRING("13Ly1m833Vy83-6y1m833Vy1m9k83Zy1m83-Gy83-6y1m83xgy83-6y1m832Cy83-6y1m83-eRy83-6y1m83jNy83-6y1m833Qy83-6y1m83n9y83-6y1m83BOy83-6y");
    string_constant_304 = 
	    STATIC_STRING("1m834Hy83-6y1m83xiy83-6y1m839Wy83-6y1m834Ry83-6y1m83-6ky83-6y1m83-GSy83-6y1m837dy83-6y1m83eWy83-6y1m834Hy83eWy1m834Hy83-eUy1m834");
    string_constant_305 = 
	    STATIC_STRING("Hy839Wy1m834Hy834Ry1m834Hy83xiy1m839Wy83-GSy1m839Wy83xiy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_3(string_constant_303,
	    string_constant_304,string_constant_305)));
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    mutate_global_property(Qab_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    mutate_global_property(Qitem_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    mutate_global_property(Qmessage_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    mutate_global_property(Qobject_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qjunction_class = STATIC_SYMBOL("JUNCTION-CLASS",AB_package);
    mutate_global_property(Qjunction_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qsimulation_subtable_class = STATIC_SYMBOL("SIMULATION-SUBTABLE-CLASS",
	    AB_package);
    mutate_global_property(Qsimulation_subtable_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    mutate_global_property(Qnew_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    mutate_global_property(Qconnection_class,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qobject_name = STATIC_SYMBOL("OBJECT-NAME",AB_package);
    mutate_global_property(Qobject_name,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    SET_SYMBOL_FUNCTION(Qcut_out_fourth_element,
	    STATIC_FUNCTION(cut_out_fourth_element,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcut_out_fifth_element,
	    STATIC_FUNCTION(cut_out_fifth_element,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qcut_out_sixth_element,
	    STATIC_FUNCTION(cut_out_sixth_element,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmemq_2_cdddr,STATIC_FUNCTION(memq_2_cdddr,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmemq_2_cddddr,STATIC_FUNCTION(memq_2_cddddr,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmemq_3_cddddr,STATIC_FUNCTION(memq_3_cddddr,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmemq_3_cdr_cddddr,
	    STATIC_FUNCTION(memq_3_cdr_cddddr,NIL,FALSE,1,1));
    Qnormalized_parse = STATIC_SYMBOL("NORMALIZED-PARSE",AB_package);
    string_constant_50 = 
	    STATIC_STRING("The class given for attribute ~A (~(~a~)) is not an ~\n                  instantiable variable or parameter.");
    string_constant_51 = 
	    STATIC_STRING("The class type-specification given for attribute ~A ~\n                  (~(~a~)) is not an instantiable variable or parameter.");
    string_constant_52 = 
	    STATIC_STRING("The initial value for attribute ~A does not conform to ~\n                the given type specification.");
    string_constant_53 = 
	    STATIC_STRING("The initial value for attribute ~A is not a subclass ~\n                  of its declared type.");
    string_constant_54 = 
	    STATIC_STRING("The class given for attribute ~A (~(~a~)) is not an ~\n                  instantiable object.");
    string_constant_55 = 
	    STATIC_STRING("The class type-specification given for attribute ~A ~\n                  (~(~a~)) is not an instantiable object.");
    string_constant_56 = 
	    STATIC_STRING("~A cannot be the name of a class because it specifies a ~\n                  type in G2.");
    Qattribute_descriptions = STATIC_SYMBOL("ATTRIBUTE-DESCRIPTIONS",
	    AB_package);
    Qcompile_attribute_descriptions_for_slot = 
	    STATIC_SYMBOL("COMPILE-ATTRIBUTE-DESCRIPTIONS-FOR-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_attribute_descriptions_for_slot,
	    STATIC_FUNCTION(compile_attribute_descriptions_for_slot,NIL,
	    TRUE,3,6));
    mutate_global_property(Qattribute_descriptions,
	    SYMBOL_FUNCTION(Qcompile_attribute_descriptions_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qattribute_descriptions,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qcached_system_slot_is_present_only_on_non_user_subclassable_system_slots 
	    = 
	    STATIC_SYMBOL("CACHED-SYSTEM-SLOT-IS-PRESENT-ONLY-ON-NON-USER-SUBCLASSABLE-SYSTEM-SLOTS",
	    AB_package);
    Cached_system_slot_is_present_only_on_non_user_subclassable_system_slots_prop 
	    = 
	    Qcached_system_slot_is_present_only_on_non_user_subclassable_system_slots;
    Qunknown = STATIC_SYMBOL("UNKNOWN",AB_package);
    Qslot_category = STATIC_SYMBOL("SLOT-CATEGORY",AB_package);
    Qslot_names_for_alias = STATIC_SYMBOL("SLOT-NAMES-FOR-ALIAS",AB_package);
    string_constant_57 = 
	    STATIC_STRING("There is a badly formed class-qualified attribute name.");
    string_constant_58 = 
	    STATIC_STRING("~A is the name of a G2 system attribute and cannot be a user-defined attribute.");
    string_constant_59 = 
	    string_append2(STATIC_STRING("The direct superiors of a class must be complete before ~\n                          placing an initialization on ~a because it is a built-in ~\n                          attrib"),
	    STATIC_STRING("ute that requires specific built-in class inheritance."));
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)3L,Qab_or,Qitem_or_datum,
	    list_constant_24);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    SET_SYMBOL_FUNCTION(Qcheck_value_attribute_initialization_type,
	    STATIC_FUNCTION(check_value_attribute_initialization_type,NIL,
	    FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qcheck_value_attribute_initialization_type);
    array_constant_13 = STATIC_ARRAY(list_constant_23,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)57344L);
    Qg2 = STATIC_SYMBOL("G2",AB_package);
    Qzero = STATIC_SYMBOL("ZERO",AB_package);
    SET_SYMBOL_FUNCTION(Qadd_initial_value_for_declared_type,
	    STATIC_FUNCTION(add_initial_value_for_declared_type,NIL,FALSE,
	    1,1));
    SET_SYMBOL_FUNCTION(Qfix_attribute_description,
	    STATIC_FUNCTION(fix_attribute_description,NIL,FALSE,2,2));
    Qsymbolic_value_list = STATIC_SYMBOL("SYMBOLIC-VALUE-LIST",AB_package);
    Qcompile_symbolic_value_list_for_slot = 
	    STATIC_SYMBOL("COMPILE-SYMBOLIC-VALUE-LIST-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_symbolic_value_list_for_slot,
	    STATIC_FUNCTION(compile_symbolic_value_list_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qsymbolic_value_list,
	    SYMBOL_FUNCTION(Qcompile_symbolic_value_list_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qsymbolic_value_list,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
}
