/* gram6c.c
 * Input file:  grammar6c.lisp
 * Copyright (C) 1986-2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram6c.h"


/* FLATTEN-POINT-TREE-PHRASE-INTO-LIST */
Object flatten_point_tree_phrase_into_list(point_tree)
    Object point_tree;
{
    x_note_fn_call(202,0);
    return nreverse_canonically(flatten_point_tree_phrase_into_reverse_list(point_tree));
}

static Object Qarc;                /* arc */

/* FLATTEN-POINT-TREE-PHRASE-INTO-REVERSE-LIST */
Object flatten_point_tree_phrase_into_reverse_list(point_tree)
    Object point_tree;
{
    Object temp, thing, cdr_thing, car_thing, cadr_thing;
    char temp_1;

    x_note_fn_call(202,1);
    if (CONSP(point_tree) && EQ(M_CAR(point_tree),Qarc)) {
	temp = M_CDR(point_tree);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point_tree))) : TRUEP(Nil)) {
	thing = M_CAR(M_CDR(point_tree));
	if (CONSP(thing)) {
	    temp = CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	thing = CADR(point_tree);
	if (CONSP(thing)) {
	    temp = M_CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = ((temp_1 ?  !TRUEP(M_CDR(M_CDR(thing))) : TRUEP(Nil)) ? 
		FIXNUMP(M_CAR(thing)) : TRUEP(Nil)) ? 
		FIXNUMP(M_CAR(M_CDR(thing))) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1);
    else {
	if (CONSP(point_tree)) {
	    temp = M_CDR(point_tree);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = ((temp_1 ?  !TRUEP(M_CDR(M_CDR(point_tree))) : 
		TRUEP(Nil)) ? FIXNUMP(M_CAR(point_tree)) : TRUEP(Nil)) ? 
		FIXNUMP(M_CAR(M_CDR(point_tree))) : TRUEP(Nil);
    }
    if (temp_1);
    else {
	cdr_thing = Nil;
	car_thing = Nil;
	cadr_thing = Nil;
	if (CONSP(point_tree)) {
	    cdr_thing = M_CDR(point_tree);
	    temp_1 = TRUEP(cdr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
		!TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
	    car_thing = M_CAR(point_tree);
	    temp_1 = TRUEP(car_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    cadr_thing = M_CAR(cdr_thing);
	    temp_1 = TRUEP(cadr_thing);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = (temp_1 ?  !FIXNUMP(car_thing) ||  !FIXNUMP(cadr_thing) : 
		TRUEP(Nil)) ? CONSP(car_thing) && EQ(M_CAR(car_thing),
		Qplus) || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),Qplus) 
		|| SYMBOLP(car_thing) || SYMBOLP(cadr_thing) : TRUEP(Nil);
    }
    if (temp_1)
	return phrase_cons(point_tree,Nil);
    else {
	temp = SECOND(point_tree);
	return phrase_cons(temp,
		flatten_point_tree_phrase_into_reverse_list(CAR(point_tree)));
    }
}

/* COPY-TREE-INCLUDING-LEAVES-USING-PHRASE-CONSES */
Object copy_tree_including_leaves_using_phrase_conses(tree_qm)
    Object tree_qm;
{
    Object temp, new_list, last_new_cons, current_copy_position, cdr_new_value;

    x_note_fn_call(202,2);
    if (text_string_p(tree_qm))
	temp = copy_text_string(tree_qm);
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(tree_qm) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(tree_qm)) == (SI_Long)1L)
	temp = copy_managed_float(tree_qm);
    else if (ATOM(tree_qm))
	temp = tree_qm;
    else {
	temp = copy_tree_including_leaves_using_phrase_conses(CAR(tree_qm));
	new_list = phrase_cons(temp,CDR(tree_qm));
	last_new_cons = new_list;
	current_copy_position = CDR(tree_qm);
      next_loop:
	if (ATOM(current_copy_position))
	    goto end_loop;
	temp = 
		copy_tree_including_leaves_using_phrase_conses(CAR(current_copy_position));
	cdr_new_value = phrase_cons(temp,CDR(current_copy_position));
	M_CDR(last_new_cons) = cdr_new_value;
	last_new_cons = CDR(last_new_cons);
	current_copy_position = CDR(current_copy_position);
	goto next_loop;
      end_loop:
	temp = new_list;
	goto end_1;
	temp = Qnil;
      end_1:;
    }
    return VALUES_1(temp);
}

/* POINT-TREE-PHRASE */
Object point_tree_phrase(points)
    Object points;
{
    Object temp, result_1, point, ab_loop_list_;

    x_note_fn_call(202,3);
    if (EQ(length(points),FIX((SI_Long)1L)))
	return copy_tree_including_leaves_using_phrase_conses(CAR(points));
    else {
	temp = copy_tree_including_leaves_using_phrase_conses(CAR(points));
	result_1 = phrase_list_2(temp,
		copy_tree_including_leaves_using_phrase_conses(CADR(points)));
	point = Nil;
	ab_loop_list_ = CDDR(points);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	point = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = result_1;
	result_1 = phrase_list_2(temp,
		copy_tree_including_leaves_using_phrase_conses(point));
	goto next_loop;
      end_loop:
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
}

static Object Qstatement_format;   /* statement-format */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant;     /* "~a" */

/* WRITE-TEXT-SPECIFICATION-FOR-ICON-EDITOR-TABLE-INFO-FRAME */
Object write_text_specification_for_icon_editor_table_info_frame(spec)
    Object spec;
{
    Object text_box_format_name, text_box_format, current_wide_string_list;
    Object wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object text_string, text_within_region, clipped_text_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(202,4);
    text_box_format_name = Qstatement_format;
    text_box_format = get_or_make_format_frame_function(text_box_format_name);
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
	      write_text_specification(spec);
	      text_string = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    text_within_region = convert_text_string_to_text_within_region(5,
	    text_string,FIX((SI_Long)360L),FIX((SI_Long)100L),
	    text_box_format,Nil);
    clipped_text_string = convert_text_to_text_string(1,text_within_region);
    tformat(2,string_constant,clipped_text_string);
    reclaim_text(text_within_region);
    return reclaim_text_string(clipped_text_string);
}

static Object array_constant;      /* # */

static Object string_constant_1;   /* " \"~a\" " */

static Object string_constant_2;   /* "~%" */

static Object string_constant_3;   /* " at " */

static Object string_constant_4;   /* " in " */

static Object string_constant_5;   /* " ~(~a~) " */

/* WRITE-TEXT-SPECIFICATION */
Object write_text_specification(spec)
    Object spec;
{
    Object temp;

    x_note_fn_call(202,5);
    if ( !TRUEP(spec))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else {
	temp = SECOND(spec);
	if (SYMBOLP(temp))
	    twrite_symbol(1,SECOND(spec));
	else
	    tformat(2,string_constant_1,SECOND(spec));
	tformat(1,string_constant_2);
	tformat(1,string_constant_3);
	write_point(THIRD(spec));
	tformat(1,string_constant_4);
	return tformat(2,string_constant_5,FOURTH(spec));
    }
}

/* WRITE-GLOBAL-STIPPLE-SPECIFICATION?-FROM-SLOT */
Object write_global_stipple_specification_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(202,6);
    return write_stipple_specification(value);
}

/* WRITE-STIPPLE-SPECIFICATION?-FROM-SLOT */
Object write_stipple_specification_qm_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(202,7);
    return write_stipple_specification(value);
}

/* WRITE-STIPPLE-SPECIFICATION-FOR-ICON-EDITOR-TABLE-INFO-FRAME */
Object write_stipple_specification_for_icon_editor_table_info_frame(spec)
    Object spec;
{
    x_note_fn_call(202,8);
    return write_stipple_specification(spec);
}

static Object string_constant_6;   /* "~(~a~)" */

static Object string_constant_7;   /* " (~d, ~d) (~d, ~d)" */

/* WRITE-STIPPLE-SPECIFICATION */
Object write_stipple_specification(spec)
    Object spec;
{
    Object point, temp, temp_1, temp_2;

    x_note_fn_call(202,9);
    if ( !TRUEP(spec))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (ATOM(spec))
	return tformat(2,string_constant_6,spec);
    else {
	tformat(2,string_constant_6,SECOND(spec));
	if (CDDR(spec)) {
	    point = THIRD(spec);
	    temp = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		    simple_eval_for_icon(FIRST(point));
	    point = THIRD(spec);
	    temp_1 = FIXNUMP(SECOND(point)) ? SECOND(point) : 
		    simple_eval_for_icon(SECOND(point));
	    point = FOURTH(spec);
	    temp_2 = FIXNUMP(FIRST(point)) ? FIRST(point) : 
		    simple_eval_for_icon(FIRST(point));
	    point = FOURTH(spec);
	    return tformat(5,string_constant_7,temp,temp_1,temp_2,
		    FIXNUMP(SECOND(point)) ? SECOND(point) : 
		    simple_eval_for_icon(SECOND(point)));
	}
	else
	    return VALUES_1(Nil);
    }
}

static Object Qnone;               /* none */

/* COMPILE-IMAGE-NAME?-FOR-SLOT */
Object compile_image_name_qm_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(202,10);
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
    if (EQ(parse_result,Qnone))
	return VALUES_1(Nil);
    else
	return VALUES_1(parse_result);
}

/* WRITE-IMAGE-SPECIFICATION?-FROM-SLOT */
Object write_image_specification_qm_from_slot(image_specification_qm,
	    gensymed_symbol)
    Object image_specification_qm, gensymed_symbol;
{
    x_note_fn_call(202,11);
    if ( !TRUEP(image_specification_qm))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)4L));
    else if (ATOM(image_specification_qm))
	return twrite(image_specification_qm);
    else {
	tformat(2,string_constant_6,SECOND(image_specification_qm));
	if (THIRD(image_specification_qm)) {
	    tformat(1,string_constant_3);
	    return write_point(THIRD(image_specification_qm));
	}
	else
	    return VALUES_1(Nil);
    }
}

/* WRITE-TEXT-SPECIFICATION?-FROM-SLOT */
Object write_text_specification_qm_from_slot(text_specification_qm,
	    gensymed_symbol)
    Object text_specification_qm, gensymed_symbol;
{
    x_note_fn_call(202,12);
    return write_text_specification_for_icon_editor_table_info_frame(text_specification_qm);
}

/* FIX-LINE-LIST */
Object fix_line_list(x)
    Object x;
{
    x_note_fn_call(202,13);
    return phrase_cons(CAR(x),CDDR(x));
}

static Object list_constant;       /* # */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

/* POINT-EXPRESSION-CONTAINS-BAD-VARIABLE-P */
Object point_expression_contains_bad_variable_p(point_expression,
	    variable_spec_list)
    Object point_expression, variable_spec_list;
{
    Object value_qm, temp;

    x_note_fn_call(202,14);
    if ( !TRUEP(point_expression))
	return VALUES_1(Nil);
    else if (INTEGERP(point_expression))
	return VALUES_1(Nil);
    else if (EQ(point_expression,Qplus) || EQ(point_expression,Qminus))
	return VALUES_1(Nil);
    else if (SYMBOLP(point_expression)) {
	if (memq_function(point_expression,list_constant))
	    return VALUES_1(Nil);
	else {
	    value_qm = getfq_function_no_default(variable_spec_list,
		    point_expression);
	    temp =  !TRUEP(value_qm) ? gensym_list_2(array_constant_1,
		    point_expression) : Qnil;
	    if (temp)
		return VALUES_1(temp);
	    else if ( !INTEGERP(value_qm))
		return gensym_list_2(array_constant_2,point_expression);
	    else
		return VALUES_1(Nil);
	}
    }
    else if (CONSP(point_expression)) {
	temp = 
		point_expression_contains_bad_variable_p(M_CAR(point_expression),
		variable_spec_list);
	if (temp)
	    return VALUES_1(temp);
	else
	    return point_expression_contains_bad_variable_p(M_CDR(point_expression),
		    variable_spec_list);
    }
    else
	return VALUES_1(Qnil);
}

static Object string_constant_8;   /* " contains an invalid point. Report the problem to Gensym.~% " */

/* POINT-CONTAINS-BAD-VARIABLE-P */
Object point_contains_bad_variable_p(point,variable_specification_qm)
    Object point, variable_specification_qm;
{
    Object temp, thing, cdr_thing, car_thing, cadr_thing;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object error_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(202,15);
    if (CONSP(point) && EQ(M_CAR(point),Qarc)) {
	temp = M_CDR(point);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point))) : TRUEP(Nil)) {
	thing = M_CAR(M_CDR(point));
	if (CONSP(thing)) {
	    temp = CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return point_contains_bad_variable_p(M_CAR(M_CDR(point)),
		variable_specification_qm);
    else {
	if (CONSP(point)) {
	    temp = M_CDR(point);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (((temp_1 ?  !TRUEP(M_CDR(M_CDR(point))) : TRUEP(Nil)) ? 
		FIXNUMP(M_CAR(point)) : TRUEP(Nil)) ? 
		FIXNUMP(M_CAR(M_CDR(point))) : TRUEP(Nil))
	    return VALUES_1(Nil);
	else {
	    cdr_thing = Nil;
	    car_thing = Nil;
	    cadr_thing = Nil;
	    if (CONSP(point)) {
		cdr_thing = M_CDR(point);
		temp_1 = TRUEP(cdr_thing);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
		    !TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
		car_thing = M_CAR(point);
		temp_1 = TRUEP(car_thing);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		cadr_thing = M_CAR(cdr_thing);
		temp_1 = TRUEP(cadr_thing);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if ((temp_1 ?  !FIXNUMP(car_thing) ||  !FIXNUMP(cadr_thing) : 
		    TRUEP(Nil)) ? CONSP(car_thing) && EQ(M_CAR(car_thing),
		    Qplus) || CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),
		    Qplus) || SYMBOLP(car_thing) || SYMBOLP(cadr_thing) : 
		    TRUEP(Nil)) {
		temp = 
			point_expression_contains_bad_variable_p(M_CAR(point),
			variable_specification_qm);
		if (temp)
		    return VALUES_1(temp);
		else
		    return point_expression_contains_bad_variable_p(M_CAR(M_CDR(point)),
			    variable_specification_qm);
	    }
	    else {
		cdr_thing = Nil;
		car_thing = Nil;
		cadr_thing = Nil;
		if (CONSP(point)) {
		    cdr_thing = M_CDR(point);
		    temp_1 = TRUEP(cdr_thing);
		}
		else
		    temp_1 = TRUEP(Nil);
		if ((temp_1 ? CONSP(cdr_thing) : TRUEP(Nil)) ?  
			!TRUEP(M_CDR(cdr_thing)) : TRUEP(Nil)) {
		    car_thing = M_CAR(point);
		    temp_1 = TRUEP(car_thing);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    cadr_thing = M_CAR(cdr_thing);
		    temp_1 = TRUEP(cadr_thing);
		}
		else
		    temp_1 = TRUEP(Nil);
		if ((temp_1 ?  !FIXNUMP(car_thing) ||  
			!FIXNUMP(cadr_thing) : TRUEP(Nil)) ? 
			CONSP(car_thing) && EQ(M_CAR(car_thing),Qplus) || 
			CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),Qplus) 
			|| CONSP(car_thing) && EQ(M_CAR(car_thing),Qminus) 
			|| CONSP(cadr_thing) && EQ(M_CAR(cadr_thing),
			Qminus) || SYMBOLP(car_thing) || 
			SYMBOLP(cadr_thing) : TRUEP(Nil))
		    return VALUES_1(Nil);
		else {
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
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | (SI_Long)0L;
		      UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,
			      aref_new_value);
		      UBYTE_16_ISASET_1(wide_string_bv16,(SI_Long)2048L,
			      (SI_Long)0L);
		      current_wide_string = wide_string_bv16;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_wide_string,Qcurrent_wide_string,current_wide_string,
			      3);
			fill_pointer_for_current_wide_string = 
				FIX((SI_Long)0L);
			PUSH_SPECIAL_WITH_SYMBOL(Fill_pointer_for_current_wide_string,Qfill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
				2);
			  length_1 = 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			  total_length_of_current_wide_string = 
				  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)2L) + 
				  ((UBYTE_16_ISAREF_1(Current_wide_string,
				  length_1 - (SI_Long)1L) & 
				  (SI_Long)8191L) << (SI_Long)16L));
			  PUSH_SPECIAL_WITH_SYMBOL(Total_length_of_current_wide_string,Qtotal_length_of_current_wide_string,total_length_of_current_wide_string,
				  1);
			    current_twriting_output_type = Qwide_string;
			    PUSH_SPECIAL_WITH_SYMBOL(Current_twriting_output_type,Qcurrent_twriting_output_type,current_twriting_output_type,
				    0);
			      tformat(1,string_constant_8);
			      error_string = copy_out_current_wide_string();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    return gensym_list_2(error_string,Nil);
		}
	    }
	}
    }
}

/* POINTS-CONTAIN-BAD-VARIABLE-P */
Object points_contain_bad_variable_p(list_of_points,variable_specification)
    Object list_of_points, variable_specification;
{
    Object point, ab_loop_list_, ab_loop_it_;

    x_note_fn_call(202,16);
    point = Nil;
    ab_loop_list_ = list_of_points;
    ab_loop_it_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    point = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loop_it_ = point_contains_bad_variable_p(point,variable_specification);
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object array_constant_3;    /* # */

/* TEXT-DRAWING-ELEMENT-LABEL-CONTAINS-BAD-VARIABLE-P */
Object text_drawing_element_label_contains_bad_variable_p(label,
	    variable_spec_list)
    Object label, variable_spec_list;
{
    Object temp;

    x_note_fn_call(202,17);
    if (text_string_p(label))
	return VALUES_1(Nil);
    else {
	temp =  !TRUEP(getfq_function_no_default(variable_spec_list,
		label)) ? gensym_list_2(array_constant_1,label) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if ( 
		!TRUEP(text_string_p(getfq_function_no_default(variable_spec_list,
		label))))
	    return gensym_list_2(array_constant_3,label);
	else
	    return VALUES_1(Nil);
    }
}

static Object list_constant_1;     /* # */

static Object array_constant_4;    /* # */

/* TEXT-DRAWING-ELEMENT-FONTSIZE-CONTAINS-BAD-VARIABLE-P */
Object text_drawing_element_fontsize_contains_bad_variable_p(font_or_variable,
	    variable_spec_list)
    Object font_or_variable, variable_spec_list;
{
    Object font, temp;

    x_note_fn_call(202,18);
    if (memq_function(font_or_variable,list_constant_1))
	return VALUES_1(Nil);
    else {
	font = getfq_function_no_default(variable_spec_list,font_or_variable);
	temp =  !TRUEP(font) ? gensym_list_2(array_constant_1,
		font_or_variable) : Qnil;
	if (temp)
	    return VALUES_1(temp);
	else if ( !TRUEP(memq_function(font,list_constant_1)))
	    return gensym_list_2(array_constant_4,font_or_variable);
	else
	    return VALUES_1(Nil);
    }
}

static Object array_constant_5;    /* # */

static Object array_constant_6;    /* # */

/* IMAGE-DRAWING-ELEMENT-IMAGE-NAME-CONTAINS-BAD-VARIABLE-P */
Object image_drawing_element_image_name_contains_bad_variable_p(image_name,
	    variable_spec_list)
    Object image_name, variable_spec_list;
{
    Object temp;

    x_note_fn_call(202,19);
    temp = getfq_function_no_default(variable_spec_list,image_name);
    if (INTEGERP(temp))
	return gensym_list_2(array_constant_5,image_name);
    else if (text_string_p(getfq_function_no_default(variable_spec_list,
	    image_name)))
	return gensym_list_2(array_constant_6,image_name);
    else
	return VALUES_1(Nil);
}

static Object Qtext;               /* text */

static Object Qimage;              /* image */

static Object Qsolid_rectangle;    /* solid-rectangle */

static Object Qfilled_circle;      /* filled-circle */

static Object Qstippled_area;      /* stippled-area */

static Object Qfilled_polygon;     /* filled-polygon */

/* ELEMENT-CONTAINS-BAD-VARIABLE? */
Object element_contains_bad_variable_qm(element,variable_spec_list)
    Object element, variable_spec_list;
{
    Object temp;

    x_note_fn_call(202,20);
    if (ATOM(element))
	return VALUES_1(Nil);
    else if (CONSP(element) && EQ(FIRST(element),Qtext)) {
	temp = 
		text_drawing_element_label_contains_bad_variable_p(SECOND(element),
		variable_spec_list);
	if (temp);
	else
	    temp = point_contains_bad_variable_p(THIRD(element),
		    variable_spec_list);
	if (temp)
	    return VALUES_1(temp);
	else
	    return text_drawing_element_fontsize_contains_bad_variable_p(FOURTH(element),
		    variable_spec_list);
    }
    else if (CONSP(element) && EQ(FIRST(element),Qimage)) {
	temp = 
		image_drawing_element_image_name_contains_bad_variable_p(SECOND(element),
		variable_spec_list);
	if (temp)
	    return VALUES_1(temp);
	else if (THIRD(element))
	    return point_contains_bad_variable_p(THIRD(element),
		    variable_spec_list);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(FIRST(element),Qsolid_rectangle)) {
	temp = point_contains_bad_variable_p(SECOND(element),
		variable_spec_list);
	if (temp)
	    return VALUES_1(temp);
	else
	    return point_contains_bad_variable_p(THIRD(element),
		    variable_spec_list);
    }
    else if (EQ(FIRST(element),Qfilled_circle)) {
	temp = point_contains_bad_variable_p(SECOND(element),
		variable_spec_list);
	if (temp);
	else
	    temp = point_contains_bad_variable_p(THIRD(element),
		    variable_spec_list);
	if (temp)
	    return VALUES_1(temp);
	else
	    return point_contains_bad_variable_p(FOURTH(element),
		    variable_spec_list);
    }
    else if (EQ(FIRST(element),Qstippled_area)) {
	if (CDDR(element))
	    return points_contain_bad_variable_p(CDDR(element),
		    variable_spec_list);
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(FIRST(element),Qfilled_polygon)) {
	if (IFIX(length(SECOND(element))) > (SI_Long)2L)
	    return points_contain_bad_variable_p(SECOND(element),
		    variable_spec_list);
	else
	    return points_contain_bad_variable_p(CDR(element),
		    variable_spec_list);
    }
    else
	return points_contain_bad_variable_p(CDR(element),variable_spec_list);
}

static Object string_constant_9;   /* "~% The " */

static Object string_constant_10;  /* " the local variable ~s" */

static Object string_constant_11;  /* " = ~s" */

static Object array_constant_7;    /* # */

static Object array_constant_8;    /* # */

/* BAD-VARIABLE-IN-ELEMENT-MESSAGE-STRING */
Object bad_variable_in_element_message_string(bad_element,verb,
	    variable_name,variable_value_qm,reason_for_rejection)
    Object bad_element, verb, variable_name, variable_value_qm;
    Object reason_for_rejection;
{
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,21);
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
	      tformat(1,string_constant_9);
	      write_drawing_element(EQ(CAR(bad_element),Qfilled_polygon) ? 
		      phrase_list_2(Qfilled_polygon,CDR(bad_element)) : 
		      bad_element);
	      if (variable_name) {
		  tformat(1,string_constant_2);
		  twrite_general_string(verb);
		  tformat(2,string_constant_10,variable_name);
		  if (variable_value_qm)
		      tformat(2,string_constant_11,variable_value_qm);
		  twrite_beginning_of_wide_string(array_constant_7,
			  FIX((SI_Long)8L));
	      }
	      twrite_general_string(reason_for_rejection);
	      twrite_beginning_of_wide_string(array_constant_8,
		      FIX((SI_Long)1L));
	      result = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object array_constant_9;    /* # */

/* BAD-VARIABLE-IN-ELEMENT-MESSAGE */
Object bad_variable_in_element_message(bad_element,variable_name,
	    variable_value_qm,reason_for_rejection)
    Object bad_element, variable_name, variable_value_qm, reason_for_rejection;
{
    Object temp, temp_1;

    x_note_fn_call(202,22);
    temp = Bad_phrase;
    temp_1 = bad_variable_in_element_message_string(bad_element,
	    array_constant_9,variable_name,variable_value_qm,
	    reason_for_rejection);
    return VALUES_2(temp,temp_1);
}

Object Reserved_icon_variable_names = UNBOUND;

static Object string_constant_12;  /* "~s is a reserved icon variable name.~%" */

static Object string_constant_13;  /* "The reserved icon variable names are ~%" */

static Object string_constant_14;  /* " and " */

static Object string_constant_15;  /* ", " */

static Object string_constant_16;  /* "." */

/* RESERVED-ICON-VARIABLE-MESSAGE */
Object reserved_icon_variable_message(bad_variable_name_qm)
    Object bad_variable_name_qm;
{
    Object temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object name, next_qm, next_next_qm, ab_loop_list_, temp_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(202,23);
    temp = Bad_phrase;
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
	      tformat(2,string_constant_12,bad_variable_name_qm);
	      tformat(1,string_constant_13);
	      name = Nil;
	      next_qm = Nil;
	      next_next_qm = Nil;
	      ab_loop_list_ = Reserved_icon_variable_names;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      name = CAR(ab_loop_list_);
	      temp_1 = CDR(ab_loop_list_);
	      next_qm = CAR(temp_1);
	      temp_1 = CDR(ab_loop_list_);
	      temp_1 = CDR(temp_1);
	      next_next_qm = CAR(temp_1);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(next_qm))
		  twrite(string_constant_14);
	      twrite_symbol(1,name);
	      if (next_next_qm)
		  twrite(string_constant_15);
	      goto next_loop;
	    end_loop:;
	      twrite(string_constant_16);
	      temp_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return VALUES_2(temp,temp_1);
}

static Object string_constant_17;  /* "Width and height must be a positive integer." */

static Object string_constant_18;  /* "Width and height must be less than or equal to ~d." */

static Object float_constant;      /* 0.0 */

static Object string_constant_19;  /* "The product of width and height must be less than or equal to ~d." */

/* CHECK-ICON-SIZE */
Object check_icon_size(width,height)
    Object width, height;
{
    Object temp;
    char temp_3;
    double temp_1, temp_2;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(202,24);
    if (IFIX(width) < (SI_Long)1L || IFIX(height) < (SI_Long)1L)
	return tformat_text_string(1,string_constant_17);
    else if (FIXNUM_GT(width,Max_icon_size) || FIXNUM_GT(height,Max_icon_size))
	return tformat_text_string(2,string_constant_18,Max_icon_size);
    else {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    temp = lfloat(width,float_constant);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    temp = lfloat(height,float_constant);
	    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    temp_3 = temp_1 * temp_2 > 2500000.0;
	}
	POP_LOCAL_ALLOCATION(0,0);
	if (temp_3)
	    return tformat_text_string(2,string_constant_19,Max_icon_area);
	else
	    return VALUES_1(Qnil);
    }
}

static Object Qclass_inheritance_path_of_definition;  /* class-inheritance-path-of-definition */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qlookup;             /* lookup */

static Object Qicon_description;   /* icon-description */

static Object string_constant_20;  /* "Cannot change the icon-description of ~NF.  The value ~
				    *                  of the direct-superior-classes attribute on the ~
				    *                  class-definition does not indicate that the class has a ~
				    *                  changeable icon-description."
				    */

static Object Qinherited;          /* inherited */

static Object Qpolychrome;         /* polychrome */

static Object Qsc;                 /* \; */

static Object Qnot_simple_polygon;  /* not-simple-polygon */

static Object Qtoo_many_points;    /* too-many-points */

static Object string_constant_21;  /* "The " */

static Object string_constant_22;  /* " crosses itself or has two identical vertices." */

static Object string_constant_23;  /* " contains ~s points. ~s is the maximum." */

static Object string_constant_24;  /* " is not valid." */

static Object Qvariables;          /* variables */

static Object Qbackground_layer;   /* background-layer */

static Object Qforeground;         /* foreground */

static Object Qstipple;            /* stipple */

/* COMPILE-ICON-DESCRIPTION?-FOR-SLOT */
Object compile_icon_description_qm_for_slot varargs_1(int, n)
{
    Object parse_result, item, gensymed_symbol;
    Object superior, ab_loop_list_, ab_loop_it_, skip_list, key_value, marked;
    Object pred, curr, succ, reference, temp, temp_1, entry_hash, tail, head;
    Object new_cons, temp_2, svref_arg_2, svref_new_value, gensymed_symbol_1;
    Object gensymed_symbol_2, global_properties, kb_properties;
    Object kb_specific_value, resulting_value, sub_class_bit_vector, width;
    Object height, rest_1, unfixed_region_specification_list;
    Object region_specification_qm, variable_specification_qm;
    Object icon_background_layer_qm, icon_background_layer_spec_qm, stipple_qm;
    Object header_count, unfixed_element_list, element_list_1, element_list;
    Object bad_background_layer_qm, variable_spec_list, name, value;
    Object bad_name_qm, bad_variable_name_qm, element, bad_variable_qm;
    Object bad_variable_in_element_qm, current_icon_untransformed_width;
    Object current_icon_untransformed_height, current_icon_variables_plist;
    Object current_icon_variables_override_plist, bad_polygon_qm;
    Object bad_region_or_color_or_metacolor_qm, error_text_qm, polygon, reason;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object bad_variable, reason_for_rejection, variable_name;
    Object variable_value_qm, bad_element, polychrome_header, variable_header;
    Object background_header;
    SI_Long key_hash_value, bottom_level, level, ab_loop_bind_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_3, gensymed_symbol_4, gensymed_symbol_5;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_3;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,25);
    INIT_ARGS_nonrelocating();
    parse_result = REQUIRED_ARG_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    if (get_lookup_slot_value_given_default(item,
	    Qclass_inheritance_path_of_definition,Nil)) {
	superior = Nil;
	ab_loop_list_ = ISVREF(item,(SI_Long)21L);
	ab_loop_it_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	superior = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_3:
	if ( !TRUEP(marked))
	    goto end_loop_2;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_3;
      end_loop_2:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == key_hash_value 
		? (EQ(key_value,ISVREF(curr,(SI_Long)2L)) ? ISVREF(curr,
		(SI_Long)3L) : Nil) : Nil;
	if ( !TRUEP(gensymed_symbol)) {
	    gensymed_symbol = superior;
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
	    gensymed_symbol = set_skip_list_entry(temp,FIX((SI_Long)31L),
		    Qeq,Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
      next_loop_6:
	if ( !TRUEP(marked))
	    goto end_loop_5;
	curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	temp = ATOMIC_REF_OBJECT(reference);
	temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	result = VALUES_2(temp,temp_1);
	MVS_2(result,succ,marked);
	goto next_loop_6;
      end_loop_5:
	entry_hash = ISVREF(curr,(SI_Long)1L);
	if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		key_hash_value &&  !EQ(key_value,ISVREF(curr,(SI_Long)2L))) {
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
	  next_loop_7:
	    if (level < ab_loop_bind_)
		goto end_loop_7;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_8:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_9:
	    if ( !TRUEP(marked))
		goto end_loop_8;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_9;
	  end_loop_8:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	    key_hash_value = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
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
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_11:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_12:
	    if ( !TRUEP(marked))
		goto end_loop_11;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_12;
	  end_loop_11:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
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
	gensymed_symbol = resulting_value;
	if (gensymed_symbol) {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
		temp_3 = (SI_Long)0L < gensymed_symbol_3;
	    }
	    else
		temp_3 = TRUEP(Nil);
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
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
	  next_loop_13:
	    if (level < ab_loop_bind_)
		goto end_loop_13;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_14:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_15:
	    if ( !TRUEP(marked))
		goto end_loop_14;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_15;
	  end_loop_14:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_5;
	    goto next_loop_14;
	  end_loop_15:
	  end_5:
	    level = level - (SI_Long)1L;
	    goto next_loop_13;
	  end_loop_13:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
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
	  next_loop_16:
	    if (level < ab_loop_bind_)
		goto end_loop_16;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_17:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_18:
	    if ( !TRUEP(marked))
		goto end_loop_17;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_18;
	  end_loop_17:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_6;
	    goto next_loop_17;
	  end_loop_18:
	  end_6:
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
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_20:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_21:
		if ( !TRUEP(marked))
		    goto end_loop_20;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_21;
	      end_loop_20:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_7;
		goto next_loop_20;
	      end_loop_21:
	      end_7:
		level = level - (SI_Long)1L;
		goto next_loop_19;
	      end_loop_19:;
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
	      next_loop_22:
		if (level < ab_loop_bind_)
		    goto end_loop_22;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_23:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_24:
		if ( !TRUEP(marked))
		    goto end_loop_23;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_24;
	      end_loop_23:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_8;
		goto next_loop_23;
	      end_loop_24:
	      end_8:
		level = level - (SI_Long)1L;
		goto next_loop_22;
	      end_loop_22:;
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
			IFIX(ISVREF(Connection_class_description,
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
		    temp_3 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_3 = TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_3 =  !temp_3;
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
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
	  next_loop_25:
	    if (level < ab_loop_bind_)
		goto end_loop_25;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_26:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_27:
	    if ( !TRUEP(marked))
		goto end_loop_26;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_27;
	  end_loop_26:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_9;
	    goto next_loop_26;
	  end_loop_27:
	  end_9:
	    level = level - (SI_Long)1L;
	    goto next_loop_25;
	  end_loop_25:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
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
	  next_loop_28:
	    if (level < ab_loop_bind_)
		goto end_loop_28;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_29:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_30:
	    if ( !TRUEP(marked))
		goto end_loop_29;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_30;
	  end_loop_29:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_10;
	    goto next_loop_29;
	  end_loop_30:
	  end_10:
	    level = level - (SI_Long)1L;
	    goto next_loop_28;
	  end_loop_28:;
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
	      next_loop_31:
		if (level < ab_loop_bind_)
		    goto end_loop_31;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_32:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_33:
		if ( !TRUEP(marked))
		    goto end_loop_32;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_33;
	      end_loop_32:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_11;
		goto next_loop_32;
	      end_loop_33:
	      end_11:
		level = level - (SI_Long)1L;
		goto next_loop_31;
	      end_loop_31:;
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
	      next_loop_34:
		if (level < ab_loop_bind_)
		    goto end_loop_34;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_35:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_36:
		if ( !TRUEP(marked))
		    goto end_loop_35;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_36;
	      end_loop_35:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_12;
		goto next_loop_35;
	      end_loop_36:
	      end_12:
		level = level - (SI_Long)1L;
		goto next_loop_34;
	      end_loop_34:;
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
			IFIX(ISVREF(Meter_class_description,(SI_Long)18L));
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
		    temp_3 = (SI_Long)0L < gensymed_symbol_3;
		}
		else
		    temp_3 = TRUEP(Nil);
	    }
	    else
		temp_3 = TRUEP(Nil);
	    temp_3 =  !temp_3;
	}
	else
	    temp_3 = TRUEP(Nil);
	if (temp_3) {
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
	  next_loop_37:
	    if (level < ab_loop_bind_)
		goto end_loop_37;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_38:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_39:
	    if ( !TRUEP(marked))
		goto end_loop_38;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_39;
	  end_loop_38:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_13;
	    goto next_loop_38;
	  end_loop_39:
	  end_13:
	    level = level - (SI_Long)1L;
	    goto next_loop_37;
	  end_loop_37:;
	    gensymed_symbol = IFIX(ISVREF(curr,(SI_Long)1L)) == 
		    key_hash_value ? (EQ(key_value,ISVREF(curr,
		    (SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
	    if ( !TRUEP(gensymed_symbol)) {
		gensymed_symbol = superior;
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
	  next_loop_40:
	    if (level < ab_loop_bind_)
		goto end_loop_40;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	  next_loop_41:
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	  next_loop_42:
	    if ( !TRUEP(marked))
		goto end_loop_41;
	    curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),level));
	    reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
	    temp = ATOMIC_REF_OBJECT(reference);
	    temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T : Nil;
	    result = VALUES_2(temp,temp_1);
	    MVS_2(result,succ,marked);
	    goto next_loop_42;
	  end_loop_41:
	    entry_hash = ISVREF(curr,(SI_Long)1L);
	    if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) == 
		    key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		pred = curr;
		curr = succ;
	    }
	    else
		goto end_14;
	    goto next_loop_41;
	  end_loop_42:
	  end_14:
	    level = level - (SI_Long)1L;
	    goto next_loop_40;
	  end_loop_40:;
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
	      next_loop_43:
		if (level < ab_loop_bind_)
		    goto end_loop_43;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_44:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_45:
		if ( !TRUEP(marked))
		    goto end_loop_44;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_45;
	      end_loop_44:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_15;
		goto next_loop_44;
	      end_loop_45:
	      end_15:
		level = level - (SI_Long)1L;
		goto next_loop_43;
	      end_loop_43:;
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
	      next_loop_46:
		if (level < ab_loop_bind_)
		    goto end_loop_46;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
	      next_loop_47:
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
	      next_loop_48:
		if ( !TRUEP(marked))
		    goto end_loop_47;
		curr = ATOMIC_REF_OBJECT(ISVREF(ISVREF(pred,(SI_Long)0L),
			level));
		reference = ISVREF(ISVREF(curr,(SI_Long)0L),level);
		temp = ATOMIC_REF_OBJECT(reference);
		temp_1 = (SI_Long)355L == ATOMIC_REF_STAMP(reference) ? T :
			 Nil;
		result = VALUES_2(temp,temp_1);
		MVS_2(result,succ,marked);
		goto next_loop_48;
	      end_loop_47:
		entry_hash = ISVREF(curr,(SI_Long)1L);
		if (IFIX(entry_hash) < key_hash_value || IFIX(entry_hash) 
			== key_hash_value &&  !EQ(key_value,ISVREF(curr,
			(SI_Long)2L))) {
		    pred = curr;
		    curr = succ;
		}
		else
		    goto end_16;
		goto next_loop_47;
	      end_loop_48:
	      end_16:
		level = level - (SI_Long)1L;
		goto next_loop_46;
	      end_loop_46:;
		resulting_value = IFIX(ISVREF(curr,(SI_Long)1L)) == 
			key_hash_value ? (EQ(key_value,ISVREF(curr,
			(SI_Long)2L)) ? ISVREF(curr,(SI_Long)3L) : Nil) : Nil;
		if (resulting_value);
		else
		    resulting_value = Nil;
	    }
	    gensymed_symbol = resulting_value;
	    ab_loop_it_ = 
		    ISVREF(get_slot_description_of_class_description_function(Qicon_description,
		    gensymed_symbol,Nil),(SI_Long)6L);
	}
	else
	    ab_loop_it_ = Nil;
	if (ab_loop_it_) {
	    temp_3 = TRUEP(ab_loop_it_);
	    goto end_17;
	}
	goto next_loop;
      end_loop:
	temp_3 = TRUEP(Qnil);
      end_17:;
    }
    else
	temp_3 = TRUEP(Nil);
    if ( !temp_3) {
	temp = Bad_phrase;
	temp_1 = tformat_text_string(2,string_constant_20,item);
	return VALUES_2(temp,temp_1);
    }
    if (EQ(parse_result,Qinherited) || EQ(parse_result,Qnil))
	return VALUES_1(Nil);
    else {
	width = FIRST(parse_result);
	height = SECOND(parse_result);
	rest_1 = CDDR(parse_result);
	temp_1 = CAR(rest_1);
	if (CONSP(temp_1) && EQ(CAAR(rest_1),Qpolychrome)) {
	    unfixed_region_specification_list = CAR(rest_1);
	    if (CONSP(unfixed_region_specification_list)) {
		temp_1 = last(unfixed_region_specification_list,_);
		temp_3 =  !TRUEP(CDR(temp_1));
	    }
	    else
		temp_3 = TRUEP(Nil);
	    if ( !temp_3)
		region_specification_qm = phrase_list_2(Qpolychrome,
			CDR(unfixed_region_specification_list));
	    else {
		temp_1 = SECOND(unfixed_region_specification_list);
		if (SYMBOLP(temp_1))
		    region_specification_qm = phrase_cons(Qpolychrome,
			    CDDR(unfixed_region_specification_list));
		else
		    region_specification_qm = 
			    unfixed_region_specification_list;
	    }
	}
	else
	    region_specification_qm = Nil;
	variable_specification_qm = get_variable_specification_if_any(rest_1);
	icon_background_layer_qm = get_icon_background_layer_if_any(rest_1);
	icon_background_layer_spec_qm = SECOND(icon_background_layer_qm);
	stipple_qm = get_icon_stipple_if_any(rest_1);
	header_count = FIX((SI_Long)0L);
	if (region_specification_qm)
	    header_count = FIXNUM_ADD1(header_count);
	if (variable_specification_qm)
	    header_count = FIXNUM_ADD1(header_count);
	if (icon_background_layer_qm)
	    header_count = FIXNUM_ADD1(header_count);
	if (stipple_qm)
	    header_count = FIXNUM_ADD1(header_count);
	unfixed_element_list = nthcdr(header_count,rest_1);
	element_list_1 = EQ(CAR(unfixed_element_list),Qsc) ? 
		CDR(unfixed_element_list) : 
		phrase_cons(unfixed_element_list,Nil);
	element_list = 
		normalize_line_drawing_elements_from_parse(element_list_1);
	bad_background_layer_qm = SYMBOLP(icon_background_layer_spec_qm) 
		&&  
		!TRUEP(color_or_metacolor_p(icon_background_layer_spec_qm)) 
		&& ( !TRUEP(region_specification_qm) ||  
		!TRUEP(assq_function(icon_background_layer_spec_qm,
		CDR(region_specification_qm)))) ? 
		icon_background_layer_spec_qm : Nil;
	variable_spec_list = CDR(variable_specification_qm);
	name = Nil;
	value = Nil;
	ab_loop_list_ = variable_spec_list;
	bad_name_qm = Nil;
	ab_loop_it_ = Nil;
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_49;
      next_loop_49:
	name = CAR(ab_loop_list_);
	temp_1 = CDR(ab_loop_list_);
	value = CAR(temp_1);
	bad_name_qm = memq_function(name,Reserved_icon_variable_names);
	ab_loop_it_ = bad_name_qm ? name : Nil;
	if (ab_loop_it_) {
	    bad_variable_name_qm = ab_loop_it_;
	    goto end_18;
	}
	ab_loop_list_ = CDDR(ab_loop_list_);
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_49;
	goto next_loop_49;
      end_loop_49:
	bad_variable_name_qm = Qnil;
      end_18:;
	variable_spec_list = CDR(variable_specification_qm);
	element = Nil;
	ab_loop_list_ = element_list;
	bad_variable_qm = Nil;
	ab_loop_it_ = Nil;
      next_loop_50:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_50;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	bad_variable_qm = element_contains_bad_variable_qm(element,
		variable_spec_list);
	ab_loop_it_ = bad_variable_qm ? gensym_list_2(bad_variable_qm,
		element) : Nil;
	if (ab_loop_it_) {
	    bad_variable_in_element_qm = ab_loop_it_;
	    goto end_19;
	}
	goto next_loop_50;
      end_loop_50:
	bad_variable_in_element_qm = Qnil;
      end_19:;
	if ( !TRUEP(bad_variable_in_element_qm)) {
	    element = Nil;
	    ab_loop_list_ = element_list;
	    ab_loop_it_ = Nil;
	  next_loop_51:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_51;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (CONSP(element) && EQ(CAR(element),Qfilled_polygon)) {
		current_icon_untransformed_width = width;
		PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
			3);
		  current_icon_untransformed_height = height;
		  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
			  2);
		    current_icon_variables_plist = 
			    CDR(variable_specification_qm);
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
			    1);
		      current_icon_variables_override_plist = Nil;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
			      0);
			temp_3 = TRUEP(simple_polygon_p(CDR(element)));
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
		if ( !temp_3)
		    ab_loop_it_ = gensym_list_2(element,Qnot_simple_polygon);
		else if (FIXNUM_GT(length(CDR(element)),
			Maximum_polygon_points))
		    ab_loop_it_ = gensym_list_2(element,Qtoo_many_points);
		else
		    ab_loop_it_ = Qnil;
	    }
	    else
		ab_loop_it_ = Nil;
	    if (ab_loop_it_) {
		bad_polygon_qm = ab_loop_it_;
		goto end_20;
	    }
	    goto next_loop_51;
	  end_loop_51:
	    bad_polygon_qm = Qnil;
	  end_20:;
	}
	else
	    bad_polygon_qm = Nil;
	element = Nil;
	ab_loop_list_ = element_list;
	ab_loop_it_ = Nil;
      next_loop_52:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_52;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loop_it_ = SYMBOLP(element) &&  
		!TRUEP(color_or_metacolor_p(element)) && ( 
		!TRUEP(region_specification_qm) ||  
		!TRUEP(assq_function(element,
		CDR(region_specification_qm)))) ? element : Nil;
	if (ab_loop_it_) {
	    bad_region_or_color_or_metacolor_qm = ab_loop_it_;
	    goto end_21;
	}
	goto next_loop_52;
      end_loop_52:
	bad_region_or_color_or_metacolor_qm = Qnil;
      end_21:;
	error_text_qm = Nil;
	if (bad_background_layer_qm) {
	    temp = Bad_phrase;
	    temp_1 = make_bad_region_text_string(bad_background_layer_qm);
	    return VALUES_2(temp,temp_1);
	}
	else if (bad_region_or_color_or_metacolor_qm) {
	    temp = Bad_phrase;
	    temp_1 = 
		    make_bad_region_text_string(bad_region_or_color_or_metacolor_qm);
	    return VALUES_2(temp,temp_1);
	}
	else if (bad_polygon_qm) {
	    polygon = CAR(bad_polygon_qm);
	    reason = CADR(bad_polygon_qm);
	    reclaim_gensym_list_1(bad_polygon_qm);
	    temp = Bad_phrase;
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
		      twrite(string_constant_21);
		      write_drawing_element(EQ(CAR(polygon),
			      Qfilled_polygon) ? 
			      phrase_list_2(Qfilled_polygon,CDR(polygon)) :
			       polygon);
		      if (EQ(reason,Qnot_simple_polygon))
			  twrite(string_constant_22);
		      else if (EQ(reason,Qtoo_many_points))
			  tformat(3,string_constant_23,
				  length(CDR(polygon)),Maximum_polygon_points);
		      else
			  twrite(string_constant_24);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return VALUES_2(temp,temp_1);
	}
	else if (bad_variable_name_qm)
	    return reserved_icon_variable_message(bad_variable_name_qm);
	else if (bad_variable_in_element_qm) {
	    bad_variable = FIRST(bad_variable_in_element_qm);
	    reason_for_rejection = FIRST(bad_variable);
	    variable_name = SECOND(bad_variable);
	    variable_value_qm = 
		    getfq_function_no_default(CDR(variable_specification_qm),
		    variable_name);
	    bad_element = SECOND(bad_variable_in_element_qm);
	    reclaim_gensym_cons_1(bad_variable_in_element_qm);
	    return bad_variable_in_element_message(bad_element,
		    variable_name,variable_value_qm,reason_for_rejection);
	}
	else {
	    error_text_qm = check_icon_size(width,height);
	    if (error_text_qm)
		return VALUES_2(Bad_phrase,error_text_qm);
	    else {
		element = Nil;
		ab_loop_list_ = element_list;
	      next_loop_53:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_53;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (CONSP(element) && EQ(CAR(element),Qfilled_polygon)) {
		    current_icon_untransformed_width = width;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
			    3);
		      current_icon_untransformed_height = height;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
			      2);
			current_icon_variables_plist = 
				CDR(variable_specification_qm);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
				1);
			  current_icon_variables_override_plist = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
				  0);
			    temp_3 = TRUEP(clockwise_polygon_p(CDR(element)));
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    if ( !temp_3) {
			temp_2 = nreverse(CDR(element));
			M_CDR(element) = temp_2;
		    }
		    temp = CDR(element);
		    current_icon_untransformed_width = width;
		    PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_width,Qcurrent_icon_untransformed_width,current_icon_untransformed_width,
			    3);
		      current_icon_untransformed_height = height;
		      PUSH_SPECIAL_WITH_SYMBOL(Current_icon_untransformed_height,Qcurrent_icon_untransformed_height,current_icon_untransformed_height,
			      2);
			current_icon_variables_plist = 
				CDR(variable_specification_qm);
			PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_plist,Qcurrent_icon_variables_plist,current_icon_variables_plist,
				1);
			  current_icon_variables_override_plist = Nil;
			  PUSH_SPECIAL_WITH_SYMBOL(Current_icon_variables_override_plist,Qcurrent_icon_variables_override_plist,current_icon_variables_override_plist,
				  0);
			    temp_1 = decompose_polygon(1,CDR(element));
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		    temp_2 = phrase_cons(temp,temp_1);
		    M_CDR(element) = temp_2;
		}
		goto next_loop_53;
	      end_loop_53:;
		polychrome_header = region_specification_qm;
		if (polychrome_header);
		else
		    polychrome_header = phrase_cons(Qpolychrome,Nil);
		variable_header = variable_specification_qm;
		if (variable_header);
		else
		    variable_header = phrase_cons(Qvariables,Nil);
		background_header = icon_background_layer_qm;
		if (background_header);
		else
		    background_header = phrase_cons(Qbackground_layer,Nil);
		element = Nil;
		ab_loop_list_ = element_list;
	      next_loop_54:
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_54;
		element = M_CAR(ab_loop_list_);
		ab_loop_list_ = M_CDR(ab_loop_list_);
		if (SYMBOLP(element) &&  !TRUEP(assq_function(element,
			CDR(polychrome_header)))) {
		    temp_2 = phrase_cons(phrase_cons(element,element),
			    CDR(polychrome_header));
		    M_CDR(polychrome_header) = temp_2;
		}
		goto next_loop_54;
	      end_loop_54:;
		temp_1 = CAR(element_list);
		if ( !SYMBOLP(temp_1) && CDR(polychrome_header) &&  
			!TRUEP(assq_function(Qforeground,
			CDR(polychrome_header)))) {
		    temp_2 = phrase_cons(phrase_cons(Qforeground,
			    Qforeground),CDR(polychrome_header));
		    M_CDR(polychrome_header) = temp_2;
		}
		return phrase_cons(width,phrase_cons(height,
			phrase_cons(polychrome_header,
			phrase_cons(variable_header,
			phrase_cons(background_header,nconc2(stipple_qm ? 
			phrase_cons(phrase_list_2(Qstipple,stipple_qm),
			Nil) : Nil,element_list))))));
	    }
	}
    }
}

static Object Qoutline;            /* outline */

static Object Qlines;              /* lines */

/* NORMALIZE-LINE-DRAWING-ELEMENTS-FROM-PARSE */
Object normalize_line_drawing_elements_from_parse(parse_result_element_list)
    Object parse_result_element_list;
{
    Object element, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object temp;

    x_note_fn_call(202,26);
    element = Nil;
    ab_loop_list_ = parse_result_element_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (CONSP(element)) {
	temp = CAR(element);
	if (EQ(temp,Qfilled_polygon) || EQ(temp,Qoutline) || EQ(temp,Qlines)) {
	    temp = CAR(element);
	    temp = phrase_cons(temp,
		    flatten_point_tree_phrase_into_list(CDR(element)));
	}
	else
	    temp = Nil;
    }
    else
	temp = Nil;
    if (temp);
    else
	temp = element;
    ab_loopvar__2 = phrase_cons(temp,Nil);
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

static Object string_constant_25;  /* "The symbol ~a does not belong here, since it ~
				    *      is not a declared region, a color, or a metacolor."
				    */

/* MAKE-BAD-REGION-TEXT-STRING */
Object make_bad_region_text_string(symbol)
    Object symbol;
{
    x_note_fn_call(202,27);
    return tformat_text_string(2,string_constant_25,symbol);
}

static Object array_constant_10;   /* # */

static Object array_constant_11;   /* # */

static Object string_constant_26;  /* ";~%" */

/* WRITE-REGION-SPECIFICATION-LIST */
Object write_region_specification_list(region_specification_list)
    Object region_specification_list;
{
    Object wrote_some_qm, region_or_color_or_metacolor, color_or_metacolor;
    Object ab_loop_list_, temp;

    x_note_fn_call(202,28);
    wrote_some_qm = Nil;
    region_or_color_or_metacolor = Nil;
    color_or_metacolor = Nil;
    ab_loop_list_ = region_specification_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    temp = CAR(ab_loop_list_);
    region_or_color_or_metacolor = CAR(temp);
    temp = CAR(ab_loop_list_);
    color_or_metacolor = CDR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !EQ(region_or_color_or_metacolor,color_or_metacolor)) {
	if (wrote_some_qm)
	    twrite_beginning_of_wide_string(array_constant_10,
		    FIX((SI_Long)2L));
	twrite_symbol(1,region_or_color_or_metacolor);
	twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)3L));
	twrite_color(color_or_metacolor);
	wrote_some_qm = T;
    }
    goto next_loop;
  end_loop:
    if (wrote_some_qm)
	tformat(1,string_constant_26);
    return VALUES_1(Qnil);
}

/* WRITE-VARIABLE-NAME-AND-VALUE */
Object write_variable_name_and_value(name,value)
    Object name, value;
{
    x_note_fn_call(202,29);
    twrite_symbol(1,name);
    twrite_beginning_of_wide_string(array_constant_11,FIX((SI_Long)3L));
    if (text_string_p(value))
	return tformat(2,string_constant_1,value);
    else
	return twrite(value);
}

static Object string_constant_27;  /* "variables :~%    " */

/* WRITE-VARIABLE-SPECIFICATION-LIST */
Object write_variable_specification_list(variable_specification_list)
    Object variable_specification_list;
{
    Object wrote_some_qm, variable_name, value, more_qm, ab_loop_list_, temp;

    x_note_fn_call(202,30);
    tformat(1,string_constant_27);
    wrote_some_qm = Nil;
    variable_name = Nil;
    value = Nil;
    more_qm = Nil;
    ab_loop_list_ = variable_specification_list;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    variable_name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    temp = CDR(ab_loop_list_);
    more_qm = CDR(temp);
    write_variable_name_and_value(variable_name,value);
    if (more_qm)
	twrite_beginning_of_wide_string(array_constant_10,FIX((SI_Long)2L));
    wrote_some_qm = T;
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    if (wrote_some_qm)
	tformat(1,string_constant_26);
    return VALUES_1(Qnil);
}

static Object string_constant_28;  /* "icon-background-layer : " */

static Object string_constant_29;  /* "color image " */

static Object string_constant_30;  /* "; ~%" */

/* WRITE-ICON-BACKGROUND-LAYER */
Object write_icon_background_layer(background_layer)
    Object background_layer;
{
    x_note_fn_call(202,31);
    tformat(1,string_constant_28);
    if (CONSP(background_layer) && EQ(FIRST(background_layer),Qimage)) {
	tformat(1,string_constant_29);
	if ( !TRUEP(background_layer))
	    twrite_beginning_of_wide_string(array_constant,FIX((SI_Long)4L));
	else if (ATOM(background_layer))
	    twrite(background_layer);
	else {
	    tformat(2,string_constant_6,SECOND(background_layer));
	    if (THIRD(background_layer)) {
		tformat(1,string_constant_3);
		write_point(THIRD(background_layer));
	    }
	}
    }
    else
	twrite_symbol(1,background_layer);
    return tformat(1,string_constant_30);
}

static Object string_constant_31;  /* "inherited" */

static Object string_constant_32;  /* "width ~d; " */

static Object string_constant_33;  /* "height ~d;~%" */

static Object string_constant_34;  /* "stipple: ~(~a~);~%" */

static Object string_constant_35;  /* "    " */

static Object string_constant_36;  /* ":~%" */

/* WRITE-ICON-DESCRIPTION?-FROM-SLOT */
Object write_icon_description_qm_from_slot(icon_description_qm,gensymed_symbol)
    Object icon_description_qm, gensymed_symbol;
{
    Object width, height, line_drawing_description, temp, polychrome_header_qm;
    Object variable_header_qm, background_header_qm, stipple_qm, header_count;
    Object element_list, element, more_qm, ab_loop_list_;

    x_note_fn_call(202,32);
    if ( !TRUEP(icon_description_qm))
	return twrite(string_constant_31);
    else {
	width = FIRST(icon_description_qm);
	height = SECOND(icon_description_qm);
	line_drawing_description = CDDR(icon_description_qm);
	temp = CAR(line_drawing_description);
	polychrome_header_qm = CONSP(temp) && 
		EQ(CAAR(line_drawing_description),Qpolychrome) ? 
		CAR(line_drawing_description) : Nil;
	variable_header_qm = 
		get_variable_specification_if_any(line_drawing_description);
	background_header_qm = 
		get_icon_background_layer_if_any(line_drawing_description);
	stipple_qm = get_icon_stipple_if_any(line_drawing_description);
	header_count = FIX((SI_Long)0L);
	if (polychrome_header_qm)
	    header_count = FIXNUM_ADD1(header_count);
	if (variable_header_qm)
	    header_count = FIXNUM_ADD1(header_count);
	if (background_header_qm)
	    header_count = FIXNUM_ADD1(header_count);
	if (stipple_qm)
	    header_count = FIXNUM_ADD1(header_count);
	element_list = nthcdr(header_count,line_drawing_description);
	tformat(2,string_constant_32,width);
	tformat(2,string_constant_33,height);
	if (polychrome_header_qm)
	    write_region_specification_list(CDR(polychrome_header_qm));
	if (CDR(variable_header_qm))
	    write_variable_specification_list(CDR(variable_header_qm));
	if (CDR(background_header_qm))
	    write_icon_background_layer(SECOND(background_header_qm));
	if (stipple_qm)
	    tformat(2,string_constant_34,stipple_qm);
	element = Nil;
	more_qm = Nil;
	ab_loop_list_ = element_list;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	element = CAR(ab_loop_list_);
	more_qm = CDR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (SYMBOLP(element))
	    twrite_symbol(1,element);
	else {
	    twrite(string_constant_35);
	    write_drawing_element(element);
	}
	if (more_qm)
	    tformat(1,SYMBOLP(element) ? string_constant_36 : 
		    string_constant_26);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
}

static Object string_constant_37;  /* "stippled area ~(~a~)" */

static Object list_constant_2;     /* # */

static Object string_constant_38;  /* "filled rectangle" */

static Object string_constant_39;  /* "filled polygon" */

static Object string_constant_40;  /* "filled circle" */

static Object array_constant_12;   /* # */

static Object array_constant_13;   /* # */

/* WRITE-DRAWING-ELEMENT */
Object write_drawing_element(element)
    Object element;
{
    Object temp, point, ab_loop_list_;

    x_note_fn_call(202,33);
    temp = CAR(element);
    if (EQ(temp,Qstippled_area)) {
	tformat(2,string_constant_37,SECOND(element));
	point = Nil;
	ab_loop_list_ = CDDR(element);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	point = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_point(point);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (member_eql(temp,list_constant_2)) {
	temp = CAR(element);
	if (EQ(temp,Qsolid_rectangle))
	    twrite(string_constant_38);
	else if (EQ(temp,Qfilled_polygon))
	    twrite(string_constant_39);
	else if (EQ(temp,Qfilled_circle))
	    twrite(string_constant_40);
	else
	    twrite_symbol(1,CAR(element));
	point = Nil;
	ab_loop_list_ = EQ(CAR(element),Qfilled_polygon) ? SECOND(element) 
		: CDR(element);
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	point = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	write_point(point);
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(Qnil);
    }
    else if (EQ(temp,Qtext)) {
	twrite_beginning_of_wide_string(array_constant_12,FIX((SI_Long)5L));
	return write_text_specification(element);
    }
    else if (EQ(temp,Qimage)) {
	twrite_beginning_of_wide_string(array_constant_13,FIX((SI_Long)6L));
	if ( !TRUEP(element))
	    return twrite_beginning_of_wide_string(array_constant,
		    FIX((SI_Long)4L));
	else if (ATOM(element))
	    return twrite(element);
	else {
	    tformat(2,string_constant_6,SECOND(element));
	    if (THIRD(element)) {
		tformat(1,string_constant_3);
		return write_point(THIRD(element));
	    }
	    else
		return VALUES_1(Nil);
	}
    }
    else
	return VALUES_1(Qnil);
}

/* RESOLVE-CONSTANTS */
Object resolve_constants(expression)
    Object expression;
{
    Object function, arg1, arg2_qm, arg2, args, result_1;

    x_note_fn_call(202,34);
    if (FIXNUMP(expression))
	return VALUES_1(expression);
    else if (SYMBOLP(expression))
	return VALUES_1(FIX((SI_Long)0L));
    else {
	function = CAR(expression);
	arg1 = resolve_constants(SECOND(expression));
	arg2_qm = THIRD(expression);
	arg2 = arg2_qm ? resolve_constants(arg2_qm) : Nil;
	args = arg2_qm ? slot_value_list_2(arg1,arg2) : 
		slot_value_list_2(FIX((SI_Long)0L),arg1);
	result_1 = simple_apply_for_icon(function,args);
	reclaim_slot_value(args);
	return VALUES_1(result_1);
    }
}

/* DISTRIBUTE-MINUS-SIGN */
Object distribute_minus_sign(expression)
    Object expression;
{
    Object new_expression, reverse_expression, symbol_or_sign, ab_loop_list_;

    x_note_fn_call(202,35);
    new_expression = Nil;
    reverse_expression = nreverse(expression);
    symbol_or_sign = Nil;
    ab_loop_list_ = reverse_expression;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    symbol_or_sign = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(symbol_or_sign,Qplus))
	new_expression = slot_value_cons_1(Qminus,new_expression);
    else if (EQ(symbol_or_sign,Qminus))
	new_expression = slot_value_cons_1(Qplus,new_expression);
    else
	new_expression = slot_value_cons_1(symbol_or_sign,new_expression);
    goto next_loop;
  end_loop:
    reclaim_slot_value(reverse_expression);
    return VALUES_1(new_expression);
    return VALUES_1(Qnil);
}

static Object Qab_slot_value;      /* slot-value */

/* ADD-PLUS-TO-FRONT */
Object add_plus_to_front(expression)
    Object expression;
{
    Object temp, slot_value_pop_store, cons_1, next_cons, temp_1, svref_arg_2;
    Object neg_num;

    x_note_fn_call(202,36);
    if ( !TRUEP(expression))
	return VALUES_1(expression);
    else if (EQ(CAR(expression),Qplus) || EQ(CAR(expression),Qminus))
	return VALUES_1(expression);
    else {
	temp = CAR(expression);
	if (INTEGERP(temp) && IFIX(CAR(expression)) < (SI_Long)0L) {
	    slot_value_pop_store = Nil;
	    cons_1 = expression;
	    if (cons_1) {
		slot_value_pop_store = M_CAR(cons_1);
		next_cons = M_CDR(cons_1);
		inline_note_reclaim_cons(cons_1,Qab_slot_value);
		if (ISVREF(Available_slot_value_conses_tail_vector,
			IFIX(Current_thread_index))) {
		    temp_1 = 
			    ISVREF(Available_slot_value_conses_tail_vector,
			    IFIX(Current_thread_index));
		    M_CDR(temp_1) = cons_1;
		    temp_1 = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		}
		else {
		    temp_1 = Available_slot_value_conses_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		    temp_1 = Available_slot_value_conses_tail_vector;
		    svref_arg_2 = Current_thread_index;
		    SVREF(temp_1,svref_arg_2) = cons_1;
		}
		M_CDR(cons_1) = Nil;
	    }
	    else
		next_cons = Nil;
	    expression = next_cons;
	    neg_num = slot_value_pop_store;
	    return VALUES_1(nconc2(slot_value_list_2(Qminus,
		    FIX((SI_Long)-1L * IFIX(neg_num))),expression));
	}
	else {
	    expression = slot_value_cons_1(Qplus,expression);
	    return VALUES_1(expression);
	}
    }
}

/* REMOVE-PLUS-FROM-FRONT */
Object remove_plus_from_front(expression)
    Object expression;
{
    x_note_fn_call(202,37);
    if (EQ(CAR(expression),Qplus))
	return VALUES_1(CDR(expression));
    else
	return VALUES_1(expression);
}

/* EXTRACT-CONSTANTS */
Object extract_constants(expression)
    Object expression;
{
    Object third_expression, temp, result_1, second_expression;

    x_note_fn_call(202,38);
    if (FIXNUMP(expression))
	return VALUES_1(Nil);
    else if (SYMBOLP(expression))
	return slot_value_cons_1(expression,Nil);
    else if (EQ(FIRST(expression),Qminus) && THIRD(expression)) {
	third_expression = 
		add_plus_to_front(extract_constants(THIRD(expression)));
	temp = extract_constants(SECOND(expression));
	result_1 = nconc2(temp,
		distribute_minus_sign(copy_for_slot_value(third_expression)));
	reclaim_slot_value(third_expression);
	return VALUES_1(result_1);
    }
    else if (EQ(FIRST(expression),Qminus)) {
	second_expression = 
		add_plus_to_front(extract_constants(SECOND(expression)));
	result_1 = 
		remove_plus_from_front(distribute_minus_sign(copy_for_slot_value(second_expression)));
	reclaim_slot_value(second_expression);
	return VALUES_1(result_1);
    }
    else {
	temp = extract_constants(SECOND(expression));
	return VALUES_1(nconc2(temp,
		add_plus_to_front(extract_constants(THIRD(expression)))));
    }
}

/* EVAL-POINT-EXPRESSION */
Object eval_point_expression(expression)
    Object expression;
{
    Object resolved_constants, variables, result_1, reverse_variables, elt_1;
    Object ab_loop_list_;

    x_note_fn_call(202,39);
    resolved_constants = resolve_constants(expression);
    variables = remove_plus_from_front(extract_constants(expression));
    if ( !TRUEP(variables))
	return VALUES_1(resolved_constants);
    else if (EQ(resolved_constants,FIX((SI_Long)0L))) {
	if (CDR(variables))
	    return VALUES_1(variables);
	else {
	    result_1 = CAR(variables);
	    reclaim_slot_value_cons_1(variables);
	    return VALUES_1(result_1);
	}
    }
    else if (EQ(CAR(variables),Qminus)) {
	variables = slot_value_cons_1(resolved_constants,variables);
	return VALUES_1(variables);
    }
    else {
	result_1 = add_plus_to_front(slot_value_cons_1(resolved_constants,
		Nil));
	reverse_variables = nreverse(variables);
	elt_1 = Nil;
	ab_loop_list_ = reverse_variables;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result_1 = slot_value_cons_1(elt_1,result_1);
	goto next_loop;
      end_loop:
	reclaim_slot_value(reverse_variables);
	return VALUES_1(result_1);
	return VALUES_1(Qnil);
    }
}

static Object string_constant_41;  /* " arc (~A, ~A)" */

static Object string_constant_42;  /* " (~A, ~A)" */

/* WRITE-POINT */
Object write_point(point)
    Object point;
{
    Object temp, temp_2, non_arc_point, eval_point_x, eval_point_y;
    char temp_1;

    x_note_fn_call(202,40);
    if (CONSP(point)) {
	temp = M_CDR(point);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (((temp_1 ?  !TRUEP(M_CDR(M_CDR(point))) : TRUEP(Nil)) ? 
	    FIXNUMP(M_CAR(point)) : TRUEP(Nil)) ? 
	    FIXNUMP(M_CAR(M_CDR(point))) : TRUEP(Nil)) {
	if (EQ(CAR(point),Qarc)) {
	    temp_2 = SECOND(point);
	    temp = SECOND(point);
	    return tformat(3,string_constant_41,FIRST(temp_2),SECOND(temp));
	}
	else
	    return tformat(3,string_constant_42,FIRST(point),SECOND(point));
    }
    else {
	non_arc_point = EQ(CAR(point),Qarc) ? SECOND(point) : point;
	eval_point_x = eval_point_expression(FIRST(non_arc_point));
	eval_point_y = eval_point_expression(SECOND(non_arc_point));
	if (EQ(CAR(point),Qarc))
	    tformat(3,string_constant_41,eval_point_x,eval_point_y);
	else
	    tformat(3,string_constant_42,eval_point_x,eval_point_y);
	reclaim_slot_value(eval_point_x);
	return reclaim_slot_value(eval_point_y);
    }
}

static Object list_constant_3;     /* # */

static Object list_constant_4;     /* # */

static Object Qregion_name;        /* region-name */

static Object Qcolor_or_metacolor;  /* color-or-metacolor */

static Object Qcategory_evaluator_interface;  /* category-evaluator-interface */

static Object Qcolor_name;         /* color-name */

/* REGION-SPECIFICATION-EVALUATION-SETTER */
Object region_specification_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,41);
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
			  list_constant_3))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_4,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_region_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp = estructure_slot(gensymed_symbol,Qregion_name,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcolor_or_metacolor),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qcolor_name,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(temp,temp_1);
  end_safe_category_setter_calling_block:
  end_region_specification_evaluation_setter:
    return result;
}

/* REGION-SPECIFICATION-EVALUATION-GETTER */
Object region_specification_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,42);
    if ( !EQ(CAR(slot_value),CDR(slot_value))) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(gensymed_symbol,Qregion_name,
		CAR(slot_value));
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcolor_or_metacolor),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CDR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qcolor_name,temp);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_5;     /* # */

static Object list_constant_6;     /* # */

static Object Qregion_specification;  /* region-specification */

/* REGION-SPECIFICATION-LIST-EVALUATION-SETTER */
Object region_specification_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object region_specification, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object elt_1, validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,43);
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
			  list_constant_5))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_6,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_region_specification_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (evaluation_value) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	region_specification = Nil;
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
	region_specification = validated_elt;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qregion_specification),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = region_specification;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
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
      end_safe_category_setter_calling_block:;
    }
    else
	result = VALUES_1(Nil);
  end_region_specification_list_evaluation_setter:
    return result;
}

/* REGION-SPECIFICATION-LIST-EVALUATION-GETTER */
Object region_specification_list_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object result_1, region_specification, ab_loop_list_, region_info_qm;
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(202,44);
    result_1 = Nil;
    region_specification = Nil;
    ab_loop_list_ = slot_value;
    region_info_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    region_specification = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qregion_specification),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = region_specification;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	region_info_qm = inline_funcall_3(gensymed_symbol,
		gensymed_symbol_1,gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	region_info_qm = Nil;
    if (region_info_qm)
	result_1 = eval_cons_1(region_info_qm,result_1);
    goto next_loop;
  end_loop:
    temp = result_1 ? allocate_evaluation_sequence(nreverse(result_1)) : Nil;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

/* VARIABLE-SPECIFICATION-EVALUATION-SETTER */
Object variable_specification_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,45);
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
			  list_constant_7))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_8,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_variable_specification_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(Nil);
  end_variable_specification_evaluation_setter:
    return result;
}

static Object Qvariable_name;      /* variable-name */

static Object Qfloat_array;        /* float-array */

static Object Qtruth_value;        /* truth-value */

static Object Qinitial_value;      /* initial-value */

/* VARIABLE-SPECIFICATION-EVALUATION-GETTER */
Object variable_specification_evaluation_getter(name,value,slot_description)
    Object name, value, slot_description;
{
    Object gensymed_symbol, temp, amf_available_array_cons_qm, amf_array;
    Object temp_1, temp_2, amf_result, new_float, gensymed_symbol_1;
    double aref_new_value;

    x_note_fn_call(202,46);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qvariable_name,name);
    if (FIXNUMP(value))
	temp = value;
    else if ( !TRUEP(value))
	temp = Evaluation_false_value;
    else if (EQ(value,T))
	temp = Evaluation_true_value;
    else if (SYMBOLP(value))
	temp = value;
    else if (INLINE_DOUBLE_FLOAT_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	temp = copy_managed_float(value);
    else if (FLOATP(value)) {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_1 = Vector_of_simple_float_array_pools;
	    temp_2 = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_1,FIX((SI_Long)1L)) = temp_2;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qfloat_array);
	    if (ISVREF(Available_float_array_conses_tail_vector,
		    IFIX(Current_thread_index))) {
		temp_1 = ISVREF(Available_float_array_conses_tail_vector,
			IFIX(Current_thread_index));
		M_CDR(temp_1) = amf_available_array_cons_qm;
		temp_1 = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
	    }
	    else {
		temp_1 = Available_float_array_conses_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
		temp_1 = Available_float_array_conses_tail_vector;
		temp_2 = Current_thread_index;
		SVREF(temp_1,temp_2) = amf_available_array_cons_qm;
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
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(value);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	temp = new_float;
    }
    else if (INLINE_LONG_VECTOR_P(value) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) == (SI_Long)1L)
	temp = copy_managed_long(value);
    else if (INLINE_LONG_P(value) != (SI_Long)0L)
	temp = make_evaluation_long(value);
    else if (text_string_p(value))
	temp = copy_as_wide_string(value);
    else if (CONSP(value) && EQ(M_CDR(value),Qtruth_value)) {
	gensymed_symbol_1 = M_CAR(value);
	if (FIXNUM_EQ(gensymed_symbol_1,Truth))
	    temp = Evaluation_true_value;
	else if (FIXNUM_EQ(gensymed_symbol_1,Falsity))
	    temp = Evaluation_false_value;
	else
	    temp = eval_cons_1(gensymed_symbol_1,Qtruth_value);
    }
    else
	temp = error((SI_Long)2L,
		"Bad type ~a for make-evaluation-value-based-on-type.",
		type_of(value));
    set_evaluation_structure_slot(gensymed_symbol,Qinitial_value,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_9;     /* # */

static Object list_constant_10;    /* # */

/* VARIABLE-SPECIFICATION-LIST-EVALUATION-SETTER */
Object variable_specification_list_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, plist, held_vector;
    Object variable_spec, elt_1, validated_elt;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,47);
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
		      goto end_variable_specification_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    plist = Nil;
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    variable_spec = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    variable_spec = validated_elt;
    gensymed_symbol = variable_spec;
    temp_1 = estructure_slot(gensymed_symbol,Qvariable_name,Nil);
    plist = phrase_cons(temp_1,plist);
    temp_1 = estructure_slot(gensymed_symbol,Qinitial_value,Nil);
    plist = phrase_cons(temp_1,plist);
    goto next_loop;
  end_loop:
    result = nreverse(plist);
    goto end_1;
    result = VALUES_1(Qnil);
  end_1:;
  end_variable_specification_list_evaluation_setter:
    return result;
}

static Object Qvariable_specification;  /* variable-specification */

/* VARIABLE-SPECIFICATION-LIST-EVALUATION-GETTER */
Object variable_specification_list_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object eval_list, name, value, ab_loop_list_, temp;
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(202,48);
    eval_list = Nil;
    name = Nil;
    value = Nil;
    ab_loop_list_ = slot_value;
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
  next_loop:
    name = CAR(ab_loop_list_);
    temp = CDR(ab_loop_list_);
    value = CAR(temp);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvariable_specification),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = name;
	gensymed_symbol_2 = value;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    eval_list = eval_cons_1(temp,eval_list);
    ab_loop_list_ = CDDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    goto next_loop;
  end_loop:
    temp = eval_list ? allocate_evaluation_sequence(nreverse(eval_list)) : Nil;
    goto end_1;
    temp = Qnil;
  end_1:;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_11;    /* # */

static Object list_constant_12;    /* # */

/* FONT-SIZE-EVALUATION-SETTER */
Object font_size_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,49);
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
		      goto end_font_size_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = VALUES_1(evaluation_value);
  end_font_size_evaluation_setter:
    return result;
}

/* FONT-SIZE-EVALUATION-GETTER */
Object font_size_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(202,50);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_13;    /* # */

static Object list_constant_14;    /* # */

static Object Qunreserved_symbol;  /* unreserved-symbol */

/* POINT-FACTOR-EVALUATION-SETTER */
Object point_factor_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,51);
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
			  list_constant_13))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_14,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_point_factor_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (SYMBOLP(evaluation_value)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qunreserved_symbol),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
    else
	result = VALUES_1(evaluation_value);
  end_safe_category_setter_calling_block:
  end_point_factor_evaluation_setter:
    return result;
}

/* POINT-FACTOR-EVALUATION-GETTER */
Object point_factor_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    x_note_fn_call(202,52);
    GENSYM_RETURN_ONE(slot_value);
    return VALUES_1(Nil);
}

static Object list_constant_15;    /* # */

static Object Qpoint_sum;          /* point-sum */

/* POINT-SUM-EVALUATION-SETTER */
Object point_sum_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,53);
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
			  list_constant_15))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,Qtext,
			      Value_at_type_failure,Type_at_type_failure,
			      Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_point_sum_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    result = parse_text_string(2,evaluation_value,Qpoint_sum);
  end_point_sum_evaluation_setter:
    return result;
}

static Object string_constant_43;  /* "~A" */

/* POINT-SUM-EVALUATION-GETTER */
Object point_sum_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object evaluated_expression, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object result_1;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(202,54);
    evaluated_expression = eval_point_expression(slot_value);
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
	      tformat(2,string_constant_43,evaluated_expression);
	      result_1 = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    reclaim_slot_value(evaluated_expression);
    GENSYM_RETURN_ONE(result_1);
    return VALUES_1(Nil);
}

static Object list_constant_16;    /* # */

static Object list_constant_17;    /* # */

static Object Qpoint_factor;       /* point-factor */

/* POINT-EXPRESSION-EVALUATION-SETTER */
Object point_expression_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,55);
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
			  list_constant_16))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_17,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_point_expression_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (INTEGERP(evaluation_value) || SYMBOLP(evaluation_value)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_factor),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_sum),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
  end_safe_category_setter_calling_block:
  end_point_expression_evaluation_setter:
    return result;
}

/* POINT-EXPRESSION-EVALUATION-GETTER */
Object point_expression_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(202,56);
    if (INTEGERP(slot_value) || SYMBOLP(slot_value)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_factor),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_sum),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_18;    /* # */

static Object list_constant_19;    /* # */

static Object Qpoint_expression;   /* point-expression */

static Object Qx;                  /* x */

static Object Qy;                  /* y */

/* POINT-EVALUATION-SETTER */
Object point_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,57);
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
			  list_constant_18))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_19,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_point_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qx,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp = parse_result_or_bad_phrase;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qy,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_list_2(temp,temp_1);
  end_safe_category_setter_calling_block:
  end_point_evaluation_setter:
    return result;
}

/* POINT-EVALUATION-GETTER */
Object point_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,58);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CAR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qx,temp);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CADR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qy,temp);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_20;    /* # */

static Object list_constant_21;    /* # */

/* POINT-OR-ARCPOINT-EVALUATION-SETTER */
Object point_or_arcpoint_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object point;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,59);
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
			  list_constant_20))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_21,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_point_or_arcpoint_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qx,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp = parse_result_or_bad_phrase;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qy,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    point = phrase_list_2(temp,temp_1);
    temp_1 = estructure_slot(gensymed_symbol,Qarc,Nil);
    if (CONSP(temp_1) && EQ(M_CDR(estructure_slot(gensymed_symbol,Qarc,
	    Nil)),Qtruth_value) && 
	    evaluation_truth_value_true_p(estructure_slot(gensymed_symbol,
	    Qarc,Nil)))
	result = phrase_list_2(Qarc,point);
    else
	result = VALUES_1(point);
  end_safe_category_setter_calling_block:
  end_point_or_arcpoint_evaluation_setter:
    return result;
}

/* POINT-OR-ARCPOINT-EVALUATION-GETTER */
Object point_or_arcpoint_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp, thing, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4;
    char temp_1;

    x_note_fn_call(202,60);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	if (CONSP(slot_value) && EQ(M_CAR(slot_value),Qarc)) {
	    temp = M_CDR(slot_value);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ?  !TRUEP(M_CDR(M_CDR(slot_value))) : TRUEP(Nil)) {
	    thing = M_CAR(M_CDR(slot_value));
	    if (CONSP(thing)) {
		temp = CDR(thing);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qtruth_value),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = Truth;
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		temp = inline_funcall_3(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		temp = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,Qarc,temp);
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = CAADR(slot_value);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		temp = inline_funcall_3(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		temp = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,Qx,temp);
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = CADADR(slot_value);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		temp = inline_funcall_3(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		temp = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,Qy,temp);
	}
	else {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = CAR(slot_value);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		temp = inline_funcall_3(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		temp = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,Qx,temp);
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_expression),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = CADR(slot_value);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		temp = inline_funcall_3(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		temp = Nil;
	    set_evaluation_structure_slot(gensymed_symbol,Qy,temp);
	}
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_22;    /* # */

static Object list_constant_23;    /* # */

/* STATIC-POINT-EVALUATION-SETTER */
Object static_point_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,61);
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
			  list_constant_22))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_23,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_static_point_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qx,Nil);
    result = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,Qy,Nil));
  end_static_point_evaluation_setter:
    return result;
}

/* STATIC-POINT-EVALUATION-GETTER */
Object static_point_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, temp;

    x_note_fn_call(202,62);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	set_evaluation_structure_slot(gensymed_symbol,Qx,CAR(slot_value));
	set_evaluation_structure_slot(gensymed_symbol,Qy,CADR(slot_value));
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_24;    /* # */

static Object list_constant_25;    /* # */

static Object Qpoint;              /* point */

/* POINTS-EVALUATION-SETTER */
Object points_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector, point;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1, validated_elt;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,63);
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
			  list_constant_24))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_25,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_points_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    point = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    point = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = point;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(temp_1,Nil);
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
  end_safe_category_setter_calling_block:
  end_points_evaluation_setter:
    return result;
}

/* POINTS-EVALUATION-GETTER */
Object points_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object point, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(202,64);
    point = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    point = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = point;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
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
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_26;    /* # */

static Object list_constant_27;    /* # */

static Object Qpoint_or_arcpoint;  /* point-or-arcpoint */

/* POINTS-OR-ARCPOINTS-EVALUATION-SETTER */
Object points_or_arcpoints_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, held_vector;
    Object point_or_arcpoint, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, elt_1;
    Object validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,65);
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
			  list_constant_26))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_27,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_points_or_arcpoints_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    point_or_arcpoint = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    point_or_arcpoint = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_or_arcpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = point_or_arcpoint;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    ab_loopvar__2 = phrase_cons(temp_1,Nil);
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
  end_safe_category_setter_calling_block:
  end_points_or_arcpoints_evaluation_setter:
    return result;
}

/* POINTS-OR-ARCPOINTS-EVALUATION-GETTER */
Object points_or_arcpoints_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object point_or_arcpoint, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,66);
    point_or_arcpoint = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    point_or_arcpoint = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint_or_arcpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = point_or_arcpoint;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
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
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_28;    /* # */

static Object list_constant_29;    /* # */

static Object Qpoints;             /* points */

/* FILLED-POLYGON-POINT-TREE-EVALUATION-SETTER */
Object filled_polygon_point_tree_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,67);
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
			  list_constant_28))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_29,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_filled_polygon_point_tree_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = point_tree_phrase(temp_1);
  end_safe_category_setter_calling_block:
  end_filled_polygon_point_tree_evaluation_setter:
    return result;
}

/* FILLED-POLYGON-POINT-TREE-EVALUATION-GETTER */
Object filled_polygon_point_tree_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object point, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(202,68);
    point = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    point = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = point;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
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
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* VALID-POINTS-FOR-LINES-POINT-TREE-P */
Object valid_points_for_lines_point_tree_p(points)
    Object points;
{
    Object thing, temp, point1, point2, ab_loop_list_;
    char temp_1;

    x_note_fn_call(202,69);
    thing = CAR(points);
    if (CONSP(thing) && EQ(M_CAR(thing),Qarc)) {
	temp = M_CDR(thing);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(thing))) : TRUEP(Nil)) {
	thing = M_CAR(M_CDR(thing));
	if (CONSP(thing)) {
	    temp = CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(Nil);
    else {
	point1 = Nil;
	point2 = Nil;
	ab_loop_list_ = points;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	point1 = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	point2 = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(point1) && EQ(M_CAR(point1),Qarc)) {
	    temp = M_CDR(point1);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point1))) : TRUEP(Nil)) {
	    thing = M_CAR(M_CDR(point1));
	    if (CONSP(thing)) {
		temp = CDR(thing);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (CONSP(point2) && EQ(M_CAR(point2),Qarc)) {
		temp = M_CDR(point2);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point2))) : TRUEP(Nil)) {
		thing = M_CAR(M_CDR(point2));
		if (CONSP(thing)) {
		    temp = CDR(thing);
		    temp_1 = CONSP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1);
	    else
		temp_1 =  !TRUEP(point2);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

static Object list_constant_30;    /* # */

static Object list_constant_31;    /* # */

static Object Qpoints_or_arcpoints;  /* points-or-arcpoints */

static Object string_constant_44;  /* "~%The structure (type: the symbol lines, points: ~NV) contains an invalid use of arc points." */

/* LINES-POINT-TREE-EVALUATION-SETTER */
Object lines_point_tree_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm, points;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,70);
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
			  list_constant_30))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_31,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_lines_point_tree_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints_or_arcpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	points = parse_result_or_bad_phrase;
    if (valid_points_for_lines_point_tree_p(points))
	result = point_tree_phrase(points);
    else {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_44,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_lines_point_tree_evaluation_setter:
    return result;
}

/* LINES-POINT-TREE-EVALUATION-GETTER */
Object lines_point_tree_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(202,71);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints_or_arcpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* VALID-POINTS-FOR-OUTLINE-POINT-TREE-P */
Object valid_points_for_outline_point_tree_p(points)
    Object points;
{
    Object thing, temp, point1, point2, ab_loop_list_;
    char temp_1;

    x_note_fn_call(202,72);
    thing = CAR(points);
    if (CONSP(thing) && EQ(M_CAR(thing),Qarc)) {
	temp = M_CDR(thing);
	temp_1 = CONSP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(thing))) : TRUEP(Nil)) {
	thing = M_CAR(M_CDR(thing));
	if (CONSP(thing)) {
	    temp = CDR(thing);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return VALUES_1(Nil);
    else {
	point1 = Nil;
	point2 = Nil;
	ab_loop_list_ = points;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	point1 = CAR(ab_loop_list_);
	temp = CDR(ab_loop_list_);
	point2 = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (CONSP(point1) && EQ(M_CAR(point1),Qarc)) {
	    temp = M_CDR(point1);
	    temp_1 = CONSP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point1))) : TRUEP(Nil)) {
	    thing = M_CAR(M_CDR(point1));
	    if (CONSP(thing)) {
		temp = CDR(thing);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    if (CONSP(point2) && EQ(M_CAR(point2),Qarc)) {
		temp = M_CDR(point2);
		temp_1 = CONSP(temp);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1 ?  !TRUEP(M_CDR(M_CDR(point2))) : TRUEP(Nil)) {
		thing = M_CAR(M_CDR(point2));
		if (CONSP(thing)) {
		    temp = CDR(thing);
		    temp_1 = CONSP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 = temp_1 ?  !TRUEP(CDDR(thing)) : TRUEP(Nil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    return VALUES_1(Nil);
	goto next_loop;
      end_loop:
	return VALUES_1(T);
	return VALUES_1(Qnil);
    }
}

static Object list_constant_32;    /* # */

static Object string_constant_45;  /* "~%The structure(type: the symbol outline, points: ~NV) contains an invalid use of arc points." */

/* OUTLINE-POINT-TREE-EVALUATION-SETTER */
Object outline_point_tree_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm, points;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,73);
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
			  list_constant_32))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_31,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_outline_point_tree_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints_or_arcpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = evaluation_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	points = parse_result_or_bad_phrase;
    if (valid_points_for_outline_point_tree_p(points))
	result = point_tree_phrase(points);
    else {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_45,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_outline_point_tree_evaluation_setter:
    return result;
}

/* OUTLINE-POINT-TREE-EVALUATION-GETTER */
Object outline_point_tree_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(202,74);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints_or_arcpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_33;    /* # */

static Object list_constant_34;    /* # */

static Object Qlabel;              /* label */

static Object Qfont_size;          /* font-size */

/* TEXT-DRAWING-ELEMENT-EVALUATION-SETTER */
Object text_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1, temp_2;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object temp_3;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,75);
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
			  list_constant_33))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_34,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_text_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_2 = estructure_slot(gensymed_symbol,Qtype,Nil);
    temp = copy_for_phrase(estructure_slot(gensymed_symbol,Qlabel,Nil));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qpoint,Nil);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	gensymed_symbol_5 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_3 = parse_result_or_bad_phrase;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfont_size),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qfont_size,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_list_4(temp_2,temp,temp_3,temp_1);
  end_safe_category_setter_calling_block:
  end_text_drawing_element_evaluation_setter:
    return result;
}

/* TEXT-DRAWING-ELEMENT-EVALUATION-GETTER */
Object text_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, evaluation_value, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,76);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qtext);
    evaluation_value = CADR(slot_value);
    set_evaluation_structure_slot(gensymed_symbol,Qlabel,
	    FIXNUMP(evaluation_value) || evaluation_value && 
	    SYMBOLP(evaluation_value) ? evaluation_value : 
	    copy_evaluation_value_1(evaluation_value));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CADDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoint,temp);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfont_size),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CADDDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qfont_size,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_35;    /* # */

static Object list_constant_36;    /* # */

static Object Qimage_name;         /* image-name */

/* IMAGE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object image_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,77);
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
			  list_constant_35))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_36,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_image_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qtype,Nil);
    temp = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
	    Qimage_name,Nil));
    if (estructure_slot(gensymed_symbol,Qpoint,Nil)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qpoint,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	temp_1 = phrase_cons(temp_1,Nil);
    }
    else
	temp_1 = Nil;
    result = VALUES_1(nconc2(temp,temp_1));
  end_safe_category_setter_calling_block:
  end_image_drawing_element_evaluation_setter:
    return result;
}

/* IMAGE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object image_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, value;

    x_note_fn_call(202,78);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qimage);
    set_evaluation_structure_slot(gensymed_symbol,Qimage_name,
	    CADR(slot_value));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CADDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	value = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	value = Nil;
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qpoint,value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_37;    /* # */

static Object list_constant_38;    /* # */

static Object Qstatic_point;       /* static-point */

/* BACKGROUND-IMAGE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object background_image_drawing_element_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,79);
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
			  list_constant_37))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_38,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_background_image_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp_1 = estructure_slot(gensymed_symbol,Qtype,Nil);
    temp = phrase_list_2(temp_1,estructure_slot(gensymed_symbol,
	    Qimage_name,Nil));
    if (estructure_slot(gensymed_symbol,Qpoint,Nil)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstatic_point),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qpoint,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	temp_1 = phrase_cons(temp_1,Nil);
    }
    else
	temp_1 = Nil;
    result = VALUES_1(nconc2(temp,temp_1));
  end_safe_category_setter_calling_block:
  end_background_image_drawing_element_evaluation_setter:
    return result;
}

/* BACKGROUND-IMAGE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object background_image_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, value;

    x_note_fn_call(202,80);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qimage);
    set_evaluation_structure_slot(gensymed_symbol,Qimage_name,
	    CADR(slot_value));
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qstatic_point),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CADDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	value = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	value = Nil;
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qpoint,value);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_39;    /* # */

static Object list_constant_40;    /* # */

static Object Qbackground_image_drawing_element;  /* background-image-drawing-element */

/* ICON-BACKGROUND-LAYER-ELEMENT-EVALUATION-SETTER */
Object icon_background_layer_element_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,81);
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
			  list_constant_39))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_40,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_icon_background_layer_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    if (SYMBOLP(evaluation_value)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcolor_or_metacolor),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbackground_image_drawing_element),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = evaluation_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    result = VALUES_1(parse_result_or_bad_phrase);
    }
  end_safe_category_setter_calling_block:
  end_icon_background_layer_element_evaluation_setter:
    return result;
}

/* ICON-BACKGROUND-LAYER-ELEMENT-EVALUATION-GETTER */
Object icon_background_layer_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(202,82);
    if (SYMBOLP(slot_value)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcolor_or_metacolor),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    else {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qbackground_image_drawing_element),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = slot_value;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3);
	}
	else
	    temp = Nil;
    }
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_41;    /* # */

static Object list_constant_42;    /* # */

/* POINT-DRAWING-ELEMENT-EVALUATION-SETTER */
Object point_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,83);
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
			  list_constant_41))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_42,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_point_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp = estructure_slot(gensymed_symbol,Qtype,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_list_2(temp,temp_1);
  end_safe_category_setter_calling_block:
  end_point_drawing_element_evaluation_setter:
    return result;
}

/* POINT-DRAWING-ELEMENT-EVALUATION-GETTER */
Object point_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,84);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qpoint);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoint),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CADR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_43;    /* # */

static Object list_constant_44;    /* # */

static Object string_constant_46;  /* "The circle ~s should have exactly 3 points" */

/* CIRCLE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object circle_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,85);
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
			  list_constant_43))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_44,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_circle_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (IFIX(FIXNUM_SUB1(ISVREF(M_CAR(estructure_slot(gensymed_symbol,
	    Qpoints,Nil)),(SI_Long)1L))) == (SI_Long)3L) {
	temp = estructure_slot(gensymed_symbol,Qtype,Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	result = phrase_cons(temp,temp_1);
    }
    else {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_46,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_circle_drawing_element_evaluation_setter:
    return result;
}

static Object Qcircle;             /* circle */

/* CIRCLE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object circle_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,86);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qcircle);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_45;    /* # */

static Object list_constant_46;    /* # */

static Object string_constant_47;  /* "The filled-rectangle ~s should have exactly 2 points" */

/* SOLID-RECTANGLE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object solid_rectangle_drawing_element_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,87);
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
			  list_constant_45))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_46,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_solid_rectangle_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (IFIX(FIXNUM_SUB1(ISVREF(M_CAR(estructure_slot(gensymed_symbol,
	    Qpoints,Nil)),(SI_Long)1L))) == (SI_Long)2L) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	result = phrase_cons(Qsolid_rectangle,temp_1);
    }
    else {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_47,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_solid_rectangle_drawing_element_evaluation_setter:
    return result;
}

static Object Qfilled_rectangle;   /* filled-rectangle */

/* SOLID-RECTANGLE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object solid_rectangle_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,88);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qfilled_rectangle);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_47;    /* # */

static Object list_constant_48;    /* # */

static Object string_constant_48;  /* "The filled-circle ~s should have exactly 3 points" */

/* FILLED-CIRCLE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object filled_circle_drawing_element_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,89);
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
			  list_constant_47))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_48,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_filled_circle_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (IFIX(FIXNUM_SUB1(ISVREF(M_CAR(estructure_slot(gensymed_symbol,
	    Qpoints,Nil)),(SI_Long)1L))) == (SI_Long)3L) {
	temp = estructure_slot(gensymed_symbol,Qtype,Nil);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	result = phrase_cons(temp,temp_1);
    }
    else {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_48,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_filled_circle_drawing_element_evaluation_setter:
    return result;
}

/* FILLED-CIRCLE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object filled_circle_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,90);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qfilled_circle);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_49;    /* # */

static Object list_constant_50;    /* # */

static Object Qlines_point_tree;   /* lines-point-tree */

/* LINES-DRAWING-ELEMENT-EVALUATION-SETTER */
Object lines_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,91);
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
			  list_constant_49))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_50,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_lines_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp = estructure_slot(gensymed_symbol,Qtype,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlines_point_tree),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(temp,temp_1);
  end_safe_category_setter_calling_block:
  end_lines_drawing_element_evaluation_setter:
    return result;
}

/* LINES-DRAWING-ELEMENT-EVALUATION-GETTER */
Object lines_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,92);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qlines);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlines_point_tree),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_51;    /* # */

static Object list_constant_52;    /* # */

static Object Qoutline_point_tree;  /* outline-point-tree */

/* OUTLINE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object outline_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,93);
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
			  list_constant_51))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_52,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_outline_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp = estructure_slot(gensymed_symbol,Qtype,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qoutline_point_tree),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(temp,temp_1);
  end_safe_category_setter_calling_block:
  end_outline_drawing_element_evaluation_setter:
    return result;
}

/* OUTLINE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object outline_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,94);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qoutline);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qoutline_point_tree),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CDR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_53;    /* # */

static Object list_constant_54;    /* # */

static Object Qfilled_polygon_point_tree;  /* filled-polygon-point-tree */

/* FILLED-POLYGON-DRAWING-ELEMENT-EVALUATION-SETTER */
Object filled_polygon_drawing_element_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,95);
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
			  list_constant_53))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_54,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_filled_polygon_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    temp = estructure_slot(gensymed_symbol,Qtype,Nil);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qfilled_polygon_point_tree),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	result = VALUES_2(Bad_phrase,error_string_qm);
	goto end_safe_category_setter_calling_block;
    }
    else
	temp_1 = parse_result_or_bad_phrase;
    result = phrase_cons(temp,temp_1);
  end_safe_category_setter_calling_block:
  end_filled_polygon_drawing_element_evaluation_setter:
    return result;
}

/* FILLED-POLYGON-DRAWING-ELEMENT-EVALUATION-GETTER */
Object filled_polygon_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,96);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qfilled_polygon);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = CADR(slot_value);
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_55;    /* # */

static Object list_constant_56;    /* # */

static Object string_constant_49;  /* "The stippled-area ~s should have no points or exactly 2 points" */

/* STIPPLED-AREA-DRAWING-ELEMENT-EVALUATION-SETTER */
Object stippled_area_drawing_element_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object parse_result_or_bad_phrase, error_string_qm;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,97);
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
			  list_constant_55))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_56,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_stippled_area_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if ( !TRUEP(estructure_slot(gensymed_symbol,Qpoints,Nil)) || 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(estructure_slot(gensymed_symbol,
	    Qpoints,Nil)),(SI_Long)1L))) == (SI_Long)2L) {
	temp = estructure_slot(gensymed_symbol,Qstipple,Nil);
	if (estructure_slot(gensymed_symbol,Qpoints,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol = estructure_slot(gensymed_symbol,Qpoints,Nil);
		gensymed_symbol_2 = Nil;
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol,gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		temp_1 = parse_result_or_bad_phrase;
	}
	else
	    temp_1 = Nil;
	result = phrase_cons(Qstippled_area,phrase_cons(temp,temp_1));
    }
    else {
	temp = Bad_phrase;
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
		  tformat(2,string_constant_49,evaluation_value);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
  end_safe_category_setter_calling_block:
  end_stippled_area_drawing_element_evaluation_setter:
    return result;
}

/* STIPPLED-AREA-DRAWING-ELEMENT-EVALUATION-GETTER */
Object stippled_area_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,98);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    set_evaluation_structure_slot(gensymed_symbol,Qtype,Qstippled_area);
    set_evaluation_structure_slot(gensymed_symbol,Qstipple,SECOND(slot_value));
    if (CDDR(slot_value)) {
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qpoints),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CDDR(slot_value);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qpoints,temp);
    }
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object list_constant_57;    /* # */

static Object string_constant_50;  /* "~a-~a" */

static Object Qdrawing_element;    /* drawing-element */

static Object Qsolid_rectangle_drawing_element;  /* solid-rectangle-drawing-element */

static Object Qbad_element_type_error;  /* bad-element-type-error */

/* MAP-LINE-DRAWING-ELEMENT-TYPE-TO-CATEGORY-NAME */
Object map_line_drawing_element_type_to_category_name(type)
    Object type;
{
    x_note_fn_call(202,99);
    if (memq_function(type,list_constant_57))
	return intern_text_string(1,tformat_text_string(3,
		string_constant_50,type,Qdrawing_element));
    else if (EQ(type,Qfilled_rectangle))
	return VALUES_1(Qsolid_rectangle_drawing_element);
    else
	return VALUES_1(Qbad_element_type_error);
}

static Object list_constant_58;    /* # */

static Object list_constant_59;    /* # */

static Object list_constant_60;    /* # */

static Object string_constant_51;  /* "a line-drawing-element can not be empty" */

static Object list_constant_61;    /* # */

static Object string_constant_52;  /* "~s is not a valid drawing-element type." */

static Object string_constant_53;  /* "~NT " */

static Object string_constant_54;  /* "~NV must be one of the following types: ~a" */

/* LINE-DRAWING-ELEMENT-EVALUATION-SETTER */
Object line_drawing_element_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type, category_name, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,100);
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
			  list_constant_58))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_59,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_line_drawing_element_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_60)) {
	temp = Bad_phrase;
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
		  tformat(1,string_constant_51);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
    else if (type_specification_type_p(gensymed_symbol,list_constant_61)) {
	type = estructure_slot(evaluation_value,Qtype,Nil);
	category_name = map_line_drawing_element_type_to_category_name(type);
	if (EQ(category_name,Qbad_element_type_error)) {
	    temp = Bad_phrase;
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
		      tformat(2,string_constant_52,type);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    result = VALUES_2(temp,temp_1);
	}
	else {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol = function;
		gensymed_symbol_1 = evaluation_value;
		gensymed_symbol_2 = Nil;
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		result = inline_funcall_4(gensymed_symbol,
			gensymed_symbol_1,gensymed_symbol_2,
			gensymed_symbol_3,gensymed_symbol_4);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		result = VALUES_1(parse_result_or_bad_phrase);
	}
      end_safe_category_setter_calling_block:;
    }
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
		  tformat(2,string_constant_53,list_constant_60);
		  tformat(2,string_constant_53,list_constant_61);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_54,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_line_drawing_element_evaluation_setter:
    return result;
}

/* LINE-DRAWING-ELEMENT-EVALUATION-GETTER */
Object line_drawing_element_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object line_drawing_element_type, category_name;
    Object category_evaluator_interface, function, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp;

    x_note_fn_call(202,101);
    line_drawing_element_type = CAR(slot_value);
    category_name = 
	    map_line_drawing_element_type_to_category_name(line_drawing_element_type);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(category_name),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = slot_value;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	temp = inline_funcall_3(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3);
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_62;    /* # */

static Object list_constant_63;    /* # */

static Object string_constant_55;  /* "a layer must have at least one element" */

static Object list_constant_64;    /* # */

static Object Qline_drawing_element;  /* line-drawing-element */

/* LINE-DRAWING-ELEMENTS-EVALUATION-SETTER */
Object line_drawing_elements_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object held_vector, line_drawing_element, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, elt_1, validated_elt, category_evaluator_interface;
    Object function, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, next_index;
    SI_Long length_2;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,102);
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
			  list_constant_62))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_63,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_line_drawing_elements_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_60)) {
	temp = Bad_phrase;
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
		  tformat(1,string_constant_55);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
    else if (type_specification_type_p(gensymed_symbol,list_constant_64)) {
	gensymed_symbol = evaluation_value;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_2 = (SI_Long)0L;
	line_drawing_element = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_2 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop:
	if (next_index >= length_2)
	    goto end_loop;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	line_drawing_element = validated_elt;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qline_drawing_element),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol = function;
	    gensymed_symbol_1 = line_drawing_element;
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	ab_loopvar__2 = phrase_cons(temp_1,Nil);
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
      end_safe_category_setter_calling_block:;
    }
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
		  tformat(2,string_constant_53,list_constant_60);
		  tformat(2,string_constant_53,list_constant_64);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_54,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_line_drawing_elements_evaluation_setter:
    return result;
}

/* LINE-DRAWING-ELEMENTS-EVALUATION-GETTER */
Object line_drawing_elements_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object line_drawing_element, ab_loop_list_, gensymed_symbol, ab_loopvar_;
    Object ab_loopvar__1, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, temp;

    x_note_fn_call(202,103);
    line_drawing_element = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    line_drawing_element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qline_drawing_element),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = line_drawing_element;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
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
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_65;    /* # */

static Object list_constant_66;    /* # */

/* REGION-OR-COLOR-OR-METACOLOR-EVALUATION-SETTER */
Object region_or_color_or_metacolor_evaluation_setter(evaluation_value,
	    frame,slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,104);
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
			  list_constant_65))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_66,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_region_or_color_or_metacolor_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    temp_1 = evaluation_value;
    if (temp_1)
	result = VALUES_1(temp_1);
    else
	result = VALUES_1(Qforeground);
  end_region_or_color_or_metacolor_evaluation_setter:
    return result;
}

/* REGION-OR-COLOR-OR-METACOLOR-EVALUATION-GETTER */
Object region_or_color_or_metacolor_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object temp;

    x_note_fn_call(202,105);
    temp = slot_value;
    if (temp);
    else
	temp = Qforeground;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

static Object list_constant_67;    /* # */

static Object list_constant_68;    /* # */

static Object string_constant_56;  /* "A layer should not be empty." */

static Object Qregion_or_color_or_metacolor;  /* region-or-color-or-metacolor */

static Object Qregion_or_color;    /* region-or-color */

static Object Qline_drawing_elements;  /* line-drawing-elements */

/* LAYER-EVALUATION-SETTER */
Object layer_evaluation_setter(evaluation_value,frame,slot_description,
	    gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,106);
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
			  list_constant_67))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_68,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_layer_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_60)) {
	temp = Bad_phrase;
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
		  tformat(1,string_constant_56);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
    else if (type_specification_type_p(gensymed_symbol,list_constant_61)) {
	gensymed_symbol = evaluation_value;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qregion_or_color_or_metacolor),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,
		    Qregion_or_color,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp = parse_result_or_bad_phrase;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qline_drawing_elements),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol = estructure_slot(gensymed_symbol,
		    Qline_drawing_elements,Nil);
	    gensymed_symbol_2 = Nil;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol,
		    gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	result = phrase_cons(temp,temp_1);
      end_safe_category_setter_calling_block:;
    }
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
		  tformat(2,string_constant_53,list_constant_60);
		  tformat(2,string_constant_53,list_constant_61);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_54,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_layer_evaluation_setter:
    return result;
}

/* LAYER-EVALUATION-GETTER */
Object layer_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, region_qm, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, value, temp;

    x_note_fn_call(202,107);
    gensymed_symbol = allocate_evaluation_structure(Nil);
    region_qm = CAR(slot_value);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qregion_or_color_or_metacolor),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = SYMBOLP(region_qm) ? region_qm : Qnil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	value = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	value = Nil;
    if (value)
	set_evaluation_structure_slot(gensymed_symbol,Qregion_or_color,value);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qline_drawing_elements),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = SYMBOLP(region_qm) ? CDR(slot_value) : slot_value;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    set_evaluation_structure_slot(gensymed_symbol,Qline_drawing_elements,temp);
    GENSYM_RETURN_ONE(gensymed_symbol);
    return VALUES_1(Nil);
}

static Object Qlayer;              /* layer */

/* CONVERT-LIST-OF-LAYERS-TO-SLOT-VALUE-LAYERS */
Object convert_list_of_layers_to_slot_value_layers(layers)
    Object layers;
{
    Object result_1, gensymed_symbol, held_vector, layer, layer_info, elt_1;
    Object validated_elt, category_evaluator_interface, function;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, parse_result_or_bad_phrase, error_string_qm;
    SI_Long next_index, length_1;
    Object result;

    x_note_fn_call(202,108);
    result_1 = Nil;
    gensymed_symbol = layers;
    held_vector = Nil;
    next_index = (SI_Long)1L;
    length_1 = (SI_Long)0L;
    layer = Nil;
    layer_info = Nil;
    held_vector = M_CAR(gensymed_symbol);
    length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
  next_loop:
    if (next_index >= length_1)
	goto end_loop;
    elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(held_vector,next_index + 
	    IFIX(Managed_array_index_offset)) : ISVREF(ISVREF(held_vector,
	    (next_index >>  -  - (SI_Long)10L) + (SI_Long)2L),next_index & 
	    (SI_Long)1023L);
    validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,Nil,
	    Nil) : Nil;
    next_index = next_index + (SI_Long)1L;
    layer = validated_elt;
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlayer),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
    if (function) {
	gensymed_symbol = function;
	gensymed_symbol_1 = layer;
	gensymed_symbol_2 = Nil;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	result = inline_funcall_4(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2,gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	result = VALUES_1(Nil);
    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
    if (EQ(parse_result_or_bad_phrase,Bad_phrase))
	return VALUES_2(Bad_phrase,error_string_qm);
    else
	layer_info = parse_result_or_bad_phrase;
    result_1 = nconc2(result_1,layer_info);
    goto next_loop;
  end_loop:
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

static Object list_constant_69;    /* # */

static Object list_constant_70;    /* # */

static Object string_constant_57;  /* "layers can not be empty" */

/* LABEL-AND-ELEMENT-LIST-EVALUATION-SETTER */
Object label_and_element_list_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,109);
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
			  list_constant_69))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_70,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_label_and_element_list_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_60)) {
	temp = Bad_phrase;
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
		  tformat(1,string_constant_57);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	result = VALUES_2(temp,temp_1);
    }
    else if (type_specification_type_p(gensymed_symbol,list_constant_64))
	result = convert_list_of_layers_to_slot_value_layers(evaluation_value);
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
		  tformat(2,string_constant_53,list_constant_60);
		  tformat(2,string_constant_53,list_constant_64);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_54,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_label_and_element_list_evaluation_setter:
    return result;
}

/* LABEL-AND-ELEMENT-LIST-EVALUATION-GETTER */
Object label_and_element_list_evaluation_getter(slot_value,frame,
	    slot_description)
    Object slot_value, frame, slot_description;
{
    Object layer, ab_loop_list_, gensymed_symbol, ab_loopvar_, ab_loopvar__1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, temp;

    x_note_fn_call(202,110);
    layer = Nil;
    ab_loop_list_ = slot_value;
    gensymed_symbol = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    category_evaluator_interface = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlayer),
	    Qcategory_evaluator_interface);
    function = category_evaluator_interface ? 
	    ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
    if (function) {
	gensymed_symbol_1 = function;
	gensymed_symbol_2 = layer;
	gensymed_symbol_3 = Nil;
	gensymed_symbol_4 = Nil;
	temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		gensymed_symbol_3,gensymed_symbol_4);
    }
    else
	temp = Nil;
    ab_loopvar__1 = eval_cons_1(temp,Nil);
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
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

/* CONVERT-SLOT-VALUE-LAYERS-TO-LIST-OF-LAYERS */
Object convert_slot_value_layers_to_list_of_layers(slot_value_layers)
    Object slot_value_layers;
{
    Object layer, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, first_1;
    Object ab_loopvar__3, ab_loopvar__4, temp_1, slot_value_layers_old_value;
    char temp;

    x_note_fn_call(202,111);
    layer = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(slot_value_layers))
	goto end_loop;
    first_1 = T;
    ab_loopvar__2 = Nil;
    ab_loopvar__3 = Nil;
    ab_loopvar__4 = Nil;
  next_loop_1:
    temp = TRUEP(first_1);
    if (temp);
    else {
	temp_1 = CAR(slot_value_layers);
	temp = CONSP(temp_1);
    }
    if ( !temp)
	goto end_loop_1;
    slot_value_layers_old_value = slot_value_layers;
    temp_1 = FIRST(slot_value_layers_old_value);
    slot_value_layers = REST(slot_value_layers_old_value);
    ab_loopvar__4 = gensym_cons_1(temp_1,Nil);
    if (ab_loopvar__3)
	M_CDR(ab_loopvar__3) = ab_loopvar__4;
    else
	ab_loopvar__2 = ab_loopvar__4;
    ab_loopvar__3 = ab_loopvar__4;
    first_1 = Nil;
    goto next_loop_1;
  end_loop_1:
    layer = ab_loopvar__2;
    goto end_1;
    layer = Qnil;
  end_1:;
    ab_loopvar__2 = gensym_cons_1(layer,Nil);
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

/* RECLAIM-LIST-OF-LAYERS */
Object reclaim_list_of_layers(list_of_layers)
    Object list_of_layers;
{
    Object layer, ab_loop_list_;

    x_note_fn_call(202,112);
    layer = Nil;
    ab_loop_list_ = list_of_layers;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    layer = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_gensym_list_1(layer);
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(list_of_layers);
    return VALUES_1(Qnil);
}

static Object list_constant_71;    /* # */

static Object list_constant_72;    /* # */

static Object Qlabel_and_element_list;  /* label-and-element-list */

static Object Qlayers;             /* layers */

static Object Qicon_background_layer;  /* icon-background-layer */

static Object Qicon_background_layer_element;  /* icon-background-layer-element */

static Object Qvariable_specification_list;  /* variable-specification-list */

static Object Qregions;            /* regions */

static Object Qregion_specification_list;  /* region-specification-list */

static Object Qcm;                 /* \, */

static Object Qheight;             /* height */

static Object Qwidth;              /* width */

/* ICON-DESCRIPTION?-EVALUATION-SETTER */
Object icon_description_qm_evaluation_setter(evaluation_value,frame,
	    slot_description,gensymed_symbol)
    Object evaluation_value, frame, slot_description, gensymed_symbol;
{
    Object value_at_type_failure, type_at_type_failure;
    Object reason_for_type_failure, context_of_type_failure;
    Object last_slot_checked_of_type_failure, temp, temp_1;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    Object gensymed_symbol_5, parse_result_or_bad_phrase, error_string_qm;
    Object layers_info, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object type_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);
    Object result;

    x_note_fn_call(202,113);
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
			  list_constant_71))) {
		      temp = Bad_phrase;
		      temp_1 = type_error_in_setter(evaluation_value,
			      list_constant_72,Value_at_type_failure,
			      Type_at_type_failure,Reason_for_type_failure,
			      Context_of_type_failure,
			      Last_slot_checked_of_type_failure);
		      result = VALUES_2(temp,temp_1);
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      POP_SPECIAL();
		      goto end_icon_description_qm_evaluation_setter;
		  }
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    gensymed_symbol = evaluation_value;
    if (type_specification_type_p(gensymed_symbol,list_constant_60))
	result = VALUES_1(Qinherited);
    else if (type_specification_type_p(gensymed_symbol,list_constant_61)) {
	gensymed_symbol = evaluation_value;
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_and_element_list),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = estructure_slot(gensymed_symbol,Qlayers,Nil);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    gensymed_symbol_5 = Nil;
	    result = inline_funcall_4(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4,gensymed_symbol_5);
	}
	else
	    result = VALUES_1(Nil);
	MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	    result = VALUES_2(Bad_phrase,error_string_qm);
	    goto end_safe_category_setter_calling_block;
	}
	else
	    temp_1 = parse_result_or_bad_phrase;
	layers_info = phrase_cons(Qsc,temp_1);
	if (estructure_slot(gensymed_symbol,Qstipple,Nil)) {
	    temp_1 = phrase_list_2(Qstipple,
		    estructure_slot(gensymed_symbol,Qstipple,Nil));
	    layers_info = phrase_cons(temp_1,layers_info);
	}
	if (estructure_slot(gensymed_symbol,Qicon_background_layer,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicon_background_layer_element),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = estructure_slot(gensymed_symbol,
			Qicon_background_layer,Nil);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		gensymed_symbol_5 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,
			gensymed_symbol_4,gensymed_symbol_5);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		temp_1 = parse_result_or_bad_phrase;
	    layers_info = phrase_cons(phrase_list_2(Qbackground_layer,
		    temp_1),layers_info);
	}
	if (estructure_slot(gensymed_symbol,Qvariables,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvariable_specification_list),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = estructure_slot(gensymed_symbol,
			Qvariables,Nil);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		gensymed_symbol_5 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,
			gensymed_symbol_4,gensymed_symbol_5);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		temp_1 = parse_result_or_bad_phrase;
	    layers_info = phrase_cons(phrase_cons(Qvariables,temp_1),
		    layers_info);
	}
	if (estructure_slot(gensymed_symbol,Qregions,Nil)) {
	    category_evaluator_interface = 
		    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qregion_specification_list),
		    Qcategory_evaluator_interface);
	    function = category_evaluator_interface ? 
		    ISVREF(category_evaluator_interface,(SI_Long)3L) : Qnil;
	    if (function) {
		gensymed_symbol_1 = function;
		gensymed_symbol_2 = estructure_slot(gensymed_symbol,
			Qregions,Nil);
		gensymed_symbol_3 = Nil;
		gensymed_symbol_4 = Nil;
		gensymed_symbol_5 = Nil;
		result = inline_funcall_4(gensymed_symbol_1,
			gensymed_symbol_2,gensymed_symbol_3,
			gensymed_symbol_4,gensymed_symbol_5);
	    }
	    else
		result = VALUES_1(Nil);
	    MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
	    if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
		result = VALUES_2(Bad_phrase,error_string_qm);
		goto end_safe_category_setter_calling_block;
	    }
	    else
		temp_1 = parse_result_or_bad_phrase;
	    layers_info = phrase_cons(phrase_cons(Qpolychrome,
		    phrase_cons(Qcm,temp_1)),layers_info);
	}
	temp_1 = estructure_slot(gensymed_symbol,Qheight,Nil);
	layers_info = phrase_cons(temp_1,layers_info);
	temp_1 = estructure_slot(gensymed_symbol,Qwidth,Nil);
	layers_info = phrase_cons(temp_1,layers_info);
	result = VALUES_1(layers_info);
      end_safe_category_setter_calling_block:;
    }
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
		  tformat(2,string_constant_53,list_constant_60);
		  tformat(2,string_constant_53,list_constant_61);
		  type_string = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = Bad_phrase;
	temp_1 = tformat_text_string(3,string_constant_54,gensymed_symbol,
		type_string);
	result = VALUES_2(temp,temp_1);
    }
  end_icon_description_qm_evaluation_setter:
    return result;
}

/* ICON-DESCRIPTION?-EVALUATION-GETTER */
Object icon_description_qm_evaluation_getter(slot_value,frame,slot_description)
    Object slot_value, frame, slot_description;
{
    Object gensymed_symbol, line_drawing_description, first_element;
    Object regions_header_qm, variables_header_qm, background_header_qm;
    Object stipple_qm, remaining_parse_result, regions_p, variables_p;
    Object background_p, stipple_p, header_count, list_of_layers;
    Object category_evaluator_interface, function, gensymed_symbol_1;
    Object gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4, value;
    Object temp;

    x_note_fn_call(202,114);
    if (slot_value) {
	gensymed_symbol = allocate_evaluation_structure(Nil);
	line_drawing_description = CDDR(slot_value);
	first_element = CAR(line_drawing_description);
	regions_header_qm = CONSP(first_element) && EQ(CAR(first_element),
		Qpolychrome) ? first_element : Nil;
	variables_header_qm = get_variable_specification_if_any(slot_value);
	background_header_qm = get_icon_background_layer_if_any(slot_value);
	stipple_qm = get_icon_stipple_if_any(slot_value);
	remaining_parse_result = CDDR(slot_value);
	regions_p = regions_header_qm;
	variables_p = variables_header_qm;
	background_p = background_header_qm;
	stipple_p = stipple_qm;
	header_count = FIX((SI_Long)0L);
	if (regions_p)
	    header_count = FIXNUM_ADD1(header_count);
	if (variables_p)
	    header_count = FIXNUM_ADD1(header_count);
	if (background_p)
	    header_count = FIXNUM_ADD1(header_count);
	if (stipple_p)
	    header_count = FIXNUM_ADD1(header_count);
	list_of_layers = 
		convert_slot_value_layers_to_list_of_layers(nthcdr(header_count,
		remaining_parse_result));
	set_evaluation_structure_slot(gensymed_symbol,Qwidth,
		FIRST(slot_value));
	set_evaluation_structure_slot(gensymed_symbol,Qheight,
		SECOND(slot_value));
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qregion_specification_list),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CDR(regions_header_qm);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    value = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    value = Nil;
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,Qregions,value);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qvariable_specification_list),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CDR(variables_header_qm);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    value = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    value = Nil;
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,Qvariables,value);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qicon_background_layer_element),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = CADR(background_header_qm);
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    value = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    value = Nil;
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,
		    Qicon_background_layer,value);
	value = stipple_qm;
	if (value)
	    set_evaluation_structure_slot(gensymed_symbol,Qstipple,value);
	category_evaluator_interface = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qlabel_and_element_list),
		Qcategory_evaluator_interface);
	function = category_evaluator_interface ? 
		ISVREF(category_evaluator_interface,(SI_Long)2L) : Qnil;
	if (function) {
	    gensymed_symbol_1 = function;
	    gensymed_symbol_2 = list_of_layers;
	    gensymed_symbol_3 = Nil;
	    gensymed_symbol_4 = Nil;
	    temp = inline_funcall_3(gensymed_symbol_1,gensymed_symbol_2,
		    gensymed_symbol_3,gensymed_symbol_4);
	}
	else
	    temp = Nil;
	set_evaluation_structure_slot(gensymed_symbol,Qlayers,temp);
	reclaim_list_of_layers(list_of_layers);
	temp = gensymed_symbol;
    }
    else
	temp = Nil;
    GENSYM_RETURN_ONE(temp);
    return VALUES_1(Nil);
}

void grammar6c_INIT()
{
    Object region_specification_evaluation_setter_1;
    Object region_specification_evaluation_getter_1;
    Object region_specification_list_evaluation_setter_1;
    Object region_specification_list_evaluation_getter_1;
    Object variable_specification_evaluation_setter_1;
    Object variable_specification_evaluation_getter_1;
    Object variable_specification_list_evaluation_setter_1;
    Object variable_specification_list_evaluation_getter_1;
    Object font_size_evaluation_setter_1, font_size_evaluation_getter_1;
    Object point_factor_evaluation_setter_1, point_factor_evaluation_getter_1;
    Object point_sum_evaluation_setter_1, point_sum_evaluation_getter_1;
    Object point_expression_evaluation_setter_1;
    Object point_expression_evaluation_getter_1, point_evaluation_setter_1;
    Object point_evaluation_getter_1, point_or_arcpoint_evaluation_setter_1;
    Object point_or_arcpoint_evaluation_getter_1;
    Object static_point_evaluation_setter_1, static_point_evaluation_getter_1;
    Object points_evaluation_setter_1, points_evaluation_getter_1;
    Object points_or_arcpoints_evaluation_setter_1;
    Object points_or_arcpoints_evaluation_getter_1;
    Object filled_polygon_point_tree_evaluation_setter_1;
    Object filled_polygon_point_tree_evaluation_getter_1;
    Object lines_point_tree_evaluation_setter_1;
    Object lines_point_tree_evaluation_getter_1;
    Object outline_point_tree_evaluation_setter_1;
    Object outline_point_tree_evaluation_getter_1;
    Object text_drawing_element_evaluation_setter_1;
    Object text_drawing_element_evaluation_getter_1;
    Object image_drawing_element_evaluation_setter_1;
    Object image_drawing_element_evaluation_getter_1;
    Object background_image_drawing_element_evaluation_setter_1;
    Object background_image_drawing_element_evaluation_getter_1;
    Object icon_background_layer_element_evaluation_setter_1;
    Object icon_background_layer_element_evaluation_getter_1;
    Object point_drawing_element_evaluation_setter_1;
    Object point_drawing_element_evaluation_getter_1;
    Object circle_drawing_element_evaluation_setter_1;
    Object circle_drawing_element_evaluation_getter_1;
    Object solid_rectangle_drawing_element_evaluation_setter_1;
    Object solid_rectangle_drawing_element_evaluation_getter_1;
    Object filled_circle_drawing_element_evaluation_setter_1;
    Object filled_circle_drawing_element_evaluation_getter_1;
    Object lines_drawing_element_evaluation_setter_1;
    Object lines_drawing_element_evaluation_getter_1;
    Object outline_drawing_element_evaluation_setter_1;
    Object outline_drawing_element_evaluation_getter_1;
    Object filled_polygon_drawing_element_evaluation_setter_1;
    Object filled_polygon_drawing_element_evaluation_getter_1;
    Object stippled_area_drawing_element_evaluation_setter_1;
    Object stippled_area_drawing_element_evaluation_getter_1;
    Object line_drawing_element_evaluation_setter_1;
    Object line_drawing_element_evaluation_getter_1;
    Object line_drawing_elements_evaluation_setter_1;
    Object line_drawing_elements_evaluation_getter_1;
    Object region_or_color_or_metacolor_evaluation_setter_1;
    Object region_or_color_or_metacolor_evaluation_getter_1;
    Object layer_evaluation_setter_1, layer_evaluation_getter_1;
    Object label_and_element_list_evaluation_setter_1;
    Object label_and_element_list_evaluation_getter_1;
    Object icon_description_qm_evaluation_setter_1;
    Object icon_description_qm_evaluation_getter_1;
    Object Qicon_description_qm, AB_package, Qnamed, list_constant_188, Qab_or;
    Object list_constant_187, list_constant_186, Qab_structure;
    Object list_constant_185, list_constant_168, list_constant_184;
    Object list_constant_183, list_constant_182, list_constant_181;
    Object list_constant_180, list_constant_108, list_constant_179;
    Object Qtype_specification_simple_expansion, list_constant_92;
    Object list_constant_178, list_constant_177, list_constant_176;
    Object list_constant_175, list_constant_174, list_constant_86;
    Object list_constant_173, list_constant_172, list_constant_96;
    Object list_constant_171, Qstippled_area_drawing_element;
    Object list_constant_170, list_constant_169, list_constant_147;
    Object list_constant_167, list_constant_166, Qdark_stipple;
    Object Qmedium_stipple, Qlight_stipple, list_constant_165;
    Object Qfilled_polygon_drawing_element, list_constant_144;
    Object list_constant_164, list_constant_163, list_constant_162;
    Object list_constant_161, Qoutline_drawing_element, list_constant_160;
    Object list_constant_159, list_constant_158, list_constant_157;
    Object Qlines_drawing_element, list_constant_156, list_constant_155;
    Object list_constant_154, list_constant_153;
    Object Qfilled_circle_drawing_element, list_constant_152;
    Object list_constant_151, list_constant_150, list_constant_149;
    Object list_constant_148, list_constant_146, list_constant_142;
    Object list_constant_145, Qcircle_drawing_element, list_constant_143;
    Object list_constant_139, list_constant_141, list_constant_140;
    Object Qpoint_drawing_element, list_constant_138, list_constant_137;
    Object list_constant_136, list_constant_135, list_constant_134;
    Object list_constant_133, list_constant_132, list_constant_131;
    Object list_constant_79, list_constant_93, list_constant_130;
    Object list_constant_129, list_constant_127, list_constant_128;
    Object list_constant_125, list_constant_124, Qimage_drawing_element;
    Object list_constant_126, list_constant_118, list_constant_123;
    Object Qtext_drawing_element, list_constant_122, list_constant_121;
    Object list_constant_120, list_constant_119, list_constant_117;
    Object list_constant_116, list_constant_115, list_constant_114;
    Object list_constant_112, list_constant_113, list_constant_107;
    Object list_constant_111, list_constant_110, list_constant_109;
    Object list_constant_106, list_constant_103, list_constant_102;
    Object list_constant_105, list_constant_104, list_constant_101;
    Object list_constant_100, list_constant_99, list_constant_98;
    Object list_constant_95, list_constant_97, list_constant_94;
    Object list_constant_91, list_constant_90, list_constant_89;
    Object list_constant_88, list_constant_87, list_constant_85;
    Object list_constant_84, Qno_item, list_constant_83, list_constant_82;
    Object list_constant_81, list_constant_80, list_constant_73;
    Object Qslot_value_writer, Qwrite_icon_description_qm_from_slot;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_icon_description_qm_for_slot;
    Object list_constant_78, Qextra_large, Qlarge, Qsmall, list_constant_77;
    Object Qmetacolor, Qtransparent, list_constant_76, Qcolor;
    Object list_constant_75, Qplum, Qpink, Qpale_green, Qorange;
    Object Qmedium_orchid, Qmedium_goldenrod, Qmedium_blue, Qmedium_aquamarine;
    Object Qmaroon, Qmagenta, Qlime_green, Qlight_gray, Qlight_blue, Qkhaki;
    Object Qindian_red, Qgreen_yellow, Qgreen, Qgray, Qgoldenrod, Qgold;
    Object Qforest_green, Qdim_gray, Qdark_slate_blue, Qdark_gray, Qcyan;
    Object Qcoral, Qcadet_blue, Qbrown, Qblue, Qblack, Qaquamarine;
    Object list_constant_74, Qlight_pink, Qbeige, Qlight_goldenrod;
    Object Qlight_yellow, Qlight_goldenrod_yellow, Qpale_goldenrod;
    Object Qlight_cyan, Qpale_turquoise, Qpowder_blue, Qlight_steel_blue;
    Object Qlavender, Qazure, Qivory, Qantique_white, Qlinen, Qfloral_white;
    Object Qsmoke, Qyellow, Qwhite, Qwheat, Qviolet_red, Qviolet, Qturquoise;
    Object Qthistle, Qslate_blue, Qsky_blue, Qsienna, Qsalmon, Qred, Qpurple;
    Object Qextra_light_gray, Qfix_line_list;
    Object Qwrite_text_specification_qm_from_slot, Qtext_specification_qm;
    Object Qwrite_image_specification_qm_from_slot, Qimage_specification_qm;
    Object Qimage_name_qm, Qcompile_image_name_qm_for_slot;
    Object Qwrite_symbol_from_slot, Qwrite_stipple_specification_qm_from_slot;
    Object Qstipple_specification_qm;
    Object Qwrite_global_stipple_specification_qm_from_slot;
    Object Qglobal_stipple_specification_qm, string_constant_89;
    Object string_constant_88, string_constant_87, string_constant_86;
    Object string_constant_85, string_constant_84, string_constant_83;
    Object string_constant_82, string_constant_81, string_constant_80;
    Object string_constant_79, string_constant_78, string_constant_77;
    Object string_constant_76, string_constant_75, string_constant_74;
    Object string_constant_73, string_constant_72, string_constant_71;
    Object string_constant_70, string_constant_69, string_constant_68;
    Object string_constant_67, string_constant_66, string_constant_65;
    Object string_constant_64, string_constant_63, string_constant_62;
    Object string_constant_61, string_constant_60, string_constant_59;
    Object string_constant_58, Qvariable_spec_transform;
    Object Qsimplify_last_of_nary_associative_operator;
    Object Qsimplify_associative_operation;

    x_note_fn_call(202,115);
    SET_PACKAGE("AB");
    AB_package = STATIC_PACKAGE("AB");
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    Qsimplify_last_of_nary_associative_operator = 
	    STATIC_SYMBOL("SIMPLIFY-LAST-OF-NARY-ASSOCIATIVE-OPERATOR",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qsimplify_last_of_nary_associative_operator,
	    STATIC_FUNCTION(simplify_last_of_nary_associative_operator,NIL,
	    FALSE,1,1));
    Qvariable_spec_transform = STATIC_SYMBOL("VARIABLE-SPEC-TRANSFORM",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qvariable_spec_transform,
	    STATIC_FUNCTION(variable_spec_transform,NIL,FALSE,1,1));
    string_constant_58 = 
	    STATIC_STRING("13jy1n835xy1p1m9k83-9y83lay1m9k83vy83lay1m9k83-Ay1mmo1n83f6y1q1m9k83*Hy1m9k83-9y83lay1m9k83vy83lay1m9k83-Ay1m83*Hy1mnp1m839iy835");
    string_constant_59 = 
	    STATIC_STRING("xy1m839iy1m839iy835xy1m83-cfy1m1m9k835xy835xy1m83-cfy1o1m9k83*fy835xy835xy835xy1n83-cfy1o1m9k83oy1m9k83Ygy835xy835xy1n83jyno1n83");
    string_constant_60 = 
	    STATIC_STRING("-cfy1p1m9k83oy1m9k83*fy835xy835xy835xy1o83=Rynop1n83-cfy1m1m9k83Oy83-2Fy2l83Oym1n83-cfy1m1m9k83Jy83-8Iy2l83Jym1n83-cfy1n1m9k83oy");
    string_constant_61 = 
	    STATIC_STRING("1m9k83-jMy83wIy2l83qyn1m83-cfy83-r-y1n83-r-y1n1m9k83-r*y1m9k83-Jmy83awy1m83-Dnyn1n83-r-y1p1m9k83-r*y1m9k83-Jmy83awy835xy835xy1o8");
    string_constant_62 = 
	    STATIC_STRING("3-Dnynop1m83-cfy83-Eby1m83-Ydy1m9k83-Vy1m83-Ydy1m9k83=Ay1m83-Ydy1m9k83C0y1m83-*py83-Ydy1m83-*py83-6y1m83-cfy83-=Cy1m8346y1m9k83S");
    string_constant_63 = 
	    STATIC_STRING("6y1n8346y1r1m9k83*4y83-ey1m9k83-Zy1m9k83=sy83-ey1m9k83-Zy83-YQy2mmpr1m83-YQy83-YRy1n83-YQy1n83-BTy1m9k83-Zy83-YRy2l2l83-1yln1m83");
    string_constant_64 = 
	    STATIC_STRING("-YRy83-YSy1n83-YRy1n83-wJy1m9k83-Zy83-YSy2l2l83-iyln1m83-YSy83-YTy1n83-YSy1n83-YOy1m9k83-Zy83-YTy2l2l83-jyln1m83-YTy83-cAy1n83-Y");
    string_constant_65 = 
	    STATIC_STRING("Ty1p1m9k83awy1m9k83-Py83awy1m9k83-Zy83-cAy2l1m83awynp1n83-YOy1o1m9k83-YNy1m9k83-Py1m9k83*xy83qGy1lo1n83-YOy1n1m9k83-YNy1m9k83-Py");
    string_constant_66 = 
	    STATIC_STRING("83*uy1ln1o83-cAy1n83-cfy1m9k83-Zy83-cAy1nmln9l1o83-cAy1p83-BSy1m9k83-Py83-cfy1m9k83-Zy83-cAy1oolnp9m1n83-cAy1n83-BSy1m9k83-Py83-");
    string_constant_67 = 
	    STATIC_STRING("cfy1n83-Zyln1m83-cAy83-cfy1o83-wJy1n1m9k83-iy1m9k83-Py83-wKyn9n1n83-wKy83-wIy1m83vyl1o83-wKy1n83-wIy1m9k83vy83-wKy1nmln9l1m83-wG");
    string_constant_68 = 
	    STATIC_STRING("y83-6y1n83-wIy1n83-wGy1m9k9o83Sy1mln1n83-wIy1n83-wGy1m9k9o83-Uy1mln1n83-wIy1n83-wGy1m9k9o83-Ydy1mln1n83-wIy1n83-wGy1m9k9o835Uy1m");
    string_constant_69 = 
	    STATIC_STRING("ln1o83-BTy83-lsyl9p1n83-lsy83-lry1m83vyl1o83-lsy1n83-lry1m9k83vy83-lsy1nmln9l1n83-lry1n83Yky1m9k9o83*uy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qsimplify_last_of_nary_associative_operator);
    push_optimized_constant(Qvariable_spec_transform);
    push_optimized_constant(Qnum_eq);
    push_optimized_constant(Qcdr);
    add_grammar_rules_function(regenerate_optimized_constant(list(12,
	    string_constant_58,string_constant_59,string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69)));
    string_constant_70 = 
	    STATIC_STRING("1n1m83awy1m9k83-cdy1m83awy1m9k83-e9y1m83awy1m9k83-Pjy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_70));
    string_constant_71 = 
	    STATIC_STRING("1q1m83-2Fy839iy1m83-2Fy83-cjy1m83-cky1m839iy83f6y1m83-cky1m83-cjy83f6y1m83-cjy1m83-cky835xy1m83-cjy1m83-cjy835xy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_71));
    string_constant_72 = 
	    STATIC_STRING("1q1m83-8Iy839iy1m83-8Iy83-i=y1m83-i0y1m839iy83f6y1m83-i0y1m83-i=y83f6y1m83-i=y1m83-i0y835xy1m83-i=y1m83-i=y835xy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_72));
    string_constant_73 = 
	    STATIC_STRING("1o1m83wIy1m83-Twy835xy1m83-Twy1m83-Txy835xy1m83-Txy835xy1m83-Txy1m83-Txy835xy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_73));
    Qarc = STATIC_SYMBOL("ARC",AB_package);
    string_constant_74 = 
	    STATIC_STRING("1n1m83lay83-92y1m83-92y83Sy1m83-92y83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_74));
    string_constant_75 = 
	    STATIC_STRING("1v1m83lay83-jIy1m83-jIy83-jKy1n83-jIy1m83-jKy83-pJy1n9klm1m83-pJy83-pKy1n83-pJy1m83-pKy83-pJy1n9klm1m83-jKy83-jJy1m83-jKy83-pKy1");
    string_constant_76 = 
	    STATIC_STRING("n83-pKy1m1m9l9k83-jJym1m83-pKy1m1m9l9m83-jJy1m83-jJy83-92y1n83-92y1n1m9l83-9y83lay1m9l83-Aym");
    clear_optimized_constants();
    push_optimized_constant(Qplus);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qminus);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_75,
	    string_constant_76)));
    string_constant_77 = STATIC_STRING("1l1m835Uy83-6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_77));
    string_constant_78 = STATIC_STRING("1m1m83-Z8y835Uy1n83-Z8y1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_78));
    string_constant_79 = 
	    STATIC_STRING("1m1n83isy835Uy1m83Cmyl1n83isy1n835Uy1m9k83=Gy835xy1n83Cmyln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_79));
    string_constant_80 = STATIC_STRING("1m1m83Coy83isy1n83Coy1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_80));
    string_constant_81 = STATIC_STRING("1l1n83-=Cy1m1m9k83Cmy83isym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_81));
    string_constant_82 = 
	    STATIC_STRING("1l1n83-Dgy1p1m9k83-9y83Sy1m9k83vy83Sy1m9k83-Ay1mmo");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_82));
    string_constant_83 = 
	    STATIC_STRING("1m1n83qHy835Uy1m83Cmyl1n83qHy1n835Uy1m9k83=Gy83-Dgy1n83Cmyln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_83));
    string_constant_84 = STATIC_STRING("1l1n83qGy1m1m9k83Cmy83qHym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_84));
    string_constant_85 = 
	    STATIC_STRING("1m1n83nmy1p83-Uy1m9k83=Gy835xy1m9k83*Xy83-*py1o83Gylnp1n83nmy1p83-6y1m9k83=Gy835xy1m9k83*Xy83-*py1o83Gylnp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_85));
    string_constant_86 = STATIC_STRING("1m1m83FMy83nmy1n83FMy1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_86));
    string_constant_87 = STATIC_STRING("1l1n83-Eby1m1m9k83Gy83nmym");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_87));
    Qstatement_format = STATIC_SYMBOL("STATEMENT-FORMAT",AB_package);
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant = STATIC_STRING("~a");
    list_constant_73 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    string_constant_1 = STATIC_STRING(" \"~a\" ");
    string_constant_2 = STATIC_STRING("~%");
    string_constant_3 = STATIC_STRING(" at ");
    string_constant_4 = STATIC_STRING(" in ");
    string_constant_5 = STATIC_STRING(" ~(~a~) ");
    string_constant_88 = STATIC_STRING("1m1m83CXy83awy1n83CXy1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_88));
    string_constant_89 = 
	    STATIC_STRING("1n1n83FDy83awy1m83-Dnyl1n83FDy1n83awy835xy835xy1o83-Dnylmn1n83FDy1m9k83Zy0");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_89));
    Qglobal_stipple_specification_qm = 
	    STATIC_SYMBOL("GLOBAL-STIPPLE-SPECIFICATION\?",AB_package);
    Qwrite_global_stipple_specification_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-GLOBAL-STIPPLE-SPECIFICATION\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_global_stipple_specification_qm_from_slot,
	    STATIC_FUNCTION(write_global_stipple_specification_qm_from_slot,
	    NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qglobal_stipple_specification_qm,
	    SYMBOL_FUNCTION(Qwrite_global_stipple_specification_qm_from_slot),
	    Qslot_value_writer);
    Qstipple_specification_qm = STATIC_SYMBOL("STIPPLE-SPECIFICATION\?",
	    AB_package);
    Qwrite_stipple_specification_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-STIPPLE-SPECIFICATION\?-FROM-SLOT",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_stipple_specification_qm_from_slot,
	    STATIC_FUNCTION(write_stipple_specification_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qstipple_specification_qm,
	    SYMBOL_FUNCTION(Qwrite_stipple_specification_qm_from_slot),
	    Qslot_value_writer);
    string_constant_6 = STATIC_STRING("~(~a~)");
    string_constant_7 = STATIC_STRING(" (~d, ~d) (~d, ~d)");
    Qimage_name_qm = STATIC_SYMBOL("IMAGE-NAME\?",AB_package);
    Qwrite_symbol_from_slot = STATIC_SYMBOL("WRITE-SYMBOL-FROM-SLOT",
	    AB_package);
    mutate_global_property(Qimage_name_qm,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qimage_name = STATIC_SYMBOL("IMAGE-NAME",AB_package);
    mutate_global_property(Qimage_name,
	    SYMBOL_FUNCTION(Qwrite_symbol_from_slot),Qslot_value_writer);
    Qnone = STATIC_SYMBOL("NONE",AB_package);
    Qcompile_image_name_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-IMAGE-NAME\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_image_name_qm_for_slot,
	    STATIC_FUNCTION(compile_image_name_qm_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qimage_name_qm,
	    SYMBOL_FUNCTION(Qcompile_image_name_qm_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qimage_name_qm,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qimage_specification_qm = STATIC_SYMBOL("IMAGE-SPECIFICATION\?",
	    AB_package);
    Qwrite_image_specification_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-IMAGE-SPECIFICATION\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_image_specification_qm_from_slot,
	    STATIC_FUNCTION(write_image_specification_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qimage_specification_qm,
	    SYMBOL_FUNCTION(Qwrite_image_specification_qm_from_slot),
	    Qslot_value_writer);
    Qtext_specification_qm = STATIC_SYMBOL("TEXT-SPECIFICATION\?",AB_package);
    Qwrite_text_specification_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-TEXT-SPECIFICATION\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_text_specification_qm_from_slot,
	    STATIC_FUNCTION(write_text_specification_qm_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qtext_specification_qm,
	    SYMBOL_FUNCTION(Qwrite_text_specification_qm_from_slot),
	    Qslot_value_writer);
    Qfix_line_list = STATIC_SYMBOL("FIX-LINE-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qfix_line_list,STATIC_FUNCTION(fix_line_list,NIL,
	    FALSE,1,1));
    Qcolor = STATIC_SYMBOL("COLOR",AB_package);
    Qaquamarine = STATIC_SYMBOL("AQUAMARINE",AB_package);
    Qblack = STATIC_SYMBOL("BLACK",AB_package);
    Qblue = STATIC_SYMBOL("BLUE",AB_package);
    Qbrown = STATIC_SYMBOL("BROWN",AB_package);
    Qcadet_blue = STATIC_SYMBOL("CADET-BLUE",AB_package);
    Qcoral = STATIC_SYMBOL("CORAL",AB_package);
    Qcyan = STATIC_SYMBOL("CYAN",AB_package);
    Qdark_gray = STATIC_SYMBOL("DARK-GRAY",AB_package);
    Qdark_slate_blue = STATIC_SYMBOL("DARK-SLATE-BLUE",AB_package);
    Qdim_gray = STATIC_SYMBOL("DIM-GRAY",AB_package);
    Qforest_green = STATIC_SYMBOL("FOREST-GREEN",AB_package);
    Qgold = STATIC_SYMBOL("GOLD",AB_package);
    Qgoldenrod = STATIC_SYMBOL("GOLDENROD",AB_package);
    Qgray = STATIC_SYMBOL("GRAY",AB_package);
    Qgreen = STATIC_SYMBOL("GREEN",AB_package);
    Qgreen_yellow = STATIC_SYMBOL("GREEN-YELLOW",AB_package);
    Qindian_red = STATIC_SYMBOL("INDIAN-RED",AB_package);
    Qkhaki = STATIC_SYMBOL("KHAKI",AB_package);
    Qlight_blue = STATIC_SYMBOL("LIGHT-BLUE",AB_package);
    Qlight_gray = STATIC_SYMBOL("LIGHT-GRAY",AB_package);
    Qlime_green = STATIC_SYMBOL("LIME-GREEN",AB_package);
    Qmagenta = STATIC_SYMBOL("MAGENTA",AB_package);
    Qmaroon = STATIC_SYMBOL("MAROON",AB_package);
    Qmedium_aquamarine = STATIC_SYMBOL("MEDIUM-AQUAMARINE",AB_package);
    Qmedium_blue = STATIC_SYMBOL("MEDIUM-BLUE",AB_package);
    Qmedium_goldenrod = STATIC_SYMBOL("MEDIUM-GOLDENROD",AB_package);
    Qmedium_orchid = STATIC_SYMBOL("MEDIUM-ORCHID",AB_package);
    Qorange = STATIC_SYMBOL("ORANGE",AB_package);
    Qpale_green = STATIC_SYMBOL("PALE-GREEN",AB_package);
    Qpink = STATIC_SYMBOL("PINK",AB_package);
    Qplum = STATIC_SYMBOL("PLUM",AB_package);
    Qpurple = STATIC_SYMBOL("PURPLE",AB_package);
    Qred = STATIC_SYMBOL("RED",AB_package);
    Qsalmon = STATIC_SYMBOL("SALMON",AB_package);
    Qsienna = STATIC_SYMBOL("SIENNA",AB_package);
    Qsky_blue = STATIC_SYMBOL("SKY-BLUE",AB_package);
    Qslate_blue = STATIC_SYMBOL("SLATE-BLUE",AB_package);
    Qthistle = STATIC_SYMBOL("THISTLE",AB_package);
    Qturquoise = STATIC_SYMBOL("TURQUOISE",AB_package);
    Qviolet = STATIC_SYMBOL("VIOLET",AB_package);
    Qviolet_red = STATIC_SYMBOL("VIOLET-RED",AB_package);
    Qwheat = STATIC_SYMBOL("WHEAT",AB_package);
    Qwhite = STATIC_SYMBOL("WHITE",AB_package);
    Qyellow = STATIC_SYMBOL("YELLOW",AB_package);
    Qsmoke = STATIC_SYMBOL("SMOKE",AB_package);
    Qfloral_white = STATIC_SYMBOL("FLORAL-WHITE",AB_package);
    Qlinen = STATIC_SYMBOL("LINEN",AB_package);
    Qantique_white = STATIC_SYMBOL("ANTIQUE-WHITE",AB_package);
    Qivory = STATIC_SYMBOL("IVORY",AB_package);
    Qazure = STATIC_SYMBOL("AZURE",AB_package);
    Qlavender = STATIC_SYMBOL("LAVENDER",AB_package);
    Qlight_steel_blue = STATIC_SYMBOL("LIGHT-STEEL-BLUE",AB_package);
    Qpowder_blue = STATIC_SYMBOL("POWDER-BLUE",AB_package);
    Qpale_turquoise = STATIC_SYMBOL("PALE-TURQUOISE",AB_package);
    Qlight_cyan = STATIC_SYMBOL("LIGHT-CYAN",AB_package);
    Qpale_goldenrod = STATIC_SYMBOL("PALE-GOLDENROD",AB_package);
    Qlight_goldenrod_yellow = STATIC_SYMBOL("LIGHT-GOLDENROD-YELLOW",
	    AB_package);
    Qlight_yellow = STATIC_SYMBOL("LIGHT-YELLOW",AB_package);
    Qlight_goldenrod = STATIC_SYMBOL("LIGHT-GOLDENROD",AB_package);
    Qbeige = STATIC_SYMBOL("BEIGE",AB_package);
    Qlight_pink = STATIC_SYMBOL("LIGHT-PINK",AB_package);
    Qextra_light_gray = STATIC_SYMBOL("EXTRA-LIGHT-GRAY",AB_package);
    list_constant_74 = STATIC_CONS(Qextra_light_gray,Qnil);
    list_constant_75 = STATIC_LIST_STAR((SI_Long)32L,Qpurple,Qred,Qsalmon,
	    Qsienna,Qsky_blue,Qslate_blue,Qtan,Qthistle,Qturquoise,Qviolet,
	    Qviolet_red,Qwheat,Qwhite,Qyellow,Qsmoke,Qfloral_white,Qlinen,
	    Qantique_white,Qivory,Qazure,Qlavender,Qlight_steel_blue,
	    Qpowder_blue,Qpale_turquoise,Qlight_cyan,Qpale_goldenrod,
	    Qlight_goldenrod_yellow,Qlight_yellow,Qlight_goldenrod,Qbeige,
	    Qlight_pink,list_constant_74);
    list_constant_76 = STATIC_LIST_STAR((SI_Long)32L,Qaquamarine,Qblack,
	    Qblue,Qbrown,Qcadet_blue,Qcoral,Qcyan,Qdark_gray,
	    Qdark_slate_blue,Qdim_gray,Qforest_green,Qgold,Qgoldenrod,
	    Qgray,Qgreen,Qgreen_yellow,Qindian_red,Qkhaki,Qlight_blue,
	    Qlight_gray,Qlime_green,Qmagenta,Qmaroon,Qmedium_aquamarine,
	    Qmedium_blue,Qmedium_goldenrod,Qmedium_orchid,Qorange,
	    Qpale_green,Qpink,Qplum,list_constant_75);
    Qunreserved_symbol = STATIC_SYMBOL("UNRESERVED-SYMBOL",AB_package);
    def_semi_open_category_1(5,Qcolor,list_constant_76,Qunreserved_symbol,
	    Nil,Nil);
    Qmetacolor = STATIC_SYMBOL("METACOLOR",AB_package);
    Qtransparent = STATIC_SYMBOL("TRANSPARENT",AB_package);
    Qforeground = STATIC_SYMBOL("FOREGROUND",AB_package);
    list_constant_77 = STATIC_LIST((SI_Long)2L,Qtransparent,Qforeground);
    def_semi_open_category_1(5,Qmetacolor,list_constant_77,
	    Qunreserved_symbol,Nil,Nil);
    Qwidth = STATIC_SYMBOL("WIDTH",AB_package);
    Qheight = STATIC_SYMBOL("HEIGHT",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qwidth,Qheight);
    array_constant_1 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)10L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)11L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)12L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)22L,(SI_Long)17L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)23L,(SI_Long)57344L);
    string_constant_8 = 
	    STATIC_STRING(" contains an invalid point. Report the problem to Gensym.~% ");
    array_constant_3 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)22L,(SI_Long)15L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)23L,(SI_Long)57344L);
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    Qlarge = STATIC_SYMBOL("LARGE",AB_package);
    Qextra_large = STATIC_SYMBOL("EXTRA-LARGE",AB_package);
    list_constant_1 = STATIC_LIST((SI_Long)3L,Qsmall,Qlarge,Qextra_large);
    array_constant_4 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)19L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)57344L);
    array_constant_5 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)9L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)10L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)13L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)15L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)16L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)18L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)19L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)22L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)23L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)25L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)26L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)27L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)28L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)29L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)30L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)32L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)33L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)34L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)35L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)36L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)37L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)38L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)39L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)40L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)42L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)43L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)44L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)45L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)46L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)47L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)48L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)49L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)50L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)51L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)52L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)53L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)54L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)55L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)56L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)57L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)58L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)59L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)60L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)61L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)62L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)63L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)64L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)65L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)66L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)78L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)79L,(SI_Long)57344L);
    array_constant_6 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)80L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)32L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)33L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)34L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)35L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)37L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)40L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)41L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)42L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)43L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)44L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)45L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)46L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)47L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)48L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)49L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)50L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)51L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)52L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)53L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)54L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)55L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)56L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)57L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)58L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)59L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)60L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)61L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)62L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)63L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)64L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)78L,(SI_Long)65L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)79L,(SI_Long)57344L);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qimage = STATIC_SYMBOL("IMAGE",AB_package);
    Qsolid_rectangle = STATIC_SYMBOL("SOLID-RECTANGLE",AB_package);
    Qfilled_circle = STATIC_SYMBOL("FILLED-CIRCLE",AB_package);
    Qstippled_area = STATIC_SYMBOL("STIPPLED-AREA",AB_package);
    Qfilled_polygon = STATIC_SYMBOL("FILLED-POLYGON",AB_package);
    string_constant_9 = STATIC_STRING("~% The ");
    string_constant_10 = STATIC_STRING(" the local variable ~s");
    string_constant_11 = STATIC_STRING(" = ~s");
    array_constant_7 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    array_constant_8 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    array_constant_9 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)15L,(SI_Long)57344L);
    list_constant_78 = STATIC_LIST_STAR((SI_Long)3L,Qwidth,Qheight,
	    list_constant_1);
    Reserved_icon_variable_names = list_constant_78;
    string_constant_12 = 
	    STATIC_STRING("~s is a reserved icon variable name.~%");
    string_constant_13 = 
	    STATIC_STRING("The reserved icon variable names are ~%");
    string_constant_14 = STATIC_STRING(" and ");
    string_constant_15 = STATIC_STRING(", ");
    string_constant_16 = STATIC_STRING(".");
    string_constant_17 = 
	    STATIC_STRING("Width and height must be a positive integer.");
    string_constant_18 = 
	    STATIC_STRING("Width and height must be less than or equal to ~d.");
    float_constant = STATIC_FLOAT(0.0);
    string_constant_19 = 
	    STATIC_STRING("The product of width and height must be less than or equal to ~d.");
    Qclass_inheritance_path_of_definition = 
	    STATIC_SYMBOL("CLASS-INHERITANCE-PATH-OF-DEFINITION",AB_package);
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qlookup = STATIC_SYMBOL("LOOKUP",AB_package);
    Qicon_description = STATIC_SYMBOL("ICON-DESCRIPTION",AB_package);
    string_constant_20 = 
	    string_append2(STATIC_STRING("Cannot change the icon-description of ~NF.  The value ~\n                 of the direct-superior-classes attribute on the ~\n                 class-definition does not indicate "),
	    STATIC_STRING("that the class has a ~\n                 changeable icon-description."));
    Qinherited = STATIC_SYMBOL("INHERITED",AB_package);
    Qpolychrome = STATIC_SYMBOL("POLYCHROME",AB_package);
    Qsc = STATIC_SYMBOL(";",AB_package);
    Qnot_simple_polygon = STATIC_SYMBOL("NOT-SIMPLE-POLYGON",AB_package);
    Qtoo_many_points = STATIC_SYMBOL("TOO-MANY-POINTS",AB_package);
    string_constant_21 = STATIC_STRING("The ");
    string_constant_22 = 
	    STATIC_STRING(" crosses itself or has two identical vertices.");
    string_constant_23 = 
	    STATIC_STRING(" contains ~s points. ~s is the maximum.");
    string_constant_24 = STATIC_STRING(" is not valid.");
    Qvariables = STATIC_SYMBOL("VARIABLES",AB_package);
    Qbackground_layer = STATIC_SYMBOL("BACKGROUND-LAYER",AB_package);
    Qstipple = STATIC_SYMBOL("STIPPLE",AB_package);
    Qicon_description_qm = STATIC_SYMBOL("ICON-DESCRIPTION\?",AB_package);
    Qcompile_icon_description_qm_for_slot = 
	    STATIC_SYMBOL("COMPILE-ICON-DESCRIPTION\?-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_icon_description_qm_for_slot,
	    STATIC_FUNCTION(compile_icon_description_qm_for_slot,NIL,TRUE,
	    3,6));
    mutate_global_property(Qicon_description_qm,
	    SYMBOL_FUNCTION(Qcompile_icon_description_qm_for_slot),
	    Qslot_value_compiler);
    mutate_global_property(Qicon_description_qm,Nil,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qoutline = STATIC_SYMBOL("OUTLINE",AB_package);
    Qlines = STATIC_SYMBOL("LINES",AB_package);
    string_constant_25 = 
	    STATIC_STRING("The symbol ~a does not belong here, since it ~\n     is not a declared region, a color, or a metacolor.");
    array_constant_10 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    array_constant_11 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)61L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)7L,(SI_Long)57344L);
    string_constant_26 = STATIC_STRING(";~%");
    string_constant_27 = STATIC_STRING("variables :~%    ");
    string_constant_28 = STATIC_STRING("icon-background-layer : ");
    string_constant_29 = STATIC_STRING("color image ");
    string_constant_30 = STATIC_STRING("; ~%");
    string_constant_31 = STATIC_STRING("inherited");
    string_constant_32 = STATIC_STRING("width ~d; ");
    string_constant_33 = STATIC_STRING("height ~d;~%");
    string_constant_34 = STATIC_STRING("stipple: ~(~a~);~%");
    string_constant_35 = STATIC_STRING("    ");
    string_constant_36 = STATIC_STRING(":~%");
    Qwrite_icon_description_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-ICON-DESCRIPTION\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_icon_description_qm_from_slot,
	    STATIC_FUNCTION(write_icon_description_qm_from_slot,NIL,FALSE,
	    2,2));
    mutate_global_property(Qicon_description_qm,
	    SYMBOL_FUNCTION(Qwrite_icon_description_qm_from_slot),
	    Qslot_value_writer);
    string_constant_37 = STATIC_STRING("stippled area ~(~a~)");
    Qpoint = STATIC_SYMBOL("POINT",AB_package);
    Qcircle = STATIC_SYMBOL("CIRCLE",AB_package);
    list_constant_2 = STATIC_LIST((SI_Long)7L,Qpoint,Qlines,Qoutline,
	    Qsolid_rectangle,Qcircle,Qfilled_polygon,Qfilled_circle);
    string_constant_38 = STATIC_STRING("filled rectangle");
    string_constant_39 = STATIC_STRING("filled polygon");
    string_constant_40 = STATIC_STRING("filled circle");
    array_constant_12 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)2L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_12,(SI_Long)7L,(SI_Long)57344L);
    array_constant_13 = STATIC_ARRAY(list_constant_73,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    Qab_slot_value = STATIC_SYMBOL("SLOT-VALUE",AB_package);
    string_constant_41 = STATIC_STRING(" arc (~A, ~A)");
    string_constant_42 = STATIC_STRING(" (~A, ~A)");
    Qregion_specification = STATIC_SYMBOL("REGION-SPECIFICATION",AB_package);
    Qtype_specification_simple_expansion = 
	    STATIC_SYMBOL("TYPE-SPECIFICATION-SIMPLE-EXPANSION",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    list_constant_61 = STATIC_CONS(Qab_structure,Qnil);
    set_property_value_function(get_symbol_properties_function(Qregion_specification),
	    Qtype_specification_simple_expansion,list_constant_61);
    Qregion_name = STATIC_SYMBOL("REGION-NAME",AB_package);
    list_constant_80 = STATIC_LIST((SI_Long)2L,Qregion_name,Qsymbol);
    Qcolor_name = STATIC_SYMBOL("COLOR-NAME",AB_package);
    Qnamed = STATIC_SYMBOL("NAMED",AB_package);
    Qcolor_or_metacolor = STATIC_SYMBOL("COLOR-OR-METACOLOR",AB_package);
    list_constant_79 = STATIC_LIST((SI_Long)2L,Qnamed,Qcolor_or_metacolor);
    list_constant_81 = STATIC_LIST((SI_Long)2L,Qcolor_name,list_constant_79);
    list_constant_82 = STATIC_LIST((SI_Long)2L,list_constant_80,
	    list_constant_81);
    list_constant_83 = STATIC_LIST((SI_Long)3L,Qand,Qregion_name,Qcolor_name);
    list_constant_4 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_82,list_constant_83);
    define_type_specification_explicit_complex_type(Qregion_specification,
	    list_constant_4);
    list_constant_3 = STATIC_LIST((SI_Long)2L,Qnamed,Qregion_specification);
    Qcategory_evaluator_interface = 
	    STATIC_SYMBOL("CATEGORY-EVALUATOR-INTERFACE",AB_package);
    region_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(region_specification_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qregion_specification,
	    region_specification_evaluation_setter_1);
    region_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(region_specification_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qregion_specification,
	    region_specification_evaluation_getter_1);
    Qregion_specification_list = STATIC_SYMBOL("REGION-SPECIFICATION-LIST",
	    AB_package);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qno_item = STATIC_SYMBOL("NO-ITEM",AB_package);
    list_constant_60 = STATIC_CONS(Qno_item,Qnil);
    list_constant_64 = STATIC_CONS(Qsequence,Qnil);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_60,
	    list_constant_64);
    set_property_value_function(get_symbol_properties_function(Qregion_specification_list),
	    Qtype_specification_simple_expansion,list_constant_84);
    list_constant_85 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_3,
	    FIX((SI_Long)1L));
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_60,
	    list_constant_85);
    define_type_specification_explicit_complex_type(Qregion_specification_list,
	    list_constant_6);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qregion_specification_list);
    region_specification_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(region_specification_list_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qregion_specification_list,
	    region_specification_list_evaluation_setter_1);
    region_specification_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(region_specification_list_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qregion_specification_list,
	    region_specification_list_evaluation_getter_1);
    Qvariable_specification = STATIC_SYMBOL("VARIABLE-SPECIFICATION",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qvariable_specification),
	    Qtype_specification_simple_expansion,list_constant_61);
    Qvariable_name = STATIC_SYMBOL("VARIABLE-NAME",AB_package);
    list_constant_86 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_88 = STATIC_CONS(Qvariable_name,list_constant_86);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    list_constant_87 = STATIC_LIST((SI_Long)4L,Qab_or,Qinteger,Qsymbol,Qtext);
    list_constant_89 = STATIC_LIST((SI_Long)2L,Qinitial_value,
	    list_constant_87);
    list_constant_90 = STATIC_LIST((SI_Long)2L,list_constant_88,
	    list_constant_89);
    list_constant_91 = STATIC_LIST((SI_Long)3L,Qand,Qvariable_name,
	    Qinitial_value);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_90,list_constant_91);
    define_type_specification_explicit_complex_type(Qvariable_specification,
	    list_constant_8);
    list_constant_7 = STATIC_LIST((SI_Long)2L,Qnamed,Qvariable_specification);
    variable_specification_evaluation_setter_1 = 
	    STATIC_FUNCTION(variable_specification_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qvariable_specification,
	    variable_specification_evaluation_setter_1);
    Qfloat_array = STATIC_SYMBOL("FLOAT-ARRAY",AB_package);
    Qcreated_simple_float_array_pool_arrays = 
	    STATIC_SYMBOL("CREATED-SIMPLE-FLOAT-ARRAY-POOL-ARRAYS",AB_package);
    Qsimple_float_array_pool_memory_usage = 
	    STATIC_SYMBOL("SIMPLE-FLOAT-ARRAY-POOL-MEMORY-USAGE",AB_package);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    variable_specification_evaluation_getter_1 = 
	    STATIC_FUNCTION(variable_specification_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qvariable_specification,
	    variable_specification_evaluation_getter_1);
    Qvariable_specification_list = 
	    STATIC_SYMBOL("VARIABLE-SPECIFICATION-LIST",AB_package);
    set_property_value_function(get_symbol_properties_function(Qvariable_specification_list),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_92 = STATIC_CONS(FIX((SI_Long)1L),Qnil);
    list_constant_10 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_7,list_constant_92);
    define_type_specification_explicit_complex_type(Qvariable_specification_list,
	    list_constant_10);
    list_constant_9 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qvariable_specification_list);
    variable_specification_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(variable_specification_list_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qvariable_specification_list,
	    variable_specification_list_evaluation_setter_1);
    variable_specification_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(variable_specification_list_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qvariable_specification_list,
	    variable_specification_list_evaluation_getter_1);
    Qfont_size = STATIC_SYMBOL("FONT-SIZE",AB_package);
    list_constant_93 = STATIC_LIST((SI_Long)3L,Qab_or,Qnil,Qnil);
    set_property_value_function(get_symbol_properties_function(Qfont_size),
	    Qtype_specification_simple_expansion,list_constant_93);
    list_constant_94 = STATIC_CONS(Qmember,list_constant_1);
    list_constant_95 = STATIC_LIST((SI_Long)2L,Qnamed,Qunreserved_symbol);
    list_constant_12 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_94,
	    list_constant_95);
    define_type_specification_explicit_complex_type(Qfont_size,
	    list_constant_12);
    list_constant_11 = STATIC_LIST((SI_Long)2L,Qnamed,Qfont_size);
    font_size_evaluation_setter_1 = 
	    STATIC_FUNCTION(font_size_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfont_size,
	    font_size_evaluation_setter_1);
    font_size_evaluation_getter_1 = 
	    STATIC_FUNCTION(font_size_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfont_size,
	    font_size_evaluation_getter_1);
    Qpoint_factor = STATIC_SYMBOL("POINT-FACTOR",AB_package);
    list_constant_96 = STATIC_CONS(Qnil,Qnil);
    list_constant_97 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_96);
    set_property_value_function(get_symbol_properties_function(Qpoint_factor),
	    Qtype_specification_simple_expansion,list_constant_97);
    list_constant_98 = STATIC_CONS(list_constant_95,Qnil);
    list_constant_14 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,Qinteger,
	    list_constant_98);
    define_type_specification_explicit_complex_type(Qpoint_factor,
	    list_constant_14);
    list_constant_13 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoint_factor);
    point_factor_evaluation_setter_1 = 
	    STATIC_FUNCTION(point_factor_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoint_factor,
	    point_factor_evaluation_setter_1);
    point_factor_evaluation_getter_1 = 
	    STATIC_FUNCTION(point_factor_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoint_factor,
	    point_factor_evaluation_getter_1);
    Qpoint_sum = STATIC_SYMBOL("POINT-SUM",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpoint_sum),
	    Qtype_specification_simple_expansion,Qtext);
    define_type_specification_explicit_complex_type(Qpoint_sum,Qtext);
    list_constant_15 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoint_sum);
    point_sum_evaluation_setter_1 = 
	    STATIC_FUNCTION(point_sum_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoint_sum,
	    point_sum_evaluation_setter_1);
    string_constant_43 = STATIC_STRING("~A");
    point_sum_evaluation_getter_1 = 
	    STATIC_FUNCTION(point_sum_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoint_sum,
	    point_sum_evaluation_getter_1);
    Qpoint_expression = STATIC_SYMBOL("POINT-EXPRESSION",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpoint_expression),
	    Qtype_specification_simple_expansion,list_constant_93);
    list_constant_17 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_13,
	    list_constant_15);
    define_type_specification_explicit_complex_type(Qpoint_expression,
	    list_constant_17);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoint_expression);
    point_expression_evaluation_setter_1 = 
	    STATIC_FUNCTION(point_expression_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoint_expression,
	    point_expression_evaluation_setter_1);
    point_expression_evaluation_getter_1 = 
	    STATIC_FUNCTION(point_expression_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoint_expression,
	    point_expression_evaluation_getter_1);
    set_property_value_function(get_symbol_properties_function(Qpoint),
	    Qtype_specification_simple_expansion,list_constant_61);
    Qx = STATIC_SYMBOL("X",AB_package);
    list_constant_99 = STATIC_CONS(list_constant_16,Qnil);
    list_constant_100 = STATIC_CONS(Qx,list_constant_99);
    Qy = STATIC_SYMBOL("Y",AB_package);
    list_constant_101 = STATIC_CONS(Qy,list_constant_99);
    list_constant_102 = STATIC_LIST((SI_Long)2L,list_constant_100,
	    list_constant_101);
    list_constant_103 = STATIC_LIST((SI_Long)3L,Qand,Qx,Qy);
    list_constant_19 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_102,list_constant_103);
    define_type_specification_explicit_complex_type(Qpoint,list_constant_19);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoint);
    point_evaluation_setter_1 = STATIC_FUNCTION(point_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoint,
	    point_evaluation_setter_1);
    point_evaluation_getter_1 = STATIC_FUNCTION(point_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoint,
	    point_evaluation_getter_1);
    Qpoint_or_arcpoint = STATIC_SYMBOL("POINT-OR-ARCPOINT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpoint_or_arcpoint),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_104 = STATIC_LIST((SI_Long)2L,Qnamed,Qtruth_value);
    list_constant_105 = STATIC_LIST((SI_Long)2L,Qarc,list_constant_104);
    list_constant_106 = STATIC_CONS(list_constant_105,list_constant_102);
    list_constant_107 = STATIC_CONS(list_constant_103,Qnil);
    list_constant_21 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_106,list_constant_107);
    define_type_specification_explicit_complex_type(Qpoint_or_arcpoint,
	    list_constant_21);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoint_or_arcpoint);
    point_or_arcpoint_evaluation_setter_1 = 
	    STATIC_FUNCTION(point_or_arcpoint_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoint_or_arcpoint,
	    point_or_arcpoint_evaluation_setter_1);
    point_or_arcpoint_evaluation_getter_1 = 
	    STATIC_FUNCTION(point_or_arcpoint_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoint_or_arcpoint,
	    point_or_arcpoint_evaluation_getter_1);
    Qstatic_point = STATIC_SYMBOL("STATIC-POINT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qstatic_point),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_108 = STATIC_CONS(Qinteger,Qnil);
    list_constant_109 = STATIC_CONS(Qx,list_constant_108);
    list_constant_110 = STATIC_CONS(Qy,list_constant_108);
    list_constant_111 = STATIC_LIST((SI_Long)2L,list_constant_109,
	    list_constant_110);
    list_constant_23 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_111,list_constant_107);
    define_type_specification_explicit_complex_type(Qstatic_point,
	    list_constant_23);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qnamed,Qstatic_point);
    static_point_evaluation_setter_1 = 
	    STATIC_FUNCTION(static_point_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qstatic_point,
	    static_point_evaluation_setter_1);
    static_point_evaluation_getter_1 = 
	    STATIC_FUNCTION(static_point_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstatic_point,
	    static_point_evaluation_getter_1);
    Qpoints = STATIC_SYMBOL("POINTS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpoints),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_25 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_18,list_constant_92);
    define_type_specification_explicit_complex_type(Qpoints,list_constant_25);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoints);
    points_evaluation_setter_1 = STATIC_FUNCTION(points_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoints,
	    points_evaluation_setter_1);
    points_evaluation_getter_1 = STATIC_FUNCTION(points_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoints,
	    points_evaluation_getter_1);
    Qpoints_or_arcpoints = STATIC_SYMBOL("POINTS-OR-ARCPOINTS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpoints_or_arcpoints),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_27 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_20,list_constant_92);
    define_type_specification_explicit_complex_type(Qpoints_or_arcpoints,
	    list_constant_27);
    list_constant_26 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoints_or_arcpoints);
    points_or_arcpoints_evaluation_setter_1 = 
	    STATIC_FUNCTION(points_or_arcpoints_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoints_or_arcpoints,
	    points_or_arcpoints_evaluation_setter_1);
    points_or_arcpoints_evaluation_getter_1 = 
	    STATIC_FUNCTION(points_or_arcpoints_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoints_or_arcpoints,
	    points_or_arcpoints_evaluation_getter_1);
    Qfilled_polygon_point_tree = STATIC_SYMBOL("FILLED-POLYGON-POINT-TREE",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qfilled_polygon_point_tree),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_29 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_18,
	    FIX((SI_Long)3L));
    define_type_specification_explicit_complex_type(Qfilled_polygon_point_tree,
	    list_constant_29);
    list_constant_28 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qfilled_polygon_point_tree);
    filled_polygon_point_tree_evaluation_setter_1 = 
	    STATIC_FUNCTION(filled_polygon_point_tree_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfilled_polygon_point_tree,
	    filled_polygon_point_tree_evaluation_setter_1);
    filled_polygon_point_tree_evaluation_getter_1 = 
	    STATIC_FUNCTION(filled_polygon_point_tree_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfilled_polygon_point_tree,
	    filled_polygon_point_tree_evaluation_getter_1);
    Qlines_point_tree = STATIC_SYMBOL("LINES-POINT-TREE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlines_point_tree),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_31 = STATIC_LIST((SI_Long)3L,Qsequence,list_constant_20,
	    FIX((SI_Long)2L));
    define_type_specification_explicit_complex_type(Qlines_point_tree,
	    list_constant_31);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qnamed,Qlines_point_tree);
    string_constant_44 = 
	    STATIC_STRING("~%The structure (type: the symbol lines, points: ~NV) contains an invalid use of arc points.");
    lines_point_tree_evaluation_setter_1 = 
	    STATIC_FUNCTION(lines_point_tree_evaluation_setter,NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlines_point_tree,
	    lines_point_tree_evaluation_setter_1);
    lines_point_tree_evaluation_getter_1 = 
	    STATIC_FUNCTION(lines_point_tree_evaluation_getter,NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlines_point_tree,
	    lines_point_tree_evaluation_getter_1);
    Qoutline_point_tree = STATIC_SYMBOL("OUTLINE-POINT-TREE",AB_package);
    set_property_value_function(get_symbol_properties_function(Qoutline_point_tree),
	    Qtype_specification_simple_expansion,list_constant_64);
    define_type_specification_explicit_complex_type(Qoutline_point_tree,
	    list_constant_31);
    list_constant_32 = STATIC_LIST((SI_Long)2L,Qnamed,Qoutline_point_tree);
    string_constant_45 = 
	    STATIC_STRING("~%The structure(type: the symbol outline, points: ~NV) contains an invalid use of arc points.");
    outline_point_tree_evaluation_setter_1 = 
	    STATIC_FUNCTION(outline_point_tree_evaluation_setter,NIL,FALSE,
	    4,4);
    set_evaluation_value_to_category_function(Qoutline_point_tree,
	    outline_point_tree_evaluation_setter_1);
    outline_point_tree_evaluation_getter_1 = 
	    STATIC_FUNCTION(outline_point_tree_evaluation_getter,NIL,FALSE,
	    3,3);
    set_slot_value_to_evaluation_value_function(Qoutline_point_tree,
	    outline_point_tree_evaluation_getter_1);
    Qtext_drawing_element = STATIC_SYMBOL("TEXT-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qtext_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_112 = STATIC_CONS(Qtext,Qnil);
    list_constant_113 = STATIC_CONS(Qmember,list_constant_112);
    list_constant_116 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_113);
    Qlabel = STATIC_SYMBOL("LABEL",AB_package);
    list_constant_114 = STATIC_CONS(Qsymbol,list_constant_112);
    list_constant_115 = STATIC_CONS(Qab_or,list_constant_114);
    list_constant_117 = STATIC_LIST((SI_Long)2L,Qlabel,list_constant_115);
    list_constant_118 = STATIC_LIST((SI_Long)2L,Qpoint,list_constant_18);
    list_constant_119 = STATIC_LIST((SI_Long)2L,Qfont_size,list_constant_11);
    list_constant_121 = STATIC_LIST((SI_Long)4L,list_constant_116,
	    list_constant_117,list_constant_118,list_constant_119);
    list_constant_120 = STATIC_CONS(Qfont_size,Qnil);
    list_constant_122 = STATIC_LIST_STAR((SI_Long)5L,Qand,Qtype,Qlabel,
	    Qpoint,list_constant_120);
    list_constant_34 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_121,list_constant_122);
    define_type_specification_explicit_complex_type(Qtext_drawing_element,
	    list_constant_34);
    list_constant_33 = STATIC_LIST((SI_Long)2L,Qnamed,Qtext_drawing_element);
    text_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(text_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qtext_drawing_element,
	    text_drawing_element_evaluation_setter_1);
    text_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(text_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qtext_drawing_element,
	    text_drawing_element_evaluation_getter_1);
    Qimage_drawing_element = STATIC_SYMBOL("IMAGE-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qimage_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_123 = STATIC_LIST((SI_Long)2L,Qmember,Qimage);
    list_constant_124 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_123);
    list_constant_125 = STATIC_CONS(Qimage_name,list_constant_86);
    list_constant_126 = STATIC_LIST((SI_Long)3L,list_constant_124,
	    list_constant_125,list_constant_118);
    list_constant_127 = STATIC_LIST((SI_Long)3L,Qand,Qtype,Qimage_name);
    list_constant_36 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_126,list_constant_127);
    define_type_specification_explicit_complex_type(Qimage_drawing_element,
	    list_constant_36);
    list_constant_35 = STATIC_LIST((SI_Long)2L,Qnamed,Qimage_drawing_element);
    image_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(image_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qimage_drawing_element,
	    image_drawing_element_evaluation_setter_1);
    image_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(image_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qimage_drawing_element,
	    image_drawing_element_evaluation_getter_1);
    Qbackground_image_drawing_element = 
	    STATIC_SYMBOL("BACKGROUND-IMAGE-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qbackground_image_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_128 = STATIC_LIST((SI_Long)2L,Qpoint,list_constant_22);
    list_constant_129 = STATIC_LIST((SI_Long)3L,list_constant_124,
	    list_constant_125,list_constant_128);
    list_constant_130 = STATIC_CONS(list_constant_127,Qnil);
    list_constant_38 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_129,list_constant_130);
    define_type_specification_explicit_complex_type(Qbackground_image_drawing_element,
	    list_constant_38);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qbackground_image_drawing_element);
    background_image_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(background_image_drawing_element_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qbackground_image_drawing_element,
	    background_image_drawing_element_evaluation_setter_1);
    background_image_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(background_image_drawing_element_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qbackground_image_drawing_element,
	    background_image_drawing_element_evaluation_getter_1);
    Qicon_background_layer_element = 
	    STATIC_SYMBOL("ICON-BACKGROUND-LAYER-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qicon_background_layer_element),
	    Qtype_specification_simple_expansion,list_constant_93);
    list_constant_131 = STATIC_CONS(list_constant_79,Qnil);
    list_constant_40 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_37,list_constant_131);
    define_type_specification_explicit_complex_type(Qicon_background_layer_element,
	    list_constant_40);
    list_constant_39 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qicon_background_layer_element);
    icon_background_layer_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(icon_background_layer_element_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qicon_background_layer_element,
	    icon_background_layer_element_evaluation_setter_1);
    icon_background_layer_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(icon_background_layer_element_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qicon_background_layer_element,
	    icon_background_layer_element_evaluation_getter_1);
    Qpoint_drawing_element = STATIC_SYMBOL("POINT-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qpoint_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_132 = STATIC_CONS(Qpoint,Qnil);
    list_constant_133 = STATIC_CONS(Qmember,list_constant_132);
    list_constant_135 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_133);
    list_constant_134 = STATIC_CONS(list_constant_18,Qnil);
    list_constant_136 = STATIC_CONS(Qpoints,list_constant_134);
    list_constant_138 = STATIC_LIST((SI_Long)2L,list_constant_135,
	    list_constant_136);
    list_constant_137 = STATIC_CONS(Qpoints,Qnil);
    list_constant_139 = STATIC_LIST_STAR((SI_Long)3L,Qand,Qtype,
	    list_constant_137);
    list_constant_42 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_138,list_constant_139);
    define_type_specification_explicit_complex_type(Qpoint_drawing_element,
	    list_constant_42);
    list_constant_41 = STATIC_LIST((SI_Long)2L,Qnamed,Qpoint_drawing_element);
    point_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(point_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qpoint_drawing_element,
	    point_drawing_element_evaluation_setter_1);
    point_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(point_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qpoint_drawing_element,
	    point_drawing_element_evaluation_getter_1);
    Qcircle_drawing_element = STATIC_SYMBOL("CIRCLE-DRAWING-ELEMENT",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qcircle_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_140 = STATIC_LIST((SI_Long)2L,Qmember,Qcircle);
    list_constant_141 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_140);
    list_constant_142 = STATIC_LIST((SI_Long)2L,Qpoints,list_constant_24);
    list_constant_143 = STATIC_LIST((SI_Long)2L,list_constant_141,
	    list_constant_142);
    list_constant_144 = STATIC_CONS(list_constant_139,Qnil);
    list_constant_44 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_143,list_constant_144);
    define_type_specification_explicit_complex_type(Qcircle_drawing_element,
	    list_constant_44);
    list_constant_43 = STATIC_LIST((SI_Long)2L,Qnamed,Qcircle_drawing_element);
    string_constant_46 = 
	    STATIC_STRING("The circle ~s should have exactly 3 points");
    circle_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(circle_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qcircle_drawing_element,
	    circle_drawing_element_evaluation_setter_1);
    circle_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(circle_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qcircle_drawing_element,
	    circle_drawing_element_evaluation_getter_1);
    Qsolid_rectangle_drawing_element = 
	    STATIC_SYMBOL("SOLID-RECTANGLE-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qsolid_rectangle_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    Qfilled_rectangle = STATIC_SYMBOL("FILLED-RECTANGLE",AB_package);
    list_constant_145 = STATIC_LIST((SI_Long)2L,Qmember,Qfilled_rectangle);
    list_constant_146 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_145);
    list_constant_147 = STATIC_CONS(list_constant_142,Qnil);
    list_constant_148 = STATIC_CONS(list_constant_146,list_constant_147);
    list_constant_46 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_148,list_constant_144);
    define_type_specification_explicit_complex_type(Qsolid_rectangle_drawing_element,
	    list_constant_46);
    list_constant_45 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qsolid_rectangle_drawing_element);
    string_constant_47 = 
	    STATIC_STRING("The filled-rectangle ~s should have exactly 2 points");
    solid_rectangle_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(solid_rectangle_drawing_element_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qsolid_rectangle_drawing_element,
	    solid_rectangle_drawing_element_evaluation_setter_1);
    solid_rectangle_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(solid_rectangle_drawing_element_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qsolid_rectangle_drawing_element,
	    solid_rectangle_drawing_element_evaluation_getter_1);
    Qfilled_circle_drawing_element = 
	    STATIC_SYMBOL("FILLED-CIRCLE-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qfilled_circle_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_149 = STATIC_CONS(Qfilled_circle,Qnil);
    list_constant_150 = STATIC_CONS(Qmember,list_constant_149);
    list_constant_151 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_150);
    list_constant_152 = STATIC_CONS(list_constant_151,list_constant_147);
    list_constant_48 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_152,list_constant_144);
    define_type_specification_explicit_complex_type(Qfilled_circle_drawing_element,
	    list_constant_48);
    list_constant_47 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qfilled_circle_drawing_element);
    string_constant_48 = 
	    STATIC_STRING("The filled-circle ~s should have exactly 3 points");
    filled_circle_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(filled_circle_drawing_element_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfilled_circle_drawing_element,
	    filled_circle_drawing_element_evaluation_setter_1);
    filled_circle_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(filled_circle_drawing_element_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfilled_circle_drawing_element,
	    filled_circle_drawing_element_evaluation_getter_1);
    Qlines_drawing_element = STATIC_SYMBOL("LINES-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlines_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_153 = STATIC_LIST((SI_Long)2L,Qmember,Qlines);
    list_constant_154 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_153);
    list_constant_155 = STATIC_LIST((SI_Long)2L,Qpoints,list_constant_30);
    list_constant_156 = STATIC_LIST((SI_Long)2L,list_constant_154,
	    list_constant_155);
    list_constant_50 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_156,list_constant_144);
    define_type_specification_explicit_complex_type(Qlines_drawing_element,
	    list_constant_50);
    list_constant_49 = STATIC_LIST((SI_Long)2L,Qnamed,Qlines_drawing_element);
    lines_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(lines_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlines_drawing_element,
	    lines_drawing_element_evaluation_setter_1);
    lines_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(lines_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlines_drawing_element,
	    lines_drawing_element_evaluation_getter_1);
    Qoutline_drawing_element = STATIC_SYMBOL("OUTLINE-DRAWING-ELEMENT",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qoutline_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_157 = STATIC_LIST((SI_Long)2L,Qmember,Qoutline);
    list_constant_158 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_157);
    list_constant_159 = STATIC_LIST((SI_Long)2L,Qpoints,list_constant_32);
    list_constant_160 = STATIC_LIST((SI_Long)2L,list_constant_158,
	    list_constant_159);
    list_constant_52 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_160,list_constant_144);
    define_type_specification_explicit_complex_type(Qoutline_drawing_element,
	    list_constant_52);
    list_constant_51 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qoutline_drawing_element);
    outline_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(outline_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qoutline_drawing_element,
	    outline_drawing_element_evaluation_setter_1);
    outline_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(outline_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qoutline_drawing_element,
	    outline_drawing_element_evaluation_getter_1);
    Qfilled_polygon_drawing_element = 
	    STATIC_SYMBOL("FILLED-POLYGON-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qfilled_polygon_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_161 = STATIC_LIST((SI_Long)2L,Qmember,Qfilled_polygon);
    list_constant_162 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_161);
    list_constant_163 = STATIC_LIST((SI_Long)2L,Qpoints,list_constant_28);
    list_constant_164 = STATIC_LIST((SI_Long)2L,list_constant_162,
	    list_constant_163);
    list_constant_54 = STATIC_LIST_STAR((SI_Long)3L,Qab_structure,
	    list_constant_164,list_constant_144);
    define_type_specification_explicit_complex_type(Qfilled_polygon_drawing_element,
	    list_constant_54);
    list_constant_53 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qfilled_polygon_drawing_element);
    filled_polygon_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(filled_polygon_drawing_element_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qfilled_polygon_drawing_element,
	    filled_polygon_drawing_element_evaluation_setter_1);
    filled_polygon_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(filled_polygon_drawing_element_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qfilled_polygon_drawing_element,
	    filled_polygon_drawing_element_evaluation_getter_1);
    Qstippled_area_drawing_element = 
	    STATIC_SYMBOL("STIPPLED-AREA-DRAWING-ELEMENT",AB_package);
    set_property_value_function(get_symbol_properties_function(Qstippled_area_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_61);
    list_constant_165 = STATIC_LIST((SI_Long)2L,Qmember,Qstippled_area);
    list_constant_167 = STATIC_LIST((SI_Long)2L,Qtype,list_constant_165);
    Qlight_stipple = STATIC_SYMBOL("LIGHT-STIPPLE",AB_package);
    Qmedium_stipple = STATIC_SYMBOL("MEDIUM-STIPPLE",AB_package);
    Qdark_stipple = STATIC_SYMBOL("DARK-STIPPLE",AB_package);
    list_constant_166 = STATIC_LIST((SI_Long)4L,Qmember,Qlight_stipple,
	    Qmedium_stipple,Qdark_stipple);
    list_constant_168 = STATIC_LIST((SI_Long)2L,Qstipple,list_constant_166);
    list_constant_169 = STATIC_LIST_STAR((SI_Long)3L,list_constant_167,
	    list_constant_168,list_constant_147);
    list_constant_170 = STATIC_LIST((SI_Long)3L,Qand,Qtype,Qstipple);
    list_constant_56 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_169,list_constant_170);
    define_type_specification_explicit_complex_type(Qstippled_area_drawing_element,
	    list_constant_56);
    list_constant_55 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qstippled_area_drawing_element);
    string_constant_49 = 
	    STATIC_STRING("The stippled-area ~s should have no points or exactly 2 points");
    stippled_area_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(stippled_area_drawing_element_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qstippled_area_drawing_element,
	    stippled_area_drawing_element_evaluation_setter_1);
    stippled_area_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(stippled_area_drawing_element_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qstippled_area_drawing_element,
	    stippled_area_drawing_element_evaluation_getter_1);
    list_constant_171 = STATIC_CONS(Qstippled_area,Qnil);
    list_constant_57 = STATIC_LIST_STAR((SI_Long)10L,Qtext,Qimage,Qpoint,
	    Qcircle,Qfilled_circle,Qlines,Qoutline,Qfilled_polygon,
	    Qsolid_rectangle,list_constant_171);
    string_constant_50 = STATIC_STRING("~a-~a");
    Qdrawing_element = STATIC_SYMBOL("DRAWING-ELEMENT",AB_package);
    Qbad_element_type_error = STATIC_SYMBOL("BAD-ELEMENT-TYPE-ERROR",
	    AB_package);
    Qline_drawing_element = STATIC_SYMBOL("LINE-DRAWING-ELEMENT",AB_package);
    list_constant_172 = STATIC_CONS(Qnil,list_constant_96);
    list_constant_173 = STATIC_LIST_STAR((SI_Long)10L,Qab_or,Qnil,Qnil,
	    Qnil,Qnil,Qnil,Qnil,Qnil,Qnil,list_constant_172);
    set_property_value_function(get_symbol_properties_function(Qline_drawing_element),
	    Qtype_specification_simple_expansion,list_constant_173);
    list_constant_59 = STATIC_LIST((SI_Long)11L,Qab_or,list_constant_33,
	    list_constant_35,list_constant_41,list_constant_43,
	    list_constant_45,list_constant_47,list_constant_49,
	    list_constant_51,list_constant_53,list_constant_55);
    define_type_specification_explicit_complex_type(Qline_drawing_element,
	    list_constant_59);
    list_constant_58 = STATIC_LIST((SI_Long)2L,Qnamed,Qline_drawing_element);
    string_constant_51 = 
	    STATIC_STRING("a line-drawing-element can not be empty");
    string_constant_52 = 
	    STATIC_STRING("~s is not a valid drawing-element type.");
    string_constant_53 = STATIC_STRING("~NT ");
    string_constant_54 = 
	    STATIC_STRING("~NV must be one of the following types: ~a");
    line_drawing_element_evaluation_setter_1 = 
	    STATIC_FUNCTION(line_drawing_element_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qline_drawing_element,
	    line_drawing_element_evaluation_setter_1);
    line_drawing_element_evaluation_getter_1 = 
	    STATIC_FUNCTION(line_drawing_element_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qline_drawing_element,
	    line_drawing_element_evaluation_getter_1);
    Qline_drawing_elements = STATIC_SYMBOL("LINE-DRAWING-ELEMENTS",AB_package);
    set_property_value_function(get_symbol_properties_function(Qline_drawing_elements),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_58,list_constant_92);
    define_type_specification_explicit_complex_type(Qline_drawing_elements,
	    list_constant_63);
    list_constant_62 = STATIC_LIST((SI_Long)2L,Qnamed,Qline_drawing_elements);
    string_constant_55 = 
	    STATIC_STRING("a layer must have at least one element");
    line_drawing_elements_evaluation_setter_1 = 
	    STATIC_FUNCTION(line_drawing_elements_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qline_drawing_elements,
	    line_drawing_elements_evaluation_setter_1);
    line_drawing_elements_evaluation_getter_1 = 
	    STATIC_FUNCTION(line_drawing_elements_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qline_drawing_elements,
	    line_drawing_elements_evaluation_getter_1);
    Qregion_or_color_or_metacolor = 
	    STATIC_SYMBOL("REGION-OR-COLOR-OR-METACOLOR",AB_package);
    list_constant_66 = STATIC_LIST_STAR((SI_Long)3L,Qab_or,
	    list_constant_60,list_constant_86);
    set_property_value_function(get_symbol_properties_function(Qregion_or_color_or_metacolor),
	    Qtype_specification_simple_expansion,list_constant_66);
    define_type_specification_explicit_complex_type(Qregion_or_color_or_metacolor,
	    list_constant_66);
    list_constant_65 = STATIC_LIST((SI_Long)2L,Qnamed,
	    Qregion_or_color_or_metacolor);
    region_or_color_or_metacolor_evaluation_setter_1 = 
	    STATIC_FUNCTION(region_or_color_or_metacolor_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qregion_or_color_or_metacolor,
	    region_or_color_or_metacolor_evaluation_setter_1);
    region_or_color_or_metacolor_evaluation_getter_1 = 
	    STATIC_FUNCTION(region_or_color_or_metacolor_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qregion_or_color_or_metacolor,
	    region_or_color_or_metacolor_evaluation_getter_1);
    Qlayer = STATIC_SYMBOL("LAYER",AB_package);
    set_property_value_function(get_symbol_properties_function(Qlayer),
	    Qtype_specification_simple_expansion,list_constant_61);
    Qregion_or_color = STATIC_SYMBOL("REGION-OR-COLOR",AB_package);
    list_constant_174 = STATIC_LIST((SI_Long)2L,Qregion_or_color,
	    list_constant_65);
    list_constant_175 = STATIC_LIST((SI_Long)2L,Qline_drawing_elements,
	    list_constant_62);
    list_constant_177 = STATIC_LIST((SI_Long)2L,list_constant_174,
	    list_constant_175);
    list_constant_176 = STATIC_CONS(Qline_drawing_elements,Qnil);
    list_constant_178 = STATIC_LIST_STAR((SI_Long)3L,Qand,Qregion_or_color,
	    list_constant_176);
    list_constant_68 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_177,list_constant_178);
    define_type_specification_explicit_complex_type(Qlayer,list_constant_68);
    list_constant_67 = STATIC_LIST((SI_Long)2L,Qnamed,Qlayer);
    string_constant_56 = STATIC_STRING("A layer should not be empty.");
    layer_evaluation_setter_1 = STATIC_FUNCTION(layer_evaluation_setter,
	    NIL,FALSE,4,4);
    set_evaluation_value_to_category_function(Qlayer,
	    layer_evaluation_setter_1);
    layer_evaluation_getter_1 = STATIC_FUNCTION(layer_evaluation_getter,
	    NIL,FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlayer,
	    layer_evaluation_getter_1);
    Qlabel_and_element_list = STATIC_SYMBOL("LABEL-AND-ELEMENT-LIST",
	    AB_package);
    set_property_value_function(get_symbol_properties_function(Qlabel_and_element_list),
	    Qtype_specification_simple_expansion,list_constant_64);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)3L,Qsequence,
	    list_constant_67,list_constant_92);
    define_type_specification_explicit_complex_type(Qlabel_and_element_list,
	    list_constant_70);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qnamed,Qlabel_and_element_list);
    string_constant_57 = STATIC_STRING("layers can not be empty");
    label_and_element_list_evaluation_setter_1 = 
	    STATIC_FUNCTION(label_and_element_list_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qlabel_and_element_list,
	    label_and_element_list_evaluation_setter_1);
    label_and_element_list_evaluation_getter_1 = 
	    STATIC_FUNCTION(label_and_element_list_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qlabel_and_element_list,
	    label_and_element_list_evaluation_getter_1);
    list_constant_179 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_60,
	    list_constant_61);
    set_property_value_function(get_symbol_properties_function(Qicon_description_qm),
	    Qtype_specification_simple_expansion,list_constant_179);
    list_constant_180 = STATIC_CONS(Qwidth,list_constant_108);
    list_constant_181 = STATIC_CONS(Qheight,list_constant_108);
    Qregions = STATIC_SYMBOL("REGIONS",AB_package);
    list_constant_182 = STATIC_LIST((SI_Long)2L,Qregions,list_constant_5);
    list_constant_183 = STATIC_LIST((SI_Long)2L,Qvariables,list_constant_9);
    Qicon_background_layer = STATIC_SYMBOL("ICON-BACKGROUND-LAYER",AB_package);
    list_constant_184 = STATIC_LIST((SI_Long)2L,Qicon_background_layer,
	    list_constant_39);
    Qlayers = STATIC_SYMBOL("LAYERS",AB_package);
    list_constant_185 = STATIC_LIST((SI_Long)2L,Qlayers,list_constant_69);
    list_constant_186 = STATIC_LIST((SI_Long)7L,list_constant_180,
	    list_constant_181,list_constant_182,list_constant_183,
	    list_constant_184,list_constant_168,list_constant_185);
    list_constant_187 = STATIC_LIST((SI_Long)4L,Qand,Qwidth,Qheight,Qlayers);
    list_constant_188 = STATIC_LIST((SI_Long)3L,Qab_structure,
	    list_constant_186,list_constant_187);
    list_constant_72 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_60,
	    list_constant_188);
    define_type_specification_explicit_complex_type(Qicon_description_qm,
	    list_constant_72);
    list_constant_71 = STATIC_LIST((SI_Long)2L,Qnamed,Qicon_description_qm);
    Qcm = STATIC_SYMBOL(",",AB_package);
    icon_description_qm_evaluation_setter_1 = 
	    STATIC_FUNCTION(icon_description_qm_evaluation_setter,NIL,
	    FALSE,4,4);
    set_evaluation_value_to_category_function(Qicon_description_qm,
	    icon_description_qm_evaluation_setter_1);
    icon_description_qm_evaluation_getter_1 = 
	    STATIC_FUNCTION(icon_description_qm_evaluation_getter,NIL,
	    FALSE,3,3);
    set_slot_value_to_evaluation_value_function(Qicon_description_qm,
	    icon_description_qm_evaluation_getter_1);
}
