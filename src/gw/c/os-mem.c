/* os-mem.c
 * Input file:  os-memory.lisp
 * Copyright (c) 1986 - 2017 Gensym Corporation.  All Rights Reserved.
 */

#include "user.h"
#include "os-mem.h"


Object G2int_default_bytes_for_renderings = UNBOUND;

Object G2int_minimum_bytes_for_renderings = UNBOUND;

/* MAKE-REGION-INFO */
Object g2int_make_region_info(index_1,name,command_line_keyword_argument,
	    environment_variable)
    Object index_1, name, command_line_keyword_argument, environment_variable;
{
    Object array;

    x_note_fn_call(12,0);
    array = make_array(1,FIX((SI_Long)10L));
    SVREF(array,FIX((SI_Long)0L)) = index_1;
    SVREF(array,FIX((SI_Long)1L)) = name;
    SVREF(array,FIX((SI_Long)2L)) = command_line_keyword_argument;
    SVREF(array,FIX((SI_Long)3L)) = environment_variable;
    ISVREF(array,(SI_Long)4L) = FIX((SI_Long)0L);
    ISVREF(array,(SI_Long)5L) = FIX((SI_Long)0L);
    SVREF(array,FIX((SI_Long)6L)) = Nil;
    ISVREF(array,(SI_Long)7L) = FIX((SI_Long)0L);
    ISVREF(array,(SI_Long)8L) = FIX((SI_Long)0L);
    ISVREF(array,(SI_Long)9L) = FIX((SI_Long)0L);
    return VALUES_1(array);
}

Object G2int_region_1_info = UNBOUND;

Object G2int_region_2_info = UNBOUND;

Object G2int_region_3_info = UNBOUND;

Object G2int_all_region_info = UNBOUND;

Object G2int_number_of_memory_regions = UNBOUND;

static Object Qg2int_telewindows;  /* telewindows */

static Object string_constant;     /* "TWRGN1LMT" */

static Object string_constant_1;   /* "TWRGN2LMT" */

static Object string_constant_2;   /* "TWRGN3LMT" */

static Object Qg2int_gsi;          /* gsi */

static Object string_constant_3;   /* "GSIRGN1LMT" */

static Object string_constant_4;   /* "GSIRGN2LMT" */

static Object Qg2int_ab;           /* ab */

static Object Qg2int_alphaosf;     /* alphaosf */

/* INITIALIZE-ALL-REGION-INFO */
Object g2int_initialize_all_region_info(system_1)
    Object system_1;
{
    Object svref_arg_1, svref_new_value;
    SI_Long temp;

    x_note_fn_call(12,1);
    if (EQ(system_1,Qg2int_telewindows)) {
	svref_arg_1 = G2int_region_1_info;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = string_constant;
	svref_arg_1 = G2int_region_2_info;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = string_constant_1;
	svref_arg_1 = G2int_region_3_info;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = string_constant_2;
    }
    else if (EQ(system_1,Qg2int_gsi)) {
	svref_arg_1 = G2int_region_1_info;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = string_constant_3;
	svref_arg_1 = G2int_region_2_info;
	SVREF(svref_arg_1,FIX((SI_Long)3L)) = string_constant_4;
    }
    if (EQ(system_1,Qg2int_ab)) {
	svref_arg_1 = G2int_region_1_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)20000000L : (SI_Long)10000000L;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX(temp);
	svref_arg_1 = G2int_region_1_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)9500000L : (SI_Long)4750000L;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX(temp);
	svref_arg_1 = G2int_region_2_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)5000000L : (SI_Long)3500000L;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX(temp);
	svref_arg_1 = G2int_region_2_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)5000000L : (SI_Long)3500000L;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX(temp);
    }
    else if (EQ(system_1,Qg2int_telewindows)) {
	svref_arg_1 = G2int_region_1_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)2800000L : (SI_Long)1400000L;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX(temp);
	svref_arg_1 = G2int_region_1_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)1600000L : (SI_Long)800000L;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX(temp);
	svref_arg_1 = G2int_region_2_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)800000L : (SI_Long)800000L;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX(temp);
	svref_arg_1 = G2int_region_2_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)800000L : (SI_Long)800000L;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX(temp);
    }
    else if (EQ(system_1,Qg2int_gsi)) {
	svref_arg_1 = G2int_region_1_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)3500000L : (SI_Long)800000L;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX(temp);
	svref_arg_1 = G2int_region_1_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)2900000L : (SI_Long)800000L;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX(temp);
	svref_arg_1 = G2int_region_2_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)300000L : (SI_Long)500000L;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX(temp);
	svref_arg_1 = G2int_region_2_info;
	temp = EQ(Qg2int_alphaosf,G2int_g2_machine_type) ? 
		(SI_Long)300000L : (SI_Long)500000L;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX(temp);
    }
    if (EQ(system_1,Qg2int_ab) || EQ(system_1,Qg2int_telewindows)) {
	svref_arg_1 = G2int_region_3_info;
	ISVREF(svref_arg_1,(SI_Long)4L) = FIX((SI_Long)2500000L);
	svref_arg_1 = G2int_region_3_info;
	ISVREF(svref_arg_1,(SI_Long)5L) = FIX((SI_Long)400000L);
    }
    svref_arg_1 = G2int_all_region_info;
    temp = (SI_Long)1L - (SI_Long)1L;
    svref_new_value = G2int_region_1_info;
    ISVREF(svref_arg_1,temp) = svref_new_value;
    svref_arg_1 = G2int_all_region_info;
    temp = (SI_Long)2L - (SI_Long)1L;
    svref_new_value = G2int_region_2_info;
    ISVREF(svref_arg_1,temp) = svref_new_value;
    if (EQ(system_1,Qg2int_ab) || EQ(system_1,Qg2int_telewindows)) {
	svref_arg_1 = G2int_all_region_info;
	temp = (SI_Long)3L - (SI_Long)1L;
	svref_new_value = G2int_region_3_info;
	ISVREF(svref_arg_1,temp) = svref_new_value;
	G2int_number_of_memory_regions = FIX((SI_Long)3L);
    }
    else
	G2int_number_of_memory_regions = FIX((SI_Long)2L);
    return VALUES_1(G2int_all_region_info);
}

static Object float_constant;      /* 1.0995E+# */

static Object float_constant_1;    /* 0.0 */

/* INITIALIZE-MEMORY-FOR-REGION */
Object g2int_initialize_memory_for_region(system_1,index_1)
    Object system_1, index_1;
{
    Object info, svref_new_value, desired_allocation, minimum_size;
    Object maximum_size, region_name, out_of_memory_p, temp;
    char too_small_p, too_large_p;
    double target, temp_1;

    x_note_fn_call(12,2);
    info = ISVREF(G2int_all_region_info,IFIX(FIXNUM_SUB1(index_1)));
    if (info) {
	svref_new_value = 
		g2int_get_command_line_keyword_argument_as_memory_size(1,
		ISVREF(info,(SI_Long)2L));
	if (svref_new_value);
	else
	    svref_new_value = 
		    g2int_read_memory_size_for_gensym_environment_variable(ISVREF(info,
		    (SI_Long)3L));
	SVREF(info,FIX((SI_Long)6L)) = svref_new_value;
	svref_new_value = ISVREF(info,(SI_Long)6L);
	if (svref_new_value);
	else
	    svref_new_value = ISVREF(info,(SI_Long)4L);
	SVREF(info,FIX((SI_Long)7L)) = svref_new_value;
	desired_allocation = ISVREF(info,(SI_Long)7L);
	minimum_size = ISVREF(info,(SI_Long)5L);
	maximum_size = float_constant;
	too_small_p = NUM_LT(desired_allocation,minimum_size);
	too_large_p = NUM_GT(desired_allocation,maximum_size);
	if (too_small_p || too_large_p) {
	    g2int_reject_proposed_region_size(system_1,index_1,
		    desired_allocation,minimum_size,maximum_size);
	    svref_new_value = too_small_p ? minimum_size : maximum_size;
	}
	else
	    svref_new_value = desired_allocation;
	SVREF(info,FIX((SI_Long)7L)) = svref_new_value;
	region_name = ISVREF(info,(SI_Long)1L);
	out_of_memory_p = Nil;
	if (EQ(region_name,Kstatic) || EQ(region_name,Kdynamic)) {
	    target = (double)IFIX(G2int_size_of_chunks_for_allocate_to_target);
	  next_loop:
	    temp = lfloat(ISVREF(info,(SI_Long)7L),float_constant_1);
	    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    if ( !(target < temp_1))
		goto end_loop;
	    if ( !TRUEP(allocate_memory_to_target(region_name,
		    DOUBLE_TO_DOUBLE_FLOAT(target)))) {
		out_of_memory_p = T;
		goto end;
	    }
	    target = target + 4000000.0;
	    goto next_loop;
	  end_loop:
	    if ( !TRUEP(allocate_memory_to_target(region_name,ISVREF(info,
		    (SI_Long)7L))))
		out_of_memory_p = T;
	  end:;
	}
	if (out_of_memory_p)
	    g2int_exit_lisp_process(0);
	return VALUES_1(Nil);
    }
    else
	return VALUES_1(Nil);
}

/* SET-UP-LISP-MEMORY-MANAGEMENT */
Object g2int_set_up_lisp_memory_management(system_1)
    Object system_1;
{
    SI_Long index_1, ab_loop_bind_;

    x_note_fn_call(12,3);
    g2int_initialize_all_region_info(system_1);
    index_1 = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
  next_loop:
    if (index_1 > ab_loop_bind_)
	goto end_loop;
    g2int_initialize_memory_for_region(system_1,FIX(index_1));
    index_1 = index_1 + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(Qnil);
}

Object G2int_gsi_suppress_output = UNBOUND;

/* REPORT-MEMORY-USAGE */
Object g2int_report_memory_usage(system_1)
    Object system_1;
{
    Object ab_loop_it_, info, svref_new_value;
    SI_Long index_1, ab_loop_bind_;
    char temp;

    x_note_fn_call(12,4);
    if ( !TRUEP(g2int_gsi_option_is_set_p(G2int_gsi_suppress_output))) {
	index_1 = (SI_Long)1L;
	ab_loop_it_ = Nil;
      next_loop:
	if (index_1 > (SI_Long)2L)
	    goto end_loop;
	ab_loop_it_ = ISVREF(ISVREF(G2int_all_region_info,index_1 - 
		(SI_Long)1L),(SI_Long)6L);
	if (ab_loop_it_) {
	    temp = TRUEP(ab_loop_it_);
	    goto end;
	}
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop;
      end_loop:
	temp = TRUEP(Qnil);
      end:;
    }
    else
	temp = TRUEP(Nil);
    if (temp) {
	index_1 = (SI_Long)1L;
	ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
	info = Nil;
      next_loop_1:
	if (index_1 > ab_loop_bind_)
	    goto end_loop_1;
	info = ISVREF(G2int_all_region_info,index_1 - (SI_Long)1L);
	svref_new_value = g2int_g2_region_memory_usage_as_float(FIX(index_1));
	SVREF(info,FIX((SI_Long)8L)) = svref_new_value;
	svref_new_value = g2int_g2_region_memory_size_as_float(FIX(index_1));
	SVREF(info,FIX((SI_Long)9L)) = svref_new_value;
	index_1 = index_1 + (SI_Long)1L;
	goto next_loop_1;
      end_loop_1:;
	g2int_announce_region_sizes(system_1);
	return g2int_check_for_region_deficits(system_1);
    }
    else
	return VALUES_1(Nil);
}

static Object string_constant_5;   /* "" */

static Object string_constant_6;   /* "0" */

/* FORMAT-INTO-STRING-GROUPING-THOUSANDS */
Object g2int_format_into_string_grouping_thousands(thing)
    Object thing;
{
    Object temp, number_of_digits, output_string, index_1, comma_counter;
    Object schar_new_value;
    SI_Long ab_loopvar_, temp_1, number_of_commas, length_of_string;
    double quotient, digits;

    x_note_fn_call(12,5);
    if (STRINGP(thing))
	return VALUES_1(thing);
    else if ( !NUMBERP(thing))
	return VALUES_1(string_constant_5);
    else {
	temp = FIX((SI_Long)0L);
	if (NUM_EQ(thing,temp))
	    return VALUES_1(string_constant_6);
	else {
	    temp = lfloat(thing,float_constant_1);
	    quotient = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    ab_loopvar_ = (SI_Long)0L;
	  next_loop:
	    temp = FIX((SI_Long)0L);
	    if (NUM_EQ(DOUBLE_TO_DOUBLE_FLOAT(quotient),temp))
		goto end_loop;
	    ab_loopvar_ = ab_loopvar_ + (SI_Long)1L;
	    temp = lffloor(DOUBLE_TO_DOUBLE_FLOAT(quotient),FIX((SI_Long)10L));
	    quotient = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    goto next_loop;
	  end_loop:
	    number_of_digits = FIX(ab_loopvar_);
	    goto end;
	    number_of_digits = Qnil;
	  end:;
	    temp_1 = IFIX(FIXNUM_SUB1(number_of_digits)) / (SI_Long)3L;
	    number_of_commas = temp_1;
	    length_of_string = IFIX(number_of_digits) + number_of_commas;
	    output_string = make_string(1,FIX(length_of_string));
	    index_1 = FIX(length_of_string - (SI_Long)1L);
	    comma_counter = FIX((SI_Long)1L);
	    temp = lfloat(thing,float_constant_1);
	    digits = DOUBLE_FLOAT_TO_DOUBLE(temp);
	  next_loop_1:
	    if ( !(digits >= 1.0))
		goto end_loop_1;
	    schar_new_value = 
		    digit_char(lfloor(mod(DOUBLE_TO_DOUBLE_FLOAT(digits),
		    FIX((SI_Long)10L)),_),_,_);
	    SET_SCHAR(output_string,index_1,schar_new_value);
	    index_1 = FIXNUM_SUB1(index_1);
	    if ( !(IFIX(index_1) >= (SI_Long)0L))
		goto end_loop_1;
	    comma_counter = FIXNUM_ADD1(comma_counter);
	    if (IFIX(comma_counter) > (SI_Long)3L) {
		temp = CHR(',');
		SET_SCHAR(output_string,index_1,temp);
		index_1 = FIXNUM_SUB1(index_1);
		comma_counter = FIX((SI_Long)1L);
	    }
	    temp = lffloor(DOUBLE_TO_DOUBLE_FLOAT(digits),FIX((SI_Long)10L));
	    digits = DOUBLE_FLOAT_TO_DOUBLE(temp);
	    goto next_loop_1;
	  end_loop_1:;
	    return VALUES_1(output_string);
	}
    }
}

/* RIGHT-JUSTIFY-IN-COLUMN */
Object g2int_right_justify_in_column(thing,column_size)
    Object thing, column_size;
{
    Object formatted_string, length_of_formatted_string;

    x_note_fn_call(12,6);
    formatted_string = g2int_format_into_string_grouping_thousands(thing);
    length_of_formatted_string = length(formatted_string);
    if (NUM_GT(length_of_formatted_string,column_size))
	return VALUES_1(formatted_string);
    else
	return concatenate(3,Qstring,make_string(3,minus(column_size,
		length_of_formatted_string),Kinitial_element,CHR(' ')),
		formatted_string);
}

static Object string_constant_7;   /* "G2" */

static Object string_constant_8;   /* "Telewindows" */

static Object string_constant_9;   /* "unsupplied" */

static Object string_constant_10;  /* "unknown" */

/* ANNOUNCE-REGION-SIZES */
Object g2int_announce_region_sizes(system_name)
    Object system_name;
{
    Object temp, temp_1, desired_total, unsupplied_desired_component_p;
    Object lowest_total, default_total, measured_size_total;
    Object measured_usage_total, info, lowest_size, default_size, desired_size;
    Object measured_size, measured_usage, temp_2, temp_3, temp_4, temp_5;
    Object temp_6, incf_arg;
    SI_Long region_index, ab_loop_bind_;

    x_note_fn_call(12,7);
    temp = Terminal_io;
    if (EQ(system_name,Qg2int_ab))
	temp_1 = string_constant_7;
    else if (EQ(system_name,Qg2int_telewindows))
	temp_1 = string_constant_8;
    else
	temp_1 = system_name;
    format((SI_Long)3L,temp,"~&~a Memory Region Sizes (bytes):~%",temp_1);
    format((SI_Long)2L,Terminal_io,
	    "~&  region#        minimum        default        desired    measured size  measured usage~%");
    format((SI_Long)2L,Terminal_io,
	    "  -------      ----------     ----------     ----------     ----------     ----------  ~%");
    desired_total = FIX((SI_Long)0L);
    unsupplied_desired_component_p = Nil;
    lowest_total = FIX((SI_Long)0L);
    default_total = FIX((SI_Long)0L);
    measured_size_total = FIX((SI_Long)0L);
    measured_usage_total = FIX((SI_Long)0L);
    region_index = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
    info = Nil;
    lowest_size = Nil;
    default_size = Nil;
    desired_size = Nil;
    measured_size = Nil;
    measured_usage = Nil;
  next_loop:
    if (region_index > ab_loop_bind_)
	goto end_loop;
    info = ISVREF(G2int_all_region_info,region_index - (SI_Long)1L);
    lowest_size = ISVREF(info,(SI_Long)5L);
    default_size = ISVREF(info,(SI_Long)4L);
    desired_size = ISVREF(info,(SI_Long)7L);
    measured_size = ISVREF(info,(SI_Long)9L);
    measured_usage = ISVREF(info,(SI_Long)8L);
    temp = Terminal_io;
    temp_1 = FIX(region_index);
    temp_2 = g2int_right_justify_in_column(lowest_size,FIX((SI_Long)15L));
    temp_3 = g2int_right_justify_in_column(default_size,FIX((SI_Long)15L));
    temp_4 = desired_size;
    if (temp_4);
    else
	temp_4 = string_constant_9;
    temp_4 = g2int_right_justify_in_column(temp_4,FIX((SI_Long)15L));
    temp_5 = measured_size;
    if (temp_5);
    else
	temp_5 = string_constant_10;
    temp_5 = g2int_right_justify_in_column(temp_5,FIX((SI_Long)15L));
    temp_6 = measured_usage;
    if (temp_6);
    else
	temp_6 = string_constant_10;
    format((SI_Long)8L,temp,"     ~a    ~a~a~a~a~a~%",temp_1,temp_2,temp_3,
	    temp_4,temp_5,g2int_right_justify_in_column(temp_6,
	    FIX((SI_Long)15L)));
    incf_arg = lowest_size;
    lowest_total = add(lowest_total,incf_arg);
    incf_arg = default_size;
    default_total = add(default_total,incf_arg);
    if (desired_size) {
	incf_arg = desired_size;
	desired_total = add(desired_total,incf_arg);
    }
    else
	unsupplied_desired_component_p = T;
    if (measured_usage) {
	incf_arg = measured_usage;
	measured_usage_total = add(measured_usage_total,incf_arg);
    }
    if (measured_size) {
	incf_arg = measured_size;
	measured_size_total = add(measured_size_total,incf_arg);
    }
    region_index = region_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    format((SI_Long)2L,Terminal_io,
	    "  -------      ----------     ----------     ----------     ----------     ----------  ~%");
    temp = Terminal_io;
    temp_1 = g2int_right_justify_in_column(lowest_total,FIX((SI_Long)15L));
    temp_2 = g2int_right_justify_in_column(default_total,FIX((SI_Long)15L));
    temp_3 = g2int_right_justify_in_column(unsupplied_desired_component_p ?
	     string_constant_5 : desired_total,FIX((SI_Long)15L));
    temp_4 = g2int_right_justify_in_column(measured_size_total,
	    FIX((SI_Long)15L));
    format((SI_Long)7L,temp,"  Totals: ~a~a~a~a~a~%",temp_1,temp_2,temp_3,
	    temp_4,g2int_right_justify_in_column(measured_usage_total,
	    FIX((SI_Long)15L)));
    return VALUES_1(Qnil);
}

static Object string_constant_11;  /* "GSI" */

/* REJECT-PROPOSED-REGION-SIZE */
Object g2int_reject_proposed_region_size(system_name,region_index,
	    proposed_region_size,lowest_allowed_value,highest_allowed_value)
    Object system_name, region_index, proposed_region_size;
    Object lowest_allowed_value, highest_allowed_value;
{
    Object system_name_for_user, temp;

    x_note_fn_call(12,8);
    if (EQ(system_name,Qg2int_ab))
	system_name_for_user = string_constant_7;
    else if (EQ(system_name,Qg2int_telewindows))
	system_name_for_user = string_constant_8;
    else if (EQ(system_name,Qg2int_gsi))
	system_name_for_user = string_constant_11;
    else
	system_name_for_user = system_name;
    format((SI_Long)2L,Terminal_io,
	    "~&*************************************************************************~%");
    temp = Terminal_io;
    format((SI_Long)4L,temp,
	    "*   Attempt to set memory region #~a to ~a bytes.~%",
	    region_index,
	    g2int_format_into_string_grouping_thousands(proposed_region_size));
    if (NUM_LT(proposed_region_size,lowest_allowed_value)) {
	format((SI_Long)3L,Terminal_io,
		"*   This value is too low for proper ~a operation.~%",
		system_name_for_user);
	temp = Terminal_io;
	format((SI_Long)4L,temp,
		"*   ~a will use the lowest recommended value (~a bytes).~%",
		system_name_for_user,
		g2int_format_into_string_grouping_thousands(lowest_allowed_value));
    }
    else {
	format((SI_Long)3L,Terminal_io,
		"*   This value is too high for proper ~a operation.~%",
		system_name_for_user);
	temp = Terminal_io;
	format((SI_Long)4L,temp,
		"*   ~a will use the highest possible value (~a bytes).~%",
		system_name_for_user,
		g2int_format_into_string_grouping_thousands(highest_allowed_value));
    }
    return format((SI_Long)2L,Terminal_io,
	    "*************************************************************************~%");
}

/* REGION-IS-PREALLOCATED-P */
Object g2int_region_is_preallocated_p(region_index)
    Object region_index;
{
    Object temp;

    x_note_fn_call(12,9);
    temp = FIX((SI_Long)1L);
    temp = NUM_EQ(region_index,temp) ? T : Nil;
    if (temp)
	return VALUES_1(temp);
    else {
	temp = FIX((SI_Long)2L);
	return VALUES_1(NUM_EQ(region_index,temp) ? T : Nil);
    }
}

/* CHECK-FOR-REGION-DEFICITS */
Object g2int_check_for_region_deficits(system_name)
    Object system_name;
{
    Object info, default_region_size, proposed_region_size;
    Object measured_region_size, at_least_one_deficit_found_p;
    Object system_name_for_user, temp, temp_1, temp_2;
    SI_Long region_index, ab_loop_bind_;

    x_note_fn_call(12,10);
    region_index = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
    info = Nil;
    default_region_size = Nil;
    proposed_region_size = Nil;
    measured_region_size = Nil;
    at_least_one_deficit_found_p = Nil;
    if (EQ(system_name,Qg2int_ab))
	system_name_for_user = string_constant_7;
    else if (EQ(system_name,Qg2int_telewindows))
	system_name_for_user = string_constant_8;
    else if (EQ(system_name,Qg2int_gsi))
	system_name_for_user = string_constant_11;
    else
	system_name_for_user = system_name;
  next_loop:
    if (region_index > ab_loop_bind_)
	goto end_loop;
    info = ISVREF(G2int_all_region_info,region_index - (SI_Long)1L);
    default_region_size = ISVREF(info,(SI_Long)4L);
    proposed_region_size = ISVREF(info,(SI_Long)7L);
    measured_region_size = ISVREF(info,(SI_Long)9L);
    if (g2int_region_is_preallocated_p(FIX(region_index)) && 
	    (proposed_region_size ? NUM_LT(measured_region_size,
	    proposed_region_size) : NUM_LT(measured_region_size,
	    default_region_size))) {
	if ( !TRUEP(at_least_one_deficit_found_p)) {
	    format((SI_Long)2L,Terminal_io,
		    "~&****************************************************************~%");
	    format((SI_Long)2L,Terminal_io,
		    "*                            Warning:~%");
	    format((SI_Long)2L,Terminal_io,
		    "* Operating system could not allocate all memory requested for~%");
	    format((SI_Long)3L,Terminal_io,
		    "* ~a.  Performance may be degraded.  Please check the~%",
		    system_name_for_user);
	    format((SI_Long)3L,Terminal_io,
		    "* ~a Installation Manual for possible remedies.~%",
		    system_name_for_user);
	    format((SI_Long)2L,Terminal_io,
		    "*---------------------------------------------------------------~%");
	    at_least_one_deficit_found_p = T;
	}
	temp = Terminal_io;
	temp_1 = FIX(region_index);
	temp_2 = proposed_region_size;
	if (temp_2);
	else
	    temp_2 = default_region_size;
	format((SI_Long)5L,temp,
		"~&*   Region #~a: requested ~a, measured ~a.~%",temp_1,
		temp_2,measured_region_size);
    }
    region_index = region_index + (SI_Long)1L;
    goto next_loop;
  end_loop:
    if (at_least_one_deficit_found_p)
	format((SI_Long)2L,Terminal_io,
		"~&****************************************************************~%");
    return VALUES_1(Qnil);
}

Object G2int_unrecoverable_error_p = UNBOUND;

Object G2int_out_of_memory_handler = UNBOUND;

/* OUT-OF-MEMORY-HANDLER */
Object g2int_out_of_memory_handler()
{
    x_note_fn_call(12,11);
    G2int_unrecoverable_error_p = T;
    return error((SI_Long)1L,"No More Memory");
}

#define set_area_overflow_function(fun) (Area_overflow_function=fun)

/* G2-MEMORY-USAGE */
Object g2int_g2_memory_usage()
{
    Object incff_1_arg;
    SI_Long total, region, ab_loop_bind_;

    x_note_fn_call(12,12);
    total = (SI_Long)0L;
    region = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
  next_loop:
    if (region > ab_loop_bind_)
	goto end_loop;
    incff_1_arg = g2int_g2_region_memory_usage(FIX(region));
    total = total + IFIX(incff_1_arg);
    region = region + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(total));
    return VALUES_1(Qnil);
}

/* G2-MEMORY-USAGE-AS-FLOAT */
Object g2int_g2_memory_usage_as_float()
{
    Object temp_1;
    SI_Long region, ab_loop_bind_;
    double total, temp, temp_2;

    x_note_fn_call(12,13);
    total = 0.0;
    region = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
  next_loop:
    if (region > ab_loop_bind_)
	goto end_loop;
    temp = total;
    temp_1 = g2int_g2_region_memory_usage_as_float(FIX(region));
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
    total = temp + temp_2;
    region = region + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(total));
    return VALUES_1(Qnil);
}

/* G2-MEMORY-SIZE */
Object g2int_g2_memory_size()
{
    Object incff_1_arg;
    SI_Long total, region, ab_loop_bind_;

    x_note_fn_call(12,14);
    total = (SI_Long)0L;
    region = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
  next_loop:
    if (region > ab_loop_bind_)
	goto end_loop;
    incff_1_arg = g2int_g2_region_memory_size(FIX(region));
    total = total + IFIX(incff_1_arg);
    region = region + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(FIX(total));
    return VALUES_1(Qnil);
}

/* G2-MEMORY-SIZE-AS-FLOAT */
Object g2int_g2_memory_size_as_float()
{
    Object temp_1;
    SI_Long region, ab_loop_bind_;
    double total, temp, temp_2;

    x_note_fn_call(12,15);
    total = 0.0;
    region = (SI_Long)1L;
    ab_loop_bind_ = IFIX(G2int_number_of_memory_regions);
  next_loop:
    if (region > ab_loop_bind_)
	goto end_loop;
    temp = total;
    temp_1 = g2int_g2_region_memory_size_as_float(FIX(region));
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp_1);
    total = temp + temp_2;
    region = region + (SI_Long)1L;
    goto next_loop;
  end_loop:
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(total));
    return VALUES_1(Qnil);
}

/* G2-MEMORY-AVAILABLE */
Object g2int_g2_memory_available()
{
    Object temp;

    x_note_fn_call(12,16);
    temp = g2int_g2_memory_size();
    return VALUES_1(FIXNUM_MINUS(temp,g2int_g2_memory_usage()));
}

/* G2-MEMORY-AVAILABLE-AS-FLOAT */
Object g2int_g2_memory_available_as_float()
{
    Object temp;
    double temp_1, temp_2;

    x_note_fn_call(12,17);
    temp = g2int_g2_memory_size_as_float();
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = g2int_g2_memory_usage_as_float();
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp_1 - temp_2));
}

/* G2-REGION-MEMORY-USAGE */
Object g2int_g2_region_memory_usage(region_number)
    Object region_number;
{
    x_note_fn_call(12,18);
    if ( !(FIXNUMP(region_number) && FIXNUM_LE(FIX((SI_Long)-128L),
	    region_number) && FIXNUM_LE(region_number,FIX((SI_Long)127L))))
	return VALUES_1(FIX((SI_Long)0L));
    else
	switch (INTEGER_TO_CHAR(region_number)) {
	  case 1:
	    return area_memory_used(Kdynamic);
	  case 2:
	    return area_memory_used(Kstatic);
	  case 3:
	    return g2int_bytes_allocated_for_image_tiles();
	  default:
	    return VALUES_1(FIX((SI_Long)0L));
	}
}

/* G2-REGION-MEMORY-USAGE-AS-FLOAT */
Object g2int_g2_region_memory_usage_as_float(region_number)
    Object region_number;
{
    x_note_fn_call(12,19);
    if ( !(FIXNUMP(region_number) && FIXNUM_LE(FIX((SI_Long)-128L),
	    region_number) && FIXNUM_LE(region_number,FIX((SI_Long)127L))))
	return VALUES_1(float_constant_1);
    else
	switch (INTEGER_TO_CHAR(region_number)) {
	  case 1:
	    return area_memory_used_as_float(Kdynamic);
	  case 2:
	    return area_memory_used_as_float(Kstatic);
	  case 3:
	    return lfloat(g2int_bytes_allocated_for_image_tiles(),
		    float_constant_1);
	  default:
	    return VALUES_1(float_constant_1);
	}
}

/* G2-REGION-MEMORY-SIZE */
Object g2int_g2_region_memory_size(region_number)
    Object region_number;
{
    x_note_fn_call(12,20);
    if ( !(FIXNUMP(region_number) && FIXNUM_LE(FIX((SI_Long)-128L),
	    region_number) && FIXNUM_LE(region_number,FIX((SI_Long)127L))))
	return VALUES_1(FIX((SI_Long)0L));
    else
	switch (INTEGER_TO_CHAR(region_number)) {
	  case 1:
	    return area_memory_limit(Kdynamic);
	  case 2:
	    return area_memory_limit(Kstatic);
	  case 3:
	    return g2int_maximum_bytes_for_image_tiles();
	  default:
	    return VALUES_1(FIX((SI_Long)0L));
	}
}

/* G2-REGION-MEMORY-SIZE-AS-FLOAT */
Object g2int_g2_region_memory_size_as_float(region_number)
    Object region_number;
{
    x_note_fn_call(12,21);
    if ( !(FIXNUMP(region_number) && FIXNUM_LE(FIX((SI_Long)-128L),
	    region_number) && FIXNUM_LE(region_number,FIX((SI_Long)127L))))
	return VALUES_1(float_constant_1);
    else
	switch (INTEGER_TO_CHAR(region_number)) {
	  case 1:
	    return area_memory_limit_as_float(Kdynamic);
	  case 2:
	    return area_memory_limit_as_float(Kstatic);
	  case 3:
	    return lfloat(g2int_maximum_bytes_for_image_tiles(),
		    float_constant_1);
	  default:
	    return VALUES_1(float_constant_1);
	}
}

/* G2-REGION-MEMORY-AVAILABLE */
Object g2int_g2_region_memory_available(region_number)
    Object region_number;
{
    Object temp;

    x_note_fn_call(12,22);
    temp = g2int_g2_region_memory_size(region_number);
    return VALUES_1(FIXNUM_MINUS(temp,
	    g2int_g2_region_memory_usage(region_number)));
}

/* G2-REGION-MEMORY-AVAILABLE-AS-FLOAT */
Object g2int_g2_region_memory_available_as_float(region_number)
    Object region_number;
{
    Object temp;
    double temp_1, temp_2;

    x_note_fn_call(12,23);
    temp = g2int_g2_region_memory_size_as_float(region_number);
    temp_1 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    temp = g2int_g2_region_memory_usage_as_float(region_number);
    temp_2 = DOUBLE_FLOAT_TO_DOUBLE(temp);
    return VALUES_1(DOUBLE_TO_DOUBLE_FLOAT(temp_1 - temp_2));
}

Object G2int_bytes_per_rtl_ptr = UNBOUND;

/* BYTES-PER-SIMPLE-VECTOR */
Object g2int_bytes_per_simple_vector(length_1)
    Object length_1;
{
    x_note_fn_call(12,24);
    return VALUES_1(FIXNUM_ADD(ltimes(FIX((SI_Long)2L),
	    G2int_bytes_per_rtl_ptr),FIXNUM_TIMES(G2int_bytes_per_rtl_ptr,
	    length_1)));
}

/* BYTES-PER-UNSIGNED-BYTE-8-SIMPLE-ARRAY */
Object g2int_bytes_per_unsigned_byte_8_simple_array(vector_length)
    Object vector_length;
{
    Object temp;
    SI_Long temp_1;

    x_note_fn_call(12,25);
    temp = ltimes(FIX((SI_Long)2L),G2int_bytes_per_rtl_ptr);
    temp_1 = IFIX(FIXNUM_ADD(vector_length,
	    FIXNUM_SUB1(G2int_bytes_per_rtl_ptr))) / 
	    IFIX(G2int_bytes_per_rtl_ptr);
    return VALUES_1(FIXNUM_ADD(temp,FIXNUM_TIMES(FIX(temp_1),
	    G2int_bytes_per_rtl_ptr)));
}

/* BYTES-PER-UNSIGNED-BYTE-16-SIMPLE-ARRAY */
Object g2int_bytes_per_unsigned_byte_16_simple_array(vector_length)
    Object vector_length;
{
    Object temp;
    SI_Long temp_1;

    x_note_fn_call(12,26);
    temp = ltimes(FIX((SI_Long)2L),G2int_bytes_per_rtl_ptr);
    temp_1 = (IFIX(vector_length) + ((SI_Long)2L - (SI_Long)1L)) / (SI_Long)2L;
    return VALUES_1(FIXNUM_ADD(temp,FIXNUM_TIMES(FIX(temp_1),
	    G2int_bytes_per_rtl_ptr)));
}

/* BYTES-PER-DOUBLE-FLOAT-SIMPLE-ARRAY */
Object g2int_bytes_per_double_float_simple_array(vector_length)
    Object vector_length;
{
    x_note_fn_call(12,27);
    return VALUES_1(FIXNUM_ADD(ltimes(FIX((SI_Long)2L),
	    G2int_bytes_per_rtl_ptr),
	    FIXNUM_TIMES(G2int_bytes_per_rtl_double,vector_length)));
}

/* BYTES-PER-LONG-SIMPLE-ARRAY */
Object g2int_bytes_per_long_simple_array(vector_length)
    Object vector_length;
{
    Object temp;

    x_note_fn_call(12,28);
    temp = FIXNUM_ADD(ltimes(FIX((SI_Long)2L),G2int_bytes_per_rtl_ptr),
	    FIXNUM_TIMES(G2int_bytes_per_rtl_int64,vector_length));
    return VALUES_1(temp);
}

/* BYTES-PER-SIMPLE-STRING */
Object g2int_bytes_per_simple_string(vector_length)
    Object vector_length;
{
    Object temp;
    SI_Long temp_1;

    x_note_fn_call(12,29);
    temp = ltimes(FIX((SI_Long)2L),G2int_bytes_per_rtl_ptr);
    temp_1 = IFIX(vector_length) / IFIX(G2int_bytes_per_rtl_ptr);
    return VALUES_1(FIXNUM_ADD(temp,FIXNUM_TIMES(FIX(temp_1),
	    G2int_bytes_per_rtl_ptr)));
}

static Object list_constant;       /* # */

static Object list_constant_1;     /* # */

/* BYTES-PER-TYPED-SIMPLE-ARRAY */
Object g2int_bytes_per_typed_simple_array(element_type,length_1)
    Object element_type, length_1;
{
    Object temp;

    x_note_fn_call(12,30);
    if (EQ(element_type,T))
	temp = g2int_bytes_per_simple_vector(length_1);
    else if (EQ(element_type,Qsingle_float) || EQ(element_type,Qdouble_float))
	temp = g2int_bytes_per_double_float_simple_array(length_1);
    else if (EQ(element_type,Qstring_char) || EQ(element_type,Qcharacter))
	temp = g2int_bytes_per_simple_string(length_1);
    else if (EQUAL(element_type,list_constant))
	temp = g2int_bytes_per_unsigned_byte_8_simple_array(length_1);
    else if (EQUAL(element_type,list_constant_1))
	temp = g2int_bytes_per_unsigned_byte_16_simple_array(length_1);
    else
	temp = g2int_bytes_per_simple_vector(length_1);
    return VALUES_1(temp);
}

void os_memory_INIT()
{
    Object out_of_memory_handler;
    Object Qg2int_bytes_per_rtl_int64, AB_package, Qg2int_bytes_per_rtl_double;
    Object Qg2int_measured_memory_tab_setting;
    Object Qg2int_desired_memory_tab_setting;
    Object Qg2int_default_memory_tab_setting;
    Object Qg2int_minimum_memory_tab_setting;
    Object Qg2int_size_of_chunks_for_allocate_to_target, string_constant_17;
    Object string_constant_16, Qg2int_image_tile, string_constant_15;
    Object string_constant_14, string_constant_13, string_constant_12;

    x_note_fn_call(12,31);
    SET_PACKAGE("AB");
    G2int_default_bytes_for_renderings = FIX((SI_Long)2500000L);
    G2int_minimum_bytes_for_renderings = FIX((SI_Long)400000L);
    string_constant_12 = STATIC_STRING("rgn1lmt");
    string_constant_13 = STATIC_STRING("G2RGN1LMT");
    if (G2int_region_1_info == UNBOUND)
	G2int_region_1_info = g2int_make_region_info(FIX((SI_Long)1L),
		Kdynamic,string_constant_12,string_constant_13);
    string_constant_14 = STATIC_STRING("rgn2lmt");
    string_constant_15 = STATIC_STRING("G2RGN2LMT");
    if (G2int_region_2_info == UNBOUND)
	G2int_region_2_info = g2int_make_region_info(FIX((SI_Long)2L),
		Kstatic,string_constant_14,string_constant_15);
    AB_package = STATIC_PACKAGE("AB");
    Qg2int_image_tile = STATIC_SYMBOL("IMAGE-TILE",AB_package);
    string_constant_16 = STATIC_STRING("rgn3lmt");
    string_constant_17 = STATIC_STRING("G2RGN3LMT");
    if (G2int_region_3_info == UNBOUND)
	G2int_region_3_info = g2int_make_region_info(FIX((SI_Long)3L),
		Qg2int_image_tile,string_constant_16,string_constant_17);
    if (G2int_all_region_info == UNBOUND)
	G2int_all_region_info = make_array(1,FIX((SI_Long)3L));
    if (G2int_number_of_memory_regions == UNBOUND)
	G2int_number_of_memory_regions = Nil;
    Qg2int_telewindows = STATIC_SYMBOL("TELEWINDOWS",AB_package);
    string_constant = STATIC_STRING("TWRGN1LMT");
    string_constant_1 = STATIC_STRING("TWRGN2LMT");
    string_constant_2 = STATIC_STRING("TWRGN3LMT");
    Qg2int_gsi = STATIC_SYMBOL("GSI",AB_package);
    string_constant_3 = STATIC_STRING("GSIRGN1LMT");
    string_constant_4 = STATIC_STRING("GSIRGN2LMT");
    Qg2int_ab = STATIC_SYMBOL("AB",AB_package);
    Qg2int_alphaosf = STATIC_SYMBOL("ALPHAOSF",AB_package);
    Qg2int_size_of_chunks_for_allocate_to_target = 
	    STATIC_SYMBOL("SIZE-OF-CHUNKS-FOR-ALLOCATE-TO-TARGET",AB_package);
    SET_SYMBOL_VALUE(Qg2int_size_of_chunks_for_allocate_to_target,
	    FIX((SI_Long)4000000L));
    float_constant = STATIC_FLOAT(1.0995E+12);
    float_constant_1 = STATIC_FLOAT(0.0);
    Qg2int_minimum_memory_tab_setting = 
	    STATIC_SYMBOL("MINIMUM-MEMORY-TAB-SETTING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_minimum_memory_tab_setting,FIX((SI_Long)15L));
    Qg2int_default_memory_tab_setting = 
	    STATIC_SYMBOL("DEFAULT-MEMORY-TAB-SETTING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_default_memory_tab_setting,FIX((SI_Long)30L));
    Qg2int_desired_memory_tab_setting = 
	    STATIC_SYMBOL("DESIRED-MEMORY-TAB-SETTING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_desired_memory_tab_setting,FIX((SI_Long)45L));
    Qg2int_measured_memory_tab_setting = 
	    STATIC_SYMBOL("MEASURED-MEMORY-TAB-SETTING",AB_package);
    SET_SYMBOL_VALUE(Qg2int_measured_memory_tab_setting,FIX((SI_Long)60L));
    string_constant_5 = STATIC_STRING("");
    string_constant_6 = STATIC_STRING("0");
    string_constant_7 = STATIC_STRING("G2");
    string_constant_8 = STATIC_STRING("Telewindows");
    string_constant_9 = STATIC_STRING("unsupplied");
    string_constant_10 = STATIC_STRING("unknown");
    string_constant_11 = STATIC_STRING("GSI");
    if (G2int_unrecoverable_error_p == UNBOUND)
	G2int_unrecoverable_error_p = Nil;
    if (G2int_out_of_memory_handler == UNBOUND)
	G2int_out_of_memory_handler = Nil;
    out_of_memory_handler = STATIC_FUNCTION(g2int_out_of_memory_handler,
	    NIL,FALSE,0,0);
    G2int_out_of_memory_handler = out_of_memory_handler;
    set_area_overflow_function(G2int_out_of_memory_handler);
    G2int_bytes_per_rtl_ptr = G2int_staris_g2_enterpriseqmstar ? 
	    FIX((SI_Long)8L) : FIX((SI_Long)4L);
    Qg2int_bytes_per_rtl_double = STATIC_SYMBOL("BYTES-PER-RTL-DOUBLE",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_bytes_per_rtl_double,FIX((SI_Long)8L));
    Qg2int_bytes_per_rtl_int64 = STATIC_SYMBOL("BYTES-PER-RTL-INT64",
	    AB_package);
    SET_SYMBOL_VALUE(Qg2int_bytes_per_rtl_int64,FIX((SI_Long)8L));
    list_constant = STATIC_LIST((SI_Long)2L,Qunsigned_byte,FIX((SI_Long)8L));
    list_constant_1 = STATIC_LIST((SI_Long)2L,Qunsigned_byte,
	    FIX((SI_Long)16L));
}
