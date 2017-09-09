/* gram1a.c
 * Input file:  grammar1a.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "gram1a.h"


/* MAKE-PHRASE-SEQUENCE-FROM-SEQUENCE-COMPONENT-LIST */
Object make_phrase_sequence_from_sequence_component_list(sequence_component_list)
    Object sequence_component_list;
{
    Object temp;

    x_note_fn_call(195,0);
    temp = phrase_cons(sequence_component_list,Phrase_sequence_marker);
    return VALUES_1(temp);
}

/* MAKE-EMPTY-PHRASE-SEQUENCE-KLUDGE */
Object make_empty_phrase_sequence_kludge(nothing_1)
    Object nothing_1;
{
    x_note_fn_call(195,1);
    return phrase_cons(Qnil,Phrase_sequence_marker);
}

/* MAKE-EMPTY-PHRASE-STRUCTURE-KLUDGE */
Object make_empty_phrase_structure_kludge(nothing_1)
    Object nothing_1;
{
    x_note_fn_call(195,2);
    return phrase_cons(Qnil,Phrase_structure_marker);
}

/* MAKE-PHRASE-STRUCTURE-FROM-STRUCTURE-COMPONENT-LIST */
Object make_phrase_structure_from_structure_component_list(structure_component_list)
    Object structure_component_list;
{
    Object i, v, ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp;

    x_note_fn_call(195,3);
    i = Nil;
    v = Nil;
    ab_loop_list_ = structure_component_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    i = CAR(ab_loop_desetq_);
    v = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = phrase_cons(i,Nil);
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    ab_loopvar__2 = phrase_cons(v,Nil);
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
    temp = phrase_cons(temp,Phrase_structure_marker);
    return VALUES_1(temp);
}

static Object string_constant;     /* "binary" */

/* CONVERT-BINARY-STRING-FOR-PARSING */
Object convert_binary_string_for_parsing(string_1)
    Object string_1;
{
    Object uuid_qm, problem_report_qm;
    Object result;

    x_note_fn_call(195,4);
    result = convert_binary_string_representation_to_internal(string_1,Nil,
	    string_constant);
    MVS_2(result,uuid_qm,problem_report_qm);
    if (uuid_qm) {
	note_use_of_text_string_in_phrase(uuid_qm);
	return VALUES_1(uuid_qm);
    }
    else
	return VALUES_2(Bad_phrase,problem_report_qm);
}

/* MAKE-PHRASE-ITEM-DENOTATION-FROM-PARSE */
Object make_phrase_item_denotation_from_parse(parse)
    Object parse;
{
    x_note_fn_call(195,5);
    return phrase_cons(parse,Phrase_item_denotation_marker);
}

/* FIX-UP-ATTRIBUTE-TYPE-AND-MODIFICATIONS-PHRASE */
Object fix_up_attribute_type_and_modifications_phrase(phrase)
    Object phrase;
{
    Object third_new_value;

    x_note_fn_call(195,6);
    if (LISTP(phrase) && THIRD(phrase)) {
	third_new_value = remove_noise_at_head_of_list_phrase(THIRD(phrase));
	M_THIRD(phrase) = third_new_value;
    }
    return VALUES_1(phrase);
}

/* ATTRIBUTE-DEFINITION-TYPE-SPECIFICATION */
Object attribute_definition_type_specification(attribute_definition_type)
    Object attribute_definition_type;
{
    x_note_fn_call(195,7);
    if (CONSP(attribute_definition_type) && 
	    EQ(CAR(attribute_definition_type),Type_and_modifications_tag))
	return VALUES_1(SECOND(attribute_definition_type));
    else
	return VALUES_1(attribute_definition_type);
}

/* ATTRIBUTE-DEFINITION-TYPE-MODIFICATIONS */
Object attribute_definition_type_modifications(attribute_definition_type)
    Object attribute_definition_type;
{
    x_note_fn_call(195,8);
    if (CONSP(attribute_definition_type) && 
	    EQ(CAR(attribute_definition_type),Type_and_modifications_tag))
	return VALUES_1(THIRD(attribute_definition_type));
    else
	return VALUES_1(Nil);
}

/* COERCE-QUANTITY-INTERVAL-TO-FLOAT-INTERVAL */
Object coerce_quantity_interval_to_float_interval(quantity_interval)
    Object quantity_interval;
{
    Object temp;

    x_note_fn_call(195,9);
    temp = coerce_phrase_number_to_float(CAR(quantity_interval));
    return phrase_cons(temp,CDR(quantity_interval));
}

static Object Qab_gensym;          /* gensym */

static Object float_constant;      /* 0.0 */

/* COERCE-PHRASE-NUMBER-TO-FLOAT */
Object coerce_phrase_number_to_float(phrase_number)
    Object phrase_number;
{
    Object amf_available_array_cons_qm, amf_array, temp, svref_new_value;
    Object amf_result, incff_1_arg, new_float, temp_1;
    double aref_new_value;

    x_note_fn_call(195,10);
    if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == (SI_Long)1L)
	return VALUES_1(phrase_number);
    else {
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp = Vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp;
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	if (INLINE_DOUBLE_FLOAT_VECTOR_P(phrase_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == (SI_Long)1L)
	    temp_1 = DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(phrase_number,
		    (SI_Long)0L));
	else if (INLINE_LONG_VECTOR_P(phrase_number) != (SI_Long)0L && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(phrase_number)) == (SI_Long)1L)
	    temp_1 = aref1(phrase_number,FIX((SI_Long)0L));
	else
	    temp_1 = phrase_number;
	temp_1 = lfloat(temp_1,float_constant);
	aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
	return note_use_of_managed_float_in_phrase(new_float);
    }
}

static Object float_constant_1;    /* 1.0 */

/* TRANSFORM-DATE-PHRASE-AND-TIME-OF-DAY-INTO-G2-TIME-STAMP */
Object transform_date_phrase_and_time_of_day_into_g2_time_stamp(date_and_time_of_day_as_seconds_since_midnight)
    Object date_and_time_of_day_as_seconds_since_midnight;
{
    Object universal_date, time_of_day_as_seconds_since_midnight, day, month;
    Object year, seconds, minutes, hours, temp, second_1, minute, hour;
    double g2_time_at_start_float_value, unix_time, arg, arg_1;
    double gensymed_symbol, gensymed_symbol_1, temp_1;
    XDeclare_area(2);
    XDeclare_frontier(2);
    Object result;

    x_note_fn_call(195,11);
    if (PUSH_LOCAL_ALLOCATION(Local_area,1,1)) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    universal_date = 
		    FIRST(date_and_time_of_day_as_seconds_since_midnight);
	    time_of_day_as_seconds_since_midnight = 
		    SECOND(date_and_time_of_day_as_seconds_since_midnight);
	    g2_time_at_start_float_value = 
		    DFLOAT_ISAREF_1(G2_time_at_start,(SI_Long)0L);
	    result = decode_universal_date(universal_date);
	    MVS_3(result,day,month,year);
	    if (FIXNUMP(time_of_day_as_seconds_since_midnight))
		result = decode_normalized_time_of_day(time_of_day_as_seconds_since_midnight);
	    else
		result = decode_normalized_time_of_day_with_subseconds(time_of_day_as_seconds_since_midnight);
	    MVS_3(result,seconds,minutes,hours);
	    if (FIXNUMP(seconds)) {
		unix_time = g2ext_get_encoded_unix_time(IFIX(seconds),
			IFIX(minutes),IFIX(hours),IFIX(day),IFIX(month),
			IFIX(year));
		arg = unix_time;
		arg_1 = -1.0;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    temp = encode_unix_time_after_failure(seconds,minutes,
			    hours,day,month,year);
		    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
		}
		else
		    gensymed_symbol = unix_time;
		gensymed_symbol_1 = (double)((SI_Long)60L * 
			IFIX(Global_daylight_saving_time_adjustment));
		gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
		gensymed_symbol_1 = g2_time_at_start_float_value;
		result = VALUES_1(LONG_TO_FIXNUM(inline_floor_1(gensymed_symbol 
			- gensymed_symbol_1)));
	    }
	    else {
		temp = lfloat(rem(seconds,FIX((SI_Long)1L)),float_constant_1);
		temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
		second_1 = lfloor(seconds,_);
		minute = minutes;
		hour = hours;
		unix_time = g2ext_get_encoded_unix_time(IFIX(second_1),
			IFIX(minute),IFIX(hour),IFIX(day),IFIX(month),
			IFIX(year));
		arg = unix_time;
		arg_1 = -1.0;
		if (arg == arg_1 &&  !inline_nanp_for_comparison(arg) &&  
			!inline_nanp_for_comparison(arg_1)) {
		    temp = encode_unix_time_after_failure(second_1,minute,
			    hour,day,month,year);
		    gensymed_symbol = DOUBLE_FLOAT_TO_DOUBLE(temp);
		}
		else
		    gensymed_symbol = unix_time;
		gensymed_symbol_1 = (double)((SI_Long)60L * 
			IFIX(Global_daylight_saving_time_adjustment));
		result = VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp_1 + 
			(gensymed_symbol - gensymed_symbol_1) - 
			g2_time_at_start_float_value));
	    }
	}
	POP_LOCAL_ALLOCATION(0,0);
    }
    POP_LOCAL_ALLOCATION(1,1);
    return result;
}

static Object Qformat_override;    /* format-override */

static Object Qddd_dot_dddd_format;  /* ddd.dddd-format */

static Object string_constant_1;   /* "bad attribute format" */

/* DECODE-DDD.DDDD-FORMAT-IN-FORMAT-OVERRIDE */
Object decode_ddd_dot_dddd_format_in_format_override(phrase)
    Object phrase;
{
    Object left, right, temp, temp_2;
    char temp_1;
    Object result;

    x_note_fn_call(195,12);
    left = Nil;
    right = Nil;
    if (LISTP(phrase) && CDR(phrase) && SECOND(phrase)) {
	temp = SECOND(phrase);
	temp_1 = SYMBOLP(temp);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	result = decode_format(SECOND(phrase));
	MVS_2(result,left,right);
	temp_1 = TRUEP(left);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1)
	return phrase_list_3(Qformat_override,Qddd_dot_dddd_format,
		phrase_cons(left,right));
    else {
	temp_2 = Bad_phrase;
	temp = tformat_text_string(1,string_constant_1);
	return VALUES_2(temp_2,temp);
    }
}

static Object string_constant_2;   /* ", " */

/* WRITE-ATTRIBUTE-TYPE-MODIFICATIONS */
Object write_attribute_type_modifications(modifications)
    Object modifications;
{
    Object mod_1, more_qm, ab_loop_list_;

    x_note_fn_call(195,13);
    mod_1 = Nil;
    more_qm = Nil;
    ab_loop_list_ = modifications;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    mod_1 = CAR(ab_loop_list_);
    more_qm = CDR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    write_one_attribute_type_modification(mod_1);
    if (more_qm)
	tformat(1,string_constant_2);
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qinterval;           /* interval */

static Object string_constant_3;   /* " an" */

static Object Qtime_stamp;         /* time-stamp */

static Object string_constant_4;   /* " a" */

static Object string_constant_5;   /* "" */

static Object string_constant_6;   /* "formatted as~a " */

static Object Qformat_qm;          /* format? */

static Object Qseconds;            /* seconds */

static Object Qslot_value_writer;  /* slot-value-writer */

static Object string_constant_7;   /* "[deleted attribute]" */

/* WRITE-ONE-ATTRIBUTE-TYPE-MODIFICATION */
Object write_one_attribute_type_modification(modification)
    Object modification;
{
    Object temp, grammar_category_symbol, slot_value, frame_qm;
    Object slot_value_writer_qm, write_symbols_in_lower_case_qm;
    Object write_symbols_parsably_qm;
    Declare_special(2);
    Object result;

    x_note_fn_call(195,14);
    temp = FIRST(modification);
    if (EQ(temp,Qformat_override)) {
	temp = SECOND(modification);
	if (EQ(temp,Qinterval))
	    temp = string_constant_3;
	else if (EQ(temp,Qtime_stamp))
	    temp = string_constant_4;
	else
	    temp = string_constant_5;
	tformat(2,string_constant_6,temp);
	grammar_category_symbol = Qformat_qm;
	slot_value = EQ(SECOND(modification),Qddd_dot_dddd_format) ? 
		THIRD(modification) : EQ(SECOND(modification),Qinterval) ? 
		Qseconds : SECOND(modification);
	frame_qm = Nil;
	slot_value_writer_qm = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(grammar_category_symbol),
		Qslot_value_writer);
	if (slot_value_writer_qm) {
	    write_symbols_in_lower_case_qm = T;
	    write_symbols_parsably_qm = T;
	    PUSH_SPECIAL(Write_symbols_parsably_qm,write_symbols_parsably_qm,
		    1);
	      PUSH_SPECIAL(Write_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		      0);
		result = VALUES_1(inline_funcall_2(slot_value_writer_qm,
			slot_value,frame_qm));
	      POP_SPECIAL();
	    POP_SPECIAL();
	    return result;
	}
	else
	    return twrite(string_constant_7);
    }
    else
	return VALUES_1(Nil);
}

/* COMPILE-ELEMENT-TYPE-FOR-SLOT */
Object compile_element_type_for_slot varargs_1(int, n)
{
    Object parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(195,15);
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
    if (System_is_running || System_has_paused)
	return no_change_while_running();
    else
	return VALUES_1(parse_result);
}

static Object string_constant_8;   /* "none" */

static Object Qitem_or_datum;      /* item-or-datum */

static Object array_constant;      /* # */

static Object Qdatum;              /* datum */

static Object array_constant_1;    /* # */

static Object array_constant_2;    /* # */

static Object string_constant_9;   /* "~(~A~)" */

/* WRITE-ELEMENT-TYPE-FROM-SLOT */
Object write_element_type_from_slot(value,gensymed_symbol)
    Object value, gensymed_symbol;
{
    x_note_fn_call(195,16);
    if ( !TRUEP(value))
	return twrite(string_constant_8);
    else if (EQ(value,Qitem_or_datum))
	return twrite_beginning_of_wide_string(array_constant,
		FIX((SI_Long)13L));
    else if (EQ(value,Qdatum))
	return twrite_beginning_of_wide_string(array_constant_1,
		FIX((SI_Long)5L));
    else if (EQ(value,Qnumber))
	return twrite_beginning_of_wide_string(array_constant_2,
		FIX((SI_Long)8L));
    else
	return tformat(2,string_constant_9,value);
}

void grammar1a_INIT()
{
    Object Qwrite_element_type_from_slot, Qelement_type, AB_package;
    Object list_constant, Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_element_type_for_slot;
    Object string_constant_102, Qdecode_ddd_dot_dddd_format_in_format_override;
    Object Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp;
    Object Qcoerce_phrase_number_to_float;
    Object Qcoerce_quantity_interval_to_float_interval, string_constant_101;
    Object string_constant_100, string_constant_99, string_constant_98;
    Object string_constant_97, string_constant_96, Qcm;
    Object Qattribute_type_modification, Qattribute_type_modification_list;
    Object Qfix_up_attribute_type_and_modifications_phrase, string_constant_95;
    Object string_constant_94, string_constant_93, string_constant_92;
    Object string_constant_91, string_constant_90, string_constant_89;
    Object Qcategory_is_not_g2_element_datum_type;
    Object Qregistered_directory_of_names_p, Qlocal_name, Qrelation_name;
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
    Object string_constant_58, string_constant_57, string_constant_56;
    Object string_constant_55, string_constant_54, string_constant_53;
    Object string_constant_52, string_constant_51, string_constant_50;
    Object string_constant_49, string_constant_48, string_constant_47;
    Object string_constant_46, string_constant_45, string_constant_44;
    Object string_constant_43, string_constant_42, string_constant_41;
    Object string_constant_40, string_constant_39, string_constant_38;
    Object string_constant_37, string_constant_36, string_constant_35;
    Object string_constant_34, string_constant_33, string_constant_32;
    Object string_constant_31, Qend;
    Object Qtranslate_role_local_name_and_preposition;
    Object Qtranslate_role_and_preposition, string_constant_30;
    Object Qstructure_component_allowing_binary_data;
    Object Qstructure_component_allowing_binary_data_list, string_constant_29;
    Object Qmake_phrase_structure_from_structure_component_list;
    Object Qmake_empty_phrase_structure_kludge, string_constant_28;
    Object Qsequence_component_allowing_binary_data;
    Object Qsequence_component_allowing_binary_data_list, string_constant_27;
    Object Qmake_phrase_sequence_from_sequence_component_list;
    Object Qmake_empty_phrase_sequence_kludge, string_constant_26;
    Object Qstructure_component_allowing_items;
    Object Qstructure_component_allowing_items_list, string_constant_25;
    Object string_constant_24, Qsequence_component_allowing_items;
    Object Qsequence_component_allowing_items_list, string_constant_23;
    Object Qmake_phrase_item_denotation_from_parse, string_constant_22;
    Object Qthe_item_having_uuid, string_constant_21, string_constant_20;
    Object Qreject_truth_value_as_unit_of_measure_constant, string_constant_19;
    Object Qconvert_binary_string_for_parsing, string_constant_18;
    Object string_constant_17, string_constant_16, string_constant_15;
    Object Qstructure_component, Qstructure_component_list, string_constant_14;
    Object string_constant_13, Qsequence_component, Qsequence_component_list;
    Object string_constant_12, string_constant_11, string_constant_10;

    x_note_fn_call(195,17);
    SET_PACKAGE("AB");
    string_constant_10 = STATIC_STRING("1l1m83-mwy83Zuy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_10));
    string_constant_11 = STATIC_STRING("1l1m83-pby83b=y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_11));
    AB_package = STATIC_PACKAGE("AB");
    Qmake_empty_phrase_sequence_kludge = 
	    STATIC_SYMBOL("MAKE-EMPTY-PHRASE-SEQUENCE-KLUDGE",AB_package);
    Qmake_phrase_sequence_from_sequence_component_list = 
	    STATIC_SYMBOL("MAKE-PHRASE-SEQUENCE-FROM-SEQUENCE-COMPONENT-LIST",
	    AB_package);
    string_constant_12 = 
	    STATIC_STRING("1m1o830Sy1n1m9k830Sy1m9k83-9y1m9k83-Ay1ll9l1p830Sy1o1m9k830Sy1m9k83-9y83-n0y1m9k83-Ayn9m9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_empty_phrase_sequence_kludge);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qmake_phrase_sequence_from_sequence_component_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_12));
    SET_SYMBOL_FUNCTION(Qmake_phrase_sequence_from_sequence_component_list,
	    STATIC_FUNCTION(make_phrase_sequence_from_sequence_component_list,
	    NIL,FALSE,1,1));
    Qsequence_component_list = STATIC_SYMBOL("SEQUENCE-COMPONENT-LIST",
	    AB_package);
    Qsequence_component = STATIC_SYMBOL("SEQUENCE-COMPONENT",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(3,Qsequence_component_list,
	    Qsequence_component,Qcm);
    string_constant_13 = STATIC_STRING("1l1m83-mxy83f6y");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_13));
    Qmake_empty_phrase_structure_kludge = 
	    STATIC_SYMBOL("MAKE-EMPTY-PHRASE-STRUCTURE-KLUDGE",AB_package);
    Qmake_phrase_structure_from_structure_component_list = 
	    STATIC_SYMBOL("MAKE-PHRASE-STRUCTURE-FROM-STRUCTURE-COMPONENT-LIST",
	    AB_package);
    string_constant_14 = 
	    STATIC_STRING("1m1o8s1n1m9k8s1m9k83-9y1m9k83-Ay1ll9l1p8s1o1m9k8s1m9k83-9y83-phy1m9k83-Ayn9m9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_empty_phrase_structure_kludge);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qmake_phrase_structure_from_structure_component_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_14));
    SET_SYMBOL_FUNCTION(Qmake_empty_phrase_sequence_kludge,
	    STATIC_FUNCTION(make_empty_phrase_sequence_kludge,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmake_empty_phrase_structure_kludge,
	    STATIC_FUNCTION(make_empty_phrase_structure_kludge,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qmake_phrase_structure_from_structure_component_list,
	    STATIC_FUNCTION(make_phrase_structure_from_structure_component_list,
	    NIL,FALSE,1,1));
    Qstructure_component_list = STATIC_SYMBOL("STRUCTURE-COMPONENT-LIST",
	    AB_package);
    Qstructure_component = STATIC_SYMBOL("STRUCTURE-COMPONENT",AB_package);
    add_grammar_rules_for_list(3,Qstructure_component_list,
	    Qstructure_component,Qcm);
    string_constant_15 = STATIC_STRING("1l1n83-pcy1n83-6y1m9k83-Py83f6y2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_15));
    string_constant_16 = 
	    STATIC_STRING("1s1m83Koy1m9k83Zy1m83Koy83-Hy1m83Koy83-Uy1m83Koy834my1m83Koy83Zuy1m83Koy83b=y1m83Koy83-0*y1n83Koy1n1m9k9l1m9k83-2y830Tyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_16));
    string_constant_17 = 
	    STATIC_STRING("1s1m83hCy1m9k83Zy1m83hCy83-Hy1m83hCy83-Uy1m83hCy83qby1m83hCy834my1m83hCy83-Cey1m83hCy83-Dvy1n83hCy1n1m9k9l1m9k83-2y830Tyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_17));
    Qconvert_binary_string_for_parsing = 
	    STATIC_SYMBOL("CONVERT-BINARY-STRING-FOR-PARSING",AB_package);
    string_constant_18 = 
	    STATIC_STRING("1l1o83qby1o1m9k9l1m9k83-Kmy1m9k9m83-Uyo9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qstring);
    push_optimized_constant(Qconvert_binary_string_for_parsing);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_18));
    string_constant = STATIC_STRING("binary");
    SET_SYMBOL_FUNCTION(Qconvert_binary_string_for_parsing,
	    STATIC_FUNCTION(convert_binary_string_for_parsing,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qconvert_binary_string_for_parsing);
    Qreject_truth_value_as_unit_of_measure_constant = 
	    STATIC_SYMBOL("REJECT-TRUTH-VALUE-AS-UNIT-OF-MEASURE-CONSTANT",
	    AB_package);
    string_constant_19 = 
	    STATIC_STRING("1n1o83-OGy83dUyl9k1m83-OGy831Ny1m83-OGy83Koy");
    clear_optimized_constants();
    push_optimized_constant(Qreject_truth_value_as_unit_of_measure_constant);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_19));
    string_constant_20 = 
	    STATIC_STRING("1t1o83t3y83dUyl9k1m83t3y831Ny1m83t3y1m9l83Zy1m83t3y83-Hy1m83t3y83-Uy1m83t3y834my1m83t3y83Zuy1m83t3y83b=y1n83t3y1n1m9l9m1m9l83-2y");
    string_constant_21 = STATIC_STRING("830Tyn");
    clear_optimized_constants();
    push_optimized_constant(Qreject_truth_value_as_unit_of_measure_constant);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_20,
	    string_constant_21)));
    Qmake_phrase_item_denotation_from_parse = 
	    STATIC_SYMBOL("MAKE-PHRASE-ITEM-DENOTATION-FROM-PARSE",AB_package);
    Qthe_item_having_uuid = STATIC_SYMBOL("THE-ITEM-HAVING-UUID",AB_package);
    string_constant_22 = 
	    STATIC_STRING("1n1o83-0*y834Hyl9k1o83-0*y1o1m9l9m830Ty1m9l83-Ty83-0*y1nlmo9k1o83-0*y1p1m9l9m83-Gy1m9l83-*6y1m9l83AQy83-Uy1n9nmp9k");
    clear_optimized_constants();
    push_optimized_constant(Qmake_phrase_item_denotation_from_parse);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qthe_item_having_uuid);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_22));
    SET_SYMBOL_FUNCTION(Qmake_phrase_item_denotation_from_parse,
	    STATIC_FUNCTION(make_phrase_item_denotation_from_parse,NIL,
	    FALSE,1,1));
    string_constant_23 = 
	    STATIC_STRING("1m1o83Zuy1n1m9k830Sy1m9k83-9y1m9k83-Ay1ll9l1p83Zuy1o1m9k830Sy1m9k83-9y83-n=y1m9k83-Ayn9m9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_empty_phrase_sequence_kludge);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qmake_phrase_sequence_from_sequence_component_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_23));
    Qsequence_component_allowing_items_list = 
	    STATIC_SYMBOL("SEQUENCE-COMPONENT-ALLOWING-ITEMS-LIST",AB_package);
    Qsequence_component_allowing_items = 
	    STATIC_SYMBOL("SEQUENCE-COMPONENT-ALLOWING-ITEMS",AB_package);
    add_grammar_rules_for_list(3,Qsequence_component_allowing_items_list,
	    Qsequence_component_allowing_items,Qcm);
    string_constant_24 = STATIC_STRING("1l1m83-n*y83Koy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_24));
    string_constant_25 = 
	    STATIC_STRING("1m1o83b=y1n1m9k8s1m9k83-9y1m9k83-Ay1ll9l1p83b=y1o1m9k8s1m9k83-9y83-pgy1m9k83-Ayn9m9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_empty_phrase_structure_kludge);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qmake_phrase_structure_from_structure_component_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_25));
    Qstructure_component_allowing_items_list = 
	    STATIC_SYMBOL("STRUCTURE-COMPONENT-ALLOWING-ITEMS-LIST",
	    AB_package);
    Qstructure_component_allowing_items = 
	    STATIC_SYMBOL("STRUCTURE-COMPONENT-ALLOWING-ITEMS",AB_package);
    add_grammar_rules_for_list(3,Qstructure_component_allowing_items_list,
	    Qstructure_component_allowing_items,Qcm);
    string_constant_26 = STATIC_STRING("1l1n83-pfy1n83-6y1m9k83-Py83Koy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_26));
    string_constant_27 = 
	    STATIC_STRING("1m1o83-Cey1n1m9k830Sy1m9k83-9y1m9k83-Ay1ll9l1p83-Cey1o1m9k830Sy1m9k83-9y83-n-y1m9k83-Ayn9m9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_empty_phrase_sequence_kludge);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qmake_phrase_sequence_from_sequence_component_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_27));
    Qsequence_component_allowing_binary_data_list = 
	    STATIC_SYMBOL("SEQUENCE-COMPONENT-ALLOWING-BINARY-DATA-LIST",
	    AB_package);
    Qsequence_component_allowing_binary_data = 
	    STATIC_SYMBOL("SEQUENCE-COMPONENT-ALLOWING-BINARY-DATA",
	    AB_package);
    add_grammar_rules_for_list(3,
	    Qsequence_component_allowing_binary_data_list,
	    Qsequence_component_allowing_binary_data,Qcm);
    string_constant_28 = STATIC_STRING("1l1m83-n+y83hCy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_28));
    string_constant_29 = 
	    STATIC_STRING("1m1o83-Dvy1n1m9k8s1m9k83-9y1m9k83-Ay1ll9l1p83-Dvy1o1m9k8s1m9k83-9y83-pey1m9k83-Ayn9m9n");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmake_empty_phrase_structure_kludge);
    push_optimized_constant(Qcdr);
    push_optimized_constant(Qmake_phrase_structure_from_structure_component_list);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_29));
    Qstructure_component_allowing_binary_data_list = 
	    STATIC_SYMBOL("STRUCTURE-COMPONENT-ALLOWING-BINARY-DATA-LIST",
	    AB_package);
    Qstructure_component_allowing_binary_data = 
	    STATIC_SYMBOL("STRUCTURE-COMPONENT-ALLOWING-BINARY-DATA",
	    AB_package);
    add_grammar_rules_for_list(3,
	    Qstructure_component_allowing_binary_data_list,
	    Qstructure_component_allowing_binary_data,Qcm);
    string_constant_30 = STATIC_STRING("1l1n83-pdy1n83-6y1m9k83-Py83hCy2lln");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_30));
    Qtranslate_role_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-AND-PREPOSITION",AB_package);
    Qtranslate_role_local_name_and_preposition = 
	    STATIC_SYMBOL("TRANSLATE-ROLE-LOCAL-NAME-AND-PREPOSITION",
	    AB_package);
    Qend = STATIC_SYMBOL("END",AB_package);
    string_constant_31 = 
	    STATIC_STRING("13*Iy1o83Hwy1m83-Gy83Y6y1mlm9k1o83-Fby1m83-Gy83-Fjy1mlm9k1o83nAy1m83-Gy83-oOy1mlm9k1o83Hwy1n83-Gy83*Zy83Y6y1nlmn9l1o83-Fby1n83-G");
    string_constant_32 = 
	    STATIC_STRING("y83*Zy83-Fjy1nlmn9l1o83nAy1n83-Gy83*Zy83-oOy1nlmn9l1n83Hwy1m1m9m83*ry1m9m83-Ty1n834Zy83*ry83=uy1n83-Fby1m1m9m83*ry1m9m83-Ty1n834");
    string_constant_33 = 
	    STATIC_STRING("Zy83*ry83=uy1n83nAy1m1m9m83*ry1m9m83-Ty1n834Zy83*ry83=uy1n83Hwy1n1m9m83*ry83*Zy1m9m83-Ty2l1n834Zy83*ry83=uym1n83-Fby1n1m9m83*ry8");
    string_constant_34 = 
	    STATIC_STRING("3*Zy1m9m83-Ty2l1n834Zy83*ry83=uym1n83nAy1n1m9m83*ry83*Zy1m9m83-Ty2l1n834Zy83*ry83=uym1n83Hwy1m1m9m83b9y1m9m83-Ty1n834Zy83b9y83=u");
    string_constant_35 = 
	    STATIC_STRING("y1n83-Fby1m1m9m83b9y1m9m83-Ty1n834Zy83b9y83=uy1n83nAy1m1m9m83b9y1m9m83-Ty1n834Zy83b9y83=uy1n83Hwy1n1m9m83b9y83*Zy1m9m83-Ty2l1n83");
    string_constant_36 = 
	    STATIC_STRING("4Zy83b9y83=uym1n83-Fby1n1m9m83b9y83*Zy1m9m83-Ty2l1n834Zy83b9y83=uym1n83nAy1n1m9m83b9y83*Zy1m9m83-Ty2l1n834Zy83b9y83=uym1n83Hwy1m");
    string_constant_37 = 
	    STATIC_STRING("83-Yy1m9m83*Xy1m838Eyl1n83-Fby1m83-Yy1m9m83*Xy1m838Eyl1n83nAy1m83-Yy1m9m83*Xy1m838Eyl1n83Hwy1n83-Yy83*Zy1m9m83*Xy2l1m838Eylm1n83");
    string_constant_38 = 
	    STATIC_STRING("-Fby1n83-Yy83*Zy1m9m83*Xy2l1m838Eylm1n83nAy1n83-Yy83*Zy1m9m83*Xy2l1m838Eylm1n83Hwy1m1m9m83=hy1m9m83-Ty1m834Zy83=hy1n83-Fby1m1m9m");
    string_constant_39 = 
	    STATIC_STRING("83=hy1m9m83-Ty1m834Zy83=hy1n83nAy1m1m9m83=hy1m9m83-Ty1m834Zy83=hy1n83Hwy1n1m9m83=hy83*Zy1m9m83-Ty2l1m834Zy83=hym1n83-Fby1n1m9m83");
    string_constant_40 = 
	    STATIC_STRING("=hy83*Zy1m9m83-Ty2l1m834Zy83=hym1n83nAy1n1m9m83=hy83*Zy1m9m83-Ty2l1m834Zy83=hym1n83Hwy1s1m9m83-2y1m9m8319y1m9m83*Iy83=Zy1m9m83AN");
    string_constant_41 = 
	    STATIC_STRING("y1m9m83-qy1m9m83=hy1m9m83-Ty1m83oOyl1n83-Fby1s1m9m83-2y1m9m8319y1m9m83*Iy83=Zy1m9m83ANy1m9m83-qy1m9m83=hy1m9m83-Ty1m83oOyl1n83nA");
    string_constant_42 = 
	    STATIC_STRING("y1s1m9m83-2y1m9m8319y1m9m83*Iy83=Zy1m9m83ANy1m9m83-qy1m9m83=hy1m9m83-Ty1m83oOyl1n83Hwy1t1m9m83-2y83*Zy1m9m8319y1m9m83*Iy83=Zy1m9");
    string_constant_43 = 
	    STATIC_STRING("m83ANy1m9m83-qy1m9m83=hy1m9m83-Ty2l1m83oOylm1n83-Fby1t1m9m83-2y83*Zy1m9m8319y1m9m83*Iy83=Zy1m9m83ANy1m9m83-qy1m9m83=hy1m9m83-Ty2");
    string_constant_44 = 
	    STATIC_STRING("l1m83oOylm1n83nAy1t1m9m83-2y83*Zy1m9m8319y1m9m83*Iy83=Zy1m9m83ANy1m9m83-qy1m9m83=hy1m9m83-Ty2l1m83oOylm1n83Hwy1r1m9m83-2y1m9m831");
    string_constant_45 = 
	    STATIC_STRING("9y1m9m83*Iy83=Zy1m9m83-qy1m9m83=hy1m9m83-Ty1m83fIyl1n83-Fby1r1m9m83-2y1m9m8319y1m9m83*Iy83=Zy1m9m83-qy1m9m83=hy1m9m83-Ty1m83fIyl");
    string_constant_46 = 
	    STATIC_STRING("1n83nAy1r1m9m83-2y1m9m8319y1m9m83*Iy83=Zy1m9m83-qy1m9m83=hy1m9m83-Ty1m83fIyl1n83Hwy1s1m9m83-2y83*Zy1m9m8319y1m9m83*Iy83=Zy1m9m83");
    string_constant_47 = 
	    STATIC_STRING("-qy1m9m83=hy1m9m83-Ty2l1m83fIylm1n83-Fby1s1m9m83-2y83*Zy1m9m8319y1m9m83*Iy83=Zy1m9m83-qy1m9m83=hy1m9m83-Ty2l1m83fIylm1n83nAy1s1m");
    string_constant_48 = 
	    STATIC_STRING("9m83-2y83*Zy1m9m8319y1m9m83*Iy83=Zy1m9m83-qy1m9m83=hy1m9m83-Ty2l1m83fIylm1n83Hwy1q1m9m83-2y1m9m8319y1m9m83*Iy1m9m83=ay1m9m83-=Xy");
    string_constant_49 = 
	    STATIC_STRING("1m9m83-Ty1m83-=Xyl1n83-Fby1q1m9m83-2y1m9m8319y1m9m83*Iy1m9m83=ay1m9m83-=Xy1m9m83-Ty1m83-=Xyl1n83nAy1q1m9m83-2y1m9m8319y1m9m83*Iy");
    string_constant_50 = 
	    STATIC_STRING("1m9m83=ay1m9m83-=Xy1m9m83-Ty1m83-=Xyl1n83Hwy1r1m9m83-2y83*Zy1m9m8319y1m9m83*Iy1m9m83=ay1m9m83-=Xy1m9m83-Ty2l1m83-=Xylm1n83-Fby1r");
    string_constant_51 = 
	    STATIC_STRING("1m9m83-2y83*Zy1m9m8319y1m9m83*Iy1m9m83=ay1m9m83-=Xy1m9m83-Ty2l1m83-=Xylm1n83nAy1r1m9m83-2y83*Zy1m9m8319y1m9m83*Iy1m9m83=ay1m9m83");
    string_constant_52 = 
	    STATIC_STRING("-=Xy1m9m83-Ty2l1m83-=Xylm1n83Hwy1q1m9m83-2y1m9m8319y1m9m83*Iy1m9m83=Yy1m9m83A2y1m9m83-Ty1m83A2yl1n83-Fby1q1m9m83-2y1m9m8319y1m9m");
    string_constant_53 = 
	    STATIC_STRING("83*Iy1m9m83=Yy1m9m83A2y1m9m83-Ty1m83A2yl1n83nAy1q1m9m83-2y1m9m8319y1m9m83*Iy1m9m83=Yy1m9m83A2y1m9m83-Ty1m83A2yl1n83Hwy1r1m9m83-2");
    string_constant_54 = 
	    STATIC_STRING("y83*Zy1m9m8319y1m9m83*Iy1m9m83=Yy1m9m83A2y1m9m83-Ty2l1m83A2ylm1n83-Fby1r1m9m83-2y83*Zy1m9m8319y1m9m83*Iy1m9m83=Yy1m9m83A2y1m9m83");
    string_constant_55 = 
	    STATIC_STRING("-Ty2l1m83A2ylm1n83nAy1r1m9m83-2y83*Zy1m9m8319y1m9m83*Iy1m9m83=Yy1m9m83A2y1m9m83-Ty2l1m83A2ylm1n83Y6y1m1m9m83Igy1m9m83=3y83gGy1n8");
    string_constant_56 = 
	    STATIC_STRING("3-Fjy1m1m9m83Igy1m9m83=3y83gGy1n83-oOy1m1m9m83Igy1m9m83=3y83gGy1n83Y6y1p1m9m83Igy1m9m83=Gy1m9m9n839jy1m9m83-Ty1m83pvyo1n83-Fjy1p");
    string_constant_57 = 
	    STATIC_STRING("1m9m83Igy1m9m83=Gy1m9m9n839jy1m9m83-Ty1m83pvyo1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m9n839jy1m9m83-Ty1m83pvyo1n83Y6y1p1m9m83Igy1m9m83=G");
    string_constant_58 = 
	    STATIC_STRING("y1m9m9n1m9m83dy1m9m83=3y83fDy1n83-Fjy1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83dy1m9m83=3y83fDy1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83dy1");
    string_constant_59 = 
	    STATIC_STRING("m9m83=3y83fDy1n83Y6y1p1m9m83Igy1m9m83=Gy1m9m83=ay1m9m83dy1m9m83=3y83fDy1n83-Fjy1p1m9m83Igy1m9m83=Gy1m9m83=ay1m9m83dy1m9m83=3y83f");
    string_constant_60 = 
	    STATIC_STRING("Dy1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m83=ay1m9m83dy1m9m83=3y83fDy1n83Y6y1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83dy1m9m83-Ty83fDy1n83-Fjy1p1m");
    string_constant_61 = 
	    STATIC_STRING("9m83Igy1m9m83=Gy1m9m9n1m9m83dy1m9m83-Ty83fDy1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83dy1m9m83-Ty83fDy1n83Y6y1p1m9m83Igy1m9m83=Gy1");
    string_constant_62 = 
	    STATIC_STRING("m9m83=ay1m9m83dy1m9m83-Ty83fDy1n83-Fjy1p1m9m83Igy1m9m83=Gy1m9m83=ay1m9m83dy1m9m83-Ty83fDy1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m83=ay1m");
    string_constant_63 = 
	    STATIC_STRING("9m83dy1m9m83-Ty83fDy1n83Y6y1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83py1m9m83-Ty83fEy1n83-Fjy1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83py1m9m83-Ty83");
    string_constant_64 = 
	    STATIC_STRING("fEy1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m9n1m9m83py1m9m83-Ty83fEy1n83Y6y1p1m9m83Igy1m9m83=Gy1m9m83=ay1m9m83py1m9m83-Ty83fEy1n83-Fjy1p1");
    string_constant_65 = 
	    STATIC_STRING("m9m83Igy1m9m83=Gy1m9m83=ay1m9m83py1m9m83-Ty83fEy1n83-oOy1p1m9m83Igy1m9m83=Gy1m9m83=ay1m9m83py1m9m83-Ty83fEy1n83Y6y1p1m9m83=Gy1m9");
    string_constant_66 = 
	    STATIC_STRING("m9n1m9m83dy1m9m9o1m9m83-Ty83pty1n83-Fjy1p1m9m83=Gy1m9m9n1m9m83dy1m9m9o1m9m83-Ty83pty1n83-oOy1p1m9m83=Gy1m9m9n1m9m83dy1m9m9o1m9m8");
    string_constant_67 = 
	    STATIC_STRING("3-Ty83pty1n83Y6y1p1m9m83=Gy1m9m83=ay1m9m83dy1m9m9o1m9m83-Ty83pty1n83-Fjy1p1m9m83=Gy1m9m83=ay1m9m83dy1m9m9o1m9m83-Ty83pty1n83-oOy");
    string_constant_68 = 
	    STATIC_STRING("1p1m9m83=Gy1m9m83=ay1m9m83dy1m9m9o1m9m83-Ty83pty1n83Y6y1p1m9m83=Gy1m9m9n1m9m83py1m9m9o1m9m83-Ty83puy1n83-Fjy1p1m9m83=Gy1m9m9n1m9");
    string_constant_69 = 
	    STATIC_STRING("m83py1m9m9o1m9m83-Ty83puy1n83-oOy1p1m9m83=Gy1m9m9n1m9m83py1m9m9o1m9m83-Ty83puy1n83Y6y1p1m9m83=Gy1m9m83=ay1m9m83py1m9m9o1m9m83-Ty");
    string_constant_70 = 
	    STATIC_STRING("83puy1n83-Fjy1p1m9m83=Gy1m9m83=ay1m9m83py1m9m9o1m9m83-Ty83puy1n83-oOy1p1m9m83=Gy1m9m83=ay1m9m83py1m9m9o1m9m83-Ty83puy1n83Y6y1o1m");
    string_constant_71 = 
	    STATIC_STRING("9m83=Gy1m9m83h0y1m9m9o1m9m83-Ty83psy1n83-Fjy1o1m9m83=Gy1m9m83h0y1m9m9o1m9m83-Ty83psy1n83-oOy1o1m9m83=Gy1m9m83h0y1m9m9o1m9m83-Ty8");
    string_constant_72 = 
	    STATIC_STRING("3psy1n83Y6y1o1m9m83=Gy1m9m83=ay1m9m9o1m9m83-Ty83psy1n83-Fjy1o1m9m83=Gy1m9m83=ay1m9m9o1m9m83-Ty83psy1n83-oOy1o1m9m83=Gy1m9m83=ay1");
    string_constant_73 = 
	    STATIC_STRING("m9m9o1m9m83-Ty83psy1n83Y6y1m1m9m83-7Iy1m9m83=3y83-7Iy1n83-Fjy1m1m9m83-7Iy1m9m83=3y83-7Iy1n83-oOy1m1m9m83-7Iy1m9m83=3y83-7Iy1n83Y");
    string_constant_74 = 
	    STATIC_STRING("6y1m1m9m83-pxy1m9m83=3y83-q-y1n83-Fjy1m1m9m83-pxy1m9m83=3y83-q-y1n83-oOy1m1m9m83-pxy1m9m83=3y83-q-y1n83Y6y1p1m9m8319y1m9m83*Iy1m");
    string_constant_75 = 
	    STATIC_STRING("9m83=ay1m9m83-qy1m9m83-Ty83-K9y1n83-Fjy1p1m9m8319y1m9m83*Iy1m9m83=ay1m9m83-qy1m9m83-Ty83-K9y1n83-oOy1p1m9m8319y1m9m83*Iy1m9m83=a");
    string_constant_76 = 
	    STATIC_STRING("y1m9m83-qy1m9m83-Ty83-K9y1m83Y6y1m9m83-Fvy1m83-Fjy1m9m83-Fvy1m83-oOy1m9m83-Fvy1n83Y6y1n1m9m8319y1m9m83*Iy834Uy1m83-BYyn1n83-Fjy1");
    string_constant_77 = 
	    STATIC_STRING("n1m9m8319y1m9m83*Iy834Uy1m83-BYyn1n83-oOy1n1m9m8319y1m9m83*Iy834Uy1m83-BYyn1n83Y6y1m1m9m8319y1m9m83gMy83kjy1n83-Fjy1m1m9m8319y1m");
    string_constant_78 = 
	    STATIC_STRING("9m83gMy83kjy1n83-oOy1m1m9m8319y1m9m83gMy83kjy1m83*Zy83-6y1m834Uy83-6y1n836ay1n1m9m83-9y83-TBy1m9m83-Ay1lm1n83oHy1n1m9m83-9y83-tL");
    string_constant_79 = 
	    STATIC_STRING("y1m9m83-Ay1lm1n83-Cvy1n1m9m83-9y83-oHy1m9m83-Ay1lm1n836ay1o1m9m83-9y83-TBy1m9m83vy83-Jqy2lmo1n83oHy1o1m9m83-9y83-tLy1m9m83vy83-t");
    string_constant_80 = 
	    STATIC_STRING("Iy2lmo1n83-Cvy1o1m9m83-9y83-oHy1m9m83vy83-oCy2lmo1n83-Jqy1m83-TBy1m9m83-Ay1ll1n83-tIy1m83-tLy1m9m83-Ay1ll1n83-oCy1m83-oHy1m9m83-");
    string_constant_81 = 
	    STATIC_STRING("Ay1ll1n83-Jqy1n83-TBy1m9m83vy83-Jqy2lln1n83-tIy1n83-tLy1m9m83vy83-tIy2lln1n83-oCy1n83-oHy1m9m83vy83-oCy2lln1n83-Dwy1p1m9m83-9y83");
    string_constant_82 = 
	    STATIC_STRING("-2y1m9m83-Py83-TBy1m9m83-Ay1m1m9mmo1n83-Dwy1p1m9m83-9y83-2y1m9m83-Py83-tLy1m9m83-Ay1m1m9mmo1n83-Dwy1p1m9m83-9y83-2y1m9m83-Py83-o");
    string_constant_83 = 
	    STATIC_STRING("Hy1m9m83-Ay1m1m9mmo1n83-Dwy1q1m9m83-9y83-2y1m9m83-Py83-TBy1m9m83vy83-pay2m1m9mmoq1n83-Dwy1q1m9m83-9y83-2y1m9m83-Py83-tLy1m9m83vy");
    string_constant_84 = 
	    STATIC_STRING("83-tUy2m1m9mmoq1n83-Dwy1q1m9m83-9y83-2y1m9m83-Py83-oHy1m9m83vy83-oSy2m1m9mmoq1n83-pay1o83-2y1m9m83-Py83-TBy1m9m83-Ay1m1m9mln1n83");
    string_constant_85 = 
	    STATIC_STRING("-tUy1o83-2y1m9m83-Py83-tLy1m9m83-Ay1m1m9mln1n83-oSy1o83-2y1m9m83-Py83-oHy1m9m83-Ay1m1m9mln1n83-pay1p83-2y1m9m83-Py83-TBy1m9m83vy");
    string_constant_86 = 
	    STATIC_STRING("83-pay2m1m9mlnp1n83-tUy1p83-2y1m9m83-Py83-tLy1m9m83vy83-tUy2m1m9mlnp1n83-oSy1p83-2y1m9m83-Py83-oHy1m9m83vy83-oSy2m1m9mlnp1m83-TB");
    string_constant_87 = 
	    STATIC_STRING("y83=py1m83-tLy83=xy1m83-oHy836Ey1m83-TBy83UTy1m83-tLy831Py1m83-oHy83aFy1n83UAy1m9m9p83-Tuy1n83UAy1m9m9q83-bLy1n83UAy1m9m9r83-mYy");
    string_constant_88 = 
	    STATIC_STRING("1n83UAy1n1m9m837Fy1m9m83=3y1m9m9q83-fly");
    clear_optimized_constants();
    push_optimized_constant(Qtranslate_role_and_preposition);
    push_optimized_constant(Qtranslate_role_local_name_and_preposition);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qend);
    push_optimized_constant(Qfirst);
    push_optimized_constant(Qlast);
    push_optimized_constant(Qsecond);
    add_grammar_rules_function(regenerate_optimized_constant(nconc2(list(50,
	    string_constant_31,string_constant_32,string_constant_33,
	    string_constant_34,string_constant_35,string_constant_36,
	    string_constant_37,string_constant_38,string_constant_39,
	    string_constant_40,string_constant_41,string_constant_42,
	    string_constant_43,string_constant_44,string_constant_45,
	    string_constant_46,string_constant_47,string_constant_48,
	    string_constant_49,string_constant_50,string_constant_51,
	    string_constant_52,string_constant_53,string_constant_54,
	    string_constant_55,string_constant_56,string_constant_57,
	    string_constant_58,string_constant_59,string_constant_60,
	    string_constant_61,string_constant_62,string_constant_63,
	    string_constant_64,string_constant_65,string_constant_66,
	    string_constant_67,string_constant_68,string_constant_69,
	    string_constant_70,string_constant_71,string_constant_72,
	    string_constant_73,string_constant_74,string_constant_75,
	    string_constant_76,string_constant_77,string_constant_78,
	    string_constant_79,string_constant_80),list(8,
	    string_constant_81,string_constant_82,string_constant_83,
	    string_constant_84,string_constant_85,string_constant_86,
	    string_constant_87,string_constant_88))));
    Qrelation_name = STATIC_SYMBOL("RELATION-NAME",AB_package);
    Qregistered_directory_of_names_p = 
	    STATIC_SYMBOL("REGISTERED-DIRECTORY-OF-NAMES-P",AB_package);
    mutate_global_property(Qrelation_name,T,Qregistered_directory_of_names_p);
    Qlocal_name = STATIC_SYMBOL("LOCAL-NAME",AB_package);
    mutate_global_property(Qlocal_name,T,Qregistered_directory_of_names_p);
    Qcategory_is_not_g2_element_datum_type = 
	    STATIC_SYMBOL("CATEGORY-IS-NOT-G2-ELEMENT-DATUM-TYPE",AB_package);
    string_constant_89 = 
	    STATIC_STRING("1y1m83-Yy83BEy1o83BEy83-Gyl9k1m83BEy83hhy1m83BEy83C7y1n83hhy1m9l8377y83=Ky1n83xhy1m9l83*ly83=oy1n83xhy1m9l830my83-Hy1m83xhy1m9l8");
    string_constant_90 = 
	    STATIC_STRING("3Sy1m83xhy1m9l83=By1m83xhy1m9l9m1m83xhy1m9l83-2y1m83xhy1m9l83Gy1n83xhy1m9l8s1l8s1n83xhy1m9l830Sy1l830Sy");
    clear_optimized_constants();
    push_optimized_constant(Qcategory_is_not_g2_element_datum_type);
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_89,
	    string_constant_90)));
    string_constant_91 = 
	    STATIC_STRING("1u1n83C7y1m9k83*ly83=oy1n83C7y1m9k830my83-Hy1m83C7y1m9k83Sy1m83C7y1m9k83=By1m83C7y1m9k9l1m83C7y1m9k83-2y1m83C7y1m9k83-hy1m83C7y1");
    string_constant_92 = 
	    STATIC_STRING("m9k83Gy1n83C7y1m9k8s1l8s1n83C7y1m9k830Sy1l830Sy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfloat);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_91,
	    string_constant_92)));
    string_constant_93 = STATIC_STRING("1m1m83xVy83C7y1m83xVy83hhy");
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_93));
    Qfix_up_attribute_type_and_modifications_phrase = 
	    STATIC_SYMBOL("FIX-UP-ATTRIBUTE-TYPE-AND-MODIFICATIONS-PHRASE",
	    AB_package);
    string_constant_94 = 
	    STATIC_STRING("1m1m83pwy83xVy1o83pwy1n83xVy1m9k83vy83q2y1n83-FQyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_up_attribute_type_and_modifications_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_94));
    string_constant_95 = 
	    STATIC_STRING("1m1m83pxy83hhy1o83pxy1n83hhy1m9k83vy83q2y1n83-FQyln9l");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qfix_up_attribute_type_and_modifications_phrase);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_95));
    SET_SYMBOL_FUNCTION(Qfix_up_attribute_type_and_modifications_phrase,
	    STATIC_FUNCTION(fix_up_attribute_type_and_modifications_phrase,
	    NIL,FALSE,1,1));
    Qattribute_type_modification_list = 
	    STATIC_SYMBOL("ATTRIBUTE-TYPE-MODIFICATION-LIST",AB_package);
    Qattribute_type_modification = 
	    STATIC_SYMBOL("ATTRIBUTE-TYPE-MODIFICATION",AB_package);
    add_grammar_rules_for_list(5,Qattribute_type_modification_list,
	    Qattribute_type_modification,Qcm,Qcm,Nil);
    Qdecode_ddd_dot_dddd_format_in_format_override = 
	    STATIC_SYMBOL("DECODE-DDD.DDDD-FORMAT-IN-FORMAT-OVERRIDE",
	    AB_package);
    string_constant_96 = 
	    STATIC_STRING("1o1n83=5y1p1m9k83=7y1m9k83*5y83=Zy1m9k831Ay1m9k83A*y1m83=6y832ny1n83=5y1o1m9k83=7y1m9k83*5y83=Zy1m9k83-oy1m83=6y83-oy1o83=5y1n1m");
    string_constant_97 = 
	    STATIC_STRING("9k83=7y1m9k83*5y83J9y1m83=6yn9l1n83=5y1o1m9k83=7y1m9k83*5y1m9k83-ey1m9k83Gy1m83=6y8341y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qdecode_ddd_dot_dddd_format_in_format_override);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_96,
	    string_constant_97)));
    Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp = 
	    STATIC_SYMBOL("TRANSFORM-DATE-PHRASE-AND-TIME-OF-DAY-INTO-G2-TIME-STAMP",
	    AB_package);
    string_constant_98 = STATIC_STRING("1l1o832ny1m8355y83o+y1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_98));
    string_constant_99 = STATIC_STRING("1l1o83-F3y1m8355y83o-y1mlm9k");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_99));
    Qcoerce_phrase_number_to_float = 
	    STATIC_SYMBOL("COERCE-PHRASE-NUMBER-TO-FLOAT",AB_package);
    string_constant_100 = STATIC_STRING("1l1p83-F4y1m8355y83o-y1mlm9k9l");
    clear_optimized_constants();
    push_optimized_constant(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp);
    push_optimized_constant(Qcoerce_phrase_number_to_float);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_100));
    Qcoerce_quantity_interval_to_float_interval = 
	    STATIC_SYMBOL("COERCE-QUANTITY-INTERVAL-TO-FLOAT-INTERVAL",
	    AB_package);
    string_constant_101 = STATIC_STRING("1l1o83-U-y831Nyl9k");
    clear_optimized_constants();
    push_optimized_constant(Qcoerce_quantity_interval_to_float_interval);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_101));
    SET_SYMBOL_FUNCTION(Qcoerce_quantity_interval_to_float_interval,
	    STATIC_FUNCTION(coerce_quantity_interval_to_float_interval,NIL,
	    FALSE,1,1));
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    float_constant = STATIC_FLOAT(0.0);
    SET_SYMBOL_FUNCTION(Qcoerce_phrase_number_to_float,
	    STATIC_FUNCTION(coerce_phrase_number_to_float,NIL,FALSE,1,1));
    float_constant_1 = STATIC_FLOAT(1.0);
    SET_SYMBOL_FUNCTION(Qtransform_date_phrase_and_time_of_day_into_g2_time_stamp,
	    STATIC_FUNCTION(transform_date_phrase_and_time_of_day_into_g2_time_stamp,
	    NIL,FALSE,1,1));
    Qformat_override = STATIC_SYMBOL("FORMAT-OVERRIDE",AB_package);
    Qddd_dot_dddd_format = STATIC_SYMBOL("DDD.DDDD-FORMAT",AB_package);
    string_constant_1 = STATIC_STRING("bad attribute format");
    SET_SYMBOL_FUNCTION(Qdecode_ddd_dot_dddd_format_in_format_override,
	    STATIC_FUNCTION(decode_ddd_dot_dddd_format_in_format_override,
	    NIL,FALSE,1,1));
    string_constant_102 = STATIC_STRING("1l1n83-L5y1m1m9k83-ey1m9k83Gy8341y");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    add_grammar_rules_function(regenerate_optimized_constant(string_constant_102));
    string_constant_2 = STATIC_STRING(", ");
    Qinterval = STATIC_SYMBOL("INTERVAL",AB_package);
    string_constant_3 = STATIC_STRING(" an");
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    string_constant_4 = STATIC_STRING(" a");
    string_constant_5 = STATIC_STRING("");
    string_constant_6 = STATIC_STRING("formatted as~a ");
    Qformat_qm = STATIC_SYMBOL("FORMAT\?",AB_package);
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    string_constant_7 = STATIC_STRING("[deleted attribute]");
    Qelement_type = STATIC_SYMBOL("ELEMENT-TYPE",AB_package);
    Qcompile_element_type_for_slot = 
	    STATIC_SYMBOL("COMPILE-ELEMENT-TYPE-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_element_type_for_slot,
	    STATIC_FUNCTION(compile_element_type_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qelement_type,
	    SYMBOL_FUNCTION(Qcompile_element_type_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qelement_type,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    string_constant_8 = STATIC_STRING("none");
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant,(SI_Long)1L,FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)3L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)4L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)5L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)15L,(SI_Long)57344L);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)57344L);
    array_constant_2 = STATIC_ARRAY(list_constant,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)0L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)1L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)2L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)4L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)15L,(SI_Long)57344L);
    string_constant_9 = STATIC_STRING("~(~A~)");
    Qwrite_element_type_from_slot = 
	    STATIC_SYMBOL("WRITE-ELEMENT-TYPE-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_element_type_from_slot,
	    STATIC_FUNCTION(write_element_type_from_slot,NIL,FALSE,2,2));
    mutate_global_property(Qelement_type,
	    SYMBOL_FUNCTION(Qwrite_element_type_from_slot),Qslot_value_writer);
}
