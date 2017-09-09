/* qrs.c
 * Input file:  queries.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "qrs.h"


/* CDR-AND-REDUCE-NOTING-SOURCE-POSITION */
Object cdr_and_reduce_noting_source_position(parse)
    Object parse;
{
    x_note_fn_call(214,0);
    return reduce_noting_source_position(CDR(parse));
}

static Object Qcannot_replace_in_runtime_or_embedded_g2;  /* cannot-replace-in-runtime-or-embedded-g2 */

/* NOT-RUNTIME-OR-EMBEDDED */
Object not_runtime_or_embedded(parse)
    Object parse;
{
    x_note_fn_call(214,1);
    if (T)
	return VALUES_1(parse);
    else
	return VALUES_2(Bad_phrase,Qcannot_replace_in_runtime_or_embedded_g2);
}

static Object Qtrue;               /* true */

static Object Qfalse;              /* false */

/* WHERE-IS-SYMBOL-CANNOT-BE-TRUE-OR-FALSE */
Object where_is_symbol_cannot_be_true_or_false(parsed_where)
    Object parsed_where;
{
    Object gensymed_symbol, symbol_qm, actual_parse;

    x_note_fn_call(214,2);
    gensymed_symbol = parsed_where;
    symbol_qm = CAR(gensymed_symbol);
    gensymed_symbol = CDR(gensymed_symbol);
    actual_parse = CAR(gensymed_symbol);
    if (EQ(symbol_qm,Qtrue) || EQ(symbol_qm,Qfalse))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(actual_parse);
}

static Object list_constant;       /* # */

/* REJECT-INSPECT-KEYWORDS-AS-LOCAL-NAMES */
Object reject_inspect_keywords_as_local_names(parse_of_local_name)
    Object parse_of_local_name;
{
    x_note_fn_call(214,3);
    if (member_eql(parse_of_local_name,list_constant))
	return VALUES_1(Bad_phrase);
    else
	return VALUES_1(parse_of_local_name);
}

static Object list_constant_1;     /* # */

/* DO-QUERY-EVALUATION-FOR-CONTAINING */
Object do_query_evaluation_for_containing(item,what_to_look_for,
	    observance_of_word_boundary_qm)
    Object item, what_to_look_for, observance_of_word_boundary_qm;
{
    Object gathering_normally_editable_slots_for_search_qm, found_qm;
    Object string_to_look_for, slot_texts, text_representation_of_slot_value;
    Object ab_loop_list_, ab_loop_desetq_, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,4);
    gathering_normally_editable_slots_for_search_qm = T;
    PUSH_SPECIAL(Gathering_normally_editable_slots_for_search_qm,gathering_normally_editable_slots_for_search_qm,
	    0);
      found_qm = Nil;
      string_to_look_for = SYMBOLP(what_to_look_for) ? 
	      copy_symbol_name_parsably(what_to_look_for,Nil) : 
	      what_to_look_for;
      slot_texts = make_attributes_table_description(4,item,Nil,Nil,
	      list_constant_1);
      text_representation_of_slot_value = Nil;
      ab_loop_list_ = slot_texts;
      ab_loop_desetq_ = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      ab_loop_desetq_ = M_CAR(ab_loop_list_);
      temp = CDR(ab_loop_desetq_);
      temp = CDR(temp);
      text_representation_of_slot_value = CAR(temp);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (find_string_in_text_for_inspect(3,string_to_look_for,
	      text_representation_of_slot_value,
	      observance_of_word_boundary_qm)) {
	  found_qm = T;
	  goto end_loop;
      }
      goto next_loop;
    end_loop:
      if ( !EQ(string_to_look_for,what_to_look_for))
	  reclaim_text_string(string_to_look_for);
      reclaim_slot_value(slot_texts);
      result = VALUES_1(found_qm);
      goto end_1;
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

static Object Qok;                 /* ok */

static Object Qbad;                /* bad */

static Object Qincomplete;         /* incomplete */

static Object Qactive;             /* active */

static Object Qinactive;           /* inactive */

static Object Qenabled;            /* enabled */

static Object Qdisabled;           /* disabled */

/* DO-QUERY-EVALUATION-FOR-WITH-STATUS */
Object do_query_evaluation_for_with_status(item,status)
    Object item, status;
{
    Object goal_internal_status, frame_status_and_notes, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,5);
    if (EQ(status,Qok) || EQ(status,Qbad) || EQ(status,Qincomplete)) {
	goal_internal_status = EQ(status,Qok) ? Nil : status;
	frame_status_and_notes = ISVREF(item,(SI_Long)8L);
	return VALUES_1(EQ(goal_internal_status,
		ATOM(frame_status_and_notes) ? frame_status_and_notes : 
		CAR(frame_status_and_notes)) ? T : Nil);
    }
    else if (EQ(status,Qactive) || EQ(status,Qinactive)) {
	temp = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & (SI_Long)256L);
	if (temp);
	else {
	    if (System_is_running || System_has_paused) {
		sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
			(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Simulation_subtable_class_description,
			(SI_Long)18L));
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
		temp =  !temp;
	    }
	    else
		temp = TRUEP(Nil);
	    temp = temp ?  !((SI_Long)0L != (IFIX(ISVREF(item,
		    (SI_Long)5L)) & (SI_Long)1L)) : TRUEP(Nil);
	}
	return VALUES_1(EQ(temp ? Qinactive : Qactive,status) ? T : Nil);
    }
    else if (EQ(status,Qenabled) || EQ(status,Qdisabled))
	return VALUES_1(EQ((SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)4L)) 
		& (SI_Long)8192L) ? Qdisabled : Qenabled,status) ? T : Nil);
    else
	return VALUES_1(Qnil);
}

/* DO-QUERY-EVALUATION-FOR-RULE-RESTRICTION */
Object do_query_evaluation_for_rule_restriction varargs_1(int, n)
{
    Object item, name, slot_name;
    Object class_qualifier_qm, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,6);
    INIT_ARGS_nonrelocating();
    item = REQUIRED_ARG_nonrelocating();
    name = REQUIRED_ARG_nonrelocating();
    slot_name = REQUIRED_ARG_nonrelocating();
    class_qualifier_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
	return memq_function(name,get_slot_value_function(item,slot_name,
		class_qualifier_qm));
    else
	return VALUES_1(Nil);
}

static Object Qunbound_in_protected_let;  /* unbound-in-protected-let */

static Object array_constant;      /* # */

/* MAKE-FULL-PATHNAME */
Object make_full_pathname(file_name_string_or_symbol)
    Object file_name_string_or_symbol;
{
    volatile Object name_string;
    volatile Object ascii_file_name;
    volatile Object default_full_pathname;
    Object merged_pathname;
    volatile Object merged_name_string;
    Object temp;
    Declare_stack_pointer;
    Declare_catch(1);
    Object result;

    x_note_fn_call(214,7);
    SAVE_STACK();
    name_string = Qunbound_in_protected_let;
    ascii_file_name = Qunbound_in_protected_let;
    default_full_pathname = Qunbound_in_protected_let;
    merged_pathname = Qunbound_in_protected_let;
    merged_name_string = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(0)) {
	name_string = SYMBOLP(file_name_string_or_symbol) ? 
		copy_symbol_name(2,file_name_string_or_symbol,Nil) : 
		copy_text_string(file_name_string_or_symbol);
	ascii_file_name = 
		convert_text_string_to_ascii_filename_as_much_as_possible(name_string);
	temp = Current_kb_pathname_qm;
	if (temp);
	else
	    temp = Process_specific_system_pathname;
	default_full_pathname = 
		gensym_make_pathname_with_copied_components(Nil,Nil,Nil,
		Nil,array_constant,Knewest,temp);
	merged_pathname = gensym_merge_pathnames_function(ascii_file_name,
		default_full_pathname,Nil);
	merged_name_string = gensym_namestring_as_text_string(1,
		merged_pathname);
	augment_pathname_from_file_system(merged_pathname,merged_name_string);
	SAVE_VALUES(VALUES_1(merged_pathname));
    }
    POP_UNWIND_PROTECT(0);
    if (merged_name_string) {
	if ( !EQ(merged_name_string,Qunbound_in_protected_let))
	    reclaim_text_string(merged_name_string);
    }
    if (default_full_pathname) {
	if ( !EQ(default_full_pathname,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(default_full_pathname);
    }
    if (ascii_file_name) {
	if ( !EQ(ascii_file_name,Qunbound_in_protected_let))
	    reclaim_text_string(ascii_file_name);
    }
    if (name_string) {
	if ( !EQ(name_string,Qunbound_in_protected_let))
	    reclaim_text_string(name_string);
    }
    CONTINUE_UNWINDING(0);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

static Object Qabort_level_3;      /* abort-level-3 */

/* OPEN-FILE-FOR-SEARCH-RESULTS */
Object open_file_for_search_results(namestring_1,inspect_command_qm)
    Object namestring_1, inspect_command_qm;
{
    Object inner_abort_level_tag, file_stream_for_printing_search_results_qm;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(214,8);
    if (PUSH_AREA(Dynamic_area,0)) {
	if (PUSH_CATCH(Qabort_level_3,0)) {
	    inner_abort_level_tag = Qabort_level_3;
	    PUSH_SPECIAL(Inner_abort_level_tag,inner_abort_level_tag,0);
	      file_stream_for_printing_search_results_qm = 
		      g2_stream_open_for_output(namestring_1);
	      if (file_stream_for_printing_search_results_qm)
		  write_inspect_file_header(2,
			  file_stream_for_printing_search_results_qm,
			  inspect_command_qm);
	      result = VALUES_1(file_stream_for_printing_search_results_qm);
	    POP_SPECIAL();
	}
	else
	    result = CATCH_VALUES();
	POP_CATCH(0);
    }
    POP_AREA(0);
    return result;
}

static Object Qtext_conversion_style;  /* text-conversion-style */

/* PRINT-FRAME-TO-FILE-FOR-SEARCH-RESULTS */
Object print_frame_to_file_for_search_results(file_stream_for_printing_search_results,
	    frame,slots_to_include_qm)
    Object file_stream_for_printing_search_results, frame, slots_to_include_qm;
{
    Object inner_abort_level_tag, temp;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(214,9);
    if (PUSH_AREA(Dynamic_area,0)) {
	if (PUSH_CATCH(Qabort_level_3,0)) {
	    inner_abort_level_tag = Qabort_level_3;
	    PUSH_SPECIAL(Inner_abort_level_tag,inner_abort_level_tag,0);
	      temp = 
		      get_lookup_slot_value_given_default(Language_parameters,
		      Qtext_conversion_style,Nil) ? 
		      get_text_conversion_style_structure_per_name(get_lookup_slot_value_given_default(Language_parameters,
		      Qtext_conversion_style,Nil)) : Nil;
	      if (temp);
	      else
		  temp = Default_text_conversion_style;
	      result = print_frame(4,frame,slots_to_include_qm,
		      file_stream_for_printing_search_results,temp);
	    POP_SPECIAL();
	}
	else
	    result = CATCH_VALUES();
	POP_CATCH(0);
    }
    POP_AREA(0);
    return result;
}

/* CLOSE-FILE-FOR-SEARCH-RESULTS */
Object close_file_for_search_results(file_stream_for_printing_search_results)
    Object file_stream_for_printing_search_results;
{
    Object inner_abort_level_tag;
    Declare_catch(1);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(214,10);
    if (PUSH_AREA(Dynamic_area,0)) {
	if (PUSH_CATCH(Qabort_level_3,0)) {
	    inner_abort_level_tag = Qabort_level_3;
	    PUSH_SPECIAL(Inner_abort_level_tag,inner_abort_level_tag,0);
	      result = g2_stream_close(file_stream_for_printing_search_results);
	    POP_SPECIAL();
	}
	else
	    result = CATCH_VALUES();
	POP_CATCH(0);
    }
    POP_AREA(0);
    return result;
}

static Object array_constant_1;    /* # */

static Object string_constant;     /* "An unsaved knowledge base." */

static Object string_constant_1;   /* "** From KB:    ~a" */

static Object string_constant_2;   /* "** File:       ~a" */

static Object Qdo_not_use;         /* do-not-use */

static Object Qwide_string;        /* wide-string */

static Object string_constant_3;   /* "** Written at: " */

static Object array_constant_2;    /* # */

static Object array_constant_3;    /* # */

static Object list_constant_2;     /* # */

static Object array_constant_4;    /* # */

/* WRITE-INSPECT-FILE-HEADER */
Object write_inspect_file_header varargs_1(int, n)
{
    Object file_stream_for_printing_search_results;
    Object query_command_qm, output_file_namestring;
    Object transcode_text_conversion_style, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, temp, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object second_1, minute, hour, day, month, year, initial_header_lines;
    Object line, ab_loop_list_;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);
    Object result;

    x_note_fn_call(214,11);
    INIT_ARGS_nonrelocating();
    file_stream_for_printing_search_results = REQUIRED_ARG_nonrelocating();
    query_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    output_file_namestring = gensym_namestring_as_text_string(1,
	    gensym_truename(file_stream_for_printing_search_results));
    transcode_text_conversion_style = 
	    get_lookup_slot_value_given_default(Language_parameters,
	    Qtext_conversion_style,Nil) ? 
	    get_text_conversion_style_structure_per_name(get_lookup_slot_value_given_default(Language_parameters,
	    Qtext_conversion_style,Nil)) : Nil;
    if (transcode_text_conversion_style);
    else
	transcode_text_conversion_style = Default_text_conversion_style;
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)7L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = 
	    copy_constant_wide_string_given_length(array_constant_1,
	    FIX((SI_Long)45L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    temp = Current_kb_pathname_qm ? gensym_namestring(1,
	    Current_kb_pathname_qm) : Nil;
    if (temp);
    else
	temp = string_constant;
    car_new_value = tformat_text_string(2,string_constant_1,temp);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = tformat_text_string(2,string_constant_2,
	    output_file_namestring);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      tformat(1,string_constant_3);
	      result = get_decoded_real_time();
	      MVS_6(result,second_1,minute,hour,day,month,year);
	      print_decoded_time(second_1,minute,hour,day,month,year);
	      car_new_value = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = 
	    copy_constant_wide_string_given_length(array_constant_2,
	    FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = 
	    copy_constant_wide_string_given_length(array_constant_2,
	    FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = 
	    copy_constant_wide_string_given_length(array_constant_2,
	    FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_1) = car_new_value;
    initial_header_lines = gensymed_symbol;
    line = Nil;
    ab_loop_list_ = initial_header_lines;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    line = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    export_and_emit_text_line(line,transcode_text_conversion_style,
	    file_stream_for_printing_search_results);
    goto next_loop;
  end_loop:
    reclaim_slot_value(initial_header_lines);
    if (query_command_qm) {
	export_and_emit_text_line(array_constant_3,
		transcode_text_conversion_style,
		file_stream_for_printing_search_results);
	print_frame(4,query_command_qm,list_constant_2,
		file_stream_for_printing_search_results,
		transcode_text_conversion_style);
    }
    export_and_emit_text_line(array_constant_2,
	    transcode_text_conversion_style,
	    file_stream_for_printing_search_results);
    return export_and_emit_text_line(array_constant_4,
	    transcode_text_conversion_style,
	    file_stream_for_printing_search_results);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-FOR-INSPECT-COMMAND-SEARCH-STATE?-VALUE */
Object reclaim_frame_serial_number_for_inspect_command_search_state_qm_value(value,
	    block)
    Object value, block;
{
    x_note_fn_call(214,12);
    reclaim_frame_serial_number(value);
    ISVREF(block,(SI_Long)20L) = Nil;
    return VALUES_1(Nil);
}

Object The_type_description_of_inspect_command_spot = UNBOUND;

Object Chain_of_available_inspect_command_spots = UNBOUND;

Object Inspect_command_spot_count = UNBOUND;

/* INSPECT-COMMAND-SPOT-STRUCTURE-MEMORY-USAGE */
Object inspect_command_spot_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,13);
    temp = Inspect_command_spot_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)16L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-INSPECT-COMMAND-SPOT-COUNT */
Object outstanding_inspect_command_spot_count()
{
    Object def_structure_inspect_command_spot_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,14);
    gensymed_symbol = IFIX(Inspect_command_spot_count);
    def_structure_inspect_command_spot_variable = 
	    Chain_of_available_inspect_command_spots;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_inspect_command_spot_variable))
	goto end_loop;
    def_structure_inspect_command_spot_variable = 
	    ISVREF(def_structure_inspect_command_spot_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-INSPECT-COMMAND-SPOT-1 */
Object reclaim_inspect_command_spot_1(inspect_command_spot)
    Object inspect_command_spot;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,15);
    inline_note_reclaim_cons(inspect_command_spot,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = inspect_command_spot;
    reclaim_structure_if_any(ISVREF(inspect_command_spot,(SI_Long)2L));
    SVREF(inspect_command_spot,FIX((SI_Long)2L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_inspect_command_spots;
    SVREF(inspect_command_spot,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_inspect_command_spots = inspect_command_spot;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-INSPECT-COMMAND-SPOT */
Object reclaim_structure_for_inspect_command_spot(inspect_command_spot)
    Object inspect_command_spot;
{
    x_note_fn_call(214,16);
    return reclaim_inspect_command_spot_1(inspect_command_spot);
}

static Object Qg2_defstruct_structure_name_inspect_command_spot_g2_struct;  /* g2-defstruct-structure-name::inspect-command-spot-g2-struct */

/* MAKE-PERMANENT-INSPECT-COMMAND-SPOT-STRUCTURE-INTERNAL */
Object make_permanent_inspect_command_spot_structure_internal()
{
    Object def_structure_inspect_command_spot_variable;
    Object inspect_command_spot_count_new_value;
    Object defstruct_g2_inspect_command_spot_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,17);
    def_structure_inspect_command_spot_variable = Nil;
    inspect_command_spot_count_new_value = 
	    FIXNUM_ADD1(Inspect_command_spot_count);
    Inspect_command_spot_count = inspect_command_spot_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_inspect_command_spot_variable = Nil;
	gensymed_symbol = (SI_Long)16L;
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
	defstruct_g2_inspect_command_spot_variable = the_array;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)0L)) 
		= Qg2_defstruct_structure_name_inspect_command_spot_g2_struct;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)1L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)2L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)3L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)4L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)5L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)6L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)7L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)8L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,FIX((SI_Long)9L)) 
		= Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,
		FIX((SI_Long)10L)) = Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,
		FIX((SI_Long)11L)) = Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,
		FIX((SI_Long)12L)) = Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,
		FIX((SI_Long)13L)) = Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,
		FIX((SI_Long)14L)) = Nil;
	SVREF(defstruct_g2_inspect_command_spot_variable,
		FIX((SI_Long)15L)) = Nil;
	def_structure_inspect_command_spot_variable = 
		defstruct_g2_inspect_command_spot_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_inspect_command_spot_variable);
}

static Object Kunknown;            /* :unknown */

/* MAKE-INSPECT-COMMAND-SPOT-1 */
Object make_inspect_command_spot_1()
{
    Object def_structure_inspect_command_spot_variable;

    x_note_fn_call(214,18);
    def_structure_inspect_command_spot_variable = 
	    Chain_of_available_inspect_command_spots;
    if (def_structure_inspect_command_spot_variable) {
	Chain_of_available_inspect_command_spots = 
		ISVREF(def_structure_inspect_command_spot_variable,
		(SI_Long)0L);
	SVREF(def_structure_inspect_command_spot_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_inspect_command_spot_g2_struct;
    }
    else
	def_structure_inspect_command_spot_variable = 
		make_permanent_inspect_command_spot_structure_internal();
    inline_note_allocate_cons(def_structure_inspect_command_spot_variable,Nil);
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)3L)) = T;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)4L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)5L)) = Nil;
    ISVREF(def_structure_inspect_command_spot_variable,(SI_Long)6L) = 
	    FIX((SI_Long)1000L);
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)7L)) = T;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)8L)) = 
	    Kunknown;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)9L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)10L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)11L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)12L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)13L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)14L)) = Nil;
    SVREF(def_structure_inspect_command_spot_variable,FIX((SI_Long)15L)) = Nil;
    return VALUES_1(def_structure_inspect_command_spot_variable);
}

/* GENERATE-SPOT-FOR-INSPECT-COMMAND */
Object generate_spot_for_inspect_command(inspect_command,mouse_pointer)
    Object inspect_command, mouse_pointer;
{
    x_note_fn_call(214,19);
    return generate_text_box_spot(inspect_command,mouse_pointer,
	    make_inspect_command_spot_1());
}

/* COMPILE-QUERY-COMMAND-FOR-SLOT */
Object compile_query_command_for_slot varargs_1(int, n)
{
    Object query_command_parse_result, gensymed_symbol, gensymed_symbol_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,20);
    INIT_ARGS_nonrelocating();
    query_command_parse_result = REQUIRED_ARG_nonrelocating();
    gensymed_symbol = REQUIRED_ARG_nonrelocating();
    gensymed_symbol_1 = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    return rewrite_query_command_parse_into_nicer_format(query_command_parse_result);
}

Object Temporary_name_number_1 = UNBOUND;

Object Temporary_name_number_2 = UNBOUND;

static Object Qsource_position;    /* source-position */

static Object list_constant_3;     /* # */

static Object Qclass_qualified_method;  /* class-qualified-method */

static Object list_constant_4;     /* # */

static Object list_constant_5;     /* # */

static Object Ksource_text;        /* :source-text */

static Object Kargument_1;         /* :argument-1 */

static Object Ktemporary_name;     /* :temporary-name */

static Object Ktemporary_name_2;   /* :temporary-name-2 */

/* REWRITE-QUERY-COMMAND-PARSE-INTO-NICER-FORMAT */
Object rewrite_query_command_parse_into_nicer_format(query_command_parse_result)
    Object query_command_parse_result;
{
    Object x, query_command, temp, name, normalized_name, gensymed_symbol;
    Object gensymed_symbol_1, query_command_symbol_or_form;
    Object start_filter_source_position, query_domain;
    Object end_filter_source_position, optional_attribute_argument;
    Object attribute_argument_qm, source_text, phrase_text_string, class_1;
    Object argument_1;

    x_note_fn_call(214,21);
    x = SECOND(query_command_parse_result);
    if (SYMBOLP(x))
	query_command = x;
    else if ( !EQ(CAR(x),Qsource_position))
	query_command = CAR(x);
    else {
	temp = SECOND(x);
	if (SYMBOLP(temp))
	    query_command = SECOND(x);
	else {
	    temp = SECOND(x);
	    query_command = CAR(temp);
	}
    }
    if ( !TRUEP(memq_function(query_command,list_constant_3)))
	return VALUES_1(query_command_parse_result);
    else {
	name = THIRD(query_command_parse_result);
	normalized_name = Nil;
	if (CONSP(name) && EQ(M_CAR(name),Qclass_qualified_method)) {
	    normalized_name = copy_for_phrase(list_constant_4);
	    nsubst(3,name,Kname,normalized_name);
	    M_THIRD(query_command_parse_result) = normalized_name;
	}
	else if (SYMBOLP(name)) {
	    normalized_name = copy_for_phrase(list_constant_5);
	    nsubst(3,name,Kname,normalized_name);
	    M_THIRD(query_command_parse_result) = normalized_name;
	}
	gensymed_symbol = query_command_parse_result;
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	query_command_symbol_or_form = CAR(gensymed_symbol_1);
	start_filter_source_position = CDR(gensymed_symbol_1);
	gensymed_symbol_1 = CAR(gensymed_symbol);
	gensymed_symbol = CDR(gensymed_symbol);
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	query_domain = CAR(gensymed_symbol_1);
	end_filter_source_position = CDR(gensymed_symbol_1);
	optional_attribute_argument = gensymed_symbol;
	attribute_argument_qm = Nil;
	query_command = SYMBOLP(query_command_symbol_or_form) ? 
		query_command_symbol_or_form : 
		CAR(query_command_symbol_or_form);
	if ( !TRUEP(memq_function(query_command,list_constant_3)))
	    return strip_source_positions(query_command_parse_result);
	else {
	    if (optional_attribute_argument) {
		gensymed_symbol = optional_attribute_argument;
		gensymed_symbol = CAR(gensymed_symbol);
		gensymed_symbol = CDR(gensymed_symbol);
		attribute_argument_qm = CAR(gensymed_symbol);
		start_filter_source_position = CDR(gensymed_symbol);
	    }
	    source_text = 
		    text_string_from_current_source(start_filter_source_position,
		    end_filter_source_position);
	    phrase_text_string = Nil;
	    phrase_text_string = copy_for_phrase(source_text);
	    if (text_string_p(source_text))
		reclaim_text_string(source_text);
	    gensymed_symbol = query_domain;
	    gensymed_symbol = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    class_1 = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CAR(gensymed_symbol);
	    gensymed_symbol = CDR(gensymed_symbol);
	    gensymed_symbol = CAR(gensymed_symbol);
	    gensymed_symbol = CAR(gensymed_symbol);
	    argument_1 = CAR(gensymed_symbol);
	    nsubst(3,phrase_text_string,Ksource_text,query_domain);
	    nsubst(3,class_1,Kclass,query_domain);
	    nsubst(3,argument_1,Kargument_1,query_domain);
	    nsubst(3,Temporary_name_number_1,Ktemporary_name,query_domain);
	    nsubst(3,Temporary_name_number_2,Ktemporary_name_2,query_domain);
	    M_SECOND(query_command_parse_result) = 
		    query_command_symbol_or_form;
	    M_THIRD(query_command_parse_result) = query_domain;
	    if (attribute_argument_qm)
		M_FOURTH(query_command_parse_result) = attribute_argument_qm;
	    return VALUES_1(query_command_parse_result);
	}
    }
}

/* STRIP-SOURCE-POSITIONS */
Object strip_source_positions(phrase_cons_tree)
    Object phrase_cons_tree;
{
    Object temp;

    x_note_fn_call(214,22);
    if (CONSP(phrase_cons_tree)) {
	if (EQ(M_CAR(phrase_cons_tree),Qsource_position))
	    return strip_source_positions(SECOND(phrase_cons_tree));
	else {
	    temp = strip_source_positions(CAR(phrase_cons_tree));
	    M_CAR(phrase_cons_tree) = temp;
	    temp = strip_source_positions(CDR(phrase_cons_tree));
	    M_CDR(phrase_cons_tree) = temp;
	    return VALUES_1(phrase_cons_tree);
	}
    }
    else
	return VALUES_1(phrase_cons_tree);
}

static Object Qinspect_command;    /* inspect-command */

/* CLEANUP-FOR-INSPECT-COMMAND */
Object cleanup_for_inspect_command(inspect_command)
    Object inspect_command;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,23);
    frame = inspect_command;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qinspect_command)) {
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
    return cancel_search_state_for_inspect_command_if_necessary(inspect_command);
}

static Object Qavailable_frame_vector;  /* available-frame-vector */

/* CANCEL-SEARCH-STATE-FOR-INSPECT-COMMAND-IF-NECESSARY */
Object cancel_search_state_for_inspect_command_if_necessary(inspect_command)
    Object inspect_command;
{
    Object search_state_qm, gensymed_symbol, x, y, xa, ya;
    char temp;

    x_note_fn_call(214,24);
    search_state_qm = ISVREF(inspect_command,(SI_Long)19L);
    if (search_state_qm) {
	gensymed_symbol = ISVREF(search_state_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(search_state_qm) ? 
		EQ(ISVREF(search_state_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(inspect_command,(SI_Long)20L);
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
		    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(y),M_CDR(x)) 
			    : TRUEP(Qnil);
	    }
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	cancel_scheduled_search_if_necessary(search_state_qm);
	delete_frame(search_state_qm);
	return VALUES_1(ISVREF(inspect_command,(SI_Long)19L) = Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_defstruct_structure_name_class_description_g2_struct;  /* g2-defstruct-structure-name::class-description-g2-struct */

/* CLONED-WORKSPACE-TO-BE-DELETED-P */
Object cloned_workspace_to_be_deleted_p(frame)
    Object frame;
{
    Object gensymed_symbol, superblock_qm, sub_class_bit_vector, x2, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(214,25);
    gensymed_symbol = ISVREF(frame,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)5L) : Nil;
    superblock_qm = gensymed_symbol;
    if (superblock_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	if (temp);
	else {
	    if (SIMPLE_VECTOR_P(superblock_qm) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(superblock_qm)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(superblock_qm,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(superblock_qm,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		sub_class_bit_vector = ISVREF(ISVREF(superblock_qm,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Workspace_class_description,(SI_Long)18L));
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
	}
	if (temp) {
	    gensymed_symbol = ISVREF(superblock_qm,(SI_Long)3L);
	    temp_1 =  ! !(FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) 
		    == (SI_Long)-1L : TRUEP(Nil)) ? T : Nil;
	}
	else
	    temp_1 = Nil;
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object Qpriority_queue;     /* priority-queue */

/* IGNORE-IN-RECOMPILE-P */
Object ignore_in_recompile_p(frame)
    Object frame;
{
    Object gensymed_symbol, sub_class_bit_vector, temp_1, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(214,26);
    if (g2_enterprise_p()) {
	gensymed_symbol = ISVREF(frame,(SI_Long)1L);
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Parameter_class_description,(SI_Long)18L));
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
	if (temp)
	    temp_1 = T;
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Quantity_array_class_description,
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
	    if (temp)
		temp_1 = T;
	    else {
		gensymed_symbol_4 = 
			lookup_global_or_kb_specific_property_value(Qhash_table,
			Class_description_gkbprop);
		if (gensymed_symbol_4) {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
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
		if (temp)
		    temp_1 = T;
		else {
		    gensymed_symbol_4 = 
			    lookup_global_or_kb_specific_property_value(Qpriority_queue,
			    Class_description_gkbprop);
		    if (gensymed_symbol_4) {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(gensymed_symbol_4,(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
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
		    if (temp)
			temp_1 = T;
		    else
			temp_1 = Nil;
		}
	    }
	}
    }
    else
	temp_1 = Nil;
    return VALUES_1(temp_1);
}

static Object list_constant_6;     /* # */

static Object Qnamed_by_debugging_name;  /* named-by-debugging-name */

static Object Qnamed_by;           /* named-by */

static Object list_constant_7;     /* # */

static Object list_constant_8;     /* # */

static Object list_constant_9;     /* # */

static Object Qany;                /* any */

/* EVALUATE-QUERY-TO-FIRST-APPROXIMATION */
Object evaluate_query_to_first_approximation(query_designation,
	    ignore_in_recompile_qm)
    Object query_designation, ignore_in_recompile_qm;
{
    Object current_computation_flags, eval_list_of_items, gensymed_symbol;
    Object class_1, predicate, logical_expression, name, workspace_designation;
    Object flag, result_1, role_1, domain_1, role_2, domain_2, temp, role;
    Object domain, temp_1, temp_2, temp_3, temp_4, workspace_qm;
    Object class_description_qm, x2, sub_class_bit_vector, ab_queue_form_;
    Object ab_next_queue_element_, frame, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, designation, eval_cons_trailer, eval_cons;
    Object next_eval_cons;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_5;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,27);
    current_computation_flags = Current_computation_flags;
    PUSH_SPECIAL(Current_computation_flags,current_computation_flags,0);
      eval_list_of_items = Nil;
      Current_computation_flags = FIX(IFIX(Current_computation_flags) | 
	      (SI_Long)16L);
      gensymed_symbol = query_designation;
      gensymed_symbol = CDR(gensymed_symbol);
      class_1 = CAR(gensymed_symbol);
      gensymed_symbol = CDR(gensymed_symbol);
      predicate = CAR(gensymed_symbol);
      logical_expression = THIRD(predicate);
      name = Nil;
      workspace_designation = Nil;
      if (CONSP(class_1) && EQ(M_CAR(class_1),Qclass_qualified_method))
	  eval_list_of_items = serve_eval_list_of_role_values(class_1,Nil);
      else {
	  result = logical_expression_includes_pattern(logical_expression,
		  list_constant_6,FIX((SI_Long)3L));
	  MVS_2(result,flag,result_1);
	  name = result_1;
	  if (flag) {
	      role_1 = gensym_list_2(Qnamed_by_debugging_name,class_1);
	      domain_1 = make_temporary_constant_no_expiration(name,Qsymbol);
	      role_2 = gensym_list_2(Qnamed_by,class_1);
	      domain_2 = make_temporary_constant_no_expiration(name,Qsymbol);
	      temp = serve_eval_list_of_role_values(role_1,domain_1);
	      temp = nconc2(temp,serve_eval_list_of_role_values(role_2,
		      domain_2));
	      reclaim_slot_value(role_1);
	      reclaim_temporary_constant_1(domain_1);
	      reclaim_slot_value(role_2);
	      reclaim_temporary_constant_1(domain_2);
	      eval_list_of_items = temp;
	  }
	  else {
	      result = logical_expression_includes_pattern(logical_expression,
		      list_constant_7,FIX((SI_Long)2L));
	      MVS_2(result,flag,result_1);
	      name = result_1;
	      if (flag) {
		  role = gensym_list_2(Qnamed_by,class_1);
		  domain = make_temporary_constant_no_expiration(name,Qsymbol);
		  temp = serve_eval_list_of_role_values(role,domain);
		  reclaim_slot_value(role);
		  reclaim_temporary_constant_1(domain);
		  eval_list_of_items = temp;
	      }
	      else {
		  result = logical_expression_includes_pattern(logical_expression,
			  list_constant_8,FIX((SI_Long)2L));
		  MVS_2(result,flag,result_1);
		  name = result_1;
		  if (flag) {
		      role_1 = gensym_list_2(Qnamed_by_debugging_name,class_1);
		      domain_1 = 
			      make_temporary_constant_no_expiration(name,
			      Qsymbol);
		      role_2 = gensym_list_2(Qnamed_by,class_1);
		      domain_2 = 
			      make_temporary_constant_no_expiration(name,
			      Qsymbol);
		      temp_1 = serve_eval_list_of_role_values(role_1,domain_1);
		      temp_2 = serve_eval_list_of_role_values(role_2,domain_2);
		      temp_3 = reclaim_slot_value(role_1);
		      temp_4 = reclaim_temporary_constant_1(domain_1);
		      temp = reclaim_slot_value(role_2);
		      temp = nconc2(temp_1,nconc2(temp_2,nconc2(temp_3,
			      nconc2(temp_4,nconc2(temp,
			      reclaim_temporary_constant_1(domain_2))))));
		      eval_list_of_items = temp;
		  }
		  else {
		      result = logical_expression_includes_pattern(logical_expression,
			      list_constant_9,FIX((SI_Long)2L));
		      MVS_2(result,flag,result_1);
		      workspace_designation = result_1;
		      if (flag) {
			  workspace_qm = 
				  evaluate_designation(workspace_designation,
				  Nil);
			  class_description_qm = 
				  lookup_global_or_kb_specific_property_value(class_1,
				  Class_description_gkbprop);
			  if (workspace_qm && class_description_qm && 
				  ISVREF(class_description_qm,(SI_Long)16L)) {
			      if (SIMPLE_VECTOR_P(workspace_qm) && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(workspace_qm)) 
				      > (SI_Long)2L &&  
				      !EQ(ISVREF(workspace_qm,(SI_Long)1L),
				      Qavailable_frame_vector)) {
				  x2 = ISVREF(workspace_qm,(SI_Long)1L);
				  gensymed_symbol = SIMPLE_VECTOR_P(x2) && 
					  EQ(ISVREF(x2,(SI_Long)0L),
					  Qg2_defstruct_structure_name_class_description_g2_struct) 
					  ? x2 : Qnil;
			      }
			      else
				  gensymed_symbol = Nil;
			      if (gensymed_symbol) {
				  sub_class_bit_vector = 
					  ISVREF(gensymed_symbol,(SI_Long)19L);
				  superior_class_bit_number = 
					  IFIX(ISVREF(Kb_workspace_class_description,
					  (SI_Long)18L));
				  sub_class_vector_index = 
					  superior_class_bit_number >>  -  
					  - (SI_Long)3L;
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
				      gensymed_symbol_2 = 
					      gensymed_symbol_2 << 
					      gensymed_symbol_3;
				      gensymed_symbol_1 = 
					      gensymed_symbol_1 & 
					      gensymed_symbol_2;
				      temp_5 = (SI_Long)0L < gensymed_symbol_1;
				  }
				  else
				      temp_5 = TRUEP(Nil);
			      }
			      else
				  temp_5 = TRUEP(Nil);
			      if (temp_5);
			      else {
				  if (SIMPLE_VECTOR_P(workspace_qm) && 
					  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(workspace_qm)) 
					  > (SI_Long)2L &&  
					  !EQ(ISVREF(workspace_qm,
					  (SI_Long)1L),
					  Qavailable_frame_vector)) {
				      x2 = ISVREF(workspace_qm,(SI_Long)1L);
				      gensymed_symbol = 
					      SIMPLE_VECTOR_P(x2) && 
					      EQ(ISVREF(x2,(SI_Long)0L),
					      Qg2_defstruct_structure_name_class_description_g2_struct) 
					      ? x2 : Qnil;
				  }
				  else
				      gensymed_symbol = Nil;
				  if (gensymed_symbol) {
				      sub_class_bit_vector = 
					      ISVREF(gensymed_symbol,
					      (SI_Long)19L);
				      superior_class_bit_number = 
					      IFIX(ISVREF(Message_board_class_description,
					      (SI_Long)18L));
				      sub_class_vector_index = 
					      superior_class_bit_number >> 
					       -  - (SI_Long)3L;
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
					  temp_5 = (SI_Long)0L < 
						  gensymed_symbol_1;
				      }
				      else
					  temp_5 = TRUEP(Nil);
				  }
				  else
				      temp_5 = TRUEP(Nil);
			      }
			  }
			  else
			      temp_5 = TRUEP(Nil);
			  if (temp_5) {
			      gensymed_symbol = ISVREF(workspace_qm,
				      (SI_Long)14L);
			      gensymed_symbol = gensymed_symbol ? 
				      ISVREF(gensymed_symbol,(SI_Long)4L) :
				       Nil;
			      ab_queue_form_ = gensymed_symbol;
			      ab_next_queue_element_ = Nil;
			      frame = Nil;
			      ab_loopvar_ = Nil;
			      ab_loopvar__1 = Nil;
			      ab_loopvar__2 = Nil;
			      if (ab_queue_form_)
				  ab_next_queue_element_ = 
					  ISVREF(ab_queue_form_,(SI_Long)0L);
			    next_loop:
			      if (EQ(ab_next_queue_element_,ab_queue_form_))
				  goto end_loop;
			      frame = ISVREF(ab_next_queue_element_,
				      (SI_Long)2L);
			      ab_next_queue_element_ = 
				      ISVREF(ab_next_queue_element_,
				      (SI_Long)0L);
			      gensymed_symbol = ISVREF(frame,(SI_Long)1L);
			      sub_class_bit_vector = 
				      ISVREF(gensymed_symbol,(SI_Long)19L);
			      superior_class_bit_number = 
				      IFIX(ISVREF(class_description_qm,
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
				  gensymed_symbol_2 = gensymed_symbol_2 << 
					  gensymed_symbol_3;
				  gensymed_symbol_1 = gensymed_symbol_1 & 
					  gensymed_symbol_2;
				  temp_5 = (SI_Long)0L < gensymed_symbol_1;
			      }
			      else
				  temp_5 = TRUEP(Nil);
			      if (temp_5) {
				  ab_loopvar__2 = gensym_cons_1(frame,Nil);
				  if (ab_loopvar__1)
				      M_CDR(ab_loopvar__1) = ab_loopvar__2;
				  else
				      ab_loopvar_ = ab_loopvar__2;
				  ab_loopvar__1 = ab_loopvar__2;
			      }
			      goto next_loop;
			    end_loop:
			      eval_list_of_items = ab_loopvar_;
			      goto end_1;
			      eval_list_of_items = Qnil;
			    end_1:;
			  }
			  else
			      eval_list_of_items = Nil;
		      }
		      else {
			  designation = gensym_list_2(Qany,class_1);
			  temp = 
				  serve_eval_list_of_designation_values(designation);
			  reclaim_gensym_list_1(designation);
			  eval_list_of_items = temp;
		      }
		  }
	      }
	  }
      }
      if (eval_list_of_items) {
	  eval_cons_trailer = Nil;
	  eval_cons = eval_list_of_items;
	  next_eval_cons = Nil;
	next_loop_1:
	  next_eval_cons = M_CDR(eval_cons);
	  if (embedded_rule_p(M_CAR(eval_cons))) {
	      reclaim_gensym_cons_1(eval_cons);
	      eval_cons = next_eval_cons;
	      if (eval_cons_trailer)
		  M_CDR(eval_cons_trailer) = next_eval_cons;
	      else
		  eval_list_of_items = next_eval_cons;
	  }
	  else if (cloned_workspace_to_be_deleted_p(M_CAR(eval_cons))) {
	      reclaim_gensym_cons_1(eval_cons);
	      eval_cons = next_eval_cons;
	      if (eval_cons_trailer)
		  M_CDR(eval_cons_trailer) = next_eval_cons;
	      else
		  eval_list_of_items = next_eval_cons;
	  }
	  else if (ignore_in_recompile_qm && 
		  ignore_in_recompile_p(M_CAR(eval_cons))) {
	      reclaim_gensym_cons_1(eval_cons);
	      eval_cons = next_eval_cons;
	      if (eval_cons_trailer)
		  M_CDR(eval_cons_trailer) = next_eval_cons;
	      else
		  eval_list_of_items = next_eval_cons;
	  }
	  else {
	      eval_cons_trailer = eval_cons;
	      eval_cons = next_eval_cons;
	  }
	  if ( !TRUEP(eval_cons))
	      goto end_loop_1;
	  goto next_loop_1;
	end_loop_1:;
      }
      result = VALUES_1(eval_list_of_items);
    POP_SPECIAL();
    return result;
}

Object Match_pattern_for_inspect_binding_vector = UNBOUND;

Object Fill_pointer_for_match_pattern_for_inspect_binding_vector = UNBOUND;

/* LOGICAL-EXPRESSION-INCLUDES-PATTERN */
Object logical_expression_includes_pattern(logical_expression,pattern,
	    return_index)
    Object logical_expression, pattern, return_index;
{
    Object temp, sub_expression, ab_loop_list_, flag, result_1;
    Object result;

    x_note_fn_call(214,28);
    Fill_pointer_for_match_pattern_for_inspect_binding_vector = 
	    FIX((SI_Long)0L);
    if (match_pattern_for_inspect_1(logical_expression,pattern)) {
	temp = ISVREF(Match_pattern_for_inspect_binding_vector,
		IFIX(sub1(return_index)));
	return VALUES_2(T,temp);
    }
    if (CONSP(logical_expression) && EQ(Qand,CAR(logical_expression))) {
	sub_expression = Nil;
	ab_loop_list_ = REST(logical_expression);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	sub_expression = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	result = logical_expression_includes_pattern(sub_expression,
		pattern,return_index);
	MVS_2(result,flag,result_1);
	if (flag)
	    return VALUES_2(flag,result_1);
	goto next_loop;
      end_loop:;
    }
    return VALUES_1(Nil);
}

static Object Kany;                /* :any */

static Object Ksymbol;             /* :symbol */

static Object Ka;                  /* :a */

static Object Kb;                  /* :b */

static Object Kc;                  /* :c */

/* MATCH-PATTERN-FOR-INSPECT-1 */
Object match_pattern_for_inspect_1(target,pattern)
    Object target, pattern;
{
    Object add_to_binding_vector_qm, temp, temp_1, svref_arg_2;

    x_note_fn_call(214,29);
    if (CONSP(pattern)) {
	if (CONSP(target) && match_pattern_for_inspect_1(CAR(target),
		CAR(pattern)))
	    return match_pattern_for_inspect_1(CDR(target),CDR(pattern));
	else
	    return VALUES_1(Nil);
    }
    else if (KEYWORDP(pattern)) {
	add_to_binding_vector_qm = Nil;
	if (EQ(pattern,Kany)) {
	    add_to_binding_vector_qm = T;
	    temp = T;
	}
	else if (EQ(pattern,Ksymbol)) {
	    add_to_binding_vector_qm = T;
	    temp = SYMBOLP(target) ? T : Nil;
	}
	else if (EQ(pattern,Ka))
	    temp = EQ(target,
		    ISVREF(Match_pattern_for_inspect_binding_vector,
		    (SI_Long)0L)) ? T : Nil;
	else if (EQ(pattern,Kb))
	    temp = EQ(target,
		    ISVREF(Match_pattern_for_inspect_binding_vector,
		    (SI_Long)1L)) ? T : Nil;
	else if (EQ(pattern,Kc))
	    temp = EQ(target,
		    ISVREF(Match_pattern_for_inspect_binding_vector,
		    (SI_Long)2L)) ? T : Nil;
	else
	    temp = Qnil;
	if (add_to_binding_vector_qm) {
	    temp_1 = Match_pattern_for_inspect_binding_vector;
	    svref_arg_2 = 
		    Fill_pointer_for_match_pattern_for_inspect_binding_vector;
	    SVREF(temp_1,svref_arg_2) = target;
	    temp_1 = 
		    FIXNUM_ADD1(Fill_pointer_for_match_pattern_for_inspect_binding_vector);
	    Fill_pointer_for_match_pattern_for_inspect_binding_vector = temp_1;
	}
	return VALUES_1(temp);
    }
    else if (ATOM(pattern))
	return VALUES_1(EQ(pattern,target) ? T : Nil);
    else
	return VALUES_1(EQ(pattern,target) ? T : Nil);
}

Object Override_limited_license_block_on_inspect_qm = UNBOUND;

/* G2-PERMIT-INSPECTOR-WITHIN-RESTRICTED-LICENSE */
Object g2_permit_inspector_within_restricted_license()
{
    x_note_fn_call(214,30);
    Override_limited_license_block_on_inspect_qm = T;
    return VALUES_1(Evaluation_true_value);
}

Object Inspect_command_history_list = UNBOUND;

/* CLEAR-INSPECT-COMMAND-HISTORY-LIST */
Object clear_inspect_command_history_list()
{
    Object history_string, ab_loop_list_;

    x_note_fn_call(214,31);
    history_string = Nil;
    ab_loop_list_ = Inspect_command_history_list;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    history_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_text_string(history_string);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(Inspect_command_history_list);
    Inspect_command_history_list = Nil;
    return VALUES_1(Nil);
}

static Object Qshow_inspect_command_history_on_a_workspace;  /* show-inspect-command-history-on-a-workspace */

/* CACHE-INSPECT-COMMAND-HISTORY */
Object cache_inspect_command_history(inspect_command)
    Object inspect_command;
{
    Object temp, query, query_handler, inspect_command_string;
    Object trailing_pointer_1, leading_pointer_1, cdr_new_value;
    Object trailing_pointer_2, leading_pointer_2;

    x_note_fn_call(214,32);
    temp = ISVREF(inspect_command,(SI_Long)16L);
    query = CAR(temp);
    temp = SECOND(query);
    if (CONSP(temp)) {
	temp = SECOND(query);
	query_handler = FIRST(temp);
    }
    else
	query_handler = SECOND(query);
    if (EQUAL(Qshow_inspect_command_history_on_a_workspace,query_handler))
	return VALUES_1(Nil);
    temp = ISVREF(inspect_command,(SI_Long)16L);
    inspect_command_string = convert_text_to_text_string(1,CDR(temp));
    trailing_pointer_1 = Nil;
    leading_pointer_1 = Inspect_command_history_list;
  next_loop:
    if ( !TRUEP(leading_pointer_1))
	goto end_loop;
    if (string_eq_w(CAR(leading_pointer_1),inspect_command_string)) {
	if (trailing_pointer_1) {
	    cdr_new_value = CDR(leading_pointer_1);
	    M_CDR(trailing_pointer_1) = cdr_new_value;
	}
	else
	    Inspect_command_history_list = CDR(Inspect_command_history_list);
	reclaim_text_string(CAR(leading_pointer_1));
	reclaim_gensym_cons_1(leading_pointer_1);
	Inspect_command_history_list = 
		nconc2(gensym_cons_1(inspect_command_string,Nil),
		Inspect_command_history_list);
	return VALUES_1(Nil);
    }
    trailing_pointer_1 = leading_pointer_1;
    leading_pointer_1 = CDR(leading_pointer_1);
    goto next_loop;
  end_loop:;
    if (FIXNUM_GE(length(Inspect_command_history_list),
	    Inspect_command_history_list_max_size)) {
	trailing_pointer_2 = Nil;
	leading_pointer_2 = Inspect_command_history_list;
      next_loop_1:
	if ( !TRUEP(CDR(leading_pointer_2))) {
	    reclaim_text_string(M_CAR(leading_pointer_2));
	    reclaim_gensym_cons_1(leading_pointer_2);
	    M_CDR(trailing_pointer_2) = Nil;
	    goto end_loop_1;
	}
	trailing_pointer_2 = leading_pointer_2;
	leading_pointer_2 = CDR(leading_pointer_2);
	goto next_loop_1;
      end_loop_1:;
    }
    Inspect_command_history_list = 
	    nconc2(gensym_cons_1(inspect_command_string,Nil),
	    Inspect_command_history_list);
    return VALUES_1(Nil);
}

static Object string_constant_4;   /* "~% There exists ~D command history.~%~%" */

static Object Qinspect_history;    /* inspect-history */

static Object Qbox_translation_and_text;  /* box-translation-and-text */

static Object string_constant_5;   /* "No inspect command history." */

/* SHOW-INSPECT-COMMAND-HISTORY-ON-A-WORKSPACE */
Object show_inspect_command_history_on_a_workspace(inspect_command)
    Object inspect_command;
{
    Object workspace, workspace_margin, gensymed_symbol, top_edge_in_workspace;
    Object note_text_box, command_history_text, ab_loop_list_, history_frame;
    Object temp, svref_new_value, free_text_box;
    SI_Long interitem_spacing, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long left_edge_in_workspace;

    x_note_fn_call(214,33);
    workspace = get_and_clear_workspace_for_inspect_command(1,inspect_command);
    if (workspace);
    else
	workspace = make_inspect_workspace(1,inspect_command);
    interitem_spacing = (SI_Long)5L;
    workspace_margin = ISVREF(workspace,(SI_Long)17L);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    left_edge_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    gensymed_symbol = ISVREF(inspect_command,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = interitem_spacing;
    top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    if (Inspect_command_history_list) {
	note_text_box = make_free_text_box(1,tformat_text_string(2,
		string_constant_4,length(Inspect_command_history_list)));
	add_to_workspace(4,note_text_box,workspace,
		FIX(left_edge_in_workspace),top_edge_in_workspace);
	gensymed_symbol = ISVREF(note_text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = interitem_spacing;
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	command_history_text = Nil;
	ab_loop_list_ = Inspect_command_history_list;
	history_frame = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	command_history_text = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	history_frame = make_text_box(Qinspect_history);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(history_frame,Qbox_translation_and_text);
	temp = No_value;
	svref_new_value = gensym_cons_1(temp,
		convert_text_string_to_text(copy_text_string(command_history_text)));
	SVREF(history_frame,FIX((SI_Long)16L)) = svref_new_value;
	reformat_text_box_in_place(1,history_frame);
	add_to_workspace(4,history_frame,workspace,
		FIX(left_edge_in_workspace),top_edge_in_workspace);
	gensymed_symbol = ISVREF(history_frame,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = interitem_spacing;
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	goto next_loop;
      end_loop:;
    }
    else {
	free_text_box = make_free_text_box(1,tformat_text_string(1,
		string_constant_5));
	add_to_workspace(4,free_text_box,workspace,
		FIX(left_edge_in_workspace),top_edge_in_workspace);
    }
    shrink_wrap_workspace(workspace);
    put_inspect_workspace_on_current_detail_pane(workspace);
    return VALUES_1(Nil);
}

/* EXECUTE-COMMAND-FOR-INSPECT-HISTORY */
Object execute_command_for_inspect_history(inspect_history)
    Object inspect_history;
{
    Object temp, inspect_command_string, inspect_command;

    x_note_fn_call(214,34);
    temp = ISVREF(inspect_history,(SI_Long)16L);
    inspect_command_string = convert_text_to_text_string(1,CDR(temp));
    inspect_command = 
	    make_inspect_command_or_signal_error(inspect_command_string);
    reformat_text_box_in_place(1,inspect_command);
    return execute_inspect_command(inspect_command);
}

/* EXECUTE-COMMAND-FOR-INSPECT-COMMAND */
Object execute_command_for_inspect_command(inspect_command)
    Object inspect_command;
{
    x_note_fn_call(214,35);
    return execute_inspect_command(inspect_command);
}

static Object Qexecute_inspect_command;  /* execute-inspect-command */

static Object Qrecompile;          /* recompile */

static Object list_constant_10;    /* # */

static Object Qwrite_to_a_file;    /* write-to-a-file */

static Object Qshow_on_a_workspace;  /* show-on-a-workspace */

static Object Qvisit;              /* visit */

static Object Qdisplay_a_table;    /* display-a-table */

static Object Qdisplay_a_table_columnwise;  /* display-a-table-columnwise */

static Object Qcolumnwise;         /* columnwise */

static Object Qnon_word;           /* non-word */

static Object Qshow_class_hierarchy_on_a_workspace;  /* show-class-hierarchy-on-a-workspace */

static Object Qshow_workspace_hierarchy_on_a_workspace;  /* show-workspace-hierarchy-on-a-workspace */

static Object Qshow_procedure_invocation_hierarchy_on_a_workspace;  /* show-procedure-invocation-hierarchy-on-a-workspace */

static Object Qshow_method_inheritance_path_on_a_workspace;  /* show-method-inheritance-path-on-a-workspace */

static Object Qshow_method_hierarchy_on_a_workspace;  /* show-method-hierarchy-on-a-workspace */

static Object Qshow_module_hierarchy_on_a_workspace;  /* show-module-hierarchy-on-a-workspace */

static Object Qshow_procedure_calling_hierarchy_on_a_workspace;  /* show-procedure-calling-hierarchy-on-a-workspace */

static Object Qshow_procedure_caller_hierarchy_on_a_workspace;  /* show-procedure-caller-hierarchy-on-a-workspace */

static Object Qcheck_for_consistent_modularization;  /* check-for-consistent-modularization */

static Object Qinspect_kb_for_modularity_problems;  /* inspect-kb-for-modularity-problems */

static Object Qwrite_class_hierarchy_to_file;  /* write-class-hierarchy-to-file */

static Object Qversion_control;    /* version-control */

/* EXECUTE-INSPECT-COMMAND */
Object execute_inspect_command(inspect_command)
    Object inspect_command;
{
    Object index_of_top_of_backtrace_stack, temp, svref_arg_2, temp_1, query;
    Object query_handler, query_designations, item_filter;
    Object current_computation_frame, frame_list, write_to_a_file_p;
    volatile Object pathname_for_search_items_qm;
    Object namestring_for_search_items_qm;
    Object ascii_namestring_for_search_items_qm, temp_2, temp_3, temp_4;
    Object temp_5, observance_of_word_boundary_qm, what_to_look_for;
    Object replacement_qm, string_to_look_for, replacement_string_qm;
    Object file_name, class_1;
    char ignore_in_recompile_qm, temp_6;
    Declare_stack_pointer;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(214,36);
    SAVE_STACK();
    index_of_top_of_backtrace_stack = Index_of_top_of_backtrace_stack;
    PUSH_SPECIAL(Index_of_top_of_backtrace_stack,index_of_top_of_backtrace_stack,
	    1);
      if (FIXNUM_LE(FIXNUM_ADD(Index_of_top_of_backtrace_stack,
	      Size_of_basic_backtrace_information),
	      Maximum_index_in_backtrace_stack_for_internal_error)) {
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = FIX((SI_Long)0L);
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Nil;
	  temp = FIXNUM_ADD1(Index_of_top_of_backtrace_stack);
	  Index_of_top_of_backtrace_stack = temp;
	  temp = Backtrace_stack_for_internal_error;
	  svref_arg_2 = Index_of_top_of_backtrace_stack;
	  SVREF(temp,svref_arg_2) = Qexecute_inspect_command;
      }
      temp_1 = ISVREF(inspect_command,(SI_Long)16L);
      query = CAR(temp_1);
      temp_1 = SECOND(query);
      if (CONSP(temp_1)) {
	  temp_1 = SECOND(query);
	  query_handler = FIRST(temp_1);
      }
      else
	  query_handler = SECOND(query);
      cancel_search_state_for_inspect_command_if_necessary(inspect_command);
      cache_inspect_command_history(inspect_command);
      if (member_eql(query_handler,list_constant_3)) {
	  query_designations = THIRD(query);
	  item_filter = copy_for_slot_value(query_designations);
	  ignore_in_recompile_qm = EQ(query_handler,Qrecompile);
	  current_computation_frame = inspect_command;
	  PUSH_SPECIAL(Current_computation_frame,current_computation_frame,0);
	    frame_list = 
		    evaluate_query_to_first_approximation(CAR(item_filter),
		    ignore_in_recompile_qm ? T : Nil);
	  POP_SPECIAL();
	  if (memq_function(query_handler,list_constant_10)) {
	      write_to_a_file_p = Qunbound_in_protected_let;
	      pathname_for_search_items_qm = Qunbound_in_protected_let;
	      namestring_for_search_items_qm = Qunbound_in_protected_let;
	      ascii_namestring_for_search_items_qm = Qunbound_in_protected_let;
	      if (PUSH_UNWIND_PROTECT(0)) {
		  write_to_a_file_p = EQ(query_handler,Qwrite_to_a_file) ? 
			  T : Nil;
		  if (write_to_a_file_p) {
		      temp_1 = SECOND(query);
		      pathname_for_search_items_qm = 
			      make_full_pathname(SECOND(temp_1));
		  }
		  else
		      pathname_for_search_items_qm = Nil;
		  namestring_for_search_items_qm = write_to_a_file_p ? 
			  gensym_namestring_as_text_string(2,
			  pathname_for_search_items_qm,T) : Qnil;
		  ascii_namestring_for_search_items_qm = write_to_a_file_p 
			  ? gensym_namestring(2,
			  pathname_for_search_items_qm,Nil) : Qnil;
		  temp_1 =  !(EQ(query_handler,Qshow_on_a_workspace) || 
			  EQ(query_handler,Qvisit)) ? T : Nil;
		  temp_2 = namestring_for_search_items_qm;
		  temp_3 = ascii_namestring_for_search_items_qm;
		  temp_4 = EQ(query_handler,Qvisit) ? T : Nil;
		  if (EQ(query_handler,Qdisplay_a_table))
		      temp_5 = T;
		  else if (EQ(query_handler,Qdisplay_a_table_columnwise))
		      temp_5 = Qcolumnwise;
		  else
		      temp_5 = Nil;
		  search_items(13,frame_list,item_filter,Nil,Nil,Nil,
			  temp_1,temp_2,temp_3,inspect_command,temp_4,
			  temp_5,
			  copy_list_using_gensym_conses_1(FOURTH(query)),
			  EQ(query_handler,Qrecompile) ? T : Nil);
	      }
	      POP_UNWIND_PROTECT(0);
	      if (pathname_for_search_items_qm) {
		  if ( !EQ(pathname_for_search_items_qm,
			  Qunbound_in_protected_let))
		      reclaim_gensym_pathname(pathname_for_search_items_qm);
	      }
	      CONTINUE_UNWINDING(0);
	  }
	  else {
	      temp_1 = SECOND(query);
	      temp_6 = TRUEP(text_string_p(SECOND(temp_1)));
	      if (temp_6);
	      else {
		  temp_1 = SECOND(query);
		  temp_6 = EQ(SECOND(temp_1),Qnon_word);
	      }
	      if ( !temp_6) {
		  temp_1 = SECOND(query);
		  observance_of_word_boundary_qm = SECOND(temp_1);
	      }
	      else
		  observance_of_word_boundary_qm = Nil;
	      temp_1 = SECOND(query);
	      what_to_look_for = THIRD(temp_1);
	      temp_1 = SECOND(query);
	      replacement_qm = FOURTH(temp_1);
	      string_to_look_for = SYMBOLP(what_to_look_for) ? 
		      copy_symbol_name_parsably(what_to_look_for,Nil) : 
		      what_to_look_for;
	      replacement_string_qm = replacement_qm ? 
		      (SYMBOLP(replacement_qm) ? 
		      copy_symbol_name_parsably(replacement_qm,Nil) : 
		      replacement_qm) : Nil;
	      search_items(12,frame_list,item_filter,string_to_look_for,
		      replacement_string_qm,observance_of_word_boundary_qm,
		      Nil,Nil,Nil,inspect_command,Nil,Nil,
		      copy_list_using_gensym_conses_1(FOURTH(query)));
	      if ( !EQ(string_to_look_for,what_to_look_for))
		  reclaim_text_string(string_to_look_for);
	      if ( !EQ(replacement_string_qm,replacement_qm))
		  reclaim_text_string(replacement_string_qm);
	  }
	  result = reclaim_gensym_list_1(frame_list);
      }
      else if (EQ(query_handler,Qshow_class_hierarchy_on_a_workspace) || 
	      EQ(query_handler,Qshow_workspace_hierarchy_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_workspace_or_class_hierarchy_on_a_workspace(3,
		      THIRD(query),EQ(query_handler,
		      Qshow_class_hierarchy_on_a_workspace) ? T : Nil,
		      inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,
	      Qshow_procedure_invocation_hierarchy_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = graph_detailed_procedures(2,Nil,inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,
		  Qshow_method_inheritance_path_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_method_inheritance_path_for_class_on_a_workspace(3,
		      THIRD(query),FOURTH(query),inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,Qshow_method_hierarchy_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_method_hierarchy_on_a_workspace(2,THIRD(query),
		      inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,
		  Qshow_inspect_command_history_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_inspect_command_history_on_a_workspace(inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,Qshow_module_hierarchy_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_module_hierarchy_on_a_workspace(2,THIRD(query),
		      inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,
	      Qshow_procedure_calling_hierarchy_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_procedure_reference_hierarchy_on_a_workspace(2,
		      THIRD(query),inspect_command);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,
	      Qshow_procedure_caller_hierarchy_on_a_workspace)) {
	  if ( !TRUEP(ISVREF(inspect_command,(SI_Long)21L)))
	      result = show_procedure_reference_hierarchy_on_a_workspace(3,
		      THIRD(query),inspect_command,T);
	  else
	      result = VALUES_1(Nil);
      }
      else if (EQ(query_handler,Qcheck_for_consistent_modularization))
	  result = search_items(15,Nil,Nil,Nil,Nil,Nil,T,Nil,Nil,
		  inspect_command,Nil,Nil,Nil,Nil,
		  Qinspect_kb_for_modularity_problems,
		  gensym_cons_1(inspect_command,Nil));
      else if (EQ(query_handler,Qwrite_class_hierarchy_to_file)) {
	  temp_1 = SECOND(query);
	  file_name = SECOND(temp_1);
	  class_1 = THIRD(query);
	  result = write_class_hierarchy_to_file(file_name,class_1,
		  inspect_command);
      }
      else if (EQ(query_handler,Qversion_control))
	  result = version_control_query(inspect_command,
		  ISVREF(inspect_command,(SI_Long)21L));
      else
	  result = VALUES_1(Qnil);
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* INSPECT-KB-FOR-MODULARITY-PROBLEMS */
Object inspect_kb_for_modularity_problems(inspect_command_qm)
    Object inspect_command_qm;
{
    x_note_fn_call(214,37);
    check_savability_of_kb_in_terms_of_modularity(1,inspect_command_qm);
    return VALUES_1(Nil);
}

static Object Qcell_array_element;  /* cell-array-element */

/* FRAME-MATCHES-ITEM-FILTER-P */
Object frame_matches_item_filter_p(kb_search_state,frame,item_filter)
    Object kb_search_state, frame, item_filter;
{
    Object temp, cell_index, current_computation_frame;
    Object current_block_of_dependent_frame;
    Object current_computation_component_particulars;
    Object truth_value_or_unknown_datum;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,38);
    temp = CAR(item_filter);
    cell_index = THIRD(temp);
    current_computation_frame = kb_search_state;
    PUSH_SPECIAL(Current_computation_frame,current_computation_frame,2);
      current_block_of_dependent_frame = kb_search_state;
      PUSH_SPECIAL(Current_block_of_dependent_frame,current_block_of_dependent_frame,
	      1);
	current_computation_component_particulars = 
		gensym_list_2(Qcell_array_element,cell_index);
	PUSH_SPECIAL(Current_computation_component_particulars,current_computation_component_particulars,
		0);
	  truth_value_or_unknown_datum = 
		  funcall_expression_cell_1(cell_index,frame);
	  reclaim_slot_value(Current_computation_component_particulars);
	  if ( !TRUEP(truth_value_or_unknown_datum))
	      result = VALUES_1(Nil);
	  else
	      result = evaluation_truth_value_is_true_p(truth_value_or_unknown_datum);
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return result;
}

static Object Qcell_array;         /* cell-array */

static Object Qempty_expression_cell;  /* empty-expression-cell */

/* FUNCALL-EXPRESSION-CELL-1 */
Object funcall_expression_cell_1(cell_index,argument_1)
    Object cell_index, argument_1;
{
    Object argument_list, temp, expression_cell;

    x_note_fn_call(214,39);
    argument_list = gensym_cons_1(argument_1,Nil);
    if (FIXNUM_LE(ISVREF(ISVREF(get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
	    Qcell_array,Nil),(SI_Long)3L),(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	temp = 
		ISVREF(get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
		Qcell_array,Nil),(SI_Long)3L);
	expression_cell = ISVREF(temp,IFIX(FIXNUM_ADD(cell_index,
		Managed_array_index_offset)));
    }
    else {
	temp = 
		ISVREF(get_lookup_slot_value_given_default(Current_block_of_dependent_frame,
		Qcell_array,Nil),(SI_Long)3L);
	expression_cell = ISVREF(ISVREF(temp,(IFIX(cell_index) >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),IFIX(cell_index) & 
		(SI_Long)1023L);
    }
    if ( ! !EQ(ISVREF(expression_cell,(SI_Long)2L),Qempty_expression_cell))
	return VALUES_1(Nil);
    else {
	attempt_expression_cell_execution(expression_cell,argument_list,T);
	reclaim_gensym_list_1(argument_list);
	return VALUES_1(ISVREF(expression_cell,(SI_Long)6L));
    }
}

/* EXPRESSION-CELL-UPDATED-FOR-KB-SEARCH-STATE */
Object expression_cell_updated_for_kb_search_state(kb_search_state,
	    g2_cell_array,cell_index,old_value_qm,new_value_qm)
    Object kb_search_state, g2_cell_array, cell_index, old_value_qm;
    Object new_value_qm;
{
    x_note_fn_call(214,40);
    return VALUES_1(Nil);
}

static Object Qname_or_names_for_frame;  /* name-or-names-for-frame */

static Object Qname_for_debugging;  /* name-for-debugging */

/* NAME-FOR-FRAME-P */
Object name_for_frame_p(name,frame)
    Object name, frame;
{
    Object name_or_names_for_frame, temp, sub_class_bit_vector;
    Object gensymed_symbol_3;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(214,41);
    name_or_names_for_frame = get_lookup_slot_value_given_default(frame,
	    Qname_or_names_for_frame,Nil);
    temp = ATOM(name_or_names_for_frame) ? (EQ(name,
	    name_or_names_for_frame) ? T : Nil) : memq_function(name,
	    name_or_names_for_frame);
    if (temp)
	return VALUES_1(temp);
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Block_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    gensymed_symbol_3 = get_lookup_slot_value_given_default(frame,
		    Qname_for_debugging,Nil);
	    if (text_string_p(gensymed_symbol_3))
		return string_eq_w(gensymed_symbol_3,SYMBOLP(name) ? 
			symbol_name_text_string(name) : name);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
}

Object Inspection_instance_counter = UNBOUND;

static Object Qtemporary_workspace;  /* temporary-workspace */

static Object string_constant_6;   /* "INSPECT-~d" */

/* MAKE-INSPECT-WORKSPACE */
Object make_inspect_workspace varargs_1(int, n)
{
    Object inspect_command_qm;
    Object show_name_box_qm, workspace, inspection_instance_counter_new_value;
    Object gensymed_symbol, temp;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,42);
    INIT_ARGS_nonrelocating();
    inspect_command_qm = REQUIRED_ARG_nonrelocating();
    show_name_box_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workspace = make_workspace(7,Qtemporary_workspace,Nil,Nil,
	    FIX((SI_Long)5L),Nil,Nil,Current_workstation);
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(workspace,Qname_or_names_for_frame);
    inspection_instance_counter_new_value = 
	    FIXNUM_ADD1(Inspection_instance_counter);
    Inspection_instance_counter = inspection_instance_counter_new_value;
    set_lookup_slot_value_1(workspace,Qname_or_names_for_frame,
	    intern_text_string(1,tformat_text_string(2,string_constant_6,
	    Inspection_instance_counter)));
    if (show_name_box_qm)
	update_name_box(workspace);
    if (inspect_command_qm) {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(workspace,(SI_Long)17L));
	temp = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(ISVREF(workspace,(SI_Long)17L));
	add_to_workspace(4,inspect_command_qm,workspace,temp,
		FIX(gensymed_symbol_1 + gensymed_symbol_2));
    }
    return VALUES_1(workspace);
}

/* WRITE-CLASS-HIERARCHY-TO-FILE */
Object write_class_hierarchy_to_file(file_name,class_1,query_command)
    Object file_name, class_1, query_command;
{
    volatile Object pathname_for_write_hierarchy;
    volatile Object namestring_for_write_hierarchy;
    Object inner_abort_level_tag;
    volatile Object output_file_stream_qm;
    Object transcode_text_conversion_style;
    Declare_stack_pointer;
    Declare_catch(3);
    Declare_special(1);
    XDeclare_area(1);
    Object result;

    x_note_fn_call(214,43);
    SAVE_STACK();
    pathname_for_write_hierarchy = Qunbound_in_protected_let;
    namestring_for_write_hierarchy = Qunbound_in_protected_let;
    if (PUSH_UNWIND_PROTECT(2)) {
	pathname_for_write_hierarchy = make_full_pathname(file_name);
	namestring_for_write_hierarchy = gensym_namestring(1,
		pathname_for_write_hierarchy);
	if (PUSH_AREA(Dynamic_area,0)) {
	    if (PUSH_CATCH(Qabort_level_3,1)) {
		inner_abort_level_tag = Qabort_level_3;
		PUSH_SPECIAL(Inner_abort_level_tag,inner_abort_level_tag,0);
		  output_file_stream_qm = Qunbound_in_protected_let;
		  if (PUSH_UNWIND_PROTECT(0)) {
		      output_file_stream_qm = 
			      g2_stream_open_for_output(namestring_for_write_hierarchy);
		      if (output_file_stream_qm) {
			  transcode_text_conversion_style = 
				  get_lookup_slot_value_given_default(Language_parameters,
				  Qtext_conversion_style,Nil) ? 
				  get_text_conversion_style_structure_per_name(get_lookup_slot_value_given_default(Language_parameters,
				  Qtext_conversion_style,Nil)) : Nil;
			  if (transcode_text_conversion_style);
			  else
			      transcode_text_conversion_style = 
				      Default_text_conversion_style;
			  write_inspect_file_header(2,
				  output_file_stream_qm,query_command);
			  SAVE_VALUES(show_inheritance_tree(3,class_1,
				  output_file_stream_qm,
				  transcode_text_conversion_style));
		      }
		      else
			  SAVE_VALUES(VALUES_1(Nil));
		  }
		  POP_UNWIND_PROTECT(0);
		  if (output_file_stream_qm) {
		      if ( !EQ(output_file_stream_qm,
			      Qunbound_in_protected_let))
			  g2_stream_close(output_file_stream_qm);
		  }
		  CONTINUE_UNWINDING(0);
		  result = RESTORE_VALUES();
		POP_SPECIAL();
	    }
	    else
		result = CATCH_VALUES();
	    POP_CATCH(1);
	}
	POP_AREA(0);
	SAVE_VALUES(result);
    }
    POP_UNWIND_PROTECT(2);
    if (namestring_for_write_hierarchy) {
	if ( !EQ(namestring_for_write_hierarchy,Qunbound_in_protected_let))
	    reclaim_text_string(namestring_for_write_hierarchy);
    }
    if (pathname_for_write_hierarchy) {
	if ( !EQ(pathname_for_write_hierarchy,Qunbound_in_protected_let))
	    reclaim_gensym_pathname(pathname_for_write_hierarchy);
    }
    CONTINUE_UNWINDING(2);
    result = RESTORE_VALUES();
    RESTORE_STACK();
    return result;
}

/* SHOW-INHERITANCE-TREE */
Object show_inheritance_tree varargs_1(int, n)
{
    Object class_1;
    Object destination_g2_stream_qm, transcode_text_conversion_style_if_stream;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,44);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    destination_g2_stream_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    transcode_text_conversion_style_if_stream = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    return show_inheritance_tree_1(4,class_1,FIX((SI_Long)0L),
	    destination_g2_stream_qm,
	    transcode_text_conversion_style_if_stream);
}

static Object array_constant_5;    /* # */

static Object string_constant_7;   /* " -- ~d instance~a" */

static Object string_constant_8;   /* "s" */

static Object string_constant_9;   /* "" */

/* SHOW-INHERITANCE-TREE-1 */
Object show_inheritance_tree_1 varargs_1(int, n)
{
    Object class_1, depth, destination_g2_stream_qm;
    Object transcode_text_conversion_style_if_stream, temp, schar_arg_2;
    Object schar_new_value, string_1, number_of_instances, text_string;
    Object inferior_class, ab_loop_list_;
    SI_Long tab, ab_loop_bind_;
    char thing;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,45);
    INIT_ARGS_nonrelocating();
    class_1 = REQUIRED_ARG_nonrelocating();
    depth = REQUIRED_ARG_nonrelocating();
    destination_g2_stream_qm = REQUIRED_ARG_nonrelocating();
    transcode_text_conversion_style_if_stream = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    END_ARGS_nonrelocating();
    if (destination_g2_stream_qm)
	export_and_emit_text_line(array_constant_2,
		transcode_text_conversion_style_if_stream,
		destination_g2_stream_qm);
    else if (EQ(Current_twriting_output_type,Qwide_string)) {
	thing = '\n';
	twrite_wide_character(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
    }
    else {
	if ( !FIXNUM_LT(Fill_pointer_for_current_gensym_string,
		Total_length_of_current_gensym_string))
	    extend_current_gensym_string(0);
	temp = Current_gensym_string;
	schar_arg_2 = Fill_pointer_for_current_gensym_string;
	thing = '\n';
	schar_new_value = CODE_CHAR(CHARACTERP(CHR(thing)) ? 
		CHAR_CODE(CHR(thing)) : CHR(thing));
	SET_SCHAR(temp,schar_arg_2,schar_new_value);
	temp = FIXNUM_ADD1(Fill_pointer_for_current_gensym_string);
	Fill_pointer_for_current_gensym_string = temp;
    }
    string_1 = array_constant_5;
    tab = (SI_Long)1L;
    ab_loop_bind_ = IFIX(depth);
  next_loop:
    if (tab > ab_loop_bind_)
	goto end_loop;
    if (destination_g2_stream_qm)
	export_and_emit_text_string(string_1,
		transcode_text_conversion_style_if_stream,
		destination_g2_stream_qm);
    else
	twrite_general_string(string_1);
    tab = tab + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    if (destination_g2_stream_qm)
	export_and_emit_text_string(symbol_name_text_string(class_1),
		transcode_text_conversion_style_if_stream,
		destination_g2_stream_qm);
    else
	twrite_general_string(symbol_name_text_string(class_1));
    number_of_instances = 
	    compute_number_of_instances_specific_to_class(class_1);
    if (IFIX(number_of_instances) > (SI_Long)0L) {
	text_string = tformat_text_string(3,string_constant_7,
		number_of_instances,IFIX(number_of_instances) > 
		(SI_Long)1L ? string_constant_8 : string_constant_9);
	if (destination_g2_stream_qm)
	    export_and_emit_text_string(text_string,
		    transcode_text_conversion_style_if_stream,
		    destination_g2_stream_qm);
	else
	    twrite_general_string(text_string);
    }
    inferior_class = Nil;
    ab_loop_list_ = lookup_global_or_kb_specific_property_value(class_1,
	    Inferior_classes_gkbprop);
  next_loop_1:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_1;
    inferior_class = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    show_inheritance_tree_1(4,inferior_class,FIXNUM_ADD1(depth),
	    destination_g2_stream_qm,
	    transcode_text_conversion_style_if_stream);
    goto next_loop_1;
  end_loop_1:
    return VALUES_1(Qnil);
}

/* COMPUTE-NUMBER-OF-INSTANCES-SPECIFIC-TO-CLASS */
Object compute_number_of_instances_specific_to_class(class_1)
    Object class_1;
{
    Object count_so_far, next_frame_qm;

    x_note_fn_call(214,46);
    count_so_far = FIX((SI_Long)0L);
    next_frame_qm = lookup_kb_specific_property_value(class_1,
	    Instances_specific_to_this_class_kbprop);
  next_loop:
    if ( !TRUEP(next_frame_qm))
	goto end_loop;
    count_so_far = FIXNUM_ADD1(count_so_far);
    next_frame_qm = ISVREF(next_frame_qm,(SI_Long)6L);
    goto next_loop;
  end_loop:;
    return VALUES_1(count_so_far);
}

static Object Qitem;               /* item */

static Object Qsymbol_properties_hash_table;  /* symbol-properties-hash-table */

static Object Qab_gensym;          /* gensym */

static Object Qhash_symbol_or_frame;  /* hash-symbol-or-frame */

static Object Qsxhashw;            /* sxhashw */

static Object Qhorizontal;         /* horizontal */

static Object Qvertical;           /* vertical */

static Object Qsubclasses_of_class_for_graph_display;  /* subclasses-of-class-for-graph-display */

static Object Qsubcomponents_of_workspace_or_item_for_display;  /* subcomponents-of-workspace-or-item-for-display */

static Object Qshort_representation_of_symbol_or_frame;  /* short-representation-of-symbol-or-frame */

static Object Qshort_representation_of_symbol_or_frame_or_top_level;  /* short-representation-of-symbol-or-frame-or-top-level */

static Object string_constant_10;  /* "Cannot show the class hierarchy for ~a, since it is not ~a." */

static Object string_constant_11;  /* "a subclass of item" */

static Object string_constant_12;  /* "a class" */

static Object string_constant_13;  /* "Cannot show the workspace hierarchy for ~a, since it is not ~
				    *               the name of an item."
				    */

/* SHOW-WORKSPACE-OR-CLASS-HIERARCHY-ON-A-WORKSPACE */
Object show_workspace_or_class_hierarchy_on_a_workspace varargs_1(int, n)
{
    Object class_or_item_or_workspace_name_qm, class_case_qm;
    Object inspect_command_qm, item_qm, class_1;
    Object workspace_with_inspect_command_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_4, temp, temp_1, new_cons;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, sub_class_bit_vector, temp_3, temp_4, temp_5;
    Object temp_6, temp_7, temp_8, temp_9, temp_10;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_5;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,47);
    INIT_ARGS_nonrelocating();
    class_or_item_or_workspace_name_qm = REQUIRED_ARG_nonrelocating();
    class_case_qm = REQUIRED_ARG_nonrelocating();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    item_qm =  !TRUEP(class_case_qm) ? (class_or_item_or_workspace_name_qm 
	    ? get_instance_with_name_if_any(Qitem,
	    class_or_item_or_workspace_name_qm) : Nil) : Nil;
    class_1 = class_case_qm ? class_or_item_or_workspace_name_qm : Nil;
    workspace_with_inspect_command_qm = inspect_command_qm ? 
	    get_and_clear_workspace_for_inspect_command(1,
	    inspect_command_qm) : Nil;
    if (class_case_qm) {
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = class_1;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(class_1) & 
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
	    gensymed_symbol = class_1;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
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
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
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
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
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
	temp_2 = gensymed_symbol ? TRUEP(ISVREF(gensymed_symbol,
		(SI_Long)16L)) : TRUEP(Qnil);
    }
    else {
	temp_2 =  !TRUEP(class_or_item_or_workspace_name_qm);
	if (temp_2);
	else
	    temp_2 = TRUEP(item_qm);
    }
    if (temp_2) {
	if (class_case_qm)
	    temp_1 = Qitem;
	else if ( !TRUEP(item_qm))
	    temp_1 = Nil;
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(item_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
	    sub_class_vector_index = superior_class_bit_number >>  -  - 
		    (SI_Long)3L;
	    if (sub_class_vector_index < 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		gensymed_symbol_2 = UBYTE_8_ISAREF_1(sub_class_bit_vector,
			sub_class_vector_index);
		gensymed_symbol_3 = (SI_Long)1L;
		gensymed_symbol_5 = superior_class_bit_number & (SI_Long)7L;
		gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_5;
		gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		temp_2 = (SI_Long)0L < gensymed_symbol_2;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2 ? TRUEP(ISVREF(item_qm,(SI_Long)18L)) : TRUEP(Nil)) {
		temp_1 = ISVREF(item_qm,(SI_Long)18L);
		temp_1 = CAR(temp_1);
	    }
	    else
		temp_1 = item_qm;
	}
	temp = IDENTITY(Qhash_symbol_or_frame);
	if (temp);
	else
	    temp = Qsxhashw;
	temp_3 = IDENTITY(Qhorizontal);
	if (temp_3);
	else
	    temp_3 = Qvertical;
	temp_4 = IDENTITY(FIX((SI_Long)1L));
	if (temp_4);
	else
	    temp_4 = FIX((SI_Long)50L);
	temp_5 = IDENTITY(FIX((SI_Long)50L));
	if (temp_5);
	else
	    temp_5 = FIX((SI_Long)50L);
	temp_6 =  !TRUEP(workspace_with_inspect_command_qm) ? 
		Current_workstation_detail_pane : Nil;
	temp_7 = IDENTITY(Nil);
	if (temp_7);
	else
	    temp_7 = Qtemporary_workspace;
	temp_8 = workspace_with_inspect_command_qm;
	if (temp_8);
	else
	    temp_8 = make_inspect_workspace(1,inspect_command_qm);
	if (inspect_command_qm) {
	    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_9 = gensymed_symbol;
	}
	else
	    temp_9 = Nil;
	if (inspect_command_qm) {
	    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    gensymed_symbol_3 = (SI_Long)5L;
	    temp_10 = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	}
	else
	    temp_10 = Nil;
	reclaim_graph_display_1(graph_frame_hierarchy_function(temp_1,
		class_case_qm ? Qsubclasses_of_class_for_graph_display : 
		Qsubcomponents_of_workspace_or_item_for_display,
		class_case_qm ? class_1 : Nil,class_case_qm ? 
		Qshort_representation_of_symbol_or_frame : 
		Qshort_representation_of_symbol_or_frame_or_top_level,temp,
		temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,temp_9,temp_10));
    }
    else if (class_case_qm) {
	if (SYMBOLP(class_1)) {
	    gensymed_symbol = CDR(Symbol_properties_table);
	    gensymed_symbol_1 = class_1;
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(class_1) & 
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
		gensymed_symbol = class_1;
		temp = Symbol_properties_table;
		temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
		gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,
			Nil,T,gensymed_symbol,temp_1,gensymed_symbol_1);
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
	    temp_2 = TRUEP(resulting_value);
	}
	else
	    temp_2 = TRUEP(Nil);
	notify_user(3,string_constant_10,class_1,temp_2 ? 
		string_constant_11 : string_constant_12);
    }
    else
	notify_user(2,string_constant_13,class_or_item_or_workspace_name_qm);
    if (workspace_with_inspect_command_qm)
	return shrink_wrap_workspace(workspace_with_inspect_command_qm);
    else
	return VALUES_1(Nil);
}

static Object Qclass_definition;   /* class-definition */

/* SUBCLASSES-OF-CLASS-FOR-GRAPH-DISPLAY */
Object subclasses_of_class_for_graph_display(definition_or_class,
	    class_of_interest)
    Object definition_or_class, class_of_interest;
{
    Object current_class_name, inferior_classes, gensymed_symbol;
    Object current_class_is_subclass_qm, class_1, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, temp_1;
    char temp;

    x_note_fn_call(214,48);
    current_class_name = SYMBOLP(definition_or_class) ? 
	    definition_or_class : ISVREF(definition_or_class,(SI_Long)20L);
    inferior_classes = 
	    lookup_global_or_kb_specific_property_value(current_class_name,
	    Inferior_classes_gkbprop);
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(current_class_name,
	    Class_description_gkbprop);
    current_class_is_subclass_qm = gensymed_symbol ? 
	    memq_function(class_of_interest,ISVREF(gensymed_symbol,
	    (SI_Long)2L)) : Nil;
    class_1 = Nil;
    ab_loop_list_ = inferior_classes;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp = TRUEP(current_class_is_subclass_qm);
    if (temp);
    else
	temp = EQ(class_1,class_of_interest);
    if (temp);
    else {
	gensymed_symbol = 
		lookup_global_or_kb_specific_property_value(class_of_interest,
		Class_description_gkbprop);
	temp = gensymed_symbol ? TRUEP(memq_function(class_1,
		ISVREF(gensymed_symbol,(SI_Long)2L))) : TRUEP(Nil);
    }
    if (temp) {
	temp_1 = get_instance_with_name_if_any(Qclass_definition,class_1);
	if (temp_1);
	else
	    temp_1 = class_1;
	ab_loopvar__2 = gensym_cons_1(temp_1,Nil);
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

static Object Qnext_methods_for_graph_display;  /* next-methods-for-graph-display */

static Object string_constant_14;  /* "There are no methods defined on the class hierarchy for ~a." */

static Object string_constant_15;  /* "There are no ~a methods defined on the class hierarchy for ~a." */

static Object string_constant_16;  /* "Cannot show the method hierarchy for ~a because it is not ~
				    *           a defined class."
				    */

/* SHOW-METHOD-INHERITANCE-PATH-FOR-CLASS-ON-A-WORKSPACE */
Object show_method_inheritance_path_for_class_on_a_workspace varargs_1(int, n)
{
    Object class_of_interest, method_or_class_name;
    Object inspect_command_qm, gensymed_symbol, gensymed_symbol_1;
    Object gensymed_symbol_4, temp, temp_1, new_cons, global_properties;
    Object kb_properties, kb_specific_value, resulting_value, class_1;
    Object class_description, ab_loop_list_, ab_loop_it_;
    Object workspace_with_inspect_command_qm, extra_arg_for_graphing, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, temp_8, temp_9, temp_10;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,49);
    INIT_ARGS_nonrelocating();
    class_of_interest = REQUIRED_ARG_nonrelocating();
    method_or_class_name = REQUIRED_ARG_nonrelocating();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SYMBOLP(class_of_interest)) {
	gensymed_symbol = CDR(Symbol_properties_table);
	gensymed_symbol_1 = class_of_interest;
	gensymed_symbol_2 = SXHASH_SYMBOL_1(class_of_interest) & 
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
	    gensymed_symbol = class_of_interest;
	    temp = Symbol_properties_table;
	    temp_1 = FIX(SXHASH_SYMBOL_1(gensymed_symbol) & 
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
	    gensymed_symbol = set_balanced_binary_tree_entry(temp,Qeq,Nil,
		    T,gensymed_symbol,temp_1,gensymed_symbol_1);
	}
	global_properties = gensymed_symbol;
	gensymed_symbol = CDR(global_properties);
	gensymed_symbol_1 = Current_kb_specific_property_list_property_name;
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
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
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
	    gensymed_symbol_2 = SXHASH_SYMBOL_1(Class_description_gkbprop) 
		    & IFIX(Most_positive_fixnum);
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
	temp_2 = TRUEP(resulting_value);
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (EQ(class_of_interest,method_or_class_name)) {
	    class_1 = Nil;
	    class_description = 
		    lookup_global_or_kb_specific_property_value(class_of_interest,
		    Class_description_gkbprop);
	    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	    ab_loop_it_ = Nil;
	  next_loop_8:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_8;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = lookup_kb_specific_property_value(class_1,
		    Procedure_methods_of_class_kbprop);
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_9;
	    }
	    goto next_loop_8;
	  end_loop_8:
	    temp_2 = TRUEP(Qnil);
	  end_9:;
	}
	else {
	    class_1 = Nil;
	    class_description = 
		    lookup_global_or_kb_specific_property_value(class_of_interest,
		    Class_description_gkbprop);
	    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
	    ab_loop_it_ = Nil;
	  next_loop_9:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_9;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    ab_loop_it_ = 
		    get_named_procedure_methods_for_class(method_or_class_name,
		    class_1);
	    if (ab_loop_it_) {
		temp_2 = TRUEP(ab_loop_it_);
		goto end_10;
	    }
	    goto next_loop_9;
	  end_loop_9:
	    temp_2 = TRUEP(Qnil);
	  end_10:;
	}
	if (temp_2) {
	    workspace_with_inspect_command_qm = inspect_command_qm ? 
		    get_and_clear_workspace_for_inspect_command(1,
		    inspect_command_qm) : Nil;
	    extra_arg_for_graphing = EQ(class_of_interest,
		    method_or_class_name) ? class_of_interest : 
		    gensym_list_2(class_of_interest,method_or_class_name);
	    temp_1 = get_instance_with_name_if_any(Qclass_definition,
		    class_of_interest);
	    if (temp_1);
	    else
		temp_1 = class_of_interest;
	    temp = IDENTITY(Qhash_symbol_or_frame);
	    if (temp);
	    else
		temp = Qsxhashw;
	    temp_3 = IDENTITY(Qhorizontal);
	    if (temp_3);
	    else
		temp_3 = Qvertical;
	    temp_4 = IDENTITY(FIX((SI_Long)1L));
	    if (temp_4);
	    else
		temp_4 = FIX((SI_Long)50L);
	    temp_5 = IDENTITY(FIX((SI_Long)25L));
	    if (temp_5);
	    else
		temp_5 = FIX((SI_Long)50L);
	    temp_6 =  !TRUEP(workspace_with_inspect_command_qm) ? 
		    Current_workstation_detail_pane : Nil;
	    temp_7 = IDENTITY(Nil);
	    if (temp_7);
	    else
		temp_7 = Qtemporary_workspace;
	    temp_8 = workspace_with_inspect_command_qm;
	    if (temp_8);
	    else
		temp_8 = make_inspect_workspace(1,inspect_command_qm);
	    if (inspect_command_qm) {
		gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)0L) : FIX((SI_Long)0L);
		temp_9 = gensymed_symbol;
	    }
	    else
		temp_9 = Nil;
	    if (inspect_command_qm) {
		gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
		gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
			(SI_Long)3L) : FIX((SI_Long)0L);
		gensymed_symbol_2 = IFIX(gensymed_symbol);
		gensymed_symbol_3 = (SI_Long)5L;
		temp_10 = FIX(gensymed_symbol_2 + gensymed_symbol_3);
	    }
	    else
		temp_10 = Nil;
	    reclaim_graph_display_1(graph_frame_hierarchy_function(temp_1,
		    Qnext_methods_for_graph_display,extra_arg_for_graphing,
		    Qshort_representation_of_symbol_or_frame,temp,temp_3,
		    temp_4,temp_5,temp_6,temp_7,temp_8,temp_9,temp_10));
	    if (workspace_with_inspect_command_qm)
		shrink_wrap_workspace(workspace_with_inspect_command_qm);
	    if (CONSP(extra_arg_for_graphing))
		return reclaim_gensym_list_1(extra_arg_for_graphing);
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(class_of_interest,method_or_class_name))
	    return notify_user(2,string_constant_14,class_of_interest);
	else
	    return notify_user(3,string_constant_15,method_or_class_name,
		    class_of_interest);
    }
    else
	return notify_user(2,string_constant_16,class_of_interest);
}

static Object Qmethod_declaration;  /* method-declaration */

/* NEXT-METHODS-FOR-GRAPH-DISPLAY */
Object next_methods_for_graph_display(frame_or_name,class_name_or_list)
    Object frame_or_name, class_name_or_list;
{
    Object query_class, specific_method_of_interest_qm, class_description;
    Object class_inheritance_path, x2, sub_class_bit_vector, gensymed_symbol_3;
    Object gensymed_symbol_4, gensymed_symbol_5, temp_1, temp_2, new_cons;
    Object global_properties, kb_properties, kb_specific_value;
    Object resulting_value, method_name_list, class_1, ab_loop_list_;
    Object class_methods, method_name, ab_loop_list__1, ab_loop_desetq_;
    Object cons_1, cons_after_which_to_insert_method_name, cdr_new_value;
    Object method, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object next_methods_to_return, argument_count, class_for_method;
    Object methods_for_this_class_qm;
    Object method_with_correct_number_of_arguments_qm;
    Object list_of_argument_counts_represented, next_methods_to_return_qm;
    Object cons_after_which_to_insert_method;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,50);
    query_class = CONSP(class_name_or_list) ? M_CAR(class_name_or_list) : 
	    class_name_or_list;
    specific_method_of_interest_qm = CONSP(class_name_or_list) ? 
	    M_CAR(M_CDR(class_name_or_list)) : Qnil;
    class_description = 
	    lookup_global_or_kb_specific_property_value(query_class,
	    Class_description_gkbprop);
    class_inheritance_path = ISVREF(class_description,(SI_Long)2L);
    if (SIMPLE_VECTOR_P(frame_or_name) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_name)) > (SI_Long)2L 
	    &&  !EQ(ISVREF(frame_or_name,(SI_Long)1L),
		Qavailable_frame_vector)) {
	x2 = ISVREF(frame_or_name,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = ISVREF(ISVREF(frame_or_name,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Class_definition_class_description,(SI_Long)18L));
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
    if (temp);
    else if (SYMBOLP(frame_or_name)) {
	gensymed_symbol_3 = CDR(Symbol_properties_table);
	gensymed_symbol_4 = frame_or_name;
	gensymed_symbol = SXHASH_SYMBOL_1(frame_or_name) & 
		IFIX(Most_positive_fixnum);
	gensymed_symbol_1 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_3))
	    goto end_loop;
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_1)
	    gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_1)
	    gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
	else {
	    gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)3L);
	    gensymed_symbol_5 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_3))
		goto end_loop_1;
	    gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol_3));
	    if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
		gensymed_symbol_3 = M_CDR(M_CAR(gensymed_symbol_3));
		goto end_1;
	    }
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
	    goto next_loop_1;
	  end_loop_1:
	    gensymed_symbol_3 = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	gensymed_symbol_3 = Qnil;
      end_2:;
	if ( !TRUEP(gensymed_symbol_3)) {
	    gensymed_symbol_3 = frame_or_name;
	    temp_1 = Symbol_properties_table;
	    temp_2 = FIX(SXHASH_SYMBOL_1(gensymed_symbol_3) & 
		    IFIX(Most_positive_fixnum));
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_4 = new_cons;
	    }
	    else
		gensymed_symbol_4 = Nil;
	    if ( !TRUEP(gensymed_symbol_4))
		gensymed_symbol_4 = replenish_gensym_cons_pool();
	    M_CAR(gensymed_symbol_4) = Qsymbol_properties_hash_table;
	    M_CDR(gensymed_symbol_4) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_4,Qab_gensym);
	    gensymed_symbol_3 = set_balanced_binary_tree_entry(temp_1,Qeq,
		    Nil,T,gensymed_symbol_3,temp_2,gensymed_symbol_4);
	}
	global_properties = gensymed_symbol_3;
	gensymed_symbol_3 = CDR(global_properties);
	gensymed_symbol_4 = Current_kb_specific_property_list_property_name;
	gensymed_symbol = 
		SXHASH_SYMBOL_1(Current_kb_specific_property_list_property_name) 
		& IFIX(Most_positive_fixnum);
	gensymed_symbol_1 = (SI_Long)0L;
      next_loop_2:
	if ( !TRUEP(gensymed_symbol_3))
	    goto end_loop_2;
	gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_1)
	    gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_1)
	    gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
	else {
	    gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)3L);
	    gensymed_symbol_5 = Nil;
	  next_loop_3:
	    if ( !TRUEP(gensymed_symbol_3))
		goto end_loop_3;
	    gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol_3));
	    if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
		kb_properties = M_CDR(M_CAR(gensymed_symbol_3));
		goto end_3;
	    }
	    gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
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
	    gensymed_symbol_3 = CDR(kb_properties);
	    gensymed_symbol_4 = Class_description_gkbprop;
	    gensymed_symbol = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_1 = (SI_Long)0L;
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol_3))
		goto end_loop_4;
	    gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)0L));
	    if (gensymed_symbol < gensymed_symbol_1)
		gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
	    else if (gensymed_symbol > gensymed_symbol_1)
		gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
	    else {
		gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)3L);
		gensymed_symbol_5 = Nil;
	      next_loop_5:
		if ( !TRUEP(gensymed_symbol_3))
		    goto end_loop_5;
		gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol_3));
		if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
		    kb_specific_value = M_CDR(M_CAR(gensymed_symbol_3));
		    goto end_5;
		}
		gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
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
	    gensymed_symbol_3 = CDR(global_properties);
	    gensymed_symbol_4 = Class_description_gkbprop;
	    gensymed_symbol = SXHASH_SYMBOL_1(Class_description_gkbprop) & 
		    IFIX(Most_positive_fixnum);
	    gensymed_symbol_1 = (SI_Long)0L;
	  next_loop_6:
	    if ( !TRUEP(gensymed_symbol_3))
		goto end_loop_6;
	    gensymed_symbol_1 = IFIX(ISVREF(gensymed_symbol_3,(SI_Long)0L));
	    if (gensymed_symbol < gensymed_symbol_1)
		gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)1L);
	    else if (gensymed_symbol > gensymed_symbol_1)
		gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)2L);
	    else {
		gensymed_symbol_3 = ISVREF(gensymed_symbol_3,(SI_Long)3L);
		gensymed_symbol_5 = Nil;
	      next_loop_7:
		if ( !TRUEP(gensymed_symbol_3))
		    goto end_loop_7;
		gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol_3));
		if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
		    resulting_value = M_CDR(M_CAR(gensymed_symbol_3));
		    goto end_7;
		}
		gensymed_symbol_3 = M_CDR(gensymed_symbol_3);
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
	temp = TRUEP(resulting_value);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	if (specific_method_of_interest_qm) {
	    temp_2 = get_instance_with_name_if_any(Qmethod_declaration,
		    specific_method_of_interest_qm);
	    if (temp_2);
	    else
		temp_2 = specific_method_of_interest_qm;
	    return gensym_cons_1(temp_2,Nil);
	}
	else {
	    method_name_list = Nil;
	    class_1 = Nil;
	    ab_loop_list_ = class_inheritance_path;
	    class_methods = Nil;
	  next_loop_8:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_8;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    class_methods = lookup_kb_specific_property_value(class_1,
		    Procedure_methods_of_class_kbprop);
	    method_name = Nil;
	    ab_loop_list__1 = class_methods;
	    ab_loop_desetq_ = Nil;
	  next_loop_9:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_9;
	    ab_loop_desetq_ = M_CAR(ab_loop_list__1);
	    method_name = CAR(ab_loop_desetq_);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    if ( !TRUEP(memq_function(method_name,method_name_list))) {
		if ( !TRUEP(method_name_list))
		    method_name_list = gensym_cons_1(method_name,Nil);
		else {
		    temp_2 = symbol_name_text_string(method_name);
		    if (string_lesspw(temp_2,
			    symbol_name_text_string(M_CAR(method_name_list))))
			method_name_list = gensym_cons_1(method_name,
				method_name_list);
		    else {
			cons_1 = method_name_list;
		      next_loop_10:
			if ( !TRUEP(cons_1))
			    goto end_loop_10;
			temp_2 = symbol_name_text_string(method_name);
			if (string_greaterpw(temp_2,
				symbol_name_text_string(M_CAR(cons_1)))) {
			    temp =  !TRUEP(CDR(cons_1));
			    if (temp);
			    else {
				temp_2 = symbol_name_text_string(method_name);
				temp = TRUEP(string_lesspw(temp_2,
					symbol_name_text_string(M_CAR(M_CDR(cons_1)))));
			    }
			}
			else
			    temp = TRUEP(Nil);
			if (temp) {
			    cons_after_which_to_insert_method_name = cons_1;
			    goto end_9;
			}
			cons_1 = M_CDR(cons_1);
			goto next_loop_10;
		      end_loop_10:
			cons_after_which_to_insert_method_name = Qnil;
		      end_9:;
			cdr_new_value = gensym_cons_1(method_name,
				CDR(cons_after_which_to_insert_method_name));
			M_CDR(cons_after_which_to_insert_method_name) = 
				cdr_new_value;
		    }
		}
	    }
	    goto next_loop_9;
	  end_loop_9:;
	    goto next_loop_8;
	  end_loop_8:
	    method = Nil;
	    ab_loop_list_ = method_name_list;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_11:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_11;
	    method = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    temp_2 = get_instance_with_name_if_any(Qmethod_declaration,method);
	    if (temp_2);
	    else
		temp_2 = method;
	    ab_loopvar__2 = gensym_cons_1(temp_2,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_11;
	  end_loop_11:
	    next_methods_to_return = ab_loopvar_;
	    goto end_10;
	    next_methods_to_return = Qnil;
	  end_10:;
	    reclaim_gensym_list_1(method_name_list);
	    return VALUES_1(next_methods_to_return);
	    return VALUES_1(Qnil);
	}
    }
    else {
	if (SIMPLE_VECTOR_P(frame_or_name) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_name)) > 
		(SI_Long)2L &&  !EQ(ISVREF(frame_or_name,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(frame_or_name,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(frame_or_name,
		    (SI_Long)1L),(SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Method_class_description,(SI_Long)18L));
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
	    argument_count = ISVREF(frame_or_name,(SI_Long)23L);
	    method_name = ISVREF(frame_or_name,(SI_Long)30L);
	    class_for_method = ISVREF(frame_or_name,(SI_Long)31L);
	    class_1 = Nil;
	    temp_2 = memq_function(class_for_method,class_inheritance_path);
	    ab_loop_list_ = CDR(temp_2);
	    methods_for_this_class_qm = Nil;
	    method_with_correct_number_of_arguments_qm = Nil;
	  next_loop_12:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_12;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    methods_for_this_class_qm = 
		    get_named_procedure_methods_for_class(method_name,class_1);
	    if (methods_for_this_class_qm) {
		method = Nil;
		ab_loop_list__1 = M_CDR(methods_for_this_class_qm);
	      next_loop_13:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_13;
		method = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		if (EQ(ISVREF(method,(SI_Long)23L),argument_count)) {
		    method_with_correct_number_of_arguments_qm = method;
		    goto end_11;
		}
		goto next_loop_13;
	      end_loop_13:
		method_with_correct_number_of_arguments_qm = Qnil;
	      end_11:;
	    }
	    else
		method_with_correct_number_of_arguments_qm = Nil;
	    if (method_with_correct_number_of_arguments_qm)
		return gensym_cons_1(method_with_correct_number_of_arguments_qm,
			Nil);
	    goto next_loop_12;
	  end_loop_12:
	    return VALUES_1(Qnil);
	}
	else {
	    list_of_argument_counts_represented = Nil;
	    next_methods_to_return_qm = Nil;
	    if (SIMPLE_VECTOR_P(frame_or_name) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frame_or_name)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(frame_or_name,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(frame_or_name,(SI_Long)1L);
		temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp = TRUEP(Nil);
	    method_name = temp ? 
		    get_lookup_slot_value_given_default(frame_or_name,
		    Qname_or_names_for_frame,Nil) : frame_or_name;
	    class_1 = Nil;
	    ab_loop_list_ = class_inheritance_path;
	    methods_for_this_class_qm = Nil;
	  next_loop_14:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_14;
	    class_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    methods_for_this_class_qm = 
		    get_named_procedure_methods_for_class(method_name,class_1);
	    if (methods_for_this_class_qm) {
		method = Nil;
		ab_loop_list__1 = M_CDR(methods_for_this_class_qm);
		argument_count = Nil;
	      next_loop_15:
		if ( !TRUEP(ab_loop_list__1))
		    goto end_loop_15;
		method = M_CAR(ab_loop_list__1);
		ab_loop_list__1 = M_CDR(ab_loop_list__1);
		argument_count = ISVREF(method,(SI_Long)23L);
		if ( !TRUEP(memq_function(argument_count,
			list_of_argument_counts_represented))) {
		    list_of_argument_counts_represented = 
			    gensym_cons_1(argument_count,
			    list_of_argument_counts_represented);
		    if ( !TRUEP(next_methods_to_return_qm))
			next_methods_to_return_qm = gensym_cons_1(method,Nil);
		    else if (FIXNUM_LT(argument_count,
			    ISVREF(M_CAR(next_methods_to_return_qm),
			    (SI_Long)23L)))
			next_methods_to_return_qm = gensym_cons_1(method,
				next_methods_to_return_qm);
		    else {
			cons_1 = next_methods_to_return_qm;
		      next_loop_16:
			if ( !TRUEP(cons_1))
			    goto end_loop_16;
			if (FIXNUM_GT(argument_count,ISVREF(M_CAR(cons_1),
				(SI_Long)23L)) && ( !TRUEP(CDR(cons_1)) || 
				FIXNUM_LT(argument_count,
				ISVREF(M_CAR(M_CDR(cons_1)),(SI_Long)23L)))) {
			    cons_after_which_to_insert_method = cons_1;
			    goto end_12;
			}
			cons_1 = M_CDR(cons_1);
			goto next_loop_16;
		      end_loop_16:
			cons_after_which_to_insert_method = Qnil;
		      end_12:;
			cdr_new_value = gensym_cons_1(method,
				CDR(cons_after_which_to_insert_method));
			M_CDR(cons_after_which_to_insert_method) = 
				cdr_new_value;
		    }
		}
		goto next_loop_15;
	      end_loop_15:;
	    }
	    goto next_loop_14;
	  end_loop_14:
	    reclaim_gensym_list_1(list_of_argument_counts_represented);
	    return VALUES_1(next_methods_to_return_qm);
	    return VALUES_1(Qnil);
	}
    }
}

static Object string_constant_17;  /* "~a" */

static Object Qsmall;              /* small */

/* SHORT-REPRESENTATION-OF-SYMBOL-OR-FRAME */
Object short_representation_of_symbol_or_frame(symbol_or_frame)
    Object symbol_or_frame;
{
    x_note_fn_call(214,51);
    if (SYMBOLP(symbol_or_frame))
	return make_description_box(tformat_text_string(2,
		string_constant_17,symbol_or_frame));
    else
	return make_short_representation(3,symbol_or_frame,Nil,Qsmall);
}

static Object Qclass_qualified_name;  /* class-qualified-name */

static Object Qab_class;           /* class */

static Object Qshort_representation_table_format;  /* short-representation-table-format */

static Object Qshort_representation_class_format;  /* short-representation-class-format */

/* MAKE-SHORT-REPRESENTATION-AS-APPROPRIATE */
Object make_short_representation_as_appropriate varargs_1(int, n)
{
    Object frame;
    Object string_to_look_for_qm, second_string_to_look_for_qm;
    Object observe_word_boundaries_qm;
    Object only_find_string_to_look_for_qm_if_editable_qm;
    Object candidate_denotations_of_slots_to_describe_or_search_qm;
    Object background_color_qm, attributes_table_description_qm, slot_name;
    Object defining_class_qm, text_representation_for_slot_value_qm;
    Object ab_loop_list_, text_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object ab_loop_desetq_, temp, sub_class_bit_vector;
    Object slot_denotations_for_occurrences, key_slot_name_if_no_occurrence_qm;
    Object attributes_table_description, slot_denotations_for_table;
    Object key_slot_name, attribute_table_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,52);
    INIT_ARGS_nonrelocating();
    frame = REQUIRED_ARG_nonrelocating();
    string_to_look_for_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    second_string_to_look_for_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    observe_word_boundaries_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    only_find_string_to_look_for_qm_if_editable_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    candidate_denotations_of_slots_to_describe_or_search_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    background_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    attributes_table_description_qm = Nil;
    if (string_to_look_for_qm) {
	slot_name = Nil;
	defining_class_qm = Nil;
	text_representation_for_slot_value_qm = Nil;
	attributes_table_description_qm = 
		make_attributes_table_description(3,frame,T,
		candidate_denotations_of_slots_to_describe_or_search_qm);
	ab_loop_list_ = attributes_table_description_qm;
	text_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	slot_name = CAR(ab_loop_desetq_);
	temp = CDR(ab_loop_desetq_);
	defining_class_qm = CAR(temp);
	temp = CDR(ab_loop_desetq_);
	temp = CDR(temp);
	text_representation_for_slot_value_qm = CAR(temp);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = text_representation_for_slot_value_qm;
	if (temp);
	else {
	    temp = get_slot_value_function(frame,slot_name,defining_class_qm);
	    temp = CDR(temp);
	}
	text_qm = temp;
	if (text_qm) {
	    temp_1 =  !TRUEP(only_find_string_to_look_for_qm_if_editable_qm);
	    if (temp_1);
	    else {
		if (type_of_slot_if_editable(4,ISVREF(ISVREF(frame,
			(SI_Long)1L),(SI_Long)1L),slot_name,Nil,
			defining_class_qm) && ((SI_Long)0L != 
			(IFIX(ISVREF(frame,(SI_Long)5L)) & 
			(SI_Long)262144L) || (SI_Long)0L != 
			(IFIX(ISVREF(frame,(SI_Long)4L)) & (SI_Long)1L))) {
		    temp_1 = TRUEP(text_representation_for_slot_value_qm);
		    if (temp_1);
		    else
			temp_1 =  !TRUEP(stripped_text_p(text_qm));
		    if (temp_1);
		    else {
			sub_class_bit_vector = ISVREF(ISVREF(frame,
				(SI_Long)1L),(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Message_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_1 = (SI_Long)1L;
			    gensymed_symbol_2 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_1 = gensymed_symbol_1 << 
				    gensymed_symbol_2;
			    gensymed_symbol = gensymed_symbol & 
				    gensymed_symbol_1;
			    temp_1 = (SI_Long)0L < gensymed_symbol;
			}
			else
			    temp_1 = TRUEP(Nil);
		    }
		}
		else
		    temp_1 = TRUEP(Nil);
		temp_1 = temp_1 ? TRUEP(edit_attribute_allowed_p(frame,
			slot_name,defining_class_qm)) : TRUEP(Nil);
	    }
	    temp_1 = temp_1 ? TRUEP(find_string_in_text_for_inspect(3,
		    string_to_look_for_qm,text_qm,
		    observe_word_boundaries_qm)) : TRUEP(Nil);
	    if (temp_1);
	    else
		temp_1 = second_string_to_look_for_qm ? 
			TRUEP(find_string_in_text_for_inspect(3,
			second_string_to_look_for_qm,text_qm,
			observe_word_boundaries_qm)) : TRUEP(Nil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    ab_loopvar__2 = gensym_cons_1(defining_class_qm ? 
		    gensym_cons_1(Qclass_qualified_name,
		    gensym_cons_1(defining_class_qm,
		    gensym_cons_1(slot_name,Nil))) : slot_name,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop;
      end_loop:
	slot_denotations_for_occurrences = ab_loopvar_;
	goto end_1;
	slot_denotations_for_occurrences = Qnil;
      end_1:;
    }
    else
	slot_denotations_for_occurrences = Nil;
    key_slot_name_if_no_occurrence_qm = Nil;
    if (candidate_denotations_of_slots_to_describe_or_search_qm) {
	if ( !TRUEP(string_to_look_for_qm) || 
		    slot_denotations_for_occurrences) {
	    attributes_table_description = 
		    make_attributes_table_description(5,frame,T,
		    candidate_denotations_of_slots_to_describe_or_search_qm,
		    Nil,T);
	    slot_name = Nil;
	    defining_class_qm = Nil;
	    ab_loop_list_ = attributes_table_description;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    ab_loop_desetq_ = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    slot_name = CAR(ab_loop_desetq_);
	    temp = CDR(ab_loop_desetq_);
	    defining_class_qm = CAR(temp);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if ( !TRUEP(slot_denotation_member(slot_name,defining_class_qm,
		    slot_denotations_for_occurrences))) {
		ab_loopvar__2 = gensym_cons_1(defining_class_qm ? 
			gensym_cons_1(Qclass_qualified_name,
			gensym_cons_1(defining_class_qm,
			gensym_cons_1(slot_name,Nil))) : slot_name,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    temp = ab_loopvar_;
	    goto end_2;
	    temp = Qnil;
	  end_2:;
	    temp = nconc2(temp,slot_denotations_for_occurrences);
	    reclaim_slot_value(attributes_table_description);
	    slot_denotations_for_table = temp;
	}
	else
	    slot_denotations_for_table = Nil;
    }
    else if ( !TRUEP(string_to_look_for_qm) || 
	    slot_denotations_for_occurrences) {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	key_slot_name = temp_1 ? Qbox_translation_and_text : Qab_class;
	if (string_to_look_for_qm && slot_denotation_member(key_slot_name,
		Nil,slot_denotations_for_occurrences))
	    slot_denotations_for_table = slot_denotations_for_occurrences;
	else {
	    key_slot_name_if_no_occurrence_qm = key_slot_name;
	    slot_denotations_for_table = 
		    gensym_cons_1(key_slot_name_if_no_occurrence_qm,
		    slot_denotations_for_occurrences);
	}
    }
    else
	slot_denotations_for_table = Nil;
    attribute_table_qm = slot_denotations_for_table ? 
	    make_attributes_table(7,frame,
	    Qshort_representation_table_format,
	    Qshort_representation_class_format,Nil,Nil,
	    slot_denotations_for_table,T) : Nil;
    if (attribute_table_qm)
	change_background_color_of_short_representation_table(attribute_table_qm,
		background_color_qm);
    if (attributes_table_description_qm)
	reclaim_slot_value(attributes_table_description_qm);
    if (slot_denotations_for_table) {
	reclaim_gensym_tree_1(slot_denotations_for_table);
	return VALUES_2(attribute_table_qm,key_slot_name_if_no_occurrence_qm);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_18;  /* "~a, a symbol" */

static Object string_constant_19;  /* "~a, a generic method" */

/* SHORT-REPRESENTATION-FOR-REF-HIERARCHY */
Object short_representation_for_ref_hierarchy varargs_1(int, n)
{
    Object symbol_or_frame;
    Object table_class_qm, font_size_qm, background_color_qm;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,53);
    INIT_ARGS_nonrelocating();
    symbol_or_frame = REQUIRED_ARG_nonrelocating();
    table_class_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    font_size_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    background_color_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SYMBOLP(symbol_or_frame))
	return make_free_text_description_box(tformat_text_string(2,
		string_constant_18,symbol_or_frame));
    else if (LISTP(symbol_or_frame))
	return make_free_text_description_box(tformat_text_string(2,
		string_constant_19,CAR(symbol_or_frame)));
    else
	return make_short_representation_as_appropriate(4,symbol_or_frame,
		table_class_qm,font_size_qm,background_color_qm);
}

static Object Qfree_text;          /* free-text */

static Object Qfont_for_free_text;  /* font-for-free-text */

/* MAKE-FREE-TEXT-DESCRIPTION-BOX */
Object make_free_text_description_box(text_line)
    Object text_line;
{
    x_note_fn_call(214,54);
    return make_free_text_box(3,text_line,Qfree_text,
	    choose_font_format_per_fonts_table(Qshort_representation_class_format,
	    Qfont_for_free_text));
}

/* HASH-SYMBOL-OR-FRAME */
Object hash_symbol_or_frame(symbol_or_frame)
    Object symbol_or_frame;
{
    Object fsn;

    x_note_fn_call(214,55);
    if (SYMBOLP(symbol_or_frame))
	return sxhash(symbol_or_frame);
    else {
	fsn = ISVREF(symbol_or_frame,(SI_Long)3L);
	if (FIXNUMP(fsn))
	    return VALUES_1(fsn);
	else
	    return VALUES_1(FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
    }
}

static Object Qkb_workspace;       /* kb-workspace */

/* SUBCOMPONENTS-OF-WORKSPACE-OR-ITEM-FOR-DISPLAY */
Object subcomponents_of_workspace_or_item_for_display(frame_qm,extra_arg)
    Object frame_qm, extra_arg;
{
    Object sub_class_bit_vector, workspace_qm, temp_1, block_qm;
    Object gensymed_symbol_3, ab_queue_form_, ab_next_queue_element_, subblock;
    Object subworkspace_qm, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Object scope_conses, block, ab_loopvar__3, ab_loopvar__4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,56);
    if (frame_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(frame_qm,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Kb_workspace_class_description,(SI_Long)18L));
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
	if (temp)
	    workspace_qm = frame_qm;
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(frame_qm,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	    if ((temp ? TRUEP(ISVREF(ISVREF(frame_qm,(SI_Long)1L),
		    (SI_Long)16L)) : TRUEP(Nil)) ? TRUEP(ISVREF(frame_qm,
		    (SI_Long)18L)) : TRUEP(Nil)) {
		temp_1 = ISVREF(frame_qm,(SI_Long)18L);
		workspace_qm = CAR(temp_1);
	    }
	    else {
		result = get_block_on_workspace_for_frame(frame_qm);
		MVS_2(result,block_qm,workspace_qm);
		if (block_qm && workspace_qm) {
		    sub_class_bit_vector = ISVREF(ISVREF(workspace_qm,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Kb_workspace_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp = TRUEP(Nil);
		    workspace_qm = temp ? workspace_qm : Nil;
		}
		else
		    workspace_qm = Nil;
	    }
	}
	if (workspace_qm) {
	    gensymed_symbol_3 = ISVREF(workspace_qm,(SI_Long)14L);
	    gensymed_symbol_3 = gensymed_symbol_3 ? 
		    ISVREF(gensymed_symbol_3,(SI_Long)4L) : Nil;
	    ab_queue_form_ = gensymed_symbol_3;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    subworkspace_qm = Nil;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
	  next_loop:
	    if (EQ(ab_next_queue_element_,ab_queue_form_))
		goto end_loop;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
	    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,
		    (SI_Long)0L);
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Entity_class_description,(SI_Long)18L));
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
	    if (temp ? TRUEP(ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)16L)) : TRUEP(Nil)) {
		temp_1 = ISVREF(subblock,(SI_Long)18L);
		subworkspace_qm = CAR(temp_1);
	    }
	    else
		subworkspace_qm = Nil;
	    if (subworkspace_qm) {
		ab_loopvar__2 = gensym_cons_1(subworkspace_qm,Nil);
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
	else
	    return VALUES_1(Nil);
    }
    else {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	block = Nil;
	PUSH_SPECIAL(Scope_conses,scope_conses,0);
	  ab_loopvar__2 = Nil;
	  ab_loopvar__3 = Nil;
	  ab_loopvar__4 = Nil;
	  ab_loopvar_ = collect_subclasses(Qkb_workspace);
	next_loop_1:
	  if ( !TRUEP(ab_loopvar__1)) {
	    next_loop_2:
	      if ( !TRUEP(ab_loopvar_))
		  goto end_loop_1;
	      ab_loopvar__1 = 
		      lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		      Instances_specific_to_this_class_kbprop);
	      ab_loopvar_ = M_CDR(ab_loopvar_);
	      if (ab_loopvar__1)
		  goto end_loop_1;
	      goto next_loop_2;
	    end_loop_1:
	      temp =  !TRUEP(ab_loopvar__1);
	  }
	  else
	      temp = TRUEP(Nil);
	  if (temp)
	      goto end_loop_2;
	  block = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ( !TRUEP(ISVREF(block,(SI_Long)18L))) {
	      ab_loopvar__4 = gensym_cons_1(block,Nil);
	      if (ab_loopvar__3)
		  M_CDR(ab_loopvar__3) = ab_loopvar__4;
	      else
		  ab_loopvar__2 = ab_loopvar__4;
	      ab_loopvar__3 = ab_loopvar__4;
	  }
	  goto next_loop_1;
	end_loop_2:
	  result = VALUES_1(ab_loopvar__2);
	  goto end_1;
	  result = VALUES_1(Qnil);
	end_1:;
	POP_SPECIAL();
	return result;
    }
}

static Object Qsubnodes_of_method_hierarchy;  /* subnodes-of-method-hierarchy */

static Object string_constant_20;  /* "Cannot show the method hierarchy for ~a, since no methods are defined for it." */

/* SHOW-METHOD-HIERARCHY-ON-A-WORKSPACE */
Object show_method_hierarchy_on_a_workspace varargs_1(int, n)
{
    Object method_name;
    Object inspect_command_qm, workspace_with_inspect_command_qm, temp, temp_1;
    Object temp_2, temp_3, temp_4, temp_5, temp_6, gensymed_symbol, temp_7;
    Object temp_8;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,57);
    INIT_ARGS_nonrelocating();
    method_name = REQUIRED_ARG_nonrelocating();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workspace_with_inspect_command_qm = inspect_command_qm ? 
	    get_and_clear_workspace_for_inspect_command(1,
	    inspect_command_qm) : Nil;
    if (methods_exist_in_subclass_hierarchy(Qitem,method_name)) {
	temp = IDENTITY(Qhash_symbol_or_frame);
	if (temp);
	else
	    temp = Qsxhashw;
	temp_1 = IDENTITY(Qhorizontal);
	if (temp_1);
	else
	    temp_1 = Qvertical;
	temp_2 = IDENTITY(FIX((SI_Long)1L));
	if (temp_2);
	else
	    temp_2 = FIX((SI_Long)50L);
	temp_3 = IDENTITY(FIX((SI_Long)50L));
	if (temp_3);
	else
	    temp_3 = FIX((SI_Long)50L);
	temp_4 =  !TRUEP(workspace_with_inspect_command_qm) ? 
		Current_workstation_detail_pane : Nil;
	temp_5 = IDENTITY(Nil);
	if (temp_5);
	else
	    temp_5 = Qtemporary_workspace;
	temp_6 = workspace_with_inspect_command_qm;
	if (temp_6);
	else
	    temp_6 = make_inspect_workspace(1,inspect_command_qm);
	if (inspect_command_qm) {
	    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_7 = gensymed_symbol;
	}
	else
	    temp_7 = Nil;
	if (inspect_command_qm) {
	    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)5L;
	    temp_8 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	else
	    temp_8 = Nil;
	reclaim_graph_display_1(graph_frame_hierarchy_function(Qitem,
		Qsubnodes_of_method_hierarchy,method_name,
		Qshort_representation_of_symbol_or_frame,temp,temp_1,
		temp_2,temp_3,temp_4,temp_5,temp_6,temp_7,temp_8));
    }
    else
	notify_user(2,string_constant_20,method_name);
    if (workspace_with_inspect_command_qm)
	return shrink_wrap_workspace(workspace_with_inspect_command_qm);
    else
	return VALUES_1(Nil);
}

/* METHODS-EXIST-IN-SUBCLASS-HIERARCHY */
Object methods_exist_in_subclass_hierarchy(class_name,method_name)
    Object class_name, method_name;
{
    Object scope_conses, ab_loopvar_, subclass, ab_loop_it_, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,58);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar_ = class_name;
    subclass = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      ab_loop_it_ = Nil;
      ab_loopvar_ = collect_subclasses(ab_loopvar_);
    next_loop:
      if ( !TRUEP(ab_loopvar_))
	  goto end_loop;
      temp = M_CAR(ab_loopvar_);
      ab_loopvar_ = M_CDR(ab_loopvar_);
      subclass = temp;
      ab_loop_it_ = get_named_procedure_methods_for_class(method_name,
	      subclass);
      if (ab_loop_it_) {
	  result = VALUES_1(ab_loop_it_);
	  goto end_1;
      }
      goto next_loop;
    end_loop:
      result = VALUES_1(Qnil);
    end_1:;
    POP_SPECIAL();
    return result;
}

/* SUBNODES-OF-METHOD-HIERARCHY */
Object subnodes_of_method_hierarchy(definition_class_or_method,method_name)
    Object definition_class_or_method, method_name;
{
    Object x2, gensymed_symbol, sub_class_bit_vector, temp_1;
    Object current_class_name, class_1, ab_loop_list_, class_methods;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(214,59);
    if (SIMPLE_VECTOR_P(definition_class_or_method) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(definition_class_or_method)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(definition_class_or_method,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(definition_class_or_method,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Method_class_description,
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
    temp =  !temp;
    if (temp);
    else {
	temp_1 = 
		get_named_procedure_methods_for_class(ISVREF(definition_class_or_method,
		(SI_Long)30L),ISVREF(definition_class_or_method,(SI_Long)31L));
	temp_1 = CDR(temp_1);
	temp = EQ(CAR(temp_1),definition_class_or_method);
    }
    if ( !temp)
	return VALUES_1(Nil);
    else if (SYMBOLP(definition_class_or_method) && 
	    IFIX(length(get_named_procedure_methods_for_class(method_name,
	    definition_class_or_method))) >= (SI_Long)2L) {
	temp_1 = get_named_procedure_methods_for_class(method_name,
		definition_class_or_method);
	return copy_list_using_gensym_conses_1(CDR(temp_1));
    }
    else {
	if (SYMBOLP(definition_class_or_method))
	    current_class_name = definition_class_or_method;
	else {
	    sub_class_bit_vector = 
		    ISVREF(ISVREF(definition_class_or_method,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Class_definition_class_description,
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
	    if (temp)
		current_class_name = ISVREF(definition_class_or_method,
			(SI_Long)20L);
	    else
		current_class_name = ISVREF(definition_class_or_method,
			(SI_Long)31L);
	}
	class_1 = Nil;
	ab_loop_list_ = 
		lookup_global_or_kb_specific_property_value(current_class_name,
		Inferior_classes_gkbprop);
	class_methods = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = get_named_procedure_methods_for_class(method_name,class_1);
	class_methods = CDR(temp_1);
	if (class_methods || methods_exist_in_subclass_hierarchy(class_1,
		method_name)) {
	    ab_loopvar__2 = class_methods &&  !TRUEP(CDR(class_methods)) ? 
		    copy_list_using_gensym_conses_1(class_methods) : 
		    gensym_cons_1(class_1,Nil);
	    if (ab_loopvar__2) {
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = last(ab_loopvar__2,_);
	    }
	}
	goto next_loop;
      end_loop:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

static Object Qknowledge_base;     /* knowledge-base */

/* SHORT-REPRESENTATION-OF-SYMBOL-OR-FRAME-OR-TOP-LEVEL */
Object short_representation_of_symbol_or_frame_or_top_level(symbol_or_frame_qm)
    Object symbol_or_frame_qm;
{
    Object temp;

    x_note_fn_call(214,60);
    temp = symbol_or_frame_qm;
    if (temp);
    else
	temp = Qknowledge_base;
    return short_representation_of_symbol_or_frame(temp);
}

/* GET-DIRECTLY-REQUIRED-MODULE-INFORMATION-SYSTEM-TABLES */
Object get_directly_required_module_information_system_tables varargs_1(int, n)
{
    Object module_information_system_table;
    Object module, ab_loop_list_, system_table_for_module_qm, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,61);
    INIT_ARGS_nonrelocating();
    module_information_system_table = REQUIRED_ARG_nonrelocating();
    if (OPTIONAL_ARG_P_nonrelocating())
	OPTIONAL_ARG_nonrelocating();
    END_ARGS_nonrelocating();
    module = Nil;
    ab_loop_list_ = ISVREF(module_information_system_table,(SI_Long)24L);
    system_table_for_module_qm = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    module = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    system_table_for_module_qm = lookup_kb_specific_property_value(module,
	    Module_information_instance_for_module_qm_kbprop);
    if (system_table_for_module_qm) {
	ab_loopvar__2 = gensym_cons_1(system_table_for_module_qm,Nil);
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

static Object list_constant_11;    /* # */

/* MAKE-ATTRIBUTES-TABLE-FOR-MODULE-INFORMATION-IN-HIERARCHY */
Object make_attributes_table_for_module_information_in_hierarchy(module_information_system_table)
    Object module_information_system_table;
{
    x_note_fn_call(214,62);
    return make_attributes_table(8,module_information_system_table,
	    Qshort_representation_table_format,Nil,Nil,Nil,
	    list_constant_11,Nil,list_constant_11);
}

static Object Qget_directly_required_module_information_system_tables;  /* get-directly-required-module-information-system-tables */

static Object Qmake_attributes_table_for_module_information_in_hierarchy;  /* make-attributes-table-for-module-information-in-hierarchy */

static Object string_constant_21;  /* "No module hierarchy ~a~a" */

static Object string_constant_22;  /* "can be shown for " */

static Object string_constant_23;  /* "exists, because the top-level module is unnamed." */

static Object string_constant_24;  /* "Top-Level Module-Information System Table: " */

static Object Qmodule_information;  /* module-information */

static Object array_constant_6;    /* # */

/* SHOW-MODULE-HIERARCHY-ON-A-WORKSPACE */
Object show_module_hierarchy_on_a_workspace varargs_1(int, n)
{
    Object module_to_start_with_qm;
    Object inspect_command_qm, ultimate_top_level_module_qm, workspace;
    Object workspace_margin, gensymed_symbol, top_edge_in_workspace;
    Object system_table_for_top_module_qm, temp, temp_1, temp_2, temp_3;
    Object temp_4, graph, free_text_box, table, x_in_workspace, y_in_workspace;
    Object any_tables_up_qm, scope_conses, ab_loopvar_, ab_loopvar__1;
    Object module_information_instance, module_qm, instance_qm, text_box;
    SI_Long interitem_spacing, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long left_edge_in_workspace, initial_x_in_workspace;
    char temp_5;
    Declare_varargs_nonrelocating;
    Declare_special(1);

    x_note_fn_call(214,63);
    INIT_ARGS_nonrelocating();
    module_to_start_with_qm = REQUIRED_ARG_nonrelocating();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    ultimate_top_level_module_qm = ISVREF(Module_information,(SI_Long)23L);
    workspace = inspect_command_qm ? 
	    get_and_clear_workspace_for_inspect_command(1,
	    inspect_command_qm) : Nil;
    if (workspace);
    else
	workspace = make_inspect_workspace(1,inspect_command_qm);
    interitem_spacing = (SI_Long)5L;
    workspace_margin = ISVREF(workspace,(SI_Long)17L);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    left_edge_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    if (inspect_command_qm) {
	gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = interitem_spacing;
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    else {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(workspace_margin);
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    system_table_for_top_module_qm = module_to_start_with_qm ? 
	    lookup_kb_specific_property_value(module_to_start_with_qm,
	    Module_information_instance_for_module_qm_kbprop) : 
	    Module_information;
    if (system_table_for_top_module_qm && 
	    ISVREF(system_table_for_top_module_qm,(SI_Long)23L)) {
	temp = IDENTITY(Qhash_symbol_or_frame);
	if (temp);
	else
	    temp = Qsxhashw;
	temp_1 = IDENTITY(Qvertical);
	if (temp_1);
	else
	    temp_1 = Qvertical;
	temp_2 = IDENTITY(FIX((SI_Long)50L));
	if (temp_2);
	else
	    temp_2 = FIX((SI_Long)50L);
	temp_3 = IDENTITY(FIX((SI_Long)5L));
	if (temp_3);
	else
	    temp_3 = FIX((SI_Long)50L);
	temp_4 = IDENTITY(Nil);
	if (temp_4);
	else
	    temp_4 = Qtemporary_workspace;
	graph = 
		graph_frame_hierarchy_function(system_table_for_top_module_qm,
		Qget_directly_required_module_information_system_tables,
		Nil,
		Qmake_attributes_table_for_module_information_in_hierarchy,
		temp,temp_1,temp_2,temp_3,Nil,temp_4,workspace,
		FIX(left_edge_in_workspace),top_edge_in_workspace);
	top_edge_in_workspace = FIX(IFIX(ISVREF(graph,(SI_Long)15L)) + 
		(interitem_spacing << (SI_Long)1L));
	reclaim_graph_display_1(graph);
    }
    else {
	temp_4 = module_to_start_with_qm;
	if (temp_4);
	else
	    temp_4 = string_constant_9;
	free_text_box = make_free_text_box(1,tformat_text_string(3,
		string_constant_21,module_to_start_with_qm ? 
		string_constant_22 : string_constant_23,temp_4));
	add_to_workspace(5,free_text_box,workspace,
		FIX(left_edge_in_workspace),top_edge_in_workspace,T);
	gensymed_symbol = ISVREF(free_text_box,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = interitem_spacing << (SI_Long)1L;
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	if ( !TRUEP(module_to_start_with_qm)) {
	    free_text_box = make_free_text_box(1,tformat_text_string(1,
		    string_constant_24));
	    add_to_workspace(5,free_text_box,workspace,
		    FIX(left_edge_in_workspace),top_edge_in_workspace,T);
	    gensymed_symbol = ISVREF(free_text_box,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = interitem_spacing << (SI_Long)1L;
	    top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	    table = 
		    make_attributes_table_for_module_information_in_hierarchy(Module_information);
	    add_to_workspace(5,table,workspace,FIX(left_edge_in_workspace),
		    top_edge_in_workspace,T);
	    gensymed_symbol = ISVREF(table,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = interitem_spacing << (SI_Long)1L;
	    top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
    }
    initial_x_in_workspace = left_edge_in_workspace;
    x_in_workspace = FIX(left_edge_in_workspace);
    y_in_workspace = top_edge_in_workspace;
    any_tables_up_qm = Nil;
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    module_information_instance = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      module_qm = Nil;
      ab_loopvar_ = collect_subclasses(Qmodule_information);
      propagate_kb_requires_module_p_to_all_modules();
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
	  temp_5 =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp_5 = TRUEP(Nil);
      if (temp_5)
	  goto end_loop_1;
      module_information_instance = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      module_qm = ISVREF(module_information_instance,(SI_Long)23L);
      if ( !EQ(module_information_instance,Module_information)) {
	  temp_5 =  !TRUEP(module_qm);
	  if (temp_5);
	  else
	      temp_5 =  !TRUEP(ultimate_top_level_module_qm);
	  if (temp_5);
	  else {
	      instance_qm = lookup_kb_specific_property_value(module_qm,
		      Module_information_instance_for_module_qm_kbprop);
	      temp_5 =  !(instance_qm && ISVREF(instance_qm,(SI_Long)25L));
	  }
      }
      else
	  temp_5 = TRUEP(Nil);
      if (temp_5) {
	  table = 
		  make_attributes_table_for_module_information_in_hierarchy(module_information_instance);
	  if ( !TRUEP(any_tables_up_qm)) {
	      any_tables_up_qm = T;
	      text_box = make_free_text_box(1,
		      copy_constant_wide_string_given_length(array_constant_6,
		      FIX((SI_Long)31L)));
	      add_to_workspace(5,text_box,workspace,x_in_workspace,
		      y_in_workspace,T);
	      x_in_workspace = FIX(initial_x_in_workspace);
	      gensymed_symbol = ISVREF(text_box,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)3L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = (SI_Long)5L;
	      y_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  }
	  add_to_workspace(5,table,workspace,x_in_workspace,y_in_workspace,T);
	  gensymed_symbol = ISVREF(table,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)2L) : FIX((SI_Long)0L);
	  gensymed_symbol_1 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = (SI_Long)5L;
	  x_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  if (IFIX(x_in_workspace) - initial_x_in_workspace > (SI_Long)400L) {
	      x_in_workspace = FIX(initial_x_in_workspace);
	      gensymed_symbol = ISVREF(table,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)3L) : FIX((SI_Long)0L);
	      gensymed_symbol_1 = IFIX(gensymed_symbol);
	      gensymed_symbol_2 = (SI_Long)5L;
	      y_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	  }
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    shrink_wrap_workspace(workspace);
    return put_inspect_workspace_on_current_detail_pane(workspace);
}

/* FIND-METHOD-DECLARATION-FOR-NAME */
Object find_method_declaration_for_name(generic_name)
    Object generic_name;
{
    Object candidates, elt_1, ab_loop_list_;

    x_note_fn_call(214,64);
    candidates = lookup_kb_specific_property_value(generic_name,
	    Frame_or_frames_with_this_name_kbprop);
    if (LISTP(candidates)) {
	elt_1 = Nil;
	ab_loop_list_ = candidates;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	elt_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (EQ(ISVREF(ISVREF(elt_1,(SI_Long)1L),(SI_Long)1L),
		Qmethod_declaration))
	    return VALUES_1(elt_1);
	goto next_loop;
      end_loop:
	return VALUES_1(Qnil);
    }
    else if (EQ(ISVREF(ISVREF(candidates,(SI_Long)1L),(SI_Long)1L),
	    Qmethod_declaration))
	return VALUES_1(candidates);
    else
	return VALUES_1(Nil);
}

static Object Qprocedure;          /* procedure */

static Object string_constant_25;  /* "Cannot show the procedure reference hierarchy for ~a, since it is not a procedure." */

static Object Qreferencing_procedures_for_graph_display;  /* referencing-procedures-for-graph-display */

static Object Qreferenced_procedures_for_graph_display;  /* referenced-procedures-for-graph-display */

static Object Qshort_representation_for_ref_hierarchy;  /* short-representation-for-ref-hierarchy */

/* SHOW-PROCEDURE-REFERENCE-HIERARCHY-ON-A-WORKSPACE */
Object show_procedure_reference_hierarchy_on_a_workspace varargs_1(int, n)
{
    Object root_procedure_name;
    Object inspect_command_qm, upward_qm, method_p_qm, root_procedure;
    Object workspace_with_inspect_command_qm, temp, temp_1, temp_2, temp_3;
    Object temp_4, temp_5, temp_6, temp_7, gensymed_symbol, temp_8, temp_9;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,65);
    INIT_ARGS_nonrelocating();
    root_procedure_name = REQUIRED_ARG_nonrelocating();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    upward_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    method_p_qm = Nil;
    if (SYMBOLP(root_procedure_name))
	root_procedure = get_instance_with_name_if_any(Qprocedure,
		root_procedure_name);
    else if (EQ(CAR(root_procedure_name),Qclass_qualified_method)) {
	method_p_qm = T;
	root_procedure = 
		find_method_declaration_for_name(THIRD(root_procedure_name));
    }
    else
	root_procedure = Qnil;
    if ( !TRUEP(root_procedure))
	return notify_user(2,string_constant_25,root_procedure_name);
    else {
	workspace_with_inspect_command_qm = inspect_command_qm ? 
		get_and_clear_workspace_for_inspect_command(1,
		inspect_command_qm) : Nil;
	temp = EQ(ISVREF(ISVREF(root_procedure,(SI_Long)1L),(SI_Long)1L),
		Qmethod_declaration) && LISTP(root_procedure_name) ? 
		SECOND(root_procedure_name) : inspect_command_qm;
	temp_1 = IDENTITY(Qhash_symbol_or_frame);
	if (temp_1);
	else
	    temp_1 = Qsxhashw;
	temp_2 = IDENTITY(Qhorizontal);
	if (temp_2);
	else
	    temp_2 = Qvertical;
	temp_3 = IDENTITY(FIX((SI_Long)1L));
	if (temp_3);
	else
	    temp_3 = FIX((SI_Long)50L);
	temp_4 = IDENTITY(FIX((SI_Long)50L));
	if (temp_4);
	else
	    temp_4 = FIX((SI_Long)50L);
	temp_5 =  !TRUEP(workspace_with_inspect_command_qm) ? 
		Current_workstation_detail_pane : Nil;
	temp_6 = IDENTITY(Nil);
	if (temp_6);
	else
	    temp_6 = Qtemporary_workspace;
	temp_7 = workspace_with_inspect_command_qm;
	if (temp_7);
	else
	    temp_7 = make_inspect_workspace(1,inspect_command_qm);
	if (inspect_command_qm) {
	    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)0L) : FIX((SI_Long)0L);
	    temp_8 = gensymed_symbol;
	}
	else
	    temp_8 = Nil;
	if (inspect_command_qm) {
	    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol_2 = (SI_Long)5L;
	    temp_9 = FIX(gensymed_symbol_1 + gensymed_symbol_2);
	}
	else
	    temp_9 = Nil;
	reclaim_graph_display_1(graph_frame_hierarchy_function(root_procedure,
		upward_qm ? Qreferencing_procedures_for_graph_display : 
		Qreferenced_procedures_for_graph_display,temp,
		Qshort_representation_for_ref_hierarchy,temp_1,temp_2,
		temp_3,temp_4,temp_5,temp_6,temp_7,temp_8,temp_9));
	if (workspace_with_inspect_command_qm) {
	    shrink_wrap_workspace(workspace_with_inspect_command_qm);
	    return put_inspect_workspace_on_current_detail_pane(workspace_with_inspect_command_qm);
	}
	else
	    return VALUES_1(Nil);
    }
}

/* PUT-UP-VERSON-CONTROL-INSPECT-WORKSPACE */
Object put_up_verson_control_inspect_workspace(list_of_strings,
	    inspect_command_qm)
    Object list_of_strings, inspect_command_qm;
{
    Object workspace, workspace_margin, gensymed_symbol, top_edge_in_workspace;
    Object string_1, ab_loop_list_, new_text_box;
    SI_Long interitem_spacing, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long left_edge_in_workspace;

    x_note_fn_call(214,66);
    interitem_spacing = (SI_Long)20L;
    workspace = inspect_command_qm ? 
	    get_and_clear_workspace_for_inspect_command(1,
	    inspect_command_qm) : Nil;
    if (workspace);
    else
	workspace = make_inspect_workspace(1,inspect_command_qm);
    workspace_margin = ISVREF(workspace,(SI_Long)17L);
    gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = IFIX(workspace_margin);
    left_edge_in_workspace = gensymed_symbol_1 + gensymed_symbol_2;
    if (inspect_command_qm) {
	gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = interitem_spacing;
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    else {
	gensymed_symbol = ISVREF(workspace,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol_2 = IFIX(workspace_margin);
	top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    }
    string_1 = Nil;
    ab_loop_list_ = list_of_strings;
    new_text_box = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_text_box = make_free_text_box(2,string_1,Qfree_text);
    add_to_workspace(5,new_text_box,workspace,FIX(left_edge_in_workspace),
	    top_edge_in_workspace,T);
    gensymed_symbol = ISVREF(new_text_box,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol_2 = interitem_spacing;
    top_edge_in_workspace = FIX(gensymed_symbol_1 + gensymed_symbol_2);
    goto next_loop;
  end_loop:;
    reclaim_gensym_list_1(list_of_strings);
    shrink_wrap_workspace(workspace);
    return put_inspect_workspace_on_current_detail_pane(workspace);
}

static Object Qab_method;          /* method */

/* REFERENCING-PROCEDURES-FOR-GRAPH-DISPLAY */
Object referencing_procedures_for_graph_display varargs_1(int, n)
{
    Object symbol_or_item;
    Object extra_arg_qm, temp, procedure_methods, elt_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, items, item;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,67);
    INIT_ARGS_nonrelocating();
    symbol_or_item = REQUIRED_ARG_nonrelocating();
    extra_arg_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (LISTP(symbol_or_item) && EQ(CAR(symbol_or_item),
	    Qclass_qualified_method)) {
	temp = get_named_procedure_methods_for_class(THIRD(symbol_or_item),
		SECOND(symbol_or_item));
	procedure_methods = CDR(temp);
    }
    else if (EQ(type_of(symbol_or_item),Qsimple_vector) && 
	    EQ(ISVREF(ISVREF(symbol_or_item,(SI_Long)1L),(SI_Long)1L),
	    Qmethod_declaration)) {
	if (SYMBOLP(extra_arg_qm)) {
	    temp = 
		    get_named_procedure_methods_for_class(get_primary_name_for_frame_if_any(symbol_or_item),
		    extra_arg_qm);
	    procedure_methods = CDR(temp);
	}
	else {
	    elt_1 = Nil;
	    temp = get_primary_name_for_frame_if_any(symbol_or_item);
	    ab_loop_list_ = lookup_kb_specific_property_value(temp,
		    Compiled_items_referring_to_this_name_kbprop);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    elt_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(ISVREF(ISVREF(elt_1,(SI_Long)1L),(SI_Long)1L),Qab_method)) {
		ab_loopvar__2 = gensym_cons_1(elt_1,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop;
	  end_loop:
	    procedure_methods = ab_loopvar_;
	    goto end_1;
	    procedure_methods = Qnil;
	  end_1:;
	}
    }
    else
	procedure_methods = Qnil;
    temp = procedure_methods;
    if (temp)
	return VALUES_1(temp);
    else {
	items = referencing_items_for_graph_display(2,symbol_or_item,
		extra_arg_qm);
	item = Nil;
	ab_loop_list_ = items;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	item = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	if (get_instance_with_name_if_any(Qprocedure,
		get_primary_name_for_frame_if_any(item)) || 
		get_instance_with_name_if_any(Qab_method,
		get_primary_name_for_frame_if_any(item))) {
	    ab_loopvar__2 = gensym_cons_1(item,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_1;
      end_loop_1:
	return VALUES_1(ab_loopvar_);
	return VALUES_1(Qnil);
    }
}

/* REFERENCING-ITEMS-FOR-GRAPH-DISPLAY */
Object referencing_items_for_graph_display varargs_1(int, n)
{
    Object symbol_or_item;
    Object inspect_command_qm, temp;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,68);
    INIT_ARGS_nonrelocating();
    symbol_or_item = REQUIRED_ARG_nonrelocating();
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (SYMBOLP(symbol_or_item))
	return lookup_kb_specific_property_value(symbol_or_item,
		Compiled_items_referring_to_this_name_kbprop);
    else {
	temp = get_primary_name_for_frame_if_any(symbol_or_item);
	return lookup_kb_specific_property_value(temp,
		Compiled_items_referring_to_this_name_kbprop);
    }
}

/* REFERENCED-PROCEDURES-FOR-GRAPH-DISPLAY */
Object referenced_procedures_for_graph_display varargs_1(int, n)
{
    Object symbol_or_item;
    Object extra_arg_qm, temp, procedure_methods, elt_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, references, ref, names;
    Object sym, proc_qm, result_1;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,69);
    INIT_ARGS_nonrelocating();
    symbol_or_item = REQUIRED_ARG_nonrelocating();
    extra_arg_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    if (LISTP(symbol_or_item) && EQ(CAR(symbol_or_item),
	    Qclass_qualified_method)) {
	temp = get_named_procedure_methods_for_class(THIRD(symbol_or_item),
		SECOND(symbol_or_item));
	procedure_methods = CDR(temp);
    }
    else if (EQ(type_of(symbol_or_item),Qsimple_vector) && 
	    EQ(ISVREF(ISVREF(symbol_or_item,(SI_Long)1L),(SI_Long)1L),
	    Qmethod_declaration)) {
	if (SYMBOLP(extra_arg_qm)) {
	    temp = 
		    get_named_procedure_methods_for_class(get_primary_name_for_frame_if_any(symbol_or_item),
		    extra_arg_qm);
	    procedure_methods = CDR(temp);
	}
	else {
	    elt_1 = Nil;
	    temp = get_primary_name_for_frame_if_any(symbol_or_item);
	    ab_loop_list_ = lookup_kb_specific_property_value(temp,
		    Compiled_items_referring_to_this_name_kbprop);
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    elt_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (EQ(ISVREF(ISVREF(elt_1,(SI_Long)1L),(SI_Long)1L),Qab_method)) {
		ab_loopvar__2 = gensym_cons_1(elt_1,Nil);
		if (ab_loopvar__1)
		    M_CDR(ab_loopvar__1) = ab_loopvar__2;
		else
		    ab_loopvar_ = ab_loopvar__2;
		ab_loopvar__1 = ab_loopvar__2;
	    }
	    goto next_loop;
	  end_loop:
	    procedure_methods = ab_loopvar_;
	    goto end_1;
	    procedure_methods = Qnil;
	  end_1:;
	}
    }
    else
	procedure_methods = Qnil;
    temp = procedure_methods;
    if (temp)
	return VALUES_1(temp);
    else if (SYMBOLP(symbol_or_item))
	return VALUES_1(Nil);
    else {
	references = free_references_from_procedure(symbol_or_item);
	ref = Nil;
	ab_loop_list_ = references;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	ref = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__2 = 
		extract_procedure_names_from_free_reference_vector(ref);
	if (ab_loopvar__2) {
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = last(ab_loopvar__2,_);
	}
	goto next_loop_1;
      end_loop_1:
	names = ab_loopvar_;
	goto end_2;
	names = Qnil;
      end_2:;
	sym = Nil;
	ab_loop_list_ = names;
	proc_qm = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	sym = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	proc_qm = get_instance_with_name_if_any(Qprocedure,sym);
	if (sym) {
	    temp = proc_qm;
	    if (temp);
	    else
		temp = sym;
	    ab_loopvar__2 = gensym_cons_1(temp,Nil);
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	}
	goto next_loop_2;
      end_loop_2:
	result_1 = ab_loopvar_;
	goto end_3;
	result_1 = Qnil;
      end_3:;
	reclaim_gensym_list_1(references);
	reclaim_gensym_list_1(names);
	return VALUES_1(result_1);
    }
}

/* FREE-REFERENCES-FROM-PROCEDURE */
Object free_references_from_procedure(procedure)
    Object procedure;
{
    Object procedure_code_bodies, code_body, ab_loop_list_, byte_code_body;
    Object free_references, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,70);
    procedure_code_bodies = ISVREF(procedure,(SI_Long)28L);
    code_body = Nil;
    ab_loop_list_ = procedure_code_bodies;
    PUSH_SPECIAL(Code_body,code_body,0);
      byte_code_body = Nil;
      free_references = Nil;
      ab_loopvar_ = Nil;
      ab_loopvar__1 = Nil;
      ab_loopvar__2 = Nil;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      Code_body = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      byte_code_body = Code_body ? ISVREF(Code_body,(SI_Long)8L) : Nil;
      free_references = byte_code_body ? ISVREF(byte_code_body,
	      (SI_Long)7L) : Nil;
      if (free_references) {
	  ab_loopvar__2 = gensym_cons_1(free_references,Nil);
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
    POP_SPECIAL();
    return result;
}

static Object Qprocedure_call;     /* procedure-call */

/* EXTRACT-PROCEDURE-NAMES-FROM-FREE-REFERENCE-VECTOR */
Object extract_procedure_names_from_free_reference_vector(free_reference_vector)
    Object free_reference_vector;
{
    Object gensymed_symbol, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, temp;
    SI_Long gensymed_symbol_1, ab_loop_bind_;

    x_note_fn_call(214,71);
    gensymed_symbol = free_reference_vector;
    gensymed_symbol_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(gensymed_symbol));
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (gensymed_symbol_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(gensymed_symbol,gensymed_symbol_1),Qprocedure_call)) {
	temp = ISVREF(gensymed_symbol,gensymed_symbol_1 + (SI_Long)1L);
	ab_loopvar__2 = gensym_cons_1(CAR(temp),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

/* POSSIBLY-QUALIFIED-INLINED-NAME */
Object possibly_qualified_inlined_name(free_reference)
    Object free_reference;
{
    Object slot_name, defining_class_qm;

    x_note_fn_call(214,72);
    slot_name = CADR(free_reference);
    defining_class_qm = CAR(free_reference);
    if (defining_class_qm)
	return gensym_cons_1(Qclass_qualified_name,
		gensym_cons_1(defining_class_qm,gensym_cons_1(slot_name,Nil)));
    else
	return VALUES_1(slot_name);
}

/* EXTRACT-INLINED-PROCEDURES-FROM-FREE-REFERENCE-VECTOR */
Object extract_inlined_procedures_from_free_reference_vector(free_reference_vector)
    Object free_reference_vector;
{
    Object gensymed_symbol, ab_loopvar_, ab_loopvar__1, ab_loopvar__2;
    SI_Long gensymed_symbol_1, ab_loop_bind_;

    x_note_fn_call(214,73);
    gensymed_symbol = free_reference_vector;
    gensymed_symbol_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(length(gensymed_symbol));
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if (gensymed_symbol_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(gensymed_symbol,gensymed_symbol_1),Qinline)) {
	ab_loopvar__2 = 
		gensym_cons_1(possibly_qualified_inlined_name(ISVREF(gensymed_symbol,
		gensymed_symbol_1 + (SI_Long)1L)),Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
    }
    gensymed_symbol_1 = gensymed_symbol_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

Object Current_remote_search_representation_qm = UNBOUND;

static Object Qkb_search_state;    /* kb-search-state */

static Object Qg2_cell_array;      /* g2-cell-array */

/* INITIALIZE-FOR-KB-SEARCH-STATE */
Object initialize_for_kb_search_state(kb_search_state)
    Object kb_search_state;
{
    Object frame, sub_vector_qm, method_function_qm, cloning_qm, new_value;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,74);
    frame = kb_search_state;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_search_state)) {
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
    cloning_qm = get_lookup_slot_value_given_default(kb_search_state,
	    Qcell_array,Nil);
    if ( !TRUEP(cloning_qm)) {
	new_value = make_frame(Qg2_cell_array);
	return initialize_slot_description_value(kb_search_state,
		get_slot_description_of_class_description_function(Qcell_array,
		ISVREF(kb_search_state,(SI_Long)1L),Nil),new_value);
    }
    else
	return VALUES_1(Nil);
}

/* CLEANUP-FOR-KB-SEARCH-STATE */
Object cleanup_for_kb_search_state(kb_search_state)
    Object kb_search_state;
{
    Object frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,75);
    frame = kb_search_state;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)1L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_search_state)) {
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
    return do_inspector_suppressed_warnings_notes(kb_search_state);
}

/* ACTIVATE-FOR-KB-SEARCH-STATE */
Object activate_for_kb_search_state(kb_search_state)
    Object kb_search_state;
{
    Object current_block_of_dependent_frame, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,76);
    current_block_of_dependent_frame = kb_search_state;
    PUSH_SPECIAL(Current_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      if ( !TRUEP(In_suspend_resume_p))
	  activate_g2_cell_array(get_lookup_slot_value_given_default(kb_search_state,
		  Qcell_array,Nil));
      frame = kb_search_state;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)6L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_search_state)) {
	  method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	  goto end_1;
      }
      index_1 = index_1 + (SI_Long)2L;
      goto next_loop;
    end_loop:
      method_function_qm = Qnil;
    end_1:;
      if (method_function_qm)
	  result = inline_funcall_1(method_function_qm,frame);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* DEACTIVATE-FOR-KB-SEARCH-STATE */
Object deactivate_for_kb_search_state(kb_search_state)
    Object kb_search_state;
{
    Object current_block_of_dependent_frame, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long index_1, ab_loop_bind_;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,77);
    current_block_of_dependent_frame = kb_search_state;
    PUSH_SPECIAL(Current_block_of_dependent_frame,current_block_of_dependent_frame,
	    0);
      if ( !TRUEP(In_suspend_resume_p))
	  deactivate_g2_cell_array(get_lookup_slot_value_given_default(kb_search_state,
		  Qcell_array,Nil));
      frame = kb_search_state;
      sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)7L);
      index_1 = (SI_Long)0L;
      ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	      (SI_Long)3L;
    next_loop:
      if (index_1 >= ab_loop_bind_)
	  goto end_loop;
      if (EQ(ISVREF(sub_vector_qm,index_1),Qkb_search_state)) {
	  method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	  goto end_1;
      }
      index_1 = index_1 + (SI_Long)2L;
      goto next_loop;
    end_loop:
      method_function_qm = Qnil;
    end_1:;
      if (method_function_qm)
	  result = inline_funcall_1(method_function_qm,frame);
      else
	  result = VALUES_1(Nil);
    POP_SPECIAL();
    return result;
}

/* RECLAIM-FILE-STREAM-FOR-PRINTING-SEARCH-RESULTS?-VALUE */
Object reclaim_file_stream_for_printing_search_results_qm_value(stream_qm,
	    kb_search_state)
    Object stream_qm, kb_search_state;
{
    Object temp;

    x_note_fn_call(214,78);
    if (stream_qm) {
	temp = Nil;
	close_file_for_search_results(stream_qm);
	ISVREF(kb_search_state,(SI_Long)37L) = temp;
    }
    return VALUES_1(Nil);
}

/* RECLAIM-OLD-KB-SEARCH-RESULT-TABLES-AND-TEXT-BOXES-VALUE */
Object reclaim_old_kb_search_result_tables_and_text_boxes_value(value,
	    kb_search_state)
    Object value, kb_search_state;
{
    Object frame_serial_number, table, ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(214,79);
    if (value) {
	frame_serial_number = ISVREF(kb_search_state,(SI_Long)24L);
	table = Nil;
	ab_loop_list_ = value;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	table = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol = ISVREF(table,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(table) ? EQ(ISVREF(table,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number,gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp)
	    delete_frame(table);
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(value);
    }
    reclaim_frame_serial_number(ISVREF(kb_search_state,(SI_Long)24L));
    ISVREF(kb_search_state,(SI_Long)24L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-FOR-KB-SEARCH-VALUE */
Object reclaim_frame_serial_number_for_kb_search_value(serial_number,
	    gensymed_symbol)
    Object serial_number, gensymed_symbol;
{
    x_note_fn_call(214,80);
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-FOR-KB-SEARCH-RESULTS-WORKSPACE-VALUE */
Object reclaim_frame_serial_number_for_kb_search_results_workspace_value(serial_number,
	    kb_search_state)
    Object serial_number, kb_search_state;
{
    x_note_fn_call(214,81);
    reclaim_frame_serial_number(serial_number);
    ISVREF(kb_search_state,(SI_Long)22L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-FOR-SUBCOMMAND-MENU-FOR-KB-SEARCH?-VALUE */
Object reclaim_frame_serial_number_for_subcommand_menu_for_kb_search_qm_value(serial_number,
	    kb_search_state)
    Object serial_number, kb_search_state;
{
    x_note_fn_call(214,82);
    reclaim_frame_serial_number(serial_number);
    ISVREF(kb_search_state,(SI_Long)49L) = Nil;
    return VALUES_1(Nil);
}

/* RECLAIM-FRAME-SERIAL-NUMBER-FOR-INSPECT-COMMAND-FOR-KB-SEARCH?-VALUE */
Object reclaim_frame_serial_number_for_inspect_command_for_kb_search_qm_value(serial_number,
	    kb_search_state)
    Object serial_number, kb_search_state;
{
    x_note_fn_call(214,83);
    reclaim_frame_serial_number(serial_number);
    ISVREF(kb_search_state,(SI_Long)51L) = Nil;
    return VALUES_1(Nil);
}

static Object array_constant_7;    /* # */

static Object Qcurrent_computation_frame;  /* *current-computation-frame* */

static Object string_constant_26;  /* " of " */

/* DENOTE-CELL-ARRAY-ELEMENT-FOR-KB-SEARCH-STATE */
Object denote_cell_array_element_for_kb_search_state(kb_search_state,
	    cell_index,include_denotation_for_block)
    Object kb_search_state, cell_index, include_denotation_for_block;
{
    x_note_fn_call(214,84);
    twrite_beginning_of_wide_string(array_constant_7,FIX((SI_Long)11L));
    return denote_component_of_block_1(Qcurrent_computation_frame,
	    string_constant_26);
}

static Object Qframe_notes_for_component_particulars;  /* frame-notes-for-component-particulars */

static Object string_constant_27;  /* "~%~%but " */

static Object Qframe_note_writer_1;  /* frame-note-writer-1 */

/* WRITE-ITEM-FILTER?-FROM-SLOT */
Object write_item_filter_qm_from_slot(item_filter_qm,kb_search_state)
    Object item_filter_qm, kb_search_state;
{
    Object string_to_twrite, temporary_text_string;
    Object frame_notes_for_component_particulars, temp, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2;
    SI_Long i, ab_loop_bind_;

    x_note_fn_call(214,85);
    string_to_twrite = CDR(item_filter_qm);
    i = (SI_Long)0L;
    ab_loop_bind_ = IFIX(lengthw(string_to_twrite));
  next_loop:
    if (i >= ab_loop_bind_)
	goto end_loop;
    if ( !(UBYTE_16_ISAREF_1(string_to_twrite,i) == (SI_Long)32L)) {
	temporary_text_string = text_string_substring(string_to_twrite,
		FIX(i),Nil);
	twrite_general_string(temporary_text_string);
	reclaim_text_string(temporary_text_string);
	goto end_1;
    }
    i = i + (SI_Long)1L;
    goto next_loop;
  end_loop:
  end_1:;
    if (Current_computation_component_particulars)
	frame_notes_for_component_particulars = 
		get_particulars_of_frame_note_from_component_particulars(Qframe_notes_for_component_particulars,
		kb_search_state,Current_computation_component_particulars);
    else {
	temp = ISVREF(kb_search_state,(SI_Long)8L);
	frame_notes_for_component_particulars = 
		getfq_function_no_default(CDR(temp),
		Qframe_notes_for_component_particulars);
    }
    if (frame_notes_for_component_particulars) {
	tformat(1,string_constant_27);
	gensymed_symbol = 
		getfq_function_no_default(INLINE_SYMBOL_PLIST(Qframe_notes_for_component_particulars),
		Qframe_note_writer_1);
	gensymed_symbol = gensymed_symbol ? gensymed_symbol : Nil;
	gensymed_symbol_1 = frame_notes_for_component_particulars;
	gensymed_symbol_2 = kb_search_state;
	return VALUES_1(inline_funcall_2(gensymed_symbol,gensymed_symbol_1,
		gensymed_symbol_2));
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_28;  /* "File operation ... " */

static Object string_constant_29;  /* "FAILED!  (~a)" */

static Object string_constant_30;  /* "Searching ... [Seconds elapsed: ~d]" */

static Object string_constant_31;  /* "Search took ~D second~A.  " */

static Object string_constant_32;  /* "~D item~A ~A found." */

static Object string_constant_33;  /* "was" */

static Object string_constant_34;  /* "were" */

/* WRITE-KB-STATE-SEARCH-STATUS-FROM-SLOT */
Object write_kb_state_search_status_from_slot(arbitrary_value,kb_search_state)
    Object arbitrary_value, kb_search_state;
{
    SI_Long gensymed_symbol, gensymed_symbol_1, temp, number_of_seconds;

    x_note_fn_call(214,86);
    if (ISVREF(kb_search_state,(SI_Long)35L) &&  
	    !TRUEP(ISVREF(kb_search_state,(SI_Long)37L)) && ( 
	    !TRUEP(ISVREF(kb_search_state,(SI_Long)54L)) || 
	    text_string_p(ISVREF(kb_search_state,(SI_Long)54L)))) {
	tformat(1,string_constant_28);
	if (ISVREF(kb_search_state,(SI_Long)54L))
	    return tformat(2,string_constant_29,ISVREF(kb_search_state,
		    (SI_Long)54L));
	else
	    return VALUES_1(Nil);
    }
    else if ( !FIXNUM_EQ(ISVREF(kb_search_state,(SI_Long)29L),
	    ISVREF(kb_search_state,(SI_Long)30L))) {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(ISVREF(kb_search_state,(SI_Long)39L));
	if (gensymed_symbol >= gensymed_symbol_1)
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	}
	gensymed_symbol_1 = IFIX(Fixnum_time_units_per_second);
	temp = gensymed_symbol / gensymed_symbol_1;
	return tformat(2,string_constant_30,FIX(temp));
    }
    else {
	gensymed_symbol = IFIX(c_native_clock_ticks_or_cache(Nil,Nil));
	gensymed_symbol_1 = IFIX(ISVREF(kb_search_state,(SI_Long)39L));
	if (gensymed_symbol >= gensymed_symbol_1)
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	else {
	    gensymed_symbol = gensymed_symbol - gensymed_symbol_1;
	    gensymed_symbol = gensymed_symbol + IFIX(Most_positive_fixnum);
	    gensymed_symbol = gensymed_symbol + (SI_Long)1L;
	}
	gensymed_symbol_1 = IFIX(Fixnum_time_units_per_second);
	temp = gensymed_symbol / gensymed_symbol_1;
	number_of_seconds = temp;
	tformat(3,string_constant_31,FIX(number_of_seconds),
		number_of_seconds == (SI_Long)1L ? string_constant_9 : 
		string_constant_8);
	return tformat(4,string_constant_32,ISVREF(kb_search_state,
		(SI_Long)33L),IFIX(ISVREF(kb_search_state,(SI_Long)33L)) 
		== (SI_Long)1L ? string_constant_9 : string_constant_8,
		IFIX(ISVREF(kb_search_state,(SI_Long)33L)) == (SI_Long)1L ?
		 string_constant_33 : string_constant_34);
    }
}

/* GET-SEARCH-STATE-FOR-INSPECT-COMMAND-RESULTS-IF-ANY */
Object get_search_state_for_inspect_command_results_if_any(inspect_command)
    Object inspect_command;
{
    Object search_state_qm, serial_number, gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(214,87);
    search_state_qm = ISVREF(inspect_command,(SI_Long)19L);
    serial_number = ISVREF(inspect_command,(SI_Long)20L);
    if (search_state_qm) {
	gensymed_symbol = ISVREF(search_state_qm,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(search_state_qm) ? 
		EQ(ISVREF(search_state_qm,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(serial_number))
	    temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(serial_number,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(serial_number);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(serial_number),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	temp =  !temp;
    }
    else
	temp = TRUEP(Nil);
    return VALUES_1(temp ? search_state_qm : Nil);
}

/* GET-RESULTS-WORKSPACE-FOR-SEARCH-STATE-IF-ANY */
Object get_results_workspace_for_search_state_if_any(search_state)
    Object search_state;
{
    Object workspace, temp, gensymed_symbol, x, y, xa, ya;
    char temp_1;

    x_note_fn_call(214,88);
    workspace = ISVREF(search_state,(SI_Long)21L);
    if (ISVREF(search_state,(SI_Long)63L))
	temp = Nil;
    else {
	gensymed_symbol = ISVREF(workspace,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(workspace) ? EQ(ISVREF(workspace,
		(SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else {
	    x = gensymed_symbol;
	    y = ISVREF(search_state,(SI_Long)22L);
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
	if ( !temp_1)
	    temp = workspace;
	else
	    temp = Nil;
    }
    return VALUES_1(temp);
}

/* NOTE-FRAME-FOR-INSPECTOR-SUPPRESSED-WARNINGS */
Object note_frame_for_inspector_suppressed_warnings(frame,kb_search_state)
    Object frame, kb_search_state;
{
    Object embedded_rule_qm, sub_class_bit_vector, svref_new_value;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,89);
    embedded_rule_qm = Nil;
    sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = 
	    IFIX(ISVREF(Action_button_class_description,(SI_Long)18L));
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
	embedded_rule_qm = embedded_rule_qm_function(frame);
	if (embedded_rule_qm) {
	    svref_new_value = gensym_cons_1(embedded_rule_qm,
		    ISVREF(kb_search_state,(SI_Long)62L));
	    ISVREF(kb_search_state,(SI_Long)62L) = svref_new_value;
	}
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(User_menu_choice_class_description,(SI_Long)18L));
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
	if (temp) {
	    embedded_rule_qm = ISVREF(frame,(SI_Long)24L);
	    if (embedded_rule_qm) {
		svref_new_value = gensym_cons_1(embedded_rule_qm,
			ISVREF(kb_search_state,(SI_Long)62L));
		ISVREF(kb_search_state,(SI_Long)62L) = svref_new_value;
	    }
	}
    }
    svref_new_value = gensym_cons_1(frame,ISVREF(kb_search_state,
	    (SI_Long)62L));
    return VALUES_1(ISVREF(kb_search_state,(SI_Long)62L) = svref_new_value);
}

/* CLEAR-SUPPRESSED-WARNINGS-CACHE-IF-NECESSARY */
Object clear_suppressed_warnings_cache_if_necessary(kb_search_state)
    Object kb_search_state;
{
    Object list_1;

    x_note_fn_call(214,90);
    list_1 = ISVREF(kb_search_state,(SI_Long)62L);
    if (list_1) {
	ISVREF(kb_search_state,(SI_Long)62L) = Nil;
	return reclaim_gensym_list_1(list_1);
    }
    else
	return VALUES_1(Nil);
}

/* DO-INSPECTOR-SUPPRESSED-WARNINGS-NOTES */
Object do_inspector_suppressed_warnings_notes(kb_search_state)
    Object kb_search_state;
{
    Object add_as_item_referring_to_name_qm, reference_serial_number, frame;
    Object ab_loop_list_, gensymed_symbol, xa, ya;
    char temp;
    Declare_special(1);

    x_note_fn_call(214,91);
    if (ISVREF(kb_search_state,(SI_Long)62L)) {
	add_as_item_referring_to_name_qm = T;
	reference_serial_number = ISVREF(kb_search_state,(SI_Long)24L);
	PUSH_SPECIAL(Add_as_item_referring_to_name_qm,add_as_item_referring_to_name_qm,
		0);
	  frame = Nil;
	  ab_loop_list_ = ISVREF(kb_search_state,(SI_Long)62L);
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  frame = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  gensymed_symbol = ISVREF(frame,(SI_Long)3L);
	  temp = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
		  Qavailable_frame_vector) : TRUEP(Qnil);
	  if (temp);
	  else
	      temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		      (SI_Long)-1L : TRUEP(Nil);
	  if (temp);
	  else if (FIXNUMP(reference_serial_number))
	      temp = FIXNUMP(gensymed_symbol) ? 
		      FIXNUM_LT(reference_serial_number,gensymed_symbol) : 
		      TRUEP(T);
	  else if (FIXNUMP(gensymed_symbol))
	      temp = TRUEP(Nil);
	  else {
	      xa = M_CAR(reference_serial_number);
	      ya = M_CAR(gensymed_symbol);
	      temp = FIXNUM_LT(xa,ya);
	      if (temp);
	      else
		  temp = FIXNUM_EQ(xa,ya) ? 
			  FIXNUM_LT(M_CDR(reference_serial_number),
			  M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	  }
	  if ( !temp)
	      post_analyzer_warning_note_if_necessary(frame);
	  goto next_loop;
	end_loop:;
	POP_SPECIAL();
    }
    return clear_suppressed_warnings_cache_if_necessary(kb_search_state);
}

static Object string_constant_35;  /* "Inspect was suspended while recompiling, but there was an item ~
				    *              with notes."
				    */

static Object string_constant_36;  /* "Inspect was suspended while recompiling, but there were ~d ~
				    *              items with notes."
				    */

/* SUMMARIZE-INSPECTOR-SUPPRESSED-WARNINGS-IF-ANY */
Object summarize_inspector_suppressed_warnings_if_any(kb_search_state)
    Object kb_search_state;
{
    Object length_1;

    x_note_fn_call(214,92);
    if (ISVREF(kb_search_state,(SI_Long)62L)) {
	length_1 = length(ISVREF(kb_search_state,(SI_Long)62L));
	if ((SI_Long)1L == IFIX(length_1))
	    return notify_user(1,string_constant_35);
	else
	    return notify_user(2,string_constant_36,length_1);
    }
    else
	return VALUES_1(Nil);
}

/* MULTIPLE-ADD-TO-RESULTS-FOR-INSPECT-COMMAND */
Object multiple_add_to_results_for_inspect_command(items_or_strings_qm,
	    inspect_command)
    Object items_or_strings_qm, inspect_command;
{
    Object search_state_qm, remotep, invisiblep, item_or_string, ab_loop_list_;

    x_note_fn_call(214,93);
    search_state_qm = 
	    get_search_state_for_inspect_command_results_if_any(inspect_command);
    remotep = search_state_qm ? ISVREF(search_state_qm,(SI_Long)65L) : Qnil;
    invisiblep = ISVREF(inspect_command,(SI_Long)21L);
    item_or_string = Nil;
    ab_loop_list_ = items_or_strings_qm;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item_or_string = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (text_string_p(item_or_string)) {
	if ( !TRUEP(invisiblep) && remotep)
	    item_or_string = copy_text_string(item_or_string);
	else if (invisiblep &&  !TRUEP(remotep))
	    reclaim_text_string(item_or_string);
	if ( !TRUEP(invisiblep))
	    add_to_inspect_search_results(make_message(1,item_or_string),
		    search_state_qm);
    }
    else
	add_to_inspect_search_results(make_short_representation(3,
		item_or_string,Nil,Nil),search_state_qm);
    goto next_loop;
  end_loop:
    if (remotep) {
	if (items_or_strings_qm)
	    return_remote_query_results(search_state_qm,
		    items_or_strings_qm,Nil);
    }
    else
	reclaim_gensym_list_1(items_or_strings_qm);
    return VALUES_1(Nil);
}

/* ADD-TO-INSPECT-SEARCH-RESULTS */
Object add_to_inspect_search_results(text_box_or_table,search_state)
    Object text_box_or_table, search_state;
{
    Object workspace_qm, gensymed_symbol_1, svref_new_value;
    SI_Long gensymed_symbol, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long svref_new_value_1;
    char temp;

    x_note_fn_call(214,94);
    workspace_qm = get_results_workspace_for_search_state_if_any(search_state);
    if (workspace_qm) {
	if ( !FIXNUM_LT(ISVREF(search_state,(SI_Long)58L),
		ISVREF(search_state,(SI_Long)60L))) {
	    gensymed_symbol = IFIX(ISVREF(search_state,(SI_Long)47L));
	    gensymed_symbol_1 = ISVREF(text_box_or_table,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_1 = ISVREF(text_box_or_table,(SI_Long)14L);
	    gensymed_symbol_1 = gensymed_symbol_1 ? 
		    ISVREF(gensymed_symbol_1,(SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	    gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	    temp = FIXNUM_GT(FIX(gensymed_symbol + gensymed_symbol_2),
		    ISVREF(search_state,(SI_Long)56L));
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    svref_new_value = ISVREF(search_state,(SI_Long)55L);
	    ISVREF(search_state,(SI_Long)47L) = svref_new_value;
	    svref_new_value_1 = IFIX(ISVREF(search_state,(SI_Long)57L)) + 
		    (SI_Long)10L;
	    ISVREF(search_state,(SI_Long)46L) = FIX(svref_new_value_1);
	    ISVREF(search_state,(SI_Long)58L) = FIX((SI_Long)0L);
	}
	add_to_workspace(6,text_box_or_table,ISVREF(search_state,
		(SI_Long)21L),ISVREF(search_state,(SI_Long)46L),
		ISVREF(search_state,(SI_Long)47L),T,T);
	gensymed_symbol_1 = ISVREF(text_box_or_table,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol = IFIX(gensymed_symbol_1);
	gensymed_symbol_2 = IFIX(ISVREF(search_state,(SI_Long)61L));
	svref_new_value_1 = gensymed_symbol + gensymed_symbol_2;
	ISVREF(search_state,(SI_Long)47L) = FIX(svref_new_value_1);
	gensymed_symbol_1 = ISVREF(text_box_or_table,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol = IFIX(gensymed_symbol_1);
	gensymed_symbol_2 = IFIX(ISVREF(search_state,(SI_Long)57L));
	svref_new_value_1 = MAX(gensymed_symbol,gensymed_symbol_2);
	ISVREF(search_state,(SI_Long)57L) = FIX(svref_new_value_1);
	svref_new_value = FIXNUM_ADD1(ISVREF(search_state,(SI_Long)58L));
	ISVREF(search_state,(SI_Long)58L) = svref_new_value;
    }
    return VALUES_1(Nil);
}

/* SEARCH-ITEMS */
Object search_items varargs_1(int, n)
{
    Object frames, item_filter_for_kb_search_qm, string_to_look_for_qm;
    Object replacement_string_qm, observance_of_word_boundary_qm;
    Object no_results_tables_qm, results_file_name_qm;
    Object ascii_results_file_name_qm, inspect_command_qm, visit_qm;
    Object display_a_table_qm, slot_denotations_for_showing_as_a_table_qm;
    Object recompile_found_items_qm, special_purpose_function_qm;
    Object special_purpose_arglist_qm, kb_search_state, svref_new_value;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,95);
    INIT_ARGS_nonrelocating();
    frames = REQUIRED_ARG_nonrelocating();
    item_filter_for_kb_search_qm = REQUIRED_ARG_nonrelocating();
    string_to_look_for_qm = REQUIRED_ARG_nonrelocating();
    replacement_string_qm = REQUIRED_ARG_nonrelocating();
    observance_of_word_boundary_qm = REQUIRED_ARG_nonrelocating();
    no_results_tables_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    results_file_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    ascii_results_file_name_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    inspect_command_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    visit_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    display_a_table_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    slot_denotations_for_showing_as_a_table_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() :
	     Nil;
    recompile_found_items_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    special_purpose_function_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    special_purpose_arglist_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    kb_search_state = create_kb_search_state(frames,
	    item_filter_for_kb_search_qm,string_to_look_for_qm,
	    replacement_string_qm,observance_of_word_boundary_qm,
	    no_results_tables_qm,results_file_name_qm,
	    ascii_results_file_name_qm,inspect_command_qm,visit_qm,
	    display_a_table_qm,slot_denotations_for_showing_as_a_table_qm,
	    recompile_found_items_qm,special_purpose_function_qm,
	    special_purpose_arglist_qm);
    svref_new_value = inspect_command_qm ? ISVREF(inspect_command_qm,
	    (SI_Long)22L) : Qnil;
    ISVREF(kb_search_state,(SI_Long)64L) = svref_new_value;
    svref_new_value = inspect_command_qm ? ISVREF(inspect_command_qm,
	    (SI_Long)21L) : Qnil;
    ISVREF(kb_search_state,(SI_Long)63L) = svref_new_value;
    svref_new_value = inspect_command_qm && ISVREF(inspect_command_qm,
	    (SI_Long)23L) ? Current_remote_search_representation_qm : Qnil;
    ISVREF(kb_search_state,(SI_Long)65L) = svref_new_value;
    return search_items_a_little(kb_search_state,ISVREF(kb_search_state,
	    (SI_Long)3L));
}

/* SET-KB-SEARCH-STATE-FOR-INSPECT-COMMAND */
Object set_kb_search_state_for_inspect_command(inspect_command,kb_search_state)
    Object inspect_command, kb_search_state;
{
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;

    x_note_fn_call(214,96);
    cancel_search_state_for_inspect_command_if_necessary(inspect_command);
    ISVREF(inspect_command,(SI_Long)19L) = kb_search_state;
    frame_serial_number_setf_arg = ISVREF(kb_search_state,(SI_Long)3L);
    old = ISVREF(inspect_command,(SI_Long)20L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    return VALUES_1(ISVREF(inspect_command,(SI_Long)20L) = svref_new_value);
}

static Object Qtables_substitution_state;  /* tables-substitution-state */

static Object Qtables_search_state;  /* tables-search-state */

static Object Qfile_output_search_state;  /* file-output-search-state */

static Object Qspecial_purpose_kb_search_state;  /* special-purpose-kb-search-state */

static Object Qtotal_number_of_items_to_examine;  /* total-number-of-items-to-examine */

static Object Qspecial_purpose_kb_search_function_qm;  /* special-purpose-kb-search-function? */

static Object Qspecial_purpose_kb_search_arglist_qm;  /* special-purpose-kb-search-arglist? */

/* CREATE-KB-SEARCH-STATE */
Object create_kb_search_state(frames,item_filter_for_kb_search_qm,
	    string_to_look_for_qm,replacement_string_qm,
	    observance_of_word_boundary_qm,no_results_tables_qm,
	    results_file_name_qm,ascii_results_file_name_qm,
	    inspect_command_qm,visit_qm,display_a_table_qm,
	    slot_denotations_for_showing_as_a_table_qm,
	    recompile_found_items_qm,special_purpose_function_qm,
	    special_purpose_arglist_qm)
    Object frames, item_filter_for_kb_search_qm, string_to_look_for_qm;
    Object replacement_string_qm, observance_of_word_boundary_qm;
    Object no_results_tables_qm, results_file_name_qm;
    Object ascii_results_file_name_qm, inspect_command_qm, visit_qm;
    Object display_a_table_qm, slot_denotations_for_showing_as_a_table_qm;
    Object recompile_found_items_qm, special_purpose_function_qm;
    Object special_purpose_arglist_qm;
{
    Object temp, kb_search_state, frame_serial_number_setf_arg, old, new_1;
    Object svref_new_value, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(214,97);
    if (replacement_string_qm)
	temp = Qtables_substitution_state;
    else if (string_to_look_for_qm)
	temp = Qtables_search_state;
    else if (results_file_name_qm)
	temp = Qfile_output_search_state;
    else if (special_purpose_function_qm)
	temp = Qspecial_purpose_kb_search_state;
    else
	temp = Qkb_search_state;
    kb_search_state = make_frame(temp);
    frame_serial_number_setf_arg = Current_frame_serial_number;
    old = ISVREF(kb_search_state,(SI_Long)24L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(kb_search_state,(SI_Long)24L) = svref_new_value;
    svref_new_value = copy_list_using_gensym_conses_1(frames);
    ISVREF(kb_search_state,(SI_Long)23L) = svref_new_value;
    if (Noting_changes_to_kb_p)
	note_change_to_block_1(kb_search_state,
		Qtotal_number_of_items_to_examine);
    svref_new_value = length(ISVREF(kb_search_state,(SI_Long)23L));
    SVREF(kb_search_state,FIX((SI_Long)29L)) = svref_new_value;
    ISVREF(kb_search_state,(SI_Long)53L) = no_results_tables_qm;
    ISVREF(kb_search_state,(SI_Long)52L) = recompile_found_items_qm;
    ISVREF(kb_search_state,(SI_Long)35L) = results_file_name_qm;
    ISVREF(kb_search_state,(SI_Long)36L) = ascii_results_file_name_qm;
    svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
    ISVREF(kb_search_state,(SI_Long)39L) = svref_new_value;
    ISVREF(kb_search_state,(SI_Long)40L) = svref_new_value;
    ISVREF(kb_search_state,(SI_Long)38L) = visit_qm;
    ISVREF(kb_search_state,(SI_Long)41L) = display_a_table_qm;
    ISVREF(kb_search_state,(SI_Long)44L) = 
	    slot_denotations_for_showing_as_a_table_qm;
    if (item_filter_for_kb_search_qm)
	compile_item_filter_into_kb_search_state(item_filter_for_kb_search_qm,
		kb_search_state);
    svref_new_value = string_to_look_for_qm ? 
	    copy_text_string(string_to_look_for_qm) : Nil;
    ISVREF(kb_search_state,(SI_Long)26L) = svref_new_value;
    svref_new_value = replacement_string_qm ? 
	    copy_text_string(replacement_string_qm) : Nil;
    ISVREF(kb_search_state,(SI_Long)27L) = svref_new_value;
    ISVREF(kb_search_state,(SI_Long)28L) = observance_of_word_boundary_qm;
    gensymed_symbol = 
	    lookup_global_or_kb_specific_property_value(Qspecial_purpose_kb_search_state,
	    Class_description_gkbprop);
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(ISVREF(kb_search_state,(SI_Long)1L),
		(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
	    temp_1 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_1 = TRUEP(Nil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	set_non_savable_lookup_slot_value(kb_search_state,
		Qspecial_purpose_kb_search_function_qm,
		special_purpose_function_qm);
	set_non_savable_lookup_slot_value(kb_search_state,
		Qspecial_purpose_kb_search_arglist_qm,
		special_purpose_arglist_qm);
    }
    if (inspect_command_qm)
	set_kb_search_state_for_inspect_command(inspect_command_qm,
		kb_search_state);
    if ( !(inspect_command_qm && ISVREF(inspect_command_qm,(SI_Long)21L)))
	set_kb_search_results_workspace(kb_search_state,inspect_command_qm);
    return VALUES_1(kb_search_state);
}

static Object Qitem_filter_for_kb_search_qm;  /* item-filter-for-kb-search? */

static Object list_constant_12;    /* # */

static Object list_constant_13;    /* # */

/* COMPILE-ITEM-FILTER-INTO-KB-SEARCH-STATE */
Object compile_item_filter_into_kb_search_state(item_filter,kb_search_state)
    Object item_filter, kb_search_state;
{
    Object gensymed_symbol, gensymed_symbol_1, current_edit_state, temp;
    Object current_block_of_dependent_frame, current_computation_frame;
    Object current_annotated_frame, temp_1, predicate_expression;
    Object post_compiler_warning_note_qm, third_new_value;
    Declare_stack_pointer;
    Declare_special(5);
    Object result;

    x_note_fn_call(214,98);
    SAVE_STACK();
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
    PUSH_SPECIAL(Current_edit_state,current_edit_state,4);
      temp = Current_edit_state;
      SVREF(temp,FIX((SI_Long)90L)) = gensymed_symbol_1;
      current_block_of_dependent_frame = kb_search_state;
      PUSH_SPECIAL(Current_block_of_dependent_frame,current_block_of_dependent_frame,
	      3);
	current_computation_frame = Current_block_of_dependent_frame;
	PUSH_SPECIAL(Current_computation_frame,current_computation_frame,2);
	  current_annotated_frame = Current_block_of_dependent_frame;
	  PUSH_SPECIAL(Current_annotated_frame,current_annotated_frame,1);
	    if (Noting_changes_to_kb_p)
		note_change_to_block_1(kb_search_state,
			Qitem_filter_for_kb_search_qm);
	    SVREF(kb_search_state,FIX((SI_Long)25L)) = item_filter;
	    temp_1 = CAR(item_filter);
	    predicate_expression = THIRD(temp_1);
	    temp = CAR(item_filter);
	    post_compiler_warning_note_qm = Nil;
	    PUSH_SPECIAL(Post_compiler_warning_note_qm,post_compiler_warning_note_qm,
		    0);
	      third_new_value = 
		      compile_a_compiled_cell_expression_from_expression_parse_and_style_description(predicate_expression,
		      list_constant_12,list_constant_13);
	    POP_SPECIAL();
	    M_THIRD(temp) = third_new_value;
	    SAVE_VALUES(reclaim_slot_value(predicate_expression));
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      if (gensymed_symbol) {
	  temp = Current_edit_state;
	  SVREF(temp,FIX((SI_Long)90L)) = Nil;
      }
      reclaim_edit_state_1(Current_edit_state);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

static Object Qsearch_state_table_format;  /* search-state-table-format */

static Object list_constant_14;    /* # */

static Object Qhide;               /* hide */

static Object Qsuspend;            /* suspend */

static Object Qab_continue;        /* continue */

static Object Qrerun;              /* rerun */

static Object Qedit;               /* edit */

static Object Qfinish_inspect_subcommand;  /* finish-inspect-subcommand */

static Object Qreclaim_finish_inspect_subcommand_arglist;  /* reclaim-finish-inspect-subcommand-arglist */

/* SET-KB-SEARCH-RESULTS-WORKSPACE */
Object set_kb_search_results_workspace(kb_search_state,inspect_command_qm)
    Object kb_search_state, inspect_command_qm;
{
    Object kb_search_results_workspace, table_for_kb_search_state;
    Object gensymed_symbol, gensymed_symbol_1, subcommand_menu_1;
    Object frame_serial_number_setf_arg, old, new_1, svref_new_value;
    Object ab_queue_form_, ab_next_queue_element_, subblock, ab_loopvar_;
    Object ab_loopvar__1, ab_loop_maxmin_fl_, temp;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, svref_new_value_1;
    SI_Long gensymed_symbol_4, gensymed_symbol_5;

    x_note_fn_call(214,99);
    kb_search_results_workspace = inspect_command_qm ? 
	    get_and_clear_workspace_for_inspect_command(2,
	    inspect_command_qm,kb_search_state) : Nil;
    if (kb_search_results_workspace);
    else
	kb_search_results_workspace = make_inspect_workspace(1,
		inspect_command_qm);
    table_for_kb_search_state = make_attributes_table(6,kb_search_state,
	    Qsearch_state_table_format,Nil,Nil,Nil,list_constant_14);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)5L));
    gensymed_symbol_1 = gensymed_symbol;
    M_CAR(gensymed_symbol_1) = Qhide;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qsuspend;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qab_continue;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qrerun;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    M_CAR(gensymed_symbol_1) = Qedit;
    subcommand_menu_1 = make_subcommand_menu(1,gensymed_symbol);
    ISVREF(kb_search_state,(SI_Long)21L) = kb_search_results_workspace;
    frame_serial_number_setf_arg = ISVREF(kb_search_results_workspace,
	    (SI_Long)3L);
    old = ISVREF(kb_search_state,(SI_Long)22L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(kb_search_state,(SI_Long)22L) = svref_new_value;
    gensymed_symbol = ISVREF(kb_search_results_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = IFIX(ISVREF(kb_search_results_workspace,(SI_Long)17L));
    svref_new_value_1 = gensymed_symbol_2 + gensymed_symbol_3;
    ISVREF(kb_search_state,(SI_Long)46L) = FIX(svref_new_value_1);
    gensymed_symbol = ISVREF(kb_search_results_workspace,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)4L) : Nil;
    ab_queue_form_ = gensymed_symbol;
    ab_next_queue_element_ = Nil;
    subblock = Nil;
    ab_loopvar_ = FIX((SI_Long)0L);
    ab_loopvar__1 = FIX((SI_Long)0L);
    ab_loop_maxmin_fl_ = T;
    if (ab_queue_form_)
	ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
  next_loop:
    if (EQ(ab_next_queue_element_,ab_queue_form_))
	goto end_loop;
    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,(SI_Long)0L);
    gensymed_symbol = ISVREF(subblock,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    ab_loopvar__1 = gensymed_symbol;
    if (ab_loop_maxmin_fl_) {
	ab_loop_maxmin_fl_ = Nil;
	ab_loopvar_ = ab_loopvar__1;
    }
    else
	ab_loopvar_ = lmax(ab_loopvar_,ab_loopvar__1);
    goto next_loop;
  end_loop:
    gensymed_symbol_2 = IFIX(ab_loopvar_);
    goto end_1;
    gensymed_symbol_2 = IFIX(Qnil);
  end_1:;
    gensymed_symbol_3 = (SI_Long)5L;
    svref_new_value_1 = gensymed_symbol_2 + gensymed_symbol_3;
    ISVREF(kb_search_state,(SI_Long)47L) = FIX(svref_new_value_1);
    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = IFIX(ISVREF(kb_search_results_workspace,(SI_Long)17L));
    gensymed_symbol = ISVREF(subcommand_menu_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)2L) : FIX((SI_Long)0L);
    gensymed_symbol_4 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(subcommand_menu_1,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_5 = IFIX(gensymed_symbol);
    gensymed_symbol_4 = gensymed_symbol_4 - gensymed_symbol_5;
    temp = FIX(gensymed_symbol_2 - gensymed_symbol_3 - gensymed_symbol_4);
    gensymed_symbol = ISVREF(inspect_command_qm,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    add_to_workspace(4,subcommand_menu_1,kb_search_results_workspace,temp,
	    gensymed_symbol);
    ISVREF(subcommand_menu_1,(SI_Long)27L) = Qfinish_inspect_subcommand;
    temp = copy_frame_serial_number(ISVREF(inspect_command_qm,(SI_Long)3L));
    svref_new_value = gensym_list_4(inspect_command_qm,temp,
	    kb_search_state,
	    copy_frame_serial_number(ISVREF(kb_search_state,(SI_Long)3L)));
    ISVREF(subcommand_menu_1,(SI_Long)28L) = svref_new_value;
    svref_new_value = 
	    SYMBOL_FUNCTION(Qreclaim_finish_inspect_subcommand_arglist);
    ISVREF(subcommand_menu_1,(SI_Long)29L) = svref_new_value;
    enable_or_disable_subcommand(3,subcommand_menu_1,Qhide,Nil);
    enable_or_disable_subcommand(3,subcommand_menu_1,Qsuspend,Nil);
    enable_or_disable_subcommand(3,subcommand_menu_1,Qab_continue,T);
    enable_or_disable_subcommand(3,subcommand_menu_1,Qrerun,Nil);
    enable_or_disable_subcommand(3,subcommand_menu_1,Qedit,Nil);
    ISVREF(kb_search_state,(SI_Long)48L) = subcommand_menu_1;
    frame_serial_number_setf_arg = ISVREF(subcommand_menu_1,(SI_Long)3L);
    old = ISVREF(kb_search_state,(SI_Long)49L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(kb_search_state,(SI_Long)49L) = svref_new_value;
    ISVREF(kb_search_state,(SI_Long)50L) = inspect_command_qm;
    frame_serial_number_setf_arg = ISVREF(inspect_command_qm,(SI_Long)3L);
    old = ISVREF(kb_search_state,(SI_Long)51L);
    new_1 = frame_serial_number_setf_arg;
    svref_new_value = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) || 
	     !TRUEP(new_1)) ? new_1 : 
	    frame_serial_number_setf_helper_1(old,new_1);
    ISVREF(kb_search_state,(SI_Long)51L) = svref_new_value;
    add_to_workspace(6,table_for_kb_search_state,
	    kb_search_results_workspace,ISVREF(kb_search_state,
	    (SI_Long)46L),ISVREF(kb_search_state,(SI_Long)47L),T,T);
    gensymed_symbol = ISVREF(table_for_kb_search_state,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_3 = (SI_Long)60L;
    svref_new_value_1 = gensymed_symbol_2 + gensymed_symbol_3;
    ISVREF(kb_search_state,(SI_Long)47L) = FIX(svref_new_value_1);
    svref_new_value = ISVREF(kb_search_state,(SI_Long)47L);
    ISVREF(kb_search_state,(SI_Long)55L) = svref_new_value;
    svref_new_value = FIXNUM_ADD(ISVREF(kb_search_state,(SI_Long)47L),
	    ISVREF(kb_search_state,(SI_Long)59L));
    ISVREF(kb_search_state,(SI_Long)56L) = svref_new_value;
    svref_new_value = ISVREF(kb_search_state,(SI_Long)46L);
    ISVREF(kb_search_state,(SI_Long)57L) = svref_new_value;
    ISVREF(kb_search_state,(SI_Long)58L) = FIX((SI_Long)0L);
    return put_inspect_workspace_on_current_detail_pane(kb_search_results_workspace);
}

static Object Qfile_name_for_printing_search_results_qm;  /* file-name-for-printing-search-results? */

static Object string_constant_37;  /* "unable to open file" */

static Object Qnumber_of_substitutions_in_tables;  /* number-of-substitutions-in-tables */

static Object Qnumber_of_resulting_parsing_failures;  /* number-of-resulting-parsing-failures */

static Object Qnumber_of_items_found;  /* number-of-items-found */

static Object Qnumber_of_items_examined_so_far;  /* number-of-items-examined-so-far */

static Object Qnumber_of_occurrences_in_tables;  /* number-of-occurrences-in-tables */

static Object Qkb_search_status_qm;  /* kb-search-status? */

/* SEARCH-ITEMS-A-LITTLE */
Object search_items_a_little(kb_search_state,frame_serial_number)
    Object kb_search_state, frame_serial_number;
{
    Object gensymed_symbol, xa, ya, kb_search_results_workspace;
    Object item_filter_for_kb_search_qm, string_to_look_for_qm;
    Object replacement_string_qm, observance_of_word_boundary_qm;
    Object file_stream_for_printing_search_results_qm, table_qm;
    Object key_slot_name_if_no_occurrence_qm;
    Object filtered_items_for_this_time_slice, frames_for_kb_search;
    Object old_kb_search_result_tables_and_text_boxes, frame;
    Object frame_serial_number_for_kb_search, ab_loop_iter_flag_;
    Object original_file_name_qm, ascii_file_name, truename_1, svref_new_value;
    Object sub_class_bit_vector, temp_1, x, slot_denotations_to_show_qm;
    Object foundp, gathering_normally_editable_slots_for_search_qm, table_rows;
    Object slot_denotations, number_of_substitutions;
    Object number_of_resulting_parsing_failures;
    Object keep_edit_workspace_hidden_no_matter_what_qm, temp_2;
    Object number_of_occurrences, incff_1_arg;
    Object suppress_consistency_analysis_warnings_notes_qm;
    Object do_not_update_frame_authors_qm, fixnum_time_now, y;
    Object number_of_frames_remaining;
    Object safe_to_access_attribute_display_update_interval_p;
    Object frame_representation, ab_loop_list_;
    SI_Long number_of_items_examined_so_far, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, svref_new_value_1;
    char temp;
    Declare_special(3);
    Object result;

    x_note_fn_call(214,100);
    gensymed_symbol = ISVREF(kb_search_state,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(kb_search_state) ? EQ(ISVREF(kb_search_state,
	    (SI_Long)1L),Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	kb_search_results_workspace = 
		get_results_workspace_for_search_state_if_any(kb_search_state);
	item_filter_for_kb_search_qm = ISVREF(kb_search_state,(SI_Long)25L);
	string_to_look_for_qm = ISVREF(kb_search_state,(SI_Long)26L);
	replacement_string_qm = ISVREF(kb_search_state,(SI_Long)27L);
	observance_of_word_boundary_qm = ISVREF(kb_search_state,(SI_Long)28L);
	file_stream_for_printing_search_results_qm = 
		ISVREF(kb_search_state,(SI_Long)37L);
	table_qm = Nil;
	key_slot_name_if_no_occurrence_qm = Nil;
	filtered_items_for_this_time_slice = Nil;
	frames_for_kb_search = Nil;
	old_kb_search_result_tables_and_text_boxes = Nil;
	frame = Nil;
	frame_serial_number_for_kb_search = Nil;
	number_of_items_examined_so_far = IFIX(ISVREF(kb_search_state,
		(SI_Long)30L));
	ab_loop_iter_flag_ = T;
	original_file_name_qm = ISVREF(kb_search_state,(SI_Long)35L);
	if (original_file_name_qm &&  !TRUEP(ISVREF(kb_search_state,
		(SI_Long)37L))) {
	    ascii_file_name = ISVREF(kb_search_state,(SI_Long)36L);
	    file_stream_for_printing_search_results_qm = 
		    open_file_for_search_results(ascii_file_name,
		    ISVREF(kb_search_state,(SI_Long)50L));
	    ISVREF(kb_search_state,(SI_Long)37L) = 
		    file_stream_for_printing_search_results_qm;
	    if (file_stream_for_printing_search_results_qm) {
		reclaim_text_string(original_file_name_qm);
		truename_1 = 
			gensym_truename(file_stream_for_printing_search_results_qm);
		svref_new_value = gensym_namestring_as_text_string(1,
			truename_1);
		ISVREF(kb_search_state,(SI_Long)35L) = svref_new_value;
		reclaim_gensym_pathname(truename_1);
		update_representations_of_slot_value(2,kb_search_state,
			Qfile_name_for_printing_search_results_qm);
	    }
	    else {
		svref_new_value = tformat_text_string(1,string_constant_37);
		ISVREF(kb_search_state,(SI_Long)54L) = svref_new_value;
		goto end_loop;
	    }
	}
      next_loop:
	frames_for_kb_search = ISVREF(kb_search_state,(SI_Long)23L);
	old_kb_search_result_tables_and_text_boxes = 
		ISVREF(kb_search_state,(SI_Long)45L);
	frame = CAR(frames_for_kb_search);
	frame_serial_number_for_kb_search = 
		copy_frame_serial_number(ISVREF(kb_search_state,(SI_Long)24L));
	if ( !TRUEP(ab_loop_iter_flag_))
	    number_of_items_examined_so_far = 
		    number_of_items_examined_so_far + (SI_Long)1L;
	temp = TRUEP(frames_for_kb_search);
	if (temp);
	else
	    temp = TRUEP(old_kb_search_result_tables_and_text_boxes);
	if (temp);
	else {
	    gensymed_symbol = 
		    lookup_global_or_kb_specific_property_value(Qspecial_purpose_kb_search_state,
		    Class_description_gkbprop);
	    if (gensymed_symbol) {
		sub_class_bit_vector = ISVREF(ISVREF(kb_search_state,
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
	    if (temp ? 
		    TRUEP(get_lookup_slot_value_given_default(kb_search_state,
		    Qspecial_purpose_kb_search_function_qm,Nil)) : 
			TRUEP(Nil)) {
		temp_1 = 
			get_lookup_slot_value_given_default(kb_search_state,
			Qspecial_purpose_kb_search_function_qm,Nil);
		temp = TRUEP(APPLY_1(temp_1,
			get_lookup_slot_value_given_default(kb_search_state,
			Qspecial_purpose_kb_search_arglist_qm,Nil)));
	    }
	    else
		temp = TRUEP(Nil);
	}
	if ( !temp)
	    goto end_loop;
	if (old_kb_search_result_tables_and_text_boxes) {
	    gensymed_symbol = 
		    ISVREF(CAR(old_kb_search_result_tables_and_text_boxes),
		    (SI_Long)3L);
	    x = CAR(old_kb_search_result_tables_and_text_boxes);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(frame_serial_number_for_kb_search))
		temp = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_serial_number_for_kb_search,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number_for_kb_search);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number_for_kb_search),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp)
		delete_table_or_text_box(CAR(old_kb_search_result_tables_and_text_boxes));
	    svref_new_value = CDR(old_kb_search_result_tables_and_text_boxes);
	    ISVREF(kb_search_state,(SI_Long)45L) = svref_new_value;
	    reclaim_gensym_cons_1(old_kb_search_result_tables_and_text_boxes);
	    temp_1 = ISVREF(kb_search_state,(SI_Long)45L);
	    old_kb_search_result_tables_and_text_boxes = CDR(temp_1);
	}
	if (frames_for_kb_search) {
	    slot_denotations_to_show_qm = ISVREF(kb_search_state,(SI_Long)44L);
	    gensymed_symbol = ISVREF(frame,(SI_Long)3L);
	    temp = SIMPLE_VECTOR_P(frame) ? EQ(ISVREF(frame,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else if (FIXNUMP(frame_serial_number_for_kb_search))
		temp = FIXNUMP(gensymed_symbol) ? 
			FIXNUM_LT(frame_serial_number_for_kb_search,
			gensymed_symbol) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol))
		temp = TRUEP(Nil);
	    else {
		xa = M_CAR(frame_serial_number_for_kb_search);
		ya = M_CAR(gensymed_symbol);
		temp = FIXNUM_LT(xa,ya);
		if (temp);
		else
		    temp = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(frame_serial_number_for_kb_search),
			    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	    }
	    if ( !temp ?  !TRUEP(item_filter_for_kb_search_qm) || 
		    frame_matches_item_filter_p(kb_search_state,frame,
		    item_filter_for_kb_search_qm) : TRUEP(Nil)) {
		temp = ISVREF(kb_search_state,(SI_Long)41L) || 
			ISVREF(kb_search_state,(SI_Long)53L) ?  
			!TRUEP(string_to_look_for_qm) : TRUEP(Qnil);
		if (temp);
		else {
		    foundp = Nil;
		    gathering_normally_editable_slots_for_search_qm =  
			    !TRUEP(replacement_string_qm) ? T : Nil;
		    PUSH_SPECIAL(Gathering_normally_editable_slots_for_search_qm,gathering_normally_editable_slots_for_search_qm,
			    0);
		      result = make_short_representation_for_queries(frame,
			      string_to_look_for_qm,
			      observance_of_word_boundary_qm,
			      replacement_string_qm,
			      slot_denotations_to_show_qm,Nil);
		      MVS_3(result,foundp,table_qm,
			      key_slot_name_if_no_occurrence_qm);
		      temp = TRUEP(foundp);
		    POP_SPECIAL();
		}
	    }
	    else
		temp = TRUEP(Nil);
	    if (temp) {
		if (ISVREF(kb_search_state,(SI_Long)41L) || 
			ISVREF(kb_search_state,(SI_Long)53L)) {
		    if (table_qm) {
			delete_frame(table_qm);
			table_qm = Nil;
			key_slot_name_if_no_occurrence_qm = Nil;
		    }
		    if (ISVREF(kb_search_state,(SI_Long)41L)) {
			result = merge_frame_into_multiframe_table_rows(4,
				frame,slot_denotations_to_show_qm,
				ISVREF(kb_search_state,(SI_Long)42L),
				ISVREF(kb_search_state,(SI_Long)43L));
			MVS_2(result,table_rows,slot_denotations);
			ISVREF(kb_search_state,(SI_Long)42L) = table_rows;
			ISVREF(kb_search_state,(SI_Long)43L) = 
				slot_denotations;
		    }
		}
		else {
		    number_of_substitutions = Nil;
		    number_of_resulting_parsing_failures = Nil;
		    if (replacement_string_qm) {
			keep_edit_workspace_hidden_no_matter_what_qm = 
				ISVREF(kb_search_state,(SI_Long)63L);
			PUSH_SPECIAL(Keep_edit_workspace_hidden_no_matter_what_qm,keep_edit_workspace_hidden_no_matter_what_qm,
				0);
			  result = replace_editable_occurrences_of_string_in_table(5,
				  table_qm,string_to_look_for_qm,
				  replacement_string_qm,
				  observance_of_word_boundary_qm,
				  key_slot_name_if_no_occurrence_qm);
			POP_SPECIAL();
			MVS_2(result,number_of_substitutions,
				number_of_resulting_parsing_failures);
			if (IFIX(number_of_substitutions) > (SI_Long)0L)
			    change_slot_value(3,kb_search_state,
				    Qnumber_of_substitutions_in_tables,
				    FIXNUM_ADD(ISVREF(kb_search_state,
				    (SI_Long)31L),number_of_substitutions));
			if (IFIX(number_of_resulting_parsing_failures) > 
				(SI_Long)0L)
			    change_slot_value(3,kb_search_state,
				    Qnumber_of_resulting_parsing_failures,
				    FIXNUM_ADD(ISVREF(kb_search_state,
				    (SI_Long)32L),
				    number_of_resulting_parsing_failures));
			if ( !((SI_Long)0L == IFIX(number_of_substitutions))) {
			    svref_new_value = 
				    FIXNUM_ADD1(ISVREF(kb_search_state,
				    (SI_Long)33L));
			    if (Noting_changes_to_kb_p)
				note_change_to_block_1(kb_search_state,
					Qnumber_of_items_found);
			    SVREF(kb_search_state,FIX((SI_Long)33L)) = 
				    svref_new_value;
			}
		    }
		    if (string_to_look_for_qm && ( 
			    !TRUEP(replacement_string_qm) || 
			    IFIX(number_of_substitutions) > (SI_Long)0L)) {
			temp_2 = table_qm;
			temp_1 = replacement_string_qm;
			if (temp_1);
			else
			    temp_1 = string_to_look_for_qm;
			number_of_occurrences = 
				mark_occurrences_of_string_in_table(6,
				temp_2,temp_1,
				observance_of_word_boundary_qm,T,Nil,
				key_slot_name_if_no_occurrence_qm);
			if (IFIX(number_of_occurrences) > (SI_Long)0L) {
			    incff_1_arg = number_of_occurrences;
			    svref_new_value = 
				    FIXNUM_ADD(ISVREF(kb_search_state,
				    (SI_Long)34L),incff_1_arg);
			    ISVREF(kb_search_state,(SI_Long)34L) = 
				    svref_new_value;
			}
		    }
		    if (ISVREF(kb_search_state,(SI_Long)63L)) {
			if (table_qm)
			    delete_frame(table_qm);
		    }
		    else
			add_to_inspect_search_results(table_qm,
				kb_search_state);
		}
		if (ISVREF(kb_search_state,(SI_Long)38L) &&  
			!TRUEP(ISVREF(kb_search_state,(SI_Long)63L)))
		    goto_frame_instance(frame);
		if (file_stream_for_printing_search_results_qm)
		    print_frame_to_file_for_search_results(file_stream_for_printing_search_results_qm,
			    frame,slot_denotations_to_show_qm);
		if (ISVREF(kb_search_state,(SI_Long)65L))
		    filtered_items_for_this_time_slice = 
			    gensym_cons_1(frame,
			    filtered_items_for_this_time_slice);
		if (ISVREF(kb_search_state,(SI_Long)52L)) {
		    keep_edit_workspace_hidden_no_matter_what_qm = 
			    ISVREF(kb_search_state,(SI_Long)63L);
		    PUSH_SPECIAL(Keep_edit_workspace_hidden_no_matter_what_qm,keep_edit_workspace_hidden_no_matter_what_qm,
			    2);
		      suppress_consistency_analysis_warnings_notes_qm = T;
		      do_not_update_frame_authors_qm = T;
		      PUSH_SPECIAL(Do_not_update_frame_authors_qm,do_not_update_frame_authors_qm,
			      1);
			PUSH_SPECIAL(Suppress_consistency_analysis_warnings_notes_qm,suppress_consistency_analysis_warnings_notes_qm,
				0);
			  recompile_item(frame);
			  temp_1 = ISVREF(frame,(SI_Long)8L);
			  if (CDR(temp_1))
			      note_frame_for_inspector_suppressed_warnings(frame,
				      kb_search_state);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		}
		if ( !TRUEP(replacement_string_qm)) {
		    svref_new_value = FIXNUM_ADD1(ISVREF(kb_search_state,
			    (SI_Long)33L));
		    if (Noting_changes_to_kb_p)
			note_change_to_block_1(kb_search_state,
				Qnumber_of_items_found);
		    SVREF(kb_search_state,FIX((SI_Long)33L)) = svref_new_value;
		}
	    }
	    svref_new_value = CDR(frames_for_kb_search);
	    ISVREF(kb_search_state,(SI_Long)23L) = svref_new_value;
	    M_CDR(frames_for_kb_search) = Nil;
	    reclaim_gensym_cons_1(frames_for_kb_search);
	    fixnum_time_now = c_native_clock_ticks_or_cache(Nil,Nil);
	    gensymed_symbol_1 = IFIX(fixnum_time_now);
	    gensymed_symbol_2 = IFIX(ISVREF(kb_search_state,(SI_Long)40L));
	    if (gensymed_symbol_1 >= gensymed_symbol_2)
		temp_1 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	    else {
		gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
		gensymed_symbol_1 = gensymed_symbol_1 + 
			IFIX(Most_positive_fixnum);
		temp_1 = FIX(gensymed_symbol_1 + (SI_Long)1L);
	    }
	    if (FIXNUM_GE(temp_1,Fixnum_time_interval_for_one_second)) {
		change_slot_value(3,kb_search_state,
			Qnumber_of_items_examined_so_far,
			FIX(number_of_items_examined_so_far + (SI_Long)1L));
		update_representations_of_slot_value(2,kb_search_state,
			Qnumber_of_items_found);
		update_representations_of_slot_value(2,kb_search_state,
			Qnumber_of_occurrences_in_tables);
		update_representations_of_slot_value(2,kb_search_state,
			Qkb_search_status_qm);
		ISVREF(kb_search_state,(SI_Long)40L) = fixnum_time_now;
	    }
	    else {
		if (Noting_changes_to_kb_p)
		    note_change_to_block_1(kb_search_state,
			    Qnumber_of_items_examined_so_far);
		svref_new_value_1 = number_of_items_examined_so_far + 
			(SI_Long)1L;
		ISVREF(kb_search_state,(SI_Long)30L) = FIX(svref_new_value_1);
	    }
	}
	if (ISVREF(kb_search_state,(SI_Long)64L) ? TRUEP(Nil) : 
		TRUEP(time_slice_expired_p())) {
	    if (ISVREF(kb_search_state,(SI_Long)65L)) {
		return_remote_query_results(kb_search_state,
			filtered_items_for_this_time_slice,Nil);
		schedule_search_task(kb_search_state);
		return VALUES_1(Nil);
	    }
	    else {
		schedule_search_with_workstation_necessary(kb_search_state);
		return VALUES_1(Nil);
	    }
	}
	ab_loop_iter_flag_ = Nil;
	goto next_loop;
      end_loop:
	if (ISVREF(kb_search_state,(SI_Long)48L)) {
	    gensymed_symbol = ISVREF(ISVREF(kb_search_state,(SI_Long)48L),
		    (SI_Long)3L);
	    x = ISVREF(kb_search_state,(SI_Long)48L);
	    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp);
	    else
		temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
			(SI_Long)-1L : TRUEP(Nil);
	    if (temp);
	    else {
		x = gensymed_symbol;
		y = ISVREF(kb_search_state,(SI_Long)49L);
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
	if (temp) {
	    enable_or_disable_subcommand(3,ISVREF(kb_search_state,
		    (SI_Long)48L),Qsuspend,T);
	    enable_or_disable_subcommand(3,ISVREF(kb_search_state,
		    (SI_Long)48L),Qab_continue,T);
	}
	update_representations_of_slot_value(2,kb_search_state,
		Qnumber_of_items_examined_so_far);
	update_representations_of_slot_value(2,kb_search_state,
		Qnumber_of_items_found);
	update_representations_of_slot_value(2,kb_search_state,
		Qnumber_of_occurrences_in_tables);
	update_representations_of_slot_value(2,kb_search_state,
		Qkb_search_status_qm);
	svref_new_value = c_native_clock_ticks_or_cache(Nil,Nil);
	ISVREF(kb_search_state,(SI_Long)40L) = svref_new_value;
	if (ISVREF(kb_search_state,(SI_Long)62L))
	    do_inspector_suppressed_warnings_notes(kb_search_state);
	if (kb_search_results_workspace) {
	    if (ISVREF(kb_search_state,(SI_Long)41L) && 
		    ISVREF(kb_search_state,(SI_Long)42L)) {
		result = remove_deleted_frames_in_multiframe_table_rows(ISVREF(kb_search_state,
			(SI_Long)42L),frame_serial_number_for_kb_search);
		MVS_2(result,table_rows,number_of_frames_remaining);
		ISVREF(kb_search_state,(SI_Long)42L) = table_rows;
		change_slot_value(3,kb_search_state,Qnumber_of_items_found,
			number_of_frames_remaining);
		if (IFIX(number_of_frames_remaining) > (SI_Long)0L) {
		    temp_1 = finish_making_multiframe_table(2,
			    ISVREF(kb_search_state,(SI_Long)42L),
			    EQ(ISVREF(kb_search_state,(SI_Long)41L),
			    Qcolumnwise) ? T : Nil);
		    ISVREF(kb_search_state,(SI_Long)42L) = Nil;
		    add_to_workspace(6,temp_1,kb_search_results_workspace,
			    ISVREF(kb_search_state,(SI_Long)46L),
			    ISVREF(kb_search_state,(SI_Long)47L),T,T);
		}
	    }
	    shrink_wrap_workspace(kb_search_results_workspace);
	}
	reclaim_frame_serial_number(frame_serial_number_for_kb_search);
	if (ISVREF(kb_search_state,(SI_Long)37L)) {
	    temp_1 = Nil;
	    ISVREF(kb_search_state,(SI_Long)54L) = T;
	    close_file_for_search_results(ISVREF(kb_search_state,
		    (SI_Long)37L));
	    ISVREF(kb_search_state,(SI_Long)37L) = temp_1;
	}
	safe_to_access_attribute_display_update_interval_p = Nil;
	PUSH_SPECIAL(Safe_to_access_attribute_display_update_interval_p,safe_to_access_attribute_display_update_interval_p,
		0);
	  update_representations(kb_search_state);
	POP_SPECIAL();
	table_qm = Nil;
      next_loop_1:
	frame_representation = Nil;
	ab_loop_list_ = ISVREF(kb_search_state,(SI_Long)9L);
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	frame_representation = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	sub_class_bit_vector = ISVREF(ISVREF(frame_representation,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Table_class_description,
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
	if (temp) {
	    table_qm = frame_representation;
	    goto end_1;
	}
	goto next_loop_2;
      end_loop_1:
	table_qm = Qnil;
      end_1:;
	if ( !TRUEP(table_qm))
	    goto end_loop_2;
	detach_table_from_frames_it_represents(table_qm);
	goto next_loop_1;
      end_loop_2:;
	if (ISVREF(kb_search_state,(SI_Long)65L))
	    return_remote_query_results(kb_search_state,
		    filtered_items_for_this_time_slice,T);
	else {
	    cancel_scheduled_search_if_necessary(kb_search_state);
	    delete_frame(kb_search_state);
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qtable_rows;         /* table-rows */

/* DELETE-TABLE-OR-TEXT-BOX */
Object delete_table_or_text_box(table_or_text_box)
    Object table_or_text_box;
{
    Object sub_class_bit_vector, table_rows;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,101);
    sub_class_bit_vector = ISVREF(ISVREF(table_or_text_box,(SI_Long)1L),
	    (SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Text_box_class_description,
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
    if (temp);
    else {
	detach_table_from_frames_it_represents(table_or_text_box);
	table_rows = ISVREF(table_or_text_box,(SI_Long)19L);
	if (Noting_changes_to_kb_p)
	    note_change_to_block_1(table_or_text_box,Qtable_rows);
	SVREF(table_or_text_box,FIX((SI_Long)19L)) = Nil;
	reclaim_slot_value(table_rows);
    }
    return delete_frame(table_or_text_box);
}

/* CANCEL-SCHEDULED-SEARCH-IF-NECESSARY */
Object cancel_scheduled_search_if_necessary(kb_search_state)
    Object kb_search_state;
{
    Object workstation, entry_in_this_workstation_qm, svref_new_value;

    x_note_fn_call(214,102);
    if (ISVREF(kb_search_state,(SI_Long)64L) || ISVREF(kb_search_state,
	    (SI_Long)65L))
	return VALUES_1(Nil);
    workstation = ISVREF(ISVREF(kb_search_state,(SI_Long)21L),(SI_Long)27L);
    entry_in_this_workstation_qm = Nil;
    if ( !TRUEP(workstation))
	return VALUES_1(Nil);
    entry_in_this_workstation_qm = assq_function(kb_search_state,
	    ISVREF(workstation,(SI_Long)31L));
    if (entry_in_this_workstation_qm) {
	svref_new_value = 
		delete_gensym_element_1(entry_in_this_workstation_qm,
		ISVREF(workstation,(SI_Long)31L));
	SVREF(workstation,FIX((SI_Long)31L)) = svref_new_value;
	reclaim_frame_serial_number(CDR(entry_in_this_workstation_qm));
	return reclaim_gensym_cons_1(entry_in_this_workstation_qm);
    }
    else
	return VALUES_1(Nil);
}

/* SCHEDULE-SEARCH-WITH-WORKSTATION-NECESSARY */
Object schedule_search_with_workstation_necessary(kb_search_state)
    Object kb_search_state;
{
    Object svref_arg_1, temp, svref_new_value;

    x_note_fn_call(214,103);
    if ( !TRUEP(assq_function(kb_search_state,ISVREF(Current_workstation,
	    (SI_Long)31L)))) {
	svref_arg_1 = Current_workstation;
	temp = gensym_cons_1(kb_search_state,
		copy_frame_serial_number(ISVREF(kb_search_state,(SI_Long)3L)));
	svref_new_value = gensym_cons_1(temp,ISVREF(Current_workstation,
		(SI_Long)31L));
	return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)31L)) = 
		svref_new_value);
    }
    else
	return VALUES_1(Nil);
}

/* SUSPEND-INSPECT-KB-SEARCH */
Object suspend_inspect_kb_search(subcommand_menu_1,kb_search_state)
    Object subcommand_menu_1, kb_search_state;
{
    x_note_fn_call(214,104);
    cancel_scheduled_search_if_necessary(kb_search_state);
    enable_or_disable_subcommand(3,subcommand_menu_1,Qsuspend,T);
    enable_or_disable_subcommand(3,subcommand_menu_1,Qab_continue,Nil);
    return summarize_inspector_suppressed_warnings_if_any(kb_search_state);
}

/* FINISH-INSPECT-SUBCOMMAND */
Object finish_inspect_subcommand(subcommand_menu_1,command,inspect_command,
	    frame_serial_number_for_inspect_command,kb_search_state,
	    frame_serial_number_for_kb_search_state)
    Object subcommand_menu_1, command, inspect_command;
    Object frame_serial_number_for_inspect_command, kb_search_state;
    Object frame_serial_number_for_kb_search_state;
{
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(214,105);
    if (EQ(command,Qhide)) {
	gensymed_symbol = ISVREF(inspect_command,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(inspect_command) ? 
		EQ(ISVREF(inspect_command,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number_for_inspect_command))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number_for_inspect_command,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number_for_inspect_command);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number_for_inspect_command),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    gensymed_symbol = ISVREF(inspect_command,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)5L) : Nil;
	    return delete_frame(gensymed_symbol);
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command,Qsuspend) || EQ(command,Qab_continue)) {
	gensymed_symbol = ISVREF(kb_search_state,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(kb_search_state) ? 
		EQ(ISVREF(kb_search_state,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number_for_kb_search_state))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number_for_kb_search_state,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number_for_kb_search_state);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number_for_kb_search_state),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    if (EQ(command,Qsuspend))
		return suspend_inspect_kb_search(subcommand_menu_1,
			kb_search_state);
	    else {
		schedule_search_with_workstation_necessary(kb_search_state);
		enable_or_disable_subcommand(3,subcommand_menu_1,Qsuspend,Nil);
		return enable_or_disable_subcommand(3,subcommand_menu_1,
			Qab_continue,T);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else if (EQ(command,Qrerun) || EQ(command,Qedit)) {
	gensymed_symbol = ISVREF(inspect_command,(SI_Long)3L);
	temp = SIMPLE_VECTOR_P(inspect_command) ? 
		EQ(ISVREF(inspect_command,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp);
	else
	    temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp);
	else if (FIXNUMP(frame_serial_number_for_inspect_command))
	    temp = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_serial_number_for_inspect_command,
		    gensymed_symbol) : TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_serial_number_for_inspect_command);
	    ya = M_CAR(gensymed_symbol);
	    temp = FIXNUM_LT(xa,ya);
	    if (temp);
	    else
		temp = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_serial_number_for_inspect_command),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	if ( !temp) {
	    handle_inspect_command(4,inspect_command,Nil,Nil,EQ(command,
		    Qrerun) ? T : Nil);
	    if (EQ(command,Qedit))
		return enable_or_disable_subcommand(3,subcommand_menu_1,
			command,Nil);
	    else
		return VALUES_1(Nil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

/* RECLAIM-FINISH-INSPECT-SUBCOMMAND-ARGLIST */
Object reclaim_finish_inspect_subcommand_arglist(arglist)
    Object arglist;
{
    x_note_fn_call(214,106);
    reclaim_slot_value(FIRST(arglist));
    reclaim_frame_serial_number(SECOND(arglist));
    reclaim_slot_value(THIRD(arglist));
    reclaim_frame_serial_number(FOURTH(arglist));
    return reclaim_gensym_list_1(arglist);
}

static Object Kdraw_as_late_as_possible;  /* :draw-as-late-as-possible */

static Object list_constant_15;    /* # */

static Object list_constant_16;    /* # */

/* GET-AND-CLEAR-WORKSPACE-FOR-INSPECT-COMMAND */
Object get_and_clear_workspace_for_inspect_command varargs_1(int, n)
{
    Object inspect_command;
    Object kb_search_state_qm, workspace_qm, current_drawing_priority, temp;
    Object table_or_text_box_qm, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, sub_class_bit_vector;
    Object region_invalidation_is_preferred, svref_new_value;
    Object delete_connections_without_leaving_stubs_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(2);

    x_note_fn_call(214,107);
    INIT_ARGS_nonrelocating();
    inspect_command = REQUIRED_ARG_nonrelocating();
    kb_search_state_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    workspace_qm = get_workspace_if_any(inspect_command);
    if (workspace_qm) {
	current_drawing_priority = Kdraw_as_late_as_possible;
	PUSH_SPECIAL(Current_drawing_priority,current_drawing_priority,1);
	  if (kb_search_state_qm) {
	      temp = ISVREF(inspect_command,(SI_Long)16L);
	      temp = CAR(temp);
	      temp_1 =  !TRUEP(memq_function(SECOND(temp),list_constant_15));
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      table_or_text_box_qm = Nil;
	    next_loop:
	      gensymed_symbol = ISVREF(workspace_qm,(SI_Long)14L);
	      gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		      (SI_Long)4L) : Nil;
	      ab_queue_form_ = gensymed_symbol;
	      ab_next_queue_element_ = Nil;
	      subblock = Nil;
	      if (ab_queue_form_)
		  ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
	    next_loop_1:
	      if (EQ(ab_next_queue_element_,ab_queue_form_))
		  goto end_loop;
	      subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
	      ab_next_queue_element_ = ISVREF(ab_next_queue_element_,
		      (SI_Long)0L);
	      sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		      (SI_Long)19L);
	      superior_class_bit_number = 
		      IFIX(ISVREF(Table_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_1 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_2 = (SI_Long)1L;
		  gensymed_symbol_3 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_2 = gensymed_symbol_2 << gensymed_symbol_3;
		  gensymed_symbol_1 = gensymed_symbol_1 & gensymed_symbol_2;
		  temp_1 = (SI_Long)0L < gensymed_symbol_1;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	      if (temp_1);
	      else {
		  sub_class_bit_vector = ISVREF(ISVREF(subblock,
			  (SI_Long)1L),(SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Text_box_class_description,
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
		      gensymed_symbol_2 = gensymed_symbol_2 << 
			      gensymed_symbol_3;
		      gensymed_symbol_1 = gensymed_symbol_1 & 
			      gensymed_symbol_2;
		      temp_1 = (SI_Long)0L < gensymed_symbol_1;
		  }
		  else
		      temp_1 = TRUEP(Nil);
		  if (temp_1) {
		      sub_class_bit_vector = ISVREF(ISVREF(subblock,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Inspect_command_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
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
			  temp_1 = (SI_Long)0L < gensymed_symbol_1;
		      }
		      else
			  temp_1 = TRUEP(Nil);
		      temp_1 =  !temp_1;
		  }
		  else
		      temp_1 = TRUEP(Nil);
	      }
	      if (temp_1) {
		  table_or_text_box_qm = subblock;
		  goto end_1;
	      }
	      goto next_loop_1;
	    end_loop:
	      table_or_text_box_qm = Qnil;
	    end_1:;
	      if ( !TRUEP(table_or_text_box_qm))
		  goto end_loop_1;
	      region_invalidation_is_preferred = T;
	      PUSH_SPECIAL(Region_invalidation_is_preferred,region_invalidation_is_preferred,
		      0);
		update_images_of_block(table_or_text_box_qm,T,T);
		remove_as_subblock_if_necessary(2,table_or_text_box_qm,
			workspace_qm);
	      POP_SPECIAL();
	      svref_new_value = gensym_cons_1(table_or_text_box_qm,
		      ISVREF(kb_search_state_qm,(SI_Long)45L));
	      ISVREF(kb_search_state_qm,(SI_Long)45L) = svref_new_value;
	      goto next_loop;
	    end_loop_1:
	      delete_connections_without_leaving_stubs_qm = T;
	      PUSH_SPECIAL(Delete_connections_without_leaving_stubs_qm,delete_connections_without_leaving_stubs_qm,
		      0);
		delete_subblocks_not_of_class(workspace_qm,list_constant_16);
	      POP_SPECIAL();
	      shrink_wrap_workspace(workspace_qm);
	  }
	  else {
	      delete_connections_without_leaving_stubs_qm = T;
	      PUSH_SPECIAL(Delete_connections_without_leaving_stubs_qm,delete_connections_without_leaving_stubs_qm,
		      0);
		invalidate_workspace(workspace_qm);
		delete_subblocks_not_of_class(workspace_qm,list_constant_16);
	      POP_SPECIAL();
	  }
	POP_SPECIAL();
	if (T)
	    force_process_drawing();
    }
    return VALUES_1(workspace_qm);
}

static Object Kfirst;              /* :first */

/* NORMALIZE-DESIGNATION */
Object normalize_designation(designation)
    Object designation;
{
    x_note_fn_call(214,108);
    if (SYMBOLP(designation))
	return copy_symbol_name(2,designation,Kfirst);
    else
	return copy_wide_string(designation);
}

static Object Qtitle_bar_caption_text;  /* title-bar-caption-text */

static Object Qworkspace_background_color_qm;  /* workspace-background-color? */

static Object Qsystem_workspace_background_color;  /* system-workspace-background-color */

static Object Qleft;               /* left */

static Object Qtop;                /* top */

/* PUT-INSPECT-WORKSPACE-ON-CURRENT-DETAIL-PANE */
Object put_inspect_workspace_on_current_detail_pane(inspect_workspace)
    Object inspect_workspace;
{
    Object designation, image_plane, ab_loop_list_, main_image_plane;

    x_note_fn_call(214,109);
    if (New_g2_classic_ui_p) {
	designation = get_or_make_up_designation_for_block(inspect_workspace);
	designation = normalize_designation(designation);
	change_slot_value(3,inspect_workspace,Qtitle_bar_caption_text,
		convert_text_string_to_text(designation));
	change_slot_value(3,inspect_workspace,
		Qworkspace_background_color_qm,get_ui_parameter(1,
		Qsystem_workspace_background_color));
    }
    image_plane = Nil;
    ab_loop_list_ = ISVREF(inspect_workspace,(SI_Long)16L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    image_plane = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (EQ(ISVREF(image_plane,(SI_Long)2L),Current_workstation_detail_pane)) {
	main_image_plane = image_plane;
	goto end_1;
    }
    goto next_loop;
  end_loop:
    main_image_plane = Qnil;
  end_1:;
    if (main_image_plane);
    else
	main_image_plane = 
		put_workspace_on_pane_function(inspect_workspace,
		Current_workstation_detail_pane,Qleft,Qtop,Nil,
		FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
    return VALUES_1(main_image_plane);
}

static Object Qtext;               /* text */

/* MARK-OCCURRENCES-OF-STRING-IN-TABLE */
Object mark_occurrences_of_string_in_table varargs_1(int, n)
{
    Object table, string_to_look_for, observance_of_word_boundary_qm;
    Object only_in_text_representations_for_slot_values_qm;
    Object only_editable_occurrences_qm, name_of_slot_to_ignore_qm, row;
    Object ab_loop_list_, ab_loopvar_, cell_qm, ab_loop_list__1, ab_loopvar__1;
    Object frame_qm, slot_name_or_index_qm, defining_class_qm;
    Object type_of_slot_if_editable_qm, sub_class_bit_vector, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;
    Declare_varargs_nonrelocating;
    Object result;

    x_note_fn_call(214,110);
    INIT_ARGS_nonrelocating();
    table = REQUIRED_ARG_nonrelocating();
    string_to_look_for = REQUIRED_ARG_nonrelocating();
    observance_of_word_boundary_qm = REQUIRED_ARG_nonrelocating();
    only_in_text_representations_for_slot_values_qm = 
	    OPTIONAL_ARG_P_nonrelocating() ? OPTIONAL_ARG_nonrelocating() : T;
    only_editable_occurrences_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : T;
    name_of_slot_to_ignore_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
    ab_loopvar_ = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    row = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    cell_qm = Nil;
    ab_loop_list__1 = row;
    ab_loopvar__1 = FIX((SI_Long)0L);
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    cell_qm = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (cell_qm && CONSP(cell_qm)) {
	temp =  !TRUEP(only_in_text_representations_for_slot_values_qm) ?  
		!TRUEP(only_editable_occurrences_qm) : TRUEP(Qnil);
	if (temp);
	else {
	    result = get_slot_represented_by_text_cell_if_any(cell_qm);
	    MVS_3(result,frame_qm,slot_name_or_index_qm,defining_class_qm);
	    if (frame_qm && SYMBOLP(slot_name_or_index_qm)) {
		temp =  !TRUEP(only_editable_occurrences_qm);
		if (temp);
		else {
		    type_of_slot_if_editable_qm = 
			    type_slot_feature_assq_if_editable(ISVREF(get_slot_description_of_class_description_function(slot_name_or_index_qm,
			    ISVREF(frame_qm,(SI_Long)1L),
			    defining_class_qm),(SI_Long)9L));
		    if (type_of_slot_if_editable_qm) {
			temp =  !TRUEP(memq_function(Qtext,
				CDDR(type_of_slot_if_editable_qm)));
			if (temp);
			else
			    temp =  !TRUEP(stripped_text_p(CDDDR(cell_qm)));
			if (temp);
			else {
			    sub_class_bit_vector = ISVREF(ISVREF(frame_qm,
				    (SI_Long)1L),(SI_Long)19L);
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
					superior_class_bit_number & 
					(SI_Long)7L;
				gensymed_symbol_1 = gensymed_symbol_1 << 
					gensymed_symbol_2;
				gensymed_symbol = gensymed_symbol & 
					gensymed_symbol_1;
				temp = (SI_Long)0L < gensymed_symbol;
			    }
			    else
				temp = TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		}
	    }
	    else
		temp = TRUEP(Nil);
	    temp = ((temp ?  !(name_of_slot_to_ignore_qm ? 
		    EQ(slot_name_or_index_qm,name_of_slot_to_ignore_qm) : 
		    TRUEP(Nil)) : TRUEP(Nil)) ? (SI_Long)0L != 
		    (IFIX(ISVREF(frame_qm,(SI_Long)5L)) & 
		    (SI_Long)262144L) || (SI_Long)0L != 
		    (IFIX(ISVREF(frame_qm,(SI_Long)4L)) & (SI_Long)1L) : 
		    TRUEP(Nil)) ? TRUEP(edit_attribute_allowed_p(frame_qm,
		    slot_name_or_index_qm,defining_class_qm)) : TRUEP(Nil);
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = mark_occurrences_of_string_in_text(table,cell_qm,
		string_to_look_for,observance_of_word_boundary_qm);
	ab_loopvar__1 = add(temp_1,ab_loopvar__1);
    }
    goto next_loop_1;
  end_loop_1:
    temp_1 = ab_loopvar__1;
    goto end_1;
    temp_1 = Qnil;
  end_1:;
    ab_loopvar_ = add(temp_1,ab_loopvar_);
    goto next_loop;
  end_loop:
    return VALUES_1(ab_loopvar_);
    return VALUES_1(Qnil);
}

static Object Qediting;            /* editing */

/* REPLACE-EDITABLE-OCCURRENCES-OF-STRING-IN-TABLE */
Object replace_editable_occurrences_of_string_in_table varargs_1(int, n)
{
    Object table, string_to_replace, replacement_string;
    Object observance_of_word_boundary_qm;
    Object name_of_slot_to_ignore_qm, ignore_unmarked_cells_qm;
    Object number_of_substitutions, number_of_resulting_parsing_failures, row;
    Object ab_loop_list_, cell_qm, ab_loop_list__1, text_qm, frame_qm;
    Object slot_name_or_index_qm, defining_class_qm, beginning_line_index_qm;
    Object beginning_character_index_qm, gensymed_symbol, ab_queue_form_;
    Object ab_next_queue_element_, subblock, ab_loop_it_, sub_class_bit_vector;
    Object temp_1, temp_2, temp_3, current_edit_state, current_edit_workspace;
    Object end_line_index_qm, end_character_index_qm, editing_context;
    SI_Long row_index, column_index, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3;
    char temp;
    Declare_varargs_nonrelocating;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,111);
    INIT_ARGS_nonrelocating();
    table = REQUIRED_ARG_nonrelocating();
    string_to_replace = REQUIRED_ARG_nonrelocating();
    replacement_string = REQUIRED_ARG_nonrelocating();
    observance_of_word_boundary_qm = REQUIRED_ARG_nonrelocating();
    name_of_slot_to_ignore_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    ignore_unmarked_cells_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    number_of_substitutions = FIX((SI_Long)0L);
    number_of_resulting_parsing_failures = FIX((SI_Long)0L);
    row_index = (SI_Long)0L;
    row = Nil;
    ab_loop_list_ = ISVREF(table,(SI_Long)19L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    row = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    column_index = (SI_Long)0L;
    cell_qm = Nil;
    ab_loop_list__1 = row;
    text_qm = Nil;
    frame_qm = Nil;
    slot_name_or_index_qm = Nil;
    defining_class_qm = Nil;
    beginning_line_index_qm = Nil;
    beginning_character_index_qm = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    cell_qm = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    text_qm = cell_qm && CONSP(cell_qm) ? CDDDR(cell_qm) : Nil;
    if (text_qm && editable_text_cell_p(table,cell_qm) &&  
	    !(name_of_slot_to_ignore_qm ? EQ(slot_name_or_index_qm,
	    name_of_slot_to_ignore_qm) : TRUEP(Nil))) {
	temp =  !TRUEP(ignore_unmarked_cells_qm);
	if (temp);
	else {
	    gensymed_symbol = ISVREF(table,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)4L) : Nil;
	    ab_queue_form_ = gensymed_symbol;
	    ab_next_queue_element_ = Nil;
	    subblock = Nil;
	    ab_loop_it_ = Nil;
	    if (ab_queue_form_)
		ab_next_queue_element_ = ISVREF(ab_queue_form_,(SI_Long)0L);
	  next_loop_2:
	    if (EQ(ab_next_queue_element_,ab_queue_form_))
		goto end_loop_2;
	    subblock = ISVREF(ab_next_queue_element_,(SI_Long)2L);
	    ab_next_queue_element_ = ISVREF(ab_next_queue_element_,
		    (SI_Long)0L);
	    sub_class_bit_vector = ISVREF(ISVREF(subblock,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Text_region_class_description,(SI_Long)18L));
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
	    ab_loop_it_ = temp ? (IFIX(ISVREF(subblock,(SI_Long)20L)) == 
		    row_index ? (IFIX(ISVREF(subblock,(SI_Long)21L)) == 
		    column_index ? T : Nil) : Qnil) : Nil;
	    if (ab_loop_it_) {
		temp = TRUEP(ab_loop_it_);
		goto end_1;
	    }
	    goto next_loop_2;
	  end_loop_2:
	    temp = TRUEP(Qnil);
	  end_1:;
	}
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	result = get_slot_represented_by_text_cell_if_any(cell_qm);
	MVS_3(result,frame_qm,slot_name_or_index_qm,defining_class_qm);
	temp = TRUEP(frame_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp ? TRUEP(edit_attribute_allowed_p(frame_qm,
	    slot_name_or_index_qm,defining_class_qm)) : TRUEP(Nil)) {
	result = find_string_in_text_for_inspect(3,string_to_replace,
		text_qm,observance_of_word_boundary_qm);
	MVS_2(result,beginning_line_index_qm,beginning_character_index_qm);
	temp = TRUEP(beginning_line_index_qm);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	temp_1 = frame_qm;
	temp_2 = defining_class_qm ? gensym_cons_1(Qclass_qualified_name,
		gensym_cons_1(defining_class_qm,
		gensym_cons_1(slot_name_or_index_qm,Nil))) : 
		slot_name_or_index_qm;
	temp_3 = copy_text(text_qm);
	enter_editing_context(8,temp_1,temp_2,temp_3,T,Nil,Nil,
		beginning_line_index_qm,beginning_character_index_qm);
	current_edit_state = 
		Specific_structure_for_current_workstation_context;
	PUSH_SPECIAL(Current_edit_state,current_edit_state,1);
	  current_edit_workspace = ISVREF(Current_edit_state,(SI_Long)12L);
	  PUSH_SPECIAL(Current_edit_workspace,current_edit_workspace,0);
	    end_line_index_qm = Nil;
	    end_character_index_qm = Nil;
	  next_loop_3:
	    result = find_string_in_text_for_inspect(5,string_to_replace,
		    ISVREF(Current_edit_state,(SI_Long)15L),
		    observance_of_word_boundary_qm,
		    ISVREF(Current_edit_state,(SI_Long)24L),
		    ISVREF(Current_edit_state,(SI_Long)25L));
	    MVS_4(result,beginning_line_index_qm,
		    beginning_character_index_qm,end_line_index_qm,
		    end_character_index_qm);
	    if ( !TRUEP(beginning_line_index_qm))
		goto end_loop_3;
	    change_edit_box(9,Nil,end_line_index_qm,end_character_index_qm,
		    Nil,Nil,Nil,Nil,Nil,T);
	    change_edit_box(6,Nil,beginning_line_index_qm,
		    beginning_character_index_qm,end_line_index_qm,
		    end_character_index_qm,replacement_string);
	    number_of_substitutions = FIXNUM_ADD1(number_of_substitutions);
	    goto next_loop_3;
	  end_loop_3:;
	  POP_SPECIAL();
	POP_SPECIAL();
	editing_context = Current_workstation_context;
	temp_1 = finish_parsing_insofar_as_possible();
	if (Keep_edit_workspace_hidden_no_matter_what_qm && 
		EQ(Current_workstation_context,editing_context))
	    return_from_current_workstation_context(1,Qediting);
	if ( !TRUEP(temp_1))
	    number_of_resulting_parsing_failures = 
		    FIXNUM_ADD1(number_of_resulting_parsing_failures);
    }
    column_index = column_index + (SI_Long)1L;
    goto next_loop_1;
  end_loop_1:;
    row_index = row_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_2(number_of_substitutions,
	    number_of_resulting_parsing_failures);
    return VALUES_1(Qnil);
}

Object Remote_query_id_for_kb_recompile = UNBOUND;

static Object string_constant_38;  /* "{Comment: G2 has launched this Inspect command to compile ~
				    *                  this KB up-to-date.~a~a}"
				    */

static Object string_constant_39;  /* "  " */

static Object string_constant_40;  /* "~a~%~%~a" */

static Object string_constant_41;  /* "recompile every item whose status is incomplete" */

static Object Qrecomile_message;   /* recomile-message */

static Object Qbutton;             /* button */

static Object array_constant_8;    /* # */

static Object Qpause;              /* pause */

static Object array_constant_9;    /* # */

static Object array_constant_10;   /* # */

static Object Qhandle_remote_recompile_dialog_request;  /* handle-remote-recompile-dialog-request */

static Object Qnotify_t2_for_local_recompile;  /* notify-t2-for-local-recompile */

/* LAUNCH-COMPILE-TO-BRING-KB-UP-TO-DATE */
Object launch_compile_to_bring_kb_up_to_date varargs_1(int, n)
{
    Object additional_comment_text_string_qm, temp, comment_text_string;
    Object message_1, temp_1, temp_2, amf_available_array_cons_qm, amf_array;
    Object temp_3, svref_new_value, amf_result, incff_1_arg, new_float;
    Declare_varargs_nonrelocating;

    x_note_fn_call(214,112);
    INIT_ARGS_nonrelocating();
    additional_comment_text_string_qm = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    temp = additional_comment_text_string_qm;
    if (temp);
    else
	temp = string_constant_9;
    comment_text_string = tformat_text_string(3,string_constant_38,
	    additional_comment_text_string_qm ? string_constant_39 : 
	    string_constant_9,temp);
    temp = tformat_text_string(3,string_constant_40,comment_text_string,
	    string_constant_41);
    reclaim_text_string(comment_text_string);
    message_1 = temp;
    if (Ui_client_interface_in_which_to_launch_recompilation_qm) {
	temp_1 = gensym_list_3(Qtext,copy_text_string(message_1),
		Qrecomile_message);
	temp_2 = gensym_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_8,
		FIX((SI_Long)5L)),Qpause);
	temp = gensym_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_9,
		FIX((SI_Long)5L)),Qrerun);
	temp = gensym_list_4(temp_1,temp_2,temp,gensym_list_3(Qbutton,
		copy_constant_wide_string_given_length(array_constant_10,
		FIX((SI_Long)4L)),Qhide));
	enter_dialog_for_t2(5,Qrecompile,temp,
		Qhandle_remote_recompile_dialog_request,
		Ui_client_interface_in_which_to_launch_recompilation_qm,Nil);
	amf_available_array_cons_qm = 
		ISVREF(Vector_of_simple_float_array_pools,(SI_Long)1L);
	if (amf_available_array_cons_qm) {
	    amf_array = M_CAR(amf_available_array_cons_qm);
	    temp_3 = Vector_of_simple_float_array_pools;
	    svref_new_value = M_CDR(amf_available_array_cons_qm);
	    SVREF(temp_3,FIX((SI_Long)1L)) = svref_new_value;
	    inline_note_reclaim_cons(amf_available_array_cons_qm,Qab_gensym);
	    temp_3 = Available_gensym_conses;
	    M_CDR(amf_available_array_cons_qm) = temp_3;
	    Available_gensym_conses = amf_available_array_cons_qm;
	    amf_result = amf_array;
	}
	else {
	    temp_3 = FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
	    Created_simple_float_array_pool_arrays = temp_3;
	    incff_1_arg = 
		    bytes_per_double_float_simple_array(FIX((SI_Long)1L));
	    temp_3 = FIXNUM_ADD(Simple_float_array_pool_memory_usage,
		    incff_1_arg);
	    Simple_float_array_pool_memory_usage = temp_3;
	    amf_result = generate_float_vector(FIX((SI_Long)1L));
	}
	new_float = amf_result;
	DFLOAT_ISASET_1(new_float,(SI_Long)0L,1.0);
	Remote_query_id_for_kb_recompile = 
		start_inspect_session_internal(message_1,
		Qnotify_t2_for_local_recompile,Nil,FIX((SI_Long)1L),new_float);
    }
    else
	handle_inspect_command(4,make_command_frame(2,Qinspect_command,
		message_1),Nil,Nil,T);
    if (additional_comment_text_string_qm)
	reclaim_text_string(additional_comment_text_string_qm);
    return VALUES_1(T);
}

static Object Qadministrator;      /* administrator */

static Object array_constant_11;   /* # */

static Object Qresume;             /* resume */

static Object Qbutton_update;      /* button-update */

/* HANDLE-REMOTE-RECOMPILE-DIALOG-REQUEST */
Object handle_remote_recompile_dialog_request(dialog_sequence_number,
	    client_item)
    Object dialog_sequence_number, client_item;
{
    Object button, id, gensymed_symbol, current_workstation_1;
    Object current_workstation_window, type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object servicing_workstation_qm;
    Declare_special(10);
    Object result;

    x_note_fn_call(214,113);
    button = get_values_for_t2_dialog(dialog_sequence_number);
    id = Remote_query_id_for_kb_recompile;
    if (EQ(button,Qpause)) {
	gensymed_symbol = get_or_make_dummy_workstation();
	current_workstation_1 = gensymed_symbol;
	PUSH_SPECIAL(Current_workstation,current_workstation_1,9);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		  8);
	    type_of_current_workstation_window = Nil;
	    PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		    7);
	      current_workstation_native_window_qm = Nil;
	      PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		      6);
		temp = ISVREF(Current_workstation,(SI_Long)17L);
		current_workstation_context = CAR(temp);
		PUSH_SPECIAL(Current_workstation_context,current_workstation_context,
			5);
		  type_of_current_workstation_context = 
			  ISVREF(Current_workstation_context,(SI_Long)1L);
		  PUSH_SPECIAL(Type_of_current_workstation_context,type_of_current_workstation_context,
			  4);
		    specific_structure_for_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)2L);
		    PUSH_SPECIAL(Specific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			    3);
		      current_workstation_detail_pane = Nil;
		      PUSH_SPECIAL(Current_workstation_detail_pane,current_workstation_detail_pane,
			      2);
			current_g2_user_mode_qm = Qadministrator;
			PUSH_SPECIAL(Current_g2_user_mode_qm,current_g2_user_mode_qm,
				1);
			  servicing_workstation_qm = T;
			  PUSH_SPECIAL(Servicing_workstation_qm,servicing_workstation_qm,
				  0);
			    g2_pause_inspect_session(id);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return update_dialog_for_t2(Qrecompile,gensym_list_3(Qpause,
		copy_constant_wide_string_given_length(array_constant_11,
		FIX((SI_Long)6L)),Qresume),Qbutton_update);
    }
    else if (EQ(button,Qresume)) {
	update_dialog_for_t2(Qrecompile,gensym_list_3(Qresume,
		copy_constant_wide_string_given_length(array_constant_8,
		FIX((SI_Long)5L)),Qpause),Qbutton_update);
	gensymed_symbol = get_or_make_dummy_workstation();
	current_workstation_1 = gensymed_symbol;
	PUSH_SPECIAL(Current_workstation,current_workstation_1,9);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		  8);
	    type_of_current_workstation_window = Nil;
	    PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		    7);
	      current_workstation_native_window_qm = Nil;
	      PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		      6);
		temp = ISVREF(Current_workstation,(SI_Long)17L);
		current_workstation_context = CAR(temp);
		PUSH_SPECIAL(Current_workstation_context,current_workstation_context,
			5);
		  type_of_current_workstation_context = 
			  ISVREF(Current_workstation_context,(SI_Long)1L);
		  PUSH_SPECIAL(Type_of_current_workstation_context,type_of_current_workstation_context,
			  4);
		    specific_structure_for_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)2L);
		    PUSH_SPECIAL(Specific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			    3);
		      current_workstation_detail_pane = Nil;
		      PUSH_SPECIAL(Current_workstation_detail_pane,current_workstation_detail_pane,
			      2);
			current_g2_user_mode_qm = Qadministrator;
			PUSH_SPECIAL(Current_g2_user_mode_qm,current_g2_user_mode_qm,
				1);
			  servicing_workstation_qm = T;
			  PUSH_SPECIAL(Servicing_workstation_qm,servicing_workstation_qm,
				  0);
			    result = g2_resume_inspect_session(id);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else if (EQ(button,Qhide)) {
	leave_dialog_for_t2(dialog_sequence_number);
	remove_dialog_info_from_ui_client_interface_dialog_list(dialog_sequence_number,
		ISVREF(client_item,(SI_Long)26L));
	Ui_client_interface_in_which_to_launch_recompilation_qm = Nil;
	Remote_query_id_for_kb_recompile = Nil;
	return VALUES_1(Remote_query_id_for_kb_recompile);
    }
    else if (EQ(button,Qrerun)) {
	leave_dialog_for_t2(dialog_sequence_number);
	remove_dialog_info_from_ui_client_interface_dialog_list(dialog_sequence_number,
		ISVREF(client_item,(SI_Long)26L));
	Remote_query_id_for_kb_recompile = Nil;
	return launch_recompilation_for_this_kb();
    }
    else
	return VALUES_1(Qnil);
}

static Object Qborderless_free_text_format;  /* borderless-free-text-format */

static Object Qfont_for_descriptions;  /* font-for-descriptions */

/* MAKE-DESCRIPTION-BOX */
Object make_description_box(text_line)
    Object text_line;
{
    x_note_fn_call(214,114);
    return make_free_text_box(3,text_line,Nil,
	    choose_font_format_per_fonts_table(Qborderless_free_text_format,
	    Qfont_for_descriptions));
}

/* MAKE-DESCRIPTION-BOX-WITH-TEXT */
Object make_description_box_with_text(text)
    Object text;
{
    x_note_fn_call(214,115);
    return make_free_text_box_with_text(3,text,Nil,
	    choose_font_format_per_fonts_table(Qborderless_free_text_format,
	    Qfont_for_descriptions));
}

static Object string_constant_42;  /* "Description of ~(~NF~)" */

static Object string_constant_43;  /* "Description of ~(~NF.~)" */

/* DESCRIBE-ITEM-ON-TEMPORARY-WORKSPACE */
Object describe_item_on_temporary_workspace(item)
    Object item;
{
    Object current_computation_frame, gensymed_symbol, gensymed_symbol_1;
    Object display_description, workspace, wide_string_bv16, new_wide_string;
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, aref_arg_2, gensym_list_of_wide_strings, string_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object short_string, temp_2, current_y, display_statement;
    Object result_of_evaluation, block_to_add_to_workspace_qm;
    SI_Long bv16_length, temp, aref_new_value, length_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, incff_1_arg;
    Declare_special(6);
    Object result;

    x_note_fn_call(214,116);
    current_computation_frame = item;
    PUSH_SPECIAL(Current_computation_frame,current_computation_frame,5);
      gensymed_symbol = ISVREF(ISVREF(ISVREF(ISVREF(item,(SI_Long)1L),
	      (SI_Long)11L),(SI_Long)15L),(SI_Long)1L);
      gensymed_symbol_1 = item;
      display_description = nreverse(inline_funcall_1(gensymed_symbol,
	      gensymed_symbol_1));
      workspace = make_workspace(6,Qtemporary_workspace,Nil,Nil,
	      FIX((SI_Long)50L),Nil,Nil);
      if (New_g2_classic_ui_p) {
	  wide_string_bv16 = 
		  allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		  + (SI_Long)3L));
	  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	  temp = bv16_length - (SI_Long)2L;
	  aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		  (SI_Long)65535L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  temp = bv16_length - (SI_Long)1L;
	  aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	  UBYTE_16_ISASET_1(wide_string_bv16,temp,aref_new_value);
	  UBYTE_16_ISASET_1(wide_string_bv16,
		  IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	  new_wide_string = wide_string_bv16;
	  current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	  PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	    current_wide_string = new_wide_string;
	    PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	      fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	      PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		      2);
		length_1 = 
			IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		total_length_of_current_wide_string = 
			FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			- (SI_Long)2L) + 
			((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
			(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			1);
		  current_twriting_output_type = Qwide_string;
		  PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			  0);
		    tformat(2,string_constant_42,item);
		    temp_1 = Current_wide_string;
		    aref_arg_2 = Fill_pointer_for_current_wide_string;
		    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
		    temp = bv16_length - (SI_Long)2L;
		    aref_new_value = IFIX(aref_arg_2) & (SI_Long)65535L;
		    UBYTE_16_ISASET_1(temp_1,temp,aref_new_value);
		    temp = bv16_length - (SI_Long)1L;
		    aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2) >> 
			     -  - (SI_Long)16L;
		    UBYTE_16_ISASET_1(temp_1,temp,aref_new_value);
		    UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2),(SI_Long)0L);
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    gensym_list_of_wide_strings = Current_wide_string_list;
	  POP_SPECIAL();
	  string_1 = Nil;
	  ab_loop_list_ = gensym_list_of_wide_strings;
	  ab_loopvar_ = Nil;
	  ab_loopvar__1 = Nil;
	  ab_loopvar__2 = Nil;
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  string_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  new_cons = Available_gensym_conses;
	  if (new_cons) {
	      Available_gensym_conses = M_CDR(new_cons);
	      gensymed_symbol = new_cons;
	  }
	  else
	      gensymed_symbol = Nil;
	  if ( !TRUEP(gensymed_symbol))
	      gensymed_symbol = replenish_gensym_cons_pool();
	  temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	  M_CAR(gensymed_symbol) = temp_1;
	  M_CDR(gensymed_symbol) = Nil;
	  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	  ab_loopvar__2 = gensymed_symbol;
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  new_cons = Available_gensym_conses;
	  if (new_cons) {
	      Available_gensym_conses = M_CDR(new_cons);
	      gensymed_symbol = new_cons;
	  }
	  else
	      gensymed_symbol = Nil;
	  if ( !TRUEP(gensymed_symbol))
	      gensymed_symbol = replenish_gensym_cons_pool();
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	  if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		  (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		  Use_full_size_of_with_output_wide_string_cutoff)) {
	      short_string = copy_text_string(string_1);
	      reclaim_text_string(string_1);
	      temp_1 = short_string;
	  }
	  else
	      temp_1 = string_1;
	  M_CAR(gensymed_symbol) = temp_1;
	  M_CDR(gensymed_symbol) = Nil;
	  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	  ab_loopvar__2 = gensymed_symbol;
	  if (ab_loopvar__1)
	      M_CDR(ab_loopvar__1) = ab_loopvar__2;
	  else
	      ab_loopvar_ = ab_loopvar__2;
	  ab_loopvar__1 = ab_loopvar__2;
	  goto next_loop;
	end_loop:
	  temp_2 = ab_loopvar_;
	  goto end_1;
	  temp_2 = Qnil;
	end_1:;
	  reclaim_gensym_list_1(gensym_list_of_wide_strings);
	  change_slot_value(3,workspace,Qtitle_bar_caption_text,temp_2);
	  change_slot_value(3,workspace,Qworkspace_background_color_qm,
		  get_ui_parameter(1,Qsystem_workspace_background_color));
      }
      else {
	  temp_2 = tformat_text_string(2,string_constant_43,item);
	  display_description = gensym_cons_1(temp_2,display_description);
      }
      temp_2 = make_class_header_string(item);
      display_description = gensym_cons_1(temp_2,display_description);
      current_y = FIX((SI_Long)0L);
      display_statement = Nil;
      ab_loop_list_ = display_description;
      result_of_evaluation = Nil;
      block_to_add_to_workspace_qm = Nil;
    next_loop_1:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_1;
      display_statement = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      result_of_evaluation = ATOM(display_statement) ? display_statement : Nil;
      if ( !TRUEP(display_statement))
	  block_to_add_to_workspace_qm = Nil;
      else if (text_string_p(display_statement))
	  block_to_add_to_workspace_qm = 
		  make_description_box(result_of_evaluation);
      else if (CONSP(display_statement))
	  block_to_add_to_workspace_qm = 
		  make_description_box_with_text(result_of_evaluation);
      else
	  block_to_add_to_workspace_qm = result_of_evaluation;
      if (block_to_add_to_workspace_qm) {
	  add_to_workspace(4,block_to_add_to_workspace_qm,workspace,
		  FIX((SI_Long)0L),current_y);
	  gensymed_symbol = ISVREF(block_to_add_to_workspace_qm,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)3L) : FIX((SI_Long)0L);
	  gensymed_symbol_2 = IFIX(gensymed_symbol);
	  gensymed_symbol = ISVREF(block_to_add_to_workspace_qm,(SI_Long)14L);
	  gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		  (SI_Long)1L) : FIX((SI_Long)0L);
	  gensymed_symbol_3 = IFIX(gensymed_symbol);
	  gensymed_symbol_2 = gensymed_symbol_2 - gensymed_symbol_3;
	  gensymed_symbol_3 = (SI_Long)10L;
	  incff_1_arg = gensymed_symbol_2 + gensymed_symbol_3;
	  temp = IFIX(current_y) + incff_1_arg;
	  current_y = FIX(temp);
      }
      goto next_loop_1;
    end_loop_1:
      put_workspace_on_pane_function(workspace,
	      Current_workstation_detail_pane,Qleft,Qtop,T,
	      FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
      result = reclaim_gensym_list_1(display_description);
    POP_SPECIAL();
    return result;
}

static Object string_constant_44;  /* "This is assigned to module ~a, which is not editable because ~a." */

static Object string_constant_45;  /* "This is assigned to module ~a." */

static Object string_constant_46;  /* "This is not assigned to any module." */

static Object string_constant_47;  /* "The following items are ~(~a this ~a~)." */

static Object string_constant_48;  /* "This ~(~a is ~a~) the following items." */

static Object string_constant_49;  /* "This ~(~a~) is a member of the following g2-lists: " */

static Object string_constant_50;  /* "This ~(~a~) is a member of the following g2-list: " */

static Object string_constant_51;  /* "This item is proprietary to ~(~a~)." */

static Object string_constant_52;  /* "The following procedures were on the stack when this was created:" */

/* DESCRIBE-FRAME-FOR-BLOCK */
Object describe_frame_for_block(block)
    Object block;
{
    Object frames_to_show, relation_instances, class_of_item, module_qm;
    Object reason_qm, write_symbols_in_lower_case_qm, temp, scope_conses;
    Object ab_node_stack_, ab_current_node_, ab_skip_list_form_;
    Object ab_binary_tree_form_, gensymed_symbol, ab_skip_list_p_;
    Object ab_next_node_, ab_tail_node_, ab_current_alist_, ab_entry_cons_;
    Object relation_instance_form, given_name, relation, related_items;
    Object ab_less_than_branch_qm_, ab_node_stack__1, ab_current_node__1;
    Object ab_skip_list_p__1, ab_next_node__1, ab_tail_node__1;
    Object ab_current_alist__1, ab_entry_cons__1, related_item;
    Object element_structures, element, ab_loop_list_, proprietary_package_qm;
    Object gensymed_symbol_2, gensymed_symbol_4, backtrace_qm, held_vector;
    Object proc, elt_1, validated_elt;
    SI_Long gensymed_symbol_1, temp_2, gensymed_symbol_3, next_index, length_1;
    char temp_1;
    Declare_special(2);

    x_note_fn_call(214,117);
    frames_to_show = Nil;
    relation_instances = ISVREF(block,(SI_Long)12L);
    class_of_item = ISVREF(ISVREF(block,(SI_Long)1L),(SI_Long)1L);
    if (kb_has_modularity_information_p()) {
	module_qm = get_module_block_is_in(block);
	reason_qm = module_qm ? get_reason_module_is_not_editable(1,
		module_qm) : Qnil;
	write_symbols_in_lower_case_qm = Nil;
	PUSH_SPECIAL(Write_symbols_in_lower_case_qm,write_symbols_in_lower_case_qm,
		0);
	  if (reason_qm)
	      temp = tformat_text_string(3,string_constant_44,module_qm,
		      reason_qm);
	  else if (module_qm)
	      temp = tformat_text_string(2,string_constant_45,module_qm);
	  else
	      temp = tformat_text_string(1,string_constant_46);
	  frames_to_show = gensym_cons_1(temp,frames_to_show);
	POP_SPECIAL();
    }
    if (Disassemble_enabled_qm &&  !TRUEP(in_order_p(block))) {
	temp = disassemble_item_if_appropriate(block);
	frames_to_show = nconc2(temp,frames_to_show);
    }
    if (relation_instances) {
	scope_conses = Scope_conses;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_skip_list_form_ = relation_instances;
	ab_binary_tree_form_ = relation_instances;
	gensymed_symbol = CDR(relation_instances);
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
	ab_next_node_ = Nil;
	ab_tail_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	relation_instance_form = Nil;
	PUSH_SPECIAL(Scope_conses,scope_conses,1);
	  given_name = Nil;
	  relation = Nil;
	  related_items = Nil;
	  if (ab_skip_list_p_) {
	      ab_next_node_ = 
		      ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
		      (SI_Long)0L),(SI_Long)0L);
	      ab_tail_node_ = M_CDR(M_CDR(ab_skip_list_form_));
	      if (EQ(ab_next_node_,ab_tail_node_))
		  ab_next_node_ = Nil;
	  }
	  else
	      ab_next_node_ = M_CDR(ab_binary_tree_form_);
	next_loop:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_skip_list_p_) {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
		  ab_next_node_ = ISVREF(ISVREF(ab_current_node_,
			  (SI_Long)0L),(SI_Long)0L);
		  if (EQ(ab_next_node_,ab_tail_node_))
		      ab_next_node_ = Nil;
		  ab_entry_cons_ = scope_cons(ISVREF(ab_current_node_,
			  (SI_Long)2L),ISVREF(ab_current_node_,(SI_Long)3L));
	      }
	      else
		  ab_current_node_ = Nil;
	  }
	  else {
	      if (ab_next_node_) {
		  ab_current_node_ = ab_next_node_;
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
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_1;
	  relation_instance_form = M_CDR(ab_entry_cons_);
	  given_name = ISVREF(relation_instance_form,(SI_Long)0L);
	  relation = ISVREF(relation_instance_form,(SI_Long)1L);
	  related_items = ISVREF(relation_instance_form,(SI_Long)2L);
	  temp = EQ(given_name,ISVREF(relation,(SI_Long)22L)) || 
		  EQ(given_name,ISVREF(relation,(SI_Long)23L)) ? 
		  tformat_text_string(3,string_constant_47,given_name,
		  class_of_item) : tformat_text_string(3,
		  string_constant_48,class_of_item,ISVREF(relation,
		  (SI_Long)22L));
	  frames_to_show = gensym_cons_1(temp,frames_to_show);
	  scope_conses = Scope_conses;
	  ab_node_stack__1 = Nil;
	  ab_current_node__1 = Nil;
	  ab_skip_list_form_ = related_items;
	  ab_binary_tree_form_ = related_items;
	  gensymed_symbol = CDR(related_items);
	  if (CONSP(gensymed_symbol)) {
	      temp = M_CAR(gensymed_symbol);
	      temp_1 = SIMPLE_VECTOR_P(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      temp = M_CDR(gensymed_symbol);
	      ab_skip_list_p__1 = SIMPLE_VECTOR_P(temp) ? T : Nil;
	  }
	  else
	      ab_skip_list_p__1 = Nil;
	  ab_next_node__1 = Nil;
	  ab_tail_node__1 = Nil;
	  ab_current_alist__1 = Nil;
	  ab_entry_cons__1 = Nil;
	  related_item = Nil;
	  PUSH_SPECIAL(Scope_conses,scope_conses,0);
	    if (ab_skip_list_p__1) {
		ab_next_node__1 = 
			ISVREF(ISVREF(M_CAR(M_CDR(ab_skip_list_form_)),
			(SI_Long)0L),(SI_Long)0L);
		ab_tail_node__1 = M_CDR(M_CDR(ab_skip_list_form_));
		if (EQ(ab_next_node__1,ab_tail_node__1))
		    ab_next_node__1 = Nil;
	    }
	    else
		ab_next_node__1 = M_CDR(ab_binary_tree_form_);
	  next_loop_2:
	    if (ab_current_alist__1) {
		ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		ab_current_alist__1 = M_CDR(ab_current_alist__1);
	    }
	    else if (ab_skip_list_p__1) {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_next_node__1 = ISVREF(ISVREF(ab_current_node__1,
			    (SI_Long)0L),(SI_Long)0L);
		    if (EQ(ab_next_node__1,ab_tail_node__1))
			ab_next_node__1 = Nil;
		    ab_entry_cons__1 = 
			    scope_cons(ISVREF(ab_current_node__1,
			    (SI_Long)2L),ISVREF(ab_current_node__1,
			    (SI_Long)3L));
		}
		else
		    ab_current_node__1 = Nil;
	    }
	    else {
		if (ab_next_node__1) {
		    ab_current_node__1 = ab_next_node__1;
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node__1,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack__1 = scope_cons(ab_current_node__1,
			    ab_node_stack__1);
		    ab_current_node__1 = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack__1) {
		    ab_next_node__1 = ab_node_stack__1;
		    ab_current_node__1 = M_CAR(ab_node_stack__1);
		    ab_node_stack__1 = M_CDR(ab_node_stack__1);
		}
		else
		    ab_current_node__1 = Nil;
		if (ab_current_node__1) {
		    ab_next_node__1 = ISVREF(ab_current_node__1,(SI_Long)2L);
		    ab_current_alist__1 = ISVREF(ab_current_node__1,
			    (SI_Long)3L);
		    ab_entry_cons__1 = M_CAR(ab_current_alist__1);
		    ab_current_alist__1 = M_CDR(ab_current_alist__1);
		}
	    }
	    if ( !TRUEP(ab_current_node__1))
		goto end_loop_3;
	    related_item = M_CDR(ab_entry_cons__1);
	    if (related_item) {
		temp = make_short_representation(3,related_item,Nil,Qsmall);
		frames_to_show = gensym_cons_1(temp,frames_to_show);
	    }
	    goto next_loop_2;
	  end_loop_3:;
	  POP_SPECIAL();
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
    }
    element_structures = ISVREF(block,(SI_Long)13L);
    if (element_structures) {
	temp = SECOND(element_structures) ? tformat_text_string(2,
		string_constant_49,class_of_item) : tformat_text_string(2,
		string_constant_50,class_of_item);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
	element = Nil;
	ab_loop_list_ = element_structures;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	element = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = make_short_representation(3,ISVREF(element,(SI_Long)3L),Nil,
		Qsmall);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
	goto next_loop_4;
      end_loop_4:;
    }
    proprietary_package_qm = in_order_p(block);
    if (proprietary_package_qm) {
	temp = tformat_text_string(2,string_constant_51,
		proprietary_package_qm);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
    }
    if (Tracked_items_call_vector_table) {
	gensymed_symbol_1 = IFIX(frame_hash_function(block));
	temp = Tracked_items_call_vector_table;
	temp_2 = gensymed_symbol_1 % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_2));
	gensymed_symbol = CDR(temp);
	gensymed_symbol_2 = block;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_5:
	if ( !TRUEP(gensymed_symbol))
	    goto end_loop_5;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	if (gensymed_symbol_1 < gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	else if (gensymed_symbol_1 > gensymed_symbol_3)
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	else {
	    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_6:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_6;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		backtrace_qm = M_CDR(M_CAR(gensymed_symbol));
		goto end_1;
	    }
	    gensymed_symbol = M_CDR(gensymed_symbol);
	    goto next_loop_6;
	  end_loop_6:
	    backtrace_qm = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop_5;
      end_loop_5:
	backtrace_qm = Qnil;
      end_2:;
    }
    else
	backtrace_qm = Nil;
    if (backtrace_qm && (SI_Long)0L < 
	    IFIX(FIXNUM_SUB1(ISVREF(M_CAR(backtrace_qm),(SI_Long)1L)))) {
	temp = tformat_text_string(1,string_constant_52);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
	gensymed_symbol = backtrace_qm;
	held_vector = Nil;
	next_index = (SI_Long)1L;
	length_1 = (SI_Long)0L;
	proc = Nil;
	held_vector = M_CAR(gensymed_symbol);
	length_1 = IFIX(ISVREF(held_vector,(SI_Long)1L));
      next_loop_7:
	if (next_index >= length_1)
	    goto end_loop_7;
	elt_1 = FIXNUM_LE(ISVREF(held_vector,(SI_Long)1L),
		Maximum_in_place_array_size) ? ISVREF(held_vector,
		next_index + IFIX(Managed_array_index_offset)) : 
		ISVREF(ISVREF(held_vector,(next_index >>  -  - 
		(SI_Long)10L) + (SI_Long)2L),next_index & (SI_Long)1023L);
	validated_elt = elt_1 ? validate_item_or_evaluation_value(elt_1,
		Nil,Nil) : Nil;
	next_index = next_index + (SI_Long)1L;
	proc = validated_elt;
	temp = make_short_representation(3,proc,Nil,Qsmall);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
	goto next_loop_7;
      end_loop_7:;
    }
    return VALUES_1(frames_to_show);
}

static Object array_constant_12;   /* # */

static Object Qright;              /* right */

static Object Qbottom;             /* bottom */

static Object Qoutput;             /* output */

static Object Qinput;              /* input */

static Object string_constant_53;  /* "Bottom" */

static Object string_constant_54;  /* "Top" */

static Object string_constant_55;  /* "Right" */

static Object string_constant_56;  /* "Left" */

static Object string_constant_57;  /* "Input" */

static Object string_constant_58;  /* "Output" */

static Object Qconnection;         /* connection */

/* DESCRIBE-FRAME-FOR-CONNECTION */
Object describe_frame_for_connection(connection)
    Object connection;
{
    Object frames_to_show, connection_structure, gensymed_symbol;
    Object input_end_object, input_end_position, input_end_side;
    Object gensymed_symbol_1, output_end_object, output_end_position;
    Object output_end_side, port_name_for_input_end_qm;
    Object port_name_for_output_end_qm, wide_string_bv16, new_wide_string;
    Object current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object input_end, output_end, input_end_first_p, temp, aref_arg_2_1;
    Object gensym_list_of_wide_strings, string_1, ab_loop_list_, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, new_cons, short_string, temp_1;
    Object temp_2, frame, sub_vector_qm, method_function_qm;
    SI_Long input_end_position_on_side, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long gensymed_symbol_4, input_end_x_position, input_end_y_position;
    SI_Long output_end_position_on_side, output_end_x_position;
    SI_Long output_end_y_position, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1, vertical_distance_between_endpoints;
    SI_Long horizontal_distance_between_endpoints, index_1, ab_loop_bind_;
    Declare_special(5);

    x_note_fn_call(214,118);
    frames_to_show = Nil;
    connection_structure = ISVREF(connection,(SI_Long)21L);
    gensymed_symbol = connection_structure;
    input_end_object = ISVREF(gensymed_symbol,(SI_Long)3L);
    input_end_position = ISVREF(gensymed_symbol,(SI_Long)5L);
    input_end_side = ISVREF(array_constant_12,IFIX(input_end_position) & 
	    (SI_Long)3L);
    input_end_position_on_side = IFIX(input_end_position) >>  -  - (SI_Long)2L;
    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    if (EQ(input_end_side,Qleft))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(input_end_side,Qright)) {
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = input_end_position_on_side;
    input_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
    gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol_1);
    if (EQ(input_end_side,Qtop))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(input_end_side,Qbottom)) {
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol_1);
	gensymed_symbol_1 = ISVREF(input_end_object,(SI_Long)14L);
	gensymed_symbol_1 = gensymed_symbol_1 ? ISVREF(gensymed_symbol_1,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol_1);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = input_end_position_on_side;
    input_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
    output_end_object = ISVREF(gensymed_symbol,(SI_Long)2L);
    output_end_position = ISVREF(gensymed_symbol,(SI_Long)4L);
    output_end_side = ISVREF(array_constant_12,IFIX(output_end_position) & 
	    (SI_Long)3L);
    output_end_position_on_side = IFIX(output_end_position) >>  -  - 
	    (SI_Long)2L;
    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)0L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    if (EQ(output_end_side,Qleft))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(output_end_side,Qright)) {
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)2L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = output_end_position_on_side;
    output_end_x_position = gensymed_symbol_2 + gensymed_symbol_3;
    gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    if (EQ(output_end_side,Qtop))
	gensymed_symbol_3 = (SI_Long)0L;
    else if (EQ(output_end_side,Qbottom)) {
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_3 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(output_end_object,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_4 = IFIX(gensymed_symbol);
	gensymed_symbol_3 = gensymed_symbol_3 - gensymed_symbol_4;
	gensymed_symbol_4 = Dont_include_offset_for_end_position_qm ? 
		(SI_Long)0L : (SI_Long)1L;
	gensymed_symbol_3 = gensymed_symbol_3 + gensymed_symbol_4;
    }
    else
	gensymed_symbol_3 = output_end_position_on_side;
    output_end_y_position = gensymed_symbol_2 + gensymed_symbol_3;
    port_name_for_input_end_qm = 
	    get_port_name_given_block_and_connection(3,input_end_object,
	    connection_structure,Qoutput);
    port_name_for_output_end_qm = 
	    get_port_name_given_block_and_connection(3,output_end_object,
	    connection_structure,Qinput);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
      current_wide_string = new_wide_string;
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      if ((SI_Long)0L != (IFIX(ISVREF(connection_structure,
		      (SI_Long)7L)) & (SI_Long)1L)) {
		  vertical_distance_between_endpoints = 
			  input_end_y_position - output_end_y_position;
		  horizontal_distance_between_endpoints = 
			  input_end_x_position - output_end_x_position;
		  input_end = Nil;
		  output_end = Nil;
		  input_end_first_p = T;
		  if (ABS(vertical_distance_between_endpoints) > 
			  ABS(horizontal_distance_between_endpoints)) {
		      if (vertical_distance_between_endpoints >= (SI_Long)0L) {
			  input_end = string_constant_53;
			  output_end = string_constant_54;
			  input_end_first_p = Nil;
		      }
		      else {
			  input_end = string_constant_54;
			  output_end = string_constant_53;
		      }
		  }
		  else if (horizontal_distance_between_endpoints >= 
			  (SI_Long)0L) {
		      input_end = string_constant_55;
		      output_end = string_constant_56;
		      input_end_first_p = Nil;
		  }
		  else {
		      input_end = string_constant_56;
		      output_end = string_constant_55;
		  }
		  if (input_end_first_p)
		      print_connection_describe_info(Nil,input_end,
			      input_end_object,port_name_for_input_end_qm,
			      input_end_side,
			      FIX(input_end_position_on_side),output_end,
			      output_end_object,
			      port_name_for_output_end_qm,output_end_side,
			      FIX(output_end_position_on_side));
		  else
		      print_connection_describe_info(Nil,output_end,
			      output_end_object,
			      port_name_for_output_end_qm,output_end_side,
			      FIX(output_end_position_on_side),input_end,
			      input_end_object,port_name_for_input_end_qm,
			      input_end_side,FIX(input_end_position_on_side));
	      }
	      else
		  print_connection_describe_info(T,string_constant_57,
			  input_end_object,port_name_for_input_end_qm,
			  input_end_side,FIX(input_end_position_on_side),
			  string_constant_58,output_end_object,
			  port_name_for_output_end_qm,output_end_side,
			  FIX(output_end_position_on_side));
	      temp = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  -  
		      - (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp = short_string;
    }
    else
	temp = string_1;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
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
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    temp_2 = make_description_box_with_text(temp_1);
    frame = connection;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qconnection)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_2;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_1;
  end_loop_1:
    method_function_qm = Qnil;
  end_2:;
    temp_1 = method_function_qm ? inline_funcall_1(method_function_qm,
	    frame) : Nil;
    frames_to_show = gensym_cons_1(temp_2,nconc2(temp_1,frames_to_show));
    return VALUES_1(frames_to_show);
}

static Object string_constant_59;  /* "~A end connected to ~nf " */

static Object string_constant_60;  /* "at ~(~a~) ~d " */

static Object string_constant_61;  /* "at port ~a " */

static Object string_constant_62;  /* "~%" */

/* PRINT-CONNECTION-DESCRIBE-INFO */
Object print_connection_describe_info(directed_qm,end1,end1_block,
	    port_name_for_end1_qm,end1_side,end1_position_on_side,end2,
	    end2_block,port_name_for_end2_qm,end2_side,end2_position_on_side)
    Object directed_qm, end1, end1_block, port_name_for_end1_qm, end1_side;
    Object end1_position_on_side, end2, end2_block, port_name_for_end2_qm;
    Object end2_side, end2_position_on_side;
{
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp, print_info_for_end1_qm, print_info_for_end2_qm;

    x_note_fn_call(214,119);
    sub_class_bit_vector = ISVREF(ISVREF(end1_block,(SI_Long)1L),(SI_Long)19L);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    print_info_for_end1_qm =  !temp;
    sub_class_bit_vector = ISVREF(ISVREF(end2_block,(SI_Long)1L),(SI_Long)19L);
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
	temp = (SI_Long)0L < gensymed_symbol;
    }
    else
	temp = TRUEP(Nil);
    print_info_for_end2_qm =  !temp;
    if (print_info_for_end1_qm) {
	tformat(3,string_constant_59,end1,end1_block);
	tformat(3,string_constant_60,end1_side,end1_position_on_side);
	if (port_name_for_end1_qm)
	    tformat(2,string_constant_61,port_name_for_end1_qm);
	tformat(1,string_constant_62);
    }
    if (print_info_for_end2_qm) {
	tformat(3,string_constant_59,end2,end2_block);
	tformat(3,string_constant_60,end2_side,end2_position_on_side);
	if (port_name_for_end2_qm)
	    return tformat(2,string_constant_61,port_name_for_end2_qm);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qg2_array;           /* g2-array */

/* DESCRIBE-FRAME-FOR-G2-ARRAY */
Object describe_frame_for_g2_array(g2_array)
    Object g2_array;
{
    Object frame, sub_vector_qm, method_function_qm, temp;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,120);
    frame = g2_array;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_array)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    temp = method_function_qm ? inline_funcall_1(method_function_qm,frame) 
	    : Nil;
    return VALUES_1(nconc2(temp,
	    describe_frame_that_is_either_g2_array_or_g2_list(g2_array)));
}

static Object Qg2_list;            /* g2-list */

/* DESCRIBE-FRAME-FOR-G2-LIST */
Object describe_frame_for_g2_list(g2_list)
    Object g2_list;
{
    Object frame, sub_vector_qm, method_function_qm, temp;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,121);
    frame = g2_list;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qg2_list)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    temp = method_function_qm ? inline_funcall_1(method_function_qm,frame) 
	    : Nil;
    return VALUES_1(nconc2(temp,
	    describe_frame_that_is_either_g2_array_or_g2_list(g2_list)));
}

static Object Qquantity;           /* quantity */

static Object Qlist_is_permanent;  /* list-is-permanent */

static Object Qitem_or_datum;      /* item-or-datum */

/* DESCRIBE-FRAME-THAT-IS-EITHER-G2-ARRAY-OR-G2-LIST */
Object describe_frame_that_is_either_g2_array_or_g2_list(item)
    Object item;
{
    Object frames_to_show, class_of_item, gensymed_symbol;
    Object sub_class_bit_vector, element_type;
    Object reclaim_array_managed_float_elements_qm, temp_1, head_qm, tail_qm;
    Object array, element_type_1, items_possible_p, managed_g2_array;
    Object float_or_quantity_p, list_of_elements, element, elt_1, thing;
    Object gensymed_symbol_4, amf_available_array_cons_qm, amf_array, temp_2;
    Object svref_new_value, amf_result, incff_1_arg, new_float;
    Object element_type_spec_contains_datum_qm, ab_loop_list_;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long array_length, managed_step_size, managed_length, max_inner_index;
    SI_Long outer_index, inner_index, ab_loop_bind_, incff_1_arg_1;
    char temp;
    double aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(214,122);
    frames_to_show = Nil;
    class_of_item = ISVREF(ISVREF(item,(SI_Long)1L),(SI_Long)1L);
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
	element_type = ISVREF(item,(SI_Long)21L);
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	if (temp)
	    element_type = ISVREF(item,(SI_Long)21L);
	else
	    element_type = Qnil;
    }
    reclaim_array_managed_float_elements_qm = Nil;
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(G2_array_class_description,
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
    if (temp) {
	if (ISVREF(item,(SI_Long)24L)) {
	    temp_1 = ISVREF(item,(SI_Long)23L);
	    temp = SIMPLE_VECTOR_P(temp_1);
	}
	else
	    temp = TRUEP(Nil);
	if (temp) {
	    sub_class_bit_vector = ISVREF(ISVREF(item,(SI_Long)1L),
		    (SI_Long)19L);
	    superior_class_bit_number = 
		    IFIX(ISVREF(Value_array_class_description,(SI_Long)18L));
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
	    temp =  !temp;
	    if (temp);
	    else
		temp =  !TRUEP(zerop(ISVREF(item,(SI_Long)20L))) ? 
			TRUEP(g2_array_aref(item,FIX((SI_Long)0L))) : 
			TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp);
	else
	    temp = (SI_Long)0L != (IFIX(ISVREF(item,(SI_Long)5L)) & 
		    (SI_Long)1L);
	if (temp) {
	    if (EQ(element_type,Qfloat))
		reclaim_array_managed_float_elements_qm = T;
	    head_qm = Nil;
	    tail_qm = Nil;
	    array = item;
	    element_type_1 = ISVREF(array,(SI_Long)21L);
	    items_possible_p = 
		    g2_list_or_array_element_type_may_contain_item_p(element_type_1);
	    managed_g2_array = ISVREF(array,(SI_Long)23L);
	    array_length = IFIX(ISVREF(array,(SI_Long)20L));
	    managed_step_size = items_possible_p ? (SI_Long)2L : (SI_Long)1L;
	    managed_length = array_length * managed_step_size;
	    float_or_quantity_p = EQ(element_type_1,Qfloat) ? T : Nil;
	    if (float_or_quantity_p);
	    else
		float_or_quantity_p = EQ(element_type_1,Qquantity) ? T : Nil;
	    max_inner_index = float_or_quantity_p ? (SI_Long)100L : 
		    managed_length;
	    outer_index = (SI_Long)0L;
	    if ( !TRUEP(managed_g2_array)) {
		list_of_elements = Nil;
		goto end_1;
	    }
	  next_loop:
	    if ( !(outer_index < managed_length))
		goto end_loop;
	    if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		inner_index = (SI_Long)0L;
		ab_loop_bind_ = max_inner_index;
		element = Nil;
	      next_loop_1:
		if (inner_index >= ab_loop_bind_)
		    goto end_loop_1;
		if (EQ(element_type_1,Qfloat))
		    element = 
			    DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(ISVREF(managed_g2_array,
			    (outer_index >>  -  - (SI_Long)10L) + 
			    (SI_Long)2L),outer_index & (SI_Long)1023L));
		else {
		    elt_1 = FIXNUM_LE(ISVREF(managed_g2_array,(SI_Long)1L),
			    Maximum_in_place_array_size) ? 
			    ISVREF(managed_g2_array,outer_index + 
			    IFIX(Managed_array_index_offset)) : 
			    ISVREF(ISVREF(managed_g2_array,(outer_index >> 
			     -  - (SI_Long)10L) + (SI_Long)2L),outer_index 
			    & (SI_Long)1023L);
		    temp =  !TRUEP(items_possible_p);
		    if (temp);
		    else if (elt_1) {
			if (SIMPLE_VECTOR_P(elt_1) && 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(elt_1)) > 
				(SI_Long)2L) {
			    temp = EQ(ISVREF(elt_1,(SI_Long)1L),
				    Qavailable_frame_vector);
			    if (temp);
			    else {
				thing = ISVREF(elt_1,(SI_Long)1L);
				temp = SIMPLE_VECTOR_P(thing) ? 
					EQ(ISVREF(thing,(SI_Long)0L),
					Qg2_defstruct_structure_name_class_description_g2_struct) 
					: TRUEP(Qnil);
			    }
			}
			else
			    temp = TRUEP(Nil);
			temp =  !temp;
			if (temp);
			else {
			    gensymed_symbol = ISVREF(elt_1,(SI_Long)3L);
			    gensymed_symbol_1 = outer_index + (SI_Long)1L;
			    gensymed_symbol_4 = 
				    FIXNUM_LE(ISVREF(managed_g2_array,
				    (SI_Long)1L),
				    Maximum_in_place_array_size) ? 
				    ISVREF(managed_g2_array,
				    gensymed_symbol_1 + 
				    IFIX(Managed_array_index_offset)) : 
				    ISVREF(ISVREF(managed_g2_array,
				    (gensymed_symbol_1 >>  -  - 
				    (SI_Long)10L) + (SI_Long)2L),
				    gensymed_symbol_1 & (SI_Long)1023L);
			    temp = (FIXNUMP(gensymed_symbol) ? 
				    (FIXNUMP(gensymed_symbol_4) ? 
				    FIXNUM_EQ(gensymed_symbol,
				    gensymed_symbol_4) : TRUEP(Nil)) : 
				    FIXNUMP(gensymed_symbol_4) ? 
				    TRUEP(Nil) : 
				    FIXNUM_EQ(M_CAR(gensymed_symbol),
				    M_CAR(gensymed_symbol_4)) && 
				    FIXNUM_EQ(M_CDR(gensymed_symbol),
				    M_CDR(gensymed_symbol_4))) ? 
				    (SI_Long)0L != (IFIX(ISVREF(elt_1,
				    (SI_Long)5L)) & (SI_Long)1L) || 
				    ISVREF(array,(SI_Long)24L) : TRUEP(Nil);
			}
		    }
		    else
			temp = TRUEP(Nil);
		    element = temp ? elt_1 : Nil;
		}
		if (FLOATP(element) || INLINE_LONG_P(element) != (SI_Long)0L) {
		    amf_available_array_cons_qm = 
			    ISVREF(Vector_of_simple_float_array_pools,
			    (SI_Long)1L);
		    if (amf_available_array_cons_qm) {
			amf_array = M_CAR(amf_available_array_cons_qm);
			temp_2 = Vector_of_simple_float_array_pools;
			svref_new_value = M_CDR(amf_available_array_cons_qm);
			SVREF(temp_2,FIX((SI_Long)1L)) = svref_new_value;
			inline_note_reclaim_cons(amf_available_array_cons_qm,
				Qab_gensym);
			temp_2 = Available_gensym_conses;
			M_CDR(amf_available_array_cons_qm) = temp_2;
			Available_gensym_conses = amf_available_array_cons_qm;
			amf_result = amf_array;
		    }
		    else {
			temp_2 = 
				FIXNUM_ADD1(Created_simple_float_array_pool_arrays);
			Created_simple_float_array_pool_arrays = temp_2;
			incff_1_arg = 
				bytes_per_double_float_simple_array(FIX((SI_Long)1L));
			temp_2 = 
				FIXNUM_ADD(Simple_float_array_pool_memory_usage,
				incff_1_arg);
			Simple_float_array_pool_memory_usage = temp_2;
			amf_result = generate_float_vector(FIX((SI_Long)1L));
		    }
		    new_float = amf_result;
		    aref_new_value = DOUBLE_FLOAT_TO_DOUBLE(element);
		    DFLOAT_ISASET_1(new_float,(SI_Long)0L,aref_new_value);
		    gensymed_symbol = new_float;
		}
		else
		    gensymed_symbol = element;
		gensymed_symbol = gensym_cons_1(gensymed_symbol,Nil);
		if (head_qm) {
		    if ( !TRUEP(tail_qm))
			tail_qm = last(head_qm,_);
		    M_CDR(tail_qm) = gensymed_symbol;
		}
		else
		    head_qm = gensymed_symbol;
		tail_qm = gensymed_symbol;
		incff_1_arg_1 = managed_step_size;
		outer_index = outer_index + incff_1_arg_1;
		if ( !(outer_index < managed_length))
		    goto end_loop_1;
		inner_index = inner_index + (SI_Long)1L;
		goto next_loop_1;
	      end_loop_1:;
	    }
	    POP_LOCAL_ALLOCATION(0,0);
	    goto next_loop;
	  end_loop:
	    list_of_elements = head_qm;
	    goto end_1;
	    list_of_elements = Qnil;
	  end_1:;
	}
	else
	    list_of_elements = Nil;
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(G2_list_class_description,
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
	if (temp)
	    list_of_elements = get_lookup_slot_value(item,
		    Qlist_is_permanent) || (SI_Long)0L != 
		    (IFIX(ISVREF(item,(SI_Long)5L)) & (SI_Long)1L) ? 
		    (ISVREF(item,(SI_Long)20L) ? g2_list_elements(1,item) :
		     Nil) : Nil;
	else
	    list_of_elements = Qnil;
    }
    element_type_spec_contains_datum_qm = 
	    type_specification_for_user_or_datum_type(element_type);
    if (list_of_elements) {
	if (element_type_spec_contains_datum_qm &&  
		!EQ(element_type_spec_contains_datum_qm,Qitem_or_datum))
	    frames_to_show = 
		    describe_g2_array_or_list_datum_elements(list_of_elements,
		    element_type,class_of_item);
	else {
	    temp_1 =  !TRUEP(element_type_spec_contains_datum_qm) ? T : Nil;
	    if (temp_1);
	    else
		temp_1 =  !EQ(element_type_spec_contains_datum_qm,
			Qitem_or_datum) ? T : Nil;
	    frames_to_show = 
		    describe_g2_array_or_list_item_or_datum_elements(list_of_elements,
		    element_type,class_of_item,temp_1);
	}
	if (reclaim_array_managed_float_elements_qm) {
	    element = Nil;
	    ab_loop_list_ = list_of_elements;
	  next_loop_2:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_2;
	    element = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (INLINE_DOUBLE_FLOAT_VECTOR_P(element) != (SI_Long)0L && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) == (SI_Long)1L)
		reclaim_managed_simple_float_array_of_length_1(element);
	    goto next_loop_2;
	  end_loop_2:;
	}
	reclaim_gensym_list_1(list_of_elements);
    }
    return VALUES_1(frames_to_show);
}

static Object string_constant_63;  /* "The following are the elements of this ~(~a~):" */

static Object string_constant_64;  /* "no item" */

static Object string_constant_65;  /* "no item or value" */

static Object array_constant_13;   /* # */

static Object Qtruth_value;        /* truth-value */

static Object string_constant_66;  /* "~NC" */

static Object Qiteration_state;    /* iteration-state */

static Object string_constant_67;  /* "~NV" */

static Object Qg2_defstruct_structure_name_temporary_constant_g2_struct;  /* g2-defstruct-structure-name::temporary-constant-g2-struct */

static Object string_constant_68;  /* "~NF" */

static Object array_constant_14;   /* # */

/* DESCRIBE-G2-ARRAY-OR-LIST-ITEM-OR-DATUM-ELEMENTS */
Object describe_g2_array_or_list_item_or_datum_elements(list_of_elements,
	    element_type,class_of_item,items_only_qm)
    Object list_of_elements, element_type, class_of_item, items_only_qm;
{
    Object frames_to_show, element, ab_loop_list_, temp, x2, wide_string_bv16;
    Object new_wide_string, current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_4;
    Object managed_number_or_value, temp_2, aref_arg_2_1;
    Object gensym_list_of_wide_strings, string_1, ab_loop_list__1, ab_loopvar_;
    Object ab_loopvar__1, ab_loopvar__2, new_cons, short_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;
    Declare_special(5);

    x_note_fn_call(214,123);
    frames_to_show = 
	    gensym_cons_1(make_description_box(tformat_text_string(2,
	    string_constant_63,class_of_item)),Nil);
    element = Nil;
    ab_loop_list_ = list_of_elements;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    element = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(element))
	temp = make_description_box(copy_text_string(items_only_qm ? 
		string_constant_64 : string_constant_65));
    else {
	temp_1 = TRUEP(items_only_qm);
	if (temp_1);
	else if (SIMPLE_VECTOR_P(element) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > (SI_Long)2L &&  
		!EQ(ISVREF(element,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(element,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    temp = make_short_representation(3,element,Nil,Qsmall);
	else {
	    wide_string_bv16 = 
		    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		    (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,
		    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	    new_wide_string = wide_string_bv16;
	    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	      current_wide_string = new_wide_string;
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      if ( !TRUEP(element))
			  twrite_beginning_of_wide_string(array_constant_13,
				  FIX((SI_Long)8L));
		      else if (EQ(element_type,Qtruth_value) && 
			      FIXNUMP(element))
			  tformat(3,string_constant_66,element,Qtruth_value);
		      else {
			  gensymed_symbol = element;
			  temp_1 = FIXNUMP(gensymed_symbol);
			  if (temp_1);
			  else
			      temp_1 = 
				      INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
				      != (SI_Long)0L ? 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				      == (SI_Long)1L : TRUEP(Qnil);
			  if (temp_1);
			  else
			      temp_1 = 
				      INLINE_LONG_VECTOR_P(gensymed_symbol) 
				      != (SI_Long)0L ? 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
				      == (SI_Long)1L : TRUEP(Qnil);
			  if (temp_1);
			  else
			      temp_1 = gensymed_symbol ? 
				      SYMBOLP(gensymed_symbol) : TRUEP(Qnil);
			  if (temp_1);
			  else
			      temp_1 = 
				      INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
				      != (SI_Long)0L;
			  if (temp_1);
			  else if (CONSP(gensymed_symbol)) {
			      gensymed_symbol = M_CDR(gensymed_symbol);
			      temp_1 = EQ(gensymed_symbol,Qtruth_value);
			      if (temp_1);
			      else
				  temp_1 = EQ(gensymed_symbol,
					  Qiteration_state);
			      if (temp_1);
			      else if (SYMBOLP(gensymed_symbol)) {
				  gensymed_symbol_1 = 
					  CDR(Defined_evaluation_value_types);
				  gensymed_symbol_2 = 
					  SXHASH_SYMBOL_1(gensymed_symbol) 
					  & IFIX(Most_positive_fixnum);
				  gensymed_symbol_3 = (SI_Long)0L;
				next_loop_1:
				  if ( !TRUEP(gensymed_symbol_1))
				      goto end_loop_1;
				  gensymed_symbol_3 = 
					  IFIX(ISVREF(gensymed_symbol_1,
					  (SI_Long)0L));
				  if (gensymed_symbol_2 < gensymed_symbol_3)
				      gensymed_symbol_1 = 
					      ISVREF(gensymed_symbol_1,
					      (SI_Long)1L);
				  else if (gensymed_symbol_2 > 
					  gensymed_symbol_3)
				      gensymed_symbol_1 = 
					      ISVREF(gensymed_symbol_1,
					      (SI_Long)2L);
				  else {
				      gensymed_symbol_1 = 
					      ISVREF(gensymed_symbol_1,
					      (SI_Long)3L);
				      gensymed_symbol_4 = Nil;
				    next_loop_2:
				      if ( !TRUEP(gensymed_symbol_1))
					  goto end_loop_2;
				      gensymed_symbol_4 = 
					      M_CAR(M_CAR(gensymed_symbol_1));
				      if (EQ(gensymed_symbol,
					      gensymed_symbol_4)) {
					  temp_1 = 
						  TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
					  goto end_1;
				      }
				      gensymed_symbol_1 = 
					      M_CDR(gensymed_symbol_1);
				      goto next_loop_2;
				    end_loop_2:
				      temp_1 = TRUEP(Qnil);
				    end_1:;
				      goto end_2;
				  }
				  goto next_loop_1;
				end_loop_1:
				  temp_1 = TRUEP(Qnil);
				end_2:;
			      }
			      else
				  temp_1 = TRUEP(Nil);
			  }
			  else
			      temp_1 = TRUEP(Nil);
			  if (temp_1)
			      tformat(2,string_constant_67,element);
			  else if (SIMPLE_VECTOR_P(element) && 
				  EQ(ISVREF(element,(SI_Long)0L),
				  Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
				      {
			      managed_number_or_value = ISVREF(element,
				      (SI_Long)1L);
			      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				      == (SI_Long)1L)
				  temp = 
					  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
					  (SI_Long)0L));
			      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
				      != (SI_Long)0L && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
				      == (SI_Long)1L)
				  temp = aref1(managed_number_or_value,
					  FIX((SI_Long)0L));
			      else
				  temp = managed_number_or_value;
			      tformat(3,string_constant_66,temp,
				      ISVREF(element,(SI_Long)2L));
			  }
			  else {
			      if (SIMPLE_VECTOR_P(element) && 
				      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) 
				      > (SI_Long)2L &&  !EQ(ISVREF(element,
				      (SI_Long)1L),Qavailable_frame_vector)) {
				  x2 = ISVREF(element,(SI_Long)1L);
				  temp_1 = SIMPLE_VECTOR_P(x2) && 
					  EQ(ISVREF(x2,(SI_Long)0L),
					  Qg2_defstruct_structure_name_class_description_g2_struct) 
					  ? TRUEP(x2) : TRUEP(Qnil);
			      }
			      else
				  temp_1 = TRUEP(Nil);
			      if (temp_1)
				  tformat(2,string_constant_68,element);
			      else
				  twrite_beginning_of_wide_string(array_constant_14,
					  FIX((SI_Long)13L));
			  }
		      }
		      temp_2 = Current_wide_string;
		      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_2));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(temp_2,aref_arg_2,aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | 
			      IFIX(aref_arg_2_1) >>  -  - (SI_Long)16L;
		      UBYTE_16_ISASET_1(temp_2,aref_arg_2,aref_new_value);
		      UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),(SI_Long)0L);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      gensym_list_of_wide_strings = Current_wide_string_list;
	    POP_SPECIAL();
	    string_1 = Nil;
	    ab_loop_list__1 = gensym_list_of_wide_strings;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_3;
	    string_1 = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    temp_2 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	    M_CAR(gensymed_symbol_1) = temp_2;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_1;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_1 = new_cons;
	    }
	    else
		gensymed_symbol_1 = Nil;
	    if ( !TRUEP(gensymed_symbol_1))
		gensymed_symbol_1 = replenish_gensym_cons_pool();
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		    Use_full_size_of_with_output_wide_string_cutoff)) {
		short_string = copy_text_string(string_1);
		reclaim_text_string(string_1);
		temp_2 = short_string;
	    }
	    else
		temp_2 = string_1;
	    M_CAR(gensymed_symbol_1) = temp_2;
	    M_CDR(gensymed_symbol_1) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_1;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_3;
	  end_loop_3:
	    temp = ab_loopvar_;
	    goto end_3;
	    temp = Qnil;
	  end_3:;
	    reclaim_gensym_list_1(gensym_list_of_wide_strings);
	    temp = make_description_box_with_text(temp);
	}
    }
    frames_to_show = gensym_cons_1(temp,frames_to_show);
    goto next_loop;
  end_loop:;
    return VALUES_1(frames_to_show);
}

Object Maximum_number_of_array_or_list_elements_to_describe = UNBOUND;

static Object string_constant_69;  /* "The following ~a of this ~(~a~):~%" */

static Object string_constant_70;  /* "values are members" */

static Object string_constant_71;  /* "value is a member" */

static Object array_constant_15;   /* # */

static Object string_constant_72;  /* "[~d] " */

static Object array_constant_16;   /* # */

static Object string_constant_73;  /* "~%This operation describes at most ~a elements.  ~
				    *                       There ~a ~a remaining element~a."
				    */

static Object string_constant_74;  /* "is" */

static Object string_constant_75;  /* "are" */

/* DESCRIBE-G2-ARRAY-OR-LIST-DATUM-ELEMENTS */
Object describe_g2_array_or_list_datum_elements(list_of_elements,
	    element_type,class_of_item)
    Object list_of_elements, element_type, class_of_item;
{
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object element, ab_loop_list_, ab_loop_iter_flag_, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_4, managed_number_or_value;
    Object temp_1, x2, temp_2, aref_arg_2_1, gensym_list_of_wide_strings;
    Object string_1, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object short_string;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long gensymed_symbol_2, gensymed_symbol_3;
    SI_Long number_of_elements_not_printed;
    char temp;
    Declare_special(5);

    x_note_fn_call(214,124);
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
      current_wide_string = new_wide_string;
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      tformat(3,string_constant_69,CDR(list_of_elements) ? 
		      string_constant_70 : string_constant_71,class_of_item);
	      element = Nil;
	      ab_loop_list_ = list_of_elements;
	      index_1 = (SI_Long)0L;
	      ab_loop_iter_flag_ = T;
	    next_loop:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop;
	      element = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      if ( !TRUEP(ab_loop_iter_flag_))
		  index_1 = index_1 + (SI_Long)1L;
	      if ( !(index_1 < 
		      IFIX(Maximum_number_of_array_or_list_elements_to_describe)))
		  goto end_loop;
	      if ( !(index_1 == (SI_Long)0L))
		  twrite_beginning_of_wide_string(array_constant_15,
			  FIX((SI_Long)2L));
	      tformat(2,string_constant_72,FIX(index_1));
	      if ( !TRUEP(element))
		  twrite_beginning_of_wide_string(array_constant_13,
			  FIX((SI_Long)8L));
	      else if (EQ(element_type,Qtruth_value) && FIXNUMP(element))
		  tformat(3,string_constant_66,element,Qtruth_value);
	      else {
		  gensymed_symbol = element;
		  temp = FIXNUMP(gensymed_symbol);
		  if (temp);
		  else
		      temp = INLINE_DOUBLE_FLOAT_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L ? 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			      == (SI_Long)1L : TRUEP(Qnil);
		  if (temp);
		  else
		      temp = INLINE_LONG_VECTOR_P(gensymed_symbol) != 
			      (SI_Long)0L ? 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(gensymed_symbol)) 
			      == (SI_Long)1L : TRUEP(Qnil);
		  if (temp);
		  else
		      temp = gensymed_symbol ? SYMBOLP(gensymed_symbol) : 
			      TRUEP(Qnil);
		  if (temp);
		  else
		      temp = 
			      INLINE_UNSIGNED_BYTE_16_VECTOR_P(gensymed_symbol) 
			      != (SI_Long)0L;
		  if (temp);
		  else if (CONSP(gensymed_symbol)) {
		      gensymed_symbol = M_CDR(gensymed_symbol);
		      temp = EQ(gensymed_symbol,Qtruth_value);
		      if (temp);
		      else
			  temp = EQ(gensymed_symbol,Qiteration_state);
		      if (temp);
		      else if (SYMBOLP(gensymed_symbol)) {
			  gensymed_symbol_1 = 
				  CDR(Defined_evaluation_value_types);
			  gensymed_symbol_2 = 
				  SXHASH_SYMBOL_1(gensymed_symbol) & 
				  IFIX(Most_positive_fixnum);
			  gensymed_symbol_3 = (SI_Long)0L;
			next_loop_1:
			  if ( !TRUEP(gensymed_symbol_1))
			      goto end_loop_1;
			  gensymed_symbol_3 = 
				  IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
			  if (gensymed_symbol_2 < gensymed_symbol_3)
			      gensymed_symbol_1 = ISVREF(gensymed_symbol_1,
				      (SI_Long)1L);
			  else if (gensymed_symbol_2 > gensymed_symbol_3)
			      gensymed_symbol_1 = ISVREF(gensymed_symbol_1,
				      (SI_Long)2L);
			  else {
			      gensymed_symbol_1 = ISVREF(gensymed_symbol_1,
				      (SI_Long)3L);
			      gensymed_symbol_4 = Nil;
			    next_loop_2:
			      if ( !TRUEP(gensymed_symbol_1))
				  goto end_loop_2;
			      gensymed_symbol_4 = 
				      M_CAR(M_CAR(gensymed_symbol_1));
			      if (EQ(gensymed_symbol,gensymed_symbol_4)) {
				  temp = 
					  TRUEP(M_CDR(M_CAR(gensymed_symbol_1)));
				  goto end_1;
			      }
			      gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
			      goto next_loop_2;
			    end_loop_2:
			      temp = TRUEP(Qnil);
			    end_1:;
			      goto end_2;
			  }
			  goto next_loop_1;
			end_loop_1:
			  temp = TRUEP(Qnil);
			end_2:;
		      }
		      else
			  temp = TRUEP(Nil);
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp)
		      tformat(2,string_constant_67,element);
		  else if (SIMPLE_VECTOR_P(element) && EQ(ISVREF(element,
			  (SI_Long)0L),
			  Qg2_defstruct_structure_name_temporary_constant_g2_struct)) 
			      {
		      managed_number_or_value = ISVREF(element,(SI_Long)1L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			      == (SI_Long)1L)
			  temp_1 = aref1(managed_number_or_value,
				  FIX((SI_Long)0L));
		      else
			  temp_1 = managed_number_or_value;
		      tformat(3,string_constant_66,temp_1,ISVREF(element,
			      (SI_Long)2L));
		  }
		  else {
		      if (SIMPLE_VECTOR_P(element) && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(element)) > 
			      (SI_Long)2L &&  !EQ(ISVREF(element,
			      (SI_Long)1L),Qavailable_frame_vector)) {
			  x2 = ISVREF(element,(SI_Long)1L);
			  temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,
				  (SI_Long)0L),
				  Qg2_defstruct_structure_name_class_description_g2_struct) 
				  ? TRUEP(x2) : TRUEP(Qnil);
		      }
		      else
			  temp = TRUEP(Nil);
		      if (temp)
			  tformat(2,string_constant_68,element);
		      else
			  twrite_beginning_of_wide_string(array_constant_14,
				  FIX((SI_Long)13L));
		  }
	      }
	      ab_loop_iter_flag_ = Nil;
	      goto next_loop;
	    end_loop:
	      twrite_beginning_of_wide_string(array_constant_16,
		      FIX((SI_Long)1L));
	      if ( !(index_1 < 
		      IFIX(Maximum_number_of_array_or_list_elements_to_describe))) 
			  {
		  number_of_elements_not_printed = 
			  IFIX(length(list_of_elements)) - index_1;
		  tformat(5,string_constant_73,
			  Maximum_number_of_array_or_list_elements_to_describe,
			  number_of_elements_not_printed == (SI_Long)1L ? 
			  string_constant_74 : string_constant_75,
			  FIX(number_of_elements_not_printed),
			  number_of_elements_not_printed == (SI_Long)1L ? 
			  string_constant_9 : string_constant_8);
	      }
	      temp_2 = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_2));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp_2,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  -  
		      - (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp_2,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp_2,IFIX(aref_arg_2_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop_3:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_3;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_gensym_cons_pool();
    temp_2 = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol_1) = temp_2;
    M_CDR(gensymed_symbol_1) = Nil;
    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol_1;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol_1 = new_cons;
    }
    else
	gensymed_symbol_1 = Nil;
    if ( !TRUEP(gensymed_symbol_1))
	gensymed_symbol_1 = replenish_gensym_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp_2 = short_string;
    }
    else
	temp_2 = string_1;
    M_CAR(gensymed_symbol_1) = temp_2;
    M_CDR(gensymed_symbol_1) = Nil;
    inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol_1;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    goto next_loop_3;
  end_loop_3:
    temp_1 = ab_loopvar_;
    goto end_3;
    temp_1 = Qnil;
  end_3:;
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    return gensym_cons_1(make_description_box_with_text(temp_1),Nil);
}

static Object Qsimulation_info_qm;  /* simulation-info? */

static Object Qparameter;          /* parameter */

static Object string_constant_76;  /* "This ~(~a~) is simulated using the simulation formula ~
				    *                             in its simulation subtable."
				    */

static Object string_constant_77;  /* "This ~(~a~) is simulated using the following ~a." */

static Object string_constant_78;  /* "generic simulation formula" */

static Object string_constant_79;  /* "external simulation definition" */

static Object string_constant_80;  /* "The simulation category is ~(~a~)." */

static Object Qnon_default_initial_simulated_value_qm;  /* non-default-initial-simulated-value? */

static Object string_constant_81;  /* "  The initial value is ~(~a~)." */

static Object string_constant_82;  /* "  The non-default time increment is ~(~a~) ~(~a~)." */

static Object Qseconds;            /* seconds */

static Object string_constant_83;  /* "This ~(~a~) belongs to the following model definition." */

static Object Qvariable_or_parameter;  /* variable-or-parameter */

/* DESCRIBE-FRAME-FOR-VARIABLE-OR-PARAMETER */
Object describe_frame_for_variable_or_parameter(variable_or_parameter)
    Object variable_or_parameter;
{
    Object frames_to_show, initial_value_qm, simulation_info_qm;
    Object sub_class_bit_vector, class_to_print, simulation_specifier_to_use;
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, aref_arg_2_1, gensym_list_of_wide_strings, string_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object gensymed_symbol_3, short_string, temp_2, slot_value_number;
    Object specific_time_increment_qm, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1, index_1, ab_loop_bind_;
    char temp;
    Declare_special(5);
    XDeclare_area(1);
    XDeclare_frontier(1);

    x_note_fn_call(214,125);
    frames_to_show = Nil;
    initial_value_qm = Nil;
    simulation_info_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qsimulation_info_qm,Nil);
    if (simulation_info_qm) {
	sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Variable_class_description,
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
	class_to_print = temp ? Qvariable : Qparameter;
	simulation_specifier_to_use = 
		get_simulation_specifier_to_use(variable_or_parameter);
	sub_class_bit_vector = ISVREF(ISVREF(simulation_specifier_to_use,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Simulation_subtable_class_description,
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
	if (temp) {
	    wide_string_bv16 = 
		    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		    (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,
		    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	    new_wide_string = wide_string_bv16;
	    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	      current_wide_string = new_wide_string;
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_76,class_to_print);
		      temp_1 = Current_wide_string;
		      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | 
			      IFIX(aref_arg_2_1) >>  -  - (SI_Long)16L;
		      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		      UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),(SI_Long)0L);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      gensym_list_of_wide_strings = Current_wide_string_list;
	    POP_SPECIAL();
	    string_1 = Nil;
	    ab_loop_list_ = gensym_list_of_wide_strings;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    string_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_gensym_cons_pool();
	    temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	    M_CAR(gensymed_symbol_3) = temp_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_3;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_gensym_cons_pool();
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		    Use_full_size_of_with_output_wide_string_cutoff)) {
		short_string = copy_text_string(string_1);
		reclaim_text_string(string_1);
		temp_1 = short_string;
	    }
	    else
		temp_1 = string_1;
	    M_CAR(gensymed_symbol_3) = temp_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_3;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop;
	  end_loop:
	    temp_2 = ab_loopvar_;
	    goto end_1;
	    temp_2 = Qnil;
	  end_1:;
	    reclaim_gensym_list_1(gensym_list_of_wide_strings);
	    temp_2 = make_description_box_with_text(temp_2);
	    frames_to_show = gensym_cons_1(temp_2,frames_to_show);
	}
	else {
	    wide_string_bv16 = 
		    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		    (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,
		    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	    new_wide_string = wide_string_bv16;
	    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	      current_wide_string = new_wide_string;
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      sub_class_bit_vector = 
			      ISVREF(ISVREF(simulation_specifier_to_use,
			      (SI_Long)1L),(SI_Long)19L);
		      superior_class_bit_number = 
			      IFIX(ISVREF(Generic_simulation_formula_class_description,
			      (SI_Long)18L));
		      sub_class_vector_index = superior_class_bit_number 
			      >>  -  - (SI_Long)3L;
		      if (sub_class_vector_index < 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				  {
			  gensymed_symbol = 
				  UBYTE_8_ISAREF_1(sub_class_bit_vector,
				  sub_class_vector_index);
			  gensymed_symbol_1 = (SI_Long)1L;
			  gensymed_symbol_2 = superior_class_bit_number & 
				  (SI_Long)7L;
			  gensymed_symbol_1 = gensymed_symbol_1 << 
				  gensymed_symbol_2;
			  gensymed_symbol = gensymed_symbol & 
				  gensymed_symbol_1;
			  temp = (SI_Long)0L < gensymed_symbol;
		      }
		      else
			  temp = TRUEP(Nil);
		      tformat(3,string_constant_77,class_to_print,temp ? 
			      string_constant_78 : string_constant_79);
		      temp_1 = Current_wide_string;
		      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | 
			      IFIX(aref_arg_2_1) >>  -  - (SI_Long)16L;
		      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		      UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),(SI_Long)0L);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      gensym_list_of_wide_strings = Current_wide_string_list;
	    POP_SPECIAL();
	    string_1 = Nil;
	    ab_loop_list_ = gensym_list_of_wide_strings;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    string_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_gensym_cons_pool();
	    temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	    M_CAR(gensymed_symbol_3) = temp_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_3;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_gensym_cons_pool();
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		    Use_full_size_of_with_output_wide_string_cutoff)) {
		short_string = copy_text_string(string_1);
		reclaim_text_string(string_1);
		temp_1 = short_string;
	    }
	    else
		temp_1 = string_1;
	    M_CAR(gensymed_symbol_3) = temp_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_3;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    temp_2 = ab_loopvar_;
	    goto end_2;
	    temp_2 = Qnil;
	  end_2:;
	    reclaim_gensym_list_1(gensym_list_of_wide_strings);
	    temp_2 = make_description_box_with_text(temp_2);
	    frames_to_show = gensym_cons_1(temp_2,frames_to_show);
	    temp_2 = make_short_representation(3,
		    simulation_specifier_to_use,Nil,Qsmall);
	    frames_to_show = gensym_cons_1(temp_2,frames_to_show);
	}
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		(SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,
		IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	  current_wide_string = new_wide_string;
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(2,string_constant_80,ISVREF(simulation_info_qm,
			  (SI_Long)2L));
		  sub_class_bit_vector = 
			  ISVREF(ISVREF(variable_or_parameter,(SI_Long)1L),
			  (SI_Long)19L);
		  superior_class_bit_number = 
			  IFIX(ISVREF(Variable_class_description,
			  (SI_Long)18L));
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
		      gensymed_symbol_1 = gensymed_symbol_1 << 
			      gensymed_symbol_2;
		      gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
		      temp = (SI_Long)0L < gensymed_symbol;
		  }
		  else
		      temp = TRUEP(Nil);
		  if (temp ? 
			  TRUEP(get_lookup_slot_value_given_default(variable_or_parameter,
			  Qnon_default_initial_simulated_value_qm,Nil)) : 
			  TRUEP(Nil))
		      initial_value_qm = 
			      get_lookup_slot_value_given_default(variable_or_parameter,
			      Qnon_default_initial_simulated_value_qm,Nil);
		  else
		      initial_value_qm = ISVREF(simulation_info_qm,
			      (SI_Long)3L);
		  if (initial_value_qm) {
		      if (PUSH_LOCAL_ALLOCATION(Local_area,0,0))
			  tformat(2,string_constant_81,
				  INLINE_DOUBLE_FLOAT_VECTOR_P(initial_value_qm) 
				  != (SI_Long)0L && 
				  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(initial_value_qm)) 
				  == (SI_Long)1L ? 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(initial_value_qm,
				  (SI_Long)0L)) : initial_value_qm);
		      POP_LOCAL_ALLOCATION(0,0);
		  }
		  if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
		      slot_value_number = ISVREF(simulation_info_qm,
			      (SI_Long)4L);
		      if (INLINE_DOUBLE_FLOAT_VECTOR_P(slot_value_number) 
			      != (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			      == (SI_Long)1L)
			  specific_time_increment_qm = 
				  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(slot_value_number,
				  (SI_Long)0L));
		      else if (INLINE_LONG_VECTOR_P(slot_value_number) != 
			      (SI_Long)0L && 
			      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(slot_value_number)) 
			      == (SI_Long)1L)
			  specific_time_increment_qm = 
				  aref1(slot_value_number,FIX((SI_Long)0L));
		      else
			  specific_time_increment_qm = slot_value_number;
		      if (specific_time_increment_qm) {
			  temp_2 = FIX((SI_Long)1L);
			  tformat(3,string_constant_82,
				  specific_time_increment_qm,
				  NUM_EQ(specific_time_increment_qm,
				  temp_2) ? Qsecond : Qseconds);
		      }
		  }
		  POP_LOCAL_ALLOCATION(0,0);
		  temp_1 = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >> 
			   -  - (SI_Long)16L;
		  UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		  UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),(SI_Long)0L);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensym_list_of_wide_strings = Current_wide_string_list;
	POP_SPECIAL();
	string_1 = Nil;
	ab_loop_list_ = gensym_list_of_wide_strings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	string_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_gensym_cons_pool();
	temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	M_CAR(gensymed_symbol_3) = temp_1;
	M_CDR(gensymed_symbol_3) = Nil;
	inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol_3;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_3 = new_cons;
	}
	else
	    gensymed_symbol_3 = Nil;
	if ( !TRUEP(gensymed_symbol_3))
	    gensymed_symbol_3 = replenish_gensym_cons_pool();
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		Use_full_size_of_with_output_wide_string_cutoff)) {
	    short_string = copy_text_string(string_1);
	    reclaim_text_string(string_1);
	    temp_1 = short_string;
	}
	else
	    temp_1 = string_1;
	M_CAR(gensymed_symbol_3) = temp_1;
	M_CDR(gensymed_symbol_3) = Nil;
	inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol_3;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_2;
      end_loop_2:
	temp_2 = ab_loopvar_;
	goto end_3;
	temp_2 = Qnil;
      end_3:;
	reclaim_gensym_list_1(gensym_list_of_wide_strings);
	temp_2 = make_description_box_with_text(temp_2);
	frames_to_show = gensym_cons_1(temp_2,frames_to_show);
	if (ISVREF(simulation_info_qm,(SI_Long)8L)) {
	    wide_string_bv16 = 
		    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		    (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,
		    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	    new_wide_string = wide_string_bv16;
	    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	      current_wide_string = new_wide_string;
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_83,class_to_print);
		      temp_1 = Current_wide_string;
		      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | 
			      IFIX(aref_arg_2_1) >>  -  - (SI_Long)16L;
		      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		      UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),(SI_Long)0L);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      gensym_list_of_wide_strings = Current_wide_string_list;
	    POP_SPECIAL();
	    string_1 = Nil;
	    ab_loop_list_ = gensym_list_of_wide_strings;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    string_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_gensym_cons_pool();
	    temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	    M_CAR(gensymed_symbol_3) = temp_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_3;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol_3 = new_cons;
	    }
	    else
		gensymed_symbol_3 = Nil;
	    if ( !TRUEP(gensymed_symbol_3))
		gensymed_symbol_3 = replenish_gensym_cons_pool();
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		    Use_full_size_of_with_output_wide_string_cutoff)) {
		short_string = copy_text_string(string_1);
		reclaim_text_string(string_1);
		temp_1 = short_string;
	    }
	    else
		temp_1 = string_1;
	    M_CAR(gensymed_symbol_3) = temp_1;
	    M_CDR(gensymed_symbol_3) = Nil;
	    inline_note_allocate_cons(gensymed_symbol_3,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol_3;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_3;
	  end_loop_3:
	    temp_2 = ab_loopvar_;
	    goto end_4;
	    temp_2 = Qnil;
	  end_4:;
	    reclaim_gensym_list_1(gensym_list_of_wide_strings);
	    temp_2 = make_description_box_with_text(temp_2);
	    frames_to_show = gensym_cons_1(temp_2,frames_to_show);
	    temp_2 = make_short_representation(3,ISVREF(simulation_info_qm,
		    (SI_Long)8L),Nil,Qsmall);
	    frames_to_show = gensym_cons_1(temp_2,frames_to_show);
	}
    }
    frame = variable_or_parameter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_4:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_4;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qvariable_or_parameter)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_5;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_4;
  end_loop_4:
    method_function_qm = Qnil;
  end_5:;
    temp_2 = method_function_qm ? inline_funcall_1(method_function_qm,
	    frame) : Nil;
    return VALUES_1(nconc2(temp_2,frames_to_show));
}

static Object Qg2_defstruct_structure_name_data_server_g2_struct;  /* g2-defstruct-structure-name::data-server-g2-struct */

static Object string_constant_84;  /* "Please note that this variable has been disabled!  " */

static Object string_constant_85;  /* "Please note that this variable is disabled because ~
				    *                         it has a disabled parent or ~
				    *                         is on a subworkspace of an object with the ~
				    *                         deactivatable subworkspaces capability.  "
				    */

static Object string_constant_86;  /* "The data server for this variable is the " */

static Object string_constant_87;  /* "." */

static Object string_constant_88;  /* "This variable references an UNDEFINED data map or alias!" */

static Object string_constant_89;  /* "  This variable does not seek data." */

static Object Qcomputation;        /* computation */

static Object string_constant_90;  /* "  This variable will seek data from its data server." */

static Object string_constant_91;  /* "  This variable does not backward chain." */

static Object string_constant_92;  /* "  This variable depth first backward chains to rules." */

static Object string_constant_93;  /* "  This variable breadth first backward chains to rules." */

static Object string_constant_94;  /* "  This variable may cause forward chaining when it ~
				    *                      receives a new value."
				    */

static Object string_constant_95;  /* "  This variable may not cause forward chaining when it ~
				    *                      receives a new value."
				    */

static Object Qgsi_interface_name;  /* gsi-interface-name */

static Object Qobject;             /* object */

static Object Qidentifying_attributes;  /* identifying-attributes */

static Object string_constant_96;  /* "This variable has " */

static Object string_constant_97;  /* "GSI data service " */

static Object string_constant_98;  /* "and " */

static Object string_constant_99;  /* "GSI message service " */

static Object string_constant_100;  /* "capabilities.  " */

static Object string_constant_101;  /* "capability.  " */

static Object string_constant_102;  /* "The interface name of this variable is ~a.  " */

static Object string_constant_103;  /* "Please note that no GSI interface name ~
				     *                                            has been specified for this variable.  "
				     */

static Object string_constant_104;  /* "Please note that no object named ~a exists." */

static Object string_constant_105;  /* "Please note that the object ~a does not have ~
				     *                                     GSI interface configuration capability.  "
				     */

static Object string_constant_106;  /* "Please note that the interface object named ~a ~
				     *                                     contains no attributes which identify a sensor.  "
				     */

static Object string_constant_107;  /* "Please note that the GSI interface object ~a ~
				     *                                     expects this variable to have "
				     */

static Object string_constant_108;  /* "at least one of the following attributes: " */

static Object string_constant_109;  /* "~a, " */

static Object string_constant_110;  /* "~a.  " */

static Object string_constant_111;  /* "~a, or " */

static Object string_constant_112;  /* "the attribute ~a.  " */

static Object string_constant_113;  /* "at least one of the attributes ~a or ~a.  " */

static Object string_constant_114;  /* "However, this variable lacks " */

static Object string_constant_115;  /* "any of the expected attributes.  " */

static Object string_constant_116;  /* "the expected attribute.  " */

static Object string_constant_117;  /* "either of the expected attributes.  " */

static Object string_constant_118;  /* "This variable receives its value from this specific formula." */

static Object string_constant_119;  /* "The variable receives its value from this generic ~
				     *                              formula, and the following formulas are shadowed ~
				     *                              by it."
				     */

static Object string_constant_120;  /* "The variable receives its value from this generic ~
				     *                              formula."
				     */

static Object string_constant_121;  /* "The following generic formula~a shadowed by the ~
				     *                          specific formula."
				     */

static Object string_constant_122;  /* "s are" */

static Object string_constant_123;  /* " is" */

static Object string_constant_124;  /* "The following backward chaining rule~a shadowed by ~
				     *                          the formula."
				     */

static Object string_constant_125;  /* "The following rule~a ~abackward chained to to ~
				     *                          supply a value for the variable."
				     */

static Object string_constant_126;  /* "depth first " */

static Object string_constant_127;  /* "breadth first " */

/* DESCRIBE-FRAME-FOR-VARIABLE */
Object describe_frame_for_variable(variable)
    Object variable;
{
    Object frames_to_show, class_of_item, source_or_map, server_qm;
    Object data_server_qm, name_of_data_server_qm, temp, specific_formula_qm;
    Object generic_formulas, data_type, links_and_objects;
    Object backward_chaining_links, backward_chaining_rules;
    Object forward_chaining_frames_to_show, forward_chaining_rules;
    Object wide_string_bv16, new_wide_string, current_wide_string_list;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, aref_arg_2_1, gensym_list_of_wide_strings, string_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object gensymed_symbol, short_string, item_has_gsi_data_service_p;
    Object item_has_gsi_message_service_p, item_has_both_gsi_services_p;
    Object gsi_interface_name, gsi_interface, interface_has_capability_p;
    Object required_sensor_id_attribute_or_attributes;
    Object required_sensor_id_attribute, disjoint_sensor_attributes_p;
    Object required_attribute, remaining_required_attributes, generic;
    Object short_representation, frame, sub_vector_qm, method_function_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_;
    char forward_chain_qm, depth_first_qm, dont_data_seek_qm;
    char manually_disabled_qm, disabled_through_ancestor_qm;
    char dont_backward_chain_qm;
    Declare_special(5);
    Object result;

    x_note_fn_call(214,126);
    frames_to_show = Nil;
    class_of_item = ISVREF(ISVREF(variable,(SI_Long)1L),(SI_Long)1L);
    forward_chain_qm = (SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) 
	    & (SI_Long)2L);
    depth_first_qm = (SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) & 
	    (SI_Long)8L);
    dont_data_seek_qm = (SI_Long)0L != (IFIX(ISVREF(variable,(SI_Long)4L)) 
	    & (SI_Long)16L);
    source_or_map = ISVREF(variable,(SI_Long)31L);
    server_qm = ATOM(source_or_map) ? 
	    lookup_kb_specific_property_value(source_or_map,
	    Data_server_or_alias_qm_kbprop) : Nil;
    data_server_qm = server_qm ? server_qm : 
	    warn_of_undefined_data_server(variable,source_or_map);
    name_of_data_server_qm = SIMPLE_VECTOR_P(data_server_qm) && 
	    EQ(ISVREF(data_server_qm,(SI_Long)0L),
	    Qg2_defstruct_structure_name_data_server_g2_struct) ? 
	    ISVREF(data_server_qm,(SI_Long)1L) : data_server_qm;
    manually_disabled_qm = (SI_Long)0L != (IFIX(ISVREF(variable,
	    (SI_Long)4L)) & (SI_Long)8192L);
    disabled_through_ancestor_qm = (SI_Long)0L != (IFIX(ISVREF(variable,
	    (SI_Long)5L)) & (SI_Long)256L);
    dont_backward_chain_qm = (SI_Long)0L != (IFIX(ISVREF(variable,
	    (SI_Long)4L)) & (SI_Long)32768L);
    temp = ISVREF(variable,(SI_Long)28L);
    specific_formula_qm = CAR(temp);
    generic_formulas = collect_generic_formulas_for_variable(variable);
    data_type = type_specification_of_variable_or_parameter_value(variable);
    if ( !(dont_data_seek_qm || dont_backward_chain_qm)) {
	links_and_objects = Nil;
	PUSH_SPECIAL(Links_and_objects,links_and_objects,0);
	  collect_rules_for_backward_chaining(variable,data_type);
	  backward_chaining_links = Links_and_objects;
	POP_SPECIAL();
    }
    else
	backward_chaining_links = Nil;
    backward_chaining_rules = 
	    rules_in_backward_link_list(backward_chaining_links);
    forward_chaining_frames_to_show = Nil;
    forward_chaining_rules = Nil;
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
      current_wide_string = new_wide_string;
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      if (manually_disabled_qm)
		  tformat(1,string_constant_84);
	      else if (disabled_through_ancestor_qm)
		  tformat(1,string_constant_85);
	      if (name_of_data_server_qm) {
		  tformat(1,string_constant_86);
		  write_data_server_map_from_slot(name_of_data_server_qm,Nil);
		  tformat(1,string_constant_87);
	      }
	      else
		  tformat(1,string_constant_88);
	      if (dont_data_seek_qm)
		  tformat(1,string_constant_89);
	      else if ( !EQ(data_server_qm,Qcomputation))
		  tformat(1,string_constant_90);
	      else if (dont_backward_chain_qm)
		  tformat(1,string_constant_91);
	      else if (depth_first_qm)
		  tformat(1,string_constant_92);
	      else
		  tformat(1,string_constant_93);
	      tformat(1,forward_chain_qm ? string_constant_94 : 
		      string_constant_95);
	      temp_1 = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  -  
		      - (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp_1 = short_string;
    }
    else
	temp_1 = string_1;
    M_CAR(gensymed_symbol) = temp_1;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
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
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    temp = make_description_box_with_text(temp);
    frames_to_show = gensym_cons_1(temp,frames_to_show);
    item_has_gsi_data_service_p = gsi_data_service_p_function(variable);
    item_has_gsi_message_service_p = gsi_message_service_p_function(variable);
    if (item_has_gsi_data_service_p || item_has_gsi_message_service_p) {
	item_has_both_gsi_services_p = item_has_gsi_data_service_p ? 
		item_has_gsi_message_service_p : Qnil;
	gsi_interface_name = get_slot_value_if_any_function(variable,
		Qgsi_interface_name,Nil);
	gsi_interface = gsi_interface_name ? 
		get_instance_with_name_if_any(Qobject,gsi_interface_name) :
		 Qnil;
	interface_has_capability_p = gsi_interface ? 
		gsi_interface_p_function(gsi_interface) : Qnil;
	required_sensor_id_attribute_or_attributes = gsi_interface ? 
		get_slot_value_if_any_function(gsi_interface,
		Qidentifying_attributes,Nil) : Qnil;
	if (CONSP(required_sensor_id_attribute_or_attributes)) {
	    required_sensor_id_attribute = Nil;
	    ab_loop_list_ = required_sensor_id_attribute_or_attributes;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    required_sensor_id_attribute = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (attribute_of_class_p(required_sensor_id_attribute,
		    class_of_item)) {
		disjoint_sensor_attributes_p = Nil;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    disjoint_sensor_attributes_p = T;
	    goto end_2;
	    disjoint_sensor_attributes_p = Qnil;
	  end_2:;
	}
	else
	    disjoint_sensor_attributes_p =  
		    !TRUEP(attribute_of_class_p(required_sensor_id_attribute_or_attributes,
		    class_of_item)) ? T : Nil;
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		(SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,
		IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	  current_wide_string = new_wide_string;
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(1,string_constant_96);
		  if (item_has_gsi_data_service_p)
		      tformat(1,string_constant_97);
		  if (item_has_both_gsi_services_p)
		      tformat(1,string_constant_98);
		  if (item_has_gsi_message_service_p)
		      tformat(1,string_constant_99);
		  if (item_has_both_gsi_services_p)
		      tformat(1,string_constant_100);
		  else
		      tformat(1,string_constant_101);
		  if (gsi_interface_name)
		      tformat(2,string_constant_102,gsi_interface_name);
		  else {
		      tformat(1,string_constant_103);
		      goto end_describing_gsi_sensor;
		  }
		  if ( !TRUEP(gsi_interface)) {
		      tformat(2,string_constant_104,gsi_interface_name);
		      goto end_describing_gsi_sensor;
		  }
		  if ( !TRUEP(interface_has_capability_p)) {
		      tformat(2,string_constant_105,gsi_interface_name);
		      goto end_describing_gsi_sensor;
		  }
		  if ( !TRUEP(required_sensor_id_attribute_or_attributes)) {
		      tformat(2,string_constant_106,gsi_interface_name);
		      goto end_describing_gsi_sensor;
		  }
		  if (disjoint_sensor_attributes_p) {
		      tformat(2,string_constant_107,gsi_interface_name);
		      if (CONSP(required_sensor_id_attribute_or_attributes)) {
			  temp = 
				  length(required_sensor_id_attribute_or_attributes);
			  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L)))) {
			      tformat(1,string_constant_108);
			      required_attribute = Nil;
			      remaining_required_attributes = Nil;
			      ab_loop_list_ = 
				      required_sensor_id_attribute_or_attributes;
			    next_loop_2:
			      if ( !TRUEP(ab_loop_list_))
				  goto end_loop_2;
			      required_attribute = CAR(ab_loop_list_);
			      remaining_required_attributes = 
				      CDR(ab_loop_list_);
			      ab_loop_list_ = M_CDR(ab_loop_list_);
			      temp = length(remaining_required_attributes);
			      if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) 
				      && FIXNUM_LE(temp,FIX((SI_Long)127L))))
				  tformat(2,string_constant_109,
					  required_attribute);
			      else
				  switch (INTEGER_TO_CHAR(temp)) {
				    case 0:
				      tformat(2,string_constant_110,
					      required_attribute);
				      break;
				    case 1:
				      tformat(2,string_constant_111,
					      required_attribute);
				      break;
				    default:
				      tformat(2,string_constant_109,
					      required_attribute);
				      break;
				  }
			      goto next_loop_2;
			    end_loop_2:;
			  }
			  else
			      switch (INTEGER_TO_CHAR(temp)) {
				case 1:
				  tformat(2,string_constant_112,
					  FIRST(required_sensor_id_attribute_or_attributes));
				  break;
				case 2:
				  tformat(3,string_constant_113,
					  FIRST(required_sensor_id_attribute_or_attributes),
					  SECOND(required_sensor_id_attribute_or_attributes));
				  break;
				default:
				  tformat(1,string_constant_108);
				  required_attribute = Nil;
				  remaining_required_attributes = Nil;
				  ab_loop_list_ = 
					  required_sensor_id_attribute_or_attributes;
				next_loop_3:
				  if ( !TRUEP(ab_loop_list_))
				      goto end_loop_3;
				  required_attribute = CAR(ab_loop_list_);
				  remaining_required_attributes = 
					  CDR(ab_loop_list_);
				  ab_loop_list_ = M_CDR(ab_loop_list_);
				  temp = length(remaining_required_attributes);
				  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),
					  temp) && FIXNUM_LE(temp,
					  FIX((SI_Long)127L))))
				      tformat(2,string_constant_109,
					      required_attribute);
				  else
				      switch (INTEGER_TO_CHAR(temp)) {
					case 0:
					  tformat(2,string_constant_110,
						  required_attribute);
					  break;
					case 1:
					  tformat(2,string_constant_111,
						  required_attribute);
					  break;
					default:
					  tformat(2,string_constant_109,
						  required_attribute);
					  break;
				      }
				  goto next_loop_3;
				end_loop_3:;
				  break;
			      }
		      }
		      else
			  tformat(2,string_constant_112,
				  required_sensor_id_attribute_or_attributes);
		      tformat(1,string_constant_114);
		      if (CONSP(required_sensor_id_attribute_or_attributes)) {
			  temp = 
				  length(required_sensor_id_attribute_or_attributes);
			  if ( !(FIXNUM_LE(FIX((SI_Long)-128L),temp) && 
				  FIXNUM_LE(temp,FIX((SI_Long)127L))))
			      tformat(1,string_constant_115);
			  else
			      switch (INTEGER_TO_CHAR(temp)) {
				case 1:
				  tformat(1,string_constant_116);
				  break;
				case 2:
				  tformat(1,string_constant_117);
				  break;
				default:
				  tformat(1,string_constant_115);
				  break;
			      }
		      }
		      else
			  tformat(1,string_constant_116);
		      goto end_describing_gsi_sensor;
		  }
		end_describing_gsi_sensor:
		  temp_1 = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp_1));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >> 
			   -  - (SI_Long)16L;
		  UBYTE_16_ISASET_1(temp_1,aref_arg_2,aref_new_value);
		  UBYTE_16_ISASET_1(temp_1,IFIX(aref_arg_2_1),(SI_Long)0L);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensym_list_of_wide_strings = Current_wide_string_list;
	POP_SPECIAL();
	string_1 = Nil;
	ab_loop_list_ = gensym_list_of_wide_strings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_4:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_4;
	string_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	temp_1 = make_lost_spaces_text_element(FIX((SI_Long)0L));
	M_CAR(gensymed_symbol) = temp_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		Use_full_size_of_with_output_wide_string_cutoff)) {
	    short_string = copy_text_string(string_1);
	    reclaim_text_string(string_1);
	    temp_1 = short_string;
	}
	else
	    temp_1 = string_1;
	M_CAR(gensymed_symbol) = temp_1;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_4;
      end_loop_4:
	temp = ab_loopvar_;
	goto end_3;
	temp = Qnil;
      end_3:;
	reclaim_gensym_list_1(gensym_list_of_wide_strings);
	temp = make_description_box_with_text(temp);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
    }
    if (specific_formula_qm) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(1,string_constant_118);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = make_description_box(temp);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
	temp = ISVREF(variable,(SI_Long)28L);
	temp = make_description_box_with_text(copy_text(CDR(temp)));
	frames_to_show = gensym_cons_1(temp,frames_to_show);
    }
    if (generic_formulas) {
	if ( !TRUEP(specific_formula_qm)) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      if (CDR(generic_formulas))
			  tformat(1,string_constant_119);
		      else
			  tformat(1,string_constant_120);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = make_description_box(temp);
	    frames_to_show = gensym_cons_1(temp,frames_to_show);
	}
	else {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_121,CDR(generic_formulas) ?
			       string_constant_122 : string_constant_123);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = make_description_box(temp);
	    frames_to_show = gensym_cons_1(temp,frames_to_show);
	}
	generic = Nil;
	ab_loop_list_ = generic_formulas;
	short_representation = Nil;
      next_loop_5:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_5;
	generic = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	short_representation = make_short_representation(3,generic,Nil,Qsmall);
	frames_to_show = gensym_cons_1(short_representation,frames_to_show);
	goto next_loop_5;
      end_loop_5:;
    }
    if (backward_chaining_links) {
	if (specific_formula_qm || generic_formulas) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(2,string_constant_124,
			      CDR(backward_chaining_links) ? 
			      string_constant_122 : string_constant_123);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = make_description_box(temp);
	    frames_to_show = gensym_cons_1(temp,frames_to_show);
	}
	else {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(3,string_constant_125,
			      CDR(backward_chaining_links) ? 
			      string_constant_122 : string_constant_123,
			      CDR(backward_chaining_links) ? 
			      (depth_first_qm ? string_constant_126 : 
			      string_constant_127) : string_constant_9);
		      temp = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp = make_description_box(temp);
	    frames_to_show = gensym_cons_1(temp,frames_to_show);
	}
	temp = 
		short_representations_of_backward_invocations(backward_chaining_links);
	frames_to_show = nconc2(temp,frames_to_show);
    }
    reclaim_gensym_tree_1(backward_chaining_links);
    reclaim_gensym_list_1(generic_formulas);
    result = collect_all_rules_for_forward_chaining(variable);
    MVS_2(result,forward_chaining_frames_to_show,forward_chaining_rules);
    frames_to_show = nconc2(forward_chaining_frames_to_show,frames_to_show);
    backward_chaining_rules = nconc2(backward_chaining_rules,
	    forward_chaining_rules);
    temp = collect_all_mentioning_rules(variable,backward_chaining_rules);
    frames_to_show = nconc2(temp,frames_to_show);
    reclaim_gensym_list_1(backward_chaining_rules);
    frame = variable;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_6:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_6;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qvariable)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_4;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_6;
  end_loop_6:
    method_function_qm = Qnil;
  end_4:;
    temp = method_function_qm ? inline_funcall_1(method_function_qm,frame) 
	    : Nil;
    return VALUES_1(nconc2(temp,frames_to_show));
}

static Object string_constant_128;  /* "Please note that this parameter has been disabled!  " */

static Object string_constant_129;  /* "Please note that this parameter is disabled because ~
				     *                             it has a disabled parent or ~
				     *                             is on a subworkspace of an object with the ~
				     *                             deactivatable subworkspaces capability.  "
				     */

static Object string_constant_130;  /* "This parameter may cause forward chaining when it ~
				     *                      receives a new value."
				     */

static Object string_constant_131;  /* "This parameter may not cause forward chaining when it ~
				     *                      receives a new value."
				     */

/* DESCRIBE-FRAME-FOR-PARAMETER */
Object describe_frame_for_parameter(parameter)
    Object parameter;
{
    Object frames_to_show, forward_chaining_frames_to_show, wide_string_bv16;
    Object new_wide_string, current_wide_string_list, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, aref_arg_2_1, gensym_list_of_wide_strings, string_1;
    Object ab_loop_list_, ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons;
    Object gensymed_symbol, short_string, temp_1, frame, sub_vector_qm;
    Object method_function_qm;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1, index_1;
    SI_Long ab_loop_bind_;
    char forward_chain_qm, manually_disabled_qm, disabled_through_ancestor_qm;
    Declare_special(5);

    x_note_fn_call(214,127);
    frames_to_show = Nil;
    forward_chain_qm = (SI_Long)0L != (IFIX(ISVREF(parameter,(SI_Long)4L)) 
	    & (SI_Long)2L);
    manually_disabled_qm = (SI_Long)0L != (IFIX(ISVREF(parameter,
	    (SI_Long)4L)) & (SI_Long)8192L);
    disabled_through_ancestor_qm = (SI_Long)0L != (IFIX(ISVREF(parameter,
	    (SI_Long)5L)) & (SI_Long)256L);
    forward_chaining_frames_to_show = Nil;
    wide_string_bv16 = 
	    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
	    + (SI_Long)3L));
    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
    aref_arg_2 = bv16_length - (SI_Long)2L;
    aref_new_value = IFIX(Wide_string_list_maximum_length) & (SI_Long)65535L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    aref_arg_2 = bv16_length - (SI_Long)1L;
    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
    UBYTE_16_ISASET_1(wide_string_bv16,
	    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
    new_wide_string = wide_string_bv16;
    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
      current_wide_string = new_wide_string;
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      if (manually_disabled_qm)
		  tformat(1,string_constant_128);
	      else if (disabled_through_ancestor_qm)
		  tformat(1,string_constant_129);
	      tformat(1,forward_chain_qm ? string_constant_130 : 
		      string_constant_131);
	      temp = Current_wide_string;
	      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
	      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
	      aref_arg_2 = bv16_length - (SI_Long)2L;
	      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      aref_arg_2 = bv16_length - (SI_Long)1L;
	      aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >>  -  
		      - (SI_Long)16L;
	      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
	      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)0L);
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
      gensym_list_of_wide_strings = Current_wide_string_list;
    POP_SPECIAL();
    string_1 = Nil;
    ab_loop_list_ = gensym_list_of_wide_strings;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    string_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
    if (ab_loopvar__1)
	M_CDR(ab_loopvar__1) = ab_loopvar__2;
    else
	ab_loopvar_ = ab_loopvar__2;
    ab_loopvar__1 = ab_loopvar__2;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)2L) + 
	    ((UBYTE_16_ISAREF_1(string_1,length_1 - (SI_Long)1L) & 
	    (SI_Long)8191L) << (SI_Long)16L)),
	    Use_full_size_of_with_output_wide_string_cutoff)) {
	short_string = copy_text_string(string_1);
	reclaim_text_string(string_1);
	temp = short_string;
    }
    else
	temp = string_1;
    M_CAR(gensymed_symbol) = temp;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ab_loopvar__2 = gensymed_symbol;
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
    reclaim_gensym_list_1(gensym_list_of_wide_strings);
    temp_1 = make_description_box_with_text(temp_1);
    frames_to_show = gensym_cons_1(temp_1,frames_to_show);
    temp_1 = collect_all_rules_for_forward_chaining(parameter);
    gensymed_symbol = temp_1;
    forward_chaining_frames_to_show = gensymed_symbol;
    frames_to_show = nconc2(forward_chaining_frames_to_show,frames_to_show);
    frame = parameter;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_1:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_1;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qparameter)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_2;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_1;
  end_loop_1:
    method_function_qm = Qnil;
  end_2:;
    temp_1 = method_function_qm ? inline_funcall_1(method_function_qm,
	    frame) : Nil;
    return VALUES_1(nconc2(temp_1,frames_to_show));
}

static Object Qimage_definition;   /* image-definition */

static Object Qimage_definition_cached_data_qm;  /* image-definition-cached-data? */

static Object string_constant_132;  /* "This is a ~dx~dx~d ~a image" */

/* DESCRIBE-FRAME-FOR-IMAGE-DEFINITION */
Object describe_frame_for_image_definition(image_definition)
    Object image_definition;
{
    Object frame, sub_vector_qm, method_function_qm, temp, frames;
    Object image_data_qm, temp_1, temp_2, temp_3, temp_4;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,128);
    frame = image_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qimage_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop;
  end_loop:
    method_function_qm = Qnil;
  end_1:;
    temp = method_function_qm ? inline_funcall_1(method_function_qm,frame) 
	    : Nil;
    frames = Nil;
    image_data_qm = get_lookup_slot_value_given_default(image_definition,
	    Qimage_definition_cached_data_qm,Nil);
    if (image_data_qm) {
	temp_1 = ISVREF(image_data_qm,(SI_Long)5L);
	temp_2 = ISVREF(image_data_qm,(SI_Long)6L);
	temp_3 = ISVREF(image_data_qm,(SI_Long)7L);
	temp_4 = ISVREF(image_data_qm,(SI_Long)3L);
	if (temp_4);
	else
	    temp_4 = string_constant_9;
	temp_4 = tformat_text_string(5,string_constant_132,temp_1,temp_2,
		temp_3,temp_4);
	frames = gensym_cons_1(temp_4,frames);
    }
    return VALUES_1(nconc2(temp,nreverse(frames)));
}

static Object string_constant_133;  /* "The following are methods defined for ~
				     *                   this method-declaration:"
				     */

static Object string_constant_134;  /* "There are no methods defined for this ~
				     *                   method-declaration."
				     */

/* DESCRIBE-FRAME-FOR-METHOD-DECLARATION */
Object describe_frame_for_method_declaration(method_declaration)
    Object method_declaration;
{
    Object frames_to_show, description_header, name_or_names_qm;
    Object method_name_qm, specific_methods_defined_p_qm, class_1;
    Object ab_loop_list_, class_methods_qm, ab_loop_desetq_, specific_method;
    Object ab_loop_list__1, temp, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,129);
    frames_to_show = Nil;
    description_header = Nil;
    name_or_names_qm = 
	    get_lookup_slot_value_given_default(method_declaration,
	    Qname_or_names_for_frame,Nil);
    method_name_qm = name_or_names_qm && SYMBOLP(name_or_names_qm) ? 
	    name_or_names_qm : Qnil;
    specific_methods_defined_p_qm = Nil;
    if (method_name_qm) {
	class_1 = Nil;
	ab_loop_list_ = lookup_kb_specific_property_value(method_name_qm,
		Classes_of_procedure_method_kbprop);
	class_methods_qm = Nil;
	ab_loop_desetq_ = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	ab_loop_desetq_ = M_CAR(ab_loop_list_);
	class_1 = CAR(ab_loop_desetq_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	class_methods_qm = 
		get_named_procedure_methods_for_class(method_name_qm,class_1);
	if (class_methods_qm) {
	    specific_methods_defined_p_qm = T;
	    specific_method = Nil;
	    ab_loop_list__1 = CDR(class_methods_qm);
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list__1))
		goto end_loop_1;
	    specific_method = M_CAR(ab_loop_list__1);
	    ab_loop_list__1 = M_CDR(ab_loop_list__1);
	    temp = make_short_representation(3,specific_method,Nil,Qsmall);
	    frames_to_show = gensym_cons_1(temp,frames_to_show);
	    goto next_loop_1;
	  end_loop_1:;
	}
	goto next_loop;
      end_loop:;
    }
    description_header = 
	    make_description_box(specific_methods_defined_p_qm ? 
	    tformat_text_string(1,string_constant_133) : 
	    tformat_text_string(1,string_constant_134));
    frame = method_declaration;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_2:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_2;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qmethod_declaration)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_1;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_2;
  end_loop_2:
    method_function_qm = Qnil;
  end_1:;
    temp = method_function_qm ? inline_funcall_1(method_function_qm,frame) 
	    : Nil;
    return VALUES_1(nconc2(temp,nconc2(frames_to_show,
	    gensym_cons_1(description_header,Nil))));
}

static Object string_constant_135;  /* "The following methods are defined specifically for this class." */

static Object string_constant_136;  /* "There are no methods defined specifically for this class." */

/* DESCRIBE-FRAME-FOR-CLASS-DEFINITION */
Object describe_frame_for_class_definition(class_definition)
    Object class_definition;
{
    Object class_methods_qm, short_representations, method_information;
    Object ab_loop_list_, method, ab_loop_list__1, temp, frames_to_show_qm;
    Object description_header, frame, sub_vector_qm, method_function_qm;
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(214,130);
    class_methods_qm = 
	    lookup_kb_specific_property_value(ISVREF(class_definition,
	    (SI_Long)20L),Procedure_methods_of_class_kbprop);
    if (class_methods_qm) {
	short_representations = Nil;
	method_information = Nil;
	ab_loop_list_ = class_methods_qm;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	method_information = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	method = Nil;
	ab_loop_list__1 = CDR(method_information);
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	method = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = make_short_representation(3,method,Nil,Qsmall);
	short_representations = gensym_cons_1(temp,short_representations);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	frames_to_show_qm = short_representations;
	goto end_1;
	frames_to_show_qm = Qnil;
      end_1:;
    }
    else
	frames_to_show_qm = Nil;
    description_header = make_description_box(class_methods_qm ? 
	    tformat_text_string(1,string_constant_135) : 
	    tformat_text_string(1,string_constant_136));
    frame = class_definition;
    sub_vector_qm = ISVREF(ISVREF(ISVREF(frame,(SI_Long)1L),(SI_Long)11L),
	    (SI_Long)15L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_vector_qm)) - 
	    (SI_Long)3L;
  next_loop_2:
    if (index_1 >= ab_loop_bind_)
	goto end_loop_2;
    if (EQ(ISVREF(sub_vector_qm,index_1),Qclass_definition)) {
	method_function_qm = ISVREF(sub_vector_qm,index_1 + (SI_Long)3L);
	goto end_2;
    }
    index_1 = index_1 + (SI_Long)2L;
    goto next_loop_2;
  end_loop_2:
    method_function_qm = Qnil;
  end_2:;
    temp = method_function_qm ? inline_funcall_1(method_function_qm,frame) 
	    : Nil;
    return VALUES_1(nconc2(temp,nconc2(frames_to_show_qm,
	    gensym_cons_1(description_header,Nil))));
}

static Object Qg2_expression_cell;  /* g2-expression-cell */

static Object array_constant_17;   /* # */

static Object array_constant_18;   /* # */

static Object array_constant_19;   /* # */

static Object array_constant_20;   /* # */

static Object Qembedded_rule_qm;   /* embedded-rule? */

static Object array_constant_21;   /* # */

static Object Qg2_defstruct_structure_name_byte_code_body_g2_struct;  /* g2-defstruct-structure-name::byte-code-body-g2-struct */

static Object array_constant_22;   /* # */

/* DISASSEMBLE-ITEM-IF-APPROPRIATE */
Object disassemble_item_if_appropriate(item)
    Object item;
{
    Object code_bodies_and_denotations_qm, g2_cell_array_qm, managed_array;
    Object current_computation_component_particulars, element, temp;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp_1, gensymed_symbol, sub_class_bit_vector, new_wide_string;
    Object aref_arg_2_1, gensym_list_of_wide_strings, string_1, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, new_cons, short_string;
    Object frames_to_show, denotation_qm, code_body_qm, ab_loop_desetq_;
    Object ab_loop_list__1;
    SI_Long index_1, ab_loop_bind_, bv16_length, aref_arg_2, aref_new_value;
    SI_Long length_1, superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_2;
    Declare_special(6);

    x_note_fn_call(214,131);
    code_bodies_and_denotations_qm = Nil;
    g2_cell_array_qm = get_lookup_slot_value_given_default(item,
	    Qcell_array,Nil);
    if (g2_cell_array_qm) {
	managed_array = ISVREF(g2_cell_array_qm,(SI_Long)3L);
	if (managed_array) {
	    current_computation_component_particulars = 
		    gensym_list_2(Qcell_array_element,FIX((SI_Long)0L));
	    PUSH_SPECIAL(Current_computation_component_particulars,current_computation_component_particulars,
		    5);
	      index_1 = (SI_Long)0L;
	      ab_loop_bind_ = IFIX(ISVREF(managed_array,(SI_Long)1L));
	      element = Nil;
	    next_loop:
	      if (index_1 >= ab_loop_bind_)
		  goto end_loop;
	      element = FIXNUM_LE(ISVREF(managed_array,(SI_Long)1L),
		      Maximum_in_place_array_size) ? ISVREF(managed_array,
		      index_1 + IFIX(Managed_array_index_offset)) : 
		      ISVREF(ISVREF(managed_array,(index_1 >>  -  - 
		      (SI_Long)10L) + (SI_Long)2L),index_1 & (SI_Long)1023L);
	      if (of_class_p_function(element,Qg2_expression_cell)) {
		  temp = Current_computation_component_particulars;
		  M_SECOND(temp) = FIX(index_1);
		  current_wide_string_list = Qdo_not_use;
		  PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,
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
		    PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		      fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		      PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			      2);
			length_1 = 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
			total_length_of_current_wide_string = 
				FIX(UBYTE_16_ISAREF_1(Current_wide_string,
				length_1 - (SI_Long)2L) + 
				((UBYTE_16_ISAREF_1(Current_wide_string,
				length_1 - (SI_Long)1L) & (SI_Long)8191L) 
				<< (SI_Long)16L));
			PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
				1);
			  current_twriting_output_type = Qwide_string;
			  PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
				  0);
			    twrite_beginning_of_wide_string(array_constant_17,
				    FIX((SI_Long)16L));
			    denote_component_of_block(1,Nil);
			    temp_1 = copy_out_current_wide_string();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		  code_bodies_and_denotations_qm = 
			  gensym_cons_1(gensym_cons_1(temp_1,
			  ISVREF(element,(SI_Long)10L)),
			  code_bodies_and_denotations_qm);
	      }
	      index_1 = index_1 + (SI_Long)1L;
	      goto next_loop;
	    end_loop:
	      reclaim_gensym_list_1(Current_computation_component_particulars);
	    POP_SPECIAL();
	}
    }
    gensymed_symbol = ISVREF(item,(SI_Long)1L);
    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
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
	temp_2 = (SI_Long)0L < gensymed_symbol_1;
    }
    else
	temp_2 = TRUEP(Nil);
    if (temp_2) {
	if (ISVREF(item,(SI_Long)28L)) {
	    wide_string_bv16 = 
		    allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		    + (SI_Long)3L));
	    bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	    aref_arg_2 = bv16_length - (SI_Long)2L;
	    aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		    (SI_Long)65535L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    aref_arg_2 = bv16_length - (SI_Long)1L;
	    aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	    UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	    UBYTE_16_ISASET_1(wide_string_bv16,
		    IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	    new_wide_string = wide_string_bv16;
	    current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	      current_wide_string = new_wide_string;
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      write_disassembled_code_bodies(ISVREF(item,
			      (SI_Long)28L));
		      temp = Current_wide_string;
		      aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		      bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
		      aref_arg_2 = bv16_length - (SI_Long)2L;
		      aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
		      aref_arg_2 = bv16_length - (SI_Long)1L;
		      aref_new_value = (SI_Long)57344L | 
			      IFIX(aref_arg_2_1) >>  -  - (SI_Long)16L;
		      UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
		      UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)0L);
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	      gensym_list_of_wide_strings = Current_wide_string_list;
	    POP_SPECIAL();
	    string_1 = Nil;
	    ab_loop_list_ = gensym_list_of_wide_strings;
	    ab_loopvar_ = Nil;
	    ab_loopvar__1 = Nil;
	    ab_loopvar__2 = Nil;
	  next_loop_1:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_1;
	    string_1 = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_gensym_cons_pool();
	    temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
	    M_CAR(gensymed_symbol) = temp;
	    M_CDR(gensymed_symbol) = Nil;
	    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    new_cons = Available_gensym_conses;
	    if (new_cons) {
		Available_gensym_conses = M_CDR(new_cons);
		gensymed_symbol = new_cons;
	    }
	    else
		gensymed_symbol = Nil;
	    if ( !TRUEP(gensymed_symbol))
		gensymed_symbol = replenish_gensym_cons_pool();
	    length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	    if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		    (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		    Use_full_size_of_with_output_wide_string_cutoff)) {
		short_string = copy_text_string(string_1);
		reclaim_text_string(string_1);
		temp = short_string;
	    }
	    else
		temp = string_1;
	    M_CAR(gensymed_symbol) = temp;
	    M_CDR(gensymed_symbol) = Nil;
	    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	    ab_loopvar__2 = gensymed_symbol;
	    if (ab_loopvar__1)
		M_CDR(ab_loopvar__1) = ab_loopvar__2;
	    else
		ab_loopvar_ = ab_loopvar__2;
	    ab_loopvar__1 = ab_loopvar__2;
	    goto next_loop_1;
	  end_loop_1:
	    temp_1 = ab_loopvar_;
	    goto end_1;
	    temp_1 = Qnil;
	  end_1:;
	    reclaim_gensym_list_1(gensym_list_of_wide_strings);
	    return gensym_cons_1(make_description_box_with_text(temp_1),Nil);
	}
    }
    else {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Function_definition_class_description,
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
	    temp_2 = (SI_Long)0L < gensymed_symbol_1;
	}
	else
	    temp_2 = TRUEP(Nil);
	if (temp_2)
	    code_bodies_and_denotations_qm = 
		    gensym_cons_1(gensym_cons_1(Nil,ISVREF(item,
		    (SI_Long)20L)),code_bodies_and_denotations_qm);
	else {
	    sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	    superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
		temp_2 = (SI_Long)0L < gensymed_symbol_1;
	    }
	    else
		temp_2 = TRUEP(Nil);
	    if (temp_2)
		code_bodies_and_denotations_qm = 
			gensym_cons_1(gensym_cons_1(Nil,ISVREF(item,
			(SI_Long)31L)),code_bodies_and_denotations_qm);
	    else {
		sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Generic_simulation_formula_class_description,
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
		    temp_2 = (SI_Long)0L < gensymed_symbol_1;
		}
		else
		    temp_2 = TRUEP(Nil);
		if (temp_2) {
		    temp_1 = 
			    copy_constant_wide_string_given_length(array_constant_18,
			    FIX((SI_Long)27L));
		    code_bodies_and_denotations_qm = 
			    gensym_cons_1(gensym_cons_1(temp_1,ISVREF(item,
			    (SI_Long)20L)),code_bodies_and_denotations_qm);
		    if (ISVREF(item,(SI_Long)21L)) {
			temp_1 = 
				copy_constant_wide_string_given_length(array_constant_19,
				FIX((SI_Long)43L));
			code_bodies_and_denotations_qm = 
				gensym_cons_1(gensym_cons_1(temp_1,
				ISVREF(item,(SI_Long)21L)),
				code_bodies_and_denotations_qm);
		    }
		}
		else {
		    sub_class_bit_vector = ISVREF(gensymed_symbol,
			    (SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Simulation_subtable_class_description,
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
			temp_2 = (SI_Long)0L < gensymed_symbol_1;
		    }
		    else
			temp_2 = TRUEP(Nil);
		    if (temp_2) {
			code_bodies_and_denotations_qm = 
				gensym_cons_1(gensym_cons_1(Nil,
				ISVREF(item,(SI_Long)23L)),
				code_bodies_and_denotations_qm);
			temp_1 = 
				copy_constant_wide_string_given_length(array_constant_20,
				FIX((SI_Long)44L));
			code_bodies_and_denotations_qm = 
				gensym_cons_1(gensym_cons_1(temp_1,
				ISVREF(item,(SI_Long)24L)),
				code_bodies_and_denotations_qm);
		    }
		    else {
			sub_class_bit_vector = ISVREF(gensymed_symbol,
				(SI_Long)19L);
			superior_class_bit_number = 
				IFIX(ISVREF(Action_button_class_description,
				(SI_Long)18L));
			sub_class_vector_index = superior_class_bit_number 
				>>  -  - (SI_Long)3L;
			if (sub_class_vector_index < 
				IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				    {
			    gensymed_symbol_1 = 
				    UBYTE_8_ISAREF_1(sub_class_bit_vector,
				    sub_class_vector_index);
			    gensymed_symbol_2 = (SI_Long)1L;
			    gensymed_symbol_3 = superior_class_bit_number 
				    & (SI_Long)7L;
			    gensymed_symbol_2 = gensymed_symbol_2 << 
				    gensymed_symbol_3;
			    gensymed_symbol_1 = gensymed_symbol_1 & 
				    gensymed_symbol_2;
			    temp_2 = (SI_Long)0L < gensymed_symbol_1;
			}
			else
			    temp_2 = TRUEP(Nil);
			if (temp_2) {
			    if (get_slot_value_function(item,
				    Qembedded_rule_qm,Nil))
				code_bodies_and_denotations_qm = 
					gensym_cons_1(gensym_cons_1(Nil,
					ISVREF(get_slot_value_function(item,
					Qembedded_rule_qm,Nil),
					(SI_Long)31L)),
					code_bodies_and_denotations_qm);
			}
			else {
			    sub_class_bit_vector = ISVREF(gensymed_symbol,
				    (SI_Long)19L);
			    superior_class_bit_number = 
				    IFIX(ISVREF(User_menu_choice_class_description,
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
				gensymed_symbol_2 = gensymed_symbol_2 << 
					gensymed_symbol_3;
				gensymed_symbol_1 = gensymed_symbol_1 & 
					gensymed_symbol_2;
				temp_2 = (SI_Long)0L < gensymed_symbol_1;
			    }
			    else
				temp_2 = TRUEP(Nil);
			    if (temp_2) {
				if (ISVREF(item,(SI_Long)24L))
				    code_bodies_and_denotations_qm = 
					    gensym_cons_1(gensym_cons_1(Nil,
					    ISVREF(ISVREF(item,
					    (SI_Long)24L),(SI_Long)31L)),
					    code_bodies_and_denotations_qm);
			    }
			}
		    }
		}
	    }
	}
    }
    code_bodies_and_denotations_qm = nreverse(code_bodies_and_denotations_qm);
    frames_to_show = Nil;
    denotation_qm = Nil;
    code_body_qm = Nil;
    ab_loop_list_ = code_bodies_and_denotations_qm;
    ab_loop_desetq_ = Nil;
  next_loop_2:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop_2;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    denotation_qm = CAR(ab_loop_desetq_);
    code_body_qm = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    temp_1 = make_description_box(denotation_qm ? denotation_qm : 
	    copy_constant_wide_string_given_length(array_constant_21,
	    FIX((SI_Long)12L)));
    frames_to_show = gensym_cons_1(temp_1,frames_to_show);
    if (SIMPLE_VECTOR_P(code_body_qm) && EQ(ISVREF(code_body_qm,
	    (SI_Long)0L),
	    Qg2_defstruct_structure_name_byte_code_body_g2_struct)) {
	wide_string_bv16 = 
		allocate_byte_vector_16(FIX(IFIX(Wide_string_list_maximum_length) 
		+ (SI_Long)3L));
	bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(wide_string_bv16));
	aref_arg_2 = bv16_length - (SI_Long)2L;
	aref_new_value = IFIX(Wide_string_list_maximum_length) & 
		(SI_Long)65535L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	aref_arg_2 = bv16_length - (SI_Long)1L;
	aref_new_value = (SI_Long)57344L | (SI_Long)0L;
	UBYTE_16_ISASET_1(wide_string_bv16,aref_arg_2,aref_new_value);
	UBYTE_16_ISASET_1(wide_string_bv16,
		IFIX(Wide_string_list_maximum_length),(SI_Long)0L);
	new_wide_string = wide_string_bv16;
	current_wide_string_list = gensym_cons_1(new_wide_string,Nil);
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
	  current_wide_string = new_wide_string;
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  write_byte_code_body(code_body_qm,ISVREF(code_body_qm,
			  (SI_Long)3L));
		  temp = Current_wide_string;
		  aref_arg_2_1 = Fill_pointer_for_current_wide_string;
		  bv16_length = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(temp));
		  aref_arg_2 = bv16_length - (SI_Long)2L;
		  aref_new_value = IFIX(aref_arg_2_1) & (SI_Long)65535L;
		  UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
		  aref_arg_2 = bv16_length - (SI_Long)1L;
		  aref_new_value = (SI_Long)57344L | IFIX(aref_arg_2_1) >> 
			   -  - (SI_Long)16L;
		  UBYTE_16_ISASET_1(temp,aref_arg_2,aref_new_value);
		  UBYTE_16_ISASET_1(temp,IFIX(aref_arg_2_1),(SI_Long)0L);
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	  gensym_list_of_wide_strings = Current_wide_string_list;
	POP_SPECIAL();
	string_1 = Nil;
	ab_loop_list__1 = gensym_list_of_wide_strings;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_3;
	string_1 = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	temp = make_lost_spaces_text_element(FIX((SI_Long)0L));
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(string_1));
	if (FIXNUM_LT(FIX(UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)2L) + ((UBYTE_16_ISAREF_1(string_1,length_1 - 
		(SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L)),
		Use_full_size_of_with_output_wide_string_cutoff)) {
	    short_string = copy_text_string(string_1);
	    reclaim_text_string(string_1);
	    temp = short_string;
	}
	else
	    temp = string_1;
	M_CAR(gensymed_symbol) = temp;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	ab_loopvar__2 = gensymed_symbol;
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_3;
      end_loop_3:
	temp_1 = ab_loopvar_;
	goto end_2;
	temp_1 = Qnil;
      end_2:;
	reclaim_gensym_list_1(gensym_list_of_wide_strings);
    }
    else
	temp_1 = 
		convert_text_string_to_text(copy_constant_wide_string_given_length(array_constant_22,
		FIX((SI_Long)12L)));
    temp_1 = make_description_box_with_text(temp_1);
    frames_to_show = gensym_cons_1(temp_1,frames_to_show);
    goto next_loop_2;
  end_loop_2:
    reclaim_gensym_tree_1(code_bodies_and_denotations_qm);
    return VALUES_1(frames_to_show);
    return VALUES_1(Qnil);
}

/* COLLECT-GENERIC-FORMULAS-FOR-VARIABLE */
Object collect_generic_formulas_for_variable(variable)
    Object variable;
{
    Object parent_entity_qm, slot_name, generic_formulas, found_formulas;
    Object class_1, class_description, ab_loop_list_, formula, ab_loop_list__1;
    Object temp;
    char temp_1;
    Object result;

    x_note_fn_call(214,132);
    result = get_kb_parent_information(variable);
    MVS_2(result,parent_entity_qm,slot_name);
    if (parent_entity_qm) {
	generic_formulas = 
		lookup_kb_specific_property_value(CONSP(slot_name) ? 
		M_CAR(M_CDR(M_CDR(slot_name))) : slot_name,
		Formulas_for_this_role_kbprop);
	found_formulas = Nil;
	class_1 = Nil;
	class_description = ISVREF(parent_entity_qm,(SI_Long)1L);
	ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	class_1 = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	formula = Nil;
	ab_loop_list__1 = generic_formulas;
      next_loop_1:
	if ( !TRUEP(ab_loop_list__1))
	    goto end_loop_1;
	formula = M_CAR(ab_loop_list__1);
	ab_loop_list__1 = M_CDR(ab_loop_list__1);
	temp = ISVREF(formula,(SI_Long)16L);
	temp = CAR(temp);
	if (EQ(class_1,SECOND(temp))) {
	    temp_1 =  !TRUEP(System_is_running) ?  
		    !TRUEP(System_has_paused) : TRUEP(Qnil);
	    if (temp_1);
	    else {
		temp = ISVREF(formula,(SI_Long)8L);
		temp_1 =  !TRUEP(CAR(temp)) ? (SI_Long)0L != 
			(IFIX(ISVREF(formula,(SI_Long)5L)) & (SI_Long)1L) 
			||  !TRUEP(Inside_breakpoint_p) && (SI_Long)0L != 
			(IFIX(ISVREF(formula,(SI_Long)4L)) & 
			(SI_Long)16777216L) &&  !((SI_Long)0L != 
			(IFIX(ISVREF(formula,(SI_Long)4L)) & 
			(SI_Long)8192L)) : TRUEP(Nil);
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1)
	    found_formulas = gensym_cons_1(formula,found_formulas);
	goto next_loop_1;
      end_loop_1:;
	goto next_loop;
      end_loop:
	return nreverse(found_formulas);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* RULES-IN-BACKWARD-LINK-LIST */
Object rules_in_backward_link_list(link_list)
    Object link_list;
{
    Object link_entry, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2;

    x_note_fn_call(214,133);
    link_entry = Nil;
    ab_loop_list_ = link_list;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    link_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    ab_loopvar__2 = gensym_cons_1(ISVREF(CAR(link_entry),(SI_Long)2L),Nil);
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

/* RULES-IN-FORWARD-LINK-LIST */
Object rules_in_forward_link_list(link_list)
    Object link_list;
{
    Object link_entry, ab_loop_list_, recipient, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, x2, gensymed_symbol, sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp;

    x_note_fn_call(214,134);
    link_entry = Nil;
    ab_loop_list_ = link_list;
    recipient = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    link_entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    recipient = ISVREF(CAR(link_entry),(SI_Long)2L);
    if (SIMPLE_VECTOR_P(recipient) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(recipient)) > (SI_Long)2L &&  
	    !EQ(ISVREF(recipient,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(recipient,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
    if (temp) {
	ab_loopvar__2 = gensym_cons_1(recipient,Nil);
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

/* COLLECT-ALL-RULES-FOR-FORWARD-CHAINING */
Object collect_all_rules_for_forward_chaining(variable)
    Object variable;
{
    Object variable_name_or_names_qm, new_cons, gensymed_symbol;
    Object variable_name_cons_qm, parent_stack, data_type, result_1, rule_list;
    Object result;

    x_note_fn_call(214,135);
    variable_name_or_names_qm = 
	    get_lookup_slot_value_given_default(variable,
	    Qname_or_names_for_frame,Nil);
    if (variable_name_or_names_qm && SYMBOLP(variable_name_or_names_qm)) {
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol = new_cons;
	}
	else
	    gensymed_symbol = Nil;
	if ( !TRUEP(gensymed_symbol))
	    gensymed_symbol = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol) = variable_name_or_names_qm;
	M_CDR(gensymed_symbol) = Nil;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	variable_name_or_names_qm = gensymed_symbol;
	variable_name_cons_qm = variable_name_or_names_qm;
    }
    else
	variable_name_cons_qm = Nil;
    parent_stack = make_parent_stack(variable);
    data_type = type_specification_of_variable_or_parameter_value(variable);
    if (EQ(data_type,Qtruth_value))
	result = collect_all_rules_for_logical_forward_chaining(variable,
		variable_name_or_names_qm,parent_stack);
    else if (EQ(data_type,Qsymbol))
	result = collect_all_rules_for_symbolic_forward_chaining(variable,
		parent_stack,variable_name_or_names_qm);
    else
	result = collect_all_rules_for_general_forward_chaining(variable,
		variable_name_or_names_qm,parent_stack);
    MVS_2(result,result_1,rule_list);
    reclaim_parent_stack(parent_stack);
    if (variable_name_cons_qm)
	reclaim_gensym_cons_1(variable_name_cons_qm);
    return VALUES_2(result_1,rule_list);
}

static Object list_constant_17;    /* # */

static Object string_constant_137;  /* "true" */

static Object string_constant_138;  /* "false" */

static Object string_constant_139;  /* "any new value" */

static Object string_constant_140;  /* "These rules are forward chained to when ~a is received." */

/* COLLECT-ALL-RULES-FOR-LOGICAL-FORWARD-CHAINING */
Object collect_all_rules_for_logical_forward_chaining(variable,
	    variable_names,parent_stack)
    Object variable, variable_names, parent_stack;
{
    Object truth_chaining, falsity_chaining, either_chaining;
    Object links_and_objects, descriptive_elements_to_show, rule_list;
    Object truth_entry, ab_loop_list_, falsity_entry, ab_loop_list__1;
    Object logical_case, links_and_object_list, descriptive_text_string;
    Object descriptive_elements_for_chaining, temp, temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,136);
    truth_chaining = Nil;
    falsity_chaining = Nil;
    either_chaining = Nil;
    links_and_objects = Nil;
    descriptive_elements_to_show = Nil;
    rule_list = Nil;
    PUSH_SPECIAL(Links_and_objects,links_and_objects,0);
      collect_rules_for_logical_forward_chaining(variable,
	      FIX((SI_Long)1000L),(SI_Long)0L != (IFIX(ISVREF(variable,
	      (SI_Long)4L)) & (SI_Long)2L) ? T : Nil,parent_stack,
	      variable_names);
      truth_chaining = Links_and_objects;
      Links_and_objects = Nil;
      collect_rules_for_logical_forward_chaining(variable,
	      FIX((SI_Long)-1000L),(SI_Long)0L != (IFIX(ISVREF(variable,
	      (SI_Long)4L)) & (SI_Long)2L) ? T : Nil,parent_stack,
	      variable_names);
      falsity_chaining = Links_and_objects;
      truth_entry = Nil;
      ab_loop_list_ = truth_chaining;
    next_loop:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop;
      truth_entry = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      falsity_entry = Nil;
      ab_loop_list__1 = falsity_chaining;
    next_loop_1:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_1;
      falsity_entry = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      if (EQUAL(truth_entry,falsity_entry)) {
	  truth_chaining = delete_gensym_element_1(truth_entry,truth_chaining);
	  either_chaining = gensym_cons_1(truth_entry,either_chaining);
	  falsity_chaining = delete_gensym_element_1(falsity_entry,
		  falsity_chaining);
	  reclaim_gensym_cons_1(falsity_entry);
	  goto end_loop_1;
      }
      goto next_loop_1;
    end_loop_1:;
      goto next_loop;
    end_loop:;
      logical_case = Nil;
      ab_loop_list_ = list_constant_17;
      links_and_object_list = Nil;
      descriptive_text_string = Nil;
      descriptive_elements_for_chaining = Nil;
    next_loop_2:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_2;
      logical_case = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      if (EQ(logical_case,Qtrue))
	  links_and_object_list = truth_chaining;
      else if (EQ(logical_case,Qfalse))
	  links_and_object_list = falsity_chaining;
      else
	  links_and_object_list = either_chaining;
      if (EQ(logical_case,Qtrue))
	  temp = string_constant_137;
      else if (EQ(logical_case,Qfalse))
	  temp = string_constant_138;
      else
	  temp = string_constant_139;
      descriptive_text_string = tformat_text_string(2,string_constant_140,
	      temp);
      descriptive_elements_for_chaining = 
	      short_representations_of_forward_invocations(links_and_object_list);
      temp_1 = descriptive_elements_for_chaining;
      temp = make_description_box(descriptive_text_string);
      descriptive_elements_to_show = nconc2(temp_1,gensym_cons_1(temp,
	      descriptive_elements_to_show));
      goto next_loop_2;
    end_loop_2:;
      temp_1 = rules_in_forward_link_list(either_chaining);
      temp = rules_in_forward_link_list(falsity_chaining);
      rule_list = nconc2(temp_1,nconc2(temp,
	      rules_in_forward_link_list(truth_chaining)));
      reclaim_gensym_tree_1(either_chaining);
      reclaim_gensym_tree_1(falsity_chaining);
      reclaim_gensym_tree_1(truth_chaining);
      result = VALUES_2(descriptive_elements_to_show,rule_list);
    POP_SPECIAL();
    return result;
}

static Object string_constant_141;  /* "These rules are forward chained to when a value is ~
				     *                            received."
				     */

/* COLLECT-ALL-RULES-FOR-GENERAL-FORWARD-CHAINING */
Object collect_all_rules_for_general_forward_chaining(variable,
	    variable_names,parent_stack)
    Object variable, variable_names, parent_stack;
{
    Object links_and_objects, descriptive_elements_to_show, rule_list;
    Object short_representations_of_chaining, descriptive_text_string, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,137);
    links_and_objects = Nil;
    descriptive_elements_to_show = Nil;
    rule_list = Nil;
    PUSH_SPECIAL(Links_and_objects,links_and_objects,0);
      collect_rules_for_general_forward_chaining(variable,(SI_Long)0L != 
	      (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)2L) ? T : Nil,
	      parent_stack,variable_names);
      short_representations_of_chaining = 
	      short_representations_of_forward_invocations(Links_and_objects);
      if (short_representations_of_chaining) {
	  descriptive_text_string = tformat_text_string(1,string_constant_141);
	  temp = make_description_box(descriptive_text_string);
	  descriptive_elements_to_show = gensym_cons_1(temp,
		  descriptive_elements_to_show);
	  descriptive_elements_to_show = 
		  nconc2(short_representations_of_chaining,
		  descriptive_elements_to_show);
      }
      rule_list = rules_in_forward_link_list(Links_and_objects);
      reclaim_gensym_tree_1(Links_and_objects);
      result = VALUES_2(descriptive_elements_to_show,rule_list);
    POP_SPECIAL();
    return result;
}

static Object list_constant_18;    /* # */

static Object string_constant_142;  /* "These rules are forward chained to when ~
				     *                                    the value ~a is received."
				     */

static Object string_constant_143;  /* "These rules are forward chained to when any ~
				     *                                    value other than ~a is received."
				     */

static Object string_constant_144;  /* "These rules are forward chained to when any ~
				     *                                new value is received."
				     */

/* COLLECT-ALL-RULES-FOR-SYMBOLIC-FORWARD-CHAINING */
Object collect_all_rules_for_symbolic_forward_chaining(variable,
	    parent_stack,variable_name_or_names_qm)
    Object variable, parent_stack, variable_name_or_names_qm;
{
    Object possible_values_qm, parent_stack_entry, links_and_objects;
    Object rule_list, gensymed_symbol, name_for_parent_qm, ab_loop_list_;
    Object link_1, ab_loop_list__1, symbolic_value, sense, temp, new_cons;
    Object gensymed_symbol_1, temp_2, link_symbolic_value, link_sense;
    Object parent_frame_qm, name_for_variable, descriptive_elements_to_show;
    Object any_value_chaining, value_dependent_chaining, link_and_object, x;
    Object x2, sub_class_bit_vector, value, entry_for_value, value_entry;
    Object match_chaining, mismatch_chaining, descriptive_text_string;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_2, gensymed_symbol_3, gensymed_symbol_4;
    char temp_1;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,138);
    possible_values_qm = Nil;
    parent_stack_entry = CAR(parent_stack);
    links_and_objects = Nil;
    rule_list = Nil;
    PUSH_SPECIAL(Links_and_objects,links_and_objects,0);
      if (parent_stack_entry) {
	  gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	  possible_values_qm = 
		  value_set_given_attribute_and_class(CONSP(gensymed_symbol) 
		  ? M_CAR(gensymed_symbol) : gensymed_symbol,
		  ISVREF(ISVREF(M_CAR(parent_stack_entry),(SI_Long)1L),
		  (SI_Long)1L));
	  name_for_parent_qm = Nil;
	  ab_loop_list_ = M_CAR(M_CDR(M_CDR(parent_stack_entry)));
	next_loop:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop;
	  name_for_parent_qm = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  link_1 = Nil;
	  ab_loop_list__1 = 
		  lookup_kb_specific_property_value(name_for_parent_qm,
		  Forward_chaining_list_kbprop);
	  symbolic_value = Nil;
	  sense = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list__1))
	      goto end_loop_1;
	  link_1 = M_CAR(ab_loop_list__1);
	  ab_loop_list__1 = M_CDR(ab_loop_list__1);
	  symbolic_value = ISVREF(link_1,(SI_Long)6L);
	  sense = ISVREF(link_1,(SI_Long)7L);
	  if (symbolic_sense_matches_for_all_p(possible_values_qm,
		  symbolic_value,sense,(SI_Long)0L != 
		  (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)2L) ? T : 
		  Nil)) {
	      temp = ISVREF(link_1,(SI_Long)3L);
	      temp_1 = SYMBOLP(temp);
	  }
	  else
	      temp_1 = TRUEP(Nil);
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
	      new_cons = Available_gensym_conses;
	      if (new_cons) {
		  Available_gensym_conses = M_CDR(new_cons);
		  gensymed_symbol_1 = new_cons;
	      }
	      else
		  gensymed_symbol_1 = Nil;
	      if ( !TRUEP(gensymed_symbol_1))
		  gensymed_symbol_1 = replenish_gensym_cons_pool();
	      M_CAR(gensymed_symbol_1) = link_1;
	      M_CDR(gensymed_symbol_1) = Nil;
	      inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	      M_CAR(gensymed_symbol) = gensymed_symbol_1;
	      temp_2 = Links_and_objects;
	      M_CDR(gensymed_symbol) = temp_2;
	      inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	      Links_and_objects = gensymed_symbol;
	  }
	  goto next_loop_1;
	end_loop_1:;
	  goto next_loop;
	end_loop:;
	  link_1 = Nil;
	  gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	  ab_loop_list_ = 
		  lookup_kb_specific_property_value(CONSP(gensymed_symbol) 
		  ? M_CAR(gensymed_symbol) : gensymed_symbol,
		  Forward_chaining_list_kbprop);
	  link_symbolic_value = Nil;
	  link_sense = Nil;
	next_loop_2:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_2;
	  link_1 = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  link_symbolic_value = ISVREF(link_1,(SI_Long)6L);
	  link_sense = ISVREF(link_1,(SI_Long)7L);
	  if (symbolic_sense_matches_for_all_p(possible_values_qm,
		  link_symbolic_value,link_sense,(SI_Long)0L != 
		  (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)2L) ? T : 
		  Nil)) {
	      parent_frame_qm = find_referenced_parent(parent_stack,
		      ISVREF(link_1,(SI_Long)3L));
	      if (parent_frame_qm) {
		  new_cons = Available_gensym_conses;
		  if (new_cons) {
		      Available_gensym_conses = M_CDR(new_cons);
		      gensymed_symbol = new_cons;
		  }
		  else
		      gensymed_symbol = Nil;
		  if ( !TRUEP(gensymed_symbol))
		      gensymed_symbol = replenish_gensym_cons_pool();
		  new_cons = Available_gensym_conses;
		  if (new_cons) {
		      Available_gensym_conses = M_CDR(new_cons);
		      gensymed_symbol_1 = new_cons;
		  }
		  else
		      gensymed_symbol_1 = Nil;
		  if ( !TRUEP(gensymed_symbol_1))
		      gensymed_symbol_1 = replenish_gensym_cons_pool();
		  M_CAR(gensymed_symbol_1) = link_1;
		  M_CDR(gensymed_symbol_1) = parent_frame_qm;
		  inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		  M_CAR(gensymed_symbol) = gensymed_symbol_1;
		  temp_2 = Links_and_objects;
		  M_CDR(gensymed_symbol) = temp_2;
		  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
		  Links_and_objects = gensymed_symbol;
	      }
	  }
	  goto next_loop_2;
	end_loop_2:;
	  collect_all_forward_chaining_for_symbolic_class_references(M_CAR(parent_stack_entry),
		  possible_values_qm,T,(SI_Long)0L != 
		  (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)2L) ? T : 
		  Nil);
	  if (CDR(parent_stack)) {
	      parent_stack_entry = SECOND(parent_stack);
	      link_1 = Nil;
	      gensymed_symbol = M_CAR(M_CDR(parent_stack_entry));
	      ab_loop_list_ = 
		      lookup_kb_specific_property_value(CONSP(gensymed_symbol) 
		      ? M_CAR(gensymed_symbol) : gensymed_symbol,
		      Forward_chaining_list_kbprop);
	      link_symbolic_value = Nil;
	      link_sense = Nil;
	    next_loop_3:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_3;
	      link_1 = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      link_symbolic_value = ISVREF(link_1,(SI_Long)6L);
	      link_sense = ISVREF(link_1,(SI_Long)7L);
	      if (symbolic_sense_matches_for_all_p(possible_values_qm,
		      link_symbolic_value,link_sense,(SI_Long)0L != 
		      (IFIX(ISVREF(variable,(SI_Long)4L)) & (SI_Long)2L) ? 
		      T : Nil)) {
		  parent_frame_qm = 
			  find_referenced_parent(CDR(parent_stack),
			  ISVREF(link_1,(SI_Long)3L));
		  if (parent_frame_qm) {
		      new_cons = Available_gensym_conses;
		      if (new_cons) {
			  Available_gensym_conses = M_CDR(new_cons);
			  gensymed_symbol = new_cons;
		      }
		      else
			  gensymed_symbol = Nil;
		      if ( !TRUEP(gensymed_symbol))
			  gensymed_symbol = replenish_gensym_cons_pool();
		      new_cons = Available_gensym_conses;
		      if (new_cons) {
			  Available_gensym_conses = M_CDR(new_cons);
			  gensymed_symbol_1 = new_cons;
		      }
		      else
			  gensymed_symbol_1 = Nil;
		      if ( !TRUEP(gensymed_symbol_1))
			  gensymed_symbol_1 = replenish_gensym_cons_pool();
		      M_CAR(gensymed_symbol_1) = link_1;
		      M_CDR(gensymed_symbol_1) = parent_frame_qm;
		      inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
		      M_CAR(gensymed_symbol) = gensymed_symbol_1;
		      temp_2 = Links_and_objects;
		      M_CDR(gensymed_symbol) = temp_2;
		      inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
		      Links_and_objects = gensymed_symbol;
		  }
	      }
	      goto next_loop_3;
	    end_loop_3:;
	  }
      }
      name_for_variable = Nil;
      ab_loop_list_ = variable_name_or_names_qm;
    next_loop_4:
      if ( !TRUEP(ab_loop_list_))
	  goto end_loop_4;
      name_for_variable = M_CAR(ab_loop_list_);
      ab_loop_list_ = M_CDR(ab_loop_list_);
      link_1 = Nil;
      ab_loop_list__1 = 
	      lookup_kb_specific_property_value(name_for_variable,
	      Forward_chaining_list_kbprop);
      symbolic_value = Nil;
      sense = Nil;
    next_loop_5:
      if ( !TRUEP(ab_loop_list__1))
	  goto end_loop_5;
      link_1 = M_CAR(ab_loop_list__1);
      ab_loop_list__1 = M_CDR(ab_loop_list__1);
      symbolic_value = ISVREF(link_1,(SI_Long)6L);
      sense = ISVREF(link_1,(SI_Long)7L);
      if (symbolic_sense_matches_for_all_p(possible_values_qm,
	      symbolic_value,sense,(SI_Long)0L != (IFIX(ISVREF(variable,
	      (SI_Long)4L)) & (SI_Long)2L) ? T : Nil)) {
	  temp = ISVREF(link_1,(SI_Long)3L);
	  temp_1 = SYMBOLP(temp);
      }
      else
	  temp_1 = TRUEP(Nil);
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
	  new_cons = Available_gensym_conses;
	  if (new_cons) {
	      Available_gensym_conses = M_CDR(new_cons);
	      gensymed_symbol_1 = new_cons;
	  }
	  else
	      gensymed_symbol_1 = Nil;
	  if ( !TRUEP(gensymed_symbol_1))
	      gensymed_symbol_1 = replenish_gensym_cons_pool();
	  M_CAR(gensymed_symbol_1) = link_1;
	  M_CDR(gensymed_symbol_1) = Nil;
	  inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	  M_CAR(gensymed_symbol) = gensymed_symbol_1;
	  temp_2 = Links_and_objects;
	  M_CDR(gensymed_symbol) = temp_2;
	  inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	  Links_and_objects = gensymed_symbol;
      }
      goto next_loop_5;
    end_loop_5:;
      goto next_loop_4;
    end_loop_4:;
      collect_all_forward_chaining_for_symbolic_class_references(variable,
	      possible_values_qm,Nil,(SI_Long)0L != (IFIX(ISVREF(variable,
	      (SI_Long)4L)) & (SI_Long)2L) ? T : Nil);
      descriptive_elements_to_show = Nil;
      if (Links_and_objects) {
	  any_value_chaining = Nil;
	  value_dependent_chaining = Nil;
	  link_and_object = Nil;
	  ab_loop_list_ = Links_and_objects;
	  sense = Nil;
	next_loop_6:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_6;
	  link_and_object = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  sense = ISVREF(CAR(link_and_object),(SI_Long)7L);
	  x = ISVREF(CAR(link_and_object),(SI_Long)2L);
	  if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		  (SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		  Qavailable_frame_vector)) {
	      x2 = ISVREF(x,(SI_Long)1L);
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
		      IFIX(ISVREF(Rule_class_description,(SI_Long)18L));
	      sub_class_vector_index = superior_class_bit_number >>  -  - 
		      (SI_Long)3L;
	      if (sub_class_vector_index < 
		      IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) {
		  gensymed_symbol_2 = 
			  UBYTE_8_ISAREF_1(sub_class_bit_vector,
			  sub_class_vector_index);
		  gensymed_symbol_3 = (SI_Long)1L;
		  gensymed_symbol_4 = superior_class_bit_number & (SI_Long)7L;
		  gensymed_symbol_3 = gensymed_symbol_3 << gensymed_symbol_4;
		  gensymed_symbol_2 = gensymed_symbol_2 & gensymed_symbol_3;
		  temp_1 = (SI_Long)0L < gensymed_symbol_2;
	      }
	      else
		  temp_1 = TRUEP(Nil);
	  }
	  else
	      temp_1 = TRUEP(Nil);
	  if (temp_1) {
	      if (memq_function(sense,list_constant_18))
		  any_value_chaining = gensym_cons_1(link_and_object,
			  any_value_chaining);
	      else {
		  value = ISVREF(CAR(link_and_object),(SI_Long)6L);
		  entry_for_value = assq_function(value,
			  value_dependent_chaining);
		  if ( !TRUEP(entry_for_value)) {
		      entry_for_value = gensym_list_3(value,Nil,Nil);
		      value_dependent_chaining = 
			      gensym_cons_1(entry_for_value,
			      value_dependent_chaining);
		  }
		  if (EQ(sense,T)) {
		      temp_2 = gensym_cons_1(link_and_object,
			      SECOND(entry_for_value));
		      M_SECOND(entry_for_value) = temp_2;
		  }
		  else {
		      temp_2 = gensym_cons_1(link_and_object,
			      THIRD(entry_for_value));
		      M_THIRD(entry_for_value) = temp_2;
		  }
	      }
	  }
	  goto next_loop_6;
	end_loop_6:;
	  if (value_dependent_chaining) {
	      value_entry = Nil;
	      ab_loop_list_ = value_dependent_chaining;
	      value = Nil;
	      match_chaining = Nil;
	      mismatch_chaining = Nil;
	    next_loop_7:
	      if ( !TRUEP(ab_loop_list_))
		  goto end_loop_7;
	      value_entry = M_CAR(ab_loop_list_);
	      ab_loop_list_ = M_CDR(ab_loop_list_);
	      value = FIRST(value_entry);
	      match_chaining = SECOND(value_entry);
	      mismatch_chaining = THIRD(value_entry);
	      if (match_chaining) {
		  descriptive_text_string = tformat_text_string(2,
			  string_constant_142,value);
		  temp = make_description_box(descriptive_text_string);
		  descriptive_elements_to_show = gensym_cons_1(temp,
			  descriptive_elements_to_show);
		  temp = 
			  short_representations_of_forward_invocations(match_chaining);
		  descriptive_elements_to_show = nconc2(temp,
			  descriptive_elements_to_show);
		  reclaim_gensym_list_1(match_chaining);
	      }
	      if (mismatch_chaining) {
		  descriptive_text_string = tformat_text_string(2,
			  string_constant_143,value);
		  temp = make_description_box(descriptive_text_string);
		  descriptive_elements_to_show = gensym_cons_1(temp,
			  descriptive_elements_to_show);
		  temp = 
			  short_representations_of_forward_invocations(mismatch_chaining);
		  descriptive_elements_to_show = nconc2(temp,
			  descriptive_elements_to_show);
		  reclaim_gensym_list_1(mismatch_chaining);
	      }
	      reclaim_gensym_list_1(value_entry);
	      goto next_loop_7;
	    end_loop_7:;
	      reclaim_gensym_list_1(value_dependent_chaining);
	  }
	  if (any_value_chaining) {
	      descriptive_text_string = tformat_text_string(1,
		      string_constant_144);
	      temp = make_description_box(descriptive_text_string);
	      descriptive_elements_to_show = gensym_cons_1(temp,
		      descriptive_elements_to_show);
	      temp = 
		      short_representations_of_forward_invocations(any_value_chaining);
	      descriptive_elements_to_show = nconc2(temp,
		      descriptive_elements_to_show);
	      reclaim_gensym_list_1(any_value_chaining);
	  }
	  rule_list = rules_in_forward_link_list(Links_and_objects);
	  reclaim_gensym_tree_1(Links_and_objects);
      }
      result = VALUES_2(descriptive_elements_to_show,rule_list);
    POP_SPECIAL();
    return result;
}

static Object Qreceives_a_value;   /* receives-a-value */

static Object Qeither;             /* either */

/* SYMBOLIC-SENSE-MATCHES-FOR-ALL-P */
Object symbolic_sense_matches_for_all_p(possible_values,stored_value,sense,
	    chaining_as_well_as_events_qm)
    Object possible_values, stored_value, sense, chaining_as_well_as_events_qm;
{
    Object temp;

    x_note_fn_call(214,139);
    temp = EQ(sense,Qreceives_a_value) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else if (chaining_as_well_as_events_qm) {
	temp = EQ(sense,Qeither) ? T : Nil;
	if (temp)
	    return VALUES_1(temp);
	else if (EQ(sense,Nil) || EQ(sense,T)) {
	    temp =  !TRUEP(possible_values) ? T : Nil;
	    if (temp)
		return VALUES_1(temp);
	    else
		return memq_function(stored_value,possible_values);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* COLLECT-ALL-FORWARD-CHAINING-FOR-SYMBOLIC-CLASS-REFERENCES */
Object collect_all_forward_chaining_for_symbolic_class_references(object,
	    possible_values_qm,stored_symbol_required_qm,
	    chaining_as_well_as_events_qm)
    Object object, possible_values_qm, stored_symbol_required_qm;
    Object chaining_as_well_as_events_qm;
{
    Object class_1, class_description, ab_loop_list_, link_1, ab_loop_list__1;
    Object symbolic_value, sense, designation, temp, new_cons, gensymed_symbol;
    Object gensymed_symbol_1, cdr_new_value;
    char temp_1;

    x_note_fn_call(214,140);
    class_1 = Nil;
    class_description = ISVREF(object,(SI_Long)1L);
    ab_loop_list_ = ISVREF(class_description,(SI_Long)2L);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    class_1 = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = Nil;
    ab_loop_list__1 = lookup_kb_specific_property_value(class_1,
	    Forward_chaining_list_kbprop);
    symbolic_value = Nil;
    sense = Nil;
    designation = Nil;
  next_loop_1:
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop_1;
    link_1 = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    symbolic_value = ISVREF(link_1,(SI_Long)6L);
    sense = ISVREF(link_1,(SI_Long)7L);
    designation = ISVREF(link_1,(SI_Long)3L);
    if (( !TRUEP(stored_symbol_required_qm) || symbolic_value) && 
	    symbolic_sense_matches_for_all_p(possible_values_qm,
	    symbolic_value,sense,chaining_as_well_as_events_qm) &&  
	    !SYMBOLP(designation)) {
	if (domain_of_designation(designation)) {
	    temp = role_of_designation(designation);
	    temp_1 = SYMBOLP(temp);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_1 =  !temp_1;
    }
    else
	temp_1 = TRUEP(Nil);
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
	new_cons = Available_gensym_conses;
	if (new_cons) {
	    Available_gensym_conses = M_CDR(new_cons);
	    gensymed_symbol_1 = new_cons;
	}
	else
	    gensymed_symbol_1 = Nil;
	if ( !TRUEP(gensymed_symbol_1))
	    gensymed_symbol_1 = replenish_gensym_cons_pool();
	M_CAR(gensymed_symbol_1) = link_1;
	M_CDR(gensymed_symbol_1) = object;
	inline_note_allocate_cons(gensymed_symbol_1,Qab_gensym);
	M_CAR(gensymed_symbol) = gensymed_symbol_1;
	cdr_new_value = Links_and_objects;
	M_CDR(gensymed_symbol) = cdr_new_value;
	inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
	Links_and_objects = gensymed_symbol;
    }
    goto next_loop_1;
  end_loop_1:;
    if (EQ(class_1,Qitem))
	goto end_loop;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

static Object Qrule;               /* rule */

static Object string_constant_145;  /* "The following rules mention the variable, though they are not ~
				     *                          invoked via any chaining mechanisms."
				     */

/* COLLECT-ALL-MENTIONING-RULES */
Object collect_all_mentioning_rules(entity,rules_to_exclude)
    Object entity, rules_to_exclude;
{
    Object mentioning_rules, descriptive_elements_to_show, parent_stack_qm;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, rule;
    Object descriptive_text_string, temp_1, ab_loop_list_;
    char temp;
    Declare_special(1);

    x_note_fn_call(214,141);
    mentioning_rules = Nil;
    descriptive_elements_to_show = Nil;
    parent_stack_qm = make_parent_stack(entity);
    if (parent_stack_qm) {
	scope_conses = Scope_conses;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	rule = Nil;
	PUSH_SPECIAL(Scope_conses,scope_conses,0);
	  ab_loopvar_ = collect_subclasses(Qrule);
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
	  rule = ab_loopvar__1;
	  ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
	  if ( !TRUEP(memq_function(rule,rules_to_exclude))) {
	      if ( !TRUEP(embedded_rule_p(rule)) && 
		      rule_mentions_entity_p(rule,entity,parent_stack_qm))
		  mentioning_rules = gensym_cons_1(rule,mentioning_rules);
	  }
	  goto next_loop;
	end_loop_1:;
	POP_SPECIAL();
	reclaim_parent_stack(parent_stack_qm);
    }
    if (mentioning_rules) {
	descriptive_text_string = tformat_text_string(1,string_constant_145);
	temp_1 = make_description_box(descriptive_text_string);
	descriptive_elements_to_show = gensym_cons_1(temp_1,
		descriptive_elements_to_show);
	rule = Nil;
	ab_loop_list_ = mentioning_rules;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	rule = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp_1 = make_short_representation(3,rule,Nil,Qsmall);
	descriptive_elements_to_show = gensym_cons_1(temp_1,
		descriptive_elements_to_show);
	goto next_loop_2;
      end_loop_2:;
	reclaim_gensym_list_1(mentioning_rules);
    }
    return VALUES_1(descriptive_elements_to_show);
}

static Object Qfor;                /* for */

/* RULE-MENTIONS-ENTITY-P */
Object rule_mentions_entity_p(rule,entity,parent_stack)
    Object rule, entity, parent_stack;
{
    Object translation, designations_in_rule, designation_entry, ab_loop_list_;
    Object designation, temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,142);
    translation = get_new_translation_of_text_slot(ISVREF(rule,(SI_Long)16L));
    if (translation) {
	designations_in_rule = Nil;
	PUSH_SPECIAL(Designations_in_rule,designations_in_rule,0);
	next_loop:
	  if ( !(CONSP(translation) && EQ(FIRST(translation),Qfor)))
	      goto end_loop;
	  lookup_previous_reference_and_note_designation(SECOND(translation));
	  translation = THIRD(translation);
	  goto next_loop;
	end_loop:
	  note_designations_in_expression_using_environment(SECOND(translation));
	  note_designations_in_consequent_using_environment(THIRD(translation));
	  designation_entry = Nil;
	  ab_loop_list_ = Designations_in_rule;
	  designation = Nil;
	next_loop_1:
	  if ( !TRUEP(ab_loop_list_))
	      goto end_loop_1;
	  designation_entry = M_CAR(ab_loop_list_);
	  ab_loop_list_ = M_CDR(ab_loop_list_);
	  designation = CDR(designation_entry);
	  if (picky_designation_could_denote_entity(designation,entity,
		  parent_stack)) {
	      temp = T;
	      goto end_1;
	  }
	  goto next_loop_1;
	end_loop_1:
	  temp = Qnil;
	end_1:;
	  reclaim_gensym_tree_1(Designations_in_rule);
	  result = VALUES_1(temp);
	POP_SPECIAL();
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* PICKY-DESIGNATION-COULD-DENOTE-ENTITY */
Object picky_designation_could_denote_entity(designation,entity,parent_stack)
    Object designation, entity, parent_stack;
{
    Object role, name_or_names, gensymed_symbol, sub_class_bit_vector;
    Object simple_designation, temp, class_qm;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;

    x_note_fn_call(214,143);
    role = Nil;
    if (SYMBOLP(designation)) {
	name_or_names = get_lookup_slot_value_given_default(entity,
		Qname_or_names_for_frame,Nil);
	if (CONSP(name_or_names))
	    return memq_function(designation,name_or_names);
	else
	    return VALUES_1(EQ(designation,name_or_names) ? T : Nil);
    }
    else {
	role = simple_role_of_role(role_of_designation(designation));
	if (SYMBOLP(role)) {
	    if ( !TRUEP(domain_of_designation(designation))) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(role,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(entity,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? 
				T : Nil);
		    }
		    else
			return VALUES_1(Nil);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else {
		simple_designation = 
			simple_installation_designation(designation);
		temp =  ! !TRUEP(find_referenced_parent(parent_stack,
			simple_designation)) ? T : Nil;
		reclaim_gensym_tree_1(simple_designation);
		return VALUES_1(temp);
	    }
	}
	else {
	    class_qm = atomic_class_element_of_role(role);
	    if (class_qm) {
		gensymed_symbol = 
			lookup_global_or_kb_specific_property_value(class_qm,
			Class_description_gkbprop);
		if (gensymed_symbol) {
		    sub_class_bit_vector = ISVREF(ISVREF(entity,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(gensymed_symbol,(SI_Long)18L));
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
			return VALUES_1((SI_Long)0L < gensymed_symbol_1 ? 
				T : Nil);
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
    }
}

static Object Qis;                 /* is */

static Object Qis_not;             /* is-not */

static Object string_constant_146;  /* "More than one attribute of class ~a has ~a as a possible ~
				     *                   value.  The implied attributes feature cannot be used when ~
				     *                   this is the case.  Attributes found so far are ~a and ~a."
				     */

/* NOTE-DESIGNATIONS-IN-EXPRESSION-USING-ENVIRONMENT */
Object note_designations_in_expression_using_environment(expression)
    Object expression;
{
    Object operator_1, designation, class_qm, temp, symbolic_value;
    Object gensymed_symbol, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_4, ab_loop_list_;
    Object ab_loop_desetq_, attribute_qm, new_designation, template_qm;
    Object sub_expression;

    x_note_fn_call(214,144);
    if ( !TRUEP(expression))
	return VALUES_1(Nil);
    else if (ATOM(expression) ? expression && SYMBOLP(expression) : 
	    TRUEP(designation_operator_or_giver_of_value_p(CAR(expression))))
	return lookup_previous_reference_and_note_designation(expression);
    else if (CONSP(expression)) {
	operator_1 = FIRST(expression);
	if (SYMBOLP(operator_1)) {
	    if (EQ(operator_1,Qis) || EQ(operator_1,Qis_not)) {
		designation = 
			lookup_previous_reference_and_note_designation(SECOND(expression));
		class_qm = class_of_designation_result(designation);
		temp = THIRD(expression);
		symbolic_value = SECOND(temp);
		if (class_qm) {
		    gensymed_symbol = class_qm;
		    gensymed_symbol_1 = symbolic_value;
		    gensymed_symbol = 
			    lookup_global_or_kb_specific_property_value(gensymed_symbol,
			    Class_description_gkbprop);
		    gensymed_symbol = gensymed_symbol ? 
			    ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
		    gensymed_symbol_2 = Nil;
		    gensymed_symbol_3 = Nil;
		    gensymed_symbol_4 = Nil;
		    ab_loop_list_ = 
			    lookup_kb_specific_property_value(gensymed_symbol_1,
			    Attribute_value_kbprop);
		    ab_loop_desetq_ = Nil;
		  next_loop:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop;
		    ab_loop_desetq_ = M_CAR(ab_loop_list_);
		    gensymed_symbol_3 = CAR(ab_loop_desetq_);
		    gensymed_symbol_4 = CDR(ab_loop_desetq_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    if (memq_function(gensymed_symbol_3,gensymed_symbol)) {
			if (gensymed_symbol_2) {
			    Suppress_warning_message_header_qm = T;
			    if ((SI_Long)1L <= IFIX(Warning_message_level))
				give_warning_1(6,FIX((SI_Long)1L),
					string_constant_146,
					gensymed_symbol_3,
					gensymed_symbol_1,
					gensymed_symbol_2,gensymed_symbol_4);
			    Suppress_warning_message_header_qm = Nil;
			    attribute_qm = Nil;
			    goto end_1;
			}
			else
			    gensymed_symbol_2 = gensymed_symbol_4;
		    }
		    goto next_loop;
		  end_loop:
		    attribute_qm = gensymed_symbol_2;
		    goto end_1;
		    attribute_qm = Qnil;
		  end_1:;
		}
		else
		    attribute_qm = Nil;
		if (attribute_qm) {
		    new_designation = gensym_list_3(Qthe,attribute_qm,
			    designation);
		    lookup_previous_reference_and_note_designation(new_designation);
		    return reclaim_gensym_list_1(new_designation);
		}
		else
		    return VALUES_1(Nil);
	    }
	    else {
		template_qm = lookup_function_template(operator_1);
		if ( !TRUEP(template_qm)) {
		    sub_expression = Nil;
		    ab_loop_list_ = CDR(expression);
		  next_loop_1:
		    if ( !TRUEP(ab_loop_list_))
			goto end_loop_1;
		    sub_expression = M_CAR(ab_loop_list_);
		    ab_loop_list_ = M_CDR(ab_loop_list_);
		    note_designations_in_expression_using_environment(sub_expression);
		    goto next_loop_1;
		  end_loop_1:
		    return VALUES_1(Qnil);
		}
		else
		    return note_designations_in_expression_given_template_using_environment(expression,
			    template_qm);
	    }
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Qnil);
}

static Object Qexpression;         /* expression */

static Object Qdesignation;        /* designation */

static Object Qscope;              /* scope */

static Object Qother;              /* other */

/* NOTE-DESIGNATIONS-IN-EXPRESSION-GIVEN-TEMPLATE-USING-ENVIRONMENT */
Object note_designations_in_expression_given_template_using_environment(expression,
	    template_1)
    Object expression, template_1;
{
    Object argument, ab_loop_list_, argument_type, ab_loop_list__1;
    Object designation;

    x_note_fn_call(214,145);
    argument = Nil;
    ab_loop_list_ = CDR(expression);
    argument_type = Nil;
    ab_loop_list__1 = CDR(template_1);
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    argument = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if ( !TRUEP(ab_loop_list__1))
	goto end_loop;
    argument_type = M_CAR(ab_loop_list__1);
    ab_loop_list__1 = M_CDR(ab_loop_list__1);
    if (EQ(argument_type,Qexpression))
	note_designations_in_expression_using_environment(argument);
    else if (EQ(argument_type,Qdesignation))
	lookup_previous_reference_and_note_designation(argument);
    else if (EQ(argument_type,Qscope)) {
	designation = gensym_cons_1(Qany,
		copy_tree_using_gensym_conses_1(argument));
	lookup_previous_reference_and_note_designation(designation);
	reclaim_gensym_tree_1(designation);
    }
    else if (EQ(argument_type,Qother));
    else;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CLASS-OF-DESIGNATION-RESULT */
Object class_of_designation_result(designation)
    Object designation;
{
    Object frames, x2, role;
    char temp;

    x_note_fn_call(214,146);
    if (SYMBOLP(designation)) {
	frames = lookup_kb_specific_property_value(designation,
		Frame_or_frames_with_this_name_kbprop);
	if (SIMPLE_VECTOR_P(frames) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(frames)) > (SI_Long)2L &&  
		!EQ(ISVREF(frames,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(frames,(SI_Long)1L);
	    temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp = TRUEP(Nil);
	if (temp)
	    return VALUES_1(ISVREF(ISVREF(frames,(SI_Long)1L),(SI_Long)1L));
	else if (CONSP(frames))
	    return VALUES_1(ISVREF(ISVREF(FIRST(frames),(SI_Long)1L),
		    (SI_Long)1L));
	else
	    return VALUES_1(Nil);
    }
    else if (CONSP(designation)) {
	role = simple_role_of_role(role_of_designation(designation));
	if (CONSP(role))
	    return atomic_class_element_of_role(role);
	else if (SYMBOLP(role) &&  !TRUEP(domain_of_designation(designation)))
	    return VALUES_1(role);
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qin_order;           /* in-order */

static Object Qsimultaneously;     /* simultaneously */

static Object Qconclude_not;       /* conclude-not */

static Object Qconclude_has_no_current_value;  /* conclude-has-no-current-value */

static Object Qfocus;              /* focus */

static Object Qconclude;           /* conclude */

static Object Qinvoke;             /* invoke */

static Object Qhalt;               /* halt */

static Object Qinform;             /* inform */

static Object Qactivate;           /* activate */

static Object Qdeactivate;         /* deactivate */

static Object Qshow;               /* show */

static Object Qmove;               /* move */

static Object Qset_position;       /* set-position */

static Object Qrotate;             /* rotate */

static Object Qset_heading;        /* set-heading */

static Object Qchange_icon_color;  /* change-icon-color */

/* NOTE-DESIGNATIONS-IN-CONSEQUENT-USING-ENVIRONMENT */
Object note_designations_in_consequent_using_environment(consequent)
    Object consequent;
{
    Object temp, action, ab_loop_list_, designation, class_qm, gensymed_symbol;
    Object gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    Object gensymed_symbol_4, ab_loop_desetq_, attribute_qm, new_designation;
    Object message_1, expression;
    char temp_1;

    x_note_fn_call(214,147);
    if (CONSP(consequent)) {
	temp = CAR(consequent);
	if (EQ(temp,Qand) || EQ(temp,Qin_order) || EQ(temp,Qsimultaneously)) {
	    action = Nil;
	    ab_loop_list_ = CDR(consequent);
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    action = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    note_designations_in_consequent_using_environment(action);
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else if (EQ(temp,Qconclude_not) || EQ(temp,
		Qconclude_has_no_current_value) || EQ(temp,Qfocus))
	    return lookup_previous_reference_and_note_designation(SECOND(consequent));
	else if (EQ(temp,Qconclude)) {
	    designation = 
		    lookup_previous_reference_and_note_designation(SECOND(consequent));
	    if (THIRD(consequent)) {
		note_designations_in_expression_using_environment(THIRD(consequent));
		temp = THIRD(consequent);
		if (CONSP(temp)) {
		    temp = THIRD(consequent);
		    temp_1 = EQ(FIRST(temp),Qquote);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    temp = THIRD(consequent);
		    temp = SECOND(temp);
		    temp_1 = SYMBOLP(temp);
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    class_qm = class_of_designation_result(designation);
		    if (class_qm) {
			gensymed_symbol = class_qm;
			temp = THIRD(consequent);
			gensymed_symbol_1 = SECOND(temp);
			gensymed_symbol = 
				lookup_global_or_kb_specific_property_value(gensymed_symbol,
				Class_description_gkbprop);
			gensymed_symbol = gensymed_symbol ? 
				ISVREF(gensymed_symbol,(SI_Long)2L) : Nil;
			gensymed_symbol_2 = Nil;
			gensymed_symbol_3 = Nil;
			gensymed_symbol_4 = Nil;
			ab_loop_list_ = 
				lookup_kb_specific_property_value(gensymed_symbol_1,
				Attribute_value_kbprop);
			ab_loop_desetq_ = Nil;
		      next_loop_1:
			if ( !TRUEP(ab_loop_list_))
			    goto end_loop_1;
			ab_loop_desetq_ = M_CAR(ab_loop_list_);
			gensymed_symbol_3 = CAR(ab_loop_desetq_);
			gensymed_symbol_4 = CDR(ab_loop_desetq_);
			ab_loop_list_ = M_CDR(ab_loop_list_);
			if (memq_function(gensymed_symbol_3,gensymed_symbol)) {
			    if (gensymed_symbol_2) {
				Suppress_warning_message_header_qm = T;
				if ((SI_Long)1L <= IFIX(Warning_message_level))
				    give_warning_1(6,FIX((SI_Long)1L),
					    string_constant_146,
					    gensymed_symbol_3,
					    gensymed_symbol_1,
					    gensymed_symbol_2,
					    gensymed_symbol_4);
				Suppress_warning_message_header_qm = Nil;
				attribute_qm = Nil;
				goto end_1;
			    }
			    else
				gensymed_symbol_2 = gensymed_symbol_4;
			}
			goto next_loop_1;
		      end_loop_1:
			attribute_qm = gensymed_symbol_2;
			goto end_1;
			attribute_qm = Qnil;
		      end_1:;
		    }
		    else
			attribute_qm = Nil;
		    if (attribute_qm) {
			new_designation = gensym_list_3(Qthe,attribute_qm,
				designation);
			lookup_previous_reference_and_note_designation(new_designation);
			return reclaim_gensym_list_1(new_designation);
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
	else if (EQ(temp,Qevery)) {
	    designation = gensym_cons_1(Qany,
		    copy_tree_using_gensym_conses_1(SECOND(consequent)));
	    lookup_previous_reference_and_note_designation(designation);
	    reclaim_gensym_tree_1(designation);
	    return note_designations_in_consequent_using_environment(THIRD(consequent));
	}
	else if (EQ(temp,Qinvoke)) {
	    if (THIRD(consequent))
		return lookup_previous_reference_and_note_designation(THIRD(consequent));
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qhalt))
	    return VALUES_1(Nil);
	else if (EQ(temp,Qinform)) {
	    lookup_previous_reference_and_note_designation(SECOND(consequent));
	    message_1 = THIRD(consequent);
	    if (CONSP(message_1)) {
		expression = Nil;
		ab_loop_list_ = CDDR(message_1);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
	      next_loop_2:
		expression = M_CAR(ab_loop_list_);
		note_designations_in_expression_using_environment(expression);
		ab_loop_list_ = CDDR(ab_loop_list_);
		if ( !TRUEP(ab_loop_list_))
		    goto end_loop_2;
		goto next_loop_2;
	      end_loop_2:
		return VALUES_1(Qnil);
	    }
	    else
		return VALUES_1(Nil);
	}
	else if (EQ(temp,Qset)) {
	    lookup_previous_reference_and_note_designation(SECOND(consequent));
	    return note_designations_in_expression_using_environment(THIRD(consequent));
	}
	else if (EQ(temp,Qactivate) || EQ(temp,Qdeactivate))
	    return lookup_previous_reference_and_note_designation(SECOND(consequent));
	else if (EQ(temp,Qshow) || EQ(temp,Qhide))
	    return lookup_previous_reference_and_note_designation(SECOND(consequent));
	else if (EQ(temp,Qmove) || EQ(temp,Qset_position)) {
	    lookup_previous_reference_and_note_designation(SECOND(consequent));
	    note_designations_in_expression_using_environment(THIRD(consequent));
	    return note_designations_in_expression_using_environment(FOURTH(consequent));
	}
	else if (EQ(temp,Qrotate) || EQ(temp,Qset_heading)) {
	    lookup_previous_reference_and_note_designation(SECOND(consequent));
	    return note_designations_in_expression_using_environment(THIRD(consequent));
	}
	else if (EQ(temp,Qchange_icon_color)) {
	    lookup_previous_reference_and_note_designation(SECOND(consequent));
	    temp = THIRD(consequent);
	    if (CONSP(temp)) {
		temp = THIRD(consequent);
		return note_designations_in_expression_using_environment(SECOND(temp));
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

static Object string_constant_147;  /* "Invoked with focus on ~nf as the ~(~a~)" */

static Object string_constant_148;  /* " ~a:" */

static Object string_constant_149;  /* ":" */

/* SHORT-REPRESENTATIONS-OF-BACKWARD-INVOCATIONS */
Object short_representations_of_backward_invocations(link_and_objects_list)
    Object link_and_objects_list;
{
    Object frames_to_show, entry, ab_loop_list_, link_1, object, rule;
    Object focus_qm, local_name_qm, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    Declare_special(5);

    x_note_fn_call(214,148);
    frames_to_show = Nil;
    entry = Nil;
    ab_loop_list_ = link_and_objects_list;
    link_1 = Nil;
    object = Nil;
    rule = Nil;
    focus_qm = Nil;
    local_name_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = CAR(entry);
    object = CDR(entry);
    rule = ISVREF(link_1,(SI_Long)2L);
    focus_qm = ISVREF(link_1,(SI_Long)4L);
    local_name_qm = ISVREF(link_1,(SI_Long)5L);
    if (focus_qm) {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  tformat(3,string_constant_147,object,focus_qm);
		  if (local_name_qm)
		      tformat(2,string_constant_148,local_name_qm);
		  else
		      tformat(1,string_constant_149);
		  temp = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp = make_description_box(temp);
	frames_to_show = gensym_cons_1(temp,frames_to_show);
    }
    temp = make_short_representation(3,rule,Nil,Qsmall);
    frames_to_show = gensym_cons_1(temp,frames_to_show);
    goto next_loop;
  end_loop:;
    return VALUES_1(frames_to_show);
}

/* SHORT-REPRESENTATIONS-OF-FORWARD-INVOCATIONS */
Object short_representations_of_forward_invocations(link_and_objects_list)
    Object link_and_objects_list;
{
    Object descriptive_elements_to_show, entry, ab_loop_list_, link_1, object;
    Object rule, focus_qm, local_name_qm, x2, gensymed_symbol;
    Object sub_class_bit_vector, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object descriptive_text_string, temp_1;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp;
    Declare_special(5);

    x_note_fn_call(214,149);
    descriptive_elements_to_show = Nil;
    entry = Nil;
    ab_loop_list_ = link_and_objects_list;
    link_1 = Nil;
    object = Nil;
    rule = Nil;
    focus_qm = Nil;
    local_name_qm = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    entry = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    link_1 = CAR(entry);
    object = CDR(entry);
    rule = ISVREF(link_1,(SI_Long)2L);
    focus_qm = ISVREF(link_1,(SI_Long)4L);
    local_name_qm = ISVREF(link_1,(SI_Long)5L);
    if (SIMPLE_VECTOR_P(rule) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(rule)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(rule,(SI_Long)1L),
	    Qavailable_frame_vector)) {
	x2 = ISVREF(rule,(SI_Long)1L);
	gensymed_symbol = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 x2 : Qnil;
    }
    else
	gensymed_symbol = Nil;
    if (gensymed_symbol) {
	sub_class_bit_vector = ISVREF(gensymed_symbol,(SI_Long)19L);
	superior_class_bit_number = IFIX(ISVREF(Rule_class_description,
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
    if (temp) {
	if (focus_qm) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      tformat(3,string_constant_147,object,focus_qm);
		      if (local_name_qm)
			  tformat(2,string_constant_148,local_name_qm);
		      else
			  tformat(1,string_constant_149);
		      descriptive_text_string = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	    temp_1 = make_description_box(descriptive_text_string);
	    descriptive_elements_to_show = gensym_cons_1(temp_1,
		    descriptive_elements_to_show);
	}
	temp_1 = make_short_representation(3,rule,Nil,Qsmall);
	descriptive_elements_to_show = gensym_cons_1(temp_1,
		descriptive_elements_to_show);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(descriptive_elements_to_show);
}

static Object Qg2_defstruct_structure_name_rule_instance_g2_struct;  /* g2-defstruct-structure-name::rule-instance-g2-struct */

/* CACHE-EXPLANATION-VARIABLES */
Object cache_explanation_variables(variable_or_parameter)
    Object variable_or_parameter;
{
    Object cached_explanation_variables, svref_arg_1, svref_new_value, temp;

    x_note_fn_call(214,150);
    if (SIMPLE_VECTOR_P(Current_computation_instance) && 
	    EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
	    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	cached_explanation_variables = ISVREF(Current_computation_instance,
		(SI_Long)21L);
	if ( !TRUEP(assq_function(variable_or_parameter,
		cached_explanation_variables))) {
	    svref_arg_1 = Current_computation_instance;
	    svref_new_value = 
		    gensym_cons_1(gensym_cons_1(variable_or_parameter,
		    copy_frame_serial_number(ISVREF(variable_or_parameter,
		    (SI_Long)3L))),cached_explanation_variables);
	    return VALUES_1(SVREF(svref_arg_1,FIX((SI_Long)21L)) = 
		    svref_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else if ( !TRUEP(assq_function(variable_or_parameter,
	    Explanation_variables))) {
	temp = gensym_cons_1(variable_or_parameter,
		copy_frame_serial_number(ISVREF(variable_or_parameter,
		(SI_Long)3L)));
	Explanation_variables = gensym_cons_1(temp,Explanation_variables);
	return VALUES_1(Explanation_variables);
    }
    else
	return VALUES_1(Nil);
}

Object The_type_description_of_cached_explanation = UNBOUND;

static Object Qg2_defstruct_structure_name_cached_explanation_g2_struct;  /* g2-defstruct-structure-name::cached-explanation-g2-struct */

/* MAKE-PERMANENT-CACHED-EXPLANATION-STRUCTURE-INTERNAL */
Object make_permanent_cached_explanation_structure_internal()
{
    Object def_structure_cached_explanation_variable;
    Object defstruct_g2_cached_explanation_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,151);
    def_structure_cached_explanation_variable = Nil;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cached_explanation_variable = Nil;
	gensymed_symbol = (SI_Long)1L;
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
	defstruct_g2_cached_explanation_variable = the_array;
	SVREF(defstruct_g2_cached_explanation_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_g2_struct;
	def_structure_cached_explanation_variable = 
		defstruct_g2_cached_explanation_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cached_explanation_variable);
}

/* MAKE-CACHED-EXPLANATION-1 */
Object make_cached_explanation_1()
{
    Object def_structure_cached_explanation_variable;

    x_note_fn_call(214,152);
    def_structure_cached_explanation_variable = 
	    make_permanent_cached_explanation_structure_internal();
    inline_note_allocate_cons(def_structure_cached_explanation_variable,Nil);
    return VALUES_1(def_structure_cached_explanation_variable);
}

static Object Qtype_description_of_unique_type_name_of_gensym_structure;  /* type-description-of-unique-type-name-of-gensym-structure */

/* RECLAIM-CACHED-EXPLANATION */
Object reclaim_cached_explanation(cached_explanation)
    Object cached_explanation;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,153);
    gensymed_symbol = ISVREF(cached_explanation,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)3L);
    gensymed_symbol_1 = cached_explanation;
    inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    return VALUES_1(Nil);
}

Object The_type_description_of_cached_explanation_from_data_server_or_initial_value = UNBOUND;

Object Chain_of_available_cached_explanation_from_data_server_or_initial_values = UNBOUND;

Object Cached_explanation_from_data_server_or_initial_value_count = UNBOUND;

/* CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-STRUCTURE-MEMORY-USAGE */
Object cached_explanation_from_data_server_or_initial_value_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,154);
    temp = Cached_explanation_from_data_server_or_initial_value_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-COUNT */
Object outstanding_cached_explanation_from_data_server_or_initial_value_count()
{
    Object def_structure_cached_explanation_from_data_server_or_initial_value_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,155);
    gensymed_symbol = 
	    IFIX(Cached_explanation_from_data_server_or_initial_value_count);
    def_structure_cached_explanation_from_data_server_or_initial_value_variable 
	    = 
	    Chain_of_available_cached_explanation_from_data_server_or_initial_values;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_cached_explanation_from_data_server_or_initial_value_variable))
	goto end_loop;
    def_structure_cached_explanation_from_data_server_or_initial_value_variable 
	    = 
	    ISVREF(def_structure_cached_explanation_from_data_server_or_initial_value_variable,
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

/* RECLAIM-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-1 */
Object reclaim_cached_explanation_from_data_server_or_initial_value_1(cached_explanation_from_data_server_or_initial_value)
    Object cached_explanation_from_data_server_or_initial_value;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,156);
    inline_note_reclaim_cons(cached_explanation_from_data_server_or_initial_value,
	    Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = 
	    cached_explanation_from_data_server_or_initial_value;
    reclaim_text_string(ISVREF(cached_explanation_from_data_server_or_initial_value,
	    (SI_Long)1L));
    SVREF(cached_explanation_from_data_server_or_initial_value,
	    FIX((SI_Long)1L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = 
	    Chain_of_available_cached_explanation_from_data_server_or_initial_values;
    SVREF(cached_explanation_from_data_server_or_initial_value,
	    FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_cached_explanation_from_data_server_or_initial_values 
	    = cached_explanation_from_data_server_or_initial_value;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE */
Object reclaim_structure_for_cached_explanation_from_data_server_or_initial_value(cached_explanation_from_data_server_or_initial_value)
    Object cached_explanation_from_data_server_or_initial_value;
{
    x_note_fn_call(214,157);
    return reclaim_cached_explanation_from_data_server_or_initial_value_1(cached_explanation_from_data_server_or_initial_value);
}

static Object Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct;  /* g2-defstruct-structure-name::cached-explanation-from-data-server-or-initial-value-g2-struct */

/* MAKE-PERMANENT-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-STRUCTURE-INTERNAL */
Object make_permanent_cached_explanation_from_data_server_or_initial_value_structure_internal()
{
    Object def_structure_cached_explanation_from_data_server_or_initial_value_variable;
    Object cached_explanation_from_data_server_or_initial_value_count_new_value;
    Object defstruct_g2_cached_explanation_from_data_server_or_initial_value_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,158);
    def_structure_cached_explanation_from_data_server_or_initial_value_variable 
	    = Nil;
    cached_explanation_from_data_server_or_initial_value_count_new_value = 
	    FIXNUM_ADD1(Cached_explanation_from_data_server_or_initial_value_count);
    Cached_explanation_from_data_server_or_initial_value_count = 
	    cached_explanation_from_data_server_or_initial_value_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cached_explanation_from_data_server_or_initial_value_variable 
		= Nil;
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
	defstruct_g2_cached_explanation_from_data_server_or_initial_value_variable 
		= the_array;
	SVREF(defstruct_g2_cached_explanation_from_data_server_or_initial_value_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct;
	def_structure_cached_explanation_from_data_server_or_initial_value_variable 
		= 
		defstruct_g2_cached_explanation_from_data_server_or_initial_value_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cached_explanation_from_data_server_or_initial_value_variable);
}

/* MAKE-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-1 */
Object make_cached_explanation_from_data_server_or_initial_value_1(explanation_string)
    Object explanation_string;
{
    Object def_structure_cached_explanation_from_data_server_or_initial_value_variable;

    x_note_fn_call(214,159);
    def_structure_cached_explanation_from_data_server_or_initial_value_variable 
	    = 
	    Chain_of_available_cached_explanation_from_data_server_or_initial_values;
    if (def_structure_cached_explanation_from_data_server_or_initial_value_variable) 
		{
	Chain_of_available_cached_explanation_from_data_server_or_initial_values 
		= 
		ISVREF(def_structure_cached_explanation_from_data_server_or_initial_value_variable,
		(SI_Long)0L);
	SVREF(def_structure_cached_explanation_from_data_server_or_initial_value_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct;
    }
    else
	def_structure_cached_explanation_from_data_server_or_initial_value_variable 
		= 
		make_permanent_cached_explanation_from_data_server_or_initial_value_structure_internal();
    inline_note_allocate_cons(def_structure_cached_explanation_from_data_server_or_initial_value_variable,
	    Nil);
    SVREF(def_structure_cached_explanation_from_data_server_or_initial_value_variable,
	    FIX((SI_Long)1L)) = explanation_string;
    return VALUES_1(def_structure_cached_explanation_from_data_server_or_initial_value_variable);
}

Object The_type_description_of_cached_explanation_from_specific_formula = UNBOUND;

Object Chain_of_available_cached_explanation_from_specific_formulas = UNBOUND;

Object Cached_explanation_from_specific_formula_count = UNBOUND;

/* CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-STRUCTURE-MEMORY-USAGE */
Object cached_explanation_from_specific_formula_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,160);
    temp = Cached_explanation_from_specific_formula_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-COUNT */
Object outstanding_cached_explanation_from_specific_formula_count()
{
    Object def_structure_cached_explanation_from_specific_formula_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,161);
    gensymed_symbol = IFIX(Cached_explanation_from_specific_formula_count);
    def_structure_cached_explanation_from_specific_formula_variable = 
	    Chain_of_available_cached_explanation_from_specific_formulas;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_cached_explanation_from_specific_formula_variable))
	goto end_loop;
    def_structure_cached_explanation_from_specific_formula_variable = 
	    ISVREF(def_structure_cached_explanation_from_specific_formula_variable,
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

/* RECLAIM-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-1 */
Object reclaim_cached_explanation_from_specific_formula_1(cached_explanation_from_specific_formula)
    Object cached_explanation_from_specific_formula;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,162);
    inline_note_reclaim_cons(cached_explanation_from_specific_formula,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = cached_explanation_from_specific_formula;
    reclaim_text_string(ISVREF(cached_explanation_from_specific_formula,
	    (SI_Long)1L));
    SVREF(cached_explanation_from_specific_formula,FIX((SI_Long)1L)) = Nil;
    reclaim_evaled_variables_list(ISVREF(cached_explanation_from_specific_formula,
	    (SI_Long)2L));
    SVREF(cached_explanation_from_specific_formula,FIX((SI_Long)2L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = 
	    Chain_of_available_cached_explanation_from_specific_formulas;
    SVREF(cached_explanation_from_specific_formula,FIX((SI_Long)0L)) = 
	    svref_new_value;
    Chain_of_available_cached_explanation_from_specific_formulas = 
	    cached_explanation_from_specific_formula;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA */
Object reclaim_structure_for_cached_explanation_from_specific_formula(cached_explanation_from_specific_formula)
    Object cached_explanation_from_specific_formula;
{
    x_note_fn_call(214,163);
    return reclaim_cached_explanation_from_specific_formula_1(cached_explanation_from_specific_formula);
}

static Object Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct;  /* g2-defstruct-structure-name::cached-explanation-from-specific-formula-g2-struct */

/* MAKE-PERMANENT-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-STRUCTURE-INTERNAL */
Object make_permanent_cached_explanation_from_specific_formula_structure_internal()
{
    Object def_structure_cached_explanation_from_specific_formula_variable;
    Object cached_explanation_from_specific_formula_count_new_value;
    Object defstruct_g2_cached_explanation_from_specific_formula_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,164);
    def_structure_cached_explanation_from_specific_formula_variable = Nil;
    cached_explanation_from_specific_formula_count_new_value = 
	    FIXNUM_ADD1(Cached_explanation_from_specific_formula_count);
    Cached_explanation_from_specific_formula_count = 
	    cached_explanation_from_specific_formula_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cached_explanation_from_specific_formula_variable = Nil;
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
	defstruct_g2_cached_explanation_from_specific_formula_variable = 
		the_array;
	SVREF(defstruct_g2_cached_explanation_from_specific_formula_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct;
	def_structure_cached_explanation_from_specific_formula_variable = 
		defstruct_g2_cached_explanation_from_specific_formula_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cached_explanation_from_specific_formula_variable);
}

/* MAKE-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-1 */
Object make_cached_explanation_from_specific_formula_1(explanation_specific_formula_text,
	    explanation_evaled_variables_from_specific_formula)
    Object explanation_specific_formula_text;
    Object explanation_evaled_variables_from_specific_formula;
{
    Object def_structure_cached_explanation_from_specific_formula_variable;

    x_note_fn_call(214,165);
    def_structure_cached_explanation_from_specific_formula_variable = 
	    Chain_of_available_cached_explanation_from_specific_formulas;
    if (def_structure_cached_explanation_from_specific_formula_variable) {
	Chain_of_available_cached_explanation_from_specific_formulas = 
		ISVREF(def_structure_cached_explanation_from_specific_formula_variable,
		(SI_Long)0L);
	SVREF(def_structure_cached_explanation_from_specific_formula_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct;
    }
    else
	def_structure_cached_explanation_from_specific_formula_variable = 
		make_permanent_cached_explanation_from_specific_formula_structure_internal();
    inline_note_allocate_cons(def_structure_cached_explanation_from_specific_formula_variable,
	    Nil);
    SVREF(def_structure_cached_explanation_from_specific_formula_variable,
	    FIX((SI_Long)1L)) = explanation_specific_formula_text;
    SVREF(def_structure_cached_explanation_from_specific_formula_variable,
	    FIX((SI_Long)2L)) = 
	    explanation_evaled_variables_from_specific_formula;
    return VALUES_1(def_structure_cached_explanation_from_specific_formula_variable);
}

Object The_type_description_of_cached_explanation_from_frame = UNBOUND;

Object Chain_of_available_cached_explanation_from_frames = UNBOUND;

Object Cached_explanation_from_frame_count = UNBOUND;

/* CACHED-EXPLANATION-FROM-FRAME-STRUCTURE-MEMORY-USAGE */
Object cached_explanation_from_frame_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,166);
    temp = Cached_explanation_from_frame_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)2L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CACHED-EXPLANATION-FROM-FRAME-COUNT */
Object outstanding_cached_explanation_from_frame_count()
{
    Object def_structure_cached_explanation_from_frame_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,167);
    gensymed_symbol = IFIX(Cached_explanation_from_frame_count);
    def_structure_cached_explanation_from_frame_variable = 
	    Chain_of_available_cached_explanation_from_frames;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_cached_explanation_from_frame_variable))
	goto end_loop;
    def_structure_cached_explanation_from_frame_variable = 
	    ISVREF(def_structure_cached_explanation_from_frame_variable,
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

/* RECLAIM-CACHED-EXPLANATION-FROM-FRAME-1 */
Object reclaim_cached_explanation_from_frame_1(cached_explanation_from_frame)
    Object cached_explanation_from_frame;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,168);
    inline_note_reclaim_cons(cached_explanation_from_frame,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = cached_explanation_from_frame;
    reclaim_if_evaluation_item_reference(ISVREF(cached_explanation_from_frame,
	    (SI_Long)1L));
    SVREF(cached_explanation_from_frame,FIX((SI_Long)1L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_cached_explanation_from_frames;
    SVREF(cached_explanation_from_frame,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_cached_explanation_from_frames = 
	    cached_explanation_from_frame;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CACHED-EXPLANATION-FROM-FRAME */
Object reclaim_structure_for_cached_explanation_from_frame(cached_explanation_from_frame)
    Object cached_explanation_from_frame;
{
    x_note_fn_call(214,169);
    return reclaim_cached_explanation_from_frame_1(cached_explanation_from_frame);
}

static Object Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct;  /* g2-defstruct-structure-name::cached-explanation-from-frame-g2-struct */

/* MAKE-PERMANENT-CACHED-EXPLANATION-FROM-FRAME-STRUCTURE-INTERNAL */
Object make_permanent_cached_explanation_from_frame_structure_internal()
{
    Object def_structure_cached_explanation_from_frame_variable;
    Object cached_explanation_from_frame_count_new_value;
    Object defstruct_g2_cached_explanation_from_frame_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,170);
    def_structure_cached_explanation_from_frame_variable = Nil;
    cached_explanation_from_frame_count_new_value = 
	    FIXNUM_ADD1(Cached_explanation_from_frame_count);
    Cached_explanation_from_frame_count = 
	    cached_explanation_from_frame_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cached_explanation_from_frame_variable = Nil;
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
	defstruct_g2_cached_explanation_from_frame_variable = the_array;
	SVREF(defstruct_g2_cached_explanation_from_frame_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct;
	def_structure_cached_explanation_from_frame_variable = 
		defstruct_g2_cached_explanation_from_frame_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cached_explanation_from_frame_variable);
}

/* MAKE-CACHED-EXPLANATION-FROM-FRAME-1 */
Object make_cached_explanation_from_frame_1(cached_explanation_item_reference)
    Object cached_explanation_item_reference;
{
    Object def_structure_cached_explanation_from_frame_variable;

    x_note_fn_call(214,171);
    def_structure_cached_explanation_from_frame_variable = 
	    Chain_of_available_cached_explanation_from_frames;
    if (def_structure_cached_explanation_from_frame_variable) {
	Chain_of_available_cached_explanation_from_frames = 
		ISVREF(def_structure_cached_explanation_from_frame_variable,
		(SI_Long)0L);
	SVREF(def_structure_cached_explanation_from_frame_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct;
    }
    else
	def_structure_cached_explanation_from_frame_variable = 
		make_permanent_cached_explanation_from_frame_structure_internal();
    inline_note_allocate_cons(def_structure_cached_explanation_from_frame_variable,
	    Nil);
    SVREF(def_structure_cached_explanation_from_frame_variable,
	    FIX((SI_Long)1L)) = cached_explanation_item_reference;
    return VALUES_1(def_structure_cached_explanation_from_frame_variable);
}

Object The_type_description_of_cached_explanation_from_generic_formula = UNBOUND;

Object Chain_of_available_cached_explanation_from_generic_formulas = UNBOUND;

Object Cached_explanation_from_generic_formula_count = UNBOUND;

/* CACHED-EXPLANATION-FROM-GENERIC-FORMULA-STRUCTURE-MEMORY-USAGE */
Object cached_explanation_from_generic_formula_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,172);
    temp = Cached_explanation_from_generic_formula_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)3L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CACHED-EXPLANATION-FROM-GENERIC-FORMULA-COUNT */
Object outstanding_cached_explanation_from_generic_formula_count()
{
    Object def_structure_cached_explanation_from_generic_formula_variable;
    Object count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,173);
    gensymed_symbol = IFIX(Cached_explanation_from_generic_formula_count);
    def_structure_cached_explanation_from_generic_formula_variable = 
	    Chain_of_available_cached_explanation_from_generic_formulas;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( 
	    !TRUEP(def_structure_cached_explanation_from_generic_formula_variable))
	goto end_loop;
    def_structure_cached_explanation_from_generic_formula_variable = 
	    ISVREF(def_structure_cached_explanation_from_generic_formula_variable,
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

/* RECLAIM-CACHED-EXPLANATION-FROM-GENERIC-FORMULA-1 */
Object reclaim_cached_explanation_from_generic_formula_1(cached_explanation_from_generic_formula)
    Object cached_explanation_from_generic_formula;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,174);
    inline_note_reclaim_cons(cached_explanation_from_generic_formula,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = cached_explanation_from_generic_formula;
    reclaim_if_evaluation_item_reference(ISVREF(cached_explanation_from_generic_formula,
	    (SI_Long)1L));
    SVREF(cached_explanation_from_generic_formula,FIX((SI_Long)1L)) = Nil;
    reclaim_evaled_variables_list(ISVREF(cached_explanation_from_generic_formula,
	    (SI_Long)2L));
    SVREF(cached_explanation_from_generic_formula,FIX((SI_Long)2L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = 
	    Chain_of_available_cached_explanation_from_generic_formulas;
    SVREF(cached_explanation_from_generic_formula,FIX((SI_Long)0L)) = 
	    svref_new_value;
    Chain_of_available_cached_explanation_from_generic_formulas = 
	    cached_explanation_from_generic_formula;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CACHED-EXPLANATION-FROM-GENERIC-FORMULA */
Object reclaim_structure_for_cached_explanation_from_generic_formula(cached_explanation_from_generic_formula)
    Object cached_explanation_from_generic_formula;
{
    x_note_fn_call(214,175);
    return reclaim_cached_explanation_from_generic_formula_1(cached_explanation_from_generic_formula);
}

static Object Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct;  /* g2-defstruct-structure-name::cached-explanation-from-generic-formula-g2-struct */

/* MAKE-PERMANENT-CACHED-EXPLANATION-FROM-GENERIC-FORMULA-STRUCTURE-INTERNAL */
Object make_permanent_cached_explanation_from_generic_formula_structure_internal()
{
    Object def_structure_cached_explanation_from_generic_formula_variable;
    Object cached_explanation_from_generic_formula_count_new_value;
    Object defstruct_g2_cached_explanation_from_generic_formula_variable;
    Object the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,176);
    def_structure_cached_explanation_from_generic_formula_variable = Nil;
    cached_explanation_from_generic_formula_count_new_value = 
	    FIXNUM_ADD1(Cached_explanation_from_generic_formula_count);
    Cached_explanation_from_generic_formula_count = 
	    cached_explanation_from_generic_formula_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cached_explanation_from_generic_formula_variable = Nil;
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
	defstruct_g2_cached_explanation_from_generic_formula_variable = 
		the_array;
	SVREF(defstruct_g2_cached_explanation_from_generic_formula_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct;
	SVREF(defstruct_g2_cached_explanation_from_generic_formula_variable,
		FIX((SI_Long)1L)) = Nil;
	def_structure_cached_explanation_from_generic_formula_variable = 
		defstruct_g2_cached_explanation_from_generic_formula_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cached_explanation_from_generic_formula_variable);
}

/* MAKE-CACHED-EXPLANATION-FROM-GENERIC-FORMULA-1 */
Object make_cached_explanation_from_generic_formula_1(cached_explanation_item_reference,
	    explanation_evaled_variables_from_generic_formula)
    Object cached_explanation_item_reference;
    Object explanation_evaled_variables_from_generic_formula;
{
    Object def_structure_cached_explanation_from_generic_formula_variable;

    x_note_fn_call(214,177);
    def_structure_cached_explanation_from_generic_formula_variable = 
	    Chain_of_available_cached_explanation_from_generic_formulas;
    if (def_structure_cached_explanation_from_generic_formula_variable) {
	Chain_of_available_cached_explanation_from_generic_formulas = 
		ISVREF(def_structure_cached_explanation_from_generic_formula_variable,
		(SI_Long)0L);
	SVREF(def_structure_cached_explanation_from_generic_formula_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct;
    }
    else
	def_structure_cached_explanation_from_generic_formula_variable = 
		make_permanent_cached_explanation_from_generic_formula_structure_internal();
    inline_note_allocate_cons(def_structure_cached_explanation_from_generic_formula_variable,
	    Nil);
    SVREF(def_structure_cached_explanation_from_generic_formula_variable,
	    FIX((SI_Long)1L)) = cached_explanation_item_reference;
    SVREF(def_structure_cached_explanation_from_generic_formula_variable,
	    FIX((SI_Long)2L)) = 
	    explanation_evaled_variables_from_generic_formula;
    return VALUES_1(def_structure_cached_explanation_from_generic_formula_variable);
}

Object The_type_description_of_cached_explanation_from_rule = UNBOUND;

Object Chain_of_available_cached_explanation_from_rules = UNBOUND;

Object Cached_explanation_from_rule_count = UNBOUND;

/* CACHED-EXPLANATION-FROM-RULE-STRUCTURE-MEMORY-USAGE */
Object cached_explanation_from_rule_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,178);
    temp = Cached_explanation_from_rule_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)5L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-CACHED-EXPLANATION-FROM-RULE-COUNT */
Object outstanding_cached_explanation_from_rule_count()
{
    Object def_structure_cached_explanation_from_rule_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,179);
    gensymed_symbol = IFIX(Cached_explanation_from_rule_count);
    def_structure_cached_explanation_from_rule_variable = 
	    Chain_of_available_cached_explanation_from_rules;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_cached_explanation_from_rule_variable))
	goto end_loop;
    def_structure_cached_explanation_from_rule_variable = 
	    ISVREF(def_structure_cached_explanation_from_rule_variable,
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

/* RECLAIM-CACHED-EXPLANATION-FROM-RULE-1 */
Object reclaim_cached_explanation_from_rule_1(cached_explanation_from_rule)
    Object cached_explanation_from_rule;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,180);
    inline_note_reclaim_cons(cached_explanation_from_rule,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = cached_explanation_from_rule;
    reclaim_if_evaluation_item_reference(ISVREF(cached_explanation_from_rule,
	    (SI_Long)1L));
    SVREF(cached_explanation_from_rule,FIX((SI_Long)1L)) = Nil;
    reclaim_evaled_variables_list(ISVREF(cached_explanation_from_rule,
	    (SI_Long)2L));
    SVREF(cached_explanation_from_rule,FIX((SI_Long)2L)) = Nil;
    reclaim_if_environment_vector(ISVREF(cached_explanation_from_rule,
	    (SI_Long)3L));
    SVREF(cached_explanation_from_rule,FIX((SI_Long)3L)) = Nil;
    reclaim_frame_serial_number(ISVREF(cached_explanation_from_rule,
	    (SI_Long)4L));
    SVREF(cached_explanation_from_rule,FIX((SI_Long)4L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_cached_explanation_from_rules;
    SVREF(cached_explanation_from_rule,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_cached_explanation_from_rules = 
	    cached_explanation_from_rule;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-CACHED-EXPLANATION-FROM-RULE */
Object reclaim_structure_for_cached_explanation_from_rule(cached_explanation_from_rule)
    Object cached_explanation_from_rule;
{
    x_note_fn_call(214,181);
    return reclaim_cached_explanation_from_rule_1(cached_explanation_from_rule);
}

static Object Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct;  /* g2-defstruct-structure-name::cached-explanation-from-rule-g2-struct */

/* MAKE-PERMANENT-CACHED-EXPLANATION-FROM-RULE-STRUCTURE-INTERNAL */
Object make_permanent_cached_explanation_from_rule_structure_internal()
{
    Object def_structure_cached_explanation_from_rule_variable;
    Object cached_explanation_from_rule_count_new_value;
    Object defstruct_g2_cached_explanation_from_rule_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,182);
    def_structure_cached_explanation_from_rule_variable = Nil;
    cached_explanation_from_rule_count_new_value = 
	    FIXNUM_ADD1(Cached_explanation_from_rule_count);
    Cached_explanation_from_rule_count = 
	    cached_explanation_from_rule_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_cached_explanation_from_rule_variable = Nil;
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
	defstruct_g2_cached_explanation_from_rule_variable = the_array;
	SVREF(defstruct_g2_cached_explanation_from_rule_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct;
	SVREF(defstruct_g2_cached_explanation_from_rule_variable,
		FIX((SI_Long)1L)) = Nil;
	def_structure_cached_explanation_from_rule_variable = 
		defstruct_g2_cached_explanation_from_rule_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_cached_explanation_from_rule_variable);
}

/* MAKE-CACHED-EXPLANATION-FROM-RULE-1 */
Object make_cached_explanation_from_rule_1(cached_explanation_item_reference,
	    explanation_evaled_variables_from_rule,
	    explanation_rule_context,explanation_rule_context_guard)
    Object cached_explanation_item_reference;
    Object explanation_evaled_variables_from_rule, explanation_rule_context;
    Object explanation_rule_context_guard;
{
    Object def_structure_cached_explanation_from_rule_variable;

    x_note_fn_call(214,183);
    def_structure_cached_explanation_from_rule_variable = 
	    Chain_of_available_cached_explanation_from_rules;
    if (def_structure_cached_explanation_from_rule_variable) {
	Chain_of_available_cached_explanation_from_rules = 
		ISVREF(def_structure_cached_explanation_from_rule_variable,
		(SI_Long)0L);
	SVREF(def_structure_cached_explanation_from_rule_variable,
		FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct;
    }
    else
	def_structure_cached_explanation_from_rule_variable = 
		make_permanent_cached_explanation_from_rule_structure_internal();
    inline_note_allocate_cons(def_structure_cached_explanation_from_rule_variable,
	    Nil);
    SVREF(def_structure_cached_explanation_from_rule_variable,
	    FIX((SI_Long)1L)) = cached_explanation_item_reference;
    SVREF(def_structure_cached_explanation_from_rule_variable,
	    FIX((SI_Long)2L)) = explanation_evaled_variables_from_rule;
    SVREF(def_structure_cached_explanation_from_rule_variable,
	    FIX((SI_Long)3L)) = explanation_rule_context;
    SVREF(def_structure_cached_explanation_from_rule_variable,
	    FIX((SI_Long)4L)) = explanation_rule_context_guard;
    return VALUES_1(def_structure_cached_explanation_from_rule_variable);
}

/* RECLAIM-IF-ENVIRONMENT-VECTOR */
Object reclaim_if_environment_vector(v_qm)
    Object v_qm;
{
    x_note_fn_call(214,184);
    if (v_qm)
	reclaim_environment_vector(v_qm);
    return VALUES_1(Nil);
}

static Object Qitem_reference;     /* item-reference */

/* GET-VALID-FRAME-FROM-EXPLANATION */
Object get_valid_frame_from_explanation(cached_explanation_from_frame)
    Object cached_explanation_from_frame;
{
    Object item_or_value, temp;

    x_note_fn_call(214,185);
    item_or_value = ISVREF(cached_explanation_from_frame,(SI_Long)1L);
    temp = CONSP(item_or_value) && EQ(M_CDR(item_or_value),
	    Qitem_reference) ? ISVREF(M_CAR(item_or_value),(SI_Long)3L) : 
	    item_or_value;
    return VALUES_1(temp);
}

/* GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY-FUNCTION */
Object get_cached_explanation_evaled_variables_if_any_function(struct_1)
    Object struct_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,186);
    gensymed_symbol = ISVREF(struct_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)26L);
    gensymed_symbol_1 = struct_1;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY-FOR-CACHED-EXPLANATION */
Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation(cached_explanation)
    Object cached_explanation;
{
    x_note_fn_call(214,187);
    return VALUES_1(Nil);
}

/* GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY-FOR-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA */
Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_specific_formula(cached_explanation_from_specific_formula)
    Object cached_explanation_from_specific_formula;
{
    x_note_fn_call(214,188);
    return VALUES_1(ISVREF(cached_explanation_from_specific_formula,
	    (SI_Long)2L));
}

/* GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY-FOR-CACHED-EXPLANATION-FROM-GENERIC-FORMULA */
Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_generic_formula(cached_explanation_from_generic_formula)
    Object cached_explanation_from_generic_formula;
{
    x_note_fn_call(214,189);
    return VALUES_1(ISVREF(cached_explanation_from_generic_formula,
	    (SI_Long)2L));
}

/* GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY-FOR-CACHED-EXPLANATION-FROM-RULE */
Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_rule(cached_explanation_from_rule)
    Object cached_explanation_from_rule;
{
    x_note_fn_call(214,190);
    return VALUES_1(ISVREF(cached_explanation_from_rule,(SI_Long)2L));
}

/* MAKE-CACHED-EXPLANATION-NODE-FUNCTION */
Object make_cached_explanation_node_function(struct_1)
    Object struct_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,191);
    gensymed_symbol = ISVREF(struct_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)27L);
    gensymed_symbol_1 = struct_1;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* MAKE-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-RULE */
Object make_cached_explanation_node_for_cached_explanation_from_rule(cached_explanation_from_rule)
    Object cached_explanation_from_rule;
{
    Object rule;

    x_note_fn_call(214,192);
    rule = get_valid_frame_from_explanation(cached_explanation_from_rule);
    return make_explanation_table(2,rule,
	    make_slot_value_lists_of_context(3,rule,
	    ISVREF(cached_explanation_from_rule,(SI_Long)3L),
	    ISVREF(cached_explanation_from_rule,(SI_Long)4L)));
}

/* MAKE-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE */
Object make_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value(cached_explanation_from_data_server_or_initial_value)
    Object cached_explanation_from_data_server_or_initial_value;
{
    x_note_fn_call(214,193);
    return make_explanation_table(2,Nil,
	    gensym_cons_1(copy_text_string(ISVREF(cached_explanation_from_data_server_or_initial_value,
	    (SI_Long)1L)),Nil));
}

/* MAKE-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA */
Object make_cached_explanation_node_for_cached_explanation_from_specific_formula(cached_explanation_from_specific_formula)
    Object cached_explanation_from_specific_formula;
{
    x_note_fn_call(214,194);
    return make_explanation_table(2,Nil,
	    gensym_cons_1(copy_text_string(ISVREF(cached_explanation_from_specific_formula,
	    (SI_Long)1L)),Nil));
}

/* MAKE-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-FRAME */
Object make_cached_explanation_node_for_cached_explanation_from_frame(cached_explanation_from_frame)
    Object cached_explanation_from_frame;
{
    x_note_fn_call(214,195);
    return make_explanation_table(1,
	    get_valid_frame_from_explanation(cached_explanation_from_frame));
}

/* RETURN-CACHED-EXPLANATION-IF-VALID-FUNCTION */
Object return_cached_explanation_if_valid_function(struct_1)
    Object struct_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,196);
    gensymed_symbol = ISVREF(struct_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)28L);
    gensymed_symbol_1 = struct_1;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

/* RETURN-CACHED-EXPLANATION-IF-VALID-FOR-CACHED-EXPLANATION */
Object return_cached_explanation_if_valid_for_cached_explanation(cached_explanation)
    Object cached_explanation;
{
    x_note_fn_call(214,197);
    return VALUES_1(cached_explanation);
}

/* RETURN-CACHED-EXPLANATION-IF-VALID-FOR-CACHED-EXPLANATION-FROM-FRAME */
Object return_cached_explanation_if_valid_for_cached_explanation_from_frame(cached_explanation_from_frame)
    Object cached_explanation_from_frame;
{
    x_note_fn_call(214,198);
    if (get_valid_frame_from_explanation(cached_explanation_from_frame))
	return VALUES_1(cached_explanation_from_frame);
    else
	return VALUES_1(Nil);
}

/* EXPORT-CACHED-EXPLANATION-NODE-FUNCTION */
Object export_cached_explanation_node_function(struct_1)
    Object struct_1;
{
    Object gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,199);
    gensymed_symbol = ISVREF(struct_1,(SI_Long)0L);
    gensymed_symbol = 
	    ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
	    Qtype_description_of_unique_type_name_of_gensym_structure),
	    (SI_Long)9L),(SI_Long)29L);
    gensymed_symbol_1 = struct_1;
    return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
}

static Object Qnode_type;          /* node-type */

static Object Qdata_server_or_initial_value;  /* data-server-or-initial-value */

static Object Qitem_or_value;      /* item-or-value */

static Object Qnode_specific_data;  /* node-specific-data */

static Object Qab_structure;       /* structure */

/* EXPORT-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE */
Object export_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value(cached_explanation_from_data_server_or_initial_value)
    Object cached_explanation_from_data_server_or_initial_value;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(214,200);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qnode_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qnode_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qdata_server_or_initial_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qdata_server_or_initial_value;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_or_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_or_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		copy_as_wide_string(ISVREF(cached_explanation_from_data_server_or_initial_value,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		copy_as_wide_string(ISVREF(cached_explanation_from_data_server_or_initial_value,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qnode_specific_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qnode_specific_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return gensym_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qspecific_formula;   /* specific-formula */

/* EXPORT-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA */
Object export_cached_explanation_node_for_cached_explanation_from_specific_formula(cached_explanation_from_specific_formula)
    Object cached_explanation_from_specific_formula;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(214,201);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qnode_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qnode_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qspecific_formula;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qspecific_formula;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_or_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_or_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		copy_as_wide_string(ISVREF(cached_explanation_from_specific_formula,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		copy_as_wide_string(ISVREF(cached_explanation_from_specific_formula,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qnode_specific_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qnode_specific_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return gensym_cons_1(gensymed_symbol,Qab_structure);
}

/* EXPORT-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-FRAME */
Object export_cached_explanation_node_for_cached_explanation_from_frame(cached_explanation_from_frame)
    Object cached_explanation_from_frame;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(214,202);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qnode_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qnode_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qitem;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qitem;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_or_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_or_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		copy_evaluation_item_reference(ISVREF(cached_explanation_from_frame,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		copy_evaluation_item_reference(ISVREF(cached_explanation_from_frame,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qnode_specific_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qnode_specific_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = allocate_evaluation_sequence(Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = allocate_evaluation_sequence(Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    return gensym_cons_1(gensymed_symbol,Qab_structure);
}

static Object Qlocal_name;         /* local-name */

/* EXPORT-CACHED-EXPLANATION-NODE-FOR-CACHED-EXPLANATION-FROM-RULE */
Object export_cached_explanation_node_for_cached_explanation_from_rule(cached_explanation_from_rule)
    Object cached_explanation_from_rule;
{
    Object gensymed_symbol, temp, item_or_value, x2, temp_2, context_lists;
    Object local_name_and_bindings, ab_loop_list_, ab_loopvar_, ab_loopvar__1;
    Object ab_loopvar__2, gensymed_symbol_2, temp_3, svref_new_value;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(214,203);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qnode_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qnode_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qrule;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qrule;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_or_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_or_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = 
		copy_evaluation_item_reference(ISVREF(cached_explanation_from_rule,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = 
		copy_evaluation_item_reference(ISVREF(cached_explanation_from_rule,
		(SI_Long)1L));
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = temp_2;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qnode_specific_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qnode_specific_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	context_lists = make_slot_value_lists_of_context(4,
		ISVREF(M_CAR(ISVREF(cached_explanation_from_rule,
		(SI_Long)1L)),(SI_Long)3L),
		ISVREF(cached_explanation_from_rule,(SI_Long)3L),
		ISVREF(cached_explanation_from_rule,(SI_Long)4L),T);
	local_name_and_bindings = Nil;
	ab_loop_list_ = context_lists;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop;
	local_name_and_bindings = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qlocal_name;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)1L)) = Qlocal_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = FIRST(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = FIRST(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)2L)) = temp_2;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qitem_or_value;
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp,FIX((SI_Long)3L)) = Qitem_or_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = SECOND(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp;
	}
	else {
	    temp = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = SECOND(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(temp,FIX((SI_Long)4L)) = temp_2;
	}
	temp_3 = gensym_cons_1(gensymed_symbol_2,Qab_structure);
	reclaim_gensym_list_1(local_name_and_bindings);
	ab_loopvar__2 = gensym_cons_1(temp_3,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop;
      end_loop:
	reclaim_gensym_list_1(context_lists);
	temp_3 = ab_loopvar_;
	goto end_1;
	temp_3 = Qnil;
      end_1:;
	item_or_value = allocate_evaluation_sequence(temp_3);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	context_lists = make_slot_value_lists_of_context(4,
		ISVREF(M_CAR(ISVREF(cached_explanation_from_rule,
		(SI_Long)1L)),(SI_Long)3L),
		ISVREF(cached_explanation_from_rule,(SI_Long)3L),
		ISVREF(cached_explanation_from_rule,(SI_Long)4L),T);
	local_name_and_bindings = Nil;
	ab_loop_list_ = context_lists;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
	ab_loopvar__2 = Nil;
      next_loop_1:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_1;
	local_name_and_bindings = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	gensymed_symbol_2 = allocate_managed_array(1,FIX((SI_Long)4L + 
		(SI_Long)1L));
	gensymed_symbol_1 = (SI_Long)0L;
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	    ISVREF(gensymed_symbol_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(gensymed_symbol_1 >>  -  - 
		    (SI_Long)10L) + (SI_Long)2L);
	    svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	    ISVREF(temp_2,svref_arg_2) = FIX((SI_Long)1L);
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)3L)) = Qlocal_name;
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)1L)) = Qlocal_name;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = FIRST(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)4L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = FIRST(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)2L)) = svref_new_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size))
	    SVREF(gensymed_symbol_2,FIX((SI_Long)5L)) = Qitem_or_value;
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    SVREF(temp_2,FIX((SI_Long)3L)) = Qitem_or_value;
	}
	if (FIXNUM_LE(ISVREF(gensymed_symbol_2,(SI_Long)1L),
		Maximum_in_place_array_size)) {
	    item_or_value = SECOND(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    temp_2 = temp_1 ? get_reference_to_item(item_or_value) : 
		    item_or_value;
	    SVREF(gensymed_symbol_2,FIX((SI_Long)6L)) = temp_2;
	}
	else {
	    temp_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
	    item_or_value = SECOND(local_name_and_bindings);
	    if (SIMPLE_VECTOR_P(item_or_value) && 
		    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		    (SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		    Qavailable_frame_vector)) {
		x2 = ISVREF(item_or_value,(SI_Long)1L);
		temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
			Qg2_defstruct_structure_name_class_description_g2_struct) 
			? TRUEP(x2) : TRUEP(Qnil);
	    }
	    else
		temp_1 = TRUEP(Nil);
	    svref_new_value = temp_1 ? 
		    get_reference_to_item(item_or_value) : item_or_value;
	    SVREF(temp_2,FIX((SI_Long)4L)) = svref_new_value;
	}
	temp_3 = gensym_cons_1(gensymed_symbol_2,Qab_structure);
	reclaim_gensym_list_1(local_name_and_bindings);
	ab_loopvar__2 = gensym_cons_1(temp_3,Nil);
	if (ab_loopvar__1)
	    M_CDR(ab_loopvar__1) = ab_loopvar__2;
	else
	    ab_loopvar_ = ab_loopvar__2;
	ab_loopvar__1 = ab_loopvar__2;
	goto next_loop_1;
      end_loop_1:
	reclaim_gensym_list_1(context_lists);
	temp_3 = ab_loopvar_;
	goto end_2;
	temp_3 = Qnil;
      end_2:;
	item_or_value = allocate_evaluation_sequence(temp_3);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = temp_2;
    }
    return gensym_cons_1(gensymed_symbol,Qab_structure);
}

/* EXPORT-CACHED-EXPLANATION-NODE-FOR-VORP */
Object export_cached_explanation_node_for_vorp(vorp)
    Object vorp;
{
    Object gensymed_symbol, temp, item_or_value, x2, svref_new_value;
    Object structure_qm, temp_2;
    SI_Long gensymed_symbol_1, svref_arg_2;
    char temp_1;

    x_note_fn_call(214,204);
    gensymed_symbol = allocate_managed_array(1,FIX((SI_Long)6L + (SI_Long)1L));
    gensymed_symbol_1 = (SI_Long)0L;
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	svref_arg_2 = gensymed_symbol_1 + IFIX(Managed_array_index_offset);
	ISVREF(gensymed_symbol,svref_arg_2) = FIX((SI_Long)1L);
    }
    else {
	temp = ISVREF(gensymed_symbol,(gensymed_symbol_1 >>  -  - 
		(SI_Long)10L) + (SI_Long)2L);
	svref_arg_2 = gensymed_symbol_1 & (SI_Long)1023L;
	ISVREF(temp,svref_arg_2) = FIX((SI_Long)1L);
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)3L)) = Qnode_type;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)1L)) = Qnode_type;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = Qvariable_or_parameter;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)4L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = Qvariable_or_parameter;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)2L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)5L)) = Qitem_or_value;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)3L)) = Qitem_or_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	item_or_value = vorp;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)6L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	item_or_value = vorp;
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)4L)) = svref_new_value;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size))
	SVREF(gensymed_symbol,FIX((SI_Long)7L)) = Qnode_specific_data;
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	SVREF(temp,FIX((SI_Long)5L)) = Qnode_specific_data;
    }
    if (FIXNUM_LE(ISVREF(gensymed_symbol,(SI_Long)1L),
	    Maximum_in_place_array_size)) {
	structure_qm = get_evaluation_value_of_variable_or_parameter(vorp,Nil);
	item_or_value = allocate_evaluation_sequence(structure_qm ? 
		gensym_cons_1(structure_qm,Nil) : Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	temp = temp_1 ? get_reference_to_item(item_or_value) : item_or_value;
	SVREF(gensymed_symbol,FIX((SI_Long)8L)) = temp;
    }
    else {
	temp = ISVREF(gensymed_symbol,(SI_Long)2L);
	structure_qm = get_evaluation_value_of_variable_or_parameter(vorp,Nil);
	item_or_value = allocate_evaluation_sequence(structure_qm ? 
		gensym_cons_1(structure_qm,Nil) : Nil);
	if (SIMPLE_VECTOR_P(item_or_value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_value)) > 
		(SI_Long)2L &&  !EQ(ISVREF(item_or_value,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(item_or_value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    ? TRUEP(x2) : TRUEP(Qnil);
	}
	else
	    temp_1 = TRUEP(Nil);
	svref_new_value = temp_1 ? get_reference_to_item(item_or_value) : 
		item_or_value;
	SVREF(temp,FIX((SI_Long)6L)) = svref_new_value;
    }
    temp_2 = gensym_cons_1(gensymed_symbol,Qab_structure);
    return VALUES_1(temp_2);
}

/* CREATE-EXPORTED-CACHED-EXPLANATION-NODE */
Object create_exported_cached_explanation_node(item_or_cached_explanation)
    Object item_or_cached_explanation;
{
    Object x2, temp_1, gensymed_symbol, gensymed_symbol_1;
    char temp;

    x_note_fn_call(214,205);
    if (SIMPLE_VECTOR_P(item_or_cached_explanation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(item_or_cached_explanation)) > 
	    (SI_Long)2L &&  !EQ(ISVREF(item_or_cached_explanation,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(item_or_cached_explanation,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp)
	temp_1 = 
		export_cached_explanation_node_for_vorp(item_or_cached_explanation);
    else {
	gensymed_symbol = ISVREF(item_or_cached_explanation,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)29L);
	gensymed_symbol_1 = item_or_cached_explanation;
	temp_1 = inline_funcall_1(gensymed_symbol,gensymed_symbol_1);
    }
    return VALUES_1(temp_1);
}

/* RECLAIM-EVALED-VARIABLES-LIST */
Object reclaim_evaled_variables_list(variables)
    Object variables;
{
    Object var, ab_loop_list_;

    x_note_fn_call(214,206);
    var = Nil;
    ab_loop_list_ = variables;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    var = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(CDR(var));
    reclaim_gensym_cons_1(var);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(variables);
}

static Object Qg2_internal_cached_explanation;  /* g2-internal-cached-explanation */

static Object Qinitial_value;      /* initial-value */

static Object array_constant_23;   /* # */

static Object array_constant_24;   /* # */

static Object Qg2_defstruct_structure_name_formula_invocation_g2_struct;  /* g2-defstruct-structure-name::formula-invocation-g2-struct */

static Object Qg2_defstruct_structure_name_procedure_invocation_g2_struct;  /* g2-defstruct-structure-name::procedure-invocation-g2-struct */

static Object Qparent_frame;       /* parent-frame */

/* CACHE-EXPLANATION */
Object cache_explanation(variable_or_parameter)
    Object variable_or_parameter;
{
    Object cached_explanation, g2_internal_cached_explanation_new_value, temp;
    Object sub_class_bit_vector;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp_1;

    x_note_fn_call(214,207);
    cached_explanation = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qg2_internal_cached_explanation,Nil);
    if (cached_explanation) {
	reclaim_cached_explanation(cached_explanation);
	set_non_savable_lookup_slot_value(variable_or_parameter,
		Qg2_internal_cached_explanation,Nil);
    }
    if (EQ(Current_computation_frame,variable_or_parameter)) {
	if (EQ(Current_computation_instance,Qinitial_value)) {
	    g2_internal_cached_explanation_new_value = 
		    make_cached_explanation_from_data_server_or_initial_value_1(copy_constant_wide_string_given_length(array_constant_23,
		    FIX((SI_Long)13L)));
	    return set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qg2_internal_cached_explanation,
		    g2_internal_cached_explanation_new_value);
	}
	else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_data_server_g2_struct)) {
	    g2_internal_cached_explanation_new_value = 
		    make_cached_explanation_from_data_server_or_initial_value_1(copy_constant_wide_string_given_length(array_constant_24,
		    FIX((SI_Long)20L)));
	    return set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qg2_internal_cached_explanation,
		    g2_internal_cached_explanation_new_value);
	}
	else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_formula_invocation_g2_struct)) {
	    temp = convert_text_to_text_string(1,
		    ISVREF(variable_or_parameter,(SI_Long)28L));
	    g2_internal_cached_explanation_new_value = 
		    make_cached_explanation_from_specific_formula_1(temp,
		    copy_explanation_variables(Explanation_variables));
	    return set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qg2_internal_cached_explanation,
		    g2_internal_cached_explanation_new_value);
	}
	else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
	    g2_internal_cached_explanation_new_value = 
		    make_cached_explanation_from_rule_and_rule_instance(ISVREF(Current_computation_instance,
		    (SI_Long)8L),Current_computation_instance);
	    return set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qg2_internal_cached_explanation,
		    g2_internal_cached_explanation_new_value);
	}
	else if (SIMPLE_VECTOR_P(Current_computation_instance) && 
		EQ(ISVREF(Current_computation_instance,(SI_Long)0L),
		Qg2_defstruct_structure_name_procedure_invocation_g2_struct)) {
	    g2_internal_cached_explanation_new_value = 
		    make_cached_explanation_from_procedure_frame(ISVREF(Current_computation_instance,
		    (SI_Long)23L));
	    return set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qg2_internal_cached_explanation,
		    g2_internal_cached_explanation_new_value);
	}
	else
	    return VALUES_1(Nil);
    }
    else {
	sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Generic_formula_class_description,(SI_Long)18L));
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
	    temp_1 = (SI_Long)0L < gensymed_symbol;
	}
	else
	    temp_1 = TRUEP(Nil);
	if (temp_1) {
	    temp = get_reference_to_item(Current_computation_frame);
	    g2_internal_cached_explanation_new_value = 
		    make_cached_explanation_from_generic_formula_1(temp,
		    copy_explanation_variables(Explanation_variables));
	    return set_non_savable_lookup_slot_value(variable_or_parameter,
		    Qg2_internal_cached_explanation,
		    g2_internal_cached_explanation_new_value);
	}
	else {
	    sub_class_bit_vector = ISVREF(ISVREF(Current_computation_frame,
		    (SI_Long)1L),(SI_Long)19L);
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
		temp_1 = (SI_Long)0L < gensymed_symbol;
	    }
	    else
		temp_1 = TRUEP(Nil);
	    if (temp_1) {
		g2_internal_cached_explanation_new_value = 
			rule_is_embedded_p(Current_computation_frame) ? 
			make_cached_explanation_from_frame_1(get_reference_to_item(get_lookup_slot_value_given_default(Current_computation_frame,
			Qparent_frame,Nil))) : 
			make_cached_explanation_from_rule_and_rule_instance(Current_computation_frame,
			Current_computation_instance);
		return set_non_savable_lookup_slot_value(variable_or_parameter,
			Qg2_internal_cached_explanation,
			g2_internal_cached_explanation_new_value);
	    }
	    else {
		sub_class_bit_vector = 
			ISVREF(ISVREF(Current_computation_frame,
			(SI_Long)1L),(SI_Long)19L);
		superior_class_bit_number = 
			IFIX(ISVREF(Procedure_class_description,(SI_Long)18L));
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
		    temp_1 = (SI_Long)0L < gensymed_symbol;
		}
		else
		    temp_1 = TRUEP(Nil);
		if (temp_1) {
		    g2_internal_cached_explanation_new_value = 
			    make_cached_explanation_from_procedure_frame(Current_computation_frame);
		    return set_non_savable_lookup_slot_value(variable_or_parameter,
			    Qg2_internal_cached_explanation,
			    g2_internal_cached_explanation_new_value);
		}
		else {
		    sub_class_bit_vector = 
			    ISVREF(ISVREF(Current_computation_frame,
			    (SI_Long)1L),(SI_Long)19L);
		    superior_class_bit_number = 
			    IFIX(ISVREF(Button_class_description,
			    (SI_Long)18L));
		    sub_class_vector_index = superior_class_bit_number >>  
			    -  - (SI_Long)3L;
		    if (sub_class_vector_index < 
			    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(sub_class_bit_vector))) 
				{
			gensymed_symbol = 
				UBYTE_8_ISAREF_1(sub_class_bit_vector,
				sub_class_vector_index);
			gensymed_symbol_1 = (SI_Long)1L;
			gensymed_symbol_2 = superior_class_bit_number & 
				(SI_Long)7L;
			gensymed_symbol_1 = gensymed_symbol_1 << 
				gensymed_symbol_2;
			gensymed_symbol = gensymed_symbol & gensymed_symbol_1;
			temp_1 = (SI_Long)0L < gensymed_symbol;
		    }
		    else
			temp_1 = TRUEP(Nil);
		    if (temp_1) {
			g2_internal_cached_explanation_new_value = 
				make_cached_explanation_from_frame_1(get_reference_to_item(Current_computation_frame));
			return set_non_savable_lookup_slot_value(variable_or_parameter,
				Qg2_internal_cached_explanation,
				g2_internal_cached_explanation_new_value);
		    }
		    else
			return VALUES_1(Nil);
		}
	    }
	}
    }
}

/* MAKE-CACHED-EXPLANATION-FROM-RULE-AND-RULE-INSTANCE */
Object make_cached_explanation_from_rule_and_rule_instance(rule,rule_instance)
    Object rule, rule_instance;
{
    Object temp, temp_1, locals, temp_2;

    x_note_fn_call(214,208);
    temp = get_reference_to_item(rule);
    temp_1 = copy_variables_list(ISVREF(rule_instance,(SI_Long)21L));
    locals = ISVREF(rule_instance,(SI_Long)2L);
    temp_2 = locals ? copy_environment_vector(locals) : Nil;
    return make_cached_explanation_from_rule_1(temp,temp_1,temp_2,
	    copy_frame_serial_number(ISVREF(rule_instance,(SI_Long)11L)));
}

/* MAKE-CACHED-EXPLANATION-FROM-PROCEDURE-FRAME */
Object make_cached_explanation_from_procedure_frame(procedure)
    Object procedure;
{
    x_note_fn_call(214,209);
    return make_cached_explanation_from_frame_1(get_reference_to_item(procedure));
}

static Object Qhash_explanation_node;  /* hash-explanation-node */

static Object Qget_explanation_children;  /* get-explanation-children */

static Object Qmake_explanation_node_representation;  /* make-explanation-node-representation */

/* CREATE-EXPLANATION-GRAPH */
Object create_explanation_graph(variable_or_parameter)
    Object variable_or_parameter;
{
    Object temp, temp_1, temp_2, temp_3, temp_4;

    x_note_fn_call(214,210);
    temp = IDENTITY(Qhash_explanation_node);
    if (temp);
    else
	temp = Qsxhashw;
    temp_1 = IDENTITY(Nil);
    if (temp_1);
    else
	temp_1 = Qvertical;
    temp_2 = IDENTITY(Nil);
    if (temp_2);
    else
	temp_2 = FIX((SI_Long)50L);
    temp_3 = IDENTITY(Nil);
    if (temp_3);
    else
	temp_3 = FIX((SI_Long)50L);
    temp_4 = IDENTITY(Qkb_workspace);
    if (temp_4);
    else
	temp_4 = Qtemporary_workspace;
    temp_4 = graph_frame_hierarchy_function(variable_or_parameter,
	    Qget_explanation_children,Nil,
	    Qmake_explanation_node_representation,temp,temp_1,temp_2,
	    temp_3,Nil,temp_4,Nil,Nil,Nil);
    return VALUES_1(temp_4);
}

static Object Qexplanation;        /* explanation */

/* CREATE-EXPLANATION */
Object create_explanation(variable_or_parameter)
    Object variable_or_parameter;
{
    Object explanation_object, graph, graph_workspace;

    x_note_fn_call(214,211);
    explanation_object = make_transient_item(Qexplanation);
    graph = create_explanation_graph(variable_or_parameter);
    graph_workspace = ISVREF(graph,(SI_Long)20L);
    reclaim_graph_display_1(graph);
    add_subworkspace(graph_workspace,explanation_object);
    return VALUES_1(explanation_object);
}

/* GET-EXPLANATION-CHILDREN */
Object get_explanation_children(variable_parameter_or_cached_explanation,
	    extra_arg)
    Object variable_parameter_or_cached_explanation, extra_arg;
{
    Object x2, sub_class_bit_vector, cached_explanation, gensymed_symbol_3;
    Object gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,212);
    if (SIMPLE_VECTOR_P(variable_parameter_or_cached_explanation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable_parameter_or_cached_explanation)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(variable_parameter_or_cached_explanation,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(variable_parameter_or_cached_explanation,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = 
		ISVREF(ISVREF(variable_parameter_or_cached_explanation,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
	cached_explanation = 
		get_valid_cached_explanation(variable_parameter_or_cached_explanation);
	if (cached_explanation)
	    return gensym_cons_1(cached_explanation,Nil);
	else
	    return VALUES_1(Nil);
    }
    else {
	gensymed_symbol_3 = 
		ISVREF(variable_parameter_or_cached_explanation,(SI_Long)0L);
	gensymed_symbol_3 = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_3),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)26L);
	gensymed_symbol_4 = variable_parameter_or_cached_explanation;
	return make_explanation_variable_list(inline_funcall_1(gensymed_symbol_3,
		gensymed_symbol_4));
    }
}

/* GET-VALID-CACHED-EXPLANATION */
Object get_valid_cached_explanation(variable_or_parameter)
    Object variable_or_parameter;
{
    Object explanation_qm, gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,213);
    explanation_qm = 
	    get_lookup_slot_value_given_default(variable_or_parameter,
	    Qg2_internal_cached_explanation,Nil);
    if (explanation_qm) {
	gensymed_symbol = ISVREF(explanation_qm,(SI_Long)0L);
	gensymed_symbol = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)28L);
	gensymed_symbol_1 = explanation_qm;
	return VALUES_1(inline_funcall_1(gensymed_symbol,gensymed_symbol_1));
    }
    else
	return VALUES_1(Nil);
}

/* MAKE-EXPLANATION-VARIABLE-LIST */
Object make_explanation_variable_list(variable_explanation_alist)
    Object variable_explanation_alist;
{
    Object variable_or_parameter, frame_serial_number, ab_loop_list_;
    Object ab_loopvar_, ab_loopvar__1, ab_loopvar__2, ab_loop_desetq_;
    Object gensymed_symbol, xa, ya;
    char temp;

    x_note_fn_call(214,214);
    variable_or_parameter = Nil;
    frame_serial_number = Nil;
    ab_loop_list_ = variable_explanation_alist;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    ab_loopvar__2 = Nil;
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    variable_or_parameter = CAR(ab_loop_desetq_);
    frame_serial_number = CDR(ab_loop_desetq_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    gensymed_symbol = ISVREF(variable_or_parameter,(SI_Long)3L);
    temp = SIMPLE_VECTOR_P(variable_or_parameter) ? 
	    EQ(ISVREF(variable_or_parameter,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else if (FIXNUMP(frame_serial_number))
	temp = FIXNUMP(gensymed_symbol) ? FIXNUM_LT(frame_serial_number,
		gensymed_symbol) : TRUEP(T);
    else if (FIXNUMP(gensymed_symbol))
	temp = TRUEP(Nil);
    else {
	xa = M_CAR(frame_serial_number);
	ya = M_CAR(gensymed_symbol);
	temp = FIXNUM_LT(xa,ya);
	if (temp);
	else
	    temp = FIXNUM_EQ(xa,ya) ? FIXNUM_LT(M_CDR(frame_serial_number),
		    M_CDR(gensymed_symbol)) : TRUEP(Qnil);
    }
    if ( !temp) {
	ab_loopvar__2 = gensym_cons_1(variable_or_parameter,Nil);
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

static Object Qnever;              /* never */

static Object array_constant_25;   /* # */

static Object array_constant_26;   /* # */

static Object array_constant_27;   /* # */

static Object array_constant_28;   /* # */

static Object Qtime_stamp;         /* time-stamp */

static Object array_constant_29;   /* # */

/* MAKE-EXPLANATION-VARIABLE-NODE */
Object make_explanation_variable_node(variable_or_parameter)
    Object variable_or_parameter;
{
    Object sub_class_bit_vector, expiration, temp_1, temp_2, temp_3;
    Object current_wide_string_list, wide_string_bv16, current_wide_string;
    Object fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object managed_number_or_value, temp_4, managed_number;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, bv16_length, aref_arg_2;
    SI_Long aref_new_value, length_1;
    char temp, expiration_is_number_qm;
    Declare_special(5);

    x_note_fn_call(214,215);
    sub_class_bit_vector = ISVREF(ISVREF(variable_or_parameter,
	    (SI_Long)1L),(SI_Long)19L);
    superior_class_bit_number = IFIX(ISVREF(Parameter_class_description,
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
    expiration = temp ? Qnever : ISVREF(variable_or_parameter,(SI_Long)26L);
    expiration_is_number_qm = FIXNUMP(expiration);
    if (expiration_is_number_qm && FIXNUM_EQ(expiration,Some_time_ago)) {
	temp_1 = copy_constant_wide_string_given_length(array_constant_25,
		FIX((SI_Long)5L));
	temp_2 = gensym_list_2(temp_1,
		copy_constant_wide_string_given_length(array_constant_13,
		FIX((SI_Long)8L)));
	temp_1 = copy_constant_wide_string_given_length(array_constant_26,
		FIX((SI_Long)9L));
	temp_3 = gensym_list_2(temp_1,
		copy_constant_wide_string_given_length(array_constant_27,
		FIX((SI_Long)4L)));
	temp_1 = copy_constant_wide_string_given_length(array_constant_28,
		FIX((SI_Long)10L));
	temp_1 = gensym_list_3(temp_2,temp_3,gensym_list_2(temp_1,
		copy_constant_wide_string_given_length(array_constant_27,
		FIX((SI_Long)4L))));
    }
    else {
	temp_3 = copy_constant_wide_string_given_length(array_constant_25,
		FIX((SI_Long)5L));
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  managed_number_or_value = ISVREF(variable_or_parameter,
			  (SI_Long)23L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number_or_value,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number_or_value) 
			  != (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number_or_value)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(managed_number_or_value,FIX((SI_Long)0L));
		  else
		      temp_1 = managed_number_or_value;
		  print_constant(2,temp_1,ISVREF(variable_or_parameter,
			  (SI_Long)20L));
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp_4 = gensym_list_2(temp_3,temp_1);
	temp_3 = copy_constant_wide_string_given_length(array_constant_26,
		FIX((SI_Long)9L));
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  managed_number = ISVREF(variable_or_parameter,(SI_Long)21L);
		  if (INLINE_DOUBLE_FLOAT_VECTOR_P(managed_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
			  == (SI_Long)1L)
		      temp_1 = 
			      DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(managed_number,
			      (SI_Long)0L));
		  else if (INLINE_LONG_VECTOR_P(managed_number) != 
			  (SI_Long)0L && 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(managed_number)) 
			  == (SI_Long)1L)
		      temp_1 = aref1(managed_number,FIX((SI_Long)0L));
		  else
		      temp_1 = managed_number;
		  print_constant(2,minus(temp_1,
			  DOUBLE_TO_DOUBLE_FLOAT(DFLOAT_ISAREF_1(G2_time_at_start,
			  (SI_Long)0L))),Qtime_stamp);
		  temp_1 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	temp_2 = gensym_list_2(temp_3,temp_1);
	temp_3 = copy_constant_wide_string_given_length(array_constant_28,
		FIX((SI_Long)10L));
	if (expiration_is_number_qm) {
	    current_wide_string_list = Qdo_not_use;
	    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
		fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
		PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
			2);
		  length_1 = 
			  IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
		  total_length_of_current_wide_string = 
			  FIX(UBYTE_16_ISAREF_1(Current_wide_string,
			  length_1 - (SI_Long)2L) + 
			  ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 
			  - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
		  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
			  1);
		    current_twriting_output_type = Qwide_string;
		    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			    0);
		      print_constant(2,minus(expiration,
			      Gensym_time_at_start),Qtime_stamp);
		      temp_1 = copy_out_current_wide_string();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	}
	else
	    temp_1 = 
		    copy_constant_wide_string_given_length(array_constant_29,
		    FIX((SI_Long)18L));
	temp_1 = gensym_list_3(temp_4,temp_2,gensym_list_2(temp_3,temp_1));
    }
    return make_explanation_table(2,variable_or_parameter,temp_1);
}

static Object Qvar_spot;           /* var-spot */

static Object Kgeneral_description;  /* :general-description */

static Object array_constant_30;   /* # */

/* MAKE-SLOT-VALUE-LISTS-OF-CONTEXT */
Object make_slot_value_lists_of_context varargs_1(int, n)
{
    Object rule, context, cached_frame_serial_number_qm;
    Object use_actual_value_p, environment_description, var_spot, value;
    Object var_name, var_description, result_1, ab_loopvar_, ab_loopvar__1;
    Object gensymed_symbol_1, current_wide_string_list, wide_string_bv16;
    Object current_wide_string, fill_pointer_for_current_wide_string;
    Object total_length_of_current_wide_string, current_twriting_output_type;
    Object temp, thing, xa, ya, temp_2;
    SI_Long index_1, ab_loop_bind_, ab_loop_repeat_, gensymed_symbol;
    SI_Long bv16_length, aref_arg_2, aref_new_value, length_1;
    char temp_1;
    Declare_varargs_nonrelocating;
    Declare_special(5);

    x_note_fn_call(214,216);
    INIT_ARGS_nonrelocating();
    rule = REQUIRED_ARG_nonrelocating();
    context = REQUIRED_ARG_nonrelocating();
    cached_frame_serial_number_qm = REQUIRED_ARG_nonrelocating();
    use_actual_value_p = OPTIONAL_ARG_P_nonrelocating() ? 
	    OPTIONAL_ARG_nonrelocating() : Nil;
    END_ARGS_nonrelocating();
    environment_description = ISVREF(ISVREF(rule,(SI_Long)31L),(SI_Long)4L);
    var_spot = gensym_list_2(Qvar_spot,FIX((SI_Long)0L));
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(rule,(SI_Long)33L));
    ab_loop_repeat_ = IFIX(length(environment_description));
    value = Nil;
    var_name = Nil;
    var_description = Nil;
    result_1 = Nil;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    value = ISVREF(context,index_1);
    gensymed_symbol = index_1 * (SI_Long)2L;
    var_name = FIXNUM_LE(ISVREF(environment_description,(SI_Long)1L),
	    Maximum_in_place_array_size) ? ISVREF(environment_description,
	    gensymed_symbol + IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(environment_description,(gensymed_symbol >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    gensymed_symbol = index_1 * (SI_Long)2L + (SI_Long)1L;
    gensymed_symbol_1 = FIXNUM_LE(ISVREF(environment_description,
	    (SI_Long)1L),Maximum_in_place_array_size) ? 
	    ISVREF(environment_description,gensymed_symbol + 
	    IFIX(Managed_array_index_offset)) : 
	    ISVREF(ISVREF(environment_description,(gensymed_symbol >>  -  
	    - (SI_Long)10L) + (SI_Long)2L),gensymed_symbol & (SI_Long)1023L);
    if (CONSP(gensymed_symbol_1) && EQ(CAR(gensymed_symbol_1),
	    Kgeneral_description)) {
	gensymed_symbol_1 = CDR(gensymed_symbol_1);
	var_description = gensymed_symbol_1;
    }
    else
	var_description = Nil;
    M_SECOND(var_spot) = FIX(index_1);
    current_wide_string_list = Qdo_not_use;
    PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
      PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		2);
	  length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	  total_length_of_current_wide_string = 
		  FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		  (SI_Long)2L) + ((UBYTE_16_ISAREF_1(Current_wide_string,
		  length_1 - (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	  PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		  1);
	    current_twriting_output_type = Qwide_string;
	    PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
		    0);
	      print_var_spot_for_stack_using_name_and_description(3,
		      var_spot,var_name,var_description);
	      temp = copy_out_current_wide_string();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    if (SIMPLE_VECTOR_P(value) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > 
	    (SI_Long)2L) {
	temp_1 = EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector);
	if (temp_1);
	else {
	    thing = ISVREF(value,(SI_Long)1L);
	    temp_1 = SIMPLE_VECTOR_P(thing) ? EQ(ISVREF(thing,(SI_Long)0L),
		    Qg2_defstruct_structure_name_class_description_g2_struct) 
		    : TRUEP(Qnil);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	if (cached_frame_serial_number_qm) {
	    gensymed_symbol_1 = ISVREF(value,(SI_Long)3L);
	    temp_1 = SIMPLE_VECTOR_P(value) ? EQ(ISVREF(value,(SI_Long)1L),
		    Qavailable_frame_vector) : TRUEP(Qnil);
	    if (temp_1);
	    else
		temp_1 = FIXNUMP(gensymed_symbol_1) ? 
			IFIX(gensymed_symbol_1) == (SI_Long)-1L : TRUEP(Nil);
	    if (temp_1);
	    else if (FIXNUMP(cached_frame_serial_number_qm))
		temp_1 = FIXNUMP(gensymed_symbol_1) ? 
			FIXNUM_LT(cached_frame_serial_number_qm,
			gensymed_symbol_1) : TRUEP(T);
	    else if (FIXNUMP(gensymed_symbol_1))
		temp_1 = TRUEP(Nil);
	    else {
		xa = M_CAR(cached_frame_serial_number_qm);
		ya = M_CAR(gensymed_symbol_1);
		temp_1 = FIXNUM_LT(xa,ya);
		if (temp_1);
		else
		    temp_1 = FIXNUM_EQ(xa,ya) ? 
			    FIXNUM_LT(M_CDR(cached_frame_serial_number_qm),
			    M_CDR(gensymed_symbol_1)) : TRUEP(Qnil);
	    }
	}
	else
	    temp_1 = TRUEP(Nil);
	temp_2 = temp_1 ? (use_actual_value_p ? Nil : 
		copy_text_string(array_constant_30)) : use_actual_value_p ?
		 value : tformat_text_string(2,string_constant_68,value);
    }
    else if (use_actual_value_p)
	temp_2 = copy_and_box_element_value_if_necessary(value);
    else {
	current_wide_string_list = Qdo_not_use;
	PUSH_SPECIAL(Current_wide_string_list,current_wide_string_list,4);
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
	  PUSH_SPECIAL(Current_wide_string,current_wide_string,3);
	    fill_pointer_for_current_wide_string = FIX((SI_Long)0L);
	    PUSH_SPECIAL(Fill_pointer_for_current_wide_string,fill_pointer_for_current_wide_string,
		    2);
	      length_1 = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(Current_wide_string));
	      total_length_of_current_wide_string = 
		      FIX(UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)2L) + 
		      ((UBYTE_16_ISAREF_1(Current_wide_string,length_1 - 
		      (SI_Long)1L) & (SI_Long)8191L) << (SI_Long)16L));
	      PUSH_SPECIAL(Total_length_of_current_wide_string,total_length_of_current_wide_string,
		      1);
		current_twriting_output_type = Qwide_string;
		PUSH_SPECIAL(Current_twriting_output_type,current_twriting_output_type,
			0);
		  write_stored_value(value);
		  temp_2 = copy_out_current_wide_string();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
    }
    ab_loopvar__1 = gensym_cons_1(gensym_list_2(temp,temp_2),Nil);
    if (ab_loopvar_)
	M_CDR(ab_loopvar_) = ab_loopvar__1;
    else
	result_1 = ab_loopvar__1;
    ab_loopvar_ = ab_loopvar__1;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    reclaim_gensym_list_1(var_spot);
    return VALUES_1(result_1);
    return VALUES_1(Qnil);
}

/* MAKE-EXPLANATION-NODE-REPRESENTATION */
Object make_explanation_node_representation(variable_parameter_or_cached_explanation)
    Object variable_parameter_or_cached_explanation;
{
    Object x2, sub_class_bit_vector, gensymed_symbol_3, gensymed_symbol_4;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,217);
    if (SIMPLE_VECTOR_P(variable_parameter_or_cached_explanation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable_parameter_or_cached_explanation)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(variable_parameter_or_cached_explanation,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(variable_parameter_or_cached_explanation,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = 
		ISVREF(ISVREF(variable_parameter_or_cached_explanation,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
    if (temp)
	return make_explanation_variable_node(variable_parameter_or_cached_explanation);
    else {
	gensymed_symbol_3 = 
		ISVREF(variable_parameter_or_cached_explanation,(SI_Long)0L);
	gensymed_symbol_3 = 
		ISVREF(ISVREF(getfq_function_no_default(INLINE_SYMBOL_PLIST(gensymed_symbol_3),
		Qtype_description_of_unique_type_name_of_gensym_structure),
		(SI_Long)9L),(SI_Long)27L);
	gensymed_symbol_4 = variable_parameter_or_cached_explanation;
	return VALUES_1(inline_funcall_1(gensymed_symbol_3,gensymed_symbol_4));
    }
}

/* HASH-EXPLANATION-NODE */
Object hash_explanation_node(variable_parameter_or_cached_explanation)
    Object variable_parameter_or_cached_explanation;
{
    Object x2, sub_class_bit_vector, fsn;
    SI_Long superior_class_bit_number, sub_class_vector_index, gensymed_symbol;
    SI_Long gensymed_symbol_1, gensymed_symbol_2;
    char temp;

    x_note_fn_call(214,218);
    if (SIMPLE_VECTOR_P(variable_parameter_or_cached_explanation) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(variable_parameter_or_cached_explanation)) 
	    > (SI_Long)2L &&  
	    !EQ(ISVREF(variable_parameter_or_cached_explanation,
	    (SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(variable_parameter_or_cached_explanation,(SI_Long)1L);
	temp = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	sub_class_bit_vector = 
		ISVREF(ISVREF(variable_parameter_or_cached_explanation,
		(SI_Long)1L),(SI_Long)19L);
	superior_class_bit_number = 
		IFIX(ISVREF(Variable_or_parameter_class_description,
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
	fsn = ISVREF(variable_parameter_or_cached_explanation,(SI_Long)3L);
	if (FIXNUMP(fsn))
	    return VALUES_1(fsn);
	else
	    return VALUES_1(FIXNUM_LOGXOR(M_CAR(fsn),M_CDR(fsn)));
    }
    else
	return sxhash(variable_parameter_or_cached_explanation);
}

static Object Qcreate_exported_cached_explanation_node;  /* create-exported-cached-explanation-node */

/* G2-GET-EXPLANATION-HIERARCHY */
Object g2_get_explanation_hierarchy(variable_or_parameter)
    Object variable_or_parameter;
{
    Object graph, temp;

    x_note_fn_call(214,219);
    graph = create_explanation_graph(variable_or_parameter);
    temp = export_graph_node(3,ISVREF(graph,(SI_Long)3L),
	    SYMBOL_FUNCTION(Qcreate_exported_cached_explanation_node),T);
    delete_frame(ISVREF(graph,(SI_Long)20L));
    reclaim_graph_display_1(graph);
    return VALUES_1(temp);
}

static Object Qframe_flags;        /* frame-flags */

/* TURN-OFF-EXPLANATION-CACHING-FOR-ALL */
Object turn_off_explanation_caching_for_all()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, rule, ab_hash_table_;
    Object ab_tree_form_, ab_node_stack_, ab_current_node_, ab_current_alist_;
    Object ab_entry_cons_, rule_instance, ab_less_than_branch_qm_;
    Object cached_variables, variable_or_parameter, cached_explanation;
    SI_Long svref_new_value, ab_table_length_, ab_index_;
    char temp;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,220);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    rule = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(Qrule);
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
      rule = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
		  (SI_Long)1048576L)) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(rule,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) &  
		  ~(SI_Long)1048576L;
	  ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	  update_representations_of_slot_value(2,rule,Qframe_flags);
	  scope_conses = Scope_conses;
	  ab_hash_table_ = ISVREF(rule,(SI_Long)27L);
	  ab_table_length_ = (SI_Long)0L;
	  ab_index_ = (SI_Long)0L;
	  ab_tree_form_ = Nil;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  rule_instance = Nil;
	  PUSH_SPECIAL(Scope_conses,scope_conses,0);
	    ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	    else if (ab_current_node_) {
		ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		if (ab_current_node_) {
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack_) {
		    ab_current_node_ = M_CAR(ab_node_stack_);
		    ab_node_stack_ = M_CDR(ab_node_stack_);
		}
		if (ab_current_node_) {
		    ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_)) {
	      next_loop_4:
		if ( !(ab_index_ < ab_table_length_))
		    goto end_loop_3;
		ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
		ab_index_ = ab_index_ + (SI_Long)1L;
		if (T) {
		    ab_current_node_ = CDR(ab_tree_form_);
		    if (ab_current_node_) {
			ab_less_than_branch_qm_ = Nil;
		      next_loop_5:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_4;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_5;
		      end_loop_4:;
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
			goto end_loop_3;
		    }
		}
		goto next_loop_4;
	      end_loop_3:;
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_5;
	    rule_instance = M_CDR(ab_entry_cons_);
	    cached_variables = ISVREF(rule_instance,(SI_Long)21L);
	    if (cached_variables) {
		reclaim_evaluation_variables_list(cached_variables);
		SVREF(rule_instance,FIX((SI_Long)21L)) = Nil;
	    }
	    goto next_loop_2;
	  end_loop_5:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    variable_or_parameter = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qvariable_or_parameter);
    next_loop_6:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_7:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_6;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_6;
	  goto next_loop_7;
	end_loop_6:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_7;
      variable_or_parameter = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,(SI_Long)4L)) 
	      & (SI_Long)1048576L)) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(variable_or_parameter,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(variable_or_parameter,
		  (SI_Long)4L)) &  ~(SI_Long)1048576L;
	  ISVREF(variable_or_parameter,(SI_Long)4L) = FIX(svref_new_value);
	  update_representations_of_slot_value(2,variable_or_parameter,
		  Qframe_flags);
	  cached_explanation = 
		  get_lookup_slot_value_given_default(variable_or_parameter,
		  Qg2_internal_cached_explanation,Nil);
	  if (cached_explanation) {
	      reclaim_cached_explanation(cached_explanation);
	      set_non_savable_lookup_slot_value(variable_or_parameter,
		      Qg2_internal_cached_explanation,Nil);
	  }
      }
      goto next_loop_6;
    end_loop_7:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

/* TURN-ON-EXPLANATION-CACHING-FOR-ALL */
Object turn_on_explanation_caching_for_all()
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, rule;
    Object variable_or_parameter;
    SI_Long svref_new_value;
    char temp;
    Declare_special(1);
    Object result;

    x_note_fn_call(214,221);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    rule = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qrule);
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
      rule = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(rule,(SI_Long)4L)) & 
	      (SI_Long)1048576L))) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(rule,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(rule,(SI_Long)4L)) | (SI_Long)1048576L;
	  ISVREF(rule,(SI_Long)4L) = FIX(svref_new_value);
	  update_representations_of_slot_value(2,rule,Qframe_flags);
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    variable_or_parameter = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qvariable_or_parameter);
    next_loop_2:
      if ( !TRUEP(ab_loopvar__1)) {
	next_loop_3:
	  if ( !TRUEP(ab_loopvar_))
	      goto end_loop_2;
	  ab_loopvar__1 = 
		  lookup_kb_specific_property_value(M_CAR(ab_loopvar_),
		  Instances_specific_to_this_class_kbprop);
	  ab_loopvar_ = M_CDR(ab_loopvar_);
	  if (ab_loopvar__1)
	      goto end_loop_2;
	  goto next_loop_3;
	end_loop_2:
	  temp =  !TRUEP(ab_loopvar__1);
      }
      else
	  temp = TRUEP(Nil);
      if (temp)
	  goto end_loop_3;
      variable_or_parameter = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if ( !((SI_Long)0L != (IFIX(ISVREF(variable_or_parameter,
	      (SI_Long)4L)) & (SI_Long)1048576L))) {
	  if (Noting_changes_to_kb_p)
	      note_change_to_block_1(variable_or_parameter,Qframe_flags);
	  svref_new_value = IFIX(ISVREF(variable_or_parameter,
		  (SI_Long)4L)) | (SI_Long)1048576L;
	  ISVREF(variable_or_parameter,(SI_Long)4L) = FIX(svref_new_value);
	  update_representations_of_slot_value(2,variable_or_parameter,
		  Qframe_flags);
      }
      goto next_loop_2;
    end_loop_3:
      result = VALUES_1(Qnil);
    POP_SPECIAL();
    return result;
}

Object The_type_description_of_frame_display = UNBOUND;

Object Chain_of_available_frame_displays = UNBOUND;

Object Frame_display_count = UNBOUND;

/* FRAME-DISPLAY-STRUCTURE-MEMORY-USAGE */
Object frame_display_structure_memory_usage()
{
    Object temp;

    x_note_fn_call(214,222);
    temp = Frame_display_count;
    temp = FIXNUM_TIMES(temp,bytes_per_simple_vector(FIX((SI_Long)8L)));
    return VALUES_1(temp);
}

/* OUTSTANDING-FRAME-DISPLAY-COUNT */
Object outstanding_frame_display_count()
{
    Object def_structure_frame_display_variable, count_1;
    SI_Long gensymed_symbol, gensymed_symbol_1;

    x_note_fn_call(214,223);
    gensymed_symbol = IFIX(Frame_display_count);
    def_structure_frame_display_variable = Chain_of_available_frame_displays;
    count_1 = FIX((SI_Long)0L);
  next_loop:
    if ( !TRUEP(def_structure_frame_display_variable))
	goto end_loop;
    def_structure_frame_display_variable = 
	    ISVREF(def_structure_frame_display_variable,(SI_Long)0L);
    count_1 = FIXNUM_ADD1(count_1);
    goto next_loop;
  end_loop:
    gensymed_symbol_1 = IFIX(count_1);
    goto end_1;
    gensymed_symbol_1 = IFIX(Qnil);
  end_1:;
    return VALUES_1(FIX(gensymed_symbol - gensymed_symbol_1));
}

/* RECLAIM-FRAME-DISPLAY-1 */
Object reclaim_frame_display_1(frame_display)
    Object frame_display;
{
    Object old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,224);
    inline_note_reclaim_cons(frame_display,Nil);
    old_structure_being_reclaimed = Structure_being_reclaimed;
    Structure_being_reclaimed = frame_display;
    reclaim_frame_display_alist(ISVREF(frame_display,(SI_Long)4L));
    SVREF(frame_display,FIX((SI_Long)4L)) = Nil;
    Structure_being_reclaimed = old_structure_being_reclaimed;
    svref_new_value = Chain_of_available_frame_displays;
    SVREF(frame_display,FIX((SI_Long)0L)) = svref_new_value;
    Chain_of_available_frame_displays = frame_display;
    return VALUES_1(Nil);
}

/* RECLAIM-STRUCTURE-FOR-FRAME-DISPLAY */
Object reclaim_structure_for_frame_display(frame_display)
    Object frame_display;
{
    x_note_fn_call(214,225);
    return reclaim_frame_display_1(frame_display);
}

static Object Qg2_defstruct_structure_name_frame_display_g2_struct;  /* g2-defstruct-structure-name::frame-display-g2-struct */

/* MAKE-PERMANENT-FRAME-DISPLAY-STRUCTURE-INTERNAL */
Object make_permanent_frame_display_structure_internal()
{
    Object def_structure_frame_display_variable, frame_display_count_new_value;
    Object defstruct_g2_frame_display_variable, the_array;
    SI_Long gensymed_symbol, i, ab_loop_bind_;
    XDeclare_area(1);

    x_note_fn_call(214,226);
    def_structure_frame_display_variable = Nil;
    frame_display_count_new_value = FIXNUM_ADD1(Frame_display_count);
    Frame_display_count = frame_display_count_new_value;
    if (PUSH_AREA(Dynamic_area,0)) {
	defstruct_g2_frame_display_variable = Nil;
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
	defstruct_g2_frame_display_variable = the_array;
	SVREF(defstruct_g2_frame_display_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_frame_display_g2_struct;
	SVREF(defstruct_g2_frame_display_variable,FIX((SI_Long)1L)) = Nil;
	def_structure_frame_display_variable = 
		defstruct_g2_frame_display_variable;
    }
    POP_AREA(0);
    return VALUES_1(def_structure_frame_display_variable);
}

/* MAKE-FRAME-DISPLAY-1 */
Object make_frame_display_1()
{
    Object def_structure_frame_display_variable;

    x_note_fn_call(214,227);
    def_structure_frame_display_variable = Chain_of_available_frame_displays;
    if (def_structure_frame_display_variable) {
	Chain_of_available_frame_displays = 
		ISVREF(def_structure_frame_display_variable,(SI_Long)0L);
	SVREF(def_structure_frame_display_variable,FIX((SI_Long)0L)) = 
		Qg2_defstruct_structure_name_frame_display_g2_struct;
    }
    else
	def_structure_frame_display_variable = 
		make_permanent_frame_display_structure_internal();
    inline_note_allocate_cons(def_structure_frame_display_variable,Nil);
    SVREF(def_structure_frame_display_variable,FIX((SI_Long)1L)) = Nil;
    SVREF(def_structure_frame_display_variable,FIX((SI_Long)2L)) = Nil;
    SVREF(def_structure_frame_display_variable,FIX((SI_Long)3L)) = Nil;
    SVREF(def_structure_frame_display_variable,FIX((SI_Long)4L)) = Nil;
    ISVREF(def_structure_frame_display_variable,(SI_Long)5L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_frame_display_variable,(SI_Long)6L) = 
	    FIX((SI_Long)0L);
    ISVREF(def_structure_frame_display_variable,(SI_Long)7L) = 
	    FIX((SI_Long)0L);
    return VALUES_1(def_structure_frame_display_variable);
}

/* RECLAIM-FRAME-DISPLAY-ALIST */
Object reclaim_frame_display_alist(alist)
    Object alist;
{
    Object item, ab_loop_list_;

    x_note_fn_call(214,228);
    item = Nil;
    ab_loop_list_ = alist;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    item = M_CAR(ab_loop_list_);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    reclaim_frame_serial_number(CDDR(item));
    reclaim_gensym_cons_1(CDR(item));
    reclaim_gensym_cons_1(item);
    goto next_loop;
  end_loop:;
    return reclaim_gensym_list_1(alist);
}

static Object Qdynamic_temporary_workspace;  /* dynamic-temporary-workspace */

/* CREATE-FRAME-DISPLAY */
Object create_frame_display()
{
    Object frame_display, workspace;

    x_note_fn_call(214,229);
    frame_display = make_frame_display_1();
    workspace = make_workspace(6,Qdynamic_temporary_workspace,Nil,Nil,
	    FIX((SI_Long)30L),Nil,Nil);
    SVREF(frame_display,FIX((SI_Long)3L)) = workspace;
    return VALUES_1(frame_display);
}

/* SHOW-FRAME-DISPLAY */
Object show_frame_display(frame_display)
    Object frame_display;
{
    x_note_fn_call(214,230);
    return put_workspace_on_pane_function(ISVREF(frame_display,
	    (SI_Long)3L),Current_workstation_detail_pane,Qleft,Qtop,T,
	    FIX((SI_Long)11L),Nil,Nil,Nil,Nil,Nil,Nil,Nil);
}

/* ADD-THING-TO-FRAME-DISPLAY */
Object add_thing_to_frame_display(thing,frame_representation,frame_display,
	    check_for_duplicate_add_qm)
    Object thing, frame_representation, frame_display;
    Object check_for_duplicate_add_qm;
{
    Object workspace, frame_display_alist, current_y, gensymed_symbol, temp;
    Object svref_new_value;
    SI_Long current_x, gensymed_symbol_1, gensymed_symbol_2, incff_1_arg;
    SI_Long current_y_new_value;

    x_note_fn_call(214,231);
    workspace = ISVREF(frame_display,(SI_Long)3L);
    frame_display_alist = ISVREF(frame_display,(SI_Long)4L);
    current_y = ISVREF(frame_display,(SI_Long)6L);
    current_x = (SI_Long)0L;
    if (check_for_duplicate_add_qm && assq_function(thing,frame_display_alist))
	return VALUES_1(Nil);
    else {
	add_to_workspace(6,frame_representation,workspace,FIX(current_x),
		current_y,T,T);
	gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)3L) : FIX((SI_Long)0L);
	gensymed_symbol_1 = IFIX(gensymed_symbol);
	gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
	gensymed_symbol_2 = (SI_Long)10L;
	incff_1_arg = gensymed_symbol_1 + gensymed_symbol_2;
	current_y_new_value = IFIX(current_y) + incff_1_arg;
	current_y = FIX(current_y_new_value);
	SVREF(frame_display,FIX((SI_Long)6L)) = current_y;
	if (ISVREF(frame_display,(SI_Long)4L)) {
	    temp = ISVREF(frame_display,(SI_Long)4L);
	    svref_new_value = nconc2(temp,
		    gensym_cons_1(gensym_cons_1(thing,
		    gensym_cons_1(frame_representation,
		    copy_frame_serial_number(Current_frame_serial_number))),
		    Nil));
	}
	else
	    svref_new_value = gensym_cons_1(gensym_cons_1(thing,
		    gensym_cons_1(frame_representation,
		    copy_frame_serial_number(Current_frame_serial_number))),
		    Nil);
	SVREF(frame_display,FIX((SI_Long)4L)) = svref_new_value;
	return VALUES_1(thing);
    }
}

/* REMOVE-THING-FROM-FRAME-DISPLAY */
Object remove_thing_from_frame_display(frame,frame_display)
    Object frame, frame_display;
{
    Object previous_cons_qm, cons_qm, temp, entry, frame_representation;
    Object frame_representation_fsn, gensymed_symbol, xa, ya;
    Object frame_representation_qm, frame_representation_height_qm;
    Object deletion_count, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, svref_new_value;
    char temp_1, deleted_last_cons_qm;

    x_note_fn_call(214,232);
    previous_cons_qm = Nil;
    cons_qm = ISVREF(frame_display,(SI_Long)4L);
  next_loop:
    if (cons_qm) {
	temp = FIRST(cons_qm);
	temp_1 =  !EQ(frame,CAR(temp));
    }
    else
	temp_1 = TRUEP(Nil);
    if ( !temp_1)
	goto end_loop;
    previous_cons_qm = cons_qm;
    cons_qm = CDR(cons_qm);
    goto next_loop;
  end_loop:
    if (cons_qm) {
	entry = CAR(cons_qm);
	frame_representation = CADR(entry);
	frame_representation_fsn = CDDR(entry);
	gensymed_symbol = ISVREF(frame_representation,(SI_Long)3L);
	temp_1 = SIMPLE_VECTOR_P(frame_representation) ? 
		EQ(ISVREF(frame_representation,(SI_Long)1L),
		Qavailable_frame_vector) : TRUEP(Qnil);
	if (temp_1);
	else
	    temp_1 = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		    (SI_Long)-1L : TRUEP(Nil);
	if (temp_1);
	else if (FIXNUMP(frame_representation_fsn))
	    temp_1 = FIXNUMP(gensymed_symbol) ? 
		    FIXNUM_LT(frame_representation_fsn,gensymed_symbol) : 
		    TRUEP(T);
	else if (FIXNUMP(gensymed_symbol))
	    temp_1 = TRUEP(Nil);
	else {
	    xa = M_CAR(frame_representation_fsn);
	    ya = M_CAR(gensymed_symbol);
	    temp_1 = FIXNUM_LT(xa,ya);
	    if (temp_1);
	    else
		temp_1 = FIXNUM_EQ(xa,ya) ? 
			FIXNUM_LT(M_CDR(frame_representation_fsn),
			M_CDR(gensymed_symbol)) : TRUEP(Qnil);
	}
	frame_representation_qm =  !temp_1 ? frame_representation : Nil;
	if (frame_representation_qm) {
	    gensymed_symbol = ISVREF(frame_representation_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)3L) : FIX((SI_Long)0L);
	    gensymed_symbol_1 = IFIX(gensymed_symbol);
	    gensymed_symbol = ISVREF(frame_representation_qm,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    gensymed_symbol_2 = IFIX(gensymed_symbol);
	    frame_representation_height_qm = FIX(gensymed_symbol_1 - 
		    gensymed_symbol_2);
	}
	else
	    frame_representation_height_qm = Nil;
	deleted_last_cons_qm =  !TRUEP(CDR(cons_qm));
	deletion_count = ISVREF(frame_display,(SI_Long)7L);
	if (previous_cons_qm) {
	    temp_2 = CDR(cons_qm);
	    M_CDR(previous_cons_qm) = temp_2;
	}
	else {
	    temp_2 = CDR(cons_qm);
	    SVREF(frame_display,FIX((SI_Long)4L)) = temp_2;
	}
	reclaim_frame_serial_number(frame_representation_fsn);
	reclaim_gensym_cons_1(CDR(entry));
	reclaim_gensym_cons_1(entry);
	reclaim_gensym_cons_1(cons_qm);
	if (frame_representation_qm)
	    delete_frame(frame_representation_qm);
	deletion_count = FIXNUM_ADD1(deletion_count);
	if (IFIX(length(ISVREF(frame_display,(SI_Long)4L))) <= (SI_Long)2L) {
	    update_frame_display(frame_display,Nil,T);
	    ISVREF(frame_display,(SI_Long)7L) = FIX((SI_Long)0L);
	}
	else if (IFIX(deletion_count) > (SI_Long)3L) {
	    update_frame_display(frame_display,T,T);
	    ISVREF(frame_display,(SI_Long)7L) = FIX((SI_Long)0L);
	}
	else if (deleted_last_cons_qm && frame_representation_height_qm) {
	    svref_new_value = IFIX(FIXNUM_MINUS(ISVREF(frame_display,
		    (SI_Long)6L),frame_representation_height_qm)) - 
		    (SI_Long)10L;
	    ISVREF(frame_display,(SI_Long)6L) = FIX(svref_new_value);
	}
	else
	    SVREF(frame_display,FIX((SI_Long)7L)) = deletion_count;
    }
    return VALUES_1( ! !TRUEP(cons_qm) ? T : Nil);
    return VALUES_1(Qnil);
}

/* UPDATE-FRAME-DISPLAY */
Object update_frame_display(frame_display,redisplay_qm,shrink_wrap_qm)
    Object frame_display, redisplay_qm, shrink_wrap_qm;
{
    Object workspace, current_y, frame_representation, ab_loop_list_;
    Object ab_loop_desetq_, temp, gensymed_symbol, temp_2;
    SI_Long current_x, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3;
    char temp_1;

    x_note_fn_call(214,233);
    workspace = ISVREF(frame_display,(SI_Long)3L);
    current_x = (SI_Long)0L;
    current_y = ISVREF(frame_display,(SI_Long)5L);
    frame_representation = Nil;
    ab_loop_list_ = validate_and_update_frame_display_alist(frame_display);
    ab_loop_desetq_ = Nil;
  next_loop:
    if ( !TRUEP(ab_loop_list_))
	goto end_loop;
    ab_loop_desetq_ = M_CAR(ab_loop_list_);
    temp = CDR(ab_loop_desetq_);
    frame_representation = CAR(temp);
    ab_loop_list_ = M_CDR(ab_loop_list_);
    if (frame_representation && redisplay_qm) {
	gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	temp_1 =  !(current_x == IFIX(gensymed_symbol));
	if (temp_1);
	else {
	    temp = current_y;
	    gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
	    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		    (SI_Long)1L) : FIX((SI_Long)0L);
	    temp_1 =  !FIXNUM_EQ(temp,gensymed_symbol);
	}
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	update_images_of_block(frame_representation,T,T);
	temp = frame_representation;
	gensymed_symbol_1 = current_x;
	gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)0L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	temp_2 = FIX(gensymed_symbol_1 - gensymed_symbol_2);
	gensymed_symbol_1 = IFIX(current_y);
	gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
	gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
		(SI_Long)1L) : FIX((SI_Long)0L);
	gensymed_symbol_2 = IFIX(gensymed_symbol);
	shift_block(temp,temp_2,FIX(gensymed_symbol_1 - gensymed_symbol_2));
	update_images_of_block(frame_representation,Nil,T);
    }
    gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)3L) : FIX((SI_Long)0L);
    gensymed_symbol_1 = IFIX(gensymed_symbol);
    gensymed_symbol = ISVREF(frame_representation,(SI_Long)14L);
    gensymed_symbol = gensymed_symbol ? ISVREF(gensymed_symbol,
	    (SI_Long)1L) : FIX((SI_Long)0L);
    gensymed_symbol_2 = IFIX(gensymed_symbol);
    gensymed_symbol_1 = gensymed_symbol_1 - gensymed_symbol_2;
    gensymed_symbol_2 = (SI_Long)10L;
    gensymed_symbol_3 = IFIX(current_y);
    current_y = FIX(gensymed_symbol_1 + gensymed_symbol_2 + gensymed_symbol_3);
    goto next_loop;
  end_loop:
    SVREF(frame_display,FIX((SI_Long)6L)) = current_y;
    if (shrink_wrap_qm && ISVREF(frame_display,(SI_Long)4L))
	shrink_wrap_workspace(workspace);
    return VALUES_1(Qnil);
}

/* VALIDATE-AND-UPDATE-FRAME-DISPLAY-ALIST */
Object validate_and_update_frame_display_alist(frame_display)
    Object frame_display;
{
    Object head, element_to_check, gensymed_symbol, x, y, xa, ya, temp_1;
    Object gensym_list, gensym_list_tail, gensym_cons, temp_2;
    char temp;

    x_note_fn_call(214,234);
    head = Nil;
    element_to_check = ISVREF(frame_display,(SI_Long)4L);
  next_loop:
    if ( !TRUEP(element_to_check))
	goto end_loop;
    gensymed_symbol = ISVREF(CADAR(element_to_check),(SI_Long)3L);
    x = CADAR(element_to_check);
    temp = SIMPLE_VECTOR_P(x) ? EQ(ISVREF(x,(SI_Long)1L),
	    Qavailable_frame_vector) : TRUEP(Qnil);
    if (temp);
    else
	temp = FIXNUMP(gensymed_symbol) ? IFIX(gensymed_symbol) == 
		(SI_Long)-1L : TRUEP(Nil);
    if (temp);
    else {
	x = gensymed_symbol;
	y = CDDAR(element_to_check);
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
    if (temp) {
	if ( !TRUEP(head)) {
	    temp_1 = CDR(element_to_check);
	    SVREF(frame_display,FIX((SI_Long)4L)) = temp_1;
	}
	else {
	    temp_1 = CDR(element_to_check);
	    M_CDR(head) = temp_1;
	}
	reclaim_frame_serial_number(CDDAR(element_to_check));
	gensym_list = CAR(element_to_check);
	gensym_list_tail = CDAR(element_to_check);
	if (gensym_list &&  !((SI_Long)0L == inline_debugging_consing())) {
	    gensym_cons = gensym_list;
	  next_loop_1:
	    inline_note_reclaim_cons(gensym_cons,Qab_gensym);
	    if (EQ(gensym_cons,gensym_list_tail))
		goto end_1;
	    else if ( !TRUEP(gensym_cons))
		goto end_1;
	    else
		gensym_cons = CDR(gensym_cons);
	    goto next_loop_1;
	  end_loop_1:
	  end_1:;
	}
	temp_1 = Available_gensym_conses;
	M_CDR(gensym_list_tail) = temp_1;
	Available_gensym_conses = gensym_list;
	temp_2 = CDR(element_to_check);
	reclaim_gensym_cons_1(element_to_check);
	element_to_check = temp_2;
    }
    else {
	head = element_to_check;
	element_to_check = CDR(element_to_check);
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(ISVREF(frame_display,(SI_Long)4L));
}

/* DELETE-AND-RECLAIM-FRAME-DISPLAY */
Object delete_and_reclaim_frame_display(frame_display,delete_workspace_qm)
    Object frame_display, delete_workspace_qm;
{
    x_note_fn_call(214,235);
    if (delete_workspace_qm)
	delete_frame(ISVREF(frame_display,(SI_Long)3L));
    return reclaim_frame_display_1(frame_display);
}

Object Available_dynamic_rule_displays_hash_vector_43_vectors = UNBOUND;

Object Count_of_dynamic_rule_displays_hash_vector_43_vectors = UNBOUND;

/* DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object dynamic_rule_displays_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(214,236);
    temp = Count_of_dynamic_rule_displays_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTORS */
Object out_dynamic_rule_displays_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(214,237);
    temp = 
	    FIXNUM_MINUS(Count_of_dynamic_rule_displays_hash_vector_43_vectors,
	    length(Available_dynamic_rule_displays_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_dynamic_rule_displays_hash_vector_43_vector_internal()
{
    Object count_of_dynamic_rule_displays_hash_vector_43_vectors_new_value;
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(214,238);
    count_of_dynamic_rule_displays_hash_vector_43_vectors_new_value = 
	    FIXNUM_ADD1(Count_of_dynamic_rule_displays_hash_vector_43_vectors);
    Count_of_dynamic_rule_displays_hash_vector_43_vectors = 
	    count_of_dynamic_rule_displays_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR */
Object make_dynamic_rule_displays_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(214,239);
    if (Available_dynamic_rule_displays_hash_vector_43_vectors) {
	temp = M_CAR(Available_dynamic_rule_displays_hash_vector_43_vectors);
	temp_1 = M_CDR(Available_dynamic_rule_displays_hash_vector_43_vectors);
	inline_note_reclaim_cons(Available_dynamic_rule_displays_hash_vector_43_vectors,
		Qab_gensym);
	cdr_arg = Available_dynamic_rule_displays_hash_vector_43_vectors;
	cdr_new_value = Available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	Available_gensym_conses = 
		Available_dynamic_rule_displays_hash_vector_43_vectors;
	Available_dynamic_rule_displays_hash_vector_43_vectors = temp_1;
    }
    else
	temp = 
		make_permanent_dynamic_rule_displays_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR */
Object reclaim_dynamic_rule_displays_hash_vector(dynamic_rule_displays_hash_vector_43_vector)
    Object dynamic_rule_displays_hash_vector_43_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(214,240);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = dynamic_rule_displays_hash_vector_43_vector;
    cdr_new_value = Available_dynamic_rule_displays_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    Available_dynamic_rule_displays_hash_vector_43_vectors = gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-DYNAMIC-RULE-DISPLAYS-TREE-FOR-HASH-LEAVES */
Object reclaim_dynamic_rule_displays_tree_for_hash_leaves(dynamic_rule_displays_tree_for_hash_binary_tree)
    Object dynamic_rule_displays_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(214,241);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(dynamic_rule_displays_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(dynamic_rule_displays_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(dynamic_rule_displays_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = ISVREF(dynamic_rule_displays_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    reclaim_binary_tree_element_1(dynamic_rule_displays_tree_for_hash_binary_tree);
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
	reclaim_dynamic_rule_displays_tree_for_hash_leaves(less_than_branch_qm);
	dynamic_rule_displays_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	dynamic_rule_displays_tree_for_hash_binary_tree = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-DYNAMIC-RULE-DISPLAYS-TREE */
Object clear_dynamic_rule_displays_tree(dynamic_rule_displays_tree_for_hash_binary_tree)
    Object dynamic_rule_displays_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(214,242);
    element_qm = CDR(dynamic_rule_displays_tree_for_hash_binary_tree);
    if (element_qm) {
	reclaim_dynamic_rule_displays_tree_for_hash_leaves(element_qm);
	M_CDR(dynamic_rule_displays_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(dynamic_rule_displays_tree_for_hash_binary_tree);
}

static Object Qdynamic_rule_displays_tree_for_hash;  /* dynamic-rule-displays-tree-for-hash */

/* MAKE-DYNAMIC-RULE-DISPLAYS */
Object make_dynamic_rule_displays()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(214,243);
    new_vector = make_dynamic_rule_displays_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qdynamic_rule_displays_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-DYNAMIC-RULE-DISPLAYS */
Object flatten_dynamic_rule_displays(dynamic_rule_displays_hash_table)
    Object dynamic_rule_displays_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(214,244);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(dynamic_rule_displays_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-DYNAMIC-RULE-DISPLAYS */
Object clear_dynamic_rule_displays(dynamic_rule_displays_hash_table)
    Object dynamic_rule_displays_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(214,245);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_dynamic_rule_displays_tree(ISVREF(dynamic_rule_displays_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-DYNAMIC-RULE-DISPLAYS */
Object reclaim_dynamic_rule_displays(dynamic_rule_displays_hash_table)
    Object dynamic_rule_displays_hash_table;
{
    Object dynamic_rule_displays_tree_for_hash_binary_tree, element_qm;
    Object cdr_new_value, temp;
    SI_Long index_1;

    x_note_fn_call(214,246);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    dynamic_rule_displays_tree_for_hash_binary_tree = 
	    ISVREF(dynamic_rule_displays_hash_table,index_1);
    element_qm = M_CDR(dynamic_rule_displays_tree_for_hash_binary_tree);
    if (element_qm)
	reclaim_dynamic_rule_displays_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(dynamic_rule_displays_tree_for_hash_binary_tree,
	    Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(dynamic_rule_displays_tree_for_hash_binary_tree) = cdr_new_value;
    Available_gensym_conses = dynamic_rule_displays_tree_for_hash_binary_tree;
    ISVREF(dynamic_rule_displays_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_dynamic_rule_displays_hash_vector(dynamic_rule_displays_hash_table);
    return VALUES_1(temp);
}

Object Dynamic_rule_display_hash_table = UNBOUND;

static Object Qreclaim_dynamic_rule_display;  /* reclaim-dynamic-rule-display */

/* CREATE-DYNAMIC-RULE-DISPLAY */
Object create_dynamic_rule_display(rule_or_object_frame)
    Object rule_or_object_frame;
{
    Object frame_display, svref_arg_1, temp, temp_2, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_5;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_1, gensymed_symbol_4;

    x_note_fn_call(214,247);
    frame_display = create_frame_display();
    svref_arg_1 = ISVREF(frame_display,(SI_Long)3L);
    ISVREF(svref_arg_1,(SI_Long)28L) = frame_display;
    SVREF(frame_display,FIX((SI_Long)1L)) = Qreclaim_dynamic_rule_display;
    SVREF(frame_display,FIX((SI_Long)2L)) = rule_or_object_frame;
    gensymed_symbol = IFIX(frame_hash_function(rule_or_object_frame));
    temp = Dynamic_rule_display_hash_table;
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = IFIX(frame_hash_function(rule_or_object_frame));
    temp_2 = Dynamic_rule_display_hash_table;
    temp_1 = gensymed_symbol_1 % (SI_Long)43L;
    temp_2 = SVREF(temp_2,FIX(temp_1));
    gensymed_symbol_2 = CDR(temp_2);
    gensymed_symbol_3 = rule_or_object_frame;
    gensymed_symbol_4 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_2))
	goto end_loop;
    gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol_2,(SI_Long)0L));
    if (gensymed_symbol_1 < gensymed_symbol_4)
	gensymed_symbol_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
    else if (gensymed_symbol_1 > gensymed_symbol_4)
	gensymed_symbol_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
    else {
	gensymed_symbol_2 = ISVREF(gensymed_symbol_2,(SI_Long)3L);
	gensymed_symbol_5 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_2))
	    goto end_loop_1;
	gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol_2));
	if (EQ(gensymed_symbol_3,gensymed_symbol_5)) {
	    temp_2 = M_CDR(M_CAR(gensymed_symbol_2));
	    goto end_1;
	}
	gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
	goto next_loop_1;
      end_loop_1:
	temp_2 = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp_2 = Qnil;
  end_2:;
    set_balanced_binary_tree_entry(temp,Qeq,Nil,T,rule_or_object_frame,
	    FIX(gensymed_symbol),gensym_cons_1(frame_display,temp_2));
    return VALUES_1(frame_display);
}

/* RECLAIM-DYNAMIC-RULE-DISPLAY */
Object reclaim_dynamic_rule_display(frame_display)
    Object frame_display;
{
    Object object_or_rule_frame, temp, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_4, new_display_list, svref_arg_1;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(214,248);
    object_or_rule_frame = ISVREF(frame_display,(SI_Long)2L);
    gensymed_symbol = IFIX(frame_hash_function(object_or_rule_frame));
    temp = Dynamic_rule_display_hash_table;
    temp_1 = gensymed_symbol % (SI_Long)43L;
    temp = SVREF(temp,FIX(temp_1));
    gensymed_symbol_1 = CDR(temp);
    gensymed_symbol_2 = object_or_rule_frame;
    gensymed_symbol_3 = (SI_Long)0L;
  next_loop:
    if ( !TRUEP(gensymed_symbol_1))
	goto end_loop;
    gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
    if (gensymed_symbol < gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
    else if (gensymed_symbol > gensymed_symbol_3)
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
    else {
	gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	gensymed_symbol_4 = Nil;
      next_loop_1:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_1;
	gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
	    temp = M_CDR(M_CAR(gensymed_symbol_1));
	    goto end_1;
	}
	gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	goto next_loop_1;
      end_loop_1:
	temp = Qnil;
      end_1:;
	goto end_2;
    }
    goto next_loop;
  end_loop:
    temp = Qnil;
  end_2:;
    new_display_list = delete_gensym_element_1(frame_display,temp);
    if (new_display_list) {
	gensymed_symbol = IFIX(frame_hash_function(object_or_rule_frame));
	temp = Dynamic_rule_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	set_balanced_binary_tree_entry(SVREF(temp,FIX(temp_1)),Qeq,Nil,T,
		object_or_rule_frame,FIX(gensymed_symbol),new_display_list);
    }
    else {
	gensymed_symbol = IFIX(frame_hash_function(object_or_rule_frame));
	temp = Dynamic_rule_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		object_or_rule_frame,SVREF(temp,FIX(temp_1)),
		FIX(gensymed_symbol));
    }
    cleanup_dynamic_rule_display(frame_display);
    svref_arg_1 = ISVREF(frame_display,(SI_Long)3L);
    ISVREF(svref_arg_1,(SI_Long)28L) = Nil;
    return reclaim_frame_display_1(frame_display);
}

/* DELETE-DYNAMIC-RULE-DISPLAYS-FOR-RULE-OR-OBJECT */
Object delete_dynamic_rule_displays_for_rule_or_object(object_or_rule)
    Object object_or_rule;
{
    Object rule_display, temp, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_4, ab_loop_list_, rule_displays, ab_loopvar_;
    Object ab_loopvar__1, display, display_workspace;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(214,249);
    if (Dynamic_rule_display_hash_table) {
	rule_display = Nil;
	gensymed_symbol = IFIX(frame_hash_function(object_or_rule));
	temp = Dynamic_rule_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_1));
	gensymed_symbol_1 = CDR(temp);
	gensymed_symbol_2 = object_or_rule;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		ab_loop_list_ = M_CDR(M_CAR(gensymed_symbol_1));
		goto end_1;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    ab_loop_list_ = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	ab_loop_list_ = Qnil;
      end_2:;
	rule_displays = Nil;
	ab_loopvar_ = Nil;
	ab_loopvar__1 = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	rule_display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	ab_loopvar__1 = gensym_cons_1(rule_display,Nil);
	if (ab_loopvar_)
	    M_CDR(ab_loopvar_) = ab_loopvar__1;
	else
	    rule_displays = ab_loopvar__1;
	ab_loopvar_ = ab_loopvar__1;
	goto next_loop_2;
      end_loop_2:
	display = Nil;
	ab_loop_list_ = rule_displays;
	display_workspace = Nil;
      next_loop_3:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_3;
	display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	display_workspace = ISVREF(display,(SI_Long)3L);
	if (display_workspace)
	    delete_frame(display_workspace);
	goto next_loop_3;
      end_loop_3:;
	reclaim_gensym_list_1(rule_displays);
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object array_constant_31;   /* # */

static Object string_constant_150;  /* "Invocation with no generic bindings." */

/* MAKE-EXPLANATION-RULE-INSTANCE-REPRESENTATION */
Object make_explanation_rule_instance_representation(rule_instance,
	    display_rule_frame_qm)
    Object rule_instance, display_rule_frame_qm;
{
    Object rule, serial_number, context_list;

    x_note_fn_call(214,250);
    rule = ISVREF(rule_instance,(SI_Long)8L);
    serial_number = copy_frame_serial_number(ISVREF(rule_instance,
	    (SI_Long)11L));
    context_list = make_slot_value_lists_of_context(3,rule,
	    ISVREF(rule_instance,(SI_Long)2L),serial_number);
    reclaim_frame_serial_number(serial_number);
    if (display_rule_frame_qm)
	return make_explanation_table(2,rule,context_list);
    else if (context_list)
	return make_explanation_table(2,Nil,
		gensym_cons_1(copy_constant_wide_string_given_length(array_constant_31,
		FIX((SI_Long)35L)),context_list));
    else
	return make_explanation_table(2,Nil,
		gensym_cons_1(copy_text_string(string_constant_150),Nil));
}

static Object Qdynamic_display_delay_in_milliseconds;  /* dynamic-display-delay-in-milliseconds */

/* ADD-RULE-INSTANCE-TO-DYNAMIC-RULE-DISPLAYS */
Object add_rule_instance_to_dynamic_rule_displays(rule_instance)
    Object rule_instance;
{
    Object rule, temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    Object frame_displays, update_made_qm, display, ab_loop_list_;
    Object instance_representation_qm;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(214,251);
    if (Dynamic_rule_display_hash_table) {
	rule = ISVREF(rule_instance,(SI_Long)8L);
	gensymed_symbol = IFIX(frame_hash_function(rule));
	temp = Dynamic_rule_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_1));
	gensymed_symbol_1 = CDR(temp);
	gensymed_symbol_2 = rule;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		frame_displays = M_CDR(M_CAR(gensymed_symbol_1));
		goto end_1;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    frame_displays = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	frame_displays = Qnil;
      end_2:;
	update_made_qm = Nil;
	display = Nil;
	ab_loop_list_ = frame_displays;
	instance_representation_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	instance_representation_qm =  !TRUEP(assq_function(rule_instance,
		ISVREF(display,(SI_Long)4L))) ? 
		make_explanation_rule_instance_representation(rule_instance,
		Nil) : Nil;
	if (instance_representation_qm) {
	    add_thing_to_frame_display(rule_instance,
		    instance_representation_qm,display,Nil);
	    update_made_qm = T;
	}
	goto next_loop_2;
      end_loop_2:;
	if (update_made_qm && 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qdynamic_display_delay_in_milliseconds,FIX((SI_Long)200L))) {
	    force_process_drawing();
	    return VALUES_1(FIX(g2ext_sys_sleep(IFIX(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qdynamic_display_delay_in_milliseconds,
		    FIX((SI_Long)200L))))));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-RULE-INSTANCE-FROM-DYNAMIC-RULE-DISPLAYS */
Object remove_rule_instance_from_dynamic_rule_displays(rule_instance)
    Object rule_instance;
{
    Object rule, temp, gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_4;
    Object frame_displays, update_made_qm, display, ab_loop_list_;
    Object instance_representation_qm;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(214,252);
    if (Dynamic_rule_display_hash_table) {
	rule = ISVREF(rule_instance,(SI_Long)8L);
	gensymed_symbol = IFIX(frame_hash_function(rule));
	temp = Dynamic_rule_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_1));
	gensymed_symbol_1 = CDR(temp);
	gensymed_symbol_2 = rule;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		frame_displays = M_CDR(M_CAR(gensymed_symbol_1));
		goto end_1;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    frame_displays = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	frame_displays = Qnil;
      end_2:;
	update_made_qm = Nil;
	display = Nil;
	ab_loop_list_ = frame_displays;
	instance_representation_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = assq_function(rule_instance,ISVREF(display,(SI_Long)4L));
	instance_representation_qm = CADR(temp);
	if (instance_representation_qm) {
	    remove_thing_from_frame_display(rule_instance,display);
	    update_made_qm = T;
	}
	goto next_loop_2;
      end_loop_2:;
	if (update_made_qm && 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qdynamic_display_delay_in_milliseconds,FIX((SI_Long)200L))) {
	    force_process_drawing();
	    return VALUES_1(FIX(g2ext_sys_sleep(IFIX(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qdynamic_display_delay_in_milliseconds,
		    FIX((SI_Long)200L))))));
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_151;  /* "Dynamic Rule Invocation Display" */

/* MAKE-DYNAMIC-RULE-INVOCATION-DISPLAY */
Object make_dynamic_rule_invocation_display(rule_frame)
    Object rule_frame;
{
    Object rule_display, display_header_title, display_header_rule;
    Object scope_conses, ab_hash_table_, ab_tree_form_, ab_node_stack_;
    Object ab_current_node_, ab_current_alist_, ab_entry_cons_, rule_instance;
    Object ab_less_than_branch_qm_, temp;
    SI_Long ab_table_length_, ab_index_;
    Declare_special(1);

    x_note_fn_call(214,253);
    if ( !TRUEP(Dynamic_rule_display_hash_table))
	Dynamic_rule_display_hash_table = make_dynamic_rule_displays();
    rule_display = create_dynamic_rule_display(rule_frame);
    display_header_title = make_explanation_table(2,Nil,
	    gensym_cons_1(copy_text_string(string_constant_151),Nil));
    display_header_rule = make_short_representation(3,rule_frame,Nil,Qsmall);
    add_thing_to_frame_display(display_header_title,display_header_title,
	    rule_display,Nil);
    add_thing_to_frame_display(display_header_rule,display_header_rule,
	    rule_display,Nil);
    if (ISVREF(rule_frame,(SI_Long)27L)) {
	scope_conses = Scope_conses;
	ab_hash_table_ = ISVREF(rule_frame,(SI_Long)27L);
	ab_table_length_ = (SI_Long)0L;
	ab_index_ = (SI_Long)0L;
	ab_tree_form_ = Nil;
	ab_node_stack_ = Nil;
	ab_current_node_ = Nil;
	ab_current_alist_ = Nil;
	ab_entry_cons_ = Nil;
	rule_instance = Nil;
	PUSH_SPECIAL(Scope_conses,scope_conses,0);
	  ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	next_loop:
	  if (ab_current_alist_) {
	      ab_entry_cons_ = M_CAR(ab_current_alist_);
	      ab_current_alist_ = M_CDR(ab_current_alist_);
	  }
	  else if (ab_current_node_) {
	      ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
	      if (ab_current_node_) {
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
		  ab_current_node_ = M_CAR(ab_node_stack_);
		  ab_node_stack_ = M_CDR(ab_node_stack_);
	      }
	      if (ab_current_node_) {
		  ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		  ab_entry_cons_ = M_CAR(ab_current_alist_);
		  ab_current_alist_ = M_CDR(ab_current_alist_);
	      }
	  }
	  if ( !TRUEP(ab_current_node_)) {
	    next_loop_2:
	      if ( !(ab_index_ < ab_table_length_))
		  goto end_loop_1;
	      ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
	      ab_index_ = ab_index_ + (SI_Long)1L;
	      if (T) {
		  ab_current_node_ = CDR(ab_tree_form_);
		  if (ab_current_node_) {
		      ab_less_than_branch_qm_ = Nil;
		    next_loop_3:
		      ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			      (SI_Long)1L);
		      if ( !TRUEP(ab_less_than_branch_qm_))
			  goto end_loop_2;
		      ab_node_stack_ = scope_cons(ab_current_node_,
			      ab_node_stack_);
		      ab_current_node_ = ab_less_than_branch_qm_;
		      goto next_loop_3;
		    end_loop_2:;
		      ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		      ab_entry_cons_ = M_CAR(ab_current_alist_);
		      ab_current_alist_ = M_CDR(ab_current_alist_);
		      goto end_loop_1;
		  }
	      }
	      goto next_loop_2;
	    end_loop_1:;
	  }
	  if ( !TRUEP(ab_current_node_))
	      goto end_loop_3;
	  rule_instance = M_CDR(ab_entry_cons_);
	  temp = rule_instance;
	  add_thing_to_frame_display(temp,
		  make_explanation_rule_instance_representation(rule_instance,
		  Nil),rule_display,Nil);
	  goto next_loop;
	end_loop_3:;
	POP_SPECIAL();
    }
    return show_frame_display(rule_display);
}

Object Available_generic_rule_instance_displays_hash_vector_43_vectors = UNBOUND;

Object Count_of_generic_rule_instance_displays_hash_vector_43_vectors = UNBOUND;

/* GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE */
Object generic_rule_instance_displays_hash_vector_43_vector_memory_usage()
{
    Object temp;

    x_note_fn_call(214,254);
    temp = Count_of_generic_rule_instance_displays_hash_vector_43_vectors;
    temp = FIXNUM_TIMES(temp,bytes_per_typed_simple_array(T,
	    FIX((SI_Long)43L)));
    return VALUES_1(temp);
}

/* OUT-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTORS */
Object out_generic_rule_instance_displays_hash_vector_43_vectors()
{
    Object temp;

    x_note_fn_call(214,255);
    temp = 
	    FIXNUM_MINUS(Count_of_generic_rule_instance_displays_hash_vector_43_vectors,
	    length(Available_generic_rule_instance_displays_hash_vector_43_vectors));
    return VALUES_1(temp);
}

/* MAKE-PERMANENT-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTOR-INTERNAL */
Object make_permanent_generic_rule_instance_displays_hash_vector_43_vector_internal()
{
    Object count_of_generic_rule_instance_displays_hash_vector_43_vectors_new_value;
    Object temp;
    XDeclare_area(1);

    x_note_fn_call(214,256);
    count_of_generic_rule_instance_displays_hash_vector_43_vectors_new_value 
	    = 
	    FIXNUM_ADD1(Count_of_generic_rule_instance_displays_hash_vector_43_vectors);
    Count_of_generic_rule_instance_displays_hash_vector_43_vectors = 
	    count_of_generic_rule_instance_displays_hash_vector_43_vectors_new_value;
    if (PUSH_AREA(Dynamic_area,0))
	temp = make_array(3,FIX((SI_Long)43L),Kinitial_element,Nil);
    POP_AREA(0);
    return VALUES_1(temp);
}

/* MAKE-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR */
Object make_generic_rule_instance_displays_hash_vector()
{
    Object temp, temp_1, cdr_arg, cdr_new_value;

    x_note_fn_call(214,257);
    if (Available_generic_rule_instance_displays_hash_vector_43_vectors) {
	temp = 
		M_CAR(Available_generic_rule_instance_displays_hash_vector_43_vectors);
	temp_1 = 
		M_CDR(Available_generic_rule_instance_displays_hash_vector_43_vectors);
	inline_note_reclaim_cons(Available_generic_rule_instance_displays_hash_vector_43_vectors,
		Qab_gensym);
	cdr_arg = 
		Available_generic_rule_instance_displays_hash_vector_43_vectors;
	cdr_new_value = Available_gensym_conses;
	M_CDR(cdr_arg) = cdr_new_value;
	Available_gensym_conses = 
		Available_generic_rule_instance_displays_hash_vector_43_vectors;
	Available_generic_rule_instance_displays_hash_vector_43_vectors = 
		temp_1;
    }
    else
	temp = 
		make_permanent_generic_rule_instance_displays_hash_vector_43_vector_internal();
    return VALUES_1(temp);
}

/* RECLAIM-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR */
Object reclaim_generic_rule_instance_displays_hash_vector(generic_rule_instance_displays_hash_vector_43_vector)
    Object generic_rule_instance_displays_hash_vector_43_vector;
{
    Object new_cons, gensymed_symbol, cdr_new_value;

    x_note_fn_call(214,258);
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = 
	    generic_rule_instance_displays_hash_vector_43_vector;
    cdr_new_value = 
	    Available_generic_rule_instance_displays_hash_vector_43_vectors;
    M_CDR(gensymed_symbol) = cdr_new_value;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    Available_generic_rule_instance_displays_hash_vector_43_vectors = 
	    gensymed_symbol;
    return VALUES_1(Nil);
}

/* RECLAIM-GENERIC-RULE-INSTANCE-DISPLAYS-TREE-FOR-HASH-LEAVES */
Object reclaim_generic_rule_instance_displays_tree_for_hash_leaves(generic_rule_instance_displays_tree_for_hash_binary_tree)
    Object generic_rule_instance_displays_tree_for_hash_binary_tree;
{
    Object less_than_branch_qm, greater_than_branch_qm, alist, alist_entry;
    Object ab_loop_list_, cdr_new_value, last_1, next_qm, temp;

    x_note_fn_call(214,259);
    less_than_branch_qm = Nil;
    greater_than_branch_qm = Nil;
    alist = Nil;
  next_loop:
    if ( !TRUEP(generic_rule_instance_displays_tree_for_hash_binary_tree))
	goto end_loop;
    less_than_branch_qm = 
	    ISVREF(generic_rule_instance_displays_tree_for_hash_binary_tree,
	    (SI_Long)1L);
    greater_than_branch_qm = 
	    ISVREF(generic_rule_instance_displays_tree_for_hash_binary_tree,
	    (SI_Long)2L);
    alist = 
	    ISVREF(generic_rule_instance_displays_tree_for_hash_binary_tree,
	    (SI_Long)3L);
    reclaim_binary_tree_element_1(generic_rule_instance_displays_tree_for_hash_binary_tree);
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
	reclaim_generic_rule_instance_displays_tree_for_hash_leaves(less_than_branch_qm);
	generic_rule_instance_displays_tree_for_hash_binary_tree = 
		greater_than_branch_qm;
    }
    else {
	temp = less_than_branch_qm;
	if (temp);
	else
	    temp = greater_than_branch_qm;
	generic_rule_instance_displays_tree_for_hash_binary_tree = temp;
    }
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* CLEAR-GENERIC-RULE-INSTANCE-DISPLAYS-TREE */
Object clear_generic_rule_instance_displays_tree(generic_rule_instance_displays_tree_for_hash_binary_tree)
    Object generic_rule_instance_displays_tree_for_hash_binary_tree;
{
    Object element_qm;

    x_note_fn_call(214,260);
    element_qm = CDR(generic_rule_instance_displays_tree_for_hash_binary_tree);
    if (element_qm) {
	reclaim_generic_rule_instance_displays_tree_for_hash_leaves(element_qm);
	M_CDR(generic_rule_instance_displays_tree_for_hash_binary_tree) = Nil;
    }
    return VALUES_1(generic_rule_instance_displays_tree_for_hash_binary_tree);
}

static Object Qgeneric_rule_instance_displays_tree_for_hash;  /* generic-rule-instance-displays-tree-for-hash */

/* MAKE-GENERIC-RULE-INSTANCE-DISPLAYS */
Object make_generic_rule_instance_displays()
{
    Object new_vector, new_cons, gensymed_symbol, temp;
    SI_Long index_1;

    x_note_fn_call(214,261);
    new_vector = make_generic_rule_instance_displays_hash_vector();
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    new_cons = Available_gensym_conses;
    if (new_cons) {
	Available_gensym_conses = M_CDR(new_cons);
	gensymed_symbol = new_cons;
    }
    else
	gensymed_symbol = Nil;
    if ( !TRUEP(gensymed_symbol))
	gensymed_symbol = replenish_gensym_cons_pool();
    M_CAR(gensymed_symbol) = Qgeneric_rule_instance_displays_tree_for_hash;
    M_CDR(gensymed_symbol) = Nil;
    inline_note_allocate_cons(gensymed_symbol,Qab_gensym);
    ISVREF(new_vector,index_1) = gensymed_symbol;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    temp = new_vector;
    goto end_1;
    temp = Qnil;
  end_1:;
    return VALUES_1(temp);
}

/* FLATTEN-GENERIC-RULE-INSTANCE-DISPLAYS */
Object flatten_generic_rule_instance_displays(generic_rule_instance_displays_hash_table)
    Object generic_rule_instance_displays_hash_table;
{
    Object result_1, subtree, temp;
    SI_Long index_1;

    x_note_fn_call(214,262);
    result_1 = Nil;
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    subtree = ISVREF(generic_rule_instance_displays_hash_table,index_1);
    if (subtree) {
	temp = flatten_binary_tree(CDR(subtree));
	result_1 = nconc2(temp,result_1);
    }
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(result_1);
}

/* CLEAR-GENERIC-RULE-INSTANCE-DISPLAYS */
Object clear_generic_rule_instance_displays(generic_rule_instance_displays_hash_table)
    Object generic_rule_instance_displays_hash_table;
{
    SI_Long index_1;

    x_note_fn_call(214,263);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    clear_generic_rule_instance_displays_tree(ISVREF(generic_rule_instance_displays_hash_table,
	    index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    return VALUES_1(Qnil);
}

/* RECLAIM-GENERIC-RULE-INSTANCE-DISPLAYS */
Object reclaim_generic_rule_instance_displays(generic_rule_instance_displays_hash_table)
    Object generic_rule_instance_displays_hash_table;
{
    Object generic_rule_instance_displays_tree_for_hash_binary_tree;
    Object element_qm, cdr_new_value, temp;
    SI_Long index_1;

    x_note_fn_call(214,264);
    index_1 = (SI_Long)0L;
  next_loop:
    if (index_1 >= (SI_Long)43L)
	goto end_loop;
    generic_rule_instance_displays_tree_for_hash_binary_tree = 
	    ISVREF(generic_rule_instance_displays_hash_table,index_1);
    element_qm = 
	    M_CDR(generic_rule_instance_displays_tree_for_hash_binary_tree);
    if (element_qm)
	reclaim_generic_rule_instance_displays_tree_for_hash_leaves(element_qm);
    inline_note_reclaim_cons(generic_rule_instance_displays_tree_for_hash_binary_tree,
	    Qab_gensym);
    cdr_new_value = Available_gensym_conses;
    M_CDR(generic_rule_instance_displays_tree_for_hash_binary_tree) = 
	    cdr_new_value;
    Available_gensym_conses = 
	    generic_rule_instance_displays_tree_for_hash_binary_tree;
    ISVREF(generic_rule_instance_displays_hash_table,index_1) = Nil;
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:;
    temp = 
	    reclaim_generic_rule_instance_displays_hash_vector(generic_rule_instance_displays_hash_table);
    return VALUES_1(temp);
}

Object Generic_rule_instance_display_hash_table = UNBOUND;

/* ADD-RULE-INSTANCE-TO-GENERIC-RULE-DISPLAYS */
Object add_rule_instance_to_generic_rule_displays(rule_instance)
    Object rule_instance;
{
    Object rule, environment_description, context, value, update_made_qm, x2;
    Object gensymed_symbol, sub_class_bit_vector, display, temp_1;
    Object gensymed_symbol_4, gensymed_symbol_5, ab_loop_list_;
    Object instance_representation_qm, temp_3, temp_4;
    SI_Long index_1, ab_loop_bind_, ab_loop_repeat_, superior_class_bit_number;
    SI_Long sub_class_vector_index, gensymed_symbol_1, gensymed_symbol_2;
    SI_Long gensymed_symbol_3, temp_2;
    char temp;

    x_note_fn_call(214,265);
    if (Dynamic_rule_display_hash_table && 
	    Generic_rule_instance_display_hash_table) {
	rule = ISVREF(rule_instance,(SI_Long)8L);
	environment_description = ISVREF(ISVREF(rule,(SI_Long)31L),
		(SI_Long)4L);
	context = ISVREF(rule_instance,(SI_Long)2L);
	index_1 = (SI_Long)0L;
	ab_loop_bind_ = IFIX(ISVREF(rule,(SI_Long)33L));
	ab_loop_repeat_ = IFIX(var_count(environment_description));
	value = Nil;
	update_made_qm = Nil;
      next_loop:
	if (index_1 >= ab_loop_bind_)
	    goto end_loop;
	if ( !((SI_Long)0L < ab_loop_repeat_))
	    goto end_loop;
	ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
	value = ISVREF(context,index_1);
	if (SIMPLE_VECTOR_P(value) && 
		IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(value)) > (SI_Long)2L &&  
		!EQ(ISVREF(value,(SI_Long)1L),Qavailable_frame_vector)) {
	    x2 = ISVREF(value,(SI_Long)1L);
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
		    IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
	    display = Nil;
	    gensymed_symbol_1 = IFIX(frame_hash_function(value));
	    temp_1 = Dynamic_rule_display_hash_table;
	    temp_2 = gensymed_symbol_1 % (SI_Long)43L;
	    temp_1 = SVREF(temp_1,FIX(temp_2));
	    gensymed_symbol = CDR(temp_1);
	    gensymed_symbol_4 = value;
	    gensymed_symbol_2 = (SI_Long)0L;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol))
		goto end_loop_1;
	    gensymed_symbol_2 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
	    if (gensymed_symbol_1 < gensymed_symbol_2)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
	    else if (gensymed_symbol_1 > gensymed_symbol_2)
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
	    else {
		gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		gensymed_symbol_5 = Nil;
	      next_loop_2:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_2;
		gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol));
		if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
		    ab_loop_list_ = M_CDR(M_CAR(gensymed_symbol));
		    goto end_1;
		}
		gensymed_symbol = M_CDR(gensymed_symbol);
		goto next_loop_2;
	      end_loop_2:
		ab_loop_list_ = Qnil;
	      end_1:;
		goto end_2;
	    }
	    goto next_loop_1;
	  end_loop_1:
	    ab_loop_list_ = Qnil;
	  end_2:;
	    instance_representation_qm = Nil;
	  next_loop_3:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop_3;
	    display = M_CAR(ab_loop_list_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    instance_representation_qm =  
		    !TRUEP(assq_function(rule_instance,ISVREF(display,
		    (SI_Long)4L))) ? 
		    make_explanation_rule_instance_representation(rule_instance,
		    T) : Nil;
	    if (instance_representation_qm) {
		add_thing_to_frame_display(rule_instance,
			instance_representation_qm,display,Nil);
		gensymed_symbol_1 = IFIX(ISVREF(rule_instance,(SI_Long)22L));
		temp_1 = Generic_rule_instance_display_hash_table;
		temp_2 = gensymed_symbol_1 % (SI_Long)43L;
		temp_1 = SVREF(temp_1,FIX(temp_2));
		temp_3 = display;
		gensymed_symbol_2 = IFIX(ISVREF(rule_instance,(SI_Long)22L));
		temp_4 = Generic_rule_instance_display_hash_table;
		temp_2 = gensymed_symbol_2 % (SI_Long)43L;
		temp_4 = SVREF(temp_4,FIX(temp_2));
		gensymed_symbol = CDR(temp_4);
		gensymed_symbol_4 = rule_instance;
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
		    gensymed_symbol_5 = Nil;
		  next_loop_5:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_5;
		    gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
			temp_4 = M_CDR(M_CAR(gensymed_symbol));
			goto end_3;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_5;
		  end_loop_5:
		    temp_4 = Qnil;
		  end_3:;
		    goto end_4;
		}
		goto next_loop_4;
	      end_loop_4:
		temp_4 = Qnil;
	      end_4:;
		set_balanced_binary_tree_entry(temp_1,Qeq,Nil,T,
			rule_instance,FIX(gensymed_symbol_1),
			gensym_cons_1(temp_3,temp_4));
		update_made_qm = T;
	    }
	    goto next_loop_3;
	  end_loop_3:;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	if (update_made_qm && 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qdynamic_display_delay_in_milliseconds,FIX((SI_Long)200L))) {
	    force_process_drawing();
	    g2ext_sys_sleep(IFIX(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qdynamic_display_delay_in_milliseconds,
		    FIX((SI_Long)200L))));
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

/* REMOVE-RULE-INSTANCE-FROM-GENERIC-RULE-DISPLAYS */
Object remove_rule_instance_from_generic_rule_displays(rule_instance)
    Object rule_instance;
{
    Object display, temp, gensymed_symbol_1, gensymed_symbol_2;
    Object gensymed_symbol_4, ab_loop_list_, instance_representation_qm;
    Object update_made_qm;
    SI_Long gensymed_symbol, temp_1, gensymed_symbol_3;

    x_note_fn_call(214,266);
    if (Dynamic_rule_display_hash_table && 
	    Generic_rule_instance_display_hash_table) {
	display = Nil;
	gensymed_symbol = IFIX(ISVREF(rule_instance,(SI_Long)22L));
	temp = Generic_rule_instance_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_1));
	gensymed_symbol_1 = CDR(temp);
	gensymed_symbol_2 = rule_instance;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_1:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_1;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		ab_loop_list_ = M_CDR(M_CAR(gensymed_symbol_1));
		goto end_1;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_1;
	  end_loop_1:
	    ab_loop_list_ = Qnil;
	  end_1:;
	    goto end_2;
	}
	goto next_loop;
      end_loop:
	ab_loop_list_ = Qnil;
      end_2:;
	instance_representation_qm = Nil;
	update_made_qm = Nil;
      next_loop_2:
	if ( !TRUEP(ab_loop_list_))
	    goto end_loop_2;
	display = M_CAR(ab_loop_list_);
	ab_loop_list_ = M_CDR(ab_loop_list_);
	temp = assq_function(rule_instance,ISVREF(display,(SI_Long)4L));
	instance_representation_qm = CADR(temp);
	if (instance_representation_qm) {
	    remove_thing_from_frame_display(rule_instance,display);
	    update_made_qm = T;
	}
	goto next_loop_2;
      end_loop_2:
	gensymed_symbol = IFIX(ISVREF(rule_instance,(SI_Long)22L));
	temp = Generic_rule_instance_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	temp = SVREF(temp,FIX(temp_1));
	gensymed_symbol_1 = CDR(temp);
	gensymed_symbol_2 = rule_instance;
	gensymed_symbol_3 = (SI_Long)0L;
      next_loop_3:
	if ( !TRUEP(gensymed_symbol_1))
	    goto end_loop_3;
	gensymed_symbol_3 = IFIX(ISVREF(gensymed_symbol_1,(SI_Long)0L));
	if (gensymed_symbol < gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)1L);
	else if (gensymed_symbol > gensymed_symbol_3)
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)2L);
	else {
	    gensymed_symbol_1 = ISVREF(gensymed_symbol_1,(SI_Long)3L);
	    gensymed_symbol_4 = Nil;
	  next_loop_4:
	    if ( !TRUEP(gensymed_symbol_1))
		goto end_loop_4;
	    gensymed_symbol_4 = M_CAR(M_CAR(gensymed_symbol_1));
	    if (EQ(gensymed_symbol_2,gensymed_symbol_4)) {
		temp = M_CDR(M_CAR(gensymed_symbol_1));
		goto end_3;
	    }
	    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
	    goto next_loop_4;
	  end_loop_4:
	    temp = Qnil;
	  end_3:;
	    goto end_4;
	}
	goto next_loop_3;
      end_loop_3:
	temp = Qnil;
      end_4:;
	reclaim_gensym_list_1(temp);
	gensymed_symbol = IFIX(ISVREF(rule_instance,(SI_Long)22L));
	temp = Generic_rule_instance_display_hash_table;
	temp_1 = gensymed_symbol % (SI_Long)43L;
	delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
		rule_instance,SVREF(temp,FIX(temp_1)),FIX(gensymed_symbol));
	if (update_made_qm && 
		get_lookup_slot_value_given_default(Debugging_parameters,
		Qdynamic_display_delay_in_milliseconds,FIX((SI_Long)200L))) {
	    force_process_drawing();
	    g2ext_sys_sleep(IFIX(get_lookup_slot_value_given_default(Debugging_parameters,
		    Qdynamic_display_delay_in_milliseconds,
		    FIX((SI_Long)200L))));
	}
	return VALUES_1(Qnil);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_152;  /* "Dynamic Generic Rule Display" */

/* MAKE-DYNAMIC-GENERIC-RULE-DISPLAY */
Object make_dynamic_generic_rule_display(object)
    Object object;
{
    Object rule_display, display_header_title, display_header_rule;
    Object scope_conses, ab_loopvar_, ab_loopvar__1, rule_frame;
    Object ab_hash_table_, ab_tree_form_, ab_node_stack_, ab_current_node_;
    Object ab_current_alist_, ab_entry_cons_, rule_instance;
    Object ab_less_than_branch_qm_, temp_1, temp_3, temp_4, gensymed_symbol_2;
    Object gensymed_symbol_3, gensymed_symbol_5;
    SI_Long ab_table_length_, ab_index_, gensymed_symbol, temp_2;
    SI_Long gensymed_symbol_1, gensymed_symbol_4;
    char temp;
    Declare_special(2);

    x_note_fn_call(214,267);
    if ( !TRUEP(Dynamic_rule_display_hash_table))
	Dynamic_rule_display_hash_table = make_dynamic_rule_displays();
    if ( !TRUEP(Generic_rule_instance_display_hash_table))
	Generic_rule_instance_display_hash_table = 
		make_generic_rule_instance_displays();
    rule_display = create_dynamic_rule_display(object);
    display_header_title = make_explanation_table(2,Nil,
	    gensym_cons_1(copy_text_string(string_constant_152),Nil));
    display_header_rule = make_short_representation(3,object,Nil,Qsmall);
    add_thing_to_frame_display(display_header_title,display_header_title,
	    rule_display,Nil);
    add_thing_to_frame_display(display_header_rule,display_header_rule,
	    rule_display,Nil);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    rule_frame = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,1);
      ab_loopvar_ = collect_subclasses(Qrule);
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
      rule_frame = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (ISVREF(rule_frame,(SI_Long)27L)) {
	  scope_conses = Scope_conses;
	  ab_hash_table_ = ISVREF(rule_frame,(SI_Long)27L);
	  ab_table_length_ = (SI_Long)0L;
	  ab_index_ = (SI_Long)0L;
	  ab_tree_form_ = Nil;
	  ab_node_stack_ = Nil;
	  ab_current_node_ = Nil;
	  ab_current_alist_ = Nil;
	  ab_entry_cons_ = Nil;
	  rule_instance = Nil;
	  PUSH_SPECIAL(Scope_conses,scope_conses,0);
	    ab_table_length_ = IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(ab_hash_table_));
	  next_loop_2:
	    if (ab_current_alist_) {
		ab_entry_cons_ = M_CAR(ab_current_alist_);
		ab_current_alist_ = M_CDR(ab_current_alist_);
	    }
	    else if (ab_current_node_) {
		ab_current_node_ = ISVREF(ab_current_node_,(SI_Long)2L);
		if (ab_current_node_) {
		    ab_less_than_branch_qm_ = Nil;
		  next_loop_3:
		    ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
			    (SI_Long)1L);
		    if ( !TRUEP(ab_less_than_branch_qm_))
			goto end_loop_2;
		    ab_node_stack_ = scope_cons(ab_current_node_,
			    ab_node_stack_);
		    ab_current_node_ = ab_less_than_branch_qm_;
		    goto next_loop_3;
		  end_loop_2:;
		}
		else if (ab_node_stack_) {
		    ab_current_node_ = M_CAR(ab_node_stack_);
		    ab_node_stack_ = M_CDR(ab_node_stack_);
		}
		if (ab_current_node_) {
		    ab_current_alist_ = ISVREF(ab_current_node_,(SI_Long)3L);
		    ab_entry_cons_ = M_CAR(ab_current_alist_);
		    ab_current_alist_ = M_CDR(ab_current_alist_);
		}
	    }
	    if ( !TRUEP(ab_current_node_)) {
	      next_loop_4:
		if ( !(ab_index_ < ab_table_length_))
		    goto end_loop_3;
		ab_tree_form_ = ISVREF(ab_hash_table_,ab_index_);
		ab_index_ = ab_index_ + (SI_Long)1L;
		if (T) {
		    ab_current_node_ = CDR(ab_tree_form_);
		    if (ab_current_node_) {
			ab_less_than_branch_qm_ = Nil;
		      next_loop_5:
			ab_less_than_branch_qm_ = ISVREF(ab_current_node_,
				(SI_Long)1L);
			if ( !TRUEP(ab_less_than_branch_qm_))
			    goto end_loop_4;
			ab_node_stack_ = scope_cons(ab_current_node_,
				ab_node_stack_);
			ab_current_node_ = ab_less_than_branch_qm_;
			goto next_loop_5;
		      end_loop_4:;
			ab_current_alist_ = ISVREF(ab_current_node_,
				(SI_Long)3L);
			ab_entry_cons_ = M_CAR(ab_current_alist_);
			ab_current_alist_ = M_CDR(ab_current_alist_);
			goto end_loop_3;
		    }
		}
		goto next_loop_4;
	      end_loop_3:;
	    }
	    if ( !TRUEP(ab_current_node_))
		goto end_loop_5;
	    rule_instance = M_CDR(ab_entry_cons_);
	    if (include_rule_instance_in_dynamic_generic_display_of_object(rule_instance,
		    object)) {
		gensymed_symbol = IFIX(ISVREF(rule_instance,(SI_Long)22L));
		temp_1 = Generic_rule_instance_display_hash_table;
		temp_2 = gensymed_symbol % (SI_Long)43L;
		temp_1 = SVREF(temp_1,FIX(temp_2));
		temp_3 = rule_instance;
		gensymed_symbol_1 = IFIX(ISVREF(rule_instance,(SI_Long)22L));
		temp_4 = Generic_rule_instance_display_hash_table;
		temp_2 = gensymed_symbol_1 % (SI_Long)43L;
		temp_4 = SVREF(temp_4,FIX(temp_2));
		gensymed_symbol_2 = CDR(temp_4);
		gensymed_symbol_3 = rule_instance;
		gensymed_symbol_4 = (SI_Long)0L;
	      next_loop_6:
		if ( !TRUEP(gensymed_symbol_2))
		    goto end_loop_6;
		gensymed_symbol_4 = IFIX(ISVREF(gensymed_symbol_2,
			(SI_Long)0L));
		if (gensymed_symbol_1 < gensymed_symbol_4)
		    gensymed_symbol_2 = ISVREF(gensymed_symbol_2,(SI_Long)1L);
		else if (gensymed_symbol_1 > gensymed_symbol_4)
		    gensymed_symbol_2 = ISVREF(gensymed_symbol_2,(SI_Long)2L);
		else {
		    gensymed_symbol_2 = ISVREF(gensymed_symbol_2,(SI_Long)3L);
		    gensymed_symbol_5 = Nil;
		  next_loop_7:
		    if ( !TRUEP(gensymed_symbol_2))
			goto end_loop_7;
		    gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol_2));
		    if (EQ(gensymed_symbol_3,gensymed_symbol_5)) {
			temp_4 = M_CDR(M_CAR(gensymed_symbol_2));
			goto end_1;
		    }
		    gensymed_symbol_2 = M_CDR(gensymed_symbol_2);
		    goto next_loop_7;
		  end_loop_7:
		    temp_4 = Qnil;
		  end_1:;
		    goto end_2;
		}
		goto next_loop_6;
	      end_loop_6:
		temp_4 = Qnil;
	      end_2:;
		set_balanced_binary_tree_entry(temp_1,Qeq,Nil,T,temp_3,
			FIX(gensymed_symbol),gensym_cons_1(rule_display,
			temp_4));
		temp_1 = rule_instance;
		add_thing_to_frame_display(temp_1,
			make_explanation_rule_instance_representation(rule_instance,
			T),rule_display,Nil);
	    }
	    goto next_loop_2;
	  end_loop_5:;
	  POP_SPECIAL();
      }
      goto next_loop;
    end_loop_1:;
    POP_SPECIAL();
    return show_frame_display(rule_display);
}

/* INCLUDE-RULE-INSTANCE-IN-DYNAMIC-GENERIC-DISPLAY-OF-OBJECT */
Object include_rule_instance_in_dynamic_generic_display_of_object(rule_instance,
	    object)
    Object rule_instance, object;
{
    Object rule, environment_description, context, value, ab_loop_it_;
    SI_Long index_1, ab_loop_bind_, ab_loop_repeat_;

    x_note_fn_call(214,268);
    rule = ISVREF(rule_instance,(SI_Long)8L);
    environment_description = ISVREF(ISVREF(rule,(SI_Long)31L),(SI_Long)4L);
    context = ISVREF(rule_instance,(SI_Long)2L);
    index_1 = (SI_Long)0L;
    ab_loop_bind_ = IFIX(ISVREF(rule,(SI_Long)33L));
    ab_loop_repeat_ = IFIX(var_count(environment_description));
    value = Nil;
    ab_loop_it_ = Nil;
  next_loop:
    if (index_1 >= ab_loop_bind_)
	goto end_loop;
    if ( !((SI_Long)0L < ab_loop_repeat_))
	goto end_loop;
    ab_loop_repeat_ = ab_loop_repeat_ - (SI_Long)1L;
    value = ISVREF(context,index_1);
    ab_loop_it_ = EQ(object,value) ? T : Nil;
    if (ab_loop_it_)
	return VALUES_1(ab_loop_it_);
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

/* CLEANUP-DYNAMIC-RULE-DISPLAY */
Object cleanup_dynamic_rule_display(frame_display)
    Object frame_display;
{
    Object x, x2, gensymed_symbol, sub_class_bit_vector;
    Object frame_or_rule_instance, ab_loop_list_, ab_loop_desetq_, temp_1;
    Object gensymed_symbol_4, gensymed_symbol_5, new_display_list, temp_3;
    SI_Long superior_class_bit_number, sub_class_vector_index;
    SI_Long gensymed_symbol_1, gensymed_symbol_2, gensymed_symbol_3, temp_2;
    char temp;

    x_note_fn_call(214,269);
    if (Generic_rule_instance_display_hash_table) {
	x = ISVREF(frame_display,(SI_Long)2L);
	if (SIMPLE_VECTOR_P(x) && IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(x)) > 
		(SI_Long)2L &&  !EQ(ISVREF(x,(SI_Long)1L),
		Qavailable_frame_vector)) {
	    x2 = ISVREF(x,(SI_Long)1L);
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
		    IFIX(ISVREF(Object_class_description,(SI_Long)18L));
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
	    frame_or_rule_instance = Nil;
	    ab_loop_list_ = ISVREF(frame_display,(SI_Long)4L);
	    ab_loop_desetq_ = Nil;
	  next_loop:
	    if ( !TRUEP(ab_loop_list_))
		goto end_loop;
	    ab_loop_desetq_ = M_CAR(ab_loop_list_);
	    frame_or_rule_instance = CAR(ab_loop_desetq_);
	    ab_loop_list_ = M_CDR(ab_loop_list_);
	    if (SIMPLE_VECTOR_P(frame_or_rule_instance) && 
		    EQ(ISVREF(frame_or_rule_instance,(SI_Long)0L),
		    Qg2_defstruct_structure_name_rule_instance_g2_struct)) {
		gensymed_symbol_1 = IFIX(ISVREF(frame_or_rule_instance,
			(SI_Long)22L));
		temp_1 = Generic_rule_instance_display_hash_table;
		temp_2 = gensymed_symbol_1 % (SI_Long)43L;
		temp_1 = SVREF(temp_1,FIX(temp_2));
		gensymed_symbol = CDR(temp_1);
		gensymed_symbol_4 = frame_or_rule_instance;
		gensymed_symbol_2 = (SI_Long)0L;
	      next_loop_1:
		if ( !TRUEP(gensymed_symbol))
		    goto end_loop_1;
		gensymed_symbol_2 = IFIX(ISVREF(gensymed_symbol,(SI_Long)0L));
		if (gensymed_symbol_1 < gensymed_symbol_2)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)1L);
		else if (gensymed_symbol_1 > gensymed_symbol_2)
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)2L);
		else {
		    gensymed_symbol = ISVREF(gensymed_symbol,(SI_Long)3L);
		    gensymed_symbol_5 = Nil;
		  next_loop_2:
		    if ( !TRUEP(gensymed_symbol))
			goto end_loop_2;
		    gensymed_symbol_5 = M_CAR(M_CAR(gensymed_symbol));
		    if (EQ(gensymed_symbol_4,gensymed_symbol_5)) {
			temp_1 = M_CDR(M_CAR(gensymed_symbol));
			goto end_1;
		    }
		    gensymed_symbol = M_CDR(gensymed_symbol);
		    goto next_loop_2;
		  end_loop_2:
		    temp_1 = Qnil;
		  end_1:;
		    goto end_2;
		}
		goto next_loop_1;
	      end_loop_1:
		temp_1 = Qnil;
	      end_2:;
		new_display_list = delete_gensym_element_1(frame_display,
			temp_1);
		if (new_display_list) {
		    gensymed_symbol_1 = IFIX(ISVREF(frame_or_rule_instance,
			    (SI_Long)22L));
		    temp_1 = Generic_rule_instance_display_hash_table;
		    temp_2 = gensymed_symbol_1 % (SI_Long)43L;
		    set_balanced_binary_tree_entry(SVREF(temp_1,
			    FIX(temp_2)),Qeq,Nil,T,frame_or_rule_instance,
			    FIX(gensymed_symbol_1),new_display_list);
		}
		else {
		    gensymed_symbol_1 = IFIX(ISVREF(frame_or_rule_instance,
			    (SI_Long)22L));
		    temp_1 = frame_or_rule_instance;
		    temp_3 = Generic_rule_instance_display_hash_table;
		    temp_2 = gensymed_symbol_1 % (SI_Long)43L;
		    delete_balanced_binary_tree_entry(SYMBOL_FUNCTION(Qeq),
			    temp_1,SVREF(temp_3,FIX(temp_2)),
			    FIX(gensymed_symbol_1));
		}
	    }
	    goto next_loop;
	  end_loop:
	    return VALUES_1(Qnil);
	}
	else
	    return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

static Object Qquery_command;      /* query-command */

/* MAKE-INSPECT-COMMAND-OR-SIGNAL-ERROR */
Object make_inspect_command_or_signal_error(command_string)
    Object command_string;
{
    Object inspect_command, gensymed_symbol, gensymed_symbol_1;
    Object current_edit_state, temp, parse_result_or_bad_phrase;
    Object error_string_qm, top_of_stack, message_1, bogus_edit_state;
    Object command_text, temp_1, temp_2;
    Declare_stack_pointer;
    Declare_special(2);
    Object result;

    x_note_fn_call(214,270);
    SAVE_STACK();
    inspect_command = make_command_frame(2,Qinspect_command,command_string);
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
    PUSH_SPECIAL(Current_edit_state,current_edit_state,1);
      temp = Current_edit_state;
      SVREF(temp,FIX((SI_Long)90L)) = gensymed_symbol_1;
      result = parse_text_string(3,command_string,Qquery_command,
	      inspect_command);
      MVS_2(result,parse_result_or_bad_phrase,error_string_qm);
      if (EQ(parse_result_or_bad_phrase,Bad_phrase)) {
	  delete_frame(inspect_command);
	  top_of_stack = Cached_top_of_stack;
	  message_1 = tformat_stack_error_text_string(1,error_string_qm);
	  SAVE_VALUES(raw_stack_error_named_error(top_of_stack,message_1));
      }
      else {
	  bogus_edit_state = make_edit_state_1();
	  command_text = 
		  convert_text_string_to_text(copy_text_string(command_string));
	  temp = ISVREF(inspect_command,(SI_Long)16L);
	  current_edit_state = bogus_edit_state;
	  PUSH_SPECIAL(Current_edit_state,current_edit_state,0);
	    temp_1 = Current_edit_state;
	    SVREF(temp_1,FIX((SI_Long)15L)) = command_text;
	    temp_2 = 
		    rewrite_query_command_parse_into_nicer_format(parse_result_or_bad_phrase);
	  POP_SPECIAL();
	  temp_1 = copy_for_slot_value(temp_2);
	  M_CAR(temp) = temp_1;
	  reclaim_edit_state_1(bogus_edit_state);
	  reclaim_text(command_text);
	  SAVE_VALUES(VALUES_1(inspect_command));
      }
      if (gensymed_symbol) {
	  temp = Current_edit_state;
	  SVREF(temp,FIX((SI_Long)90L)) = Nil;
      }
      reclaim_edit_state_1(Current_edit_state);
      result = RESTORE_VALUES();
    POP_SPECIAL();
    RESTORE_STACK();
    return result;
}

/* G2-RUN-INSPECT-COMMAND */
Object g2_run_inspect_command(command_string)
    Object command_string;
{
    Object inspect_command, gensymed_symbol, current_workstation_1;
    Object current_workstation_window, type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object servicing_workstation_qm;
    Declare_special(10);

    x_note_fn_call(214,271);
    inspect_command = make_inspect_command_or_signal_error(command_string);
    ISVREF(inspect_command,(SI_Long)21L) = T;
    ISVREF(inspect_command,(SI_Long)22L) = T;
    gensymed_symbol = get_or_make_dummy_workstation();
    current_workstation_1 = gensymed_symbol;
    PUSH_SPECIAL(Current_workstation,current_workstation_1,9);
      current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
      PUSH_SPECIAL(Current_workstation_window,current_workstation_window,8);
	type_of_current_workstation_window = Nil;
	PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		7);
	  current_workstation_native_window_qm = Nil;
	  PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		  6);
	    temp = ISVREF(Current_workstation,(SI_Long)17L);
	    current_workstation_context = CAR(temp);
	    PUSH_SPECIAL(Current_workstation_context,current_workstation_context,
		    5);
	      type_of_current_workstation_context = 
		      ISVREF(Current_workstation_context,(SI_Long)1L);
	      PUSH_SPECIAL(Type_of_current_workstation_context,type_of_current_workstation_context,
		      4);
		specific_structure_for_current_workstation_context = 
			ISVREF(Current_workstation_context,(SI_Long)2L);
		PUSH_SPECIAL(Specific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			3);
		  current_workstation_detail_pane = Nil;
		  PUSH_SPECIAL(Current_workstation_detail_pane,current_workstation_detail_pane,
			  2);
		    current_g2_user_mode_qm = Qadministrator;
		    PUSH_SPECIAL(Current_g2_user_mode_qm,current_g2_user_mode_qm,
			    1);
		      servicing_workstation_qm = T;
		      PUSH_SPECIAL(Servicing_workstation_qm,servicing_workstation_qm,
			      0);
			execute_inspect_command(inspect_command);
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    return delete_frame(inspect_command);
}

static Object Kstack_error;        /* :stack-error */

/* G2-RUN-INSPECT-COMMAND-SYSTEM-RPC-INTERNAL */
Object g2_run_inspect_command_system_rpc_internal(gensymed_symbol,
	    command_string)
    Object gensymed_symbol, command_string;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(214,272);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL(Current_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL(Current_computation_flags,current_computation_flags,0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_run_inspect_command(command_string);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

Object Highest_inspect_session_id = UNBOUND;

/* RECLAIM-QUERY-REPRESENTATION-TASK-VALUE */
Object reclaim_query_representation_task_value(value,frame)
    Object value, frame;
{
    Object schedule_task_qm, old_structure_being_reclaimed, svref_new_value;

    x_note_fn_call(214,273);
    schedule_task_qm = ISVREF(frame,(SI_Long)13L);
    if (schedule_task_qm) {
	if (EQ(schedule_task_qm,Current_schedule_task))
	    Current_schedule_task = Nil;
	if (ISVREF(schedule_task_qm,(SI_Long)6L))
	    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
	inline_note_reclaim_cons(schedule_task_qm,Nil);
	old_structure_being_reclaimed = Structure_being_reclaimed;
	Structure_being_reclaimed = schedule_task_qm;
	reclaim_schedule_task_args(ISVREF(schedule_task_qm,(SI_Long)9L));
	SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
	Structure_being_reclaimed = old_structure_being_reclaimed;
	svref_new_value = Chain_of_available_schedule_tasks;
	SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
	Chain_of_available_schedule_tasks = schedule_task_qm;
    }
    svref_new_value = Nil;
    ISVREF(frame,(SI_Long)13L) = svref_new_value;
    return VALUES_1(Nil);
}

/* RECLAIM-QUERY-REPRESENTATION-USER-DATA-VALUE */
Object reclaim_query_representation_user_data_value(user_data,frame)
    Object user_data, frame;
{
    x_note_fn_call(214,274);
    if ( !(FIXNUMP(user_data) || SYMBOLP(user_data) || 
	    SIMPLE_VECTOR_P(user_data)))
	reclaim_if_evaluation_value_1(user_data);
    ISVREF(frame,(SI_Long)14L) = Nil;
    return VALUES_1(Nil);
}

static Object Qresume_search_task_in_workstation;  /* resume-search-task-in-workstation */

static Object Qreclaim_frame_serial_number;  /* reclaim-frame-serial-number */

static Object Qg2_defstruct_structure_name_schedule_task_g2_struct;  /* g2-defstruct-structure-name::schedule-task-g2-struct */

/* SCHEDULE-SEARCH-TASK */
Object schedule_search_task(kb_search_state)
    Object kb_search_state;
{
    Object query_representation, future_task_schedule_modify_arg_2;
    Object future_task_schedule_modify_arg_8;
    Object future_task_schedule_modify_arg_10;
    Object future_task_schedule_modify_arg_11;
    Object future_task_schedule_modify_arg_12;
    Object future_task_schedule_modify_arg_13, schedule_task_qm;
    Object old_structure_being_reclaimed, temp;
    Object def_structure_schedule_task_variable, task;
    char svref_new_value;
    double future_task_schedule_modify_arg_3, aref_new_value;
    XDeclare_area(1);
    XDeclare_frontier(1);
    Object result;

    x_note_fn_call(214,275);
    query_representation = ISVREF(kb_search_state,(SI_Long)65L);
    if ( !TRUEP(ISVREF(query_representation,(SI_Long)19L))) {
	if (PUSH_LOCAL_ALLOCATION(Local_area,0,0)) {
	    future_task_schedule_modify_arg_2 = 
		    ISVREF(query_representation,(SI_Long)16L);
	    future_task_schedule_modify_arg_3 = 
		    DFLOAT_ISAREF_1(Current_g2_time,(SI_Long)0L) + 
		    DFLOAT_ISAREF_1(ISVREF(query_representation,
		    (SI_Long)17L),(SI_Long)0L);
	    future_task_schedule_modify_arg_8 = 
		    SYMBOL_FUNCTION(Qresume_search_task_in_workstation);
	    future_task_schedule_modify_arg_10 = gensym_list_3(Nil,Nil,
		    Qreclaim_frame_serial_number);
	    future_task_schedule_modify_arg_11 = Current_workstation;
	    future_task_schedule_modify_arg_12 = kb_search_state;
	    future_task_schedule_modify_arg_13 = 
		    copy_frame_serial_number(ISVREF(kb_search_state,
		    (SI_Long)3L));
	    schedule_task_qm = ISVREF(query_representation,(SI_Long)13L);
	    if (schedule_task_qm) {
		if (EQ(schedule_task_qm,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(schedule_task_qm,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		inline_note_reclaim_cons(schedule_task_qm,Nil);
		old_structure_being_reclaimed = Structure_being_reclaimed;
		Structure_being_reclaimed = schedule_task_qm;
		reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			(SI_Long)9L));
		SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		Structure_being_reclaimed = old_structure_being_reclaimed;
		temp = Chain_of_available_schedule_tasks;
		SVREF(schedule_task_qm,FIX((SI_Long)0L)) = temp;
		Chain_of_available_schedule_tasks = schedule_task_qm;
	    }
	    def_structure_schedule_task_variable = 
		    Chain_of_available_schedule_tasks;
	    if (def_structure_schedule_task_variable) {
		Chain_of_available_schedule_tasks = 
			ISVREF(def_structure_schedule_task_variable,
			(SI_Long)0L);
		SVREF(def_structure_schedule_task_variable,
			FIX((SI_Long)0L)) = 
			Qg2_defstruct_structure_name_schedule_task_g2_struct;
	    }
	    else
		def_structure_schedule_task_variable = 
			make_permanent_schedule_task_structure_internal();
	    inline_note_allocate_cons(def_structure_schedule_task_variable,
		    Nil);
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)2L)) = Nil;
	    SVREF(def_structure_schedule_task_variable,FIX((SI_Long)9L)) = Nil;
	    task = def_structure_schedule_task_variable;
	    temp = ISVREF(task,(SI_Long)1L);
	    DFLOAT_ISASET_1(temp,(SI_Long)0L,
		    future_task_schedule_modify_arg_3);
	    temp = ISVREF(task,(SI_Long)1L);
	    aref_new_value = -1.0;
	    DFLOAT_ISASET_1(temp,(SI_Long)1L,aref_new_value);
	    svref_new_value =  !TRUEP(T);
	    SVREF(task,FIX((SI_Long)3L)) = svref_new_value ? T : Nil;
	    SVREF(task,FIX((SI_Long)4L)) = future_task_schedule_modify_arg_2;
	    SVREF(task,FIX((SI_Long)5L)) = Nil;
	    SVREF(task,FIX((SI_Long)9L)) = future_task_schedule_modify_arg_10;
	    SVREF(task,FIX((SI_Long)7L)) = Qresume_search_task_in_workstation;
	    SVREF(task,FIX((SI_Long)8L)) = future_task_schedule_modify_arg_8;
	    ISVREF(task,(SI_Long)10L) = FIX((SI_Long)3L);
	    SVREF(task,FIX((SI_Long)11L)) = future_task_schedule_modify_arg_11;
	    SVREF(task,FIX((SI_Long)12L)) = future_task_schedule_modify_arg_12;
	    SVREF(task,FIX((SI_Long)13L)) = future_task_schedule_modify_arg_13;
	    future_task_schedule_2(task);
	    result = VALUES_1(ISVREF(query_representation,(SI_Long)13L) = 
		    task);
	}
	POP_LOCAL_ALLOCATION(0,0);
	return result;
    }
    else
	return VALUES_1(Nil);
}

/* RESUME-SEARCH-TASK-IN-WORKSTATION */
Object resume_search_task_in_workstation(workstation,kb_search_state,
	    reference_serial_number)
    Object workstation, kb_search_state, reference_serial_number;
{
    Object gensymed_symbol, current_workstation_1, current_workstation_window;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object servicing_workstation_qm, current_g2_window_for_this_workstation_qm;
    Object new_g2_classic_ui_p;
    Declare_special(12);
    Object result;

    x_note_fn_call(214,276);
    if (dummy_workstation_p(workstation)) {
	gensymed_symbol = get_or_make_dummy_workstation();
	current_workstation_1 = gensymed_symbol;
	PUSH_SPECIAL(Current_workstation,current_workstation_1,9);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		  8);
	    type_of_current_workstation_window = Nil;
	    PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		    7);
	      current_workstation_native_window_qm = Nil;
	      PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		      6);
		temp = ISVREF(Current_workstation,(SI_Long)17L);
		current_workstation_context = CAR(temp);
		PUSH_SPECIAL(Current_workstation_context,current_workstation_context,
			5);
		  type_of_current_workstation_context = 
			  ISVREF(Current_workstation_context,(SI_Long)1L);
		  PUSH_SPECIAL(Type_of_current_workstation_context,type_of_current_workstation_context,
			  4);
		    specific_structure_for_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)2L);
		    PUSH_SPECIAL(Specific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			    3);
		      current_workstation_detail_pane = Nil;
		      PUSH_SPECIAL(Current_workstation_detail_pane,current_workstation_detail_pane,
			      2);
			current_g2_user_mode_qm = Qadministrator;
			PUSH_SPECIAL(Current_g2_user_mode_qm,current_g2_user_mode_qm,
				1);
			  servicing_workstation_qm = T;
			  PUSH_SPECIAL(Servicing_workstation_qm,servicing_workstation_qm,
				  0);
			    result = search_items_a_little(kb_search_state,
				    reference_serial_number);
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
    else {
	current_workstation_1 = workstation;
	PUSH_SPECIAL(Current_workstation,current_workstation_1,11);
	  current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	  PUSH_SPECIAL(Current_workstation_window,current_workstation_window,
		  10);
	    current_g2_window_for_this_workstation_qm = 
		    ISVREF(Current_workstation,(SI_Long)25L);
	    PUSH_SPECIAL(Current_g2_window_for_this_workstation_qm,current_g2_window_for_this_workstation_qm,
		    9);
	      type_of_current_workstation_window = 
		      ISVREF(Current_workstation_window,(SI_Long)1L);
	      PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		      8);
		current_workstation_native_window_qm = 
			ISVREF(Current_workstation_window,(SI_Long)17L);
		PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
			7);
		  temp = ISVREF(Current_workstation,(SI_Long)17L);
		  current_workstation_context = CAR(temp);
		  PUSH_SPECIAL(Current_workstation_context,current_workstation_context,
			  6);
		    type_of_current_workstation_context = 
			    ISVREF(Current_workstation_context,(SI_Long)1L);
		    PUSH_SPECIAL(Type_of_current_workstation_context,type_of_current_workstation_context,
			    5);
		      specific_structure_for_current_workstation_context = 
			      ISVREF(Current_workstation_context,(SI_Long)2L);
		      PUSH_SPECIAL(Specific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			      4);
			current_workstation_detail_pane = 
				detail_pane(Current_workstation_window);
			PUSH_SPECIAL(Current_workstation_detail_pane,current_workstation_detail_pane,
				3);
			  current_g2_user_mode_qm = 
				  ISVREF(Current_workstation,(SI_Long)19L);
			  PUSH_SPECIAL(Current_g2_user_mode_qm,current_g2_user_mode_qm,
				  2);
			    new_g2_classic_ui_p = 
				    get_value_for_current_workstation_new_g2_classic_ui_p();
			    PUSH_SPECIAL(New_g2_classic_ui_p,new_g2_classic_ui_p,
				    1);
			      servicing_workstation_qm = T;
			      PUSH_SPECIAL(Servicing_workstation_qm,servicing_workstation_qm,
				      0);
				result = search_items_a_little(kb_search_state,
					reference_serial_number);
			      POP_SPECIAL();
			    POP_SPECIAL();
			  POP_SPECIAL();
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
	return result;
    }
}

/* G2-START-INSPECT-SESSION */
Object g2_start_inspect_session(command_string,callback,user_data,priority,
	    task_interval)
    Object command_string, callback, user_data, priority, task_interval;
{
    x_note_fn_call(214,277);
    return start_inspect_session_internal(command_string,
	    demand_representation_callback_remote_procedure_name(callback),
	    user_data,priority,task_interval);
}

/* START-INSPECT-SESSION-INTERNAL */
Object start_inspect_session_internal(command_string,callback,user_data,
	    priority,task_interval)
    Object command_string, callback, user_data, priority, task_interval;
{
    Object inspect_command, representation;
    Object current_remote_search_representation_qm, gensymed_symbol;
    Object current_workstation_1, current_workstation_window;
    Object type_of_current_workstation_window;
    Object current_workstation_native_window_qm, temp;
    Object current_workstation_context, type_of_current_workstation_context;
    Object specific_structure_for_current_workstation_context;
    Object current_workstation_detail_pane, current_g2_user_mode_qm;
    Object servicing_workstation_qm;
    Declare_special(11);

    x_note_fn_call(214,278);
    inspect_command = make_inspect_command_or_signal_error(command_string);
    representation = make_query_representation(inspect_command,callback,
	    user_data,priority,task_interval);
    ISVREF(inspect_command,(SI_Long)21L) = T;
    ISVREF(inspect_command,(SI_Long)23L) = T;
    current_remote_search_representation_qm = representation;
    PUSH_SPECIAL(Current_remote_search_representation_qm,current_remote_search_representation_qm,
	    10);
      gensymed_symbol = get_or_make_dummy_workstation();
      current_workstation_1 = gensymed_symbol;
      PUSH_SPECIAL(Current_workstation,current_workstation_1,9);
	current_workstation_window = ISVREF(Current_workstation,(SI_Long)1L);
	PUSH_SPECIAL(Current_workstation_window,current_workstation_window,8);
	  type_of_current_workstation_window = Nil;
	  PUSH_SPECIAL(Type_of_current_workstation_window,type_of_current_workstation_window,
		  7);
	    current_workstation_native_window_qm = Nil;
	    PUSH_SPECIAL(Current_workstation_native_window_qm,current_workstation_native_window_qm,
		    6);
	      temp = ISVREF(Current_workstation,(SI_Long)17L);
	      current_workstation_context = CAR(temp);
	      PUSH_SPECIAL(Current_workstation_context,current_workstation_context,
		      5);
		type_of_current_workstation_context = 
			ISVREF(Current_workstation_context,(SI_Long)1L);
		PUSH_SPECIAL(Type_of_current_workstation_context,type_of_current_workstation_context,
			4);
		  specific_structure_for_current_workstation_context = 
			  ISVREF(Current_workstation_context,(SI_Long)2L);
		  PUSH_SPECIAL(Specific_structure_for_current_workstation_context,specific_structure_for_current_workstation_context,
			  3);
		    current_workstation_detail_pane = Nil;
		    PUSH_SPECIAL(Current_workstation_detail_pane,current_workstation_detail_pane,
			    2);
		      current_g2_user_mode_qm = Qadministrator;
		      PUSH_SPECIAL(Current_g2_user_mode_qm,current_g2_user_mode_qm,
			      1);
			servicing_workstation_qm = T;
			PUSH_SPECIAL(Servicing_workstation_qm,servicing_workstation_qm,
				0);
			  execute_inspect_command(inspect_command);
			POP_SPECIAL();
		      POP_SPECIAL();
		    POP_SPECIAL();
		  POP_SPECIAL();
		POP_SPECIAL();
	      POP_SPECIAL();
	    POP_SPECIAL();
	  POP_SPECIAL();
	POP_SPECIAL();
      POP_SPECIAL();
    POP_SPECIAL();
    temp = ISVREF(representation,(SI_Long)18L);
    return VALUES_1(temp);
}

static Object Qquery_representation;  /* query-representation */

static Object Qsocket;             /* socket */

static Object Qsession_id;         /* session-id */

/* MAKE-QUERY-REPRESENTATION */
Object make_query_representation(inspect_command,callback,user_data,
	    priority,task_interval)
    Object inspect_command, callback, user_data, priority, task_interval;
{
    Object socket_1, representation, temp, x2, frame_serial_number_setf_arg;
    Object old, new_1;
    SI_Long temp_2, svref_new_value;
    char temp_1;

    x_note_fn_call(214,279);
    socket_1 = Current_system_rpc_icp_socket_qm;
    if (socket_1);
    else
	socket_1 = Local_pseudo_socket;
    representation = make_representation(socket_1,inspect_command,
	    Qquery_representation);
    store_callback_representation(representation);
    temp = gensym_list_4(Qsocket,socket_1,Qsession_id,
	    Current_system_rpc_icp_socket_qm ? 
	    ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)40L) : 
	    FIX((SI_Long)12345678L));
    ISVREF(representation,(SI_Long)8L) = temp;
    ISVREF(representation,(SI_Long)10L) = callback;
    if (SIMPLE_VECTOR_P(callback) && 
	    IFIX(SIMPLE_ARRAY_ANY_1_LENGTH(callback)) > (SI_Long)2L &&  
	    !EQ(ISVREF(callback,(SI_Long)1L),Qavailable_frame_vector)) {
	x2 = ISVREF(callback,(SI_Long)1L);
	temp_1 = SIMPLE_VECTOR_P(x2) && EQ(ISVREF(x2,(SI_Long)0L),
		Qg2_defstruct_structure_name_class_description_g2_struct) ?
		 TRUEP(x2) : TRUEP(Qnil);
    }
    else
	temp_1 = TRUEP(Nil);
    if (temp_1) {
	frame_serial_number_setf_arg = ISVREF(callback,(SI_Long)3L);
	old = ISVREF(representation,(SI_Long)11L);
	new_1 = frame_serial_number_setf_arg;
	temp = (FIXNUMP(old) ||  !TRUEP(old)) && (FIXNUMP(new_1) ||  
		!TRUEP(new_1)) ? new_1 : 
		frame_serial_number_setf_helper_1(old,new_1);
	ISVREF(representation,(SI_Long)11L) = temp;
    }
    ISVREF(representation,(SI_Long)14L) = user_data;
    ISVREF(representation,(SI_Long)15L) = inspect_command;
    temp_2 = MAX(IFIX(priority),(SI_Long)1L);
    svref_new_value = MIN((SI_Long)10L,temp_2);
    ISVREF(representation,(SI_Long)16L) = FIX(svref_new_value);
    ISVREF(representation,(SI_Long)17L) = task_interval;
    temp = FIXNUM_ADD1(Highest_inspect_session_id);
    Highest_inspect_session_id = temp;
    temp = Highest_inspect_session_id;
    ISVREF(representation,(SI_Long)18L) = temp;
    return VALUES_1(representation);
}

/* FIND-QUERY-REPRESENTATION-BY-ID */
Object find_query_representation_by_id(session_id)
    Object session_id;
{
    Object scope_conses, ab_loopvar_, ab_loopvar__1, representation, temp_1;
    char temp;
    Declare_special(1);

    x_note_fn_call(214,280);
    scope_conses = Scope_conses;
    ab_loopvar_ = Nil;
    ab_loopvar__1 = Nil;
    representation = Nil;
    PUSH_SPECIAL(Scope_conses,scope_conses,0);
      ab_loopvar_ = collect_subclasses(Qquery_representation);
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
      representation = ab_loopvar__1;
      ab_loopvar__1 = ISVREF(ab_loopvar__1,(SI_Long)6L);
      if (FIXNUM_EQ(ISVREF(representation,(SI_Long)18L),session_id)) {
	  temp_1 = representation;
	  goto end_1;
      }
      goto next_loop;
    end_loop_1:
      temp_1 = Nil;
      goto end_1;
      temp_1 = Qnil;
    end_1:;
    POP_SPECIAL();
    return VALUES_1(temp_1);
}

/* G2-PAUSE-INSPECT-SESSION */
Object g2_pause_inspect_session(session_id)
    Object session_id;
{
    Object representation_qm;

    x_note_fn_call(214,281);
    representation_qm = find_query_representation_by_id(session_id);
    if (representation_qm)
	ISVREF(representation_qm,(SI_Long)19L) = T;
    return VALUES_1(Nil);
}

/* G2-RESUME-INSPECT-SESSION */
Object g2_resume_inspect_session(session_id)
    Object session_id;
{
    Object representation_qm, kb_search_state_qm;

    x_note_fn_call(214,282);
    representation_qm = find_query_representation_by_id(session_id);
    if (representation_qm) {
	ISVREF(representation_qm,(SI_Long)19L) = Nil;
	kb_search_state_qm = ISVREF(ISVREF(representation_qm,(SI_Long)15L),
		(SI_Long)19L);
	if (kb_search_state_qm)
	    schedule_search_task(kb_search_state_qm);
    }
    return VALUES_1(Nil);
}

/* G2-ABORT-INSPECT-SESSION */
Object g2_abort_inspect_session(session_id)
    Object session_id;
{
    Object representation_qm, schedule_task_qm, old_structure_being_reclaimed;
    Object svref_new_value;

    x_note_fn_call(214,283);
    representation_qm = find_query_representation_by_id(session_id);
    if (representation_qm) {
	ISVREF(representation_qm,(SI_Long)19L) = T;
	if (ISVREF(representation_qm,(SI_Long)13L)) {
	    schedule_task_qm = ISVREF(representation_qm,(SI_Long)13L);
	    if (schedule_task_qm) {
		if (EQ(schedule_task_qm,Current_schedule_task))
		    Current_schedule_task = Nil;
		if (ISVREF(schedule_task_qm,(SI_Long)6L))
		    cancel_and_reclaim_scheduled_queue_element_1(schedule_task_qm);
		inline_note_reclaim_cons(schedule_task_qm,Nil);
		old_structure_being_reclaimed = Structure_being_reclaimed;
		Structure_being_reclaimed = schedule_task_qm;
		reclaim_schedule_task_args(ISVREF(schedule_task_qm,
			(SI_Long)9L));
		SVREF(schedule_task_qm,FIX((SI_Long)9L)) = Nil;
		Structure_being_reclaimed = old_structure_being_reclaimed;
		svref_new_value = Chain_of_available_schedule_tasks;
		SVREF(schedule_task_qm,FIX((SI_Long)0L)) = svref_new_value;
		Chain_of_available_schedule_tasks = schedule_task_qm;
	    }
	    svref_new_value = Nil;
	    ISVREF(representation_qm,(SI_Long)13L) = svref_new_value;
	}
	return delete_frame(ISVREF(representation_qm,(SI_Long)15L));
    }
    else
	return VALUES_1(Nil);
}

static Object Qfinished;           /* finished */

static Object Qframes_remaining;   /* frames-remaining */

/* RETURN-REMOTE-QUERY-RESULTS */
Object return_remote_query_results(kb_search_state,item_list,done_p)
    Object kb_search_state, item_list, done_p;
{
    Object query_representation, gensymed_symbol, gensymed_symbol_1;
    Object car_new_value, thing, argument_list, address, socket_1;

    x_note_fn_call(214,284);
    query_representation = ISVREF(kb_search_state,(SI_Long)65L);
    gensymed_symbol = make_gensym_list_1(FIX((SI_Long)6L));
    gensymed_symbol_1 = gensymed_symbol;
    car_new_value = done_p ? Qfinished : Qframes_remaining;
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(kb_search_state,(SI_Long)29L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(kb_search_state,(SI_Long)30L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = ISVREF(kb_search_state,(SI_Long)33L);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    car_new_value = allocate_evaluation_sequence(item_list);
    M_CAR(gensymed_symbol_1) = car_new_value;
    gensymed_symbol_1 = M_CDR(gensymed_symbol_1);
    thing = ISVREF(query_representation,(SI_Long)14L);
    car_new_value = FIXNUMP(thing) || thing && SYMBOLP(thing) || 
	    SIMPLE_VECTOR_P(thing) ? thing : copy_if_evaluation_value_1(thing);
    M_CAR(gensymed_symbol_1) = car_new_value;
    argument_list = gensymed_symbol;
    address = ISVREF(query_representation,(SI_Long)8L);
    socket_1 = getfq_function_no_default(address,Qsocket);
    callback_representation_fire_callback(query_representation,socket_1,
	    argument_list);
    if (done_p)
	return delete_frame(ISVREF(query_representation,(SI_Long)15L));
    else
	return VALUES_1(Nil);
}

/* G2-START-INSPECT-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_start_inspect_session_system_rpc_internal(gensymed_symbol,
	    command_string,callback,user_data,priority,task_interval)
    Object gensymed_symbol, command_string, callback, user_data, priority;
    Object task_interval;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, gensymed_symbol_2, return_list;
    Object passed_top_of_stack, error_1, error_text, supress_debugging_info_qm;
    Object temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(214,285);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	gensymed_symbol_2 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL(Current_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL(Current_computation_flags,current_computation_flags,0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    result = g2_start_inspect_session(command_string,callback,
		    user_data,priority,task_interval);
	    MVS_2(result,gensymed_symbol_1,gensymed_symbol_2);
	    return_list = gensym_cons_1(gensymed_symbol_1,Nil);
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-PAUSE-INSPECT-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_pause_inspect_session_system_rpc_internal(gensymed_symbol,session_id)
    Object gensymed_symbol, session_id;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(214,286);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL(Current_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL(Current_computation_flags,current_computation_flags,0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_pause_inspect_session(session_id);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-RESUME-INSPECT-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_resume_inspect_session_system_rpc_internal(gensymed_symbol,
	    session_id)
    Object gensymed_symbol, session_id;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(214,287);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL(Current_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL(Current_computation_flags,current_computation_flags,0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_resume_inspect_session(session_id);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

/* G2-ABORT-INSPECT-SESSION-SYSTEM-RPC-INTERNAL */
Object g2_abort_inspect_session_system_rpc_internal(gensymed_symbol,session_id)
    Object gensymed_symbol, session_id;
{
    Object current_computation_flags, current_system_rpc_icp_socket_qm;
    Object gensymed_symbol_1, return_list, passed_top_of_stack, error_1;
    Object error_text, supress_debugging_info_qm, temp, error_text_string;
    Declare_catch(1);
    Declare_special(2);
    Object result;

    x_note_fn_call(214,288);
    if (PUSH_CATCH(Kstack_error,0)) {
	current_computation_flags = Current_computation_flags;
	current_system_rpc_icp_socket_qm = ISVREF(gensymed_symbol,(SI_Long)2L);
	gensymed_symbol_1 = Nil;
	return_list = Qnil;
	PUSH_SPECIAL(Current_system_rpc_icp_socket_qm,current_system_rpc_icp_socket_qm,
		1);
	  PUSH_SPECIAL(Current_computation_flags,current_computation_flags,0);
	    if (ISVREF(Current_system_rpc_icp_socket_qm,(SI_Long)48L))
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) | (SI_Long)16L);
	    else
		Current_computation_flags = 
			FIX(IFIX(Current_computation_flags) &  ~(SI_Long)16L);
	    gensymed_symbol_1 = g2_abort_inspect_session(session_id);
	    return_list = Nil;
	    result = return_from_system_defined_rpc(gensymed_symbol,
		    return_list);
	  POP_SPECIAL();
	POP_SPECIAL();
	POP_CATCH(0);
	goto end_gensymed_symbol;
    }
    else
	result = CATCH_VALUES();
    POP_CATCH(0);
    MVS_4(result,passed_top_of_stack,error_1,error_text,
	    supress_debugging_info_qm);
    temp = CONSP(error_text) ? FIRST(error_text) : error_text;
    reclaim_error_text_but_not_string(error_text);
    error_text_string = temp;
    result = system_rpc_error(gensymed_symbol,error_1,error_text_string);
  end_gensymed_symbol:
    return result;
}

void queries_INIT()
{
    Object temp, temp_1, reclaim_structure_for_inspect_command_spot_1;
    Object type_description, temp_2, gensymed_symbol;
    Object named_dynamic_extent_description;
    Object reclaim_structure_for_cached_explanation_from_data_server_or_initial_value_1;
    Object reclaim_structure_for_cached_explanation_from_specific_formula_1;
    Object reclaim_structure_for_cached_explanation_from_frame_1;
    Object reclaim_structure_for_cached_explanation_from_generic_formula_1;
    Object reclaim_structure_for_cached_explanation_from_rule_1;
    Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_1;
    Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_specific_formula_1;
    Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_generic_formula_1;
    Object get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_rule_1;
    Object make_cached_explanation_node_for_cached_explanation_from_rule_1;
    Object make_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value_1;
    Object make_cached_explanation_node_for_cached_explanation_from_specific_formula_1;
    Object make_cached_explanation_node_for_cached_explanation_from_frame_1;
    Object return_cached_explanation_if_valid_for_cached_explanation_1;
    Object return_cached_explanation_if_valid_for_cached_explanation_from_frame_1;
    Object export_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value_1;
    Object export_cached_explanation_node_for_cached_explanation_from_specific_formula_1;
    Object export_cached_explanation_node_for_cached_explanation_from_frame_1;
    Object export_cached_explanation_node_for_cached_explanation_from_rule_1;
    Object reclaim_structure_for_frame_display_1;
    Object Qg2_abort_inspect_session_system_rpc_internal;
    Object Qg2_abort_inspect_session, Qsystem_defined_rpc, list_constant_88;
    Object AB_package, Qg2_resume_inspect_session_system_rpc_internal;
    Object Qg2_resume_inspect_session;
    Object Qg2_pause_inspect_session_system_rpc_internal;
    Object Qg2_pause_inspect_session, list_constant_87, list_constant_86;
    Object list_constant_80, Qg2_start_inspect_session_system_rpc_internal;
    Object Qg2_start_inspect_session, list_constant_85, list_constant_84;
    Object list_constant_83, list_constant_82, list_constant_81;
    Object list_constant_76, Qtask_interval, Qpriority, Qdatum, Quser_data;
    Object list_constant_79, Qcallback;
    Object Qfunction_keeps_procedure_environment_valid_qm;
    Object G2_DEFSTRUCT_STRUCTURE_NAME_package, Qslot_value_reclaimer;
    Object Qreclaim_query_representation_user_data_value;
    Object Qquery_representation_user_data;
    Object Qreclaim_query_representation_task_value;
    Object Qquery_representation_task, string_constant_287, list_constant_78;
    Object string_constant_286, string_constant_285, string_constant_284;
    Object string_constant_283, Qcallback_representation;
    Object Qg2_run_inspect_command_system_rpc_internal;
    Object Qg2_run_inspect_command, list_constant_77, Qcommand_string;
    Object Qqueries, Qgeneric_rule_instance_display_hash_table;
    Object Qout_generic_rule_instance_displays_hash_vector_43_vectors;
    Object Qgeneric_rule_instance_displays_hash_vector_43_vector_memory_usage;
    Object string_constant_282, Qutilities2;
    Object Qcount_of_generic_rule_instance_displays_hash_vector_43_vectors;
    Object Qavailable_generic_rule_instance_displays_hash_vector_43_vectors;
    Object list_constant_27, Qdynamic_rule_display_hash_table;
    Object Qout_dynamic_rule_displays_hash_vector_43_vectors;
    Object Qdynamic_rule_displays_hash_vector_43_vector_memory_usage;
    Object string_constant_281;
    Object Qcount_of_dynamic_rule_displays_hash_vector_43_vectors;
    Object Qavailable_dynamic_rule_displays_hash_vector_43_vectors;
    Object Qframe_display, Qreclaim_structure;
    Object Qoutstanding_frame_display_count;
    Object Qframe_display_structure_memory_usage, Qframe_display_count;
    Object Qchain_of_available_frame_displays, string_constant_280;
    Object Qtype_description_of_type, string_constant_279;
    Object Qunique_structure_type_of_ab_name_qm;
    Object Qab_name_of_unique_structure_type, Qg2_get_explanation_hierarchy;
    Object Qcreate_explanation, string_constant_278, string_constant_277;
    Object string_constant_276, string_constant_275, string_constant_274;
    Object list_constant_75, Qcreate_icon_description, string_constant_273;
    Object string_constant_272, string_constant_271, string_constant_270;
    Object string_constant_269, string_constant_210, list_constant_71;
    Object Qcached_explanation_from_rule, Qexport_cached_explanation_node;
    Object Qcached_explanation_from_frame;
    Object Qcached_explanation_from_specific_formula;
    Object Qcached_explanation_from_data_server_or_initial_value;
    Object Qreturn_cached_explanation_if_valid, Qcached_explanation;
    Object Qmake_cached_explanation_node;
    Object Qget_cached_explanation_evaled_variables_if_any;
    Object Qcached_explanation_from_generic_formula;
    Object Qoutstanding_cached_explanation_from_rule_count;
    Object Qcached_explanation_from_rule_structure_memory_usage;
    Object Qcached_explanation_from_rule_count;
    Object Qchain_of_available_cached_explanation_from_rules;
    Object string_constant_268, string_constant_267;
    Object Qoutstanding_cached_explanation_from_generic_formula_count;
    Object Qcached_explanation_from_generic_formula_structure_memory_usage;
    Object Qcached_explanation_from_generic_formula_count;
    Object Qchain_of_available_cached_explanation_from_generic_formulas;
    Object string_constant_266, string_constant_265;
    Object Qoutstanding_cached_explanation_from_frame_count;
    Object Qcached_explanation_from_frame_structure_memory_usage;
    Object Qcached_explanation_from_frame_count;
    Object Qchain_of_available_cached_explanation_from_frames;
    Object string_constant_264, string_constant_263;
    Object Qoutstanding_cached_explanation_from_specific_formula_count;
    Object Qcached_explanation_from_specific_formula_structure_memory_usage;
    Object Qcached_explanation_from_specific_formula_count;
    Object Qchain_of_available_cached_explanation_from_specific_formulas;
    Object string_constant_262, string_constant_261;
    Object Qoutstanding_cached_explanation_from_data_server_or_initial_value_count;
    Object Qcached_explanation_from_data_server_or_initial_value_structure_memory_usage;
    Object Qcached_explanation_from_data_server_or_initial_value_count;
    Object Qchain_of_available_cached_explanation_from_data_server_or_initial_values;
    Object string_constant_260, string_constant_259, string_constant_258;
    Object Qclasses_which_define, Qdescribe_frame;
    Object Qdescribe_frame_for_class_definition;
    Object Qdescribe_frame_for_method_declaration;
    Object Qdescribe_frame_for_image_definition, Qdescribe_frame_for_parameter;
    Object Qdescribe_frame_for_variable;
    Object Qdescribe_frame_for_variable_or_parameter;
    Object Qdescribe_frame_for_g2_list, Qdescribe_frame_for_g2_array;
    Object Qdescribe_frame_for_connection, Qdescribe_frame_for_block;
    Object Qgeneric_method_lambda_list, list_constant_74;
    Object Qlaunch_compile_to_bring_kb_up_to_date;
    Object Qremote_query_id_for_kb_recompile, Qworkspace_name_box;
    Object Qshow_on_a_workspace_the_procedure_invocation_hierarchy;
    Object Qshow_on_a_workspace_the_procedure_reference_hierarchy;
    Object Qshow_on_a_workspace_the_method_inheritance_path;
    Object Qshow_on_a_workspace_the_method_hierarchy;
    Object Qshow_on_a_workspace_the_module_hierarchy;
    Object Qshow_on_a_workspace_the_inspect_command_history;
    Object Qshow_on_a_workspace_the_class_hierarchy;
    Object Qshow_on_a_workspace_the_workspace_hierarchy;
    Object Qobservance_of_word_boundary_qm, Qreplacement_string_qm;
    Object Qstring_to_look_for_qm, list_constant_73, Qab_or, Qunknown_datum;
    Object Qupdate_only_when_shown, Qupdate_after_edits;
    Object Qmay_request_event_updates, Qmay_provide_data_on_request;
    Object Qcomputation_style_description, Qnamed_dynamic_extent_description;
    Object Qrecompile_from_inspect, string_constant_257, list_constant_72;
    Object string_constant_256, Qoccurrences_of_replacement_string;
    Object Qitems_containing_replacement_string, Qresulting_parsing_failures;
    Object Qsubstitutions_made, Qreplacement_string, Qstring_to_replace;
    Object string_constant_255, string_constant_254, string_constant_253;
    Object string_constant_252, string_constant_251, Qoccurrences;
    Object Qitems_with_occurrences, Qstring_to_look_for, string_constant_250;
    Object string_constant_249, Qname_of_file_with_results;
    Object string_constant_248, string_constant_247, Qslot_value_writer;
    Object Qwrite_kb_state_search_status_from_slot, Qkb_state_search_status;
    Object Qwrite_item_filter_qm_from_slot, Qitem_filter_qm;
    Object Qdenote_cell_array_element;
    Object Qdenote_cell_array_element_for_kb_search_state;
    Object Qreclaim_frame_serial_number_for_inspect_command_for_kb_search_qm_value;
    Object Qframe_serial_number_for_inspect_command_for_kb_search_qm;
    Object Qreclaim_frame_serial_number_for_subcommand_menu_for_kb_search_qm_value;
    Object Qframe_serial_number_for_subcommand_menu_for_kb_search_qm;
    Object Qreclaim_frame_serial_number_for_kb_search_results_workspace_value;
    Object Qframe_serial_number_for_kb_search_results_workspace;
    Object Qreclaim_frame_serial_number_for_kb_search_value;
    Object Qframe_serial_number_for_kb_search;
    Object Qreclaim_old_kb_search_result_tables_and_text_boxes_value;
    Object Qold_kb_search_result_tables_and_text_boxes;
    Object Qreclaim_file_stream_for_printing_search_results_qm_value;
    Object Qfile_stream_for_printing_search_results_qm, Qfilter, Qstatus;
    Object Qitems_examined_so_far, Qitems_to_examine;
    Object Qdeactivate_for_kb_search_state, Qactivate_for_kb_search_state;
    Object Qcleanup, Qcleanup_for_kb_search_state, Qinitialize;
    Object Qinitialize_for_kb_search_state, string_constant_246;
    Object string_constant_245, string_constant_244, string_constant_243;
    Object string_constant_242, string_constant_241, string_constant_240;
    Object string_constant_239, string_constant_238, string_constant_237;
    Object string_constant_236, string_constant_235, string_constant_234;
    Object string_constant_233, string_constant_232, string_constant_231;
    Object string_constant_230, string_constant_229, string_constant_228;
    Object string_constant_227, string_constant_226, string_constant_225;
    Object string_constant_224, string_constant_223, string_constant_222;
    Object Qentity, Qtop_level_kb_module_qm, Qformat_description;
    Object string_constant_221, string_constant_220;
    Object Qclass_hierarchy_borderless_free_text_format;
    Object Qinspection_instance_counter, Qexpression_cell_updated;
    Object Qexpression_cell_updated_for_kb_search_state, Qexecute_command;
    Object Qexecute_command_for_inspect_command;
    Object Qexecute_command_for_inspect_history;
    Object Qinspect_command_history_list_max_size;
    Object Qg2_permit_inspector_within_restricted_license, list_constant_70;
    Object list_constant_69, list_constant_52, list_constant_68, Qsame_as;
    Object list_constant_60, list_constant_66, list_constant_67, Qexists;
    Object Qworkspace, Qrole_server, list_constant_65, list_constant_64;
    Object Qg2_inspect_internal_name_for_debugging_p, list_constant_63;
    Object list_constant_62, list_constant_54, list_constant_61;
    Object list_constant_38, Qhas_a_name, list_constant_59, list_constant_58;
    Object list_constant_57, list_constant_56, list_constant_55;
    Object Qthere_exists_literal, list_constant_53, list_constant_51;
    Object Qcleanup_for_inspect_command, list_constant_50, list_constant_49;
    Object list_constant_48, Qevery_instance_such_that, list_constant_47;
    Object list_constant_46, Qg2_lambda, list_constant_45, list_constant_44;
    Object list_constant_41, list_constant_43, list_constant_42;
    Object list_constant_40, list_constant_39, Qname, list_constant_37;
    Object list_constant_36, list_constant_35, list_constant_34;
    Object list_constant_33, list_constant_32, list_constant_31;
    Object list_constant_30, Qhighlight, list_constant_29;
    Object Qtemporary_name_number_2, Qtemporary_name_number_1;
    Object string_constant_219, Kfuncall;
    Object Quse_slot_value_compiler_for_default_overrides_p;
    Object Qslot_value_compiler, Qcompile_query_command_for_slot;
    Object Qgenerate_spot, Qgenerate_spot_for_inspect_command;
    Object Qtype_of_frame_represented, Qabstract_type, Qspot;
    Object Qenclosing_spot_type, Qinnermost_spot_p, Qinspect_command_spot;
    Object Qoutstanding_inspect_command_spot_count;
    Object Qinspect_command_spot_structure_memory_usage;
    Object Qinspect_command_spot_count;
    Object Qchain_of_available_inspect_command_spots, string_constant_218;
    Object string_constant_217;
    Object Qreclaim_frame_serial_number_for_inspect_command_search_state_qm_value;
    Object Qframe_serial_number_for_inspect_command_search_state_qm;
    Object string_constant_216, list_constant_28, string_constant_215;
    Object string_constant_214, string_constant_213, string_constant_212;
    Object string_constant_211, Qcommand;
    Object Qreject_inspect_keywords_as_local_names, Qassigned, Qwhose, Qwhich;
    Object Qcontaining, Qwhere, Qfound;
    Object Qwhere_is_symbol_cannot_be_true_or_false, string_constant_209;
    Object string_constant_208, string_constant_207, string_constant_206;
    Object string_constant_205, string_constant_204, string_constant_203;
    Object string_constant_202, string_constant_201, string_constant_200;
    Object string_constant_199, string_constant_198, string_constant_197;
    Object string_constant_196, string_constant_195, string_constant_194;
    Object string_constant_193, string_constant_192, string_constant_191;
    Object string_constant_190, string_constant_189;
    Object Qsimplify_associative_operation, string_constant_188;
    Object string_constant_187, string_constant_186, string_constant_185;
    Object string_constant_184;
    Object Qconvert_class_qualified_list_to_keyword_symbol;
    Object Qreduce_noting_source_position, string_constant_183;
    Object string_constant_182, Qmessage, list_constant_26, list_constant_25;
    Object list_constant_24, list_constant_23, list_constant_22;
    Object list_constant_21, list_constant_20, list_constant_19;
    Object Qmethod_declaration_name, Qquery_symbol, Qprocedure_name;
    Object Qfunction_name, Qattribute_name, Qitem_name;
    Object Qnot_runtime_or_embedded, Qcm;
    Object Qsystem_or_user_defined_attribute_name, Qquery_attributes;
    Object Qcdr_and_reduce_noting_source_position, string_constant_181;
    Object string_constant_180, string_constant_179, string_constant_178;
    Object string_constant_177, string_constant_176, string_constant_175;
    Object string_constant_174, string_constant_173, string_constant_172;
    Object string_constant_171, string_constant_170, string_constant_169;
    Object string_constant_168, string_constant_167, string_constant_166;
    Object string_constant_165, string_constant_164, string_constant_163;
    Object string_constant_162, string_constant_161, string_constant_160;
    Object string_constant_159, string_constant_158, string_constant_157;
    Object string_constant_156, string_constant_155, string_constant_154;
    Object string_constant_153;

    x_note_fn_call(214,289);
    SET_PACKAGE("AB");
    string_constant_153 = 
	    STATIC_STRING("13Zy1n83-uky1o1m9k83AMy1m9k83-ujy1m9k83Ioy1m9k83=3y83-uky1m83-r3y1o1m9k9l1m9k83=cy1m9k9m1m9k83h8y1n83-ugy1p1m9k83-Ty1m9k9l836Iy1");
    string_constant_154 = 
	    STATIC_STRING("m9k83-Ty83m0y1mnp1n83-M=y1m83-r3y83-ugy1mlm1m83-M2y83-2y1m83-M0y83Sy1n83-uiy1n1m9k83*5y1m9k83-Ty83x*y1m83-rkyn1n83-uhy1n1m9k83=F");
    string_constant_155 = 
	    STATIC_STRING("y1m9k83-qby83-M2y1m83-qbyn1n83-ufy1n1m9k83=Fy1m9k83-lmy83-M0y1m83-lmyn1m83-M1y83-uiy1m83-M1y83-uhy1m83-M1y83-ufy1n83-jWy1m83-M=y");
    string_constant_156 = 
	    STATIC_STRING("83-M1y1mlm1m83-lly1n1m9k83-C2y1m9k9l1m9k83Gy1m83-Swy1r1m9k83-Ty1m9k9n1m9k83-2Zy1m9k83-qy1m9k83-Ty1m9k9n1m9k83Ry1n83-uAy1n1m9k83F");
    string_constant_157 = 
	    STATIC_STRING("my1m9k83-qby83-M2y1m83-qbyn1n83-lvy1n1m9k83=3y83-r3y83-uAyn1n83-lvy1n1m9k83=3y83-r3y83-uiyn1n83-qey1q1m9k83-qby83-r3y83-Swy1m9k8");
    string_constant_158 = 
	    STATIC_STRING("3*Xy1m9k83Vty83Duy1m83-qfyq1n83-liy1p83-lly83-Swy1m9k83*Xy1m9k83Vty83Duy1m83-lkyp1n83-uey1n1m9k83-qby83-M=y83-uAy1n83-qcymn1n83-");
    string_constant_159 = 
	    STATIC_STRING("uey1o1m9k83-qby83-M=y83-uiy83-uAy1o83-qcymon1n83-uey1o1m9k83-qby83-M=y83-ufy83-uAy1o83-qcymon1n83-uey1p83-lly83-ugy1m9k83=3y83-r");
    string_constant_160 = 
	    STATIC_STRING("3y83-M1y1n83-lgymp1n83-uey1m1m9k9o83-jWy1m83-Qaym1n83-uey1m83-qey83-uAy1n83-qdyml1n83-uey1n83-qey83-uiy83-uAy1o83-qdynlm1n83-uey");
    string_constant_161 = 
	    STATIC_STRING("1m83-liy83-lvy1n83-lhyml1n83-uey1p1m9k831Wy1m9k83=cy1m9k83-cKy1m9k830Py83m0y1m83-SSyp1n83-uey1p1m9k831Uy1m9k83=cy1m9k83-cKy1m9k8");
    string_constant_162 = 
	    STATIC_STRING("30Py83m0y1m83-RHyp1n832Gy1m83-uky83-uey1m83m-y2llm1m83-r5y1n1m9k9l1m9k83-RAy1m9k837my1n83-nTy1m83-Cny83-r5y1m83-uky83-nMy1n832Gy");
    string_constant_163 = 
	    STATIC_STRING("1o83-nTy83-jWy1m9k83-ty83-jWy1o83m-ylmo1m83-r6y1n1m9k9l1m9k83-2Zy1m9k83fny1n83-nVy1m83-Cny83-r6y1m83-uky83-nOy1n832Gy1n83-nVy1m9");
    string_constant_164 = 
	    STATIC_STRING("k83-Ty83m0y1n83m-yln1n83-nRy1m83-Cny83-r3y1m83-uky83-nKy1n832Gy1n83-nRy83-ugy83-M1y1o83m-ylmn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qlog);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qdelete);
    add_grammar_rules_function(regenerate_optimized_constant(list(12,
	    string_constant_153,string_constant_154,string_constant_155,
	    string_constant_156,string_constant_157,string_constant_158,
	    string_constant_159,string_constant_160,string_constant_161,
	    string_constant_162,string_constant_163,string_constant_164)));
    AB_package = STATIC_PACKAGE("AB");
    Qshow_method_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-METHOD-HIERARCHY-ON-A-WORKSPACE",AB_package);
    Qshow_module_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-MODULE-HIERARCHY-ON-A-WORKSPACE",AB_package);
    Qshow_inspect_command_history_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-INSPECT-COMMAND-HISTORY-ON-A-WORKSPACE",
	    AB_package);
    Qwrite_class_hierarchy_to_file = 
	    STATIC_SYMBOL("WRITE-CLASS-HIERARCHY-TO-FILE",AB_package);
    Qcdr_and_reduce_noting_source_position = 
	    STATIC_SYMBOL("CDR-AND-REDUCE-NOTING-SOURCE-POSITION",AB_package);
    Qreduce_noting_source_position = 
	    STATIC_SYMBOL("REDUCE-NOTING-SOURCE-POSITION",AB_package);
    Qnot_runtime_or_embedded = STATIC_SYMBOL("NOT-RUNTIME-OR-EMBEDDED",
	    AB_package);
    string_constant_165 = 
	    STATIC_STRING("13py1n832Gy83-nSy1n83m-yl83Ry1n832Gy1n83-nSy1m9k83-Ty83m=y1n83m-yln1n83-nSy1m83-Cny83-r4y83-nLy1m83-r4y1n1m9k9l1m9k83-Gy1m9k83-*");
    string_constant_166 = 
	    STATIC_STRING("My1n832Gy83-nby1m83m-yl1n83-nby1m83-Cny83-rBy83-ngy1m83-rBy1o1m9k9l1m9k83=Vy1m9k83-Zry1m9k83-*My1n832Gy83-nay1n83m-yl83Ry1n832Gy");
    string_constant_167 = 
	    STATIC_STRING("1n83-nay1m9k83-Ty83m0y1n83m-yln1n83-nay1m83-Cny83-rAy83-nfy1m83-rAy1o1m9k9l1m9k83=Vy1m9k83-LQy1m9k83-*My1n832Gy83-nZy1n83m-yl83R");
    string_constant_168 = 
	    STATIC_STRING("y1n832Gy1n83-nZy1m9k83-Ty83m0y1n83m-yln1n83-nZy1m83-Cny83-r9y83-ney1m83-r9y1o1m9k9l1m9k83=Vy1m9k83-LPy1m9k83-*My1n832Gy1n83-nWy1");
    string_constant_169 = 
	    STATIC_STRING("m9k83-Ty834Ry1n83m-yln1n83-nWy1m83-Cny83-r7y9m1m83-r7y1n1m9k9l1m9k834My1m9k83-*My1n832Gy1n83-nXy1m9k83=Iy83m=y1o83m-ylnn1n832Gy1");
    string_constant_170 = 
	    STATIC_STRING("r83-nXy1m9k83=Iy83m=y1m9k83-ty1m9k9l1m9k834My834Ry1o83m-ylnr1n83-nXy1m83-Cny83-r8y83-nPy1m83-r8y1o1m9k9l1m9k834My1m9k83-Z7y1m9k8");
    string_constant_171 = 
	    STATIC_STRING("3-hYy1n832Gy83-ncy1n83m-yl01n832Gy1n83-ncy1m9k83-Ty83-gMy1n83m-yln1n83-ncy1o83-Cny1m9k9l1m9k83*ry1m9k83-*My83-noy1m83-gMy839Wy1m");
    string_constant_172 = 
	    STATIC_STRING("83-gMy83eby1n832Gy83-nYy1n83m-yl01n832Gy1n83-nYy1m9k83-Ty83Duy1n83m-yln1n83-nYy1o83-Cny1m9k9l1m9k83Vty1m9k83-*My9n1n832Gy83-nUy1");
    string_constant_173 = 
	    STATIC_STRING("n83m-yl01n83-nUy1p83-Cny1m9k9l1m9k9o1m9k83=ny1m9k836xy9p1n832Gy83-MIy1n83m-yl01n83-MIy1o1m9k83-MGy1m9k83=Iy1m9k83-OFy1m9k83-eVy8");
    string_constant_174 = 
	    STATIC_STRING("3-MIy1n832Gy83-vwy1n83m-yl83Ry1n832Gy1n83-vwy1m9k83-Ty83m=y1n83m-yln1n83-vwy1s1m9k9q1m9k83=3y1m9k9l1m9k83LOy838Ky1m9k9l1m9k83-Gy");
    string_constant_175 = 
	    STATIC_STRING("1m9k83-*My1m9rp1n832Gy1m83-joy83-9oy1n83m-ylm1n832Gy1n83-joy83-r2y83-9oy1o83m-ylnm1o83-r2y1n1m9k9l83-jjy1m9k83-Tym9s1o83-joy1p1m");
    string_constant_176 = 
	    STATIC_STRING("9k9q1m9k83=3y1m9k9l1m9k83LOy838Ky1m83-vvyp9t1m83-joy83-Cny1m83-joy83-RNy1o83-joy1m9k83-k4yl9t1o83-Cny1o1m9k83n2y1m9k830Py1m9k83=");
    string_constant_177 = 
	    STATIC_STRING("Yy1m9k83*ry83-Cny9t1o83-RNy1o1m9k83-RMy1m9k83=Yy1m9k83*Jy1m9k83-Ty83-RNy9t1o83-RNy1p1m9k83-RMy1m9k83=Yy1m9k83*Jy1m9k83-N9y1m9k83");
    string_constant_178 = 
	    STATIC_STRING("-Ty83-ROy9t1p83-joy1p1m9k9u83-jny1m9k83=Fy83-jny1m9k83*Xy1o9u83-g=ymo9v9t1p83-joy1r1m9k9u1m9k9l1m9k83-H+y83-jny1m9k83=Fy83-jny1m");
    string_constant_179 = 
	    STATIC_STRING("9k83*Xy1o9u83-H+yoq9v9t1p83-joy1r1m9k9u1m9k9l1m9k83-2y83-jny1m9k83=Fy83-jny1m9k83*Xy1o9u83-2yoq9v9t1o83-joy1n1m9k83-XOy83-jny1m9");
    string_constant_180 = 
	    STATIC_STRING("k83*Xy1n83-XOy83-g=ym9t1o83-joy1p1m9k83-XOy1m9k9l1m9k83-H+y83-jny1m9k83*Xy1n83-XOy83-H+yo9t1o83-joy1p1m9k83-XOy1m9k9l1m9k83-2y83");
    string_constant_181 = 
	    STATIC_STRING("-jny1m9k83*Xy1n83-XOy83-2yo9t1m83-jny83m2y1m83-jny83-Uy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qshow_method_hierarchy_on_a_workspace);
    push_optimized_constant(Qshow_module_hierarchy_on_a_workspace);
    push_optimized_constant(Qinspect);
    push_optimized_constant(Qshow_inspect_command_history_on_a_workspace);
    push_optimized_constant(Qwrite);
    push_optimized_constant(Qwrite_class_hierarchy_to_file);
    push_optimized_constant(Qcdr_and_reduce_noting_source_position);
    push_optimized_constant(Qreduce_noting_source_position);
    push_optimized_constant(Qreplace);
    push_optimized_constant(Qnot_runtime_or_embedded);
    add_grammar_rules_function(regenerate_optimized_constant(list(17,
	    string_constant_165,string_constant_166,string_constant_167,
	    string_constant_168,string_constant_169,string_constant_170,
	    string_constant_171,string_constant_172,string_constant_173,
	    string_constant_174,string_constant_175,string_constant_176,
	    string_constant_177,string_constant_178,string_constant_179,
	    string_constant_180,string_constant_181)));
    SET_SYMBOL_FUNCTION(Qcdr_and_reduce_noting_source_position,
	    STATIC_FUNCTION(cdr_and_reduce_noting_source_position,NIL,
	    FALSE,1,1));
    Qquery_attributes = STATIC_SYMBOL("QUERY-ATTRIBUTES",AB_package);
    Qsystem_or_user_defined_attribute_name = 
	    STATIC_SYMBOL("SYSTEM-OR-USER-DEFINED-ATTRIBUTE-NAME",AB_package);
    Qcm = STATIC_SYMBOL(",",AB_package);
    add_grammar_rules_for_list(4,Qquery_attributes,
	    Qsystem_or_user_defined_attribute_name,Qcm,Qand);
    Qcannot_replace_in_runtime_or_embedded_g2 = 
	    STATIC_SYMBOL("CANNOT-REPLACE-IN-RUNTIME-OR-EMBEDDED-G2",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qnot_runtime_or_embedded,
	    STATIC_FUNCTION(not_runtime_or_embedded,NIL,FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qnot_runtime_or_embedded);
    Qquery_symbol = STATIC_SYMBOL("QUERY-SYMBOL",AB_package);
    list_constant_19 = STATIC_LIST((SI_Long)2L,Qquery_symbol,Qsymbol);
    Qitem_name = STATIC_SYMBOL("ITEM-NAME",AB_package);
    list_constant_20 = STATIC_LIST((SI_Long)2L,Qquery_symbol,Qitem_name);
    Qab_class = STATIC_SYMBOL("CLASS",AB_package);
    list_constant_21 = STATIC_LIST((SI_Long)2L,Qquery_symbol,Qab_class);
    Qattribute_name = STATIC_SYMBOL("ATTRIBUTE-NAME",AB_package);
    list_constant_22 = STATIC_LIST((SI_Long)2L,Qquery_symbol,Qattribute_name);
    Qfunction_name = STATIC_SYMBOL("FUNCTION-NAME",AB_package);
    list_constant_23 = STATIC_LIST((SI_Long)2L,Qquery_symbol,Qfunction_name);
    Qprocedure_name = STATIC_SYMBOL("PROCEDURE-NAME",AB_package);
    list_constant_24 = STATIC_LIST((SI_Long)2L,Qquery_symbol,Qprocedure_name);
    Qmethod_declaration_name = STATIC_SYMBOL("METHOD-DECLARATION-NAME",
	    AB_package);
    list_constant_25 = STATIC_LIST((SI_Long)2L,Qquery_symbol,
	    Qmethod_declaration_name);
    list_constant_26 = STATIC_LIST((SI_Long)7L,list_constant_19,
	    list_constant_20,list_constant_21,list_constant_22,
	    list_constant_23,list_constant_24,list_constant_25);
    add_grammar_rules_function(list_constant_26);
    Qmessage = STATIC_SYMBOL("MESSAGE",AB_package);
    string_constant_182 = 
	    STATIC_STRING("1t1m83m=y83-Gy1m83m=y1m9k83Ry1m83m=y1m9k83-Oy1m83m=y1m9k830Cy1m83m=y1m9k83=Vy1m83m=y1m9k832Jy1m83m=y1m9k83=uy1m83m=y1m9k9l1m83m=");
    string_constant_183 = STATIC_STRING("y1m9k836vy");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qmessage);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_182,
	    string_constant_183)));
    Qconvert_class_qualified_list_to_keyword_symbol = 
	    STATIC_SYMBOL("CONVERT-CLASS-QUALIFIED-LIST-TO-KEYWORD-SYMBOL",
	    AB_package);
    Qreject_inspect_keywords_as_local_names = 
	    STATIC_SYMBOL("REJECT-INSPECT-KEYWORDS-AS-LOCAL-NAMES",AB_package);
    string_constant_184 = 
	    STATIC_STRING("1x1n832Gy1m83-jpy83m0y1n83m-ylm1o83-jpy1m1m9k9l1m9k83=3y83-uvy9m1m83m0y834Hy1o83m0y1n83-Gy1m9k83=my834Hy1n83BFyln9n1m83-9oy83-fc");
    string_constant_185 = 
	    STATIC_STRING("y1m83-fcy83m0y1m83-fcy83-fey1m83-fcy83-fdy1o83-fey1o1m9k9o83m=y1m9k832dy834Hy2l1n83-Svym1n83-Uuy1l1m83-qmy1m83-Gym1n83-ty1m83-*2");
    string_constant_186 = 
	    STATIC_STRING("y83fCy1n83*Iy1n9o1m834Zy83=hy83fCy1m9ko83-owy9m1o83-fdy1m1m9k9p83m=y2l1n83-Svym1n83-Uuy1l1m83-qmy1m83-Gym83=Oy83-owy9m1o83-fdy1n");
    string_constant_187 = 
	    STATIC_STRING("1m9k9p83m=y83-9py2l1n83-Svym1n83-Uuy1l1m83-qmy1m83-Gymn83-owy9m1o83-fdy1o1m9k9p83m=y83-cAy83-9py2l1n83-Svym1n83-Uuy1l1mn1m83-Gym");
    string_constant_188 = STATIC_STRING("o83-owy9m1o83-cAy83*Zyl9q");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qgo);
    push_optimized_constant(Qreduce_noting_source_position);
    push_optimized_constant(Qconvert_class_qualified_list_to_keyword_symbol);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qevery);
    push_optimized_constant(Qreject_inspect_keywords_as_local_names);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_5(string_constant_184,
	    string_constant_185,string_constant_186,string_constant_187,
	    string_constant_188)));
    Qsimplify_associative_operation = 
	    STATIC_SYMBOL("SIMPLIFY-ASSOCIATIVE-OPERATION",AB_package);
    string_constant_189 = 
	    STATIC_STRING("1s1m83-9py83-jmy1o83-9py1n83-jmy1m9k83=Uy83-9py1n83=Uyln9l1m83-jmy83-jly1o83-jmy1n83-jly1m9k83-ty83-jmy1n83-tyln9l1m83-jly83m1y1");
    string_constant_190 = 
	    STATIC_STRING("n83-jly1m1m9k9m83m1y1m9mm1n83m1y1n1m9k83-9y83-9py1m9k83-Aym1n83m1y1n1m9k83FHy1m9k8319y831Pyn");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qsimplify_associative_operation);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(LIST_2(string_constant_189,
	    string_constant_190)));
    Qwhere_is_symbol_cannot_be_true_or_false = 
	    STATIC_SYMBOL("WHERE-IS-SYMBOL-CANNOT-BE-TRUE-OR-FALSE",
	    AB_package);
    string_constant_191 = 
	    STATIC_STRING("13ay1n83m1y1m1m9k83-ONy83-Uy1n83-ONy83fCym1n83m1y1m1m9k83-ONy83m2y1n83-ONy83fCy1m9km1n83m1y1o1m9k83-ONy1m9k9l1m9k83-H+y83-Uy1n83");
    string_constant_192 = 
	    STATIC_STRING("-OPy83fCyo1n83m1y1o1m9k83-ONy1m9k9l1m9k83-H+y83m2y1n83-OPy83fCy1m9ko1n83m1y1o1m9k83-ONy1m9k9l1m9k83-2y83-Uy1n83-OOy83fCyo1n83m1y");
    string_constant_193 = 
	    STATIC_STRING("1o1m9k83-ONy1m9k9l1m9k83-2y83m2y1n83-OOy83fCy1m9ko1n83m1y1m1m9k83=Fy1m9k83-g4y1m83-vSy83fCy1n83m1y1o1m9k83-vKy1m9k83-pOy1m9k83*I");
    string_constant_194 = 
	    STATIC_STRING("y83-Ugy1n83-vTy83fCy1m9ko1m83-Ugy1m9k839Xy1m83-Ugy1m9k83-Kay1m83-Ugy1m9k83-Ymy1m83-Ugy1m9k83-JBy1m83-Ugy1m9k83Cry1m83-Ugy1m9k83h");
    string_constant_195 = 
	    STATIC_STRING("6y1m83-Ugy1m9k83vGy1n83m1y1o1m9k83-Juy1m9k83=3y1m9k83Vty83Duy1o83-Jvy83fCy1m9ko832Zy1n83m1y1r1m9k83-Juy1m9k83=3y1m9k9l1m9k83-*My");
    string_constant_196 = 
	    STATIC_STRING("1m9k83-Ty1m9k83Vty83Duy1o83-Jvy83fCy1m9kr83=Oy1n83m1y1n1m9k83=Fy1m9k83fny1m9k83-2Zy1p83-vQy83fCy832Zy832Zy832Zy1n83m1y1p1m9k83=F");
    string_constant_197 = 
	    STATIC_STRING("y1m9k83fny1m9k83-2Zy1m9k83HAy83udy1p83-vQy83fCyp832Zy832Zy1n83m1y1p1m9k83=Fy1m9k83fny1m9k83-2Zy1m9k835+y83udy1p83-vQy83fCy832Zyp");
    string_constant_198 = 
	    STATIC_STRING("832Zy1n83m1y1s1m9k83=Fy1m9k83fny1m9k83-2Zy1m9k83HAy83udy1m9k83-ty1m9k835+y83udy1p83-vQy83fCyps832Zy1n83m1y1p1m9k83=Fy1m9k83fny1m");
    string_constant_199 = 
	    STATIC_STRING("9k83-2Zy1m9k83*uy83q4y1p83-vQy83fCy832Zy832Zy1m9kp1n83m1y1r1m9k83=Fy1m9k83fny1m9k83-2Zy1m9k83*uy83q4y1m9k83HAy83udy1p83-vQy83fCy");
    string_constant_200 = 
	    STATIC_STRING("r832Zyp1n83m1y1r1m9k83=Fy1m9k83fny1m9k83-2Zy1m9k83*uy83q4y1m9k835+y83udy1p83-vQy83fCy832Zyrp1n83m1y1u1m9k83=Fy1m9k83fny1m9k83-2Z");
    string_constant_201 = 
	    STATIC_STRING("y1m9k83*uy83q4y1m9k83HAy83udy1m9k83-ty1m9k835+y83udy1p83-vQy83fCyrup1n83m1y1n1m9k83=Fy1m9k83-tgy1m9k83fny1m83oey83fCy1n83m1y1o1m");
    string_constant_202 = 
	    STATIC_STRING("9k83-vDy836Iy838Ry8382y1nn1n9lm1m9l83-MRyo1n83m1y1o1m9k83-vDy836Iy1m9k9m8382y1n9m1n9lm1m9l83-MRyo1n83m1y1o1m9k83-vDy836Iy1m9k9n8");
    string_constant_203 = 
	    STATIC_STRING("382y1n9n1n9lm1m9l83-MRyo1o83m1y1o1m9k83-vDy836Iy1m9k83*Iy83-2y1mo1n83*Iy1n9lm1m9l83-MRy1m9ko9o1o83m1y1p1m9k83-vDy836Iy1m9k83*Iy1");
    string_constant_204 = 
	    STATIC_STRING("m9k9p83-2y1mp1m9p1n83*Iy1n9lm1m9l83-MRy1m9kp9o1n83m1y1o1m9k83-vDy836Iy1m9k83*Iy1m9k83=Oy1n9lm1m9l83-MRy1n83m1y1o1m9k83-vDy83*my1");
    string_constant_205 = 
	    STATIC_STRING("m9k83*Iy1m9k832Zy1m832Zy1n9lm1m9l83-MRy1n83m1y1o1m9k83*Xy1m9k9l1m9k83-Lby83mcy1n83-ty1n83*Iy1n9l83-Gy83fCy1m9k832Jy1n83-YWy83fCy");
    string_constant_206 = 
	    STATIC_STRING("1m9ko1n83m1y1q1m9k83-vEy1m9k831by1m9k9l1m9k83wYy1m9k83-Gy83-U=y1n83-ty1n83*Iy1n9l83-Gy83fCy1m9k832Jy1n83-vFy83fCy1m9kq1n83m1y1q1");
    string_constant_207 = 
	    STATIC_STRING("m9k83-vEy1m9k831by1m9k9l1m9k83wYy1m9k83-Oy83-U1y1n83-ty1n83*Iy1n9l83-Gy83fCy1m9k832Jy1n83-vGy83fCy1m9kq1m83-U=y83-6y1m83-U1y83-6");
    string_constant_208 = 
	    STATIC_STRING("y1m83eby83-6y1n83m1y1p1m9k83-UXy1m9k830Py1m9k9l1m9k83*ry83eby1n83-ty1m83Kry1n9l1n834Zy83*ry83=uy83fCy1n83mfy1n9l1n834Zy83*ry83=u");
    string_constant_209 = STATIC_STRING("y83fCyp");
    clear_optimized_constants();
    push_optimized_constant(Qquote);
    push_optimized_constant(Qthe);
    push_optimized_constant(Qnum_ge);
    push_optimized_constant(Qnum_le);
    push_optimized_constant(Qwhere_is_symbol_cannot_be_true_or_false);
    push_optimized_constant(Qnot);
    add_grammar_rules_function(regenerate_optimized_constant(list(19,
	    string_constant_191,string_constant_192,string_constant_193,
	    string_constant_194,string_constant_195,string_constant_196,
	    string_constant_197,string_constant_198,string_constant_199,
	    string_constant_200,string_constant_201,string_constant_202,
	    string_constant_203,string_constant_204,string_constant_205,
	    string_constant_206,string_constant_207,string_constant_208,
	    string_constant_209)));
    Qtrue = STATIC_SYMBOL("TRUE",AB_package);
    Qfalse = STATIC_SYMBOL("FALSE",AB_package);
    SET_SYMBOL_FUNCTION(Qwhere_is_symbol_cannot_be_true_or_false,
	    STATIC_FUNCTION(where_is_symbol_cannot_be_true_or_false,NIL,
	    FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qwhere_is_symbol_cannot_be_true_or_false);
    Qfound = STATIC_SYMBOL("FOUND",AB_package);
    Qwhere = STATIC_SYMBOL("WHERE",AB_package);
    Qcontaining = STATIC_SYMBOL("CONTAINING",AB_package);
    Qwhich = STATIC_SYMBOL("WHICH",AB_package);
    Qwhose = STATIC_SYMBOL("WHOSE",AB_package);
    Qassigned = STATIC_SYMBOL("ASSIGNED",AB_package);
    list_constant = STATIC_LIST((SI_Long)6L,Qfound,Qwhere,Qcontaining,
	    Qwhich,Qwhose,Qassigned);
    SET_SYMBOL_FUNCTION(Qreject_inspect_keywords_as_local_names,
	    STATIC_FUNCTION(reject_inspect_keywords_as_local_names,NIL,
	    FALSE,1,1));
    set_grammar_transform_can_return_bad_phrase_p(Qreject_inspect_keywords_as_local_names);
    list_constant_1 = STATIC_CONS(Qab_class,Qnil);
    Qok = STATIC_SYMBOL("OK",AB_package);
    Qbad = STATIC_SYMBOL("BAD",AB_package);
    Qincomplete = STATIC_SYMBOL("INCOMPLETE",AB_package);
    Qactive = STATIC_SYMBOL("ACTIVE",AB_package);
    Qinactive = STATIC_SYMBOL("INACTIVE",AB_package);
    Qenabled = STATIC_SYMBOL("ENABLED",AB_package);
    Qdisabled = STATIC_SYMBOL("DISABLED",AB_package);
    Qunbound_in_protected_let = STATIC_SYMBOL("UNBOUND-IN-PROTECTED-LET",
	    AB_package);
    list_constant_27 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
    array_constant = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant,(SI_Long)0L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)1L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant,(SI_Long)7L,(SI_Long)57344L);
    Qabort_level_3 = STATIC_SYMBOL("ABORT-LEVEL-3",AB_package);
    Qtext_conversion_style = STATIC_SYMBOL("TEXT-CONVERSION-STYLE",AB_package);
    array_constant_1 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)3L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)7L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)8L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)9L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)10L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)11L,(SI_Long)50L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)12L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)13L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)14L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)17L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)20L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)21L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)23L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)25L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)28L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)29L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)30L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)31L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)33L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)34L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)35L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)36L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)37L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)38L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)39L,(SI_Long)79L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)40L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)41L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)42L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)43L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)44L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)46L,(SI_Long)45L);
    UBYTE_16_ISASET_1(array_constant_1,(SI_Long)47L,(SI_Long)57344L);
    string_constant = STATIC_STRING("An unsaved knowledge base.");
    string_constant_1 = STATIC_STRING("** From KB:    ~a");
    string_constant_2 = STATIC_STRING("** File:       ~a");
    Qdo_not_use = STATIC_SYMBOL("DO-NOT-USE",AB_package);
    Qwide_string = STATIC_SYMBOL("WIDE-STRING",AB_package);
    string_constant_3 = STATIC_STRING("** Written at: ");
    array_constant_2 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_2,(SI_Long)7L,(SI_Long)57344L);
    array_constant_3 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)3L,(SI_Long)67L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)5L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)6L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)7L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)9L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)10L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_3,(SI_Long)15L,(SI_Long)57344L);
    Qbox_translation_and_text = STATIC_SYMBOL("BOX-TRANSLATION-AND-TEXT",
	    AB_package);
    list_constant_2 = STATIC_CONS(Qbox_translation_and_text,Qnil);
    array_constant_4 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)0L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)1L,(SI_Long)42L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)3L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)9L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)10L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)11L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)13L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)14L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)15L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)16L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)17L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)18L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)19L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)20L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)21L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)22L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)23L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)24L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)25L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)27L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)30L,(SI_Long)28L);
    UBYTE_16_ISASET_1(array_constant_4,(SI_Long)31L,(SI_Long)57344L);
    Qinspect_command = STATIC_SYMBOL("INSPECT-COMMAND",AB_package);
    Qcommand = STATIC_SYMBOL("COMMAND",AB_package);
    list_constant_28 = STATIC_CONS(Qcommand,Qnil);
    check_if_superior_classes_are_defined(Qinspect_command,list_constant_28);
    string_constant_210 = STATIC_STRING("0");
    string_constant_211 = 
	    STATIC_STRING("1q4z8r83ry83ry83SKy83SKy00001o1l8l1n8p832Gy83Gy1l8o1l83-3y000004z8r83Zqy83Zqy83SKy83SKy00001m1l8l1l8o000004z8r83MIy83MIy83SKy83S");
    string_constant_212 = 
	    STATIC_STRING("Ky00001m1l8l1l8o000004z8r83Zby83Zby83SKy83SKy00001m1l8l1l8o000004z8r83Zdy83Zdy83SKy83SKy00001m1l8l1l8o000004z8r83Zcy83Zcy83SKy83");
    string_constant_213 = STATIC_STRING("SKy00001m1l8l1l8o00000");
    string_constant_214 = 
	    STATIC_STRING("1s8q1m83SKy1l83=ny1n83ry01n8p832Gy83Gy1o83Zqy08l8o1o83MIy08l8o1o83Zby08l8o1o83Zdy08l8o1o83Zcy08l8o");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_211,
	    string_constant_212,string_constant_213));
    add_class_to_environment(9,Qinspect_command,list_constant_28,Nil,temp,
	    Nil,temp_1,list_constant_28,
	    regenerate_optimized_constant(string_constant_214),Nil);
    Inspect_command_class_description = 
	    lookup_global_or_kb_specific_property_value(Qinspect_command,
	    Class_description_gkbprop);
    Qinspect_history = STATIC_SYMBOL("INSPECT-HISTORY",AB_package);
    check_if_superior_classes_are_defined(Qinspect_history,list_constant_28);
    string_constant_215 = 
	    STATIC_STRING("1l4z8r83ry83ry83SMy83SMy00001o1l8l1n8p832Gy83Gy1l8o1l83-3y00000");
    string_constant_216 = 
	    STATIC_STRING("1n8q1m83SMy1l83=ny1n83ry01n8p832Gy83Gy");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(string_constant_215);
    add_class_to_environment(9,Qinspect_history,list_constant_28,Nil,temp,
	    Nil,temp_1,list_constant_28,
	    regenerate_optimized_constant(string_constant_216),Nil);
    Qframe_serial_number_for_inspect_command_search_state_qm = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-FOR-INSPECT-COMMAND-SEARCH-STATE\?",
	    AB_package);
    Qreclaim_frame_serial_number_for_inspect_command_search_state_qm_value 
	    = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-FOR-INSPECT-COMMAND-SEARCH-STATE\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_inspect_command_search_state_qm_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_for_inspect_command_search_state_qm_value,
	    NIL,FALSE,2,2));
    Qslot_value_reclaimer = STATIC_SYMBOL("SLOT-VALUE-RECLAIMER",AB_package);
    mutate_global_property(Qframe_serial_number_for_inspect_command_search_state_qm,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_inspect_command_search_state_qm_value),
	    Qslot_value_reclaimer);
    G2_DEFSTRUCT_STRUCTURE_NAME_package = 
	    STATIC_PACKAGE("G2-DEFSTRUCT-STRUCTURE-NAME");
    Qg2_defstruct_structure_name_inspect_command_spot_g2_struct = 
	    STATIC_SYMBOL("INSPECT-COMMAND-SPOT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qinspect_command_spot = STATIC_SYMBOL("INSPECT-COMMAND-SPOT",AB_package);
    Qab_name_of_unique_structure_type = 
	    STATIC_SYMBOL("AB-NAME-OF-UNIQUE-STRUCTURE-TYPE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_inspect_command_spot_g2_struct,
	    Qinspect_command_spot,Qab_name_of_unique_structure_type);
    Qunique_structure_type_of_ab_name_qm = 
	    STATIC_SYMBOL("UNIQUE-STRUCTURE-TYPE-OF-AB-NAME\?",AB_package);
    mutate_global_property(Qinspect_command_spot,
	    Qg2_defstruct_structure_name_inspect_command_spot_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_inspect_command_spot == UNBOUND)
	The_type_description_of_inspect_command_spot = Nil;
    string_constant_217 = 
	    STATIC_STRING("43Dy8m83j7y1q83j7y832my83*Cy83Qy8n8k1l832my0000001l1m8x832myk3Cyk0k0");
    temp = The_type_description_of_inspect_command_spot;
    The_type_description_of_inspect_command_spot = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_217));
    Qtype_description_of_unique_type_name_of_gensym_structure = 
	    STATIC_SYMBOL("TYPE-DESCRIPTION-OF-UNIQUE-TYPE-NAME-OF-GENSYM-STRUCTURE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_inspect_command_spot_g2_struct,
	    The_type_description_of_inspect_command_spot,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    Qtype_description_of_type = STATIC_SYMBOL("TYPE-DESCRIPTION-OF-TYPE",
	    AB_package);
    mutate_global_property(Qinspect_command_spot,
	    The_type_description_of_inspect_command_spot,
	    Qtype_description_of_type);
    Qoutstanding_inspect_command_spot_count = 
	    STATIC_SYMBOL("OUTSTANDING-INSPECT-COMMAND-SPOT-COUNT",AB_package);
    Qinspect_command_spot_structure_memory_usage = 
	    STATIC_SYMBOL("INSPECT-COMMAND-SPOT-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_218 = STATIC_STRING("1q83j7y8s83-ZNy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_inspect_command_spot_count);
    push_optimized_constant(Qinspect_command_spot_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_218));
    Qchain_of_available_inspect_command_spots = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-INSPECT-COMMAND-SPOTS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_inspect_command_spots,
	    Chain_of_available_inspect_command_spots);
    Qutilities2 = STATIC_SYMBOL("UTILITIES2",AB_package);
    record_system_variable(Qchain_of_available_inspect_command_spots,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qinspect_command_spot_count = 
	    STATIC_SYMBOL("INSPECT-COMMAND-SPOT-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinspect_command_spot_count,
	    Inspect_command_spot_count);
    record_system_variable(Qinspect_command_spot_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qinspect_command_spot_structure_memory_usage,
	    STATIC_FUNCTION(inspect_command_spot_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_inspect_command_spot_count,
	    STATIC_FUNCTION(outstanding_inspect_command_spot_count,NIL,
	    FALSE,0,0));
    Qreclaim_structure = STATIC_SYMBOL("RECLAIM-STRUCTURE",AB_package);
    reclaim_structure_for_inspect_command_spot_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_inspect_command_spot,NIL,
	    FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qinspect_command_spot,
	    reclaim_structure_for_inspect_command_spot_1);
    Kunknown = STATIC_SYMBOL("UNKNOWN",Pkeyword);
    Qinnermost_spot_p = STATIC_SYMBOL("INNERMOST-SPOT-P",AB_package);
    Qenclosing_spot_type = STATIC_SYMBOL("ENCLOSING-SPOT-TYPE",AB_package);
    Qspot = STATIC_SYMBOL("SPOT",AB_package);
    Qabstract_type = STATIC_SYMBOL("ABSTRACT-TYPE",AB_package);
    Qtype_of_frame_represented = STATIC_SYMBOL("TYPE-OF-FRAME-REPRESENTED",
	    AB_package);
    type_description = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinspect_command_spot),
	    Qtype_description_of_type);
    temp_2 = list_star(5,LIST_2(Qinnermost_spot_p,Qt),
	    LIST_2(Qenclosing_spot_type,Qspot),LIST_2(Qabstract_type,Qnil),
	    LIST_2(Qtype_of_frame_represented,Qinspect_command),
	    ISVREF(type_description,(SI_Long)10L));
    SVREF(type_description,FIX((SI_Long)10L)) = temp_2;
    Qgenerate_spot_for_inspect_command = 
	    STATIC_SYMBOL("GENERATE-SPOT-FOR-INSPECT-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qgenerate_spot_for_inspect_command,
	    STATIC_FUNCTION(generate_spot_for_inspect_command,NIL,FALSE,2,2));
    Qgenerate_spot = STATIC_SYMBOL("GENERATE-SPOT",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qgenerate_spot_for_inspect_command);
    set_get(Qinspect_command,Qgenerate_spot,temp_2);
    Qclasses_which_define = STATIC_SYMBOL("CLASSES-WHICH-DEFINE",AB_package);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qgenerate_spot),
	    Qclasses_which_define);
    temp_2 = CONS(Qinspect_command,temp);
    mutate_global_property(Qgenerate_spot,temp_2,Qclasses_which_define);
    Qquery_command = STATIC_SYMBOL("QUERY-COMMAND",AB_package);
    Qcompile_query_command_for_slot = 
	    STATIC_SYMBOL("COMPILE-QUERY-COMMAND-FOR-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qcompile_query_command_for_slot,
	    STATIC_FUNCTION(compile_query_command_for_slot,NIL,TRUE,3,6));
    Qslot_value_compiler = STATIC_SYMBOL("SLOT-VALUE-COMPILER",AB_package);
    mutate_global_property(Qquery_command,
	    SYMBOL_FUNCTION(Qcompile_query_command_for_slot),
	    Qslot_value_compiler);
    Quse_slot_value_compiler_for_default_overrides_p = 
	    STATIC_SYMBOL("USE-SLOT-VALUE-COMPILER-FOR-DEFAULT-OVERRIDES-P",
	    AB_package);
    mutate_global_property(Qquery_command,T,
	    Quse_slot_value_compiler_for_default_overrides_p);
    Qtemporary_name_number_1 = STATIC_SYMBOL("TEMPORARY-NAME-NUMBER-1",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtemporary_name_number_1,
	    Temporary_name_number_1);
    Qqueries = STATIC_SYMBOL("QUERIES",AB_package);
    Kfuncall = STATIC_SYMBOL("FUNCALL",Pkeyword);
    string_constant_219 = STATIC_STRING("TEMPORARY-NAME");
    list_constant_29 = STATIC_LIST((SI_Long)3L,Kfuncall,Qgentemp,
	    string_constant_219);
    record_system_variable(Qtemporary_name_number_1,Qqueries,
	    list_constant_29,Qnil,Qnil,Qnil,Qnil);
    Qtemporary_name_number_2 = STATIC_SYMBOL("TEMPORARY-NAME-NUMBER-2",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qtemporary_name_number_2,
	    Temporary_name_number_2);
    record_system_variable(Qtemporary_name_number_2,Qqueries,
	    list_constant_29,Qnil,Qnil,Qnil,Qnil);
    Qsource_position = STATIC_SYMBOL("SOURCE-POSITION",AB_package);
    Qhighlight = STATIC_SYMBOL("HIGHLIGHT",AB_package);
    Qshow_on_a_workspace = STATIC_SYMBOL("SHOW-ON-A-WORKSPACE",AB_package);
    Qdisplay_a_table = STATIC_SYMBOL("DISPLAY-A-TABLE",AB_package);
    Qdisplay_a_table_columnwise = 
	    STATIC_SYMBOL("DISPLAY-A-TABLE-COLUMNWISE",AB_package);
    Qvisit = STATIC_SYMBOL("VISIT",AB_package);
    Qwrite_to_a_file = STATIC_SYMBOL("WRITE-TO-A-FILE",AB_package);
    Qrecompile = STATIC_SYMBOL("RECOMPILE",AB_package);
    list_constant_3 = STATIC_LIST((SI_Long)8L,Qhighlight,Qreplace,
	    Qshow_on_a_workspace,Qdisplay_a_table,
	    Qdisplay_a_table_columnwise,Qvisit,Qwrite_to_a_file,Qrecompile);
    Qclass_qualified_method = STATIC_SYMBOL("CLASS-QUALIFIED-METHOD",
	    AB_package);
    Qevery_instance_such_that = STATIC_SYMBOL("EVERY-INSTANCE-SUCH-THAT",
	    AB_package);
    Qg2_lambda = STATIC_SYMBOL("G2-LAMBDA",AB_package);
    Ktemporary_name = STATIC_SYMBOL("TEMPORARY-NAME",Pkeyword);
    Qab_method = STATIC_SYMBOL("METHOD",AB_package);
    list_constant_30 = STATIC_LIST((SI_Long)2L,Qab_class,Qab_method);
    list_constant_31 = STATIC_LIST((SI_Long)2L,Ktemporary_name,
	    list_constant_30);
    list_constant_32 = STATIC_CONS(list_constant_31,Qnil);
    list_constant_33 = STATIC_LIST((SI_Long)3L,Qg2_lambda,list_constant_32,
	    Qtrue);
    Ksource_text = STATIC_SYMBOL("SOURCE-TEXT",Pkeyword);
    list_constant_34 = STATIC_LIST_STAR((SI_Long)4L,
	    Qevery_instance_such_that,Kname,list_constant_33,Ksource_text);
    list_constant_35 = STATIC_CONS(list_constant_34,Qnil);
    list_constant_4 = STATIC_LIST((SI_Long)2L,Qsource_position,
	    list_constant_35);
    Qitem = STATIC_SYMBOL("ITEM",AB_package);
    list_constant_36 = STATIC_LIST((SI_Long)2L,Qab_class,Qitem);
    list_constant_37 = STATIC_LIST((SI_Long)2L,Ktemporary_name,
	    list_constant_36);
    list_constant_46 = STATIC_CONS(list_constant_37,Qnil);
    Qab_or = STATIC_SYMBOL("OR",AB_package);
    Qthere_exists_literal = STATIC_SYMBOL("THERE-EXISTS-LITERAL",AB_package);
    Qrole_server = STATIC_SYMBOL("ROLE-SERVER",AB_package);
    Qname = STATIC_SYMBOL("NAME",AB_package);
    list_constant_38 = STATIC_LIST((SI_Long)2L,Qrole_server,Qname);
    Ktemporary_name_2 = STATIC_SYMBOL("TEMPORARY-NAME-2",Pkeyword);
    list_constant_39 = STATIC_CONS(list_constant_38,Ktemporary_name_2);
    Kargument_1 = STATIC_SYMBOL("ARGUMENT-1",Pkeyword);
    list_constant_42 = STATIC_LIST((SI_Long)2L,list_constant_39,Kargument_1);
    list_constant_40 = STATIC_LIST((SI_Long)2L,Qquote,Kname);
    list_constant_41 = STATIC_CONS(list_constant_40,Qnil);
    list_constant_43 = STATIC_LIST_STAR((SI_Long)3L,Qnum_eq,
	    Ktemporary_name_2,list_constant_41);
    list_constant_44 = STATIC_LIST((SI_Long)3L,Qthere_exists_literal,
	    list_constant_42,list_constant_43);
    Qg2_inspect_internal_name_for_debugging_p = 
	    STATIC_SYMBOL("G2-INSPECT-INTERNAL-NAME-FOR-DEBUGGING-P",
	    AB_package);
    list_constant_45 = STATIC_LIST_STAR((SI_Long)3L,
	    Qg2_inspect_internal_name_for_debugging_p,Kargument_1,
	    list_constant_41);
    list_constant_47 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_44,
	    list_constant_45);
    list_constant_48 = STATIC_LIST((SI_Long)3L,Qg2_lambda,list_constant_46,
	    list_constant_47);
    list_constant_49 = STATIC_LIST((SI_Long)3L,Qevery_instance_such_that,
	    Qitem,list_constant_48);
    list_constant_50 = STATIC_CONS(list_constant_49,Ksource_text);
    list_constant_5 = STATIC_LIST((SI_Long)2L,Qsource_position,
	    list_constant_50);
    Qcleanup_for_inspect_command = 
	    STATIC_SYMBOL("CLEANUP-FOR-INSPECT-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_inspect_command,
	    STATIC_FUNCTION(cleanup_for_inspect_command,NIL,FALSE,1,1));
    Qcleanup = STATIC_SYMBOL("CLEANUP",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_inspect_command);
    set_get(Qinspect_command,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qinspect_command,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qavailable_frame_vector = STATIC_SYMBOL("AVAILABLE-FRAME-VECTOR",
	    AB_package);
    Qg2_defstruct_structure_name_class_description_g2_struct = 
	    STATIC_SYMBOL("CLASS-DESCRIPTION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qpriority_queue = STATIC_SYMBOL("PRIORITY-QUEUE",AB_package);
    Ksymbol = STATIC_SYMBOL("SYMBOL",Pkeyword);
    list_constant_51 = STATIC_CONS(list_constant_38,Ksymbol);
    list_constant_52 = STATIC_CONS(Ksymbol,Qnil);
    list_constant_55 = STATIC_CONS(list_constant_51,list_constant_52);
    Ka = STATIC_SYMBOL("A",Pkeyword);
    list_constant_53 = STATIC_CONS(Qquote,list_constant_52);
    list_constant_54 = STATIC_CONS(list_constant_53,Qnil);
    list_constant_56 = STATIC_LIST_STAR((SI_Long)3L,Qnum_eq,Ka,
	    list_constant_54);
    list_constant_58 = STATIC_LIST((SI_Long)3L,Qthere_exists_literal,
	    list_constant_55,list_constant_56);
    Kb = STATIC_SYMBOL("B",Pkeyword);
    Kc = STATIC_SYMBOL("C",Pkeyword);
    list_constant_57 = STATIC_LIST((SI_Long)2L,Qquote,Kc);
    list_constant_59 = STATIC_LIST((SI_Long)3L,
	    Qg2_inspect_internal_name_for_debugging_p,Kb,list_constant_57);
    list_constant_6 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_58,
	    list_constant_59);
    Qnamed_by_debugging_name = STATIC_SYMBOL("NAMED-BY-DEBUGGING-NAME",
	    AB_package);
    Qnamed_by = STATIC_SYMBOL("NAMED-BY",AB_package);
    Qhas_a_name = STATIC_SYMBOL("HAS-A-NAME",AB_package);
    list_constant_62 = STATIC_CONS(Qhas_a_name,list_constant_52);
    Qis = STATIC_SYMBOL("IS",AB_package);
    list_constant_60 = STATIC_CONS(Ka,Qnil);
    list_constant_61 = STATIC_LIST_STAR((SI_Long)3L,Qthe,list_constant_38,
	    list_constant_60);
    list_constant_63 = STATIC_LIST_STAR((SI_Long)3L,Qis,list_constant_61,
	    list_constant_54);
    list_constant_7 = STATIC_LIST((SI_Long)3L,Qand,list_constant_62,
	    list_constant_63);
    list_constant_64 = STATIC_LIST((SI_Long)2L,Qquote,Kb);
    list_constant_65 = STATIC_LIST((SI_Long)3L,
	    Qg2_inspect_internal_name_for_debugging_p,Ka,list_constant_64);
    list_constant_8 = STATIC_LIST((SI_Long)3L,Qab_or,list_constant_7,
	    list_constant_65);
    Qexists = STATIC_SYMBOL("EXISTS",AB_package);
    Qworkspace = STATIC_SYMBOL("WORKSPACE",AB_package);
    Qkb_workspace = STATIC_SYMBOL("KB-WORKSPACE",AB_package);
    list_constant_66 = STATIC_LIST((SI_Long)3L,Qrole_server,Qworkspace,
	    Qkb_workspace);
    list_constant_67 = STATIC_LIST_STAR((SI_Long)3L,Qthe,list_constant_66,
	    list_constant_52);
    list_constant_69 = STATIC_LIST((SI_Long)2L,Qexists,list_constant_67);
    Qsame_as = STATIC_SYMBOL("SAME-AS",AB_package);
    list_constant_68 = STATIC_LIST_STAR((SI_Long)3L,Qthe,list_constant_66,
	    list_constant_60);
    list_constant_70 = STATIC_LIST_STAR((SI_Long)3L,Qsame_as,
	    list_constant_68,list_constant_52);
    list_constant_9 = STATIC_LIST((SI_Long)3L,Qand,list_constant_69,
	    list_constant_70);
    Qany = STATIC_SYMBOL("ANY",AB_package);
    if (Match_pattern_for_inspect_binding_vector == UNBOUND)
	Match_pattern_for_inspect_binding_vector = make_array(1,
		FIX((SI_Long)3L));
    Kany = STATIC_SYMBOL("ANY",Pkeyword);
    Qg2_permit_inspector_within_restricted_license = 
	    STATIC_SYMBOL("G2-PERMIT-INSPECTOR-WITHIN-RESTRICTED-LICENSE",
	    AB_package);
    Qfunction_keeps_procedure_environment_valid_qm = 
	    STATIC_SYMBOL("FUNCTION-KEEPS-PROCEDURE-ENVIRONMENT-VALID\?",
	    AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_permit_inspector_within_restricted_license,
	    gensymed_symbol,Qfunction_keeps_procedure_environment_valid_qm);
    Override_limited_license_block_on_inspect_qm = Nil;
    SET_SYMBOL_FUNCTION(Qg2_permit_inspector_within_restricted_license,
	    STATIC_FUNCTION(g2_permit_inspector_within_restricted_license,
	    NIL,FALSE,0,0));
    Qinspect_command_history_list_max_size = 
	    STATIC_SYMBOL("INSPECT-COMMAND-HISTORY-LIST-MAX-SIZE",AB_package);
    SET_SYMBOL_VALUE(Qinspect_command_history_list_max_size,FIX((SI_Long)50L));
    if (Inspect_command_history_list == UNBOUND)
	Inspect_command_history_list = Nil;
    string_constant_4 = 
	    STATIC_STRING("~% There exists ~D command history.~%~%");
    string_constant_5 = STATIC_STRING("No inspect command history.");
    SET_SYMBOL_FUNCTION(Qshow_inspect_command_history_on_a_workspace,
	    STATIC_FUNCTION(show_inspect_command_history_on_a_workspace,
	    NIL,FALSE,1,1));
    Qexecute_command_for_inspect_history = 
	    STATIC_SYMBOL("EXECUTE-COMMAND-FOR-INSPECT-HISTORY",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_command_for_inspect_history,
	    STATIC_FUNCTION(execute_command_for_inspect_history,NIL,FALSE,
	    1,1));
    Qexecute_command = STATIC_SYMBOL("EXECUTE-COMMAND",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qexecute_command_for_inspect_history);
    set_get(Qinspect_history,Qexecute_command,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexecute_command),
	    Qclasses_which_define);
    temp_2 = CONS(Qinspect_history,temp);
    mutate_global_property(Qexecute_command,temp_2,Qclasses_which_define);
    Qexecute_command_for_inspect_command = 
	    STATIC_SYMBOL("EXECUTE-COMMAND-FOR-INSPECT-COMMAND",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_command_for_inspect_command,
	    STATIC_FUNCTION(execute_command_for_inspect_command,NIL,FALSE,
	    1,1));
    temp_2 = SYMBOL_FUNCTION(Qexecute_command_for_inspect_command);
    set_get(Qinspect_command,Qexecute_command,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexecute_command),
	    Qclasses_which_define);
    temp_2 = CONS(Qinspect_command,temp);
    mutate_global_property(Qexecute_command,temp_2,Qclasses_which_define);
    Qexecute_inspect_command = STATIC_SYMBOL("EXECUTE-INSPECT-COMMAND",
	    AB_package);
    list_constant_10 = STATIC_LIST((SI_Long)6L,Qshow_on_a_workspace,Qvisit,
	    Qwrite_to_a_file,Qrecompile,Qdisplay_a_table,
	    Qdisplay_a_table_columnwise);
    Qcolumnwise = STATIC_SYMBOL("COLUMNWISE",AB_package);
    Qnon_word = STATIC_SYMBOL("NON-WORD",AB_package);
    Qshow_class_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-CLASS-HIERARCHY-ON-A-WORKSPACE",AB_package);
    Qshow_workspace_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-WORKSPACE-HIERARCHY-ON-A-WORKSPACE",
	    AB_package);
    Qshow_procedure_invocation_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-PROCEDURE-INVOCATION-HIERARCHY-ON-A-WORKSPACE",
	    AB_package);
    Qshow_method_inheritance_path_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-METHOD-INHERITANCE-PATH-ON-A-WORKSPACE",
	    AB_package);
    Qshow_procedure_calling_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-PROCEDURE-CALLING-HIERARCHY-ON-A-WORKSPACE",
	    AB_package);
    Qshow_procedure_caller_hierarchy_on_a_workspace = 
	    STATIC_SYMBOL("SHOW-PROCEDURE-CALLER-HIERARCHY-ON-A-WORKSPACE",
	    AB_package);
    Qcheck_for_consistent_modularization = 
	    STATIC_SYMBOL("CHECK-FOR-CONSISTENT-MODULARIZATION",AB_package);
    Qinspect_kb_for_modularity_problems = 
	    STATIC_SYMBOL("INSPECT-KB-FOR-MODULARITY-PROBLEMS",AB_package);
    Qversion_control = STATIC_SYMBOL("VERSION-CONTROL",AB_package);
    SET_SYMBOL_FUNCTION(Qexecute_inspect_command,
	    STATIC_FUNCTION(execute_inspect_command,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qinspect_kb_for_modularity_problems,
	    STATIC_FUNCTION(inspect_kb_for_modularity_problems,NIL,FALSE,1,1));
    Qcell_array_element = STATIC_SYMBOL("CELL-ARRAY-ELEMENT",AB_package);
    Qcell_array = STATIC_SYMBOL("CELL-ARRAY",AB_package);
    Qempty_expression_cell = STATIC_SYMBOL("EMPTY-EXPRESSION-CELL",AB_package);
    Qexpression_cell_updated_for_kb_search_state = 
	    STATIC_SYMBOL("EXPRESSION-CELL-UPDATED-FOR-KB-SEARCH-STATE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qexpression_cell_updated_for_kb_search_state,
	    STATIC_FUNCTION(expression_cell_updated_for_kb_search_state,
	    NIL,FALSE,5,5));
    Qkb_search_state = STATIC_SYMBOL("KB-SEARCH-STATE",AB_package);
    Qexpression_cell_updated = STATIC_SYMBOL("EXPRESSION-CELL-UPDATED",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qexpression_cell_updated_for_kb_search_state);
    set_get(Qkb_search_state,Qexpression_cell_updated,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qexpression_cell_updated),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_search_state,temp);
    mutate_global_property(Qexpression_cell_updated,temp_2,
	    Qclasses_which_define);
    Qname_or_names_for_frame = STATIC_SYMBOL("NAME-OR-NAMES-FOR-FRAME",
	    AB_package);
    Qname_for_debugging = STATIC_SYMBOL("NAME-FOR-DEBUGGING",AB_package);
    Qinspection_instance_counter = 
	    STATIC_SYMBOL("INSPECTION-INSTANCE-COUNTER",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qinspection_instance_counter,
	    Inspection_instance_counter);
    record_system_variable(Qinspection_instance_counter,Qqueries,
	    FIX((SI_Long)0L),Qnil,Qnil,Qnil,Qnil);
    Qtemporary_workspace = STATIC_SYMBOL("TEMPORARY-WORKSPACE",AB_package);
    string_constant_6 = STATIC_STRING("INSPECT-~d");
    Qclass_hierarchy_borderless_free_text_format = 
	    STATIC_SYMBOL("CLASS-HIERARCHY-BORDERLESS-FREE-TEXT-FORMAT",
	    AB_package);
    string_constant_220 = 
	    STATIC_STRING("13fy83-My83ny1l83-uy83ty3Gy83syz83uyo83-7y3N+y83*3y3G+y83*+y3u+y83kyk83-=yw83-By083-Ny83fy83*ky83fy83byq83ayn83Wyq83cym83*=yk83*");
    string_constant_221 = STATIC_STRING("1yk83*0yk83**yk83*ay3RCy83iy3RCy");
    Qformat_description = STATIC_SYMBOL("FORMAT-DESCRIPTION",AB_package);
    mutate_global_property(Qclass_hierarchy_borderless_free_text_format,
	    regenerate_optimized_constant(LIST_2(string_constant_220,
	    string_constant_221)),Qformat_description);
    SET_SYMBOL_FUNCTION(Qwrite_class_hierarchy_to_file,
	    STATIC_FUNCTION(write_class_hierarchy_to_file,NIL,FALSE,3,3));
    array_constant_5 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)0L,(SI_Long)124L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)6L,(SI_Long)3L);
    UBYTE_16_ISASET_1(array_constant_5,(SI_Long)7L,(SI_Long)57344L);
    string_constant_7 = STATIC_STRING(" -- ~d instance~a");
    string_constant_8 = STATIC_STRING("s");
    string_constant_9 = STATIC_STRING("");
    Qsymbol_properties_hash_table = 
	    STATIC_SYMBOL("SYMBOL-PROPERTIES-HASH-TABLE",AB_package);
    Qab_gensym = STATIC_SYMBOL("GENSYM",AB_package);
    Qhash_symbol_or_frame = STATIC_SYMBOL("HASH-SYMBOL-OR-FRAME",AB_package);
    Qsxhashw = STATIC_SYMBOL("SXHASHW",AB_package);
    Qhorizontal = STATIC_SYMBOL("HORIZONTAL",AB_package);
    Qvertical = STATIC_SYMBOL("VERTICAL",AB_package);
    Qsubclasses_of_class_for_graph_display = 
	    STATIC_SYMBOL("SUBCLASSES-OF-CLASS-FOR-GRAPH-DISPLAY",AB_package);
    Qsubcomponents_of_workspace_or_item_for_display = 
	    STATIC_SYMBOL("SUBCOMPONENTS-OF-WORKSPACE-OR-ITEM-FOR-DISPLAY",
	    AB_package);
    Qshort_representation_of_symbol_or_frame = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-OF-SYMBOL-OR-FRAME",
	    AB_package);
    Qshort_representation_of_symbol_or_frame_or_top_level = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-OF-SYMBOL-OR-FRAME-OR-TOP-LEVEL",
	    AB_package);
    string_constant_10 = 
	    STATIC_STRING("Cannot show the class hierarchy for ~a, since it is not ~a.");
    string_constant_11 = STATIC_STRING("a subclass of item");
    string_constant_12 = STATIC_STRING("a class");
    string_constant_13 = 
	    STATIC_STRING("Cannot show the workspace hierarchy for ~a, since it is not ~\n              the name of an item.");
    Qclass_definition = STATIC_SYMBOL("CLASS-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qsubclasses_of_class_for_graph_display,
	    STATIC_FUNCTION(subclasses_of_class_for_graph_display,NIL,
	    FALSE,2,2));
    Qnext_methods_for_graph_display = 
	    STATIC_SYMBOL("NEXT-METHODS-FOR-GRAPH-DISPLAY",AB_package);
    string_constant_14 = 
	    STATIC_STRING("There are no methods defined on the class hierarchy for ~a.");
    string_constant_15 = 
	    STATIC_STRING("There are no ~a methods defined on the class hierarchy for ~a.");
    string_constant_16 = 
	    STATIC_STRING("Cannot show the method hierarchy for ~a because it is not ~\n          a defined class.");
    Qmethod_declaration = STATIC_SYMBOL("METHOD-DECLARATION",AB_package);
    SET_SYMBOL_FUNCTION(Qnext_methods_for_graph_display,
	    STATIC_FUNCTION(next_methods_for_graph_display,NIL,FALSE,2,2));
    string_constant_17 = STATIC_STRING("~a");
    Qsmall = STATIC_SYMBOL("SMALL",AB_package);
    SET_SYMBOL_FUNCTION(Qshort_representation_of_symbol_or_frame,
	    STATIC_FUNCTION(short_representation_of_symbol_or_frame,NIL,
	    FALSE,1,1));
    Qclass_qualified_name = STATIC_SYMBOL("CLASS-QUALIFIED-NAME",AB_package);
    Qshort_representation_table_format = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-TABLE-FORMAT",AB_package);
    Qshort_representation_class_format = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-CLASS-FORMAT",AB_package);
    string_constant_18 = STATIC_STRING("~a, a symbol");
    string_constant_19 = STATIC_STRING("~a, a generic method");
    Qfree_text = STATIC_SYMBOL("FREE-TEXT",AB_package);
    Qfont_for_free_text = STATIC_SYMBOL("FONT-FOR-FREE-TEXT",AB_package);
    SET_SYMBOL_FUNCTION(Qhash_symbol_or_frame,
	    STATIC_FUNCTION(hash_symbol_or_frame,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qsubcomponents_of_workspace_or_item_for_display,
	    STATIC_FUNCTION(subcomponents_of_workspace_or_item_for_display,
	    NIL,FALSE,2,2));
    Qsubnodes_of_method_hierarchy = 
	    STATIC_SYMBOL("SUBNODES-OF-METHOD-HIERARCHY",AB_package);
    string_constant_20 = 
	    STATIC_STRING("Cannot show the method hierarchy for ~a, since no methods are defined for it.");
    SET_SYMBOL_FUNCTION(Qshow_method_hierarchy_on_a_workspace,
	    STATIC_FUNCTION(show_method_hierarchy_on_a_workspace,NIL,TRUE,
	    1,2));
    SET_SYMBOL_FUNCTION(Qsubnodes_of_method_hierarchy,
	    STATIC_FUNCTION(subnodes_of_method_hierarchy,NIL,FALSE,2,2));
    Qknowledge_base = STATIC_SYMBOL("KNOWLEDGE-BASE",AB_package);
    SET_SYMBOL_FUNCTION(Qshort_representation_of_symbol_or_frame_or_top_level,
	    STATIC_FUNCTION(short_representation_of_symbol_or_frame_or_top_level,
	    NIL,FALSE,1,1));
    Qtop_level_kb_module_qm = STATIC_SYMBOL("TOP-LEVEL-KB-MODULE\?",
	    AB_package);
    list_constant_11 = STATIC_CONS(Qtop_level_kb_module_qm,Qnil);
    Qget_directly_required_module_information_system_tables = 
	    STATIC_SYMBOL("GET-DIRECTLY-REQUIRED-MODULE-INFORMATION-SYSTEM-TABLES",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qget_directly_required_module_information_system_tables,
	    STATIC_FUNCTION(get_directly_required_module_information_system_tables,
	    NIL,TRUE,1,2));
    Qmake_attributes_table_for_module_information_in_hierarchy = 
	    STATIC_SYMBOL("MAKE-ATTRIBUTES-TABLE-FOR-MODULE-INFORMATION-IN-HIERARCHY",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qmake_attributes_table_for_module_information_in_hierarchy,
	    STATIC_FUNCTION(make_attributes_table_for_module_information_in_hierarchy,
	    NIL,FALSE,1,1));
    string_constant_21 = STATIC_STRING("No module hierarchy ~a~a");
    string_constant_22 = STATIC_STRING("can be shown for ");
    string_constant_23 = 
	    STATIC_STRING("exists, because the top-level module is unnamed.");
    string_constant_24 = 
	    STATIC_STRING("Top-Level Module-Information System Table: ");
    Qmodule_information = STATIC_SYMBOL("MODULE-INFORMATION",AB_package);
    array_constant_6 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)0L,(SI_Long)77L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)4L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)6L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)8L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)12L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)13L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)14L,(SI_Long)113L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)15L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)16L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)17L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)19L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)20L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)21L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)22L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)23L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)24L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)25L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)26L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)27L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)28L,(SI_Long)75L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)29L,(SI_Long)66L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)30L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)38L,(SI_Long)31L);
    UBYTE_16_ISASET_1(array_constant_6,(SI_Long)39L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qshow_module_hierarchy_on_a_workspace,
	    STATIC_FUNCTION(show_module_hierarchy_on_a_workspace,NIL,TRUE,
	    1,2));
    Qprocedure = STATIC_SYMBOL("PROCEDURE",AB_package);
    string_constant_25 = 
	    STATIC_STRING("Cannot show the procedure reference hierarchy for ~a, since it is not a procedure.");
    Qreferencing_procedures_for_graph_display = 
	    STATIC_SYMBOL("REFERENCING-PROCEDURES-FOR-GRAPH-DISPLAY",
	    AB_package);
    Qreferenced_procedures_for_graph_display = 
	    STATIC_SYMBOL("REFERENCED-PROCEDURES-FOR-GRAPH-DISPLAY",
	    AB_package);
    Qshort_representation_for_ref_hierarchy = 
	    STATIC_SYMBOL("SHORT-REPRESENTATION-FOR-REF-HIERARCHY",AB_package);
    SET_SYMBOL_FUNCTION(Qshort_representation_for_ref_hierarchy,
	    STATIC_FUNCTION(short_representation_for_ref_hierarchy,NIL,
	    TRUE,1,4));
    SET_SYMBOL_FUNCTION(Qreferencing_procedures_for_graph_display,
	    STATIC_FUNCTION(referencing_procedures_for_graph_display,NIL,
	    TRUE,1,2));
    SET_SYMBOL_FUNCTION(Qreferenced_procedures_for_graph_display,
	    STATIC_FUNCTION(referenced_procedures_for_graph_display,NIL,
	    TRUE,1,2));
    Qprocedure_call = STATIC_SYMBOL("PROCEDURE-CALL",AB_package);
    if (Current_remote_search_representation_qm == UNBOUND)
	Current_remote_search_representation_qm = Nil;
    Qentity = STATIC_SYMBOL("ENTITY",AB_package);
    list_constant_71 = STATIC_CONS(Qentity,Qnil);
    check_if_superior_classes_are_defined(Qkb_search_state,list_constant_71);
    string_constant_222 = 
	    STATIC_STRING("13gy4z8r83TMy83TMy8323y8323y00001p1m8p83TOy1l8l1l8o1l83Fy1l83-3y000004z8r83TIy83TIy8323y8323y00001m1l8l1l8o000004z8r83MKy83MKy83");
    string_constant_223 = 
	    STATIC_STRING("23y8323y00001m1l8l1l8o000004z8r83MQy83MQy8323y8323y00001m1l8l1l8o000004z8r83MJy83MJy8323y8323y00001m1l8l1l8o000004z8r83Sty83Sty8");
    string_constant_224 = 
	    STATIC_STRING("323y8323y00001o1m8p83Suy1l8l1l8o1l83Fy000004z8r832My832My8323y8323y00001n1l8l1l8o1l83Fy000004z8r836Ay836Ay8323y8323y00001n1l8l1l");
    string_constant_225 = 
	    STATIC_STRING("8o1l83Fy000004z8r83X9y83X9y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83cJy83cJy8323y8323y0k001o1m8p83Sy1l8l1l8o1l83Fy000004z8r83Wly");
    string_constant_226 = 
	    STATIC_STRING("83Wly8323y8323y0k001o1m8p83Sy1l8l1l8o1l83Fy000004z8r835ty835ty8323y8323y0k001n1l8l1l8o1l83Fy000004z8r835sy835sy8323y8323y0k001n1");
    string_constant_227 = 
	    STATIC_STRING("l8l1l8o1l83Fy000004z8r83Wmy83Wmy8323y8323y0k001o1m8p83Sy1l8l1l8o1l83Fy000004z8r832By832By8323y8323y0k001n1l8l1l8o1l83Fy000004z8r");
    string_constant_228 = 
	    STATIC_STRING("835Ay835Ay8323y8323y00001n1l8l1l8o1l83Fy000004z8r83Ggy83Ggy8323y8323y00001o1l8l1l8o1l83Fy1l83Ny000004z8r83LUy83LUy8323y8323y0000");
    string_constant_229 = 
	    STATIC_STRING("1n1l8l1l8o1l83Fy000004z8r83e6y83e6y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83c0y83c0y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83c4y");
    string_constant_230 = 
	    STATIC_STRING("83c4y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83K1y83K1y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83bNy83bNy8323y8323y00001n1l8l1l8o1");
    string_constant_231 = 
	    STATIC_STRING("l83Fy000004z8r83JXy83JXy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83aTy83aTy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83XDy83XDy8323y8");
    string_constant_232 = 
	    STATIC_STRING("323y00001n1l8l1l8o1l83Fy000004z8r83Tqy83Tqy8323y8323y0k001n1l8l1l8o1l83Fy000004z8r83cGy83cGy8323y8323y0k001n1l8l1l8o1l83Fy000004");
    string_constant_233 = 
	    STATIC_STRING("z8r83b6y83b6y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83MLy83MLy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83SLy83SLy8323y8323y00001n1");
    string_constant_234 = 
	    STATIC_STRING("l8l1l8o1l83Fy000004z8r83MHy83MHy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83Yhy83Yhy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83WXy83W");
    string_constant_235 = 
	    STATIC_STRING("Xy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83LRy83LRy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83SGy83SGy8323y8323y00001n1l8l1l8o1l83");
    string_constant_236 = 
	    STATIC_STRING("Fy000004z8r83Ury83Ury8323y8323y00001n1l8l1l8o1l83Fy000004z8r83V3y83V3y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83Woy83Woy8323y8323");
    string_constant_237 = 
	    STATIC_STRING("y00001n1l8l1l8o1l83Fy000004z8r83Usy83Usy8323y8323y03*OCy001n1l8l1l8o1l83Fy000004z8r83Vly83Vly8323y8323y0l001n1l8l1l8o1l83Fy00000");
    string_constant_238 = 
	    STATIC_STRING("4z8r83ajy83ajy8323y8323y0p001n1l8l1l8o1l83Fy000004z8r83T1y83T1y8323y8323y00001n1l8l1l8o1l83Fy000004z8r83TJy83TJy8323y8323y00001n");
    string_constant_239 = 
	    STATIC_STRING("1l8l1l8o1l83Fy000004z8r83TKy83TKy8323y8323y00001n1l8l1l8o1l83Fy000004z8r83TLy83TLy8323y8323y00001n1l8l1l8o1l83Fy00000");
    string_constant_240 = 
	    STATIC_STRING("13iy8q1m8323y1l83-+y1r83TMy01m8p83TOy8l8o83Fy83-3y1o83TIy08l8o1o83MKy08l8o1o83MQy08l8o1o83MJy08l8o1q83Sty01m8p83Suy8l8o83Fy1p832");
    string_constant_241 = 
	    STATIC_STRING("My08l8o83Fy1p836Ay08l8o83Fy1p83X9y08l8o83Fy1q83cJyk1m8p83Sy8l8o83Fy1q83Wlyk1m8p83Sy8l8o83Fy1p835tyk8l8o83Fy1p835syk8l8o83Fy1q83W");
    string_constant_242 = 
	    STATIC_STRING("myk1m8p83Sy8l8o83Fy1p832Byk8l8o83Fy1p835Ay08l8o83Fy1q83Ggy08l8o83Fy83Ny1p83LUy08l8o83Fy1p83e6y08l8o83Fy1p83c0y08l8o83Fy1p83c4y08");
    string_constant_243 = 
	    STATIC_STRING("l8o83Fy1p83K1y08l8o83Fy1p83bNy08l8o83Fy1p83JXy08l8o83Fy1p83aTy08l8o83Fy1p83XDy08l8o83Fy1p83Tqyk8l8o83Fy1p83cGyk8l8o83Fy1p83b6y08");
    string_constant_244 = 
	    STATIC_STRING("l8o83Fy1p83MLy08l8o83Fy1p83SLy08l8o83Fy1p83MHy08l8o83Fy1p83Yhy08l8o83Fy1p83WXy08l8o83Fy1p83LRy08l8o83Fy1p83SGy08l8o83Fy1p83Ury08");
    string_constant_245 = 
	    STATIC_STRING("l8o83Fy1p83V3y08l8o83Fy1p83Woy08l8o83Fy1p83Usy3*OCy8l8o83Fy1p83Vlyl8l8o83Fy1p83ajyp8l8o83Fy1p83T1y08l8o83Fy1p83TJy08l8o83Fy1p83T");
    string_constant_246 = STATIC_STRING("Ky08l8o83Fy1p83TLy08l8o83Fy");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(list(18,string_constant_222,
	    string_constant_223,string_constant_224,string_constant_225,
	    string_constant_226,string_constant_227,string_constant_228,
	    string_constant_229,string_constant_230,string_constant_231,
	    string_constant_232,string_constant_233,string_constant_234,
	    string_constant_235,string_constant_236,string_constant_237,
	    string_constant_238,string_constant_239));
    add_class_to_environment(9,Qkb_search_state,list_constant_71,Nil,temp,
	    Nil,temp_1,list_constant_71,
	    regenerate_optimized_constant(list(7,string_constant_240,
	    string_constant_241,string_constant_242,string_constant_243,
	    string_constant_244,string_constant_245,string_constant_246)),Nil);
    Qg2_cell_array = STATIC_SYMBOL("G2-CELL-ARRAY",AB_package);
    Qinitialize_for_kb_search_state = 
	    STATIC_SYMBOL("INITIALIZE-FOR-KB-SEARCH-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qinitialize_for_kb_search_state,
	    STATIC_FUNCTION(initialize_for_kb_search_state,NIL,FALSE,1,1));
    Qinitialize = STATIC_SYMBOL("INITIALIZE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qinitialize_for_kb_search_state);
    set_get(Qkb_search_state,Qinitialize,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qinitialize),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_search_state,temp);
    mutate_global_property(Qinitialize,temp_2,Qclasses_which_define);
    Qcleanup_for_kb_search_state = 
	    STATIC_SYMBOL("CLEANUP-FOR-KB-SEARCH-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qcleanup_for_kb_search_state,
	    STATIC_FUNCTION(cleanup_for_kb_search_state,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qcleanup_for_kb_search_state);
    set_get(Qkb_search_state,Qcleanup,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qcleanup),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_search_state,temp);
    mutate_global_property(Qcleanup,temp_2,Qclasses_which_define);
    Qactivate_for_kb_search_state = 
	    STATIC_SYMBOL("ACTIVATE-FOR-KB-SEARCH-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qactivate_for_kb_search_state,
	    STATIC_FUNCTION(activate_for_kb_search_state,NIL,FALSE,1,1));
    Qactivate = STATIC_SYMBOL("ACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qactivate_for_kb_search_state);
    set_get(Qkb_search_state,Qactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_search_state,temp);
    mutate_global_property(Qactivate,temp_2,Qclasses_which_define);
    Qdeactivate_for_kb_search_state = 
	    STATIC_SYMBOL("DEACTIVATE-FOR-KB-SEARCH-STATE",AB_package);
    SET_SYMBOL_FUNCTION(Qdeactivate_for_kb_search_state,
	    STATIC_FUNCTION(deactivate_for_kb_search_state,NIL,FALSE,1,1));
    Qdeactivate = STATIC_SYMBOL("DEACTIVATE",AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdeactivate_for_kb_search_state);
    set_get(Qkb_search_state,Qdeactivate,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdeactivate),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_search_state,temp);
    mutate_global_property(Qdeactivate,temp_2,Qclasses_which_define);
    Qtotal_number_of_items_to_examine = 
	    STATIC_SYMBOL("TOTAL-NUMBER-OF-ITEMS-TO-EXAMINE",AB_package);
    Qitems_to_examine = STATIC_SYMBOL("ITEMS-TO-EXAMINE",AB_package);
    alias_slot_name(3,Qtotal_number_of_items_to_examine,Qitems_to_examine,
	    Qnil);
    Qnumber_of_items_examined_so_far = 
	    STATIC_SYMBOL("NUMBER-OF-ITEMS-EXAMINED-SO-FAR",AB_package);
    Qitems_examined_so_far = STATIC_SYMBOL("ITEMS-EXAMINED-SO-FAR",AB_package);
    alias_slot_name(3,Qnumber_of_items_examined_so_far,
	    Qitems_examined_so_far,Qnil);
    Qkb_search_status_qm = STATIC_SYMBOL("KB-SEARCH-STATUS\?",AB_package);
    Qstatus = STATIC_SYMBOL("STATUS",AB_package);
    alias_slot_name(3,Qkb_search_status_qm,Qstatus,Qkb_search_state);
    Qitem_filter_for_kb_search_qm = 
	    STATIC_SYMBOL("ITEM-FILTER-FOR-KB-SEARCH\?",AB_package);
    Qfilter = STATIC_SYMBOL("FILTER",AB_package);
    alias_slot_name(3,Qitem_filter_for_kb_search_qm,Qfilter,Qkb_search_state);
    Qfile_stream_for_printing_search_results_qm = 
	    STATIC_SYMBOL("FILE-STREAM-FOR-PRINTING-SEARCH-RESULTS\?",
	    AB_package);
    Qreclaim_file_stream_for_printing_search_results_qm_value = 
	    STATIC_SYMBOL("RECLAIM-FILE-STREAM-FOR-PRINTING-SEARCH-RESULTS\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_file_stream_for_printing_search_results_qm_value,
	    STATIC_FUNCTION(reclaim_file_stream_for_printing_search_results_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qfile_stream_for_printing_search_results_qm,
	    SYMBOL_FUNCTION(Qreclaim_file_stream_for_printing_search_results_qm_value),
	    Qslot_value_reclaimer);
    Qold_kb_search_result_tables_and_text_boxes = 
	    STATIC_SYMBOL("OLD-KB-SEARCH-RESULT-TABLES-AND-TEXT-BOXES",
	    AB_package);
    Qreclaim_old_kb_search_result_tables_and_text_boxes_value = 
	    STATIC_SYMBOL("RECLAIM-OLD-KB-SEARCH-RESULT-TABLES-AND-TEXT-BOXES-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_old_kb_search_result_tables_and_text_boxes_value,
	    STATIC_FUNCTION(reclaim_old_kb_search_result_tables_and_text_boxes_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qold_kb_search_result_tables_and_text_boxes,
	    SYMBOL_FUNCTION(Qreclaim_old_kb_search_result_tables_and_text_boxes_value),
	    Qslot_value_reclaimer);
    Qframe_serial_number_for_kb_search = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-FOR-KB-SEARCH",AB_package);
    Qreclaim_frame_serial_number_for_kb_search_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-FOR-KB-SEARCH-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_kb_search_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_for_kb_search_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qframe_serial_number_for_kb_search,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_kb_search_value),
	    Qslot_value_reclaimer);
    Qframe_serial_number_for_kb_search_results_workspace = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-FOR-KB-SEARCH-RESULTS-WORKSPACE",
	    AB_package);
    Qreclaim_frame_serial_number_for_kb_search_results_workspace_value = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-FOR-KB-SEARCH-RESULTS-WORKSPACE-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_kb_search_results_workspace_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_for_kb_search_results_workspace_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qframe_serial_number_for_kb_search_results_workspace,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_kb_search_results_workspace_value),
	    Qslot_value_reclaimer);
    Qframe_serial_number_for_subcommand_menu_for_kb_search_qm = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-FOR-SUBCOMMAND-MENU-FOR-KB-SEARCH\?",
	    AB_package);
    Qreclaim_frame_serial_number_for_subcommand_menu_for_kb_search_qm_value 
	    = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-FOR-SUBCOMMAND-MENU-FOR-KB-SEARCH\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_subcommand_menu_for_kb_search_qm_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_for_subcommand_menu_for_kb_search_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qframe_serial_number_for_subcommand_menu_for_kb_search_qm,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_subcommand_menu_for_kb_search_qm_value),
	    Qslot_value_reclaimer);
    Qframe_serial_number_for_inspect_command_for_kb_search_qm = 
	    STATIC_SYMBOL("FRAME-SERIAL-NUMBER-FOR-INSPECT-COMMAND-FOR-KB-SEARCH\?",
	    AB_package);
    Qreclaim_frame_serial_number_for_inspect_command_for_kb_search_qm_value 
	    = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER-FOR-INSPECT-COMMAND-FOR-KB-SEARCH\?-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_inspect_command_for_kb_search_qm_value,
	    STATIC_FUNCTION(reclaim_frame_serial_number_for_inspect_command_for_kb_search_qm_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qframe_serial_number_for_inspect_command_for_kb_search_qm,
	    SYMBOL_FUNCTION(Qreclaim_frame_serial_number_for_inspect_command_for_kb_search_qm_value),
	    Qslot_value_reclaimer);
    array_constant_7 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)0L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)1L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)4L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)5L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)8L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)10L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)14L,(SI_Long)11L);
    UBYTE_16_ISASET_1(array_constant_7,(SI_Long)15L,(SI_Long)57344L);
    Qcurrent_computation_frame = 
	    STATIC_SYMBOL("*CURRENT-COMPUTATION-FRAME*",AB_package);
    string_constant_26 = STATIC_STRING(" of ");
    Qdenote_cell_array_element_for_kb_search_state = 
	    STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT-FOR-KB-SEARCH-STATE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdenote_cell_array_element_for_kb_search_state,
	    STATIC_FUNCTION(denote_cell_array_element_for_kb_search_state,
	    NIL,FALSE,3,3));
    Qdenote_cell_array_element = STATIC_SYMBOL("DENOTE-CELL-ARRAY-ELEMENT",
	    AB_package);
    temp_2 = SYMBOL_FUNCTION(Qdenote_cell_array_element_for_kb_search_state);
    set_get(Qkb_search_state,Qdenote_cell_array_element,temp_2);
    temp = 
	    getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdenote_cell_array_element),
	    Qclasses_which_define);
    temp_2 = CONS(Qkb_search_state,temp);
    mutate_global_property(Qdenote_cell_array_element,temp_2,
	    Qclasses_which_define);
    Qframe_notes_for_component_particulars = 
	    STATIC_SYMBOL("FRAME-NOTES-FOR-COMPONENT-PARTICULARS",AB_package);
    string_constant_27 = STATIC_STRING("~%~%but ");
    Qframe_note_writer_1 = STATIC_SYMBOL("FRAME-NOTE-WRITER-1",AB_package);
    Qitem_filter_qm = STATIC_SYMBOL("ITEM-FILTER\?",AB_package);
    Qwrite_item_filter_qm_from_slot = 
	    STATIC_SYMBOL("WRITE-ITEM-FILTER\?-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_item_filter_qm_from_slot,
	    STATIC_FUNCTION(write_item_filter_qm_from_slot,NIL,FALSE,2,2));
    Qslot_value_writer = STATIC_SYMBOL("SLOT-VALUE-WRITER",AB_package);
    mutate_global_property(Qitem_filter_qm,
	    SYMBOL_FUNCTION(Qwrite_item_filter_qm_from_slot),
	    Qslot_value_writer);
    string_constant_28 = STATIC_STRING("File operation ... ");
    string_constant_29 = STATIC_STRING("FAILED!  (~a)");
    string_constant_30 = STATIC_STRING("Searching ... [Seconds elapsed: ~d]");
    string_constant_31 = STATIC_STRING("Search took ~D second~A.  ");
    string_constant_32 = STATIC_STRING("~D item~A ~A found.");
    string_constant_33 = STATIC_STRING("was");
    string_constant_34 = STATIC_STRING("were");
    Qkb_state_search_status = STATIC_SYMBOL("KB-STATE-SEARCH-STATUS",
	    AB_package);
    Qwrite_kb_state_search_status_from_slot = 
	    STATIC_SYMBOL("WRITE-KB-STATE-SEARCH-STATUS-FROM-SLOT",AB_package);
    SET_SYMBOL_FUNCTION(Qwrite_kb_state_search_status_from_slot,
	    STATIC_FUNCTION(write_kb_state_search_status_from_slot,NIL,
	    FALSE,2,2));
    mutate_global_property(Qkb_state_search_status,
	    SYMBOL_FUNCTION(Qwrite_kb_state_search_status_from_slot),
	    Qslot_value_writer);
    Qfile_output_search_state = STATIC_SYMBOL("FILE-OUTPUT-SEARCH-STATE",
	    AB_package);
    list_constant_72 = STATIC_CONS(Qkb_search_state,Qnil);
    check_if_superior_classes_are_defined(Qfile_output_search_state,
	    list_constant_72);
    string_constant_247 = 
	    STATIC_STRING("1l4z8r835Ay835Ay83LSy83LSy00001p1m8p83-xy1l8l1l8o1l83Fy1l83Hy00000");
    string_constant_248 = 
	    STATIC_STRING("1n8q1m83LSy1l8323y1r835Ay01m8p83-xy8l8o83Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(string_constant_247);
    add_class_to_environment(9,Qfile_output_search_state,list_constant_72,
	    Nil,temp,Nil,temp_1,list_constant_72,
	    regenerate_optimized_constant(string_constant_248),Nil);
    Qfile_name_for_printing_search_results_qm = 
	    STATIC_SYMBOL("FILE-NAME-FOR-PRINTING-SEARCH-RESULTS\?",
	    AB_package);
    Qname_of_file_with_results = STATIC_SYMBOL("NAME-OF-FILE-WITH-RESULTS",
	    AB_package);
    alias_slot_name(3,Qfile_name_for_printing_search_results_qm,
	    Qname_of_file_with_results,Qfile_output_search_state);
    Qtables_search_state = STATIC_SYMBOL("TABLES-SEARCH-STATE",AB_package);
    check_if_superior_classes_are_defined(Qtables_search_state,
	    list_constant_72);
    string_constant_249 = 
	    STATIC_STRING("1m4z8r832My832My83bOy83bOy00001p1m8p83-xy1l8l1l8o1l83Fy1l83Hy000004z8r832By832By83bOy83bOy0k001p1m8p83Sy1l8l1l8o1l83Fy1l83Hy0000");
    string_constant_250 = 
	    STATIC_STRING("1o8q1m83bOy1l8323y1r832My01m8p83-xy8l8o83Fy83Hy1r832Byk1m8p83Sy8l8o83Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(LIST_2(string_constant_249,
	    string_constant_210));
    add_class_to_environment(9,Qtables_search_state,list_constant_72,Nil,
	    temp,Nil,temp_1,list_constant_72,
	    regenerate_optimized_constant(string_constant_250),Nil);
    Qstring_to_look_for_qm = STATIC_SYMBOL("STRING-TO-LOOK-FOR\?",AB_package);
    Qstring_to_look_for = STATIC_SYMBOL("STRING-TO-LOOK-FOR",AB_package);
    alias_slot_name(3,Qstring_to_look_for_qm,Qstring_to_look_for,
	    Qtables_search_state);
    Qnumber_of_items_found = STATIC_SYMBOL("NUMBER-OF-ITEMS-FOUND",AB_package);
    Qitems_with_occurrences = STATIC_SYMBOL("ITEMS-WITH-OCCURRENCES",
	    AB_package);
    alias_slot_name(3,Qnumber_of_items_found,Qitems_with_occurrences,
	    Qtables_search_state);
    Qnumber_of_occurrences_in_tables = 
	    STATIC_SYMBOL("NUMBER-OF-OCCURRENCES-IN-TABLES",AB_package);
    Qoccurrences = STATIC_SYMBOL("OCCURRENCES",AB_package);
    alias_slot_name(3,Qnumber_of_occurrences_in_tables,Qoccurrences,
	    Qtables_search_state);
    Qtables_substitution_state = STATIC_SYMBOL("TABLES-SUBSTITUTION-STATE",
	    AB_package);
    check_if_superior_classes_are_defined(Qtables_substitution_state,
	    list_constant_72);
    string_constant_251 = 
	    STATIC_STRING("1p4z8r832My832My83bPy83bPy00001p1m8p83-xy1l8l1l8o1l83Fy1l83Hy000004z8r836Ay836Ay83bPy83bPy00001p1m8p83-xy1l8l1l8o1l83Fy1l83Hy000");
    string_constant_252 = 
	    STATIC_STRING("004z8r835ty835ty83bPy83bPy0k001p1m8p83Sy1l8l1l8o1l83Fy1l83Hy000004z8r835sy835sy83bPy83bPy0k001p1m8p83Sy1l8l1l8o1l83Fy1l83Hy00000");
    string_constant_253 = 
	    STATIC_STRING("4z8r832By832By83bPy83bPy0k001p1m8p83Sy1l8l1l8o1l83Fy1l83Hy00000");
    string_constant_254 = 
	    STATIC_STRING("1r8q1m83bPy1l8323y1r832My01m8p83-xy8l8o83Fy83Hy1r836Ay01m8p83-xy8l8o83Fy83Hy1r835tyk1m8p83Sy8l8o83Fy83Hy1r835syk1m8p83Sy8l8o83Fy");
    string_constant_255 = STATIC_STRING("83Hy1r832Byk1m8p83Sy8l8o83Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_251,
	    string_constant_252,string_constant_253));
    add_class_to_environment(9,Qtables_substitution_state,list_constant_72,
	    Nil,temp,Nil,temp_1,list_constant_72,
	    regenerate_optimized_constant(LIST_2(string_constant_254,
	    string_constant_255)),Nil);
    Qstring_to_replace = STATIC_SYMBOL("STRING-TO-REPLACE",AB_package);
    alias_slot_name(3,Qstring_to_look_for_qm,Qstring_to_replace,
	    Qtables_substitution_state);
    Qreplacement_string_qm = STATIC_SYMBOL("REPLACEMENT-STRING\?",AB_package);
    Qreplacement_string = STATIC_SYMBOL("REPLACEMENT-STRING",AB_package);
    alias_slot_name(3,Qreplacement_string_qm,Qreplacement_string,Qnil);
    Qnumber_of_substitutions_in_tables = 
	    STATIC_SYMBOL("NUMBER-OF-SUBSTITUTIONS-IN-TABLES",AB_package);
    Qsubstitutions_made = STATIC_SYMBOL("SUBSTITUTIONS-MADE",AB_package);
    alias_slot_name(3,Qnumber_of_substitutions_in_tables,
	    Qsubstitutions_made,Qnil);
    Qnumber_of_resulting_parsing_failures = 
	    STATIC_SYMBOL("NUMBER-OF-RESULTING-PARSING-FAILURES",AB_package);
    Qresulting_parsing_failures = 
	    STATIC_SYMBOL("RESULTING-PARSING-FAILURES",AB_package);
    alias_slot_name(3,Qnumber_of_resulting_parsing_failures,
	    Qresulting_parsing_failures,Qnil);
    Qitems_containing_replacement_string = 
	    STATIC_SYMBOL("ITEMS-CONTAINING-REPLACEMENT-STRING",AB_package);
    alias_slot_name(3,Qnumber_of_items_found,
	    Qitems_containing_replacement_string,Qtables_substitution_state);
    Qoccurrences_of_replacement_string = 
	    STATIC_SYMBOL("OCCURRENCES-OF-REPLACEMENT-STRING",AB_package);
    alias_slot_name(3,Qnumber_of_occurrences_in_tables,
	    Qoccurrences_of_replacement_string,Qtables_substitution_state);
    Qspecial_purpose_kb_search_state = 
	    STATIC_SYMBOL("SPECIAL-PURPOSE-KB-SEARCH-STATE",AB_package);
    check_if_superior_classes_are_defined(Qspecial_purpose_kb_search_state,
	    list_constant_72);
    string_constant_256 = 
	    STATIC_STRING("1m4z8r83amy83amy83any83any00001n1l8l1l83Fy1l83Hy000004z8r83aly83aly83any83any00001n1l8l1l83Fy1l83Hy00000");
    string_constant_257 = 
	    STATIC_STRING("1o8q1m83any1l8323y1o83amy083Fy83Hy1o83aly083Fy83Hy");
    temp = regenerate_optimized_constant(string_constant_210);
    temp_1 = regenerate_optimized_constant(string_constant_256);
    add_class_to_environment(9,Qspecial_purpose_kb_search_state,
	    list_constant_72,Nil,temp,Nil,temp_1,list_constant_72,
	    regenerate_optimized_constant(string_constant_257),Nil);
    Qrecompile_from_inspect = STATIC_SYMBOL("RECOMPILE-FROM-INSPECT",
	    AB_package);
    Qnamed_dynamic_extent_description = 
	    STATIC_SYMBOL("NAMED-DYNAMIC-EXTENT-DESCRIPTION",AB_package);
    named_dynamic_extent_description = 
	    make_named_dynamic_extent_description(Qrecompile_from_inspect,
	    Qqueries,Nil,Qnil,Qnil,Qnil,Nil);
    mutate_global_property(Qrecompile_from_inspect,
	    named_dynamic_extent_description,
	    Qnamed_dynamic_extent_description);
    if (Suppress_consistency_analysis_warnings_notes_qm == UNBOUND)
	Suppress_consistency_analysis_warnings_notes_qm = Nil;
    if (Do_not_update_frame_authors_qm == UNBOUND)
	Do_not_update_frame_authors_qm = Nil;
    string_constant_35 = 
	    STATIC_STRING("Inspect was suspended while recompiling, but there was an item ~\n             with notes.");
    string_constant_36 = 
	    STATIC_STRING("Inspect was suspended while recompiling, but there were ~d ~\n             items with notes.");
    Qspecial_purpose_kb_search_function_qm = 
	    STATIC_SYMBOL("SPECIAL-PURPOSE-KB-SEARCH-FUNCTION\?",AB_package);
    Qspecial_purpose_kb_search_arglist_qm = 
	    STATIC_SYMBOL("SPECIAL-PURPOSE-KB-SEARCH-ARGLIST\?",AB_package);
    Qcomputation_style_description = 
	    STATIC_SYMBOL("COMPUTATION-STYLE-DESCRIPTION",AB_package);
    Qmay_provide_data_on_request = 
	    STATIC_SYMBOL("MAY-PROVIDE-DATA-ON-REQUEST",AB_package);
    Qmay_request_event_updates = STATIC_SYMBOL("MAY-REQUEST-EVENT-UPDATES",
	    AB_package);
    Qupdate_after_edits = STATIC_SYMBOL("UPDATE-AFTER-EDITS",AB_package);
    Qupdate_only_when_shown = STATIC_SYMBOL("UPDATE-ONLY-WHEN-SHOWN",
	    AB_package);
    list_constant_12 = STATIC_LIST((SI_Long)9L,
	    Qcomputation_style_description,Qmay_provide_data_on_request,
	    Qnil,Qmay_request_event_updates,Qnil,Qupdate_after_edits,Qnil,
	    Qupdate_only_when_shown,Qnil);
    Qtruth_value = STATIC_SYMBOL("TRUTH-VALUE",AB_package);
    Qunknown_datum = STATIC_SYMBOL("UNKNOWN-DATUM",AB_package);
    list_constant_73 = STATIC_CONS(Qunknown_datum,Qnil);
    list_constant_13 = STATIC_LIST((SI_Long)3L,Qab_or,Qtruth_value,
	    list_constant_73);
    Qsearch_state_table_format = STATIC_SYMBOL("SEARCH-STATE-TABLE-FORMAT",
	    AB_package);
    Qobservance_of_word_boundary_qm = 
	    STATIC_SYMBOL("OBSERVANCE-OF-WORD-BOUNDARY\?",AB_package);
    list_constant_14 = STATIC_LIST((SI_Long)12L,
	    Qitem_filter_for_kb_search_qm,Qstring_to_look_for_qm,
	    Qreplacement_string_qm,Qobservance_of_word_boundary_qm,
	    Qtotal_number_of_items_to_examine,
	    Qnumber_of_items_examined_so_far,
	    Qnumber_of_substitutions_in_tables,
	    Qnumber_of_resulting_parsing_failures,Qnumber_of_items_found,
	    Qnumber_of_occurrences_in_tables,
	    Qfile_name_for_printing_search_results_qm,Qkb_search_status_qm);
    Qhide = STATIC_SYMBOL("HIDE",AB_package);
    Qsuspend = STATIC_SYMBOL("SUSPEND",AB_package);
    Qab_continue = STATIC_SYMBOL("CONTINUE",AB_package);
    Qrerun = STATIC_SYMBOL("RERUN",AB_package);
    Qedit = STATIC_SYMBOL("EDIT",AB_package);
    Qfinish_inspect_subcommand = STATIC_SYMBOL("FINISH-INSPECT-SUBCOMMAND",
	    AB_package);
    Qreclaim_finish_inspect_subcommand_arglist = 
	    STATIC_SYMBOL("RECLAIM-FINISH-INSPECT-SUBCOMMAND-ARGLIST",
	    AB_package);
    string_constant_37 = STATIC_STRING("unable to open file");
    Qtable_rows = STATIC_SYMBOL("TABLE-ROWS",AB_package);
    SET_SYMBOL_FUNCTION(Qfinish_inspect_subcommand,
	    STATIC_FUNCTION(finish_inspect_subcommand,NIL,FALSE,6,6));
    SET_SYMBOL_FUNCTION(Qreclaim_finish_inspect_subcommand_arglist,
	    STATIC_FUNCTION(reclaim_finish_inspect_subcommand_arglist,NIL,
	    FALSE,1,1));
    Kdraw_as_late_as_possible = STATIC_SYMBOL("DRAW-AS-LATE-AS-POSSIBLE",
	    Pkeyword);
    Qshow_on_a_workspace_the_workspace_hierarchy = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-WORKSPACE-HIERARCHY",
	    AB_package);
    Qshow_on_a_workspace_the_class_hierarchy = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-CLASS-HIERARCHY",
	    AB_package);
    Qshow_on_a_workspace_the_inspect_command_history = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-INSPECT-COMMAND-HISTORY",
	    AB_package);
    Qshow_on_a_workspace_the_module_hierarchy = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-MODULE-HIERARCHY",
	    AB_package);
    Qshow_on_a_workspace_the_method_hierarchy = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-METHOD-HIERARCHY",
	    AB_package);
    Qshow_on_a_workspace_the_method_inheritance_path = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-METHOD-INHERITANCE-PATH",
	    AB_package);
    Qshow_on_a_workspace_the_procedure_reference_hierarchy = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-PROCEDURE-REFERENCE-HIERARCHY",
	    AB_package);
    Qshow_on_a_workspace_the_procedure_invocation_hierarchy = 
	    STATIC_SYMBOL("SHOW-ON-A-WORKSPACE-THE-PROCEDURE-INVOCATION-HIERARCHY",
	    AB_package);
    list_constant_15 = STATIC_LIST((SI_Long)8L,
	    Qshow_on_a_workspace_the_workspace_hierarchy,
	    Qshow_on_a_workspace_the_class_hierarchy,
	    Qshow_on_a_workspace_the_inspect_command_history,
	    Qshow_on_a_workspace_the_module_hierarchy,
	    Qshow_on_a_workspace_the_method_hierarchy,
	    Qshow_on_a_workspace_the_method_inheritance_path,
	    Qshow_on_a_workspace_the_procedure_reference_hierarchy,
	    Qshow_on_a_workspace_the_procedure_invocation_hierarchy);
    Qworkspace_name_box = STATIC_SYMBOL("WORKSPACE-NAME-BOX",AB_package);
    list_constant_16 = STATIC_LIST((SI_Long)2L,Qinspect_command,
	    Qworkspace_name_box);
    Kfirst = STATIC_SYMBOL("FIRST",Pkeyword);
    Qtitle_bar_caption_text = STATIC_SYMBOL("TITLE-BAR-CAPTION-TEXT",
	    AB_package);
    Qworkspace_background_color_qm = 
	    STATIC_SYMBOL("WORKSPACE-BACKGROUND-COLOR\?",AB_package);
    Qsystem_workspace_background_color = 
	    STATIC_SYMBOL("SYSTEM-WORKSPACE-BACKGROUND-COLOR",AB_package);
    Qleft = STATIC_SYMBOL("LEFT",AB_package);
    Qtop = STATIC_SYMBOL("TOP",AB_package);
    Qtext = STATIC_SYMBOL("TEXT",AB_package);
    Qediting = STATIC_SYMBOL("EDITING",AB_package);
    Qremote_query_id_for_kb_recompile = 
	    STATIC_SYMBOL("REMOTE-QUERY-ID-FOR-KB-RECOMPILE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qremote_query_id_for_kb_recompile,
	    Remote_query_id_for_kb_recompile);
    record_system_variable(Qremote_query_id_for_kb_recompile,Qqueries,Nil,
	    Qnil,Qnil,Qnil,Qt);
    string_constant_38 = 
	    STATIC_STRING("{Comment: G2 has launched this Inspect command to compile ~\n                 this KB up-to-date.~a~a}");
    string_constant_39 = STATIC_STRING("  ");
    string_constant_40 = STATIC_STRING("~a~%~%~a");
    string_constant_41 = 
	    STATIC_STRING("recompile every item whose status is incomplete");
    Qrecomile_message = STATIC_SYMBOL("RECOMILE-MESSAGE",AB_package);
    Qbutton = STATIC_SYMBOL("BUTTON",AB_package);
    array_constant_8 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)0L,(SI_Long)80L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)2L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)3L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_8,(SI_Long)7L,(SI_Long)57344L);
    Qpause = STATIC_SYMBOL("PAUSE",AB_package);
    array_constant_9 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)2L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)4L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_9,(SI_Long)7L,(SI_Long)57344L);
    array_constant_10 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)0L,(SI_Long)72L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)2L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_10,(SI_Long)7L,(SI_Long)57344L);
    Qhandle_remote_recompile_dialog_request = 
	    STATIC_SYMBOL("HANDLE-REMOTE-RECOMPILE-DIALOG-REQUEST",AB_package);
    Qnotify_t2_for_local_recompile = 
	    STATIC_SYMBOL("NOTIFY-T2-FOR-LOCAL-RECOMPILE",AB_package);
    Qlaunch_compile_to_bring_kb_up_to_date = 
	    STATIC_SYMBOL("LAUNCH-COMPILE-TO-BRING-KB-UP-TO-DATE",AB_package);
    SET_SYMBOL_FUNCTION(Qlaunch_compile_to_bring_kb_up_to_date,
	    STATIC_FUNCTION(launch_compile_to_bring_kb_up_to_date,NIL,TRUE,
	    0,1));
    Qadministrator = STATIC_SYMBOL("ADMINISTRATOR",AB_package);
    array_constant_11 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)0L,(SI_Long)82L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)4L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)5L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)14L,(SI_Long)6L);
    UBYTE_16_ISASET_1(array_constant_11,(SI_Long)15L,(SI_Long)57344L);
    Qresume = STATIC_SYMBOL("RESUME",AB_package);
    Qbutton_update = STATIC_SYMBOL("BUTTON-UPDATE",AB_package);
    SET_SYMBOL_FUNCTION(Qhandle_remote_recompile_dialog_request,
	    STATIC_FUNCTION(handle_remote_recompile_dialog_request,NIL,
	    FALSE,2,2));
    Qborderless_free_text_format = 
	    STATIC_SYMBOL("BORDERLESS-FREE-TEXT-FORMAT",AB_package);
    Qfont_for_descriptions = STATIC_SYMBOL("FONT-FOR-DESCRIPTIONS",AB_package);
    string_constant_42 = STATIC_STRING("Description of ~(~NF~)");
    string_constant_43 = STATIC_STRING("Description of ~(~NF.~)");
    Qdescribe_frame = STATIC_SYMBOL("DESCRIBE-FRAME",AB_package);
    list_constant_74 = STATIC_CONS(Qblock,Qnil);
    Qgeneric_method_lambda_list = 
	    STATIC_SYMBOL("GENERIC-METHOD-LAMBDA-LIST",AB_package);
    mutate_global_property(Qdescribe_frame,list_constant_74,
	    Qgeneric_method_lambda_list);
    string_constant_44 = 
	    STATIC_STRING("This is assigned to module ~a, which is not editable because ~a.");
    string_constant_45 = STATIC_STRING("This is assigned to module ~a.");
    string_constant_46 = STATIC_STRING("This is not assigned to any module.");
    string_constant_47 = 
	    STATIC_STRING("The following items are ~(~a this ~a~).");
    string_constant_48 = 
	    STATIC_STRING("This ~(~a is ~a~) the following items.");
    string_constant_49 = 
	    STATIC_STRING("This ~(~a~) is a member of the following g2-lists: ");
    string_constant_50 = 
	    STATIC_STRING("This ~(~a~) is a member of the following g2-list: ");
    string_constant_51 = STATIC_STRING("This item is proprietary to ~(~a~).");
    string_constant_52 = 
	    STATIC_STRING("The following procedures were on the stack when this was created:");
    Qdescribe_frame_for_block = STATIC_SYMBOL("DESCRIBE-FRAME-FOR-BLOCK",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_block,
	    STATIC_FUNCTION(describe_frame_for_block,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_block);
    set_get(Qblock,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qblock,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    array_constant_12 = STATIC_ARRAY(Qt,(SI_Long)1L,FIX((SI_Long)4L));
    Qbottom = STATIC_SYMBOL("BOTTOM",AB_package);
    Qright = STATIC_SYMBOL("RIGHT",AB_package);
    ISASET_1(array_constant_12,(SI_Long)0L,Qtop);
    ISASET_1(array_constant_12,(SI_Long)1L,Qleft);
    ISASET_1(array_constant_12,(SI_Long)2L,Qbottom);
    ISASET_1(array_constant_12,(SI_Long)3L,Qright);
    Qoutput = STATIC_SYMBOL("OUTPUT",AB_package);
    Qinput = STATIC_SYMBOL("INPUT",AB_package);
    string_constant_53 = STATIC_STRING("Bottom");
    string_constant_54 = STATIC_STRING("Top");
    string_constant_55 = STATIC_STRING("Right");
    string_constant_56 = STATIC_STRING("Left");
    string_constant_57 = STATIC_STRING("Input");
    string_constant_58 = STATIC_STRING("Output");
    Qconnection = STATIC_SYMBOL("CONNECTION",AB_package);
    Qdescribe_frame_for_connection = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-CONNECTION",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_connection,
	    STATIC_FUNCTION(describe_frame_for_connection,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_connection);
    set_get(Qconnection,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qconnection,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    string_constant_59 = STATIC_STRING("~A end connected to ~nf ");
    string_constant_60 = STATIC_STRING("at ~(~a~) ~d ");
    string_constant_61 = STATIC_STRING("at port ~a ");
    string_constant_62 = STATIC_STRING("~%");
    Qg2_array = STATIC_SYMBOL("G2-ARRAY",AB_package);
    Qdescribe_frame_for_g2_array = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-G2-ARRAY",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_g2_array,
	    STATIC_FUNCTION(describe_frame_for_g2_array,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_g2_array);
    set_get(Qg2_array,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_array,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    Qg2_list = STATIC_SYMBOL("G2-LIST",AB_package);
    Qdescribe_frame_for_g2_list = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-G2-LIST",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_g2_list,
	    STATIC_FUNCTION(describe_frame_for_g2_list,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_g2_list);
    set_get(Qg2_list,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qg2_list,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    Qquantity = STATIC_SYMBOL("QUANTITY",AB_package);
    Qlist_is_permanent = STATIC_SYMBOL("LIST-IS-PERMANENT",AB_package);
    Qitem_or_datum = STATIC_SYMBOL("ITEM-OR-DATUM",AB_package);
    string_constant_63 = 
	    STATIC_STRING("The following are the elements of this ~(~a~):");
    string_constant_64 = STATIC_STRING("no item");
    string_constant_65 = STATIC_STRING("no item or value");
    array_constant_13 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)3L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)4L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)5L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)6L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)7L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)14L,(SI_Long)8L);
    UBYTE_16_ISASET_1(array_constant_13,(SI_Long)15L,(SI_Long)57344L);
    string_constant_66 = STATIC_STRING("~NC");
    Qiteration_state = STATIC_SYMBOL("ITERATION-STATE",AB_package);
    string_constant_67 = STATIC_STRING("~NV");
    Qg2_defstruct_structure_name_temporary_constant_g2_struct = 
	    STATIC_SYMBOL("TEMPORARY-CONSTANT-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_68 = STATIC_STRING("~NF");
    array_constant_14 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)0L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)2L,(SI_Long)107L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)3L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)5L,(SI_Long)119L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)6L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)8L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_14,(SI_Long)15L,(SI_Long)57344L);
    if (Maximum_number_of_array_or_list_elements_to_describe == UNBOUND)
	Maximum_number_of_array_or_list_elements_to_describe = 
		FIX((SI_Long)1000L);
    string_constant_69 = STATIC_STRING("The following ~a of this ~(~a~):~%");
    string_constant_70 = STATIC_STRING("values are members");
    string_constant_71 = STATIC_STRING("value is a member");
    array_constant_15 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)0L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)1L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)6L,(SI_Long)2L);
    UBYTE_16_ISASET_1(array_constant_15,(SI_Long)7L,(SI_Long)57344L);
    string_constant_72 = STATIC_STRING("[~d] ");
    array_constant_16 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)0L,(SI_Long)46L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)6L,(SI_Long)1L);
    UBYTE_16_ISASET_1(array_constant_16,(SI_Long)7L,(SI_Long)57344L);
    string_constant_73 = 
	    STATIC_STRING("~%This operation describes at most ~a elements.  ~\n                      There ~a ~a remaining element~a.");
    string_constant_74 = STATIC_STRING("is");
    string_constant_75 = STATIC_STRING("are");
    Qsimulation_info_qm = STATIC_SYMBOL("SIMULATION-INFO\?",AB_package);
    Qparameter = STATIC_SYMBOL("PARAMETER",AB_package);
    string_constant_76 = 
	    STATIC_STRING("This ~(~a~) is simulated using the simulation formula ~\n                            in its simulation subtable.");
    string_constant_77 = 
	    STATIC_STRING("This ~(~a~) is simulated using the following ~a.");
    string_constant_78 = STATIC_STRING("generic simulation formula");
    string_constant_79 = STATIC_STRING("external simulation definition");
    string_constant_80 = STATIC_STRING("The simulation category is ~(~a~).");
    Qnon_default_initial_simulated_value_qm = 
	    STATIC_SYMBOL("NON-DEFAULT-INITIAL-SIMULATED-VALUE\?",AB_package);
    string_constant_81 = STATIC_STRING("  The initial value is ~(~a~).");
    string_constant_82 = 
	    STATIC_STRING("  The non-default time increment is ~(~a~) ~(~a~).");
    Qseconds = STATIC_SYMBOL("SECONDS",AB_package);
    string_constant_83 = 
	    STATIC_STRING("This ~(~a~) belongs to the following model definition.");
    Qvariable_or_parameter = STATIC_SYMBOL("VARIABLE-OR-PARAMETER",AB_package);
    Qdescribe_frame_for_variable_or_parameter = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-VARIABLE-OR-PARAMETER",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_variable_or_parameter,
	    STATIC_FUNCTION(describe_frame_for_variable_or_parameter,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_variable_or_parameter);
    set_get(Qvariable_or_parameter,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable_or_parameter,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    Qg2_defstruct_structure_name_data_server_g2_struct = 
	    STATIC_SYMBOL("DATA-SERVER-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    string_constant_84 = 
	    STATIC_STRING("Please note that this variable has been disabled!  ");
    string_constant_85 = 
	    string_append2(STATIC_STRING("Please note that this variable is disabled because ~\n                        it has a disabled parent or ~\n                        is on a subworkspace of an object with the ~"),
	    STATIC_STRING("\n                        deactivatable subworkspaces capability.  "));
    string_constant_86 = 
	    STATIC_STRING("The data server for this variable is the ");
    string_constant_87 = STATIC_STRING(".");
    string_constant_88 = 
	    STATIC_STRING("This variable references an UNDEFINED data map or alias!");
    string_constant_89 = STATIC_STRING("  This variable does not seek data.");
    Qcomputation = STATIC_SYMBOL("COMPUTATION",AB_package);
    string_constant_90 = 
	    STATIC_STRING("  This variable will seek data from its data server.");
    string_constant_91 = 
	    STATIC_STRING("  This variable does not backward chain.");
    string_constant_92 = 
	    STATIC_STRING("  This variable depth first backward chains to rules.");
    string_constant_93 = 
	    STATIC_STRING("  This variable breadth first backward chains to rules.");
    string_constant_94 = 
	    STATIC_STRING("  This variable may cause forward chaining when it ~\n                     receives a new value.");
    string_constant_95 = 
	    STATIC_STRING("  This variable may not cause forward chaining when it ~\n                     receives a new value.");
    Qgsi_interface_name = STATIC_SYMBOL("GSI-INTERFACE-NAME",AB_package);
    Qobject = STATIC_SYMBOL("OBJECT",AB_package);
    Qidentifying_attributes = STATIC_SYMBOL("IDENTIFYING-ATTRIBUTES",
	    AB_package);
    string_constant_96 = STATIC_STRING("This variable has ");
    string_constant_97 = STATIC_STRING("GSI data service ");
    string_constant_98 = STATIC_STRING("and ");
    string_constant_99 = STATIC_STRING("GSI message service ");
    string_constant_100 = STATIC_STRING("capabilities.  ");
    string_constant_101 = STATIC_STRING("capability.  ");
    string_constant_102 = 
	    STATIC_STRING("The interface name of this variable is ~a.  ");
    string_constant_103 = 
	    STATIC_STRING("Please note that no GSI interface name ~\n                                           has been specified for this variable.  ");
    string_constant_104 = 
	    STATIC_STRING("Please note that no object named ~a exists.");
    string_constant_105 = 
	    STATIC_STRING("Please note that the object ~a does not have ~\n                                    GSI interface configuration capability.  ");
    string_constant_106 = 
	    STATIC_STRING("Please note that the interface object named ~a ~\n                                    contains no attributes which identify a sensor.  ");
    string_constant_107 = 
	    STATIC_STRING("Please note that the GSI interface object ~a ~\n                                    expects this variable to have ");
    string_constant_108 = 
	    STATIC_STRING("at least one of the following attributes: ");
    string_constant_109 = STATIC_STRING("~a, ");
    string_constant_110 = STATIC_STRING("~a.  ");
    string_constant_111 = STATIC_STRING("~a, or ");
    string_constant_112 = STATIC_STRING("the attribute ~a.  ");
    string_constant_113 = 
	    STATIC_STRING("at least one of the attributes ~a or ~a.  ");
    string_constant_114 = STATIC_STRING("However, this variable lacks ");
    string_constant_115 = STATIC_STRING("any of the expected attributes.  ");
    string_constant_116 = STATIC_STRING("the expected attribute.  ");
    string_constant_117 = 
	    STATIC_STRING("either of the expected attributes.  ");
    string_constant_118 = 
	    STATIC_STRING("This variable receives its value from this specific formula.");
    string_constant_119 = 
	    STATIC_STRING("The variable receives its value from this generic ~\n                             formula, and the following formulas are shadowed ~\n                             by it.");
    string_constant_120 = 
	    STATIC_STRING("The variable receives its value from this generic ~\n                             formula.");
    string_constant_121 = 
	    STATIC_STRING("The following generic formula~a shadowed by the ~\n                         specific formula.");
    string_constant_122 = STATIC_STRING("s are");
    string_constant_123 = STATIC_STRING(" is");
    string_constant_124 = 
	    STATIC_STRING("The following backward chaining rule~a shadowed by ~\n                         the formula.");
    string_constant_125 = 
	    STATIC_STRING("The following rule~a ~abackward chained to to ~\n                         supply a value for the variable.");
    string_constant_126 = STATIC_STRING("depth first ");
    string_constant_127 = STATIC_STRING("breadth first ");
    Qdescribe_frame_for_variable = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-VARIABLE",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_variable,
	    STATIC_FUNCTION(describe_frame_for_variable,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_variable);
    set_get(Qvariable,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qvariable,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    string_constant_128 = 
	    STATIC_STRING("Please note that this parameter has been disabled!  ");
    string_constant_129 = 
	    string_append2(STATIC_STRING("Please note that this parameter is disabled because ~\n                            it has a disabled parent or ~\n                            is on a subworkspace of an object w"),
	    STATIC_STRING("ith the ~\n                            deactivatable subworkspaces capability.  "));
    string_constant_130 = 
	    STATIC_STRING("This parameter may cause forward chaining when it ~\n                     receives a new value.");
    string_constant_131 = 
	    STATIC_STRING("This parameter may not cause forward chaining when it ~\n                     receives a new value.");
    Qdescribe_frame_for_parameter = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-PARAMETER",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_parameter,
	    STATIC_FUNCTION(describe_frame_for_parameter,NIL,FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_parameter);
    set_get(Qparameter,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qparameter,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    Qimage_definition = STATIC_SYMBOL("IMAGE-DEFINITION",AB_package);
    Qimage_definition_cached_data_qm = 
	    STATIC_SYMBOL("IMAGE-DEFINITION-CACHED-DATA\?",AB_package);
    string_constant_132 = STATIC_STRING("This is a ~dx~dx~d ~a image");
    Qdescribe_frame_for_image_definition = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-IMAGE-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_image_definition,
	    STATIC_FUNCTION(describe_frame_for_image_definition,NIL,FALSE,
	    1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_image_definition);
    set_get(Qimage_definition,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qimage_definition,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    string_constant_133 = 
	    STATIC_STRING("The following are methods defined for ~\n                  this method-declaration:");
    string_constant_134 = 
	    STATIC_STRING("There are no methods defined for this ~\n                  method-declaration.");
    Qdescribe_frame_for_method_declaration = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-METHOD-DECLARATION",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_method_declaration,
	    STATIC_FUNCTION(describe_frame_for_method_declaration,NIL,
	    FALSE,1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_method_declaration);
    set_get(Qmethod_declaration,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qmethod_declaration,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    string_constant_135 = 
	    STATIC_STRING("The following methods are defined specifically for this class.");
    string_constant_136 = 
	    STATIC_STRING("There are no methods defined specifically for this class.");
    Qdescribe_frame_for_class_definition = 
	    STATIC_SYMBOL("DESCRIBE-FRAME-FOR-CLASS-DEFINITION",AB_package);
    SET_SYMBOL_FUNCTION(Qdescribe_frame_for_class_definition,
	    STATIC_FUNCTION(describe_frame_for_class_definition,NIL,FALSE,
	    1,1));
    temp_2 = SYMBOL_FUNCTION(Qdescribe_frame_for_class_definition);
    set_get(Qclass_definition,Qdescribe_frame,temp_2);
    temp = getfq_function_no_default(INLINE_SYMBOL_PLIST(Qdescribe_frame),
	    Qclasses_which_define);
    temp_2 = CONS(Qclass_definition,temp);
    mutate_global_property(Qdescribe_frame,temp_2,Qclasses_which_define);
    Qg2_expression_cell = STATIC_SYMBOL("G2-EXPRESSION-CELL",AB_package);
    array_constant_17 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)12L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)13L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)14L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)15L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)22L,(SI_Long)16L);
    UBYTE_16_ISASET_1(array_constant_17,(SI_Long)23L,(SI_Long)57344L);
    array_constant_18 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)32L));
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)19L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)20L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)21L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)22L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)23L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)25L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)26L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)30L,(SI_Long)27L);
    UBYTE_16_ISASET_1(array_constant_18,(SI_Long)31L,(SI_Long)57344L);
    array_constant_19 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)23L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)24L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)25L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)26L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)27L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)28L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)29L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)30L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)31L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)32L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)33L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)34L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)35L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)36L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)37L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)39L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)40L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)41L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)42L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)46L,(SI_Long)43L);
    UBYTE_16_ISASET_1(array_constant_19,(SI_Long)47L,(SI_Long)57344L);
    array_constant_20 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)48L));
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)11L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)12L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)13L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)14L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)15L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)16L,(SI_Long)104L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)17L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)18L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)19L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)20L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)21L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)22L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)23L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)24L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)25L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)26L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)27L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)28L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)29L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)30L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)31L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)32L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)33L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)34L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)35L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)36L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)37L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)38L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)39L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)40L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)41L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)42L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)43L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)46L,(SI_Long)44L);
    UBYTE_16_ISASET_1(array_constant_20,(SI_Long)47L,(SI_Long)57344L);
    Qembedded_rule_qm = STATIC_SYMBOL("EMBEDDED-RULE\?",AB_package);
    array_constant_21 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)0L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)2L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)3L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)5L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)9L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)10L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)11L,(SI_Long)58L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_21,(SI_Long)15L,(SI_Long)57344L);
    Qg2_defstruct_structure_name_byte_code_body_g2_struct = 
	    STATIC_SYMBOL("BYTE-CODE-BODY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    array_constant_22 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)0L,(SI_Long)78L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)2L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)3L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)4L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)5L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)9L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)10L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)11L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)14L,(SI_Long)12L);
    UBYTE_16_ISASET_1(array_constant_22,(SI_Long)15L,(SI_Long)57344L);
    list_constant_17 = STATIC_LIST((SI_Long)3L,Qtrue,Qfalse,Qany);
    string_constant_137 = STATIC_STRING("true");
    string_constant_138 = STATIC_STRING("false");
    string_constant_139 = STATIC_STRING("any new value");
    string_constant_140 = 
	    STATIC_STRING("These rules are forward chained to when ~a is received.");
    string_constant_141 = 
	    STATIC_STRING("These rules are forward chained to when a value is ~\n                           received.");
    Qeither = STATIC_SYMBOL("EITHER",AB_package);
    Qreceives_a_value = STATIC_SYMBOL("RECEIVES-A-VALUE",AB_package);
    list_constant_18 = STATIC_LIST((SI_Long)2L,Qeither,Qreceives_a_value);
    string_constant_142 = 
	    STATIC_STRING("These rules are forward chained to when ~\n                                   the value ~a is received.");
    string_constant_143 = 
	    STATIC_STRING("These rules are forward chained to when any ~\n                                   value other than ~a is received.");
    string_constant_144 = 
	    STATIC_STRING("These rules are forward chained to when any ~\n                               new value is received.");
    Qrule = STATIC_SYMBOL("RULE",AB_package);
    string_constant_145 = 
	    STATIC_STRING("The following rules mention the variable, though they are not ~\n                         invoked via any chaining mechanisms.");
    Qfor = STATIC_SYMBOL("FOR",AB_package);
    Qis_not = STATIC_SYMBOL("IS-NOT",AB_package);
    string_constant_146 = 
	    string_append2(STATIC_STRING("More than one attribute of class ~a has ~a as a possible ~\n                  value.  The implied attributes feature cannot be used when ~\n                  this is the case.  "),
	    STATIC_STRING("Attributes found so far are ~a and ~a."));
    Qexpression = STATIC_SYMBOL("EXPRESSION",AB_package);
    Qdesignation = STATIC_SYMBOL("DESIGNATION",AB_package);
    Qscope = STATIC_SYMBOL("SCOPE",AB_package);
    Qother = STATIC_SYMBOL("OTHER",AB_package);
    Qin_order = STATIC_SYMBOL("IN-ORDER",AB_package);
    Qsimultaneously = STATIC_SYMBOL("SIMULTANEOUSLY",AB_package);
    Qconclude_not = STATIC_SYMBOL("CONCLUDE-NOT",AB_package);
    Qconclude_has_no_current_value = 
	    STATIC_SYMBOL("CONCLUDE-HAS-NO-CURRENT-VALUE",AB_package);
    Qfocus = STATIC_SYMBOL("FOCUS",AB_package);
    Qconclude = STATIC_SYMBOL("CONCLUDE",AB_package);
    Qinvoke = STATIC_SYMBOL("INVOKE",AB_package);
    Qhalt = STATIC_SYMBOL("HALT",AB_package);
    Qinform = STATIC_SYMBOL("INFORM",AB_package);
    Qshow = STATIC_SYMBOL("SHOW",AB_package);
    Qmove = STATIC_SYMBOL("MOVE",AB_package);
    Qset_position = STATIC_SYMBOL("SET-POSITION",AB_package);
    Qrotate = STATIC_SYMBOL("ROTATE",AB_package);
    Qset_heading = STATIC_SYMBOL("SET-HEADING",AB_package);
    Qchange_icon_color = STATIC_SYMBOL("CHANGE-ICON-COLOR",AB_package);
    string_constant_147 = 
	    STATIC_STRING("Invoked with focus on ~nf as the ~(~a~)");
    string_constant_148 = STATIC_STRING(" ~a:");
    string_constant_149 = STATIC_STRING(":");
    Qg2_defstruct_structure_name_rule_instance_g2_struct = 
	    STATIC_SYMBOL("RULE-INSTANCE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_cached_explanation_g2_struct = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcached_explanation = STATIC_SYMBOL("CACHED-EXPLANATION",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_g2_struct,
	    Qcached_explanation,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcached_explanation,
	    Qg2_defstruct_structure_name_cached_explanation_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cached_explanation == UNBOUND)
	The_type_description_of_cached_explanation = Nil;
    string_constant_258 = 
	    STATIC_STRING("43Dy8m831py1n831py8n8k1l8n0000001l1m83My0klk0k0");
    temp = The_type_description_of_cached_explanation;
    The_type_description_of_cached_explanation = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_258));
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_g2_struct,
	    The_type_description_of_cached_explanation,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcached_explanation,
	    The_type_description_of_cached_explanation,
	    Qtype_description_of_type);
    Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct 
	    = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcached_explanation_from_data_server_or_initial_value = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct,
	    Qcached_explanation_from_data_server_or_initial_value,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qcached_explanation_from_data_server_or_initial_value,
	    Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cached_explanation_from_data_server_or_initial_value 
	    == UNBOUND)
	The_type_description_of_cached_explanation_from_data_server_or_initial_value 
		= Nil;
    string_constant_259 = 
	    STATIC_STRING("43Dy8m83fcy1o83fcy831py8n8k1l831py0000001m1m8x831py1n8y83-3=y1l83w2ykmk0k0");
    temp = 
	    The_type_description_of_cached_explanation_from_data_server_or_initial_value;
    The_type_description_of_cached_explanation_from_data_server_or_initial_value 
	    = load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_259));
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_data_server_or_initial_value_g2_struct,
	    The_type_description_of_cached_explanation_from_data_server_or_initial_value,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcached_explanation_from_data_server_or_initial_value,
	    The_type_description_of_cached_explanation_from_data_server_or_initial_value,
	    Qtype_description_of_type);
    Qoutstanding_cached_explanation_from_data_server_or_initial_value_count 
	    = 
	    STATIC_SYMBOL("OUTSTANDING-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-COUNT",
	    AB_package);
    Qcached_explanation_from_data_server_or_initial_value_structure_memory_usage 
	    = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_260 = STATIC_STRING("1q83fcy8s83-LGy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_cached_explanation_from_data_server_or_initial_value_count);
    push_optimized_constant(Qcached_explanation_from_data_server_or_initial_value_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_260));
    Qchain_of_available_cached_explanation_from_data_server_or_initial_values 
	    = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_cached_explanation_from_data_server_or_initial_values,
	    Chain_of_available_cached_explanation_from_data_server_or_initial_values);
    record_system_variable(Qchain_of_available_cached_explanation_from_data_server_or_initial_values,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcached_explanation_from_data_server_or_initial_value_count = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-DATA-SERVER-OR-INITIAL-VALUE-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_explanation_from_data_server_or_initial_value_count,
	    Cached_explanation_from_data_server_or_initial_value_count);
    record_system_variable(Qcached_explanation_from_data_server_or_initial_value_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcached_explanation_from_data_server_or_initial_value_structure_memory_usage,
	    STATIC_FUNCTION(cached_explanation_from_data_server_or_initial_value_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_cached_explanation_from_data_server_or_initial_value_count,
	    STATIC_FUNCTION(outstanding_cached_explanation_from_data_server_or_initial_value_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_cached_explanation_from_data_server_or_initial_value_1 
	    = 
	    STATIC_FUNCTION(reclaim_structure_for_cached_explanation_from_data_server_or_initial_value,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcached_explanation_from_data_server_or_initial_value,
	    reclaim_structure_for_cached_explanation_from_data_server_or_initial_value_1);
    Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct 
	    = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcached_explanation_from_specific_formula = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct,
	    Qcached_explanation_from_specific_formula,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qcached_explanation_from_specific_formula,
	    Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cached_explanation_from_specific_formula 
	    == UNBOUND)
	The_type_description_of_cached_explanation_from_specific_formula = Nil;
    string_constant_261 = 
	    STATIC_STRING("43Dy8m83ffy1o83ffy831py8n8k1l831py0000001m1m8x831py1n8y83-33y1m83w1y83w-yknk0k0");
    temp = The_type_description_of_cached_explanation_from_specific_formula;
    The_type_description_of_cached_explanation_from_specific_formula = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_261));
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_specific_formula_g2_struct,
	    The_type_description_of_cached_explanation_from_specific_formula,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcached_explanation_from_specific_formula,
	    The_type_description_of_cached_explanation_from_specific_formula,
	    Qtype_description_of_type);
    Qoutstanding_cached_explanation_from_specific_formula_count = 
	    STATIC_SYMBOL("OUTSTANDING-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-COUNT",
	    AB_package);
    Qcached_explanation_from_specific_formula_structure_memory_usage = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_262 = STATIC_STRING("1q83ffy8s83-LKy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_cached_explanation_from_specific_formula_count);
    push_optimized_constant(Qcached_explanation_from_specific_formula_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_262));
    Qchain_of_available_cached_explanation_from_specific_formulas = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CACHED-EXPLANATION-FROM-SPECIFIC-FORMULAS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_cached_explanation_from_specific_formulas,
	    Chain_of_available_cached_explanation_from_specific_formulas);
    record_system_variable(Qchain_of_available_cached_explanation_from_specific_formulas,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcached_explanation_from_specific_formula_count = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-SPECIFIC-FORMULA-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_explanation_from_specific_formula_count,
	    Cached_explanation_from_specific_formula_count);
    record_system_variable(Qcached_explanation_from_specific_formula_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcached_explanation_from_specific_formula_structure_memory_usage,
	    STATIC_FUNCTION(cached_explanation_from_specific_formula_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_cached_explanation_from_specific_formula_count,
	    STATIC_FUNCTION(outstanding_cached_explanation_from_specific_formula_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_cached_explanation_from_specific_formula_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_cached_explanation_from_specific_formula,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcached_explanation_from_specific_formula,
	    reclaim_structure_for_cached_explanation_from_specific_formula_1);
    Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-FRAME-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcached_explanation_from_frame = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-FRAME",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct,
	    Qcached_explanation_from_frame,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcached_explanation_from_frame,
	    Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cached_explanation_from_frame == UNBOUND)
	The_type_description_of_cached_explanation_from_frame = Nil;
    string_constant_263 = 
	    STATIC_STRING("43Dy8m836cy1o836cy831py8n8k1l831py0000001m1m8x831py1n8y83-30y1l837rykmk0k0");
    temp = The_type_description_of_cached_explanation_from_frame;
    The_type_description_of_cached_explanation_from_frame = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_263));
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_frame_g2_struct,
	    The_type_description_of_cached_explanation_from_frame,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcached_explanation_from_frame,
	    The_type_description_of_cached_explanation_from_frame,
	    Qtype_description_of_type);
    Qoutstanding_cached_explanation_from_frame_count = 
	    STATIC_SYMBOL("OUTSTANDING-CACHED-EXPLANATION-FROM-FRAME-COUNT",
	    AB_package);
    Qcached_explanation_from_frame_structure_memory_usage = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-FRAME-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_264 = STATIC_STRING("1q836cy8s83-LHy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_cached_explanation_from_frame_count);
    push_optimized_constant(Qcached_explanation_from_frame_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_264));
    Qchain_of_available_cached_explanation_from_frames = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CACHED-EXPLANATION-FROM-FRAMES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_cached_explanation_from_frames,
	    Chain_of_available_cached_explanation_from_frames);
    record_system_variable(Qchain_of_available_cached_explanation_from_frames,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcached_explanation_from_frame_count = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-FRAME-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_explanation_from_frame_count,
	    Cached_explanation_from_frame_count);
    record_system_variable(Qcached_explanation_from_frame_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcached_explanation_from_frame_structure_memory_usage,
	    STATIC_FUNCTION(cached_explanation_from_frame_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_cached_explanation_from_frame_count,
	    STATIC_FUNCTION(outstanding_cached_explanation_from_frame_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_cached_explanation_from_frame_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_cached_explanation_from_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcached_explanation_from_frame,
	    reclaim_structure_for_cached_explanation_from_frame_1);
    Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct 
	    = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-GENERIC-FORMULA-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcached_explanation_from_generic_formula = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-GENERIC-FORMULA",
	    AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct,
	    Qcached_explanation_from_generic_formula,
	    Qab_name_of_unique_structure_type);
    mutate_global_property(Qcached_explanation_from_generic_formula,
	    Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cached_explanation_from_generic_formula == 
	    UNBOUND)
	The_type_description_of_cached_explanation_from_generic_formula = Nil;
    string_constant_265 = 
	    STATIC_STRING("43Dy8m83fdy1p83fdy836cy831py8n8k1l836cy0000001m1m8x836cy1n8y83-31y1m837ry83vxyknk0k0");
    temp = The_type_description_of_cached_explanation_from_generic_formula;
    The_type_description_of_cached_explanation_from_generic_formula = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_265));
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_generic_formula_g2_struct,
	    The_type_description_of_cached_explanation_from_generic_formula,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcached_explanation_from_generic_formula,
	    The_type_description_of_cached_explanation_from_generic_formula,
	    Qtype_description_of_type);
    Qoutstanding_cached_explanation_from_generic_formula_count = 
	    STATIC_SYMBOL("OUTSTANDING-CACHED-EXPLANATION-FROM-GENERIC-FORMULA-COUNT",
	    AB_package);
    Qcached_explanation_from_generic_formula_structure_memory_usage = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-GENERIC-FORMULA-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_266 = STATIC_STRING("1q83fdy8s83-LIy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_cached_explanation_from_generic_formula_count);
    push_optimized_constant(Qcached_explanation_from_generic_formula_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_266));
    Qchain_of_available_cached_explanation_from_generic_formulas = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CACHED-EXPLANATION-FROM-GENERIC-FORMULAS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_cached_explanation_from_generic_formulas,
	    Chain_of_available_cached_explanation_from_generic_formulas);
    record_system_variable(Qchain_of_available_cached_explanation_from_generic_formulas,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcached_explanation_from_generic_formula_count = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-GENERIC-FORMULA-COUNT",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_explanation_from_generic_formula_count,
	    Cached_explanation_from_generic_formula_count);
    record_system_variable(Qcached_explanation_from_generic_formula_count,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcached_explanation_from_generic_formula_structure_memory_usage,
	    STATIC_FUNCTION(cached_explanation_from_generic_formula_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_cached_explanation_from_generic_formula_count,
	    STATIC_FUNCTION(outstanding_cached_explanation_from_generic_formula_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_cached_explanation_from_generic_formula_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_cached_explanation_from_generic_formula,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcached_explanation_from_generic_formula,
	    reclaim_structure_for_cached_explanation_from_generic_formula_1);
    Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-RULE-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qcached_explanation_from_rule = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-RULE",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct,
	    Qcached_explanation_from_rule,Qab_name_of_unique_structure_type);
    mutate_global_property(Qcached_explanation_from_rule,
	    Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_cached_explanation_from_rule == UNBOUND)
	The_type_description_of_cached_explanation_from_rule = Nil;
    string_constant_267 = 
	    STATIC_STRING("43Dy8m83fey1p83fey836cy831py8n8k1l836cy0000001m1m8x836cy1n8y83-32y1o837ry83w+y83w=y83w0ykpk0k0");
    temp = The_type_description_of_cached_explanation_from_rule;
    The_type_description_of_cached_explanation_from_rule = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_267));
    mutate_global_property(Qg2_defstruct_structure_name_cached_explanation_from_rule_g2_struct,
	    The_type_description_of_cached_explanation_from_rule,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qcached_explanation_from_rule,
	    The_type_description_of_cached_explanation_from_rule,
	    Qtype_description_of_type);
    Qoutstanding_cached_explanation_from_rule_count = 
	    STATIC_SYMBOL("OUTSTANDING-CACHED-EXPLANATION-FROM-RULE-COUNT",
	    AB_package);
    Qcached_explanation_from_rule_structure_memory_usage = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-RULE-STRUCTURE-MEMORY-USAGE",
	    AB_package);
    string_constant_268 = STATIC_STRING("1q83fey8s83-LJy09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_cached_explanation_from_rule_count);
    push_optimized_constant(Qcached_explanation_from_rule_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_268));
    Qchain_of_available_cached_explanation_from_rules = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-CACHED-EXPLANATION-FROM-RULES",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_cached_explanation_from_rules,
	    Chain_of_available_cached_explanation_from_rules);
    record_system_variable(Qchain_of_available_cached_explanation_from_rules,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcached_explanation_from_rule_count = 
	    STATIC_SYMBOL("CACHED-EXPLANATION-FROM-RULE-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcached_explanation_from_rule_count,
	    Cached_explanation_from_rule_count);
    record_system_variable(Qcached_explanation_from_rule_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qcached_explanation_from_rule_structure_memory_usage,
	    STATIC_FUNCTION(cached_explanation_from_rule_structure_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_cached_explanation_from_rule_count,
	    STATIC_FUNCTION(outstanding_cached_explanation_from_rule_count,
	    NIL,FALSE,0,0));
    reclaim_structure_for_cached_explanation_from_rule_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_cached_explanation_from_rule,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,
	    Qcached_explanation_from_rule,
	    reclaim_structure_for_cached_explanation_from_rule_1);
    Qitem_reference = STATIC_SYMBOL("ITEM-REFERENCE",AB_package);
    Qget_cached_explanation_evaled_variables_if_any = 
	    STATIC_SYMBOL("GET-CACHED-EXPLANATION-EVALED-VARIABLES-IF-ANY",
	    AB_package);
    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_1 
	    = 
	    STATIC_FUNCTION(get_cached_explanation_evaled_variables_if_any_for_cached_explanation,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qget_cached_explanation_evaled_variables_if_any,
	    Qcached_explanation,
	    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_1);
    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_specific_formula_1 
	    = 
	    STATIC_FUNCTION(get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_specific_formula,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qget_cached_explanation_evaled_variables_if_any,
	    Qcached_explanation_from_specific_formula,
	    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_specific_formula_1);
    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_generic_formula_1 
	    = 
	    STATIC_FUNCTION(get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_generic_formula,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qget_cached_explanation_evaled_variables_if_any,
	    Qcached_explanation_from_generic_formula,
	    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_generic_formula_1);
    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_rule_1 
	    = 
	    STATIC_FUNCTION(get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_rule,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qget_cached_explanation_evaled_variables_if_any,
	    Qcached_explanation_from_rule,
	    get_cached_explanation_evaled_variables_if_any_for_cached_explanation_from_rule_1);
    Qmake_cached_explanation_node = 
	    STATIC_SYMBOL("MAKE-CACHED-EXPLANATION-NODE",AB_package);
    make_cached_explanation_node_for_cached_explanation_from_rule_1 = 
	    STATIC_FUNCTION(make_cached_explanation_node_for_cached_explanation_from_rule,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qmake_cached_explanation_node,
	    Qcached_explanation_from_rule,
	    make_cached_explanation_node_for_cached_explanation_from_rule_1);
    make_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value_1 
	    = 
	    STATIC_FUNCTION(make_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qmake_cached_explanation_node,
	    Qcached_explanation_from_data_server_or_initial_value,
	    make_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value_1);
    make_cached_explanation_node_for_cached_explanation_from_specific_formula_1 
	    = 
	    STATIC_FUNCTION(make_cached_explanation_node_for_cached_explanation_from_specific_formula,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qmake_cached_explanation_node,
	    Qcached_explanation_from_specific_formula,
	    make_cached_explanation_node_for_cached_explanation_from_specific_formula_1);
    make_cached_explanation_node_for_cached_explanation_from_frame_1 = 
	    STATIC_FUNCTION(make_cached_explanation_node_for_cached_explanation_from_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qmake_cached_explanation_node,
	    Qcached_explanation_from_frame,
	    make_cached_explanation_node_for_cached_explanation_from_frame_1);
    Qreturn_cached_explanation_if_valid = 
	    STATIC_SYMBOL("RETURN-CACHED-EXPLANATION-IF-VALID",AB_package);
    return_cached_explanation_if_valid_for_cached_explanation_1 = 
	    STATIC_FUNCTION(return_cached_explanation_if_valid_for_cached_explanation,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreturn_cached_explanation_if_valid,
	    Qcached_explanation,
	    return_cached_explanation_if_valid_for_cached_explanation_1);
    return_cached_explanation_if_valid_for_cached_explanation_from_frame_1 
	    = 
	    STATIC_FUNCTION(return_cached_explanation_if_valid_for_cached_explanation_from_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qreturn_cached_explanation_if_valid,
	    Qcached_explanation_from_frame,
	    return_cached_explanation_if_valid_for_cached_explanation_from_frame_1);
    Qexport_cached_explanation_node = 
	    STATIC_SYMBOL("EXPORT-CACHED-EXPLANATION-NODE",AB_package);
    Qnode_type = STATIC_SYMBOL("NODE-TYPE",AB_package);
    Qdata_server_or_initial_value = 
	    STATIC_SYMBOL("DATA-SERVER-OR-INITIAL-VALUE",AB_package);
    Qitem_or_value = STATIC_SYMBOL("ITEM-OR-VALUE",AB_package);
    Qnode_specific_data = STATIC_SYMBOL("NODE-SPECIFIC-DATA",AB_package);
    Qab_structure = STATIC_SYMBOL("STRUCTURE",AB_package);
    export_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value_1 
	    = 
	    STATIC_FUNCTION(export_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_cached_explanation_node,
	    Qcached_explanation_from_data_server_or_initial_value,
	    export_cached_explanation_node_for_cached_explanation_from_data_server_or_initial_value_1);
    Qspecific_formula = STATIC_SYMBOL("SPECIFIC-FORMULA",AB_package);
    export_cached_explanation_node_for_cached_explanation_from_specific_formula_1 
	    = 
	    STATIC_FUNCTION(export_cached_explanation_node_for_cached_explanation_from_specific_formula,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_cached_explanation_node,
	    Qcached_explanation_from_specific_formula,
	    export_cached_explanation_node_for_cached_explanation_from_specific_formula_1);
    export_cached_explanation_node_for_cached_explanation_from_frame_1 = 
	    STATIC_FUNCTION(export_cached_explanation_node_for_cached_explanation_from_frame,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_cached_explanation_node,
	    Qcached_explanation_from_frame,
	    export_cached_explanation_node_for_cached_explanation_from_frame_1);
    Qlocal_name = STATIC_SYMBOL("LOCAL-NAME",AB_package);
    export_cached_explanation_node_for_cached_explanation_from_rule_1 = 
	    STATIC_FUNCTION(export_cached_explanation_node_for_cached_explanation_from_rule,
	    NIL,FALSE,1,1);
    record_direct_structure_method(Qexport_cached_explanation_node,
	    Qcached_explanation_from_rule,
	    export_cached_explanation_node_for_cached_explanation_from_rule_1);
    Qg2_internal_cached_explanation = 
	    STATIC_SYMBOL("G2-INTERNAL-CACHED-EXPLANATION",AB_package);
    Qinitial_value = STATIC_SYMBOL("INITIAL-VALUE",AB_package);
    array_constant_23 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)0L,(SI_Long)73L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)1L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)2L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)3L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)4L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)6L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)8L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)9L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)10L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)11L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)12L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)14L,(SI_Long)13L);
    UBYTE_16_ISASET_1(array_constant_23,(SI_Long)15L,(SI_Long)57344L);
    array_constant_24 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)2L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)5L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)7L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)9L,(SI_Long)68L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)10L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)11L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)12L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)13L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)14L,(SI_Long)83L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)16L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)17L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)18L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)19L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)22L,(SI_Long)20L);
    UBYTE_16_ISASET_1(array_constant_24,(SI_Long)23L,(SI_Long)57344L);
    Qg2_defstruct_structure_name_formula_invocation_g2_struct = 
	    STATIC_SYMBOL("FORMULA-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qg2_defstruct_structure_name_procedure_invocation_g2_struct = 
	    STATIC_SYMBOL("PROCEDURE-INVOCATION-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qparent_frame = STATIC_SYMBOL("PARENT-FRAME",AB_package);
    Qexplanation = STATIC_SYMBOL("EXPLANATION",AB_package);
    list_constant_75 = STATIC_CONS(Qitem,list_constant_71);
    check_if_superior_classes_are_defined(Qexplanation,list_constant_75);
    Qcreate_icon_description = STATIC_SYMBOL("CREATE-ICON-DESCRIPTION",
	    AB_package);
    string_constant_269 = 
	    STATIC_STRING("1l4z8r8u8u838Hy838Hy01p8w9k3uy3uy13Gy1n83Oy1m3hy3Ey1m3hy3My1p83Jy1m3ey3My1m3ey3Ry1m3ky3Ry1m3ky3My1n83Oy1m3Zy3Zy1m3py3Zy1n83Oy1m3");
    string_constant_270 = 
	    STATIC_STRING("hy3Ry1m3hy3Zy1n83Oy1m3Zy3Zy1m3Zy3hy1n83Oy1m3py3Zy1m3py3hy1p83Jy1m3my3hy1m3my3my1m3sy3my1m3sy3hy1p83Jy1m3Wy3hy1m3Wy3my1m3cy3my1m3");
    string_constant_271 = 
	    STATIC_STRING("cy3hy1p83Jy1mt3My1mt3Ry1mz3Ry1mz3My1n83Oy1mw3Ey1mw3My1p83Jy1ml3hy1ml3my1mr3my1mr3hy1n83Oy1mo3Zy1m3Gy3Zy1n83Oy1mw3Ry1mw3Zy1n83Oy1");
    string_constant_272 = 
	    STATIC_STRING("mo3Zy1mo3hy1n83Oy1m3Gy3Zy1m3Gy3hy1p83Jy1m3Dy3hy1m3Dy3my1m3Jy3my1m3Jy3hy1n83Oy1m3Qyu1m3Qy3Ey1n83Oy1mw3Ey1m3hy3Ey1p83Jy1m3Nyp1m3Ny");
    string_constant_273 = 
	    STATIC_STRING("u1m3Tyu1m3Typ1p83Jy1mkk1mk3uy1m3uy3uy1m3uyk001o1l8l1l8o1l8z1m83Dy53YySee comment on ENTITY class definition00000");
    string_constant_274 = 
	    STATIC_STRING("1n8q1m838Hy1m83Ry83-+y1m8u1p8w9k3uy3uy13Gy1n83Oy1m3hy3Ey1m3hy3My1p83Jy1m3ey3My1m3ey3Ry1m3ky3Ry1m3ky3My1n83Oy1m3Zy3Zy1m3py3Zy1n83");
    string_constant_275 = 
	    STATIC_STRING("Oy1m3hy3Ry1m3hy3Zy1n83Oy1m3Zy3Zy1m3Zy3hy1n83Oy1m3py3Zy1m3py3hy1p83Jy1m3my3hy1m3my3my1m3sy3my1m3sy3hy1p83Jy1m3Wy3hy1m3Wy3my1m3cy3");
    string_constant_276 = 
	    STATIC_STRING("my1m3cy3hy1p83Jy1mt3My1mt3Ry1mz3Ry1mz3My1n83Oy1mw3Ey1mw3My1p83Jy1ml3hy1ml3my1mr3my1mr3hy1n83Oy1mo3Zy1m3Gy3Zy1n83Oy1mw3Ry1mw3Zy1n");
    string_constant_277 = 
	    STATIC_STRING("83Oy1mo3Zy1mo3hy1n83Oy1m3Gy3Zy1m3Gy3hy1p83Jy1m3Dy3hy1m3Dy3my1m3Jy3my1m3Jy3hy1n83Oy1m3Qyu1m3Qy3Ey1n83Oy1mw3Ey1m3hy3Ey1p83Jy1m3Nyp");
    string_constant_278 = 
	    STATIC_STRING("1m3Nyu1m3Tyu1m3Typ1p83Jy1mkk1mk3uy1m3uy3uy1m3uyk");
    temp = regenerate_optimized_constant(string_constant_210);
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    temp_1 = regenerate_optimized_constant(LIST_5(string_constant_269,
	    string_constant_270,string_constant_271,string_constant_272,
	    string_constant_273));
    clear_optimized_constants();
    push_optimized_constant(Qcreate_icon_description);
    add_class_to_environment(9,Qexplanation,list_constant_75,Nil,temp,Nil,
	    temp_1,list_constant_75,
	    regenerate_optimized_constant(LIST_5(string_constant_274,
	    string_constant_275,string_constant_276,string_constant_277,
	    string_constant_278)),Nil);
    Qhash_explanation_node = STATIC_SYMBOL("HASH-EXPLANATION-NODE",AB_package);
    Qget_explanation_children = STATIC_SYMBOL("GET-EXPLANATION-CHILDREN",
	    AB_package);
    Qmake_explanation_node_representation = 
	    STATIC_SYMBOL("MAKE-EXPLANATION-NODE-REPRESENTATION",AB_package);
    Qcreate_explanation = STATIC_SYMBOL("CREATE-EXPLANATION",AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_explanation,
	    STATIC_FUNCTION(create_explanation,NIL,FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qget_explanation_children,
	    STATIC_FUNCTION(get_explanation_children,NIL,FALSE,2,2));
    Qnever = STATIC_SYMBOL("NEVER",AB_package);
    array_constant_25 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)0L,(SI_Long)86L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)3L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)6L,(SI_Long)5L);
    UBYTE_16_ISASET_1(array_constant_25,(SI_Long)7L,(SI_Long)57344L);
    array_constant_26 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)0L,(SI_Long)84L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)1L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)2L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)4L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)6L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)7L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)8L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)14L,(SI_Long)9L);
    UBYTE_16_ISASET_1(array_constant_26,(SI_Long)15L,(SI_Long)57344L);
    array_constant_27 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)8L));
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)0L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)1L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)6L,(SI_Long)4L);
    UBYTE_16_ISASET_1(array_constant_27,(SI_Long)7L,(SI_Long)57344L);
    array_constant_28 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)16L));
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)0L,(SI_Long)69L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)1L,(SI_Long)120L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)2L,(SI_Long)112L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)5L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)6L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)7L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)8L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)9L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)14L,(SI_Long)10L);
    UBYTE_16_ISASET_1(array_constant_28,(SI_Long)15L,(SI_Long)57344L);
    Qtime_stamp = STATIC_SYMBOL("TIME-STAMP",AB_package);
    array_constant_29 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)0L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)1L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)2L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)3L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)4L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)5L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)6L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)7L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)8L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)9L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)10L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)11L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)12L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)13L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)14L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)15L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)16L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)17L,(SI_Long)121L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)22L,(SI_Long)18L);
    UBYTE_16_ISASET_1(array_constant_29,(SI_Long)23L,(SI_Long)57344L);
    Qvar_spot = STATIC_SYMBOL("VAR-SPOT",AB_package);
    Kgeneral_description = STATIC_SYMBOL("GENERAL-DESCRIPTION",Pkeyword);
    array_constant_30 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)24L));
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)0L,(SI_Long)60L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)1L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)2L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)3L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)4L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)5L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)6L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)7L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)8L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)10L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)11L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)12L,(SI_Long)109L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)13L,(SI_Long)62L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)22L,(SI_Long)14L);
    UBYTE_16_ISASET_1(array_constant_30,(SI_Long)23L,(SI_Long)57344L);
    SET_SYMBOL_FUNCTION(Qmake_explanation_node_representation,
	    STATIC_FUNCTION(make_explanation_node_representation,NIL,FALSE,
	    1,1));
    SET_SYMBOL_FUNCTION(Qhash_explanation_node,
	    STATIC_FUNCTION(hash_explanation_node,NIL,FALSE,1,1));
    Qg2_get_explanation_hierarchy = 
	    STATIC_SYMBOL("G2-GET-EXPLANATION-HIERARCHY",AB_package);
    gensymed_symbol = T;
    mutate_global_property(Qg2_get_explanation_hierarchy,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    Qcreate_exported_cached_explanation_node = 
	    STATIC_SYMBOL("CREATE-EXPORTED-CACHED-EXPLANATION-NODE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qcreate_exported_cached_explanation_node,
	    STATIC_FUNCTION(create_exported_cached_explanation_node,NIL,
	    FALSE,1,1));
    SET_SYMBOL_FUNCTION(Qg2_get_explanation_hierarchy,
	    STATIC_FUNCTION(g2_get_explanation_hierarchy,NIL,FALSE,1,1));
    Qframe_flags = STATIC_SYMBOL("FRAME-FLAGS",AB_package);
    Qg2_defstruct_structure_name_frame_display_g2_struct = 
	    STATIC_SYMBOL("FRAME-DISPLAY-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    Qframe_display = STATIC_SYMBOL("FRAME-DISPLAY",AB_package);
    mutate_global_property(Qg2_defstruct_structure_name_frame_display_g2_struct,
	    Qframe_display,Qab_name_of_unique_structure_type);
    mutate_global_property(Qframe_display,
	    Qg2_defstruct_structure_name_frame_display_g2_struct,
	    Qunique_structure_type_of_ab_name_qm);
    if (The_type_description_of_frame_display == UNBOUND)
	The_type_description_of_frame_display = Nil;
    string_constant_279 = 
	    STATIC_STRING("43Dy8m83hZy1o83hZy836my8n8k1l836my0000001l1m8x836myksk0k0");
    temp = The_type_description_of_frame_display;
    The_type_description_of_frame_display = 
	    load_and_initialize_type_description(temp,
	    regenerate_optimized_constant(string_constant_279));
    mutate_global_property(Qg2_defstruct_structure_name_frame_display_g2_struct,
	    The_type_description_of_frame_display,
	    Qtype_description_of_unique_type_name_of_gensym_structure);
    mutate_global_property(Qframe_display,
	    The_type_description_of_frame_display,Qtype_description_of_type);
    Qoutstanding_frame_display_count = 
	    STATIC_SYMBOL("OUTSTANDING-FRAME-DISPLAY-COUNT",AB_package);
    Qframe_display_structure_memory_usage = 
	    STATIC_SYMBOL("FRAME-DISPLAY-STRUCTURE-MEMORY-USAGE",AB_package);
    string_constant_280 = STATIC_STRING("1q83hZy8s83-Uey09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qoutstanding_frame_display_count);
    push_optimized_constant(Qframe_display_structure_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_280));
    Qchain_of_available_frame_displays = 
	    STATIC_SYMBOL("CHAIN-OF-AVAILABLE-FRAME-DISPLAYS",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qchain_of_available_frame_displays,
	    Chain_of_available_frame_displays);
    record_system_variable(Qchain_of_available_frame_displays,Qutilities2,
	    Nil,Qnil,Qt,Qnil,Qnil);
    Qframe_display_count = STATIC_SYMBOL("FRAME-DISPLAY-COUNT",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qframe_display_count,Frame_display_count);
    record_system_variable(Qframe_display_count,Qutilities2,
	    FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    SET_SYMBOL_FUNCTION(Qframe_display_structure_memory_usage,
	    STATIC_FUNCTION(frame_display_structure_memory_usage,NIL,FALSE,
	    0,0));
    SET_SYMBOL_FUNCTION(Qoutstanding_frame_display_count,
	    STATIC_FUNCTION(outstanding_frame_display_count,NIL,FALSE,0,0));
    reclaim_structure_for_frame_display_1 = 
	    STATIC_FUNCTION(reclaim_structure_for_frame_display,NIL,FALSE,1,1);
    record_direct_structure_method(Qreclaim_structure,Qframe_display,
	    reclaim_structure_for_frame_display_1);
    Qdynamic_temporary_workspace = 
	    STATIC_SYMBOL("DYNAMIC-TEMPORARY-WORKSPACE",AB_package);
    Qavailable_dynamic_rule_displays_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_dynamic_rule_displays_hash_vector_43_vectors,
	    Available_dynamic_rule_displays_hash_vector_43_vectors);
    record_system_variable(Qavailable_dynamic_rule_displays_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_dynamic_rule_displays_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_dynamic_rule_displays_hash_vector_43_vectors,
	    Count_of_dynamic_rule_displays_hash_vector_43_vectors);
    record_system_variable(Qcount_of_dynamic_rule_displays_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qout_dynamic_rule_displays_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qdynamic_rule_displays_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("DYNAMIC-RULE-DISPLAYS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_281 = STATIC_STRING("1q83-Rxy83*By83-Oky09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_dynamic_rule_displays_hash_vector_43_vectors);
    push_optimized_constant(Qdynamic_rule_displays_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_281));
    SET_SYMBOL_FUNCTION(Qdynamic_rule_displays_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(dynamic_rule_displays_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_dynamic_rule_displays_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_dynamic_rule_displays_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qdynamic_rule_displays_tree_for_hash = 
	    STATIC_SYMBOL("DYNAMIC-RULE-DISPLAYS-TREE-FOR-HASH",AB_package);
    Qdynamic_rule_display_hash_table = 
	    STATIC_SYMBOL("DYNAMIC-RULE-DISPLAY-HASH-TABLE",AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qdynamic_rule_display_hash_table,
	    Dynamic_rule_display_hash_table);
    record_system_variable(Qdynamic_rule_display_hash_table,Qqueries,Nil,
	    Qnil,Qnil,Qnil,Qnil);
    Qreclaim_dynamic_rule_display = 
	    STATIC_SYMBOL("RECLAIM-DYNAMIC-RULE-DISPLAY",AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_dynamic_rule_display,
	    STATIC_FUNCTION(reclaim_dynamic_rule_display,NIL,FALSE,1,1));
    array_constant_31 = STATIC_ARRAY(list_constant_27,(SI_Long)1L,
	    FIX((SI_Long)40L));
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)0L,(SI_Long)71L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)1L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)2L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)3L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)4L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)5L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)6L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)7L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)8L,(SI_Long)98L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)9L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)10L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)11L,(SI_Long)100L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)12L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)13L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)14L,(SI_Long)103L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)15L,(SI_Long)115L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)16L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)17L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)18L,(SI_Long)102L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)19L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)20L,(SI_Long)114L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)21L,(SI_Long)117L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)22L,(SI_Long)108L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)23L,(SI_Long)101L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)24L,(SI_Long)32L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)25L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)26L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)27L,(SI_Long)118L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)28L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)29L,(SI_Long)99L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)30L,(SI_Long)97L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)31L,(SI_Long)116L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)32L,(SI_Long)105L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)33L,(SI_Long)111L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)34L,(SI_Long)110L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)38L,(SI_Long)35L);
    UBYTE_16_ISASET_1(array_constant_31,(SI_Long)39L,(SI_Long)57344L);
    string_constant_150 = 
	    STATIC_STRING("Invocation with no generic bindings.");
    Qdynamic_display_delay_in_milliseconds = 
	    STATIC_SYMBOL("DYNAMIC-DISPLAY-DELAY-IN-MILLISECONDS",AB_package);
    string_constant_151 = STATIC_STRING("Dynamic Rule Invocation Display");
    Qavailable_generic_rule_instance_displays_hash_vector_43_vectors = 
	    STATIC_SYMBOL("AVAILABLE-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qavailable_generic_rule_instance_displays_hash_vector_43_vectors,
	    Available_generic_rule_instance_displays_hash_vector_43_vectors);
    record_system_variable(Qavailable_generic_rule_instance_displays_hash_vector_43_vectors,
	    Qutilities2,Nil,Qnil,Qt,Qnil,Qnil);
    Qcount_of_generic_rule_instance_displays_hash_vector_43_vectors = 
	    STATIC_SYMBOL("COUNT-OF-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qcount_of_generic_rule_instance_displays_hash_vector_43_vectors,
	    Count_of_generic_rule_instance_displays_hash_vector_43_vectors);
    record_system_variable(Qcount_of_generic_rule_instance_displays_hash_vector_43_vectors,
	    Qutilities2,FIX((SI_Long)0L),Qnil,Qt,Qnil,Qnil);
    Qout_generic_rule_instance_displays_hash_vector_43_vectors = 
	    STATIC_SYMBOL("OUT-GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTORS",
	    AB_package);
    Qgeneric_rule_instance_displays_hash_vector_43_vector_memory_usage = 
	    STATIC_SYMBOL("GENERIC-RULE-INSTANCE-DISPLAYS-HASH-VECTOR-43-VECTOR-MEMORY-USAGE",
	    AB_package);
    string_constant_282 = STATIC_STRING("1q83-Vjy83*By83-Ony09k9l");
    clear_optimized_constants();
    push_optimized_constant(Qout_generic_rule_instance_displays_hash_vector_43_vectors);
    push_optimized_constant(Qgeneric_rule_instance_displays_hash_vector_43_vector_memory_usage);
    update_object_pool_meters_list(regenerate_optimized_constant(string_constant_282));
    SET_SYMBOL_FUNCTION(Qgeneric_rule_instance_displays_hash_vector_43_vector_memory_usage,
	    STATIC_FUNCTION(generic_rule_instance_displays_hash_vector_43_vector_memory_usage,
	    NIL,FALSE,0,0));
    SET_SYMBOL_FUNCTION(Qout_generic_rule_instance_displays_hash_vector_43_vectors,
	    STATIC_FUNCTION(out_generic_rule_instance_displays_hash_vector_43_vectors,
	    NIL,FALSE,0,0));
    Qgeneric_rule_instance_displays_tree_for_hash = 
	    STATIC_SYMBOL("GENERIC-RULE-INSTANCE-DISPLAYS-TREE-FOR-HASH",
	    AB_package);
    Qgeneric_rule_instance_display_hash_table = 
	    STATIC_SYMBOL("GENERIC-RULE-INSTANCE-DISPLAY-HASH-TABLE",
	    AB_package);
    SET_SYMBOL_VALUE_LOCATION(Qgeneric_rule_instance_display_hash_table,
	    Generic_rule_instance_display_hash_table);
    record_system_variable(Qgeneric_rule_instance_display_hash_table,
	    Qqueries,Nil,Qnil,Qnil,Qnil,Qnil);
    string_constant_152 = STATIC_STRING("Dynamic Generic Rule Display");
    Qg2_run_inspect_command = STATIC_SYMBOL("G2-RUN-INSPECT-COMMAND",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_run_inspect_command,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_run_inspect_command,
	    STATIC_FUNCTION(g2_run_inspect_command,NIL,FALSE,1,1));
    Qg2_run_inspect_command_system_rpc_internal = 
	    STATIC_SYMBOL("G2-RUN-INSPECT-COMMAND-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qcommand_string = STATIC_SYMBOL("COMMAND-STRING",AB_package);
    list_constant_76 = STATIC_LIST((SI_Long)3L,Qcommand_string,Ktype,Qtext);
    list_constant_77 = STATIC_CONS(list_constant_76,Qnil);
    Qsystem_defined_rpc = STATIC_SYMBOL("SYSTEM-DEFINED-RPC",AB_package);
    mutate_global_property(Qg2_run_inspect_command,
	    make_system_rpc_1(Qg2_run_inspect_command_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_77,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_run_inspect_command,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    Kstack_error = STATIC_SYMBOL("STACK-ERROR",Pkeyword);
    SET_SYMBOL_FUNCTION(Qg2_run_inspect_command_system_rpc_internal,
	    STATIC_FUNCTION(g2_run_inspect_command_system_rpc_internal,NIL,
	    FALSE,2,2));
    if (Highest_inspect_session_id == UNBOUND)
	Highest_inspect_session_id = FIX((SI_Long)1L);
    Qquery_representation = STATIC_SYMBOL("QUERY-REPRESENTATION",AB_package);
    Qcallback_representation = STATIC_SYMBOL("CALLBACK-REPRESENTATION",
	    AB_package);
    list_constant_78 = STATIC_CONS(Qcallback_representation,Qnil);
    check_if_superior_classes_are_defined(Qquery_representation,
	    list_constant_78);
    string_constant_283 = STATIC_STRING("1l1l8t");
    string_constant_284 = 
	    STATIC_STRING("1r4z8r83YWy83YWy83YRy83YRy00001m1l8l1l8o000004z8r83YYy83YYy83YRy83YRy00001m1l8l1l8o000004z8r83YSy83YSy83YRy83YRy00001m1l8l1l8o00");
    string_constant_285 = 
	    STATIC_STRING("0004z8r83YUy83YUy83YRy83YRy00001m1l8l1l8o000004z8r83YXy83YXy83YRy83YRy00001m1l8l1l8o000004z8r83YVy83YVy83YRy83YRy00001m1l8l1l8o0");
    string_constant_286 = 
	    STATIC_STRING("00004z8r83YTy83YTy83YRy83YRy00001m1l8l1l8o00000");
    string_constant_287 = 
	    STATIC_STRING("1t8q1n83YRy1l830Xy8t1n83YWy08o1n83YYy08o1n83YSy08o1n83YUy08o1n83YXy08o1n83YVy08o1n83YTy08o");
    temp = regenerate_optimized_constant(string_constant_283);
    temp_1 = regenerate_optimized_constant(LIST_3(string_constant_284,
	    string_constant_285,string_constant_286));
    add_class_to_environment(9,Qquery_representation,list_constant_78,Nil,
	    temp,Nil,temp_1,list_constant_78,
	    regenerate_optimized_constant(string_constant_287),Nil);
    Qquery_representation_task = STATIC_SYMBOL("QUERY-REPRESENTATION-TASK",
	    AB_package);
    Qreclaim_query_representation_task_value = 
	    STATIC_SYMBOL("RECLAIM-QUERY-REPRESENTATION-TASK-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_query_representation_task_value,
	    STATIC_FUNCTION(reclaim_query_representation_task_value,NIL,
	    FALSE,2,2));
    mutate_global_property(Qquery_representation_task,
	    SYMBOL_FUNCTION(Qreclaim_query_representation_task_value),
	    Qslot_value_reclaimer);
    Qquery_representation_user_data = 
	    STATIC_SYMBOL("QUERY-REPRESENTATION-USER-DATA",AB_package);
    Qreclaim_query_representation_user_data_value = 
	    STATIC_SYMBOL("RECLAIM-QUERY-REPRESENTATION-USER-DATA-VALUE",
	    AB_package);
    SET_SYMBOL_FUNCTION(Qreclaim_query_representation_user_data_value,
	    STATIC_FUNCTION(reclaim_query_representation_user_data_value,
	    NIL,FALSE,2,2));
    mutate_global_property(Qquery_representation_user_data,
	    SYMBOL_FUNCTION(Qreclaim_query_representation_user_data_value),
	    Qslot_value_reclaimer);
    Qresume_search_task_in_workstation = 
	    STATIC_SYMBOL("RESUME-SEARCH-TASK-IN-WORKSTATION",AB_package);
    Qreclaim_frame_serial_number = 
	    STATIC_SYMBOL("RECLAIM-FRAME-SERIAL-NUMBER",AB_package);
    Qg2_defstruct_structure_name_schedule_task_g2_struct = 
	    STATIC_SYMBOL("SCHEDULE-TASK-G2-STRUCT",
	    G2_DEFSTRUCT_STRUCTURE_NAME_package);
    SET_SYMBOL_FUNCTION(Qresume_search_task_in_workstation,
	    STATIC_FUNCTION(resume_search_task_in_workstation,NIL,FALSE,3,3));
    Qg2_start_inspect_session = STATIC_SYMBOL("G2-START-INSPECT-SESSION",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_start_inspect_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_start_inspect_session,
	    STATIC_FUNCTION(g2_start_inspect_session,NIL,FALSE,5,5));
    Qsocket = STATIC_SYMBOL("SOCKET",AB_package);
    Qsession_id = STATIC_SYMBOL("SESSION-ID",AB_package);
    Qg2_pause_inspect_session = STATIC_SYMBOL("G2-PAUSE-INSPECT-SESSION",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_pause_inspect_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_pause_inspect_session,
	    STATIC_FUNCTION(g2_pause_inspect_session,NIL,FALSE,1,1));
    Qg2_resume_inspect_session = STATIC_SYMBOL("G2-RESUME-INSPECT-SESSION",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_resume_inspect_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_resume_inspect_session,
	    STATIC_FUNCTION(g2_resume_inspect_session,NIL,FALSE,1,1));
    Qg2_abort_inspect_session = STATIC_SYMBOL("G2-ABORT-INSPECT-SESSION",
	    AB_package);
    gensymed_symbol = Nil;
    mutate_global_property(Qg2_abort_inspect_session,gensymed_symbol,
	    Qfunction_keeps_procedure_environment_valid_qm);
    SET_SYMBOL_FUNCTION(Qg2_abort_inspect_session,
	    STATIC_FUNCTION(g2_abort_inspect_session,NIL,FALSE,1,1));
    Qfinished = STATIC_SYMBOL("FINISHED",AB_package);
    Qframes_remaining = STATIC_SYMBOL("FRAMES-REMAINING",AB_package);
    Qg2_start_inspect_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-START-INSPECT-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    Qcallback = STATIC_SYMBOL("CALLBACK",AB_package);
    list_constant_79 = STATIC_CONS(Qsymbol,Qnil);
    list_constant_81 = STATIC_LIST_STAR((SI_Long)3L,Qcallback,Ktype,
	    list_constant_79);
    Quser_data = STATIC_SYMBOL("USER-DATA",AB_package);
    Qdatum = STATIC_SYMBOL("DATUM",AB_package);
    list_constant_82 = STATIC_LIST((SI_Long)3L,Quser_data,Ktype,Qdatum);
    Qpriority = STATIC_SYMBOL("PRIORITY",AB_package);
    list_constant_80 = STATIC_CONS(Qinteger,Qnil);
    list_constant_83 = STATIC_LIST_STAR((SI_Long)3L,Qpriority,Ktype,
	    list_constant_80);
    Qtask_interval = STATIC_SYMBOL("TASK-INTERVAL",AB_package);
    list_constant_84 = STATIC_LIST((SI_Long)3L,Qtask_interval,Ktype,Qfloat);
    list_constant_85 = STATIC_LIST((SI_Long)5L,list_constant_76,
	    list_constant_81,list_constant_82,list_constant_83,
	    list_constant_84);
    mutate_global_property(Qg2_start_inspect_session,
	    make_system_rpc_1(Qg2_start_inspect_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_85,
	    Nil,T),list_constant_80),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_start_inspect_session,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_start_inspect_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_start_inspect_session_system_rpc_internal,
	    NIL,FALSE,6,6));
    Qg2_pause_inspect_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-PAUSE-INSPECT-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    list_constant_86 = STATIC_CONS(Ktype,list_constant_80);
    list_constant_87 = STATIC_CONS(Qsession_id,list_constant_86);
    list_constant_88 = STATIC_CONS(list_constant_87,Qnil);
    mutate_global_property(Qg2_pause_inspect_session,
	    make_system_rpc_1(Qg2_pause_inspect_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_88,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_pause_inspect_session,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_pause_inspect_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_pause_inspect_session_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_resume_inspect_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-RESUME-INSPECT-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_resume_inspect_session,
	    make_system_rpc_1(Qg2_resume_inspect_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_88,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_resume_inspect_session,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_resume_inspect_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_resume_inspect_session_system_rpc_internal,
	    NIL,FALSE,2,2));
    Qg2_abort_inspect_session_system_rpc_internal = 
	    STATIC_SYMBOL("G2-ABORT-INSPECT-SESSION-SYSTEM-RPC-INTERNAL",
	    AB_package);
    mutate_global_property(Qg2_abort_inspect_session,
	    make_system_rpc_1(Qg2_abort_inspect_session_system_rpc_internal,
	    convert_description_list_to_managed_array(3,list_constant_88,
	    Nil,T),Qnil),Qsystem_defined_rpc);
    temp_2 = adjoin(2,Qg2_abort_inspect_session,System_defined_rpcs);
    System_defined_rpcs = temp_2;
    SET_SYMBOL_FUNCTION(Qg2_abort_inspect_session_system_rpc_internal,
	    STATIC_FUNCTION(g2_abort_inspect_session_system_rpc_internal,
	    NIL,FALSE,2,2));
}
